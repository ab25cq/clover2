#include "common.h"

#define NATIVE_METHOD_HASH_SIZE 1024

struct sNativeMethodHashItem {
    char* mPath;
    char* mFunName;
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

    unsigned int result =  key % NATIVE_METHOD_HASH_SIZE;

    return result;
}

void put_fun_to_hash_for_native_method(char* path, char* fun_name, fNativeMethod fun)
{
    unsigned int key, key2;

    key = get_hash_key_for_native_method(path);

    key2 = key;

    while(1) {
        if(gNativeMethodHash[key2].mPath == NULL) {
            gNativeMethodHash[key2].mPath = MSTRDUP(path);
            gNativeMethodHash[key2].mFunName = fun_name;
            gNativeMethodHash[key2].mFun = fun;
            break;
        }
        else {
            key2++;

            if(key2 >= NATIVE_METHOD_HASH_SIZE) {
                key2 = 0;
            }
            else if(key2 == key) {
                fprintf(stderr, "overflow native methods number\n");
                exit(1);
            }
        }
    }
}

fNativeMethod get_native_method(char* path, char** fun_name)
{
    unsigned int key, key2;

    key = get_hash_key_for_native_method(path);

    key2 = key;

    while(1) {
        if(gNativeMethodHash[key2].mPath == NULL) {
            (*fun_name) = NULL;
            return NULL;
        }
        else {
            if(strcmp(gNativeMethodHash[key2].mPath, path) == 0) {
                (*fun_name) = gNativeMethodHash[key2].mFunName;
                fNativeMethod result = gNativeMethodHash[key2].mFun;
                return result;
            }
            else {
                key2++;

                if(key2 >= NATIVE_METHOD_HASH_SIZE) {
                    key2 = 0;
                }
                else if(key2 == key) {
                    (*fun_name) = NULL;
                    return NULL;
                }
            }
        }
    }
}

struct sNativeMethodStruct {
    const char* mPath;
    char* mFunName;
    fNativeMethod mFun;
};

typedef struct sNativeMethodStruct sNativeMethod;

