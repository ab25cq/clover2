#include "common.h"

#define FIRST_OBJ 1234

#define GC_PAGE_SIZE 1024*2*2

#define GC_INIT_PAGE_NUM 4

struct sHeapPage_ {
    void* mMem;
    int mOffset;
};

typedef struct sHeapPage_ sHeapPage;

sHeapPage* gHeapPages;
int gSizeHeapPages;
int gNumHeapPages;

void* alloc_mem_from_page(unsigned int size, BOOL* malloced)
{
    if(size >= GC_PAGE_SIZE) {
        *malloced = TRUE;
        return MCALLOC(1, size);
    }

    if(gHeapPages[gNumHeapPages].mOffset + size >= GC_PAGE_SIZE) {
        gNumHeapPages++;

        if(gNumHeapPages == gSizeHeapPages) {
            int new_size = gSizeHeapPages * 2;

            gHeapPages = MREALLOC(gHeapPages, sizeof(sHeapPage)*new_size);

            memset(gHeapPages + gSizeHeapPages, 0, sizeof(sHeapPage)*(new_size-gSizeHeapPages));

            int i;

            gSizeHeapPages = new_size;
        }

        gHeapPages[gNumHeapPages].mMem = MCALLOC(1, GC_PAGE_SIZE);
        gHeapPages[gNumHeapPages].mOffset = 0;
    }

    void* result = gHeapPages[gNumHeapPages].mMem + gHeapPages[gNumHeapPages].mOffset;
    *malloced = FALSE;
    gHeapPages[gNumHeapPages].mOffset += size;

    return result;
}

struct sHandle_ {
    BOOL mNoneFreeHandle;
    void* mMem;
    int mNextFreeHandle;         // -1 for NULL. index of mHandles
    BOOL mMalloced;
    BOOL mSize;
};

typedef struct sHandle_ sHandle;

struct sCLHeapManager_ {
    sHandle* mHandles;
    int mSizeHandles;
    int mNumHandles;

    int mFreeHandles;    // -1 for NULL. index of mHandles
};

typedef struct sCLHeapManager_ sCLHeapManager;

static sCLHeapManager gCLHeap;

void heap_init(int heap_size, int size_hadles)
{
    gCLHeap.mHandles = MCALLOC(1, sizeof(sHandle)*size_hadles);
    gCLHeap.mSizeHandles = size_hadles;
    gCLHeap.mNumHandles = 0;

    gCLHeap.mFreeHandles = -1;

    gSizeHeapPages = GC_INIT_PAGE_NUM;
    gHeapPages = MCALLOC(1, sizeof(sHeapPage)*gSizeHeapPages);

    int i;
    for(i=0; i<gSizeHeapPages; i++) {
        gHeapPages[i].mMem = MCALLOC(1, GC_PAGE_SIZE);
        gHeapPages[i].mOffset = 0;
    }

    gNumHeapPages = 0;
}

static void delete_all_object();

void heap_final()
{
    delete_all_object();
    int i;
    for(i=0; i<=gNumHeapPages; i++) {
        MFREE(gHeapPages[i].mMem);
    }
    MFREE(gCLHeap.mHandles);
}

sCLHeapMem* get_object_pointer(CLObject obj)
{
    sCLHeapMem* result;

    const unsigned int index = obj - FIRST_OBJ;
    result = (sCLHeapMem*)(gCLHeap.mHandles[index].mMem);

    return result;
}

BOOL is_valid_object(CLObject obj)
{
    BOOL result;

    result = obj >= FIRST_OBJ && obj < FIRST_OBJ + gCLHeap.mNumHandles;

    return result;
}

