#include "common.h"

#define NATIVE_METHOD_HASH_SIZE 256

struct sNativeMethodHashItem {
    char* mPath;
    fNativeMethod mFun;
};

static struct sNativeMethodHashItem gNativeMethodHash[NATIVE_METHOD_HASH_SIZE];

static unsigned int get_hash_key_for_native_method(char* path)
{
    unsigned int key;
    char* p;

    p = path;

    key = 0;

    while(*p) {
        key += *p++;
    }

    return key % NATIVE_METHOD_HASH_SIZE;
}

static void put_fun_to_hash_for_native_method(char* path, fNativeMethod fun)
{
    unsigned int key, key2;

    key = get_hash_key_for_native_method(path);

    key2 = key;

    while(1) {
        if(gNativeMethodHash[key2].mPath == NULL) {
            gNativeMethodHash[key2].mPath = MSTRDUP(path);
            gNativeMethodHash[key2].mFun = fun;
            break;
        }
        else {
            key2++;

            if(key2 >= NATIVE_METHOD_HASH_SIZE) {
                key2 = 0;
            }
            else if(key2 == key) {
                fprintf(stderr, "overflow native methods number");
                exit(1);
            }
        }
    }
}

fNativeMethod get_native_method(char* path)
{
    unsigned int key, key2;

    key = get_hash_key_for_native_method(path);

    key2 = key;

    while(1) {
        if(gNativeMethodHash[key2].mPath == NULL) {
            return NULL;
        }
        else if(strcmp(gNativeMethodHash[key2].mPath, path) == 0) {
            return gNativeMethodHash[key2].mFun;
        }
        else {
            key2++;

            if(key2 >= NATIVE_METHOD_HASH_SIZE) {
                key2 = 0;
            }
            else if(key2 == key) {
                return NULL;
            }
        }
    }
}

struct sNativeMethodStruct {
    const char* mPath;
    fNativeMethod mFun;
};

typedef struct sNativeMethodStruct sNativeMethod;

// manually sort is needed
static sNativeMethod gNativeMethods[] = {
    { "System.exit(int)", System_exit },
    { "System.assert(bool)", System_assert },
    { "System.malloc(int)", System_malloc },
    { "System.realloc(pointer,int)", System_realloc },
    { "System.calloc(int,int)", System_calloc },
    { "System.free(pointer)", System_free },
    { "System.memcpy(pointer,pointer,int)", System_memcpy },
    { "System.memcmp(pointer,pointer,int)", System_memcmp },
    { "System.strlen(pointer)", System_strlen },
    { "System.strlen(byte[])", System_strlen2 },
    { "System.strcpy(pointer,pointer)", System_strcpy },
    { "System.strncpy(pointer,pointer,int)", System_strncpy },
    { "System.strdup(pointer)", System_strdup },
    { "System.print(String)", System_print },
    { "System.println(String)", System_println },
    { "System.printToError(String)", System_printToError },
    { "System.printlnToError(String)", System_printlnToError },
    { "System.sleep(int)", System_sleep },
    { "System.pcre_exec(regex,String,int,int,PcreOVec)", System_pcre_exec },
    { "System.sprintf(String,Array)", System_sprintf },
    { "System.mbstowcs(pointer,pointer,int)", System_mbstowcs },
    { "System.wcstombs(pointer,char[])", System_wcstombs },
    { "System.atoi(String)", System_atoi },
    { "System.atof(String)", System_atof },
    { "System.strtod(String)", System_strtod },
    { "System.strcmp(String,String)", System_strcmp },
    { "System.strcasecmp(String,String)", System_strcasecmp },
    { "System.strtol(String,int)", System_strtol },
    { "System.strtoul(String,int)", System_strtoul },
    { "System.srand(uint)", System_srand },
    { "System.rand()", System_rand },
    { "System.time()", System_time },
    { "System.open(String,int,int)", System_open },
    { "System.close(int)", System_close },
    { "System.initialize()", System_initialize },
    { "System.read(int,Buffer,int)", System_read },
    { "System.localtime(ulong,pointer,pointer,pointer,pointer,pointer,pointer,pointer,pointer,pointer)", System_localtime },
    { "System.mktime(tm)", System_mktime },
    { "System.lstat(String,stat)", System_lstat },
    { "System.stat(String,stat)", System_stat },

    { "", 0 }  // sentinel
};


void native_method_init()
{
    sNativeMethod* p;

    memset(gNativeMethodHash, 0, sizeof(gNativeMethodHash));

    p = gNativeMethods;

    while(p->mPath[0] != 0) {
        put_fun_to_hash_for_native_method((char*)p->mPath, p->mFun);
        p++;
    }

    gGetNativeMethod = get_native_method;
}

void native_method_final()
{
    int i;
    for(i=0; i<NATIVE_METHOD_HASH_SIZE; i++) {
        if(gNativeMethodHash[i].mPath) {
            MFREE(gNativeMethodHash[i].mPath);
        }
    }
}