// manually sort is needed
static sNativeMethod gNativeMethods[] = {
    { "Clover.load(String,bool)", "Clover_load", Clover_load },
    { "System.exit(int)", "System_exit", System_exit },
    { "System.assert(bool)", "System_assert", System_assert },
    { "System.malloc(ulong)", "System_malloc", System_malloc },
    { "System.GC_malloc(ulong)", "System_GC_malloc", System_GC_malloc },
    { "System.realloc(pointer,ulong)", "System_realloc", System_realloc },
    { "System.calloc(int,ulong)", "System_calloc", System_calloc },
    { "System.free(pointer)", "System_free", System_free },
    { "System.memcpy(pointer,pointer,ulong)", "System_memcpy", System_memcpy },
    { "System.memcmp(pointer,pointer,ulong)", "System_memcmp", System_memcmp },
    { "System.strlen(pointer)", "System_strlen", System_strlen },
    { "System.strlen(byte[])", "System_strlen2", System_strlen2 },
    { "System.strcpy(pointer,pointer)", "System_strcpy", System_strcpy },
    { "System.strncpy(pointer,pointer,ulong)", "System_strncpy", System_strncpy },
    { "System.strdup(pointer)", "System_strdup", System_strdup },
    { "System.print(String)", "System_print", System_print },
    { "System.println(String)", "System_println", System_println },
    { "System.printToError(String)", "System_printToError", System_printToError },
    { "System.printlnToError(String)", "System_printlnToError", System_printlnToError },
    { "System.sleep(int)", "System_sleep", System_sleep },
    { "System.pcre_exec(regex,Buffer,int,int,PcreOVec)", "System_pcre_exec", System_pcre_exec },
    { "System.sprintf(String,Array)", "System_sprintf", System_sprintf },
    { "System.mbstowcs(pointer,ulong)", "System_mbstowcs", System_mbstowcs },
    { "System.wcstombs(char[])", "System_wcstombs", System_wcstombs },
    { "System.atoi(String)", "System_atoi", System_atoi },
    { "System.atof(String)", "System_atof", System_atof },
    { "System.strtod(String)", "System_strtod", System_strtod },
    { "System.strcmp(String,String)", "System_strcmp", System_strcmp },
    { "System.strcasecmp(String,String)", "System_strcasecmp", System_strcasecmp },
    { "System.strtol(String,int)", "System_strtol", System_strtol },
    { "System.strtoul(String,int)", "System_strtoul", System_strtoul },
    { "System.srand(uint)", "System_srand", System_srand },
    { "System.rand()", "System_rand", System_rand },
    { "System.time()", "System_time", System_time },
    { "System.open(String,int,int)", "System_open", System_open },
    { "System.close(int)", "System_close", System_close },
    { "System.read(int,Buffer,ulong)", "System_read", System_read },
    { "System.write(int,Buffer,ulong)", "System_write", System_write },
    { "System.fcntl(int,int,int)", "System_fcntl", System_fcntl },
    { "System.localtime(ulong,pointer,pointer,pointer,pointer,pointer,pointer,pointer,pointer,pointer)", "System_localtime", System_localtime },
    { "System.mktime(tm)", "System_mktime", System_mktime },
    { "System.lstat(String,stat)", "System_lstat", System_lstat },
    { "System.stat(String,stat)", "System_stat", System_stat },
    { "System.realpath(String)", "System_realpath", System_realpath },
    { "System.dirname(String)", "System_dirname", System_dirname },
    { "System.basename(String)", "System_basename", System_basename },
    { "System.opendir(String)", "System_opendir", System_opendir },
    { "System.readdir(pointer)", "System_readdir", System_readdir },
    { "System.closedir(pointer)", "System_closedir", System_closedir },
    { "System.initialize_string_system()", "System_initialize_string_system", System_initialize_string_system },
    { "System.initialize_file_system()", "System_initialize_file_system", System_initialize_file_system },
    { "System.initialize_command_system()", "System_initialize_command_system", System_initialize_command_system },
    { "System.pipe(pointer,pointer)", "System_pipe", System_pipe },
    { "System.fork(lambda)", "System_fork", System_fork },
    { "System.dup2(int,int)", "System_dup2", System_dup2 },
    { "System.execvp(String,List)", "System_execvp", System_execvp },
    { "System.execv(String,List)", "System_execv", System_execv },
    { "System.waitpid(int,pointer,int)", "System_waitpid", System_waitpid },
    { "System.WIFEXITED(int)", "System_WIFEXITED", System_WIFEXITED },
    { "System.WEXITSTATUS(int)", "System_WEXITSTATUS", System_WEXITSTATUS },
    { "System.WIFSIGNALED(int)", "System_WIFSIGNALED", System_WIFSIGNALED },
    { "System.WTERMSIG(int)", "System_WTERMSIG", System_WTERMSIG },
    { "System.WCOREDUMP(int)", "System_WCOREDUMP", System_WCOREDUMP },
    { "System.WIFSTOPPED(int)", "System_WIFSTOPPED", System_WIFSTOPPED },
    { "System.WSTOPSIG(int)", "System_WSTOPSIG", System_WSTOPSIG },
    { "System.WIFCONTINUED(int)", "System_WIFCONTINUED", System_WIFCONTINUED },
    { "System.getpid()", "System_getpid", System_getpid },
    { "System.getppid()", "System_getppid", System_getppid },
    { "System.setpgid(int,int)", "System_setpgid", System_setpgid },
    { "System.kill(int,int)", "System_kill", System_kill },
    { "System.tcsetpgrp(int,int)", "System_tcsetpgrp", System_tcsetpgrp },
    { "System.tcgetattr(int)", "System_tcgetattr", System_tcgetattr },
    { "System.tcsetattr(int,int,termios)", "System_tcsetattr", System_tcsetattr },
    { "System.tcflow(int,int)", "System_tcflow", System_tcflow },
    { "System.tcflush(int,int)", "System_tcflush", System_tcflush },
    { "System.tcsendbreak(int,int)", "System_tcsendbreak", System_tcsendbreak },
    { "System.tcdrain(int)", "System_tcdrain", System_tcdrain },
    { "System.cfmakeraw(termios)", "System_cfmakeraw", System_cfmakeraw },
    { "System.cfgetispeed(termios)", "System_cfgetispeed", System_cfgetispeed },
    { "System.cfgetospeed(termios)", "System_cfgetospeed", System_cfgetospeed },
    { "System.cfsetispeed(termios,int)", "System_cfsetispeed", System_cfsetispeed },
    { "System.cfsetospeed(termios,int)", "System_cfsetospeed", System_cfsetospeed },
    { "System.cfsetspeed(termios,int)", "System_cfsetspeed", System_cfsetspeed },
    { "System.chmod(String,int)", "System_chmod", System_chmod },
    { "System.lchmod(String,int)", "System_lchmod", System_lchmod },
    { "System.fchmod(int,int)", "System_fchmod", System_fchmod },
    { "System.chown(String,int,int)", "System_chown", System_chown },
    { "System.lchown(String,int,int)", "System_lchown", System_lchown },
    { "System.fchown(int,int,int)", "System_fchown", System_fchown },
    { "System.unlink(String)", "System_unlink", System_unlink },
    { "System.access(String,int)", "System_access", System_access },
    { "System.utime(String,ulong,ulong)", "System_utime", System_utime },
    { "System.fnmatch(String,String,int)", "System_fnmatch", System_fnmatch },
    { "System.link(String,String)", "System_link", System_link },
    { "System.symlink(String,String)", "System_symlink", System_symlink },
    { "System.readlink(String)", "System_readlink", System_readlink },
    { "System.rename(String,String)", "System_rename", System_rename },
    { "System.truncate(String,ulong)", "System_truncate", System_truncate },
    { "System.ftruncate(int,ulong)", "System_ftruncate", System_ftruncate },
    { "System.chdir(String)", "System_chdir", System_chdir },
    { "System.fchdir(int)", "System_fchdir", System_fchdir },
    { "System.rmdir(String)", "System_rmdir", System_rmdir },
    { "System.mkdir(String,int)", "System_mkdir", System_mkdir },
    { "System.clock_getres(int,timespec)", "System_clock_getres", System_clock_getres },
    { "System.clock_gettime(int,timespec)", "System_clock_gettime", System_clock_gettime },
    { "System.clock_settime(int,timespec)", "System_clock_settime", System_clock_settime },
    { "System.dlopen(String,int)", "System_dlopen", System_dlopen },
    { "System.dlclose(pointer)", "System_dlclose", System_dlclose },
    { "System.dlsym(pointer,String)", "System_dlsym", System_dlsym },
    { "System.system(String)", "System_system", System_system },
    { "System.getenv(String)", "System_getenv", System_getenv },
//    { "System.secure_getenv(String)", "System_secure_getenv", System_secure_getenv },
    { "System.setenv(String,String,int)", "System_setenv", System_setenv },
    { "System.unsetenv(String)", "System_unsetenv", System_unsetenv },
    { "System.put_fun_to_hash_for_native_method(String,String,pointer)", "System_put_fun_to_hash_for_native_method", System_put_fun_to_hash_for_native_method },

    { "System.initialize_system_calls_system()", "System_initialize_system_calls_system", System_initialize_system_calls_system },
    { "System.alarm(uint)", "System_alarm", System_alarm },
    { "System.dup(int)", "System_dup", System_dup },
    { "System.execvpe(String,List,List)", "System_execvpe", System_execvpe },
    { "System.fopen(String,String)", "System_fopen", System_fopen },
    { "System.fclose(pointer)", "System_fclose", System_fclose },
    { "System.fwrite(Buffer,ulong,pointer)", "System_fwrite", System_fwrite },
    { "System.fread(Buffer,ulong,pointer)", "System_fread", System_fread },
    { "System.feof(pointer)", "System_feof", System_feof },
    { "System.fgetc(pointer)", "System_fgetc", System_fgetc },
    { "System.fgets(Buffer,int,pointer)", "System_fgets", System_fgets },
    { "System.getchar()", "System_getchar", System_getchar },
    { "System.ungetc(int,pointer)", "System_ungetc", System_ungetc },
    { "System.getcwd()", "System_getcwd", System_getcwd },
    { "Clover.initialize_lang()", "Clover_initialize_lang", Clover_initialize_lang },
    { "System.getopt(String,bool)", "System_getopt", System_getopt },
    { "System.getopt_long(String,getopt_long_option[],bool)", "System_getopt_long", System_getopt_long },
    { "System.getopt_long_only(String,getopt_long_option[],bool)", "System_getopt_long_only", System_getopt_long_only },
    { "System.setsid()", "System_setsid", System_setsid },
    { "System.getsid(int)", "System_getsid", System_getsid },
    { "System.setpgrp()", "System_setpgrp", System_setpgrp },
    { "System.gettid()", "System_gettid", System_gettid },
    { "System.popen(String,String)", "System_popen", System_popen },
    { "System.pclose(pointer)", "System_pclose", System_pclose },
    { "Clover.appendField(String,String,String,bool)", "Clover_appendField", Clover_appendField },
    { "Clover.appendClassField(String,String,String,bool)", "Clover_appendClassField", Clover_appendClassField },
    { "Clover.appendMethod(String,String,bool)", "Clover_appendMethod", Clover_appendMethod },
    { "Clover.appendMethod(String,int,String,bool)", "Clover_appendMethod2", Clover_appendMethod2 },
    { "Clover.initialize_reflection()", "Clover_initialize_reflection", Clover_initialize_reflection },
    { "Clover.getField(String,int,bool)", "Clover_getField", Clover_getField },
    { "Clover.getClassField(String,int,bool)", "Clover_getClassField", Clover_getClassField },
    { "Clover.getMethod(String,int,bool)", "Clover_getMethod", Clover_getMethod },
    { "Clover.getClassFlags(String,bool)", "Clover_getClassFlags", Clover_getClassFlags },
    { "Clover.getClassGenericsParamTypes(String,bool)", "Clover_getClassGenericsParamTypes", Clover_getClassGenericsParamTypes },
    { "Clover.getClassGenericsParamNames(String,bool)", "Clover_getClassGenericsParamNames", Clover_getClassGenericsParamNames },
    { "Clover.getNumFields(String,bool)", "Clover_getNumFields", Clover_getNumFields },
    { "Clover.getNumClassFields(String,bool)", "Clover_getNumClassFields", Clover_getNumClassFields },
    { "Clover.getNumMethods(String,bool)", "Clover_getNumMethods", Clover_getNumMethods },
    { "Clover.isLoadedClass(String,bool)", "Clover_isLoadedClass", Clover_isLoadedClass },
    { "Clover.isDefinedClass(String,bool)", "Clover_isDefinedClass", Clover_isDefinedClass },
    { "Clover.createObject(String,bool)", "Clover_createObject", Clover_createObject },
    { "Clover.createArray(String,int)", "Clover_createArray", Clover_createArray },
    { "Clover.appendClass(String)", "Clover_appendClass", Clover_appendClass },
    { "Clover.isTypedefedClass(String,String,bool)", "Clover_isTypedefedClass", Clover_isTypedefedClass },
    { "Thread.initialize_thread(Thread,lambda)", "Thread_initialize_thread", Thread_initialize_thread },
    { "Thread.pthread_join(ulong)", "Thread_pthread_join", Thread_pthread_join },
    { "pthread_mutex_t.allocSize()", "pthread_mutex_t_allocSize", pthread_mutex_t_allocSize },
    { "System.initialize_thread_system()", "System_initialize_thread_system", System_initialize_thread_system },
    { "System.pthread_mutex_init(pthread_mutex_t,uint)", "System_pthread_mutex_init", System_pthread_mutex_init },
    { "System.pthread_mutex_lock(pthread_mutex_t)", "System_pthread_mutex_lock", System_pthread_mutex_lock },
    { "System.pthread_mutex_unlock(pthread_mutex_t)", "System_pthread_mutex_unlock", System_pthread_mutex_unlock },
    { "System.pthread_mutex_destroy(pthread_mutex_t)", "System_pthread_mutex_destroy", System_pthread_mutex_destroy },
    { "System.pthread_mutex_trylock(pthread_mutex_t)", "System_pthread_mutex_trylock", System_pthread_mutex_trylock },

    { "System.pthread_mutexattr_init(uint)", "System_pthread_mutexattr_init", System_pthread_mutexattr_init },
    { "System.pthread_mutexattr_settype(uint,int)", "System_pthread_mutexattr_settype", System_pthread_mutexattr_settype },
    { "System.pthread_mutexattr_destroy(uint)", "System_pthread_mutexattr_destroy", System_pthread_mutexattr_destroy },
    { "System.pthread_mutexattr_gettype(uint,pointer)", "System_pthread_mutexattr_gettype", System_pthread_mutexattr_gettype },

    { "System.pthread_cond_init(pthread_cond_t,uint)", "System_pthread_cond_init", System_pthread_cond_init },
    { "System.pthread_cond_signal(pthread_cond_t)", "System_pthread_cond_signal", System_pthread_cond_signal },
    { "System.pthread_cond_broadcast(pthread_cond_t)", "System_pthread_cond_broadcast", System_pthread_cond_broadcast },
    { "System.pthread_cond_wait(pthread_cond_t,pthread_mutex_t)", "System_pthread_cond_wait", System_pthread_cond_wait },
    { "System.pthread_cond_timedwait(pthread_cond_t,pthread_mutex_t,timespec)", "System_pthread_cond_timedwait", System_pthread_cond_timedwait },
    { "System.pthread_cond_destroy(pthread_cond_t)", "System_pthread_cond_destroy", System_pthread_cond_destroy },
    { "pthread_cond_t.allocSize()", "pthread_cond_t_allocSize", pthread_cond_t_allocSize },
    { "System.initialize_cgi_system()", "System_initialize_cgi_system", System_initialize_cgi_system },
    { "System.setlocale(int,String)", "System_setlocale", System_setlocale },
    { "System.flock(int,int)", "System_flock", System_flock },
    { "System.fileno(pointer)", "System_fileno", System_fileno },
#ifdef HAVE_BSD_H
    { "System.getbsize(pointer,pointer)", "System_getbsize", System_getbsize },
#endif
    { "System.getegid()", "System_getegid", System_getegid },
    { "System.getgid()", "System_getgid", System_getgid },
    { "System.geteuid()", "System_geteuid", System_geteuid },
    { "System.getuid()", "System_getuid", System_getuid },
    { "System.isatty(int)", "System_isatty", System_isatty },
    { "System.umask(int)", "System_umask", System_umask },
    { "System.usleep(int)", "System_usleep", System_usleep },
    { "System.nanosleep(timespec,timespec?)", "System_nanosleep", System_nanosleep },
    { "System.putenv(String)", "System_putenv", System_putenv },
    { "System.setvbuf(pointer,pointer,int,ulong)", "System_setvbuf", System_setvbuf },
    { "System.strncat(pointer,pointer,ulong)", "System_strncat", System_strncat },
    { "System.strchr(pointer,byte)", "System_strchr", System_strchr },
    { "System.initialize_socket_system()", "System_initialize_socket_system", System_initialize_socket_system },
    { "System.socket(int,int,int)", "System_socket", System_socket },
    { "System.connect(int,sockaddr_un)", "System_connect", System_connect },
    { "System.connect(int,sockaddr_in)", "System_connect2", System_connect2 },
    { "System.bind(int,sockaddr_un)", "System_bind", System_bind },
    { "System.bind(int,sockaddr_in)", "System_bind2", System_bind2 },
    { "System.listen(int,int)", "System_listen", System_listen },
    { "System.accept(int,sockaddr_un)", "System_accept", System_accept },
    { "System.accept(int,sockaddr_in)", "System_accept2", System_accept2 },
    { "System.inet_addr(String)", "System_inet_addr", System_inet_addr },
    { "System.gethostbyaddr(pointer,ulong,int)", "System_gethostbyaddr", System_gethostbyaddr },
    { "System.gethostbyname(String)", "System_gethostbyname", System_gethostbyname },
    { "System.getservbyname(String,String)", "System_getservbyname", System_getservbyname },
    { "System.getservbyport(int,String)", "System_getservbyport", System_getservbyport },
    { "System.inet_ntoa(in_addr)", "System_inet_ntoa", System_inet_ntoa },
    { "System.gethostname()", "System_gethostname", System_gethostname },
    { "System.signal(int,pointer)", "System_signal", System_signal },
    { "System.signal(int,lambda)", "System_signal2", System_signal2 },
    { "fd_set.allocSize()", "fd_set_allocSize", fd_set_allocSize },
    { "System.FD_ZERO(fd_set)", "System_FD_ZERO", System_FD_ZERO },
    { "System.FD_CLR(int,fd_set)", "System_FD_CLR", System_FD_CLR },
    { "System.FD_SET(int,fd_set)", "System_FD_SET", System_FD_SET },
    { "System.FD_SET(int,fd_set)", "System_FD_SET", System_FD_SET },
    { "System.init_pair(short,short,short)", "System_init_pair", System_init_pair },
    { "System.start_color()", "System_start_color", System_start_color },
    { "System.COLOR_PAIR(int)", "System_COLOR_PAIR", System_COLOR_PAIR },
    { "System.FD_ISSET(int,fd_set)", "System_FD_ISSET", System_FD_ISSET },
    { "System.select(int,fd_set?,fd_set?,fd_set?,timeval?)", "System_select", System_select },
    { "System.ioctl(int,int,pointer)", "System_ioctl", System_ioctl },
    { "Clover.getAllClassName()", "Clover_getAllClassName", Clover_getAllClassName },
    { "Clover.declareMethod(String,String)", "Clover_declareMethod", Clover_declareMethod },
    { "System.initscr()", "System_initscr", System_initscr },
    { "System.addch(char)", "System_addch", System_addch },
    { "System.addstr(String)", "System_addstr", System_addstr },
    { "System.endwin()", "System_endwin", System_endwin },
    { "System.move(int,int)", "System_move", System_move },
    { "System.printw(String)", "System_printw", System_printw },
    { "System.refresh()", "System_refresh", System_refresh },
    { "System.is_cleared(pointer)", "System_is_cleared", System_is_cleared },
    { "System.is_idcok(pointer)", "System_is_idcok", System_is_idcok },
    { "System.is_idlok(pointer)", "System_is_idlok", System_is_idlok },
    { "System.is_immedok(pointer)", "System_is_immedok", System_is_immedok },
    { "System.is_keypad(pointer)", "System_is_keypad", System_is_keypad },
    { "System.is_leaveok(pointer)", "System_is_leaveok", System_is_leaveok },
    { "System.is_nodelay(pointer)", "System_is_nodelay", System_is_nodelay },
    { "System.is_notimeout(pointer)", "System_is_notimeout", System_is_notimeout },
//    { "System.is_pad(pointer)", "System_is_pad", System_is_pad },
    { "System.clrtobot()", "System_clrtobot", System_clrtobot },
    { "System.wclrtobot(pointer)", "System_wclrtobot", System_wclrtobot },
    { "System.clrtoeol()", "System_clrtoeol", System_clrtoeol },
    { "System.wclrtoeol(pointer)", "System_wclrtoeol", System_wclrtoeol },
    { "System.werase(pointer)", "System_werase", System_werase },
    
    { "System.resetty()", "System_resetty", System_resetty },
    { "System.savetty()", "System_savetty", System_savetty },
    { "System.reset_prog_mode()", "System_reset_prog_mode", System_reset_prog_mode },
    { "System.reset_shell_mode()", "System_reset_shell_mode", System_reset_shell_mode },
    { "System.getsyx(int,int)", "System_getsyx", System_getsyx },
    { "System.setsyx(int,int)", "System_setsyx", System_setsyx },
    { "System.curs_set(bool)", "System_curs_set", System_curs_set },
    { "System.napms(int)", "System_curs_set", System_curs_set },
    { "System.flash()", "System_flash", System_flash },
    { "System.is_scrollok(pointer)", "System_is_scrollok", System_is_scrollok },
//    { "System.is_subwin(pointer)", "System_is_subwin", System_is_subwin },
    { "System.is_syncok(pointer)", "System_is_syncok", System_is_syncok },
    { "System.wgetparent(pointer)", "System_wgetparent", System_wgetparent },
//    { "System.wgetdelay(pointer)", "System_wgetdelay", System_wgetdelay },
    { "System.wgetscrreg(pointer,pointer,pointer)", "System_wgetdelay", System_wgetscrreg },
    { "System.init_pair(short,short,short)", "System_init_pair", System_init_pair },
    { "System.COLOR_PAIR(int)", "System_COLOR_PAIR", System_COLOR_PAIR },
    { "System.box(pointer,char,char)", "System_box", System_box },
    { "System.isendwin()", "System_isendwin", System_isendwin },
    { "System.clear()", "System_clear", System_clear },
    { "System.erase()", "System_erase", System_erase },
    { "System.idcok(pointer,bool)", "System_idcok", System_idcok },
    { "System.idlok(pointer,bool)", "System_idlok", System_idlok },
    { "System.clearok(pointer,bool)", "System_clearok", System_clearok },
    { "System.leaveok(pointer,bool)", "System_leaveok", System_leaveok },
    { "System.attrset(int)", "System_attrset", System_attrset },
    { "System.attron(int)", "System_attron", System_attron },
    { "System.attroff(int)", "System_attroff", System_attroff },
    { "System.beep()", "System_beep", System_beep },
    { "System.border()", "System_border", System_border },
    { "System.wborder()", "System_wborder", System_wborder },
    { "System.def_prog_mode()", "System_def_prog_mode", System_def_prog_mode },
    { "System.def_shell_mode()", "System_def_shell_mode", System_def_shell_mode },
    { "System.echo()", "System_echo", System_echo },
    { "System.noecho()", "System_noecho", System_noecho },
    { "System.cbreak()", "System_cbreak", System_cbreak },
    { "System.nocbreak()", "System_nocbreak", System_nocbreak },
    { "System.border(char,char,char,char,char,char,char,char)", "System_border", System_border },
    { "System.wborder(pointer,char,char,char,char,char,char,char,char)", "System_wborder", System_wborder },
    { "System.raw()", "System_raw", System_raw },
    { "System.noraw()", "System_noraw", System_noraw },
    { "System.nodelay(pointer,bool)", "System_nodelay", System_nodelay },
    { "System.box(pointer,char,char)", "System_box", System_box },
    { "System.getch()", "System_getch", System_getch },
    { "System.newwin(int,int,int,int)", "System_newwin", System_newwin },
    { "System.delwin(pointer)", "System_delwin", System_delwin },
    { "System.mvwin(pointer,int,int)", "System_mvwin", System_mvwin },
    { "System.wrefresh(pointer)", "System_wrefresh", System_wrefresh },
    { "System.wclear(pointer)", "System_wclear", System_wclear },
    { "System.touchwin(pointer)", "System_touchwin", System_touchwin },
    { "System.setEscapeDelay(int)", "System_setEscapeDelay", System_setEscapeDelay },
    { "System.getEscapeDelay()", "System_getEscapeDelay", System_getEscapeDelay },
    { "System.keypad(pointer,bool)", "System_keypad", System_keypad },
    { "System.wmove(pointer,int,int)", "System_wmove", System_wmove },
    { "System.wprintw(pointer,String)", "System_wprintw", System_wprintw },
    { "System.getmaxx()", "System_getmaxx", System_getmaxx },
    { "System.getmaxy()", "System_getmaxy", System_getmaxy },
    { "System.isalpha(char)", "System_isalpha", System_isalpha },
    { "System.isalnum(char)", "System_isalnum", System_isalnum },
    { "System.iscntrl(char)", "System_iscntrl", System_iscntrl },
    { "System.isdigit(char)", "System_isdigit", System_isdigit },
    { "System.isgraph(char)", "System_isgraph", System_isgraph },
    { "System.islower(char)", "System_islower", System_islower },
    { "System.isprint(char)", "System_isprint", System_isprint },
    { "System.ispunct(char)", "System_ispunct", System_ispunct },
    { "System.isspace(char)", "System_isspace", System_isspace },
    { "System.isupper(char)", "System_isupper", System_isupper },
    { "System.isxdigit(char)", "System_isxdigit", System_isxdigit },
    { "System.isascii(char)", "System_isascii", System_isascii },
    { "System.isblank(char)", "System_isblank", System_isblank },
    { "Clover.gc()", "Clover_gc", Clover_gc },
    { "Clover.compaction()", "Clover_compaction", Clover_compaction },
    { "System.send(int,Buffer,ulong,int)", "System_send", System_send },
    { "System.sendto(int,Buffer,ulong,int,sockaddr_un)", "System_sendto", System_sendto },
    { "System.sendto(int,Buffer,ulong,int,sockaddr_in)", "System_sendto2", System_sendto2 },
    { "System.recv(int,Buffer,ulong,int)", "System_recv", System_recv },
    { "System.recvfrom(int,Buffer,ulong,int,sockaddr_un)", "System_recvfrom", System_recvfrom },
    { "System.recvfrom(int,Buffer,ulong,int,sockaddr_in)", "System_recvfrom2", System_recvfrom2 },
    { "System.memset(pointer,int,ulong)", "System_memset", System_memset },
    
    { "System.can_change_color()", "System_can_change_color", System_can_change_color },
    { "System.has_colors()", "System_has_colors", System_has_colors },
    { "System.init_color(short,short,short,short)", "System_init_color", System_init_color },
    { "System.color_content(short,pointer,pointer,pointer)", "System_color_content", System_color_content },
    { "System.pair_content(short,pointer,pointer)", "System_pair_content", System_pair_content },
//    { "System.reset_color_pairs()", "System_reset_color_pairs", System_reset_color_pairs },
    { "System.COLOR_PAIR(int)", "System_COLOR_PAIR", System_COLOR_PAIR },
    { "System.PAIR_NUMBER(int)", "System_PAIR_NUMBER", System_PAIR_NUMBER },
    
    { "System.attr_get(pointer,pointer,pointer)", "System_attr_get", System_attr_get },
    { "System.wattr_get(pointer,pointer,pointer,pointer)", "System_wattr_get", System_wattr_get },
    { "System.attr_set(uint,short,pointer)", "System_attr_set", System_attr_set },
    { "System.wattr_set(pointer,uint,short,pointer)", "System_wattr_set", System_wattr_set },
    { "System.attr_off(uint,pointer)", "System_attr_off", System_attr_off },
    { "System.wattr_off(pointer,uint,pointer)", "System_wattr_off", System_wattr_off },
    { "System.attr_on(uint,pointer)", "System_attr_on", System_attr_on },
    { "System.wattr_on(pointer,uint,pointer)", "System_wattr_on", System_wattr_on },
    { "System.wattroff(pointer,int)", "System_wattroff", System_wattroff },
    { "System.wattron(pointer,int)", "System_wattron", System_wattron },
    { "System.wattrset(pointer,int)", "System_wattrset", System_wattrset },
    { "System.chgat(int,uint,short,pointer)", "System_chgat", System_chgat },
    { "System.wchgat(pointer,int,uint,short,pointer)", "System_wchgat", System_wchgat },
    { "System.mvchgat(int,uint,int,uint,short,pointer)", "System_mvchgat", System_mvchgat },
    { "System.mvwchgat(pointer,int,int,int,uint,short,pointer)", "System_mvwchgat", System_mvwchgat },
    { "System.color_set(short,pointer)", "System_color_set", System_color_set },
    { "System.wcolor_set(pointer,short,pointer)", "System_wcolor_set", System_wcolor_set },

    { "System.bkgdset(uint)", "System_bkgdset", System_bkgdset },
    { "System.wbkgdset(pointer,uint)", "System_wbkgdset", System_wbkgdset },
    { "System.bkgd(uint)", "System_bkgd", System_bkgd },
    { "System.wbkgd(pointer,uint)", "System_wbkgd", System_wbkgd },
    { "System.getbkgd(pointer)", "System_wbkgd", System_wbkgd },
    { "System.wgetch(pointer)", "System_wgetch", System_wgetch },
    { "System.mvgetch(int,int)", "System_mvgetch", System_mvgetch },
    { "System.mvwgetch(pointer,int,int)", "System_mvwgetch", System_mvwgetch },
    { "System.ungetch(int)", "System_ungetch", System_ungetch },
    { "System.has_key(int)", "System_has_key", System_has_key },
    
    { "System.nofilter()", "System_nofilter", System_nofilter },
    { "System.filter()", "System_filter", System_filter },
    { "System.unctrl(uint)", "System_unctrl", System_unctrl },
    { "System.keyname(int)", "System_keyname", System_keyname },
    { "System.delay_output(int)", "System_delay_output", System_delay_output },
    
    { "System.delch()", "System_delch", System_delch },
    { "System.wdelch(pointer)", "System_wdelch", System_wdelch },
    { "System.mvdelch(int,int)", "System_mvdelch", System_mvdelch },
    { "System.mvwdelch(pointer,int,int)", "System_mvwdelch", System_mvwdelch },
    { "System.meta(pointer,bool)", "System_meta", System_meta },

    { "", "", 0 }  // sentinel
};

void native_method_init()
{
    sNativeMethod* p;

    memset(gNativeMethodHash, 0, sizeof(struct sNativeMethodHashItem)*NATIVE_METHOD_HASH_SIZE);

    p = gNativeMethods;

    while(p->mPath[0] != 0) {
        put_fun_to_hash_for_native_method((char*)p->mPath, p->mFunName, p->mFun);
        p++;
    }
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
