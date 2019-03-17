#include "common.h"

#define FIRST_OBJ 1234

#define GC_PAGE_SIZE 1024*4

#define GC_INIT_PAGE_NUM 4

struct sHeapPage_ {
    void* mMem;
    int mOffset;
};

typedef struct sHeapPage_ sHeapPage;

sHeapPage* gHeapPages;
int gSizeHeapPages;
int gNumHeapPages;

sCLClass* gLambdaClass = NULL;

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
    unsigned char mNoneFreeHandle:1;
    unsigned char mMalloced:1;
    int mNextFreeHandle;         // -1 for NULL. index of mHandles
    int mNextFreeMemHandle;      // -1 for NULL. index of mHandles
    unsigned short mSize;
    unsigned short mRefferenceCount;
    void* mMem;
};

typedef struct sHandle_ sHandle;

struct sCLHeapManager_ {
    sHandle* mHandles;
    int mSizeHandles;

    unsigned char* mMarkFlags;

    int mFreeHandles;    // -1 for NULL. index of mHandles
    int mFreeMemHandles;  /// -1 for NULL. index of mHandles
};

typedef struct sCLHeapManager_ sCLHeapManager;

static sCLHeapManager gCLHeap;

void compaction()
{
    int num_heap_pages = 0;
    unsigned int heap_page_offset = 0;

    int size_heap_pages = gSizeHeapPages * 2;
    char** pages = MCALLOC(1, sizeof(char*)*size_heap_pages);
    pages[num_heap_pages] = MCALLOC(1, GC_PAGE_SIZE);

    gCLHeap.mFreeMemHandles = -1;

    /// chain free handles ///
    gCLHeap.mFreeHandles = -1;

    int i;
    for(i=0; i<gCLHeap.mSizeHandles; i++) {
        if(gCLHeap.mHandles[i].mNoneFreeHandle) {
            BOOL malloced = gCLHeap.mHandles[i].mMalloced;
            int size = gCLHeap.mHandles[i].mSize;

            if(!malloced) {
                alignment(&heap_page_offset);

                if(heap_page_offset + size >= GC_PAGE_SIZE) {
                    num_heap_pages++;

                    pages[num_heap_pages] = MCALLOC(1, GC_PAGE_SIZE);
                    heap_page_offset = 0;

                    if(num_heap_pages == size_heap_pages) {
                        int new_size = size_heap_pages * 2;

                        pages = MREALLOC(pages, sizeof(char*)*new_size);

                        memset(pages + size_heap_pages, 0, sizeof(char*)*(new_size-size_heap_pages));

                        size_heap_pages = new_size;
                    }
                }

                char* new_object_mem = pages[num_heap_pages] + heap_page_offset;
                memcpy(new_object_mem, gCLHeap.mHandles[i].mMem, size);

                gCLHeap.mHandles[i].mMem = new_object_mem;
                heap_page_offset += size;

                alignment(&heap_page_offset);
            }
        }
        else {
            if(gCLHeap.mHandles[i].mMalloced) {
                MFREE(gCLHeap.mHandles[i].mMem);
            }

            gCLHeap.mHandles[i].mMem = NULL;
            gCLHeap.mHandles[i].mNextFreeHandle = -1;
            gCLHeap.mHandles[i].mNextFreeMemHandle = -1;
            gCLHeap.mHandles[i].mSize = 0;
            gCLHeap.mHandles[i].mRefferenceCount = 0;
            gCLHeap.mHandles[i].mMalloced = FALSE;
            gCLHeap.mHandles[i].mNoneFreeHandle = FALSE;

            /// chain free handles ///
            int top_of_free_handle = gCLHeap.mFreeHandles;
            gCLHeap.mFreeHandles = i;
            gCLHeap.mHandles[i].mNextFreeHandle = top_of_free_handle;
        }
    }

    for(i=0; i<=gNumHeapPages; i++) {
        MFREE(gHeapPages[i].mMem);
    }

    if(num_heap_pages >= gSizeHeapPages) {
        int new_size = (gSizeHeapPages+num_heap_pages) * 2;

        gHeapPages = MREALLOC(gHeapPages, sizeof(sHeapPage)*new_size);

        memset(gHeapPages + gSizeHeapPages, 0, sizeof(sHeapPage)*(new_size-gSizeHeapPages));

        gSizeHeapPages = new_size;
    }

    for(i=0; i<=num_heap_pages; i++) {
        gHeapPages[i].mMem = pages[i];
        gHeapPages[i].mOffset = GC_PAGE_SIZE;
    }

    gHeapPages[num_heap_pages].mOffset = heap_page_offset;
    gNumHeapPages = num_heap_pages;

    MFREE(pages);
}

