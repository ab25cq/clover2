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
    { "System.malloc(ulong)", System_malloc },
    { "System.realloc(pointer,ulong)", System_realloc },
    { "System.calloc(int,ulong)", System_calloc },
    { "System.free(pointer)", System_free },
    { "System.memcpy(pointer,pointer,ulong)", System_memcpy },
    { "System.memcmp(pointer,pointer,ulong)", System_memcmp },
    { "System.strlen(pointer)", System_strlen },
    { "System.strlen(byte[])", System_strlen2 },
    { "System.strcpy(pointer,pointer)", System_strcpy },
    { "System.strncpy(pointer,pointer,ulong)", System_strncpy },
    { "System.strdup(pointer)", System_strdup },
    { "System.print(String)", System_print },
    { "System.println(String)", System_println },
    { "System.printToError(String)", System_printToError },
    { "System.printlnToError(String)", System_printlnToError },
    { "System.sleep(int)", System_sleep },
    { "System.pcre_exec(regex,String,int,int,PcreOVec)", System_pcre_exec },
    { "System.sprintf(String,Array)", System_sprintf },
    { "System.mbstowcs(pointer,pointer,ulong)", System_mbstowcs },
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
    { "System.read(int,Buffer,ulong)", System_read },
    { "System.write(int,Buffer,ulong)", System_write },
    { "System.localtime(ulong,pointer,pointer,pointer,pointer,pointer,pointer,pointer,pointer,pointer)", System_localtime },
    { "System.mktime(tm)", System_mktime },
    { "System.lstat(String,stat)", System_lstat },
    { "System.stat(String,stat)", System_stat },
    { "System.realpath(String)", System_realpath },
    { "System.dirname(String)", System_dirname },
    { "System.basename(String)", System_basename },
    { "System.opendir(String)", System_opendir },
    { "System.readdir(pointer)", System_readdir },
    { "System.closedir(pointer)", System_closedir },
    { "System.initialize_command_system()", System_initialize_command_system },
    { "System.pipe(pointer,pointer)", System_pipe },
    { "System.fork(lambda)", System_fork },
    { "System.dup2(int,int)", System_dup2 },
    { "System.execvp(String,List)", System_execvp },
    { "System.waitpid(int,pointer,int)", System_waitpid },
    { "System.WIFEXITED(int)", System_WIFEXITED },
    { "System.WEXITSTATUS(int)", System_WEXITSTATUS },
    { "System.WIFSIGNALED(int)", System_WIFSIGNALED },
    { "System.WTERMSIG(int)", System_WTERMSIG },
    { "System.WCOREDUMP(int)", System_WCOREDUMP },
    { "System.WIFSTOPPED(int)", System_WIFSTOPPED },
    { "System.WSTOPSIG(int)", System_WSTOPSIG },
    { "System.WIFCONTINUED(int)", System_WIFCONTINUED },
    { "System.getpid()", System_getpid },
    { "System.setpgid(int,int)", System_setpgid },
    { "System.kill(int,int)", System_kill },
    { "System.tcsetpgrp(int,int)", System_tcsetpgrp },
    { "System.tcgetattr(int,termios)", System_tcgetattr },
    { "System.tcsetattr(int,int,termios)", System_tcsetattr },
    { "System.tcflow(int,int)", System_tcflow },
    { "System.tcflush(int,int)", System_tcflush },
    { "System.tcsendbreak(int,int)", System_tcsendbreak },
    { "System.tcdrain(int)", System_tcdrain },
    { "System.cfmakeraw(termios)", System_cfmakeraw },
    { "System.cfgetispeed(termios)", System_cfgetispeed },
    { "System.cfgetospeed(termios)", System_cfgetospeed },
    { "System.cfsetispeed(termios,int)", System_cfsetispeed },
    { "System.cfsetospeed(termios,int)", System_cfsetospeed },
    { "System.cfsetspeed(termios,int)", System_cfsetspeed },
    { "System.chmod(String,int)", System_chmod },
    { "System.lchmod(String,int)", System_lchmod },
    { "System.fchmod(int,int)", System_fchmod },
    { "System.chown(String,int,int)", System_chown },
    { "System.lchown(String,int,int)", System_lchown },
    { "System.fchown(int,int,int)", System_fchown },
    { "System.unlink(String)", System_unlink },
    { "System.access(String,int)", System_access },
    { "System.utime(String,ulong,ulong)", System_utime },
    { "System.fnmatch(String,String,int)", System_fnmatch },
    { "System.link(String,String)", System_link },
    { "System.symlink(String,String)", System_symlink },
    { "System.readlink(String)", System_readlink },
    { "System.rename(String,String)", System_rename },
    { "System.truncate(String,ulong)", System_truncate },
    { "System.ftruncate(int,ulong)", System_ftruncate },
    { "System.chdir(String)", System_chdir },
    { "System.fchdir(int)", System_fchdir },
    { "System.rmdir(String)", System_rmdir },
    { "System.mkdir(String,int)", System_mkdir },

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

