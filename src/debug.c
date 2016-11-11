#include "debug.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef MDEBUG

ALLOC void* xmalloc(size_t size)
{
    void* buf;

    buf = malloc(size);

    if(buf == NULL) {
        fprintf(stderr, "It is not enough memory");
        exit(1);
    }

    return buf;
}

ALLOC char* xstrdup(char* str)
{
    char* buf;

    buf = strdup(str);

    if(buf == NULL) {
        fprintf(stderr, "It is not enough memory\n");
        exit(1);
    }

    return buf;
}

ALLOC void* xrealloc(void* ptr, size_t size)
{
    void* buf;

    buf = realloc(ptr, size);

    if(buf == NULL) {
        fprintf(stderr, "It is not enough memory\n");
        exit(1);
    }

    return buf;
}

ALLOC void* xcalloc(size_t count, size_t size)
{
    void* buf;

    buf = calloc(count, size);

    if(buf == NULL) {
        fprintf(stderr, "It is not enough memory\n");
        exit(1);
    }

    return buf;
}

#else

static char* xstrncpy(char* des, char* src, int size)
{
    des[size-1] = 0;
    return strncpy(des, src, size-1);
}

static char* xstrncat(char* des, char* str, int size)
{
    des[size-1] = 0;
    return strncat(des, str, size-1);
}

//////////////////////////////////////////////////////////////////////
// for memory leak checking
//////////////////////////////////////////////////////////////////////
#define NAME_SIZE 128

struct _t_malloc_entry
{
    void* mMemory;

    char mFileName[NAME_SIZE];
    int mLine;
    char mFuncName[NAME_SIZE];

    struct _t_malloc_entry* mNextEntry;
};

typedef struct _t_malloc_entry t_malloc_entry;

#define ARRAY_SIZE 65535
static t_malloc_entry* gMallocEntries[ARRAY_SIZE];

void release_entry(void* memory, const char* file_name, int line, const char* func_name)
{
    t_malloc_entry *entry, *next_entry;
#ifdef __64bit__
    unsigned long long hash = ((unsigned long long)memory) % ARRAY_SIZE;
#else
    unsigned long hash = ((unsigned long )memory) % ARRAY_SIZE;
#endif
    
    entry = gMallocEntries[hash];
    if(entry->mMemory == memory) { 
        next_entry = entry->mNextEntry;
        free(entry);
        gMallocEntries[hash] = next_entry;
        return ;
    }
    else {
        while(entry->mNextEntry) {
            if(entry->mNextEntry->mMemory == memory) {
                next_entry = entry->mNextEntry->mNextEntry;
                free(entry->mNextEntry);
                entry->mNextEntry = next_entry;

                return;
            }
            entry = entry->mNextEntry;
        }
    }

#ifdef __64bit__
    fprintf(stderr, "\tinvalid free at file: %s line:%d function:%s() addr:%llx\n", entry->mFileName, entry->mLine, entry->mFuncName, (unsigned long long)entry->mMemory);
#else
    fprintf(stderr, "\tinvalid free at file: %s line:%d function:%s() addr:%lx\n", entry->mFileName, entry->mLine, entry->mFuncName, (unsigned long)entry->mMemory);
#endif
}

//////////////////////////////////////////////////////////////////////
// memory leak checking starts
//////////////////////////////////////////////////////////////////////
void debug_init()
{
    memset(gMallocEntries, 0, sizeof(t_malloc_entry*)*ARRAY_SIZE);
}

//////////////////////////////////////////////////////////////////////
// memory leak checking finish
//////////////////////////////////////////////////////////////////////
void debug_final()
{
    int i;
    t_malloc_entry* entry;

    //fprintf(stderr, "Detecting memory leak...\n");
    for(i=0; i<ARRAY_SIZE; i++) {
        entry = gMallocEntries[i];
      
        while(entry) {
#ifdef __64bit__
            fprintf(stderr, "\tDetected!! at file: %s line:%d function:%s() addr:%llx\n"
                                             , entry->mFileName, entry->mLine
                                             , entry->mFuncName, (unsigned long long)entry->mMemory);
#else
            fprintf(stderr, "\tDetected!! at file: %s line:%d function:%s() addr:%lx\n"
                                             , entry->mFileName, entry->mLine
                                             , entry->mFuncName, (unsigned long)entry->mMemory);
#endif
            entry = entry->mNextEntry;
        }
    }

    //fprintf(stderr, "done.\n");
}