void heap_init(int heap_size, int size_handles)
{
    gCLHeap.mHandles = MCALLOC(1, sizeof(sHandle)*size_handles);
    gCLHeap.mSizeHandles = size_handles;

    gCLHeap.mMarkFlags = MCALLOC(1, sizeof(unsigned char)*gCLHeap.mSizeHandles);

    gCLHeap.mFreeHandles = -1;

    /// chain free handles ///
    int i;
    for(i=0; i<size_handles; i++) {
        gCLHeap.mHandles[i].mNextFreeMemHandle = -1;

        int top_of_free_handle = gCLHeap.mFreeHandles;
        gCLHeap.mFreeHandles = i;
        gCLHeap.mHandles[i].mNextFreeHandle = top_of_free_handle;
    }

    gCLHeap.mFreeMemHandles = -1;

    gSizeHeapPages = GC_INIT_PAGE_NUM;
    gHeapPages = MCALLOC(1, sizeof(sHeapPage)*gSizeHeapPages);

    gNumHeapPages = 0;
    gHeapPages[0].mMem = MCALLOC(1, GC_PAGE_SIZE);
    gHeapPages[0].mOffset = 0;
}

static void delete_all_object();

void heap_final()
{
    delete_all_object();
    int i;
    for(i=0; i<=gNumHeapPages; i++) {
        MFREE(gHeapPages[i].mMem);
    }
    MFREE(gHeapPages);
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
    if(obj >= FIRST_OBJ && obj < FIRST_OBJ + gCLHeap.mSizeHandles) {
        int handle_num = obj - FIRST_OBJ;
        
        return gCLHeap.mHandles[handle_num].mNoneFreeHandle;
    }
    else {
        return FALSE;
    }
}

static void free_handle(unsigned int handle_num)
{
    if(gCLHeap.mHandles[handle_num].mNoneFreeHandle) {
        CLObject obj = handle_num + FIRST_OBJ;

        sCLObject* data = CLOBJECT(obj);
        sCLClass* klass = data->mClass;

        gCLHeap.mHandles[handle_num].mNoneFreeHandle = FALSE;

        if(gCLHeap.mHandles[handle_num].mMalloced) {
            MFREE(gCLHeap.mHandles[handle_num].mMem);

            gCLHeap.mHandles[handle_num].mMem = NULL;
            gCLHeap.mHandles[handle_num].mMalloced = FALSE;
            gCLHeap.mHandles[handle_num].mSize = 0;
            gCLHeap.mHandles[handle_num].mRefferenceCount = 0;
            gCLHeap.mHandles[handle_num].mNextFreeMemHandle = -1;

            /// chain free handles ///
            int top_of_free_handle = gCLHeap.mFreeHandles;
            gCLHeap.mFreeHandles = handle_num;
            gCLHeap.mHandles[handle_num].mNextFreeHandle = top_of_free_handle;
        }
        else {
            memset(gCLHeap.mHandles[handle_num].mMem, 0, gCLHeap.mHandles[handle_num].mSize);

            gCLHeap.mHandles[handle_num].mNextFreeHandle = -1;

            /// chain free handles ///
            int top_of_free_handle = gCLHeap.mFreeMemHandles;
            gCLHeap.mFreeMemHandles = handle_num;
            gCLHeap.mHandles[handle_num].mNextFreeMemHandle = top_of_free_handle;
        }
    }
}