void mark_object(CLObject obj, unsigned char* mark_flg)
{
    sCLClass* lambda_class = get_class("lambda");

    if(is_valid_object(obj)) {
        if(mark_flg[obj - FIRST_OBJ] == FALSE) {
            mark_flg[obj - FIRST_OBJ] = TRUE;

            sCLHeapMem* object = get_object_pointer(obj);

            sCLClass* klass = object->mClass;
            int array_num = object->mArrayNum;

            /// mark objects which is contained in ///
            if(array_num == -1) {
                if(klass && !(klass->mFlags & CLASS_FLAGS_PRIMITIVE)) {
                    object_mark_fun(obj, mark_flg);
                }
            }
            else if(array_num >= 0) {
                array_mark_fun(obj, mark_flg);
            }
            else if(klass == lambda_class) {
                block_mark_fun(obj, mark_flg);
            }
        }
    }
}

static void mark_all_class_fields(unsigned char* mark_flg)
{
    sClassTable* p = gHeadClassTable;

    while(p) {
        sCLClass* klass = p->mItem;

        int i;
        for(i=0; i<klass->mNumClassFields; i++) {
            sCLField* field = klass->mClassFields + i;

            mark_object(field->mValue.mObjectValue, mark_flg);
        }

        p = p->mNextClass;
    }
}

static void mark_sighandlers(unsigned char* mark_flg)
{
    int i;
    for(i=0; i<SIGMAX; i++) {
        CLObject obj = signal_handler_object[i];

        if(obj != 0) {
            mark_object(obj, mark_flg);
        }
    }
}

static void mark(unsigned char* mark_flg)
{
    int i;
    sCLStack* it;

    /// mark stack ///
    it = gHeadStack;
    while(it) {
        int len = *it->mStackPtr - it->mStack;

        for(i=0; i<len; i++) {
            CLVALUE obj = it->mStack[i];
            mark_object(obj.mObjectValue, mark_flg);
        }

        it = it->mNextStack;
    }

    /// mark class fields ///
    mark_all_class_fields(mark_flg);

    /// mark sig handlers ////
    mark_sighandlers(mark_flg);
}

static void compaction(unsigned char* mark_flg)
{
    int i;
    unsigned char* mem;

    /// call finalizer before compaction ///
    for(i=0; i<gCLHeap.mNumHandles; i++) {
        if(gCLHeap.mHandles[i].mNoneFreeHandle) {
            void* data = (void*)(gCLHeap.mHandles[i].mMem);
            sCLClass* klass = ((sCLHeapMem*)data)->mClass;
            int array_num = ((sCLHeapMem*)data)->mArrayNum;

            CLObject obj = i + FIRST_OBJ;

            /// this is not a marked object ///
            if(!mark_flg[i]) {
                /// call the destructor ///
                if(klass) {
                    if(klass->mFlags & CLASS_FLAGS_NO_FREE_OBJECT) {
                    }
                    else {
                        if(array_num == -1) {
                            (void)free_object(obj);
                        }
                        else if(array_num >= 0) {
                            free_array(obj);
                        }

                        if(klass->mFreeFun) {
                            klass->mFreeFun(obj);
                        }
                    }
                }
            }
        }
    }

    /// go to free mem ///
    for(i=0; i<gCLHeap.mNumHandles; i++) {
        if(gCLHeap.mHandles[i].mNoneFreeHandle) {
            void* data = (void*)(gCLHeap.mHandles[i].mMem);
            sCLClass* klass = ((sCLHeapMem*)data)->mClass;

            CLObject obj = i + FIRST_OBJ;

            /// this is not a marked object ///
            if(!mark_flg[i]) {
                gCLHeap.mHandles[i].mNoneFreeHandle = FALSE;

                memset(gCLHeap.mHandles[i].mMem, 0, gCLHeap.mHandles[i].mSize);

                /// chain free handles ///
                int top_of_free_handle = gCLHeap.mFreeHandles;
                gCLHeap.mFreeHandles = i;
                gCLHeap.mHandles[i].mNextFreeHandle = top_of_free_handle;
            }
        }
    }
}

static void free_malloced_memory()
{
    int i;
    for(i=0; i<gCLHeap.mNumHandles; i++) {
        if(gCLHeap.mHandles[i].mNoneFreeHandle) {
            if(gCLHeap.mHandles[i].mMalloced) {
                MFREE(gCLHeap.mHandles[i].mMem);
            }
        }
    }
}

