#include "common.h"

#define FIRST_OBJ 1234

struct sHandle_ {
    int mOffset;                 // -1 for FreeHandle
    int mNextFreeHandle;         // -1 for NULL. index of mHandles
};

typedef struct sHandle_ sHandle;

struct sCLHeapManager_ {
    unsigned char* mMem;
    unsigned char* mMemB;

    unsigned char* mCurrentMem;
    unsigned char* mSleepMem;

    unsigned int mMemLen;
    unsigned int mMemSize;

    sHandle* mHandles;
    int mSizeHandles;
    int mNumHandles;

    int mFreeHandles;    // -1 for NULL. index of mHandles
};

typedef struct sCLHeapManager_ sCLHeapManager;

static sCLHeapManager gCLHeap;

void heap_init(int heap_size, int size_hadles)
{
    gCLHeap.mMem = MCALLOC(1, heap_size);
    gCLHeap.mMemSize = heap_size;
    gCLHeap.mMemLen = 0;
    gCLHeap.mMemB = MCALLOC(1, heap_size);

    gCLHeap.mCurrentMem = gCLHeap.mMem;
    gCLHeap.mSleepMem = gCLHeap.mMemB;

    gCLHeap.mHandles = MCALLOC(1, sizeof(sHandle)*size_hadles);
    gCLHeap.mSizeHandles = size_hadles;
    gCLHeap.mNumHandles = 0;

    gCLHeap.mFreeHandles = -1;   // -1 for NULL
}

static void delete_all_object();

void heap_final()
{
    delete_all_object();
    MFREE(gCLHeap.mMem);
    MFREE(gCLHeap.mMemB);
    MFREE(gCLHeap.mHandles);
}

sCLHeapMem* get_object_pointer(CLObject obj)
{
    sCLHeapMem* result;

    const unsigned int index = obj - FIRST_OBJ;
    result = (sCLHeapMem*)(gCLHeap.mCurrentMem + gCLHeap.mHandles[index].mOffset);

    return result;
}

static BOOL is_valid_object(CLObject obj)
{
    BOOL result;

    result = obj >= FIRST_OBJ && obj < FIRST_OBJ + gCLHeap.mNumHandles;

    return result;
}