static void call_finalizer(unsigned int handle_num)
{
    if(gCLHeap.mHandles[handle_num].mNoneFreeHandle) {
        CLObject obj = handle_num + FIRST_OBJ;

        sCLObject* data = CLOBJECT(obj);
        sCLClass* klass = data->mClass;

        /// call the destructor ///
        int array_num = ((sCLHeapMem*)data)->mArrayNum;

        if(klass && klass->mFreeFun && array_num == -1) {
            klass->mFreeFun(obj);
        }

        if(array_num == -2) {   // block, regex
        }
        else if(array_num == -1) {
            (void)free_object(obj);
        }
        else {
            free_array(obj);
        }
    }
}

void inc_refference_count(CLObject obj, CLObject prev_obj, BOOL value_is_object)
{
}

void dec_refference_count(CLObject obj, BOOL value_is_object)
{
}

void free_global_stack_objects(sVMInfo* info, CLObject result_object, int num_global_stack_ptr, CLVALUE* lvar, int num_params)
{
    info->mGlobalStackPtr = info->mGlobalStack + num_global_stack_ptr;
}

void mark_object(CLObject obj, unsigned char* mark_flg)
{
    if(is_valid_object(obj)) {
        if(mark_flg[obj - FIRST_OBJ] == FALSE) {
            mark_flg[obj - FIRST_OBJ] = TRUE;

            sCLHeapMem* object = get_object_pointer(obj);

            if(object != NULL) {
                sCLClass* klass = object->mClass;
                int array_num = object->mArrayNum;

                /// mark objects which is contained in ///
                if(array_num == -1) {
                    if(klass && !(klass->mFlags & CLASS_FLAGS_NO_FREE_OBJECT)) {
                        object_mark_fun(obj, mark_flg);
                    }
                }
                else if(array_num >= 0) {
                    array_mark_fun(obj, mark_flg);
                }
                else if(klass == gLambdaClass) {
                    block_mark_fun(obj, mark_flg);
                }
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
}

static void free_objects(unsigned char* mark_flg)
{
    int i;
    unsigned char* mem;

    // call all destructor before free object ///
    for(i=0; i<gCLHeap.mSizeHandles; i++) {
        if(!mark_flg[i]) {
            call_finalizer(i);
        }
    }

    /// free object ///
    for(i=0; i<gCLHeap.mSizeHandles; i++) {
        if(!mark_flg[i]) {
            free_handle(i);
        }
    }
}

static void free_malloced_memory()
{
    int i;
    for(i=0; i<gCLHeap.mSizeHandles; i++) {
        if(gCLHeap.mHandles[i].mNoneFreeHandle) {
            if(gCLHeap.mHandles[i].mMalloced) {
                MFREE(gCLHeap.mHandles[i].mMem);
            }
        }
    }
}

static void delete_all_object()
{
    memset(gCLHeap.mMarkFlags, 0, sizeof(unsigned char)*gCLHeap.mSizeHandles);

    unsigned char* mark_flg = gCLHeap.mMarkFlags;

    free_objects(mark_flg);

    free_malloced_memory();
}

void mark_and_store_class_field(sCLClass* klass, int field_index, CLVALUE cl_value)
{
    sCLField* field = klass->mClassFields + field_index;
    CLObject prev_obj = field->mValue.mObjectValue;
    field->mValue = cl_value;

    sCLType* field_type = field->mResultType;

    char* field_class_name = CONS_str(&klass->mConst, field_type->mClassNameOffset);

    sCLClass* field_class = get_class(field_class_name, FALSE);

    BOOL value_is_object = !(field_class->mFlags & CLASS_FLAGS_NO_FREE_OBJECT);

    inc_refference_count(cl_value.mObjectValue, prev_obj, value_is_object);
}

void gc(sVMInfo* info)
{
    if(!info->in_finalize_method) {
        gLambdaClass = get_class("lambda", FALSE);

        memset(gCLHeap.mMarkFlags, 0, sizeof(unsigned char)*gCLHeap.mSizeHandles);

        /// mark class fields ///
        mark_all_class_fields(gCLHeap.mMarkFlags);

        /// mark sig handlers ////
        mark_sighandlers(gCLHeap.mMarkFlags);

        mark(gCLHeap.mMarkFlags);

        free_objects(gCLHeap.mMarkFlags);
    }
}

#define GC_TIMING 1024
#define COMPACTION_TIMING 1000

CLObject alloc_heap_mem(unsigned int size, sCLClass* klass, int array_num, sVMInfo* info)
{
    int handle;
    CLObject obj;

    alignment(&size);

    static int gc_timing = 0;

    if(gCLHeap.mFreeMemHandles == -1) {
        if(gc_timing % GC_TIMING == 0) {
            gc(info);
        }

        gc_timing++;
    }

    /// get a free handle from linked list ///
    handle = gCLHeap.mFreeMemHandles;

    int handle_before = handle;
    while(handle != -1) {
        if(size <= gCLHeap.mHandles[handle].mSize) {
            break;
        }
        handle_before = handle;
        handle = gCLHeap.mHandles[handle].mNextFreeMemHandle;
    }

    /// no free mem handle ///
    if(handle == -1) {
        handle = gCLHeap.mFreeHandles;

        /// no handle, get new one ///
        if(handle == -1) {
            const int new_offset_size = (gCLHeap.mSizeHandles + 1) * 2;

            gCLHeap.mHandles = MREALLOC(gCLHeap.mHandles, sizeof(sHandle)*new_offset_size);
            memset(gCLHeap.mHandles + gCLHeap.mSizeHandles, 0, sizeof(sHandle)*(new_offset_size - gCLHeap.mSizeHandles));

            gCLHeap.mMarkFlags = MREALLOC(gCLHeap.mMarkFlags, sizeof(unsigned char)*new_offset_size);
            memset(gCLHeap.mMarkFlags + gCLHeap.mSizeHandles, 0, sizeof(unsigned char)*(new_offset_size - gCLHeap.mSizeHandles));

            /// chain free handles ///
            int i;
            for(i=gCLHeap.mSizeHandles; i<new_offset_size; i++) {
                int top_of_free_handle = gCLHeap.mFreeHandles;
                gCLHeap.mFreeHandles = i;
                gCLHeap.mHandles[i].mNextFreeHandle = top_of_free_handle;
                gCLHeap.mHandles[i].mNextFreeMemHandle = -1;
            }

            gCLHeap.mSizeHandles = new_offset_size;

            handle = gCLHeap.mFreeHandles;
        }

        gCLHeap.mHandles[handle].mNoneFreeHandle = TRUE;
        gCLHeap.mHandles[handle].mMem = NULL;
        gCLHeap.mHandles[handle].mMalloced = FALSE;
        gCLHeap.mHandles[handle].mSize = 0;
        gCLHeap.mHandles[handle].mRefferenceCount = 0;
        gCLHeap.mHandles[handle].mNextFreeMemHandle = -1;

        gCLHeap.mFreeHandles = gCLHeap.mHandles[handle].mNextFreeHandle;
    }
    /// getted free mem handle ///
    else {
        if(handle == gCLHeap.mFreeMemHandles) {
            gCLHeap.mFreeMemHandles = gCLHeap.mHandles[handle].mNextFreeMemHandle;
            gCLHeap.mHandles[handle].mNextFreeMemHandle = -1;

            gCLHeap.mHandles[handle].mNoneFreeHandle = TRUE;
        }
        else {
            gCLHeap.mHandles[handle_before].mNextFreeMemHandle = gCLHeap.mHandles[handle].mNextFreeMemHandle;

            gCLHeap.mHandles[handle].mNoneFreeHandle = TRUE;
        }
    }
    
    obj = handle + FIRST_OBJ;

    /// if gettend handle has no memory, allocated
    if(gCLHeap.mHandles[handle].mMem == NULL) {
        BOOL malloced = FALSE;
        gCLHeap.mHandles[handle].mMem = alloc_mem_from_page(size, &malloced);
        gCLHeap.mHandles[handle].mMalloced = malloced;
        gCLHeap.mHandles[handle].mSize = size;
        gCLHeap.mHandles[handle].mNextFreeHandle = -1;
        gCLHeap.mHandles[handle].mNextFreeMemHandle = -1;

        gCLHeap.mHandles[handle].mNoneFreeHandle = TRUE;
    }

    sCLHeapMem* object_ptr = get_object_pointer(obj);

    object_ptr->mSize = size;

    object_ptr->mClass = klass;
    object_ptr->mType = NULL;
    object_ptr->mArrayNum = array_num;

    return obj;
}