static void delete_all_object()
{
    unsigned char* mark_flg;

    mark_flg = MCALLOC(1, gCLHeap.mNumHandles);

    compaction(mark_flg);

    MFREE(mark_flg);

    free_malloced_memory();
}

void gc()
{
    unsigned char* mark_flg;

    mark_flg = MCALLOC(1, gCLHeap.mNumHandles);

    mark(mark_flg);

    compaction(mark_flg);

    MFREE(mark_flg);
}

#define GC_TIMING 10000

CLObject alloc_heap_mem(unsigned int size, sCLClass* klass, int array_num)
{
    int handle;
    CLObject obj;

    alignment(&size);

    static int gc_time = 0;
    gc_time++;

    /// get a free handle from linked list ///
    if(gCLHeap.mFreeHandles >= 0) {
        handle = gCLHeap.mFreeHandles;

        int handle_before = handle;
        while(handle != -1) {
            if(size <= gCLHeap.mHandles[handle].mSize) {
                break;
            }
            handle_before = handle;
            handle = gCLHeap.mHandles[handle].mNextFreeHandle;
        }

        if(handle == -1) {
            if((gc_time % GC_TIMING) == 0) gc();

            if(gCLHeap.mNumHandles == gCLHeap.mSizeHandles) {
                const int new_offset_size = (gCLHeap.mSizeHandles + 1) * 10;

                gCLHeap.mHandles = MREALLOC(gCLHeap.mHandles, sizeof(sHandle)*new_offset_size);
                memset(gCLHeap.mHandles + gCLHeap.mSizeHandles, 0, sizeof(sHandle)*(new_offset_size - gCLHeap.mSizeHandles));

                gCLHeap.mSizeHandles = new_offset_size;
            }

            handle = gCLHeap.mNumHandles;
            gCLHeap.mNumHandles++;
        }
        else if(handle == gCLHeap.mFreeHandles) {
            gCLHeap.mFreeHandles = gCLHeap.mHandles[handle].mNextFreeHandle;
            gCLHeap.mHandles[handle].mNextFreeHandle = -1;

            gCLHeap.mHandles[handle].mNoneFreeHandle = TRUE;
        }
        else {
            gCLHeap.mHandles[handle_before].mNextFreeHandle = gCLHeap.mHandles[handle].mNextFreeHandle;

            gCLHeap.mHandles[handle].mNoneFreeHandle = TRUE;
        }
    }
    /// no free handle. get new one ///
    else {
        if((gc_time % GC_TIMING) == 0) gc();

        if(gCLHeap.mNumHandles == gCLHeap.mSizeHandles) {
            const int new_offset_size = (gCLHeap.mSizeHandles + 1) * 10;

            gCLHeap.mHandles = MREALLOC(gCLHeap.mHandles, sizeof(sHandle)*new_offset_size);
            memset(gCLHeap.mHandles + gCLHeap.mSizeHandles, 0, sizeof(sHandle)*(new_offset_size - gCLHeap.mSizeHandles));

            gCLHeap.mSizeHandles = new_offset_size;
        }

        handle = gCLHeap.mNumHandles;
        gCLHeap.mNumHandles++;
    }
    
    obj = handle + FIRST_OBJ;

    if(gCLHeap.mHandles[handle].mMem == NULL) {
        BOOL malloced = FALSE;
        gCLHeap.mHandles[handle].mMem = alloc_mem_from_page(size, &malloced);
        gCLHeap.mHandles[handle].mMalloced = malloced;
        gCLHeap.mHandles[handle].mSize = size;
        gCLHeap.mHandles[handle].mNoneFreeHandle = TRUE;
    }

    sCLHeapMem* object_ptr = get_object_pointer(obj);

    object_ptr->mSize = size;

    object_ptr->mClass = klass;
    object_ptr->mType = NULL;
    object_ptr->mArrayNum = array_num;

    return obj;
}