//////////////////////////////////////////////////////////////////////
// malloc for memory leak checking
//////////////////////////////////////////////////////////////////////
ALLOC void* debug_malloc(size_t size, const char* file_name, int line, const char* func_name)
{
    t_malloc_entry* entry;
    int i;
    int hash;
    
    entry = (t_malloc_entry*)malloc(sizeof(t_malloc_entry));

    xstrncpy(entry->mFileName, (char*)file_name, NAME_SIZE);
    entry->mLine = line;
    xstrncpy(entry->mFuncName, (char*)func_name, NAME_SIZE);
    entry->mMemory = malloc(size);
   
#ifdef __64bit__
    hash = (unsigned long long)entry->mMemory % ARRAY_SIZE;
#else
    hash = (unsigned long)entry->mMemory % ARRAY_SIZE;
#endif
    entry->mNextEntry = gMallocEntries[hash];
    gMallocEntries[hash] = entry;

    return entry->mMemory;
}

//////////////////////////////////////////////////////////////////////
// calloc for memory leak checking
//////////////////////////////////////////////////////////////////////
ALLOC void* debug_calloc(size_t count, size_t size, const char* file_name, int line, const char* func_name)
{
    t_malloc_entry* entry;
    int i;
    int hash;
    
    entry = (t_malloc_entry*)malloc(sizeof(t_malloc_entry));

    xstrncpy(entry->mFileName, (char*)file_name, NAME_SIZE);
    entry->mLine = line;
    xstrncpy(entry->mFuncName, (char*)func_name, NAME_SIZE);
    entry->mMemory = calloc(count, size);
   
#ifdef __64bit__
    hash = (unsigned long long)entry->mMemory % ARRAY_SIZE;
#else
    hash = (unsigned long)entry->mMemory % ARRAY_SIZE;
#endif
    entry->mNextEntry = gMallocEntries[hash];
    gMallocEntries[hash] = entry;

    return entry->mMemory;
}


//////////////////////////////////////////////////////////////////////
// realloc for memory leak checking
//////////////////////////////////////////////////////////////////////
#include "common.h"
ALLOC void* debug_realloc(void* memory, size_t size, const char* file_name, int line, const char* func_name)
{
    t_malloc_entry* entry;
    int hash;

    /// delete old entry ///
    if(memory) release_entry(memory, file_name, line, func_name);

    /// add new entry ///
    entry = (t_malloc_entry*)malloc(sizeof(t_malloc_entry));
      
    xstrncpy(entry->mFileName, (char*)file_name, NAME_SIZE);
    entry->mLine = line;
    xstrncpy(entry->mFuncName, (char*)func_name, NAME_SIZE);

    entry->mMemory = realloc(memory, size);
    if(entry->mMemory == NULL) {
        fprintf(stderr, "file name(%s) func_name(%s) line %d. false in allocating memory.", file_name, func_name, line);
        exit(1);
    }

#ifdef __64bit__
    hash = (unsigned long long)entry->mMemory % ARRAY_SIZE;
#else
    hash = (unsigned long)entry->mMemory % ARRAY_SIZE;
#endif
    entry->mNextEntry = gMallocEntries[hash];
    gMallocEntries[hash] = entry;

    return entry->mMemory;
}

//////////////////////////////////////////////////////////////////////
// strdup for memory leak checking
//////////////////////////////////////////////////////////////////////
ALLOC char* debug_strdup(char* str, const char* file_name, int line, const char* func_name)
{
    char* result;

    result = (char*)debug_malloc(sizeof(char)*(strlen(str)+1), file_name, line, func_name);

    xstrncpy(result, str, strlen(str)+1);

    return result;
}
   
//////////////////////////////////////////////////////////////////////
// free for memory leak chekcing
//////////////////////////////////////////////////////////////////////
void debug_free(void* memory, const char* file_name, int line, const char* func_name)
{
    release_entry(memory, file_name, line, func_name);
    free(memory);
}

#endif