void mark_object(CLObject obj, unsigned char* mark_flg)
{
    if(is_valid_object(obj)) {
        if(mark_flg[obj - FIRST_OBJ] == FALSE) {
            mark_flg[obj - FIRST_OBJ] = TRUE;

            sCLHeapMem* object = get_object_pointer(obj);

            sCLClass* klass = object->mClass;
            int array_num = object->mArrayNum;

            /// mark objects which is contained in ///
            if(klass && !(klass->mFlags & CLASS_FLAGS_PRIMITIVE)) {
                object_mark_fun(obj, mark_flg);
            }
            else if(array_num != -1) {
                array_mark_fun(obj, mark_flg);
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
}

static void compaction(unsigned char* mark_flg)
{
    int i;
    unsigned char* mem;

    memset(gCLHeap.mSleepMem, 0, gCLHeap.mMemSize);
    gCLHeap.mMemLen = 0;

    /// call finalizer before compaction ///
    for(i=0; i<gCLHeap.mNumHandles; i++) {
        if(gCLHeap.mHandles[i].mOffset != -1) {
            void* data = (void*)(gCLHeap.mCurrentMem + gCLHeap.mHandles[i].mOffset);
            sCLClass* klass = ((sCLHeapMem*)data)->mClass;
            int array_num = ((sCLHeapMem*)data)->mArrayNum;

            CLObject obj = i + FIRST_OBJ;

            /// this is not a marked object ///
            if(!mark_flg[i]) {
                /// call the destructor ///
                if(klass && !(klass->mFlags & CLASS_FLAGS_PRIMITIVE) && array_num == -1) {
                    (void)free_object(obj);
                }
            }
        }
    }

    /// go to compaction ///
    for(i=0; i<gCLHeap.mNumHandles; i++) {
        if(gCLHeap.mHandles[i].mOffset != -1) {
            void* data = (void*)(gCLHeap.mCurrentMem + gCLHeap.mHandles[i].mOffset);
            sCLClass* klass = ((sCLHeapMem*)data)->mClass;

            CLObject obj = i + FIRST_OBJ;

            /// this is not a marked object ///
            if(!mark_flg[i]) {
                int top_of_free_handle;

                gCLHeap.mHandles[i].mOffset = -1;

                /// chain free handles ///
                top_of_free_handle = gCLHeap.mFreeHandles;
                gCLHeap.mFreeHandles = i;
                gCLHeap.mHandles[i].mNextFreeHandle = top_of_free_handle;
            }
            /// this is a marked object ///
            else {
                int obj_size = CLHEAPMEM(obj)->mSize;
                
                /// copy object to new heap
                void* src = gCLHeap.mCurrentMem + gCLHeap.mHandles[i].mOffset;
                void* dst = gCLHeap.mSleepMem + gCLHeap.mMemLen;

                memcpy(dst, src, obj_size);

                gCLHeap.mHandles[i].mOffset = gCLHeap.mMemLen;
                gCLHeap.mMemLen += obj_size;
            }
        }
    }

    //// now sleep memory is current ///
    mem = gCLHeap.mSleepMem;
    gCLHeap.mSleepMem = gCLHeap.mCurrentMem;
    gCLHeap.mCurrentMem = mem;
}

static void delete_all_object()
{
    unsigned char* mark_flg;

    mark_flg = MCALLOC(1, gCLHeap.mNumHandles);

    compaction(mark_flg);

    MFREE(mark_flg);
}

static void gc()
{
    unsigned char* mark_flg;

    mark_flg = MCALLOC(1, gCLHeap.mNumHandles);

    mark(mark_flg);
    compaction(mark_flg);

    MFREE(mark_flg);
}

CLObject alloc_heap_mem(int size, sCLClass* klass, int array_num)
{
    int handle;
    CLObject obj;

    if(gCLHeap.mMemLen + size >= gCLHeap.mMemSize) {
        gc();

        /// create new space of object ///
        if(gCLHeap.mMemLen + size >= gCLHeap.mMemSize) {
            BOOL current_is_mem_a = gCLHeap.mMem == gCLHeap.mCurrentMem;

            int new_heap_size = (gCLHeap.mMemSize + size) * 2;


            gCLHeap.mMem = MREALLOC(gCLHeap.mMem, new_heap_size);
            memset(gCLHeap.mMem + gCLHeap.mMemSize, 0, new_heap_size - gCLHeap.mMemSize);

            gCLHeap.mMemB = MREALLOC(gCLHeap.mMemB, new_heap_size);
            memset(gCLHeap.mMemB + gCLHeap.mMemSize, 0, new_heap_size - gCLHeap.mMemSize);

            gCLHeap.mMemSize = new_heap_size;

            if(current_is_mem_a) {
                gCLHeap.mCurrentMem = gCLHeap.mMem;
                gCLHeap.mSleepMem = gCLHeap.mMemB;
            }
            else {
                gCLHeap.mCurrentMem = gCLHeap.mMemB;
                gCLHeap.mSleepMem = gCLHeap.mMem;
            }
        }
    }

    /// get a free handle from linked list ///
    if(gCLHeap.mFreeHandles >= 0) {
        handle = gCLHeap.mFreeHandles;
        gCLHeap.mFreeHandles = gCLHeap.mHandles[handle].mNextFreeHandle;
        gCLHeap.mHandles[handle].mNextFreeHandle = -1;
    }
    /// no free handle. get new one ///
    else {
        if(gCLHeap.mNumHandles == gCLHeap.mSizeHandles) {
            const int new_offset_size = (gCLHeap.mSizeHandles + 1) * 2;


            gCLHeap.mHandles = MREALLOC(gCLHeap.mHandles, sizeof(sHandle)*new_offset_size);
            memset(gCLHeap.mHandles + gCLHeap.mSizeHandles, 0, sizeof(sHandle)*(new_offset_size - gCLHeap.mSizeHandles));
            gCLHeap.mSizeHandles = new_offset_size;
        }

        handle = gCLHeap.mNumHandles;
        gCLHeap.mNumHandles++;
    }
    
    obj = handle + FIRST_OBJ;

    gCLHeap.mHandles[handle].mOffset = gCLHeap.mMemLen;
    gCLHeap.mMemLen += size;

    sCLHeapMem* object_ptr = get_object_pointer(obj);

    object_ptr->mSize = size;
    object_ptr->mClass = klass;
    object_ptr->mArrayNum = array_num;

    return obj;
}
