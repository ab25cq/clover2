typedef long unsigned int size_t;
extern void * memcpy(void * __restrict __dest,
                     const void * __restrict __src,
                     size_t __n) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern void * memmove(void * __dest,
                      const void * __src,
                      size_t __n) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern void * memccpy(void * __restrict __dest,
                      const void * __restrict __src,
                      int __c,
                      size_t __n) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern void * memset(void * __s,
                     int __c,
                     size_t __n) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int memcmp(const void * __s1,
                  const void * __s2,
                  size_t __n) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1, 2)));
extern void * memchr(const void * __s,
                     int __c,
                     size_t __n) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1)));
extern void * rawmemchr(const void * __s,
                        int __c) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1)));
extern void * memrchr(const void * __s,
                      int __c,
                      size_t __n) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1)));
extern char * strcpy(char * __restrict __dest,
                     const char * __restrict __src) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern char * strncpy(char * __restrict __dest,
                      const char * __restrict __src,
                      size_t __n) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern char * strcat(char * __restrict __dest,
                     const char * __restrict __src) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern char * strncat(char * __restrict __dest,
                      const char * __restrict __src,
                      size_t __n) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern int strcmp(const char * __s1,
                  const char * __s2) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1, 2)));
extern int strncmp(const char * __s1,
                   const char * __s2,
                   size_t __n) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1, 2)));
extern int strcoll(const char * __s1,
                   const char * __s2) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1, 2)));
extern size_t strxfrm(char * __restrict __dest,
                      const char * __restrict __src,
                      size_t __n) __attribute__((__nothrow__,__leaf__,__nonnull__(2)));
typedef struct __locale_struct {
            struct __locale_data * __locales[13];
            const unsigned short int * __ctype_b;
            const int * __ctype_tolower;
            const int * __ctype_toupper;
            const char * __names[13];
        } * __locale_t;
typedef __locale_t locale_t;
extern int strcoll_l(const char * __s1,
                     const char * __s2,
                     __locale_t __l) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1, 2, 3)));
extern size_t strxfrm_l(char * __dest,
                        const char * __src,
                        size_t __n,
                        __locale_t __l) __attribute__((__nothrow__,__leaf__,__nonnull__(2, 4)));
extern char * strdup(const char * __s) __attribute__((__nothrow__,__leaf__,__malloc__,__nonnull__(1)));
extern char * strndup(const char * __string,
                      size_t __n) __attribute__((__nothrow__,__leaf__,__malloc__,__nonnull__(1)));
extern char * strchr(const char * __s,
                     int __c) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1)));
extern char * strrchr(const char * __s,
                      int __c) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1)));
extern char * strchrnul(const char * __s,
                        int __c) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1)));
extern size_t strcspn(const char * __s,
                      const char * __reject) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1, 2)));
extern size_t strspn(const char * __s,
                     const char * __accept) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1, 2)));
extern char * strpbrk(const char * __s,
                      const char * __accept) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1, 2)));
extern char * strstr(const char * __haystack,
                     const char * __needle) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1, 2)));
extern char * strtok(char * __restrict __s,
                     const char * __restrict __delim) __attribute__((__nothrow__,__leaf__,__nonnull__(2)));
extern char * __strtok_r(char * __restrict __s,
                         const char * __restrict __delim,
                         char * * __restrict __save_ptr) __attribute__((__nothrow__,__leaf__,__nonnull__(2, 3)));
extern char * strtok_r(char * __restrict __s,
                       const char * __restrict __delim,
                       char * * __restrict __save_ptr) __attribute__((__nothrow__,__leaf__,__nonnull__(2, 3)));
extern char * strcasestr(const char * __haystack,
                         const char * __needle) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1, 2)));
extern void * memmem(const void * __haystack,
                     size_t __haystacklen,
                     const void * __needle,
                     size_t __needlelen) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1, 3)));
extern void * __mempcpy(void * __restrict __dest,
                        const void * __restrict __src,
                        size_t __n) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern void * mempcpy(void * __restrict __dest,
                      const void * __restrict __src,
                      size_t __n) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern size_t strlen(const char * __s) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1)));
extern size_t strnlen(const char * __string,
                      size_t __maxlen) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1)));
extern char * strerror(int __errnum) __attribute__((__nothrow__,__leaf__));
extern char * strerror_r(int __errnum,
                         char * __buf,
                         size_t __buflen) __attribute__((__nothrow__,__leaf__,__nonnull__(2)));
extern char * strerror_l(int __errnum,
                         __locale_t __l) __attribute__((__nothrow__,__leaf__));
extern void __bzero(void * __s,
                    size_t __n) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern void bcopy(const void * __src,
                  void * __dest,
                  size_t __n) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern void bzero(void * __s,
                  size_t __n) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int bcmp(const void * __s1,
                const void * __s2,
                size_t __n) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1, 2)));
extern char * index(const char * __s,
                    int __c) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1)));
extern char * rindex(const char * __s,
                     int __c) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1)));
extern int ffs(int __i) __attribute__((__nothrow__,__leaf__,const));
extern int ffsl(long int __l) __attribute__((__nothrow__,__leaf__,const));
extern int ffsll(long long int __ll) __attribute__((__nothrow__,__leaf__,const));
extern int strcasecmp(const char * __s1,
                      const char * __s2) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1, 2)));
extern int strncasecmp(const char * __s1,
                       const char * __s2,
                       size_t __n) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1, 2)));
extern int strcasecmp_l(const char * __s1,
                        const char * __s2,
                        __locale_t __loc) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1, 2, 3)));
extern int strncasecmp_l(const char * __s1,
                         const char * __s2,
                         size_t __n,
                         __locale_t __loc) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1, 2, 4)));
extern char * strsep(char * * __restrict __stringp,
                     const char * __restrict __delim) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern char * strsignal(int __sig) __attribute__((__nothrow__,__leaf__));
extern char * __stpcpy(char * __restrict __dest,
                       const char * __restrict __src) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern char * stpcpy(char * __restrict __dest,
                     const char * __restrict __src) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern char * __stpncpy(char * __restrict __dest,
                        const char * __restrict __src,
                        size_t __n) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern char * stpncpy(char * __restrict __dest,
                      const char * __restrict __src,
                      size_t __n) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern int strverscmp(const char * __s1,
                      const char * __s2) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1, 2)));
extern char * strfry(char * __string) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern void * memfrob(void * __s,
                      size_t __n) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern char * basename(const char * __filename) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
typedef int wchar_t;
typedef enum {
            P_ALL, P_PID, P_PGID
        } idtype_t;
typedef struct {
            int quot; int rem;
        } div_t;
typedef struct {
            long int quot; long int rem;
        } ldiv_t;
typedef struct {
            long long int quot; long long int rem;
        } lldiv_t;
extern size_t __ctype_get_mb_cur_max(void) __attribute__((__nothrow__,__leaf__));
extern double atof(const char * __nptr) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1)));
extern int atoi(const char * __nptr) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1)));
extern long int atol(const char * __nptr) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1)));
extern long long int atoll(const char * __nptr) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1)));
extern double strtod(const char * __restrict __nptr,
                     char * * __restrict __endptr) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern float strtof(const char * __restrict __nptr,
                    char * * __restrict __endptr) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern long double strtold(const char * __restrict __nptr,
                           char * * __restrict __endptr) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern long int strtol(const char * __restrict __nptr,
                       char * * __restrict __endptr,
                       int __base) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern unsigned long int strtoul(const char * __restrict __nptr,
                                 char * * __restrict __endptr,
                                 int __base) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern long long int strtoq(const char * __restrict __nptr,
                            char * * __restrict __endptr,
                            int __base) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern unsigned long long int strtouq(const char * __restrict __nptr,
                                      char * * __restrict __endptr,
                                      int __base) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern long long int strtoll(const char * __restrict __nptr,
                             char * * __restrict __endptr,
                             int __base) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern unsigned long long int strtoull(const char * __restrict __nptr,
                                       char * * __restrict __endptr,
                                       int __base) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern long int strtol_l(const char * __restrict __nptr,
                         char * * __restrict __endptr,
                         int __base,
                         __locale_t __loc) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 4)));
extern unsigned long int strtoul_l(const char * __restrict __nptr,
                                   char * * __restrict __endptr,
                                   int __base,
                                   __locale_t __loc) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 4)));
extern long long int strtoll_l(const char * __restrict __nptr,
                               char * * __restrict __endptr,
                               int __base,
                               __locale_t __loc) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 4)));
extern unsigned long long int strtoull_l(const char * __restrict __nptr,
                                         char * * __restrict __endptr,
                                         int __base,
                                         __locale_t __loc) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 4)));
extern double strtod_l(const char * __restrict __nptr,
                       char * * __restrict __endptr,
                       __locale_t __loc) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 3)));
extern float strtof_l(const char * __restrict __nptr,
                      char * * __restrict __endptr,
                      __locale_t __loc) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 3)));
extern long double strtold_l(const char * __restrict __nptr,
                             char * * __restrict __endptr,
                             __locale_t __loc) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 3)));
extern char * l64a(long int __n) __attribute__((__nothrow__,__leaf__));
extern long int a64l(const char * __s) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1)));
typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;
typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;
typedef long int __quad_t;
typedef unsigned long int __u_quad_t;
typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct {
            int __val[2];
        } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;
typedef int __daddr_t;
typedef int __key_t;
typedef int __clockid_t;
typedef void * __timer_t;
typedef long int __blksize_t;
typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;
typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;
typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;
typedef long int __fsword_t;
typedef long int __ssize_t;
typedef long int __syscall_slong_t;
typedef unsigned long int __syscall_ulong_t;
typedef __off64_t __loff_t;
typedef __quad_t * __qaddr_t;
typedef char * __caddr_t;
typedef long int __intptr_t;
typedef unsigned int __socklen_t;
typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;
typedef __loff_t loff_t;
typedef __ino_t ino_t;
typedef __ino64_t ino64_t;
typedef __dev_t dev_t;
typedef __gid_t gid_t;
typedef __mode_t mode_t;
typedef __nlink_t nlink_t;
typedef __uid_t uid_t;
typedef __off_t off_t;
typedef __off64_t off64_t;
typedef __pid_t pid_t;
typedef __id_t id_t;
typedef __ssize_t ssize_t;
typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;
typedef __key_t key_t;
typedef __clock_t clock_t;
typedef __time_t time_t;
typedef __clockid_t clockid_t;
typedef __timer_t timer_t;
typedef __useconds_t useconds_t;
typedef __suseconds_t suseconds_t;
typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;
typedef int int8_t __attribute__((__mode__(__QI__)));
typedef int int16_t __attribute__((__mode__(__HI__)));
typedef int int32_t __attribute__((__mode__(__SI__)));
typedef int int64_t __attribute__((__mode__(__DI__)));
typedef unsigned int u_int8_t __attribute__((__mode__(__QI__)));
typedef unsigned int u_int16_t __attribute__((__mode__(__HI__)));
typedef unsigned int u_int32_t __attribute__((__mode__(__SI__)));
typedef unsigned int u_int64_t __attribute__((__mode__(__DI__)));
typedef int register_t __attribute__((__mode__(__word__)));
static inline unsigned int __bswap_32(unsigned int __bsx)
{
    return __builtin_bswap32(__bsx);
}
static inline __uint64_t __bswap_64(__uint64_t __bsx)
{
    return __builtin_bswap64(__bsx);
}
typedef int __sig_atomic_t;
typedef struct {
            unsigned long int __val[1024 / (8 * sizeof(unsigned long int))];
        } __sigset_t;
typedef __sigset_t sigset_t;
struct timespec {
    __time_t tv_sec; __syscall_slong_t tv_nsec;
};
struct timeval {
    __time_t tv_sec; __suseconds_t tv_usec;
};
typedef long int __fd_mask;
typedef struct {
            __fd_mask fds_bits[1024 / (8 * (int) sizeof(__fd_mask))];
        } fd_set;
typedef __fd_mask fd_mask;
extern int select(int __nfds,
                  fd_set * __restrict __readfds,
                  fd_set * __restrict __writefds,
                  fd_set * __restrict __exceptfds,
                  struct timeval * __restrict __timeout);
extern int pselect(int __nfds,
                   fd_set * __restrict __readfds,
                   fd_set * __restrict __writefds,
                   fd_set * __restrict __exceptfds,
                   const struct timespec * __restrict __timeout,
                   const __sigset_t * __restrict __sigmask);
extern unsigned int gnu_dev_major(unsigned long long int __dev) __attribute__((__nothrow__,__leaf__,const));
extern unsigned int gnu_dev_minor(unsigned long long int __dev) __attribute__((__nothrow__,__leaf__,const));
extern unsigned long long int gnu_dev_makedev(unsigned int __major,
                                              unsigned int __minor) __attribute__((__nothrow__,__leaf__,const));
typedef __blksize_t blksize_t;
typedef __blkcnt_t blkcnt_t;
typedef __fsblkcnt_t fsblkcnt_t;
typedef __fsfilcnt_t fsfilcnt_t;
typedef __blkcnt64_t blkcnt64_t;
typedef __fsblkcnt64_t fsblkcnt64_t;
typedef __fsfilcnt64_t fsfilcnt64_t;
typedef unsigned long int pthread_t;
union pthread_attr_t {
    char __size[56]; long int __align;
};
typedef union pthread_attr_t pthread_attr_t;
typedef struct __pthread_internal_list {
            struct __pthread_internal_list * __prev;
            struct __pthread_internal_list * __next;
        } __pthread_list_t;
typedef union {
            struct __pthread_mutex_s {
                int __lock;
                unsigned int __count;
                int __owner;
                unsigned int __nusers;
                int __kind;
                short __spins;
                short __elision;
                __pthread_list_t __list;
            } __data;
            char __size[40];
            long int __align;
        } pthread_mutex_t;
typedef union {
            char __size[4]; int __align;
        } pthread_mutexattr_t;
typedef union {
            struct {
                int __lock;
                unsigned int __futex;
                unsigned long long int __total_seq;
                unsigned long long int __wakeup_seq;
                unsigned long long int __woken_seq;
                void * __mutex;
                unsigned int __nwaiters;
                unsigned int __broadcast_seq;
            } __data;
            char __size[48];
            long long int __align;
        } pthread_cond_t;
typedef union {
            char __size[4]; int __align;
        } pthread_condattr_t;
typedef unsigned int pthread_key_t;
typedef int pthread_once_t;
typedef union {
            struct {
                int __lock;
                unsigned int __nr_readers;
                unsigned int __readers_wakeup;
                unsigned int __writer_wakeup;
                unsigned int __nr_readers_queued;
                unsigned int __nr_writers_queued;
                int __writer;
                int __shared;
                signed char __rwelision;
                unsigned char __pad1[7];
                unsigned long int __pad2;
                unsigned int __flags;
            } __data;
            char __size[56];
            long int __align;
        } pthread_rwlock_t;
typedef union {
            char __size[8]; long int __align;
        } pthread_rwlockattr_t;
typedef volatile int pthread_spinlock_t;
typedef union {
            char __size[32]; long int __align;
        } pthread_barrier_t;
typedef union {
            char __size[4]; int __align;
        } pthread_barrierattr_t;
extern long int random(void) __attribute__((__nothrow__,__leaf__));
extern void srandom(unsigned int __seed) __attribute__((__nothrow__,__leaf__));
extern char * initstate(unsigned int __seed,
                        char * __statebuf,
                        size_t __statelen) __attribute__((__nothrow__,__leaf__,__nonnull__(2)));
extern char * setstate(char * __statebuf) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
struct random_data {
    int32_t * fptr;
    int32_t * rptr;
    int32_t * state;
    int rand_type;
    int rand_deg;
    int rand_sep;
    int32_t * end_ptr;
};
extern int random_r(struct random_data * __restrict __buf,
                    int32_t * __restrict __result) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern int srandom_r(unsigned int __seed,
                     struct random_data * __buf) __attribute__((__nothrow__,__leaf__,__nonnull__(2)));
extern int initstate_r(unsigned int __seed,
                       char * __restrict __statebuf,
                       size_t __statelen,
                       struct random_data * __restrict __buf) __attribute__((__nothrow__,__leaf__,__nonnull__(2, 4)));
extern int setstate_r(char * __restrict __statebuf,
                      struct random_data * __restrict __buf) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern int rand(void) __attribute__((__nothrow__,__leaf__));
extern void srand(unsigned int __seed) __attribute__((__nothrow__,__leaf__));
extern int rand_r(unsigned int * __seed) __attribute__((__nothrow__,__leaf__));
extern double drand48(void) __attribute__((__nothrow__,__leaf__));
extern double erand48(unsigned short int __xsubi[3]) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern long int lrand48(void) __attribute__((__nothrow__,__leaf__));
extern long int nrand48(unsigned short int __xsubi[3]) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern long int mrand48(void) __attribute__((__nothrow__,__leaf__));
extern long int jrand48(unsigned short int __xsubi[3]) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern void srand48(long int __seedval) __attribute__((__nothrow__,__leaf__));
extern unsigned short int * seed48(unsigned short int __seed16v[3]) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern void lcong48(unsigned short int __param[7]) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
struct drand48_data {
    unsigned short int __x[3];
    unsigned short int __old_x[3];
    unsigned short int __c;
    unsigned short int __init;
    unsigned long long int __a;
};
extern int drand48_r(struct drand48_data * __restrict __buffer,
                     double * __restrict __result) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern int erand48_r(unsigned short int __xsubi[3],
                     struct drand48_data * __restrict __buffer,
                     double * __restrict __result) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern int lrand48_r(struct drand48_data * __restrict __buffer,
                     long int * __restrict __result) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern int nrand48_r(unsigned short int __xsubi[3],
                     struct drand48_data * __restrict __buffer,
                     long int * __restrict __result) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern int mrand48_r(struct drand48_data * __restrict __buffer,
                     long int * __restrict __result) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern int jrand48_r(unsigned short int __xsubi[3],
                     struct drand48_data * __restrict __buffer,
                     long int * __restrict __result) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern int srand48_r(long int __seedval,
                     struct drand48_data * __buffer) __attribute__((__nothrow__,__leaf__,__nonnull__(2)));
extern int seed48_r(unsigned short int __seed16v[3],
                    struct drand48_data * __buffer) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern int lcong48_r(unsigned short int __param[7],
                     struct drand48_data * __buffer) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern void * malloc(size_t __size) __attribute__((__nothrow__,__leaf__,__malloc__));
extern void * calloc(size_t __nmemb,
                     size_t __size) __attribute__((__nothrow__,__leaf__,__malloc__));
extern void * realloc(void * __ptr,
                      size_t __size) __attribute__((__nothrow__,__leaf__,__warn_unused_result__));
extern void free(void * __ptr) __attribute__((__nothrow__,__leaf__));
extern void cfree(void * __ptr) __attribute__((__nothrow__,__leaf__));
extern void * alloca(size_t __size) __attribute__((__nothrow__,__leaf__));
extern void * valloc(size_t __size) __attribute__((__nothrow__,__leaf__,__malloc__));
extern int posix_memalign(void * * __memptr,
                          size_t __alignment,
                          size_t __size) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern void * aligned_alloc(size_t __alignment,
                            size_t __size) __attribute__((__nothrow__,__leaf__,__malloc__,__alloc_size__(2)));
extern void abort(void) __attribute__((__nothrow__,__leaf__,__noreturn__));
extern int atexit(void (* __func)(void)) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int at_quick_exit(void (* __func)(void)) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int on_exit(void (* __func)(int __status, void * __arg),
                   void * __arg) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern void exit(int __status) __attribute__((__nothrow__,__leaf__,__noreturn__));
extern void quick_exit(int __status) __attribute__((__nothrow__,__leaf__,__noreturn__));
extern void _Exit(int __status) __attribute__((__nothrow__,__leaf__,__noreturn__));
extern char * getenv(const char * __name) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern char * secure_getenv(const char * __name) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int putenv(char * __string) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int setenv(const char * __name,
                  const char * __value,
                  int __replace) __attribute__((__nothrow__,__leaf__,__nonnull__(2)));
extern int unsetenv(const char * __name) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int clearenv(void) __attribute__((__nothrow__,__leaf__));
extern char * mktemp(char * __template) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int mkstemp(char * __template) __attribute__((__nonnull__(1)));
extern int mkstemp64(char * __template) __attribute__((__nonnull__(1)));
extern int mkstemps(char * __template,
                    int __suffixlen) __attribute__((__nonnull__(1)));
extern int mkstemps64(char * __template,
                      int __suffixlen) __attribute__((__nonnull__(1)));
extern char * mkdtemp(char * __template) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int mkostemp(char * __template,
                    int __flags) __attribute__((__nonnull__(1)));
extern int mkostemp64(char * __template,
                      int __flags) __attribute__((__nonnull__(1)));
extern int mkostemps(char * __template,
                     int __suffixlen,
                     int __flags) __attribute__((__nonnull__(1)));
extern int mkostemps64(char * __template,
                       int __suffixlen,
                       int __flags) __attribute__((__nonnull__(1)));
extern int system(const char * __command);
extern char * canonicalize_file_name(const char * __name) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern char * realpath(const char * __restrict __name,
                       char * __restrict __resolved) __attribute__((__nothrow__,__leaf__));
typedef int (* __compar_fn_t)(const void *, const void *);
typedef __compar_fn_t comparison_fn_t;
typedef int (* __compar_d_fn_t)(const void *,
                                const void *,
                                void *);
extern void * bsearch(const void * __key,
                      const void * __base,
                      size_t __nmemb,
                      size_t __size,
                      __compar_fn_t __compar) __attribute__((__nonnull__(1, 2, 5)));
extern void qsort(void * __base,
                  size_t __nmemb,
                  size_t __size,
                  __compar_fn_t __compar) __attribute__((__nonnull__(1, 4)));
extern void qsort_r(void * __base,
                    size_t __nmemb,
                    size_t __size,
                    __compar_d_fn_t __compar,
                    void * __arg) __attribute__((__nonnull__(1, 4)));
extern int abs(int __x) __attribute__((__nothrow__,__leaf__,const));
extern long int labs(long int __x) __attribute__((__nothrow__,__leaf__,const));
extern long long int llabs(long long int __x) __attribute__((__nothrow__,__leaf__,const));
extern div_t div(int __numer,
                 int __denom) __attribute__((__nothrow__,__leaf__,const));
extern ldiv_t ldiv(long int __numer,
                   long int __denom) __attribute__((__nothrow__,__leaf__,const));
extern lldiv_t lldiv(long long int __numer,
                     long long int __denom) __attribute__((__nothrow__,__leaf__,const));
extern char * ecvt(double __value,
                   int __ndigit,
                   int * __restrict __decpt,
                   int * __restrict __sign) __attribute__((__nothrow__,__leaf__,__nonnull__(3, 4)));
extern char * fcvt(double __value,
                   int __ndigit,
                   int * __restrict __decpt,
                   int * __restrict __sign) __attribute__((__nothrow__,__leaf__,__nonnull__(3, 4)));
extern char * gcvt(double __value,
                   int __ndigit,
                   char * __buf) __attribute__((__nothrow__,__leaf__,__nonnull__(3)));
extern char * qecvt(long double __value,
                    int __ndigit,
                    int * __restrict __decpt,
                    int * __restrict __sign) __attribute__((__nothrow__,__leaf__,__nonnull__(3, 4)));
extern char * qfcvt(long double __value,
                    int __ndigit,
                    int * __restrict __decpt,
                    int * __restrict __sign) __attribute__((__nothrow__,__leaf__,__nonnull__(3, 4)));
extern char * qgcvt(long double __value,
                    int __ndigit,
                    char * __buf) __attribute__((__nothrow__,__leaf__,__nonnull__(3)));
extern int ecvt_r(double __value,
                  int __ndigit,
                  int * __restrict __decpt,
                  int * __restrict __sign,
                  char * __restrict __buf,
                  size_t __len) __attribute__((__nothrow__,__leaf__,__nonnull__(3, 4, 5)));
extern int fcvt_r(double __value,
                  int __ndigit,
                  int * __restrict __decpt,
                  int * __restrict __sign,
                  char * __restrict __buf,
                  size_t __len) __attribute__((__nothrow__,__leaf__,__nonnull__(3, 4, 5)));
extern int qecvt_r(long double __value,
                   int __ndigit,
                   int * __restrict __decpt,
                   int * __restrict __sign,
                   char * __restrict __buf,
                   size_t __len) __attribute__((__nothrow__,__leaf__,__nonnull__(3, 4, 5)));
extern int qfcvt_r(long double __value,
                   int __ndigit,
                   int * __restrict __decpt,
                   int * __restrict __sign,
                   char * __restrict __buf,
                   size_t __len) __attribute__((__nothrow__,__leaf__,__nonnull__(3, 4, 5)));
extern int mblen(const char * __s,
                 size_t __n) __attribute__((__nothrow__,__leaf__));
extern int mbtowc(wchar_t * __restrict __pwc,
                  const char * __restrict __s,
                  size_t __n) __attribute__((__nothrow__,__leaf__));
extern int wctomb(char * __s,
                  wchar_t __wchar) __attribute__((__nothrow__,__leaf__));
extern size_t mbstowcs(wchar_t * __restrict __pwcs,
                       const char * __restrict __s,
                       size_t __n) __attribute__((__nothrow__,__leaf__));
extern size_t wcstombs(char * __restrict __s,
                       const wchar_t * __restrict __pwcs,
                       size_t __n) __attribute__((__nothrow__,__leaf__));
extern int rpmatch(const char * __response) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int getsubopt(char * * __restrict __optionp,
                     char * const * __restrict __tokens,
                     char * * __restrict __valuep) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2, 3)));
extern void setkey(const char * __key) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int posix_openpt(int __oflag);
extern int grantpt(int __fd) __attribute__((__nothrow__,__leaf__));
extern int unlockpt(int __fd) __attribute__((__nothrow__,__leaf__));
extern char * ptsname(int __fd) __attribute__((__nothrow__,__leaf__));
extern int ptsname_r(int __fd,
                     char * __buf,
                     size_t __buflen) __attribute__((__nothrow__,__leaf__,__nonnull__(2)));
extern int getpt(void);
extern int getloadavg(double __loadavg[],
                      int __nelem) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
struct _IO_FILE;
typedef struct _IO_FILE FILE;
typedef struct _IO_FILE __FILE;
typedef struct {
            int __count;
            union {
                unsigned int __wch; char __wchb[4];
            } __value;
        } __mbstate_t;
typedef struct {
            __off_t __pos; __mbstate_t __state;
        } _G_fpos_t;
typedef struct {
            __off64_t __pos; __mbstate_t __state;
        } _G_fpos64_t;
typedef __builtin_va_list __gnuc_va_list;
struct _IO_jump_t;
struct _IO_FILE;
typedef void _IO_lock_t;
struct _IO_marker {
    struct _IO_marker * _next; struct _IO_FILE * _sbuf; int _pos;
};
enum __codecvt_result {
    __codecvt_ok, __codecvt_partial, __codecvt_error, __codecvt_noconv
};
struct _IO_FILE {
    int _flags;
    char * _IO_read_ptr;
    char * _IO_read_end;
    char * _IO_read_base;
    char * _IO_write_base;
    char * _IO_write_ptr;
    char * _IO_write_end;
    char * _IO_buf_base;
    char * _IO_buf_end;
    char * _IO_save_base;
    char * _IO_backup_base;
    char * _IO_save_end;
    struct _IO_marker * _markers;
    struct _IO_FILE * _chain;
    int _fileno;
    int _flags2;
    __off_t _old_offset;
    unsigned short _cur_column;
    signed char _vtable_offset;
    char _shortbuf[1];
    _IO_lock_t * _lock;
    __off64_t _offset;
    void * __pad1;
    void * __pad2;
    void * __pad3;
    void * __pad4;
    size_t __pad5;
    int _mode;
    char _unused2[15 * sizeof(int) - 4 * sizeof(void *) - sizeof(size_t)];
};
typedef struct _IO_FILE _IO_FILE;
struct _IO_FILE_plus;
extern struct _IO_FILE_plus _IO_2_1_stdin_;
extern struct _IO_FILE_plus _IO_2_1_stdout_;
extern struct _IO_FILE_plus _IO_2_1_stderr_;
typedef __ssize_t __io_read_fn(void * __cookie,
                               char * __buf,
                               size_t __nbytes);
typedef __ssize_t __io_write_fn(void * __cookie,
                                const char * __buf,
                                size_t __n);
typedef int __io_seek_fn(void * __cookie,
                         __off64_t * __pos,
                         int __w);
typedef int __io_close_fn(void * __cookie);
typedef __io_read_fn cookie_read_function_t;
typedef __io_write_fn cookie_write_function_t;
typedef __io_seek_fn cookie_seek_function_t;
typedef __io_close_fn cookie_close_function_t;
typedef struct {
            __io_read_fn * read;
            __io_write_fn * write;
            __io_seek_fn * seek;
            __io_close_fn * close;
        } _IO_cookie_io_functions_t;
typedef _IO_cookie_io_functions_t cookie_io_functions_t;
struct _IO_cookie_file;
extern void _IO_cookie_init(struct _IO_cookie_file * __cfile,
                            int __read_write,
                            void * __cookie,
                            _IO_cookie_io_functions_t __fns);
extern int __underflow(_IO_FILE *);
extern int __uflow(_IO_FILE *);
extern int __overflow(_IO_FILE *, int);
extern int _IO_getc(_IO_FILE * __fp);
extern int _IO_putc(int __c, _IO_FILE * __fp);
extern int _IO_feof(_IO_FILE * __fp) __attribute__((__nothrow__,__leaf__));
extern int _IO_ferror(_IO_FILE * __fp) __attribute__((__nothrow__,__leaf__));
extern int _IO_peekc_locked(_IO_FILE * __fp);
extern void _IO_flockfile(_IO_FILE *) __attribute__((__nothrow__,__leaf__));
extern void _IO_funlockfile(_IO_FILE *) __attribute__((__nothrow__,__leaf__));
extern int _IO_ftrylockfile(_IO_FILE *) __attribute__((__nothrow__,__leaf__));
extern int _IO_vfscanf(_IO_FILE * __restrict,
                       const char * __restrict,
                       __gnuc_va_list,
                       int * __restrict);
extern int _IO_vfprintf(_IO_FILE * __restrict,
                        const char * __restrict,
                        __gnuc_va_list);
extern __ssize_t _IO_padn(_IO_FILE *, int, __ssize_t);
extern size_t _IO_sgetn(_IO_FILE *, void *, size_t);
extern __off64_t _IO_seekoff(_IO_FILE *, __off64_t, int, int);
extern __off64_t _IO_seekpos(_IO_FILE *, __off64_t, int);
extern void _IO_free_backup_area(_IO_FILE *) __attribute__((__nothrow__,__leaf__));
typedef __gnuc_va_list va_list;
typedef _G_fpos_t fpos_t;
typedef _G_fpos64_t fpos64_t;
extern struct _IO_FILE * stdin;
extern struct _IO_FILE * stdout;
extern struct _IO_FILE * stderr;
extern int remove(const char * __filename) __attribute__((__nothrow__,__leaf__));
extern int rename(const char * __old,
                  const char * __new) __attribute__((__nothrow__,__leaf__));
extern int renameat(int __oldfd,
                    const char * __old,
                    int __newfd,
                    const char * __new) __attribute__((__nothrow__,__leaf__));
extern FILE * tmpfile(void);
extern FILE * tmpfile64(void);
extern char * tmpnam(char * __s) __attribute__((__nothrow__,__leaf__));
extern char * tmpnam_r(char * __s) __attribute__((__nothrow__,__leaf__));
extern char * tempnam(const char * __dir,
                      const char * __pfx) __attribute__((__nothrow__,__leaf__,__malloc__));
extern int fclose(FILE * __stream);
extern int fflush(FILE * __stream);
extern int fflush_unlocked(FILE * __stream);
extern int fcloseall(void);
extern FILE * fopen(const char * __restrict __filename,
                    const char * __restrict __modes);
extern FILE * freopen(const char * __restrict __filename,
                      const char * __restrict __modes,
                      FILE * __restrict __stream);
extern FILE * fopen64(const char * __restrict __filename,
                      const char * __restrict __modes);
extern FILE * freopen64(const char * __restrict __filename,
                        const char * __restrict __modes,
                        FILE * __restrict __stream);
extern FILE * fdopen(int __fd,
                     const char * __modes) __attribute__((__nothrow__,__leaf__));
extern FILE * fopencookie(void * __restrict __magic_cookie,
                          const char * __restrict __modes,
                          _IO_cookie_io_functions_t __io_funcs) __attribute__((__nothrow__,__leaf__));
extern FILE * fmemopen(void * __s,
                       size_t __len,
                       const char * __modes) __attribute__((__nothrow__,__leaf__));
extern FILE * open_memstream(char * * __bufloc,
                             size_t * __sizeloc) __attribute__((__nothrow__,__leaf__));
extern void setbuf(FILE * __restrict __stream,
                   char * __restrict __buf) __attribute__((__nothrow__,__leaf__));
extern int setvbuf(FILE * __restrict __stream,
                   char * __restrict __buf,
                   int __modes,
                   size_t __n) __attribute__((__nothrow__,__leaf__));
extern void setbuffer(FILE * __restrict __stream,
                      char * __restrict __buf,
                      size_t __size) __attribute__((__nothrow__,__leaf__));
extern void setlinebuf(FILE * __stream) __attribute__((__nothrow__,__leaf__));
extern int fprintf(FILE * __restrict __stream,
                   const char * __restrict __format, ...);
extern int printf(const char * __restrict __format, ...);
extern int sprintf(char * __restrict __s,
                   const char * __restrict __format, ...) __attribute__((__nothrow__));
extern int vfprintf(FILE * __restrict __s,
                    const char * __restrict __format,
                    __gnuc_va_list __arg);
extern int vprintf(const char * __restrict __format,
                   __gnuc_va_list __arg);
extern int vsprintf(char * __restrict __s,
                    const char * __restrict __format,
                    __gnuc_va_list __arg) __attribute__((__nothrow__));
extern int snprintf(char * __restrict __s,
                    size_t __maxlen,
                    const char * __restrict __format, ...) __attribute__((__nothrow__,__format__(__printf__, 3, 4)));
extern int vsnprintf(char * __restrict __s,
                     size_t __maxlen,
                     const char * __restrict __format,
                     __gnuc_va_list __arg) __attribute__((__nothrow__,__format__(__printf__, 3, 0)));
extern int vasprintf(char * * __restrict __ptr,
                     const char * __restrict __f,
                     __gnuc_va_list __arg) __attribute__((__nothrow__,__format__(__printf__, 2, 0)));
extern int __asprintf(char * * __restrict __ptr,
                      const char * __restrict __fmt, ...) __attribute__((__nothrow__,__format__(__printf__, 2, 3)));
extern int asprintf(char * * __restrict __ptr,
                    const char * __restrict __fmt, ...) __attribute__((__nothrow__,__format__(__printf__, 2, 3)));
extern int vdprintf(int __fd,
                    const char * __restrict __fmt,
                    __gnuc_va_list __arg) __attribute__((__format__(__printf__, 2, 0)));
extern int dprintf(int __fd,
                   const char * __restrict __fmt, ...) __attribute__((__format__(__printf__, 2, 3)));
extern int fscanf(FILE * __restrict __stream,
                  const char * __restrict __format, ...);
extern int scanf(const char * __restrict __format, ...);
extern int sscanf(const char * __restrict __s,
                  const char * __restrict __format, ...) __attribute__((__nothrow__,__leaf__));
extern int vfscanf(FILE * __restrict __s,
                   const char * __restrict __format,
                   __gnuc_va_list __arg) __attribute__((__format__(__scanf__, 2, 0)));
extern int vscanf(const char * __restrict __format,
                  __gnuc_va_list __arg) __attribute__((__format__(__scanf__, 1, 0)));
extern int vsscanf(const char * __restrict __s,
                   const char * __restrict __format,
                   __gnuc_va_list __arg) __attribute__((__nothrow__,__leaf__,__format__(__scanf__, 2, 0)));
extern int fgetc(FILE * __stream);
extern int getc(FILE * __stream);
extern int getchar(void);
extern int getc_unlocked(FILE * __stream);
extern int getchar_unlocked(void);
extern int fgetc_unlocked(FILE * __stream);
extern int fputc(int __c, FILE * __stream);
extern int putc(int __c, FILE * __stream);
extern int putchar(int __c);
extern int fputc_unlocked(int __c, FILE * __stream);
extern int putc_unlocked(int __c, FILE * __stream);
extern int putchar_unlocked(int __c);
extern int getw(FILE * __stream);
extern int putw(int __w, FILE * __stream);
extern char * fgets(char * __restrict __s,
                    int __n,
                    FILE * __restrict __stream);
extern char * fgets_unlocked(char * __restrict __s,
                             int __n,
                             FILE * __restrict __stream);
extern __ssize_t __getdelim(char * * __restrict __lineptr,
                            size_t * __restrict __n,
                            int __delimiter,
                            FILE * __restrict __stream);
extern __ssize_t getdelim(char * * __restrict __lineptr,
                          size_t * __restrict __n,
                          int __delimiter,
                          FILE * __restrict __stream);
extern __ssize_t getline(char * * __restrict __lineptr,
                         size_t * __restrict __n,
                         FILE * __restrict __stream);
extern int fputs(const char * __restrict __s,
                 FILE * __restrict __stream);
extern int puts(const char * __s);
extern int ungetc(int __c, FILE * __stream);
extern size_t fread(void * __restrict __ptr,
                    size_t __size,
                    size_t __n,
                    FILE * __restrict __stream);
extern size_t fwrite(const void * __restrict __ptr,
                     size_t __size,
                     size_t __n,
                     FILE * __restrict __s);
extern int fputs_unlocked(const char * __restrict __s,
                          FILE * __restrict __stream);
extern size_t fread_unlocked(void * __restrict __ptr,
                             size_t __size,
                             size_t __n,
                             FILE * __restrict __stream);
extern size_t fwrite_unlocked(const void * __restrict __ptr,
                              size_t __size,
                              size_t __n,
                              FILE * __restrict __stream);
extern int fseek(FILE * __stream, long int __off, int __whence);
extern long int ftell(FILE * __stream);
extern void rewind(FILE * __stream);
extern int fseeko(FILE * __stream, __off_t __off, int __whence);
extern __off_t ftello(FILE * __stream);
extern int fgetpos(FILE * __restrict __stream,
                   fpos_t * __restrict __pos);
extern int fsetpos(FILE * __stream, const fpos_t * __pos);
extern int fseeko64(FILE * __stream,
                    __off64_t __off,
                    int __whence);
extern __off64_t ftello64(FILE * __stream);
extern int fgetpos64(FILE * __restrict __stream,
                     fpos64_t * __restrict __pos);
extern int fsetpos64(FILE * __stream, const fpos64_t * __pos);
extern void clearerr(FILE * __stream) __attribute__((__nothrow__,__leaf__));
extern int feof(FILE * __stream) __attribute__((__nothrow__,__leaf__));
extern int ferror(FILE * __stream) __attribute__((__nothrow__,__leaf__));
extern void clearerr_unlocked(FILE * __stream) __attribute__((__nothrow__,__leaf__));
extern int feof_unlocked(FILE * __stream) __attribute__((__nothrow__,__leaf__));
extern int ferror_unlocked(FILE * __stream) __attribute__((__nothrow__,__leaf__));
extern void perror(const char * __s);
extern int sys_nerr;
extern const char * const sys_errlist[];
extern int _sys_nerr;
extern const char * const _sys_errlist[];
extern int fileno(FILE * __stream) __attribute__((__nothrow__,__leaf__));
extern int fileno_unlocked(FILE * __stream) __attribute__((__nothrow__,__leaf__));
extern FILE * popen(const char * __command, const char * __modes);
extern int pclose(FILE * __stream);
extern char * ctermid(char * __s) __attribute__((__nothrow__,__leaf__));
extern char * cuserid(char * __s);
struct obstack;
extern int obstack_printf(struct obstack * __restrict __obstack,
                          const char * __restrict __format, ...) __attribute__((__nothrow__,__format__(__printf__, 2, 3)));
extern int obstack_vprintf(struct obstack * __restrict __obstack,
                           const char * __restrict __format,
                           __gnuc_va_list __args) __attribute__((__nothrow__,__format__(__printf__, 2, 0)));
extern void flockfile(FILE * __stream) __attribute__((__nothrow__,__leaf__));
extern int ftrylockfile(FILE * __stream) __attribute__((__nothrow__,__leaf__));
extern void funlockfile(FILE * __stream) __attribute__((__nothrow__,__leaf__));
typedef __intptr_t intptr_t;
typedef __socklen_t socklen_t;
extern int access(const char * __name,
                  int __type) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int euidaccess(const char * __name,
                      int __type) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int eaccess(const char * __name,
                   int __type) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int faccessat(int __fd,
                     const char * __file,
                     int __type,
                     int __flag) __attribute__((__nothrow__,__leaf__,__nonnull__(2)));
extern __off_t lseek(int __fd,
                     __off_t __offset,
                     int __whence) __attribute__((__nothrow__,__leaf__));
extern __off64_t lseek64(int __fd,
                         __off64_t __offset,
                         int __whence) __attribute__((__nothrow__,__leaf__));
extern int close(int __fd);
extern ssize_t read(int __fd, void * __buf, size_t __nbytes);
extern ssize_t write(int __fd, const void * __buf, size_t __n);
extern ssize_t pread(int __fd,
                     void * __buf,
                     size_t __nbytes,
                     __off_t __offset);
extern ssize_t pwrite(int __fd,
                      const void * __buf,
                      size_t __n,
                      __off_t __offset);
extern ssize_t pread64(int __fd,
                       void * __buf,
                       size_t __nbytes,
                       __off64_t __offset);
extern ssize_t pwrite64(int __fd,
                        const void * __buf,
                        size_t __n,
                        __off64_t __offset);
extern int pipe(int __pipedes[2]) __attribute__((__nothrow__,__leaf__));
extern int pipe2(int __pipedes[2],
                 int __flags) __attribute__((__nothrow__,__leaf__));
extern unsigned int alarm(unsigned int __seconds) __attribute__((__nothrow__,__leaf__));
extern unsigned int sleep(unsigned int __seconds);
extern __useconds_t ualarm(__useconds_t __value,
                           __useconds_t __interval) __attribute__((__nothrow__,__leaf__));
extern int usleep(__useconds_t __useconds);
extern int pause(void);
extern int chown(const char * __file,
                 __uid_t __owner,
                 __gid_t __group) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int fchown(int __fd,
                  __uid_t __owner,
                  __gid_t __group) __attribute__((__nothrow__,__leaf__));
extern int lchown(const char * __file,
                  __uid_t __owner,
                  __gid_t __group) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int fchownat(int __fd,
                    const char * __file,
                    __uid_t __owner,
                    __gid_t __group,
                    int __flag) __attribute__((__nothrow__,__leaf__,__nonnull__(2)));
extern int chdir(const char * __path) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int fchdir(int __fd) __attribute__((__nothrow__,__leaf__));
extern char * getcwd(char * __buf,
                     size_t __size) __attribute__((__nothrow__,__leaf__));
extern char * get_current_dir_name(void) __attribute__((__nothrow__,__leaf__));
extern char * getwd(char * __buf) __attribute__((__nothrow__,__leaf__,__nonnull__(1),__deprecated__));
extern int dup(int __fd) __attribute__((__nothrow__,__leaf__));
extern int dup2(int __fd,
                int __fd2) __attribute__((__nothrow__,__leaf__));
extern int dup3(int __fd,
                int __fd2,
                int __flags) __attribute__((__nothrow__,__leaf__));
extern char * * __environ;
extern char * * environ;
extern int execve(const char * __path,
                  char * const __argv[],
                  char * const __envp[]) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern int fexecve(int __fd,
                   char * const __argv[],
                   char * const __envp[]) __attribute__((__nothrow__,__leaf__,__nonnull__(2)));
extern int execv(const char * __path,
                 char * const __argv[]) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern int execle(const char * __path,
                  const char * __arg, ...) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern int execl(const char * __path,
                 const char * __arg, ...) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern int execvp(const char * __file,
                  char * const __argv[]) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern int execlp(const char * __file,
                  const char * __arg, ...) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern int execvpe(const char * __file,
                   char * const __argv[],
                   char * const __envp[]) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern int nice(int __inc) __attribute__((__nothrow__,__leaf__));
extern void _exit(int __status) __attribute__((__noreturn__));
enum {
    _PC_LINK_MAX,
    _PC_MAX_CANON,
    _PC_MAX_INPUT,
    _PC_NAME_MAX,
    _PC_PATH_MAX,
    _PC_PIPE_BUF,
    _PC_CHOWN_RESTRICTED,
    _PC_NO_TRUNC,
    _PC_VDISABLE,
    _PC_SYNC_IO,
    _PC_ASYNC_IO,
    _PC_PRIO_IO,
    _PC_SOCK_MAXBUF,
    _PC_FILESIZEBITS,
    _PC_REC_INCR_XFER_SIZE,
    _PC_REC_MAX_XFER_SIZE,
    _PC_REC_MIN_XFER_SIZE,
    _PC_REC_XFER_ALIGN,
    _PC_ALLOC_SIZE_MIN,
    _PC_SYMLINK_MAX,
    _PC_2_SYMLINKS
};
enum {
    _SC_ARG_MAX,
    _SC_CHILD_MAX,
    _SC_CLK_TCK,
    _SC_NGROUPS_MAX,
    _SC_OPEN_MAX,
    _SC_STREAM_MAX,
    _SC_TZNAME_MAX,
    _SC_JOB_CONTROL,
    _SC_SAVED_IDS,
    _SC_REALTIME_SIGNALS,
    _SC_PRIORITY_SCHEDULING,
    _SC_TIMERS,
    _SC_ASYNCHRONOUS_IO,
    _SC_PRIORITIZED_IO,
    _SC_SYNCHRONIZED_IO,
    _SC_FSYNC,
    _SC_MAPPED_FILES,
    _SC_MEMLOCK,
    _SC_MEMLOCK_RANGE,
    _SC_MEMORY_PROTECTION,
    _SC_MESSAGE_PASSING,
    _SC_SEMAPHORES,
    _SC_SHARED_MEMORY_OBJECTS,
    _SC_AIO_LISTIO_MAX,
    _SC_AIO_MAX,
    _SC_AIO_PRIO_DELTA_MAX,
    _SC_DELAYTIMER_MAX,
    _SC_MQ_OPEN_MAX,
    _SC_MQ_PRIO_MAX,
    _SC_VERSION,
    _SC_PAGESIZE,
    _SC_RTSIG_MAX,
    _SC_SEM_NSEMS_MAX,
    _SC_SEM_VALUE_MAX,
    _SC_SIGQUEUE_MAX,
    _SC_TIMER_MAX,
    _SC_BC_BASE_MAX,
    _SC_BC_DIM_MAX,
    _SC_BC_SCALE_MAX,
    _SC_BC_STRING_MAX,
    _SC_COLL_WEIGHTS_MAX,
    _SC_EQUIV_CLASS_MAX,
    _SC_EXPR_NEST_MAX,
    _SC_LINE_MAX,
    _SC_RE_DUP_MAX,
    _SC_CHARCLASS_NAME_MAX,
    _SC_2_VERSION,
    _SC_2_C_BIND,
    _SC_2_C_DEV,
    _SC_2_FORT_DEV,
    _SC_2_FORT_RUN,
    _SC_2_SW_DEV,
    _SC_2_LOCALEDEF,
    _SC_PII,
    _SC_PII_XTI,
    _SC_PII_SOCKET,
    _SC_PII_INTERNET,
    _SC_PII_OSI,
    _SC_POLL,
    _SC_SELECT,
    _SC_UIO_MAXIOV,
    _SC_IOV_MAX = _SC_UIO_MAXIOV,
    _SC_PII_INTERNET_STREAM,
    _SC_PII_INTERNET_DGRAM,
    _SC_PII_OSI_COTS,
    _SC_PII_OSI_CLTS,
    _SC_PII_OSI_M,
    _SC_T_IOV_MAX,
    _SC_THREADS,
    _SC_THREAD_SAFE_FUNCTIONS,
    _SC_GETGR_R_SIZE_MAX,
    _SC_GETPW_R_SIZE_MAX,
    _SC_LOGIN_NAME_MAX,
    _SC_TTY_NAME_MAX,
    _SC_THREAD_DESTRUCTOR_ITERATIONS,
    _SC_THREAD_KEYS_MAX,
    _SC_THREAD_STACK_MIN,
    _SC_THREAD_THREADS_MAX,
    _SC_THREAD_ATTR_STACKADDR,
    _SC_THREAD_ATTR_STACKSIZE,
    _SC_THREAD_PRIORITY_SCHEDULING,
    _SC_THREAD_PRIO_INHERIT,
    _SC_THREAD_PRIO_PROTECT,
    _SC_THREAD_PROCESS_SHARED,
    _SC_NPROCESSORS_CONF,
    _SC_NPROCESSORS_ONLN,
    _SC_PHYS_PAGES,
    _SC_AVPHYS_PAGES,
    _SC_ATEXIT_MAX,
    _SC_PASS_MAX,
    _SC_XOPEN_VERSION,
    _SC_XOPEN_XCU_VERSION,
    _SC_XOPEN_UNIX,
    _SC_XOPEN_CRYPT,
    _SC_XOPEN_ENH_I18N,
    _SC_XOPEN_SHM,
    _SC_2_CHAR_TERM,
    _SC_2_C_VERSION,
    _SC_2_UPE,
    _SC_XOPEN_XPG2,
    _SC_XOPEN_XPG3,
    _SC_XOPEN_XPG4,
    _SC_CHAR_BIT,
    _SC_CHAR_MAX,
    _SC_CHAR_MIN,
    _SC_INT_MAX,
    _SC_INT_MIN,
    _SC_LONG_BIT,
    _SC_WORD_BIT,
    _SC_MB_LEN_MAX,
    _SC_NZERO,
    _SC_SSIZE_MAX,
    _SC_SCHAR_MAX,
    _SC_SCHAR_MIN,
    _SC_SHRT_MAX,
    _SC_SHRT_MIN,
    _SC_UCHAR_MAX,
    _SC_UINT_MAX,
    _SC_ULONG_MAX,
    _SC_USHRT_MAX,
    _SC_NL_ARGMAX,
    _SC_NL_LANGMAX,
    _SC_NL_MSGMAX,
    _SC_NL_NMAX,
    _SC_NL_SETMAX,
    _SC_NL_TEXTMAX,
    _SC_XBS5_ILP32_OFF32,
    _SC_XBS5_ILP32_OFFBIG,
    _SC_XBS5_LP64_OFF64,
    _SC_XBS5_LPBIG_OFFBIG,
    _SC_XOPEN_LEGACY,
    _SC_XOPEN_REALTIME,
    _SC_XOPEN_REALTIME_THREADS,
    _SC_ADVISORY_INFO,
    _SC_BARRIERS,
    _SC_BASE,
    _SC_C_LANG_SUPPORT,
    _SC_C_LANG_SUPPORT_R,
    _SC_CLOCK_SELECTION,
    _SC_CPUTIME,
    _SC_THREAD_CPUTIME,
    _SC_DEVICE_IO,
    _SC_DEVICE_SPECIFIC,
    _SC_DEVICE_SPECIFIC_R,
    _SC_FD_MGMT,
    _SC_FIFO,
    _SC_PIPE,
    _SC_FILE_ATTRIBUTES,
    _SC_FILE_LOCKING,
    _SC_FILE_SYSTEM,
    _SC_MONOTONIC_CLOCK,
    _SC_MULTI_PROCESS,
    _SC_SINGLE_PROCESS,
    _SC_NETWORKING,
    _SC_READER_WRITER_LOCKS,
    _SC_SPIN_LOCKS,
    _SC_REGEXP,
    _SC_REGEX_VERSION,
    _SC_SHELL,
    _SC_SIGNALS,
    _SC_SPAWN,
    _SC_SPORADIC_SERVER,
    _SC_THREAD_SPORADIC_SERVER,
    _SC_SYSTEM_DATABASE,
    _SC_SYSTEM_DATABASE_R,
    _SC_TIMEOUTS,
    _SC_TYPED_MEMORY_OBJECTS,
    _SC_USER_GROUPS,
    _SC_USER_GROUPS_R,
    _SC_2_PBS,
    _SC_2_PBS_ACCOUNTING,
    _SC_2_PBS_LOCATE,
    _SC_2_PBS_MESSAGE,
    _SC_2_PBS_TRACK,
    _SC_SYMLOOP_MAX,
    _SC_STREAMS,
    _SC_2_PBS_CHECKPOINT,
    _SC_V6_ILP32_OFF32,
    _SC_V6_ILP32_OFFBIG,
    _SC_V6_LP64_OFF64,
    _SC_V6_LPBIG_OFFBIG,
    _SC_HOST_NAME_MAX,
    _SC_TRACE,
    _SC_TRACE_EVENT_FILTER,
    _SC_TRACE_INHERIT,
    _SC_TRACE_LOG,
    _SC_LEVEL1_ICACHE_SIZE,
    _SC_LEVEL1_ICACHE_ASSOC,
    _SC_LEVEL1_ICACHE_LINESIZE,
    _SC_LEVEL1_DCACHE_SIZE,
    _SC_LEVEL1_DCACHE_ASSOC,
    _SC_LEVEL1_DCACHE_LINESIZE,
    _SC_LEVEL2_CACHE_SIZE,
    _SC_LEVEL2_CACHE_ASSOC,
    _SC_LEVEL2_CACHE_LINESIZE,
    _SC_LEVEL3_CACHE_SIZE,
    _SC_LEVEL3_CACHE_ASSOC,
    _SC_LEVEL3_CACHE_LINESIZE,
    _SC_LEVEL4_CACHE_SIZE,
    _SC_LEVEL4_CACHE_ASSOC,
    _SC_LEVEL4_CACHE_LINESIZE,
    _SC_IPV6 = _SC_LEVEL1_ICACHE_SIZE + 50,
    _SC_RAW_SOCKETS,
    _SC_V7_ILP32_OFF32,
    _SC_V7_ILP32_OFFBIG,
    _SC_V7_LP64_OFF64,
    _SC_V7_LPBIG_OFFBIG,
    _SC_SS_REPL_MAX,
    _SC_TRACE_EVENT_NAME_MAX,
    _SC_TRACE_NAME_MAX,
    _SC_TRACE_SYS_MAX,
    _SC_TRACE_USER_EVENT_MAX,
    _SC_XOPEN_STREAMS,
    _SC_THREAD_ROBUST_PRIO_INHERIT,
    _SC_THREAD_ROBUST_PRIO_PROTECT
};
enum {
    _CS_PATH,
    _CS_V6_WIDTH_RESTRICTED_ENVS,
    _CS_GNU_LIBC_VERSION,
    _CS_GNU_LIBPTHREAD_VERSION,
    _CS_V5_WIDTH_RESTRICTED_ENVS,
    _CS_V7_WIDTH_RESTRICTED_ENVS,
    _CS_LFS_CFLAGS = 1000,
    _CS_LFS_LDFLAGS,
    _CS_LFS_LIBS,
    _CS_LFS_LINTFLAGS,
    _CS_LFS64_CFLAGS,
    _CS_LFS64_LDFLAGS,
    _CS_LFS64_LIBS,
    _CS_LFS64_LINTFLAGS,
    _CS_XBS5_ILP32_OFF32_CFLAGS = 1100,
    _CS_XBS5_ILP32_OFF32_LDFLAGS,
    _CS_XBS5_ILP32_OFF32_LIBS,
    _CS_XBS5_ILP32_OFF32_LINTFLAGS,
    _CS_XBS5_ILP32_OFFBIG_CFLAGS,
    _CS_XBS5_ILP32_OFFBIG_LDFLAGS,
    _CS_XBS5_ILP32_OFFBIG_LIBS,
    _CS_XBS5_ILP32_OFFBIG_LINTFLAGS,
    _CS_XBS5_LP64_OFF64_CFLAGS,
    _CS_XBS5_LP64_OFF64_LDFLAGS,
    _CS_XBS5_LP64_OFF64_LIBS,
    _CS_XBS5_LP64_OFF64_LINTFLAGS,
    _CS_XBS5_LPBIG_OFFBIG_CFLAGS,
    _CS_XBS5_LPBIG_OFFBIG_LDFLAGS,
    _CS_XBS5_LPBIG_OFFBIG_LIBS,
    _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS,
    _CS_POSIX_V6_ILP32_OFF32_CFLAGS,
    _CS_POSIX_V6_ILP32_OFF32_LDFLAGS,
    _CS_POSIX_V6_ILP32_OFF32_LIBS,
    _CS_POSIX_V6_ILP32_OFF32_LINTFLAGS,
    _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS,
    _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS,
    _CS_POSIX_V6_ILP32_OFFBIG_LIBS,
    _CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS,
    _CS_POSIX_V6_LP64_OFF64_CFLAGS,
    _CS_POSIX_V6_LP64_OFF64_LDFLAGS,
    _CS_POSIX_V6_LP64_OFF64_LIBS,
    _CS_POSIX_V6_LP64_OFF64_LINTFLAGS,
    _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS,
    _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS,
    _CS_POSIX_V6_LPBIG_OFFBIG_LIBS,
    _CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS,
    _CS_POSIX_V7_ILP32_OFF32_CFLAGS,
    _CS_POSIX_V7_ILP32_OFF32_LDFLAGS,
    _CS_POSIX_V7_ILP32_OFF32_LIBS,
    _CS_POSIX_V7_ILP32_OFF32_LINTFLAGS,
    _CS_POSIX_V7_ILP32_OFFBIG_CFLAGS,
    _CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS,
    _CS_POSIX_V7_ILP32_OFFBIG_LIBS,
    _CS_POSIX_V7_ILP32_OFFBIG_LINTFLAGS,
    _CS_POSIX_V7_LP64_OFF64_CFLAGS,
    _CS_POSIX_V7_LP64_OFF64_LDFLAGS,
    _CS_POSIX_V7_LP64_OFF64_LIBS,
    _CS_POSIX_V7_LP64_OFF64_LINTFLAGS,
    _CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS,
    _CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS,
    _CS_POSIX_V7_LPBIG_OFFBIG_LIBS,
    _CS_POSIX_V7_LPBIG_OFFBIG_LINTFLAGS,
    _CS_V6_ENV,
    _CS_V7_ENV
};
extern long int pathconf(const char * __path,
                         int __name) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern long int fpathconf(int __fd,
                          int __name) __attribute__((__nothrow__,__leaf__));
extern long int sysconf(int __name) __attribute__((__nothrow__,__leaf__));
extern size_t confstr(int __name,
                      char * __buf,
                      size_t __len) __attribute__((__nothrow__,__leaf__));
extern __pid_t getpid(void) __attribute__((__nothrow__,__leaf__));
extern __pid_t getppid(void) __attribute__((__nothrow__,__leaf__));
extern __pid_t getpgrp(void) __attribute__((__nothrow__,__leaf__));
extern __pid_t __getpgid(__pid_t __pid) __attribute__((__nothrow__,__leaf__));
extern __pid_t getpgid(__pid_t __pid) __attribute__((__nothrow__,__leaf__));
extern int setpgid(__pid_t __pid,
                   __pid_t __pgid) __attribute__((__nothrow__,__leaf__));
extern int setpgrp(void) __attribute__((__nothrow__,__leaf__));
extern __pid_t setsid(void) __attribute__((__nothrow__,__leaf__));
extern __pid_t getsid(__pid_t __pid) __attribute__((__nothrow__,__leaf__));
extern __uid_t getuid(void) __attribute__((__nothrow__,__leaf__));
extern __uid_t geteuid(void) __attribute__((__nothrow__,__leaf__));
extern __gid_t getgid(void) __attribute__((__nothrow__,__leaf__));
extern __gid_t getegid(void) __attribute__((__nothrow__,__leaf__));
extern int getgroups(int __size,
                     __gid_t __list[]) __attribute__((__nothrow__,__leaf__));
extern int group_member(__gid_t __gid) __attribute__((__nothrow__,__leaf__));
extern int setuid(__uid_t __uid) __attribute__((__nothrow__,__leaf__));
extern int setreuid(__uid_t __ruid,
                    __uid_t __euid) __attribute__((__nothrow__,__leaf__));
extern int seteuid(__uid_t __uid) __attribute__((__nothrow__,__leaf__));
extern int setgid(__gid_t __gid) __attribute__((__nothrow__,__leaf__));
extern int setregid(__gid_t __rgid,
                    __gid_t __egid) __attribute__((__nothrow__,__leaf__));
extern int setegid(__gid_t __gid) __attribute__((__nothrow__,__leaf__));
extern int getresuid(__uid_t * __ruid,
                     __uid_t * __euid,
                     __uid_t * __suid) __attribute__((__nothrow__,__leaf__));
extern int getresgid(__gid_t * __rgid,
                     __gid_t * __egid,
                     __gid_t * __sgid) __attribute__((__nothrow__,__leaf__));
extern int setresuid(__uid_t __ruid,
                     __uid_t __euid,
                     __uid_t __suid) __attribute__((__nothrow__,__leaf__));
extern int setresgid(__gid_t __rgid,
                     __gid_t __egid,
                     __gid_t __sgid) __attribute__((__nothrow__,__leaf__));
extern __pid_t fork(void) __attribute__((__nothrow__));
extern __pid_t vfork(void) __attribute__((__nothrow__,__leaf__));
extern char * ttyname(int __fd) __attribute__((__nothrow__,__leaf__));
extern int ttyname_r(int __fd,
                     char * __buf,
                     size_t __buflen) __attribute__((__nothrow__,__leaf__,__nonnull__(2)));
extern int isatty(int __fd) __attribute__((__nothrow__,__leaf__));
extern int ttyslot(void) __attribute__((__nothrow__,__leaf__));
extern int link(const char * __from,
                const char * __to) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern int linkat(int __fromfd,
                  const char * __from,
                  int __tofd,
                  const char * __to,
                  int __flags) __attribute__((__nothrow__,__leaf__,__nonnull__(2, 4)));
extern int symlink(const char * __from,
                   const char * __to) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern ssize_t readlink(const char * __restrict __path,
                        char * __restrict __buf,
                        size_t __len) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern int symlinkat(const char * __from,
                     int __tofd,
                     const char * __to) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 3)));
extern ssize_t readlinkat(int __fd,
                          const char * __restrict __path,
                          char * __restrict __buf,
                          size_t __len) __attribute__((__nothrow__,__leaf__,__nonnull__(2, 3)));
extern int unlink(const char * __name) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int unlinkat(int __fd,
                    const char * __name,
                    int __flag) __attribute__((__nothrow__,__leaf__,__nonnull__(2)));
extern int rmdir(const char * __path) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern __pid_t tcgetpgrp(int __fd) __attribute__((__nothrow__,__leaf__));
extern int tcsetpgrp(int __fd,
                     __pid_t __pgrp_id) __attribute__((__nothrow__,__leaf__));
extern char * getlogin(void);
extern int getlogin_r(char * __name,
                      size_t __name_len) __attribute__((__nonnull__(1)));
extern int setlogin(const char * __name) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern char * optarg;
extern int optind;
extern int opterr;
extern int optopt;
extern int getopt(int ___argc,
                  char * const * ___argv,
                  const char * __shortopts) __attribute__((__nothrow__,__leaf__));
extern int gethostname(char * __name,
                       size_t __len) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int sethostname(const char * __name,
                       size_t __len) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int sethostid(long int __id) __attribute__((__nothrow__,__leaf__));
extern int getdomainname(char * __name,
                         size_t __len) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int setdomainname(const char * __name,
                         size_t __len) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int vhangup(void) __attribute__((__nothrow__,__leaf__));
extern int revoke(const char * __file) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int profil(unsigned short int * __sample_buffer,
                  size_t __size,
                  size_t __offset,
                  unsigned int __scale) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int acct(const char * __name) __attribute__((__nothrow__,__leaf__));
extern char * getusershell(void) __attribute__((__nothrow__,__leaf__));
extern void endusershell(void) __attribute__((__nothrow__,__leaf__));
extern void setusershell(void) __attribute__((__nothrow__,__leaf__));
extern int daemon(int __nochdir,
                  int __noclose) __attribute__((__nothrow__,__leaf__));
extern int chroot(const char * __path) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern char * getpass(const char * __prompt) __attribute__((__nonnull__(1)));
extern int fsync(int __fd);
extern int syncfs(int __fd) __attribute__((__nothrow__,__leaf__));
extern long int gethostid(void);
extern void sync(void) __attribute__((__nothrow__,__leaf__));
extern int getpagesize(void) __attribute__((__nothrow__,__leaf__,const));
extern int getdtablesize(void) __attribute__((__nothrow__,__leaf__));
extern int truncate(const char * __file,
                    __off_t __length) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int truncate64(const char * __file,
                      __off64_t __length) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int ftruncate(int __fd,
                     __off_t __length) __attribute__((__nothrow__,__leaf__));
extern int ftruncate64(int __fd,
                       __off64_t __length) __attribute__((__nothrow__,__leaf__));
extern int brk(void * __addr) __attribute__((__nothrow__,__leaf__));
extern void * sbrk(intptr_t __delta) __attribute__((__nothrow__,__leaf__));
extern long int syscall(long int __sysno, ...) __attribute__((__nothrow__,__leaf__));
extern int lockf(int __fd, int __cmd, __off_t __len);
extern int lockf64(int __fd, int __cmd, __off64_t __len);
extern int fdatasync(int __fildes);
extern char * crypt(const char * __key,
                    const char * __salt) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern void encrypt(char * __glibc_block,
                    int __edflag) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern void swab(const void * __restrict __from,
                 void * __restrict __to,
                 ssize_t __n) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
struct stat {
    __dev_t st_dev;
    __ino_t st_ino;
    __nlink_t st_nlink;
    __mode_t st_mode;
    __uid_t st_uid;
    __gid_t st_gid;
    int __pad0;
    __dev_t st_rdev;
    __off_t st_size;
    __blksize_t st_blksize;
    __blkcnt_t st_blocks;
    struct timespec st_atim;
    struct timespec st_mtim;
    struct timespec st_ctim;
    __syscall_slong_t __glibc_reserved[3];
};
struct stat64 {
    __dev_t st_dev;
    __ino64_t st_ino;
    __nlink_t st_nlink;
    __mode_t st_mode;
    __uid_t st_uid;
    __gid_t st_gid;
    int __pad0;
    __dev_t st_rdev;
    __off_t st_size;
    __blksize_t st_blksize;
    __blkcnt64_t st_blocks;
    struct timespec st_atim;
    struct timespec st_mtim;
    struct timespec st_ctim;
    __syscall_slong_t __glibc_reserved[3];
};
extern int stat(const char * __restrict __file,
                struct stat * __restrict __buf) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern int fstat(int __fd,
                 struct stat * __buf) __attribute__((__nothrow__,__leaf__,__nonnull__(2)));
extern int stat64(const char * __restrict __file,
                  struct stat64 * __restrict __buf) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern int fstat64(int __fd,
                   struct stat64 * __buf) __attribute__((__nothrow__,__leaf__,__nonnull__(2)));
extern int fstatat(int __fd,
                   const char * __restrict __file,
                   struct stat * __restrict __buf,
                   int __flag) __attribute__((__nothrow__,__leaf__,__nonnull__(2, 3)));
extern int fstatat64(int __fd,
                     const char * __restrict __file,
                     struct stat64 * __restrict __buf,
                     int __flag) __attribute__((__nothrow__,__leaf__,__nonnull__(2, 3)));
extern int lstat(const char * __restrict __file,
                 struct stat * __restrict __buf) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern int lstat64(const char * __restrict __file,
                   struct stat64 * __restrict __buf) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2)));
extern int chmod(const char * __file,
                 __mode_t __mode) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int lchmod(const char * __file,
                  __mode_t __mode) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int fchmod(int __fd,
                  __mode_t __mode) __attribute__((__nothrow__,__leaf__));
extern int fchmodat(int __fd,
                    const char * __file,
                    __mode_t __mode,
                    int __flag) __attribute__((__nothrow__,__leaf__,__nonnull__(2)));
extern __mode_t umask(__mode_t __mask) __attribute__((__nothrow__,__leaf__));
extern __mode_t getumask(void) __attribute__((__nothrow__,__leaf__));
extern int mkdir(const char * __path,
                 __mode_t __mode) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int mkdirat(int __fd,
                   const char * __path,
                   __mode_t __mode) __attribute__((__nothrow__,__leaf__,__nonnull__(2)));
extern int mknod(const char * __path,
                 __mode_t __mode,
                 __dev_t __dev) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int mknodat(int __fd,
                   const char * __path,
                   __mode_t __mode,
                   __dev_t __dev) __attribute__((__nothrow__,__leaf__,__nonnull__(2)));
extern int mkfifo(const char * __path,
                  __mode_t __mode) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int mkfifoat(int __fd,
                    const char * __path,
                    __mode_t __mode) __attribute__((__nothrow__,__leaf__,__nonnull__(2)));
extern int utimensat(int __fd,
                     const char * __path,
                     const struct timespec __times[2],
                     int __flags) __attribute__((__nothrow__,__leaf__,__nonnull__(2)));
extern int futimens(int __fd,
                    const struct timespec __times[2]) __attribute__((__nothrow__,__leaf__));
extern int __fxstat(int __ver,
                    int __fildes,
                    struct stat * __stat_buf) __attribute__((__nothrow__,__leaf__,__nonnull__(3)));
extern int __xstat(int __ver,
                   const char * __filename,
                   struct stat * __stat_buf) __attribute__((__nothrow__,__leaf__,__nonnull__(2, 3)));
extern int __lxstat(int __ver,
                    const char * __filename,
                    struct stat * __stat_buf) __attribute__((__nothrow__,__leaf__,__nonnull__(2, 3)));
extern int __fxstatat(int __ver,
                      int __fildes,
                      const char * __filename,
                      struct stat * __stat_buf,
                      int __flag) __attribute__((__nothrow__,__leaf__,__nonnull__(3, 4)));
extern int __fxstat64(int __ver,
                      int __fildes,
                      struct stat64 * __stat_buf) __attribute__((__nothrow__,__leaf__,__nonnull__(3)));
extern int __xstat64(int __ver,
                     const char * __filename,
                     struct stat64 * __stat_buf) __attribute__((__nothrow__,__leaf__,__nonnull__(2, 3)));
extern int __lxstat64(int __ver,
                      const char * __filename,
                      struct stat64 * __stat_buf) __attribute__((__nothrow__,__leaf__,__nonnull__(2, 3)));
extern int __fxstatat64(int __ver,
                        int __fildes,
                        const char * __filename,
                        struct stat64 * __stat_buf,
                        int __flag) __attribute__((__nothrow__,__leaf__,__nonnull__(3, 4)));
extern int __xmknod(int __ver,
                    const char * __path,
                    __mode_t __mode,
                    __dev_t * __dev) __attribute__((__nothrow__,__leaf__,__nonnull__(2, 4)));
extern int __xmknodat(int __ver,
                      int __fd,
                      const char * __path,
                      __mode_t __mode,
                      __dev_t * __dev) __attribute__((__nothrow__,__leaf__,__nonnull__(3, 5)));
struct flock {
    short int l_type;
    short int l_whence;
    __off_t l_start;
    __off_t l_len;
    __pid_t l_pid;
};
struct flock64 {
    short int l_type;
    short int l_whence;
    __off64_t l_start;
    __off64_t l_len;
    __pid_t l_pid;
};
struct iovec {
    void * iov_base; size_t iov_len;
};
enum __pid_type {
    F_OWNER_TID = 0,
    F_OWNER_PID,
    F_OWNER_PGRP,
    F_OWNER_GID = F_OWNER_PGRP
};
struct f_owner_ex {
    enum __pid_type type; __pid_t pid;
};
struct file_handle {
    unsigned int handle_bytes;
    int handle_type;
    unsigned char f_handle[0];
};
extern ssize_t readahead(int __fd,
                         __off64_t __offset,
                         size_t __count) __attribute__((__nothrow__,__leaf__));
extern int sync_file_range(int __fd,
                           __off64_t __offset,
                           __off64_t __count,
                           unsigned int __flags);
extern ssize_t vmsplice(int __fdout,
                        const struct iovec * __iov,
                        size_t __count,
                        unsigned int __flags);
extern ssize_t splice(int __fdin,
                      __off64_t * __offin,
                      int __fdout,
                      __off64_t * __offout,
                      size_t __len,
                      unsigned int __flags);
extern ssize_t tee(int __fdin,
                   int __fdout,
                   size_t __len,
                   unsigned int __flags);
extern int fallocate(int __fd,
                     int __mode,
                     __off_t __offset,
                     __off_t __len);
extern int fallocate64(int __fd,
                       int __mode,
                       __off64_t __offset,
                       __off64_t __len);
extern int name_to_handle_at(int __dfd,
                             const char * __name,
                             struct file_handle * __handle,
                             int * __mnt_id,
                             int __flags) __attribute__((__nothrow__,__leaf__));
extern int open_by_handle_at(int __mountdirfd,
                             struct file_handle * __handle,
                             int __flags);
extern int fcntl(int __fd, int __cmd, ...);
extern int open(const char * __file,
                int __oflag, ...) __attribute__((__nonnull__(1)));
extern int open64(const char * __file,
                  int __oflag, ...) __attribute__((__nonnull__(1)));
extern int openat(int __fd,
                  const char * __file,
                  int __oflag, ...) __attribute__((__nonnull__(2)));
extern int openat64(int __fd,
                    const char * __file,
                    int __oflag, ...) __attribute__((__nonnull__(2)));
extern int creat(const char * __file,
                 mode_t __mode) __attribute__((__nonnull__(1)));
extern int creat64(const char * __file,
                   mode_t __mode) __attribute__((__nonnull__(1)));
extern int posix_fadvise(int __fd,
                         off_t __offset,
                         off_t __len,
                         int __advise) __attribute__((__nothrow__,__leaf__));
extern int posix_fadvise64(int __fd,
                           off64_t __offset,
                           off64_t __len,
                           int __advise) __attribute__((__nothrow__,__leaf__));
extern int posix_fallocate(int __fd, off_t __offset, off_t __len);
extern int posix_fallocate64(int __fd,
                             off64_t __offset,
                             off64_t __len);
enum {
    _ISupper = 0 < 8 ? 1 << 0 << 8 : 1 << 0 >> 8,
    _ISlower = 1 < 8 ? 1 << 1 << 8 : 1 << 1 >> 8,
    _ISalpha = 2 < 8 ? 1 << 2 << 8 : 1 << 2 >> 8,
    _ISdigit = 3 < 8 ? 1 << 3 << 8 : 1 << 3 >> 8,
    _ISxdigit = 4 < 8 ? 1 << 4 << 8 : 1 << 4 >> 8,
    _ISspace = 5 < 8 ? 1 << 5 << 8 : 1 << 5 >> 8,
    _ISprint = 6 < 8 ? 1 << 6 << 8 : 1 << 6 >> 8,
    _ISgraph = 7 < 8 ? 1 << 7 << 8 : 1 << 7 >> 8,
    _ISblank = 8 < 8 ? 1 << 8 << 8 : 1 << 8 >> 8,
    _IScntrl = 9 < 8 ? 1 << 9 << 8 : 1 << 9 >> 8,
    _ISpunct = 10 < 8 ? 1 << 10 << 8 : 1 << 10 >> 8,
    _ISalnum = 11 < 8 ? 1 << 11 << 8 : 1 << 11 >> 8
};
extern const unsigned short int * * __ctype_b_loc(void) __attribute__((__nothrow__,__leaf__,const));
extern const __int32_t * * __ctype_tolower_loc(void) __attribute__((__nothrow__,__leaf__,const));
extern const __int32_t * * __ctype_toupper_loc(void) __attribute__((__nothrow__,__leaf__,const));
extern int isalnum(int) __attribute__((__nothrow__,__leaf__));
extern int isalpha(int) __attribute__((__nothrow__,__leaf__));
extern int iscntrl(int) __attribute__((__nothrow__,__leaf__));
extern int isdigit(int) __attribute__((__nothrow__,__leaf__));
extern int islower(int) __attribute__((__nothrow__,__leaf__));
extern int isgraph(int) __attribute__((__nothrow__,__leaf__));
extern int isprint(int) __attribute__((__nothrow__,__leaf__));
extern int ispunct(int) __attribute__((__nothrow__,__leaf__));
extern int isspace(int) __attribute__((__nothrow__,__leaf__));
extern int isupper(int) __attribute__((__nothrow__,__leaf__));
extern int isxdigit(int) __attribute__((__nothrow__,__leaf__));
extern int tolower(int __c) __attribute__((__nothrow__,__leaf__));
extern int toupper(int __c) __attribute__((__nothrow__,__leaf__));
extern int isblank(int) __attribute__((__nothrow__,__leaf__));
extern int isctype(int __c,
                   int __mask) __attribute__((__nothrow__,__leaf__));
extern int isascii(int __c) __attribute__((__nothrow__,__leaf__));
extern int toascii(int __c) __attribute__((__nothrow__,__leaf__));
extern int _toupper(int) __attribute__((__nothrow__,__leaf__));
extern int _tolower(int) __attribute__((__nothrow__,__leaf__));
extern int isalnum_l(int,
                     __locale_t) __attribute__((__nothrow__,__leaf__));
extern int isalpha_l(int,
                     __locale_t) __attribute__((__nothrow__,__leaf__));
extern int iscntrl_l(int,
                     __locale_t) __attribute__((__nothrow__,__leaf__));
extern int isdigit_l(int,
                     __locale_t) __attribute__((__nothrow__,__leaf__));
extern int islower_l(int,
                     __locale_t) __attribute__((__nothrow__,__leaf__));
extern int isgraph_l(int,
                     __locale_t) __attribute__((__nothrow__,__leaf__));
extern int isprint_l(int,
                     __locale_t) __attribute__((__nothrow__,__leaf__));
extern int ispunct_l(int,
                     __locale_t) __attribute__((__nothrow__,__leaf__));
extern int isspace_l(int,
                     __locale_t) __attribute__((__nothrow__,__leaf__));
extern int isupper_l(int,
                     __locale_t) __attribute__((__nothrow__,__leaf__));
extern int isxdigit_l(int,
                      __locale_t) __attribute__((__nothrow__,__leaf__));
extern int isblank_l(int,
                     __locale_t) __attribute__((__nothrow__,__leaf__));
extern int __tolower_l(int __c,
                       __locale_t __l) __attribute__((__nothrow__,__leaf__));
extern int tolower_l(int __c,
                     __locale_t __l) __attribute__((__nothrow__,__leaf__));
extern int __toupper_l(int __c,
                       __locale_t __l) __attribute__((__nothrow__,__leaf__));
extern int toupper_l(int __c,
                     __locale_t __l) __attribute__((__nothrow__,__leaf__));
struct lconv {
    char * decimal_point;
    char * thousands_sep;
    char * grouping;
    char * int_curr_symbol;
    char * currency_symbol;
    char * mon_decimal_point;
    char * mon_thousands_sep;
    char * mon_grouping;
    char * positive_sign;
    char * negative_sign;
    char int_frac_digits;
    char frac_digits;
    char p_cs_precedes;
    char p_sep_by_space;
    char n_cs_precedes;
    char n_sep_by_space;
    char p_sign_posn;
    char n_sign_posn;
    char int_p_cs_precedes;
    char int_p_sep_by_space;
    char int_n_cs_precedes;
    char int_n_sep_by_space;
    char int_p_sign_posn;
    char int_n_sign_posn;
};
extern char * setlocale(int __category,
                        const char * __locale) __attribute__((__nothrow__,__leaf__));
extern struct lconv * localeconv(void) __attribute__((__nothrow__,__leaf__));
extern __locale_t newlocale(int __category_mask,
                            const char * __locale,
                            __locale_t __base) __attribute__((__nothrow__,__leaf__));
extern __locale_t duplocale(__locale_t __dataset) __attribute__((__nothrow__,__leaf__));
extern void freelocale(__locale_t __dataset) __attribute__((__nothrow__,__leaf__));
extern __locale_t uselocale(__locale_t __dataset) __attribute__((__nothrow__,__leaf__));
struct real_pcre;
typedef struct real_pcre pcre;
struct real_pcre16;
typedef struct real_pcre16 pcre16;
struct real_pcre32;
typedef struct real_pcre32 pcre32;
struct real_pcre_jit_stack;
typedef struct real_pcre_jit_stack pcre_jit_stack;
struct real_pcre16_jit_stack;
typedef struct real_pcre16_jit_stack pcre16_jit_stack;
struct real_pcre32_jit_stack;
typedef struct real_pcre32_jit_stack pcre32_jit_stack;
typedef struct pcre_extra {
            unsigned long int flags;
            void * study_data;
            unsigned long int match_limit;
            void * callout_data;
            const unsigned char * tables;
            unsigned long int match_limit_recursion;
            unsigned char * * mark;
            void * executable_jit;
        } pcre_extra;
typedef struct pcre16_extra {
            unsigned long int flags;
            void * study_data;
            unsigned long int match_limit;
            void * callout_data;
            const unsigned char * tables;
            unsigned long int match_limit_recursion;
            unsigned short * * mark;
            void * executable_jit;
        } pcre16_extra;
typedef struct pcre32_extra {
            unsigned long int flags;
            void * study_data;
            unsigned long int match_limit;
            void * callout_data;
            const unsigned char * tables;
            unsigned long int match_limit_recursion;
            unsigned int * * mark;
            void * executable_jit;
        } pcre32_extra;
typedef struct pcre_callout_block {
            int version;
            int callout_number;
            int * offset_vector;
            const char * subject;
            int subject_length;
            int start_match;
            int current_position;
            int capture_top;
            int capture_last;
            void * callout_data;
            int pattern_position;
            int next_item_length;
            const unsigned char * mark;
        } pcre_callout_block;
typedef struct pcre16_callout_block {
            int version;
            int callout_number;
            int * offset_vector;
            const unsigned short * subject;
            int subject_length;
            int start_match;
            int current_position;
            int capture_top;
            int capture_last;
            void * callout_data;
            int pattern_position;
            int next_item_length;
            const unsigned short * mark;
        } pcre16_callout_block;
typedef struct pcre32_callout_block {
            int version;
            int callout_number;
            int * offset_vector;
            const unsigned int * subject;
            int subject_length;
            int start_match;
            int current_position;
            int capture_top;
            int capture_last;
            void * callout_data;
            int pattern_position;
            int next_item_length;
            const unsigned int * mark;
        } pcre32_callout_block;
extern void * (* pcre_malloc)(size_t);
extern void (* pcre_free)(void *);
extern void * (* pcre_stack_malloc)(size_t);
extern void (* pcre_stack_free)(void *);
extern int (* pcre_callout)(pcre_callout_block *);
extern int (* pcre_stack_guard)(void);
extern void * (* pcre16_malloc)(size_t);
extern void (* pcre16_free)(void *);
extern void * (* pcre16_stack_malloc)(size_t);
extern void (* pcre16_stack_free)(void *);
extern int (* pcre16_callout)(pcre16_callout_block *);
extern int (* pcre16_stack_guard)(void);
extern void * (* pcre32_malloc)(size_t);
extern void (* pcre32_free)(void *);
extern void * (* pcre32_stack_malloc)(size_t);
extern void (* pcre32_stack_free)(void *);
extern int (* pcre32_callout)(pcre32_callout_block *);
extern int (* pcre32_stack_guard)(void);
typedef pcre_jit_stack * (* pcre_jit_callback)(void *);
typedef pcre16_jit_stack * (* pcre16_jit_callback)(void *);
typedef pcre32_jit_stack * (* pcre32_jit_callback)(void *);
extern pcre * pcre_compile(const char *,
                           int,
                           const char * *,
                           int *,
                           const unsigned char *);
extern pcre16 * pcre16_compile(const unsigned short *,
                               int,
                               const char * *,
                               int *,
                               const unsigned char *);
extern pcre32 * pcre32_compile(const unsigned int *,
                               int,
                               const char * *,
                               int *,
                               const unsigned char *);
extern pcre * pcre_compile2(const char *,
                            int,
                            int *,
                            const char * *,
                            int *,
                            const unsigned char *);
extern pcre16 * pcre16_compile2(const unsigned short *,
                                int,
                                int *,
                                const char * *,
                                int *,
                                const unsigned char *);
extern pcre32 * pcre32_compile2(const unsigned int *,
                                int,
                                int *,
                                const char * *,
                                int *,
                                const unsigned char *);
extern int pcre_config(int, void *);
extern int pcre16_config(int, void *);
extern int pcre32_config(int, void *);
extern int pcre_copy_named_substring(const pcre *,
                                     const char *,
                                     int *,
                                     int,
                                     const char *,
                                     char *,
                                     int);
extern int pcre16_copy_named_substring(const pcre16 *,
                                       const unsigned short *,
                                       int *,
                                       int,
                                       const unsigned short *,
                                       unsigned short *,
                                       int);
extern int pcre32_copy_named_substring(const pcre32 *,
                                       const unsigned int *,
                                       int *,
                                       int,
                                       const unsigned int *,
                                       unsigned int *,
                                       int);
extern int pcre_copy_substring(const char *,
                               int *,
                               int,
                               int,
                               char *,
                               int);
extern int pcre16_copy_substring(const unsigned short *,
                                 int *,
                                 int,
                                 int,
                                 unsigned short *,
                                 int);
extern int pcre32_copy_substring(const unsigned int *,
                                 int *,
                                 int,
                                 int,
                                 unsigned int *,
                                 int);
extern int pcre_dfa_exec(const pcre *,
                         const pcre_extra *,
                         const char *,
                         int,
                         int,
                         int,
                         int *,
                         int,
                         int *,
                         int);
extern int pcre16_dfa_exec(const pcre16 *,
                           const pcre16_extra *,
                           const unsigned short *,
                           int,
                           int,
                           int,
                           int *,
                           int,
                           int *,
                           int);
extern int pcre32_dfa_exec(const pcre32 *,
                           const pcre32_extra *,
                           const unsigned int *,
                           int,
                           int,
                           int,
                           int *,
                           int,
                           int *,
                           int);
extern int pcre_exec(const pcre *,
                     const pcre_extra *,
                     const char *,
                     int,
                     int,
                     int,
                     int *,
                     int);
extern int pcre16_exec(const pcre16 *,
                       const pcre16_extra *,
                       const unsigned short *,
                       int,
                       int,
                       int,
                       int *,
                       int);
extern int pcre32_exec(const pcre32 *,
                       const pcre32_extra *,
                       const unsigned int *,
                       int,
                       int,
                       int,
                       int *,
                       int);
extern int pcre_jit_exec(const pcre *,
                         const pcre_extra *,
                         const char *,
                         int,
                         int,
                         int,
                         int *,
                         int,
                         pcre_jit_stack *);
extern int pcre16_jit_exec(const pcre16 *,
                           const pcre16_extra *,
                           const unsigned short *,
                           int,
                           int,
                           int,
                           int *,
                           int,
                           pcre16_jit_stack *);
extern int pcre32_jit_exec(const pcre32 *,
                           const pcre32_extra *,
                           const unsigned int *,
                           int,
                           int,
                           int,
                           int *,
                           int,
                           pcre32_jit_stack *);
extern void pcre_free_substring(const char *);
extern void pcre16_free_substring(const unsigned short *);
extern void pcre32_free_substring(const unsigned int *);
extern void pcre_free_substring_list(const char * *);
extern void pcre16_free_substring_list(const unsigned short * *);
extern void pcre32_free_substring_list(const unsigned int * *);
extern int pcre_fullinfo(const pcre *,
                         const pcre_extra *,
                         int,
                         void *);
extern int pcre16_fullinfo(const pcre16 *,
                           const pcre16_extra *,
                           int,
                           void *);
extern int pcre32_fullinfo(const pcre32 *,
                           const pcre32_extra *,
                           int,
                           void *);
extern int pcre_get_named_substring(const pcre *,
                                    const char *,
                                    int *,
                                    int,
                                    const char *,
                                    const char * *);
extern int pcre16_get_named_substring(const pcre16 *,
                                      const unsigned short *,
                                      int *,
                                      int,
                                      const unsigned short *,
                                      const unsigned short * *);
extern int pcre32_get_named_substring(const pcre32 *,
                                      const unsigned int *,
                                      int *,
                                      int,
                                      const unsigned int *,
                                      const unsigned int * *);
extern int pcre_get_stringnumber(const pcre *, const char *);
extern int pcre16_get_stringnumber(const pcre16 *,
                                   const unsigned short *);
extern int pcre32_get_stringnumber(const pcre32 *,
                                   const unsigned int *);
extern int pcre_get_stringtable_entries(const pcre *,
                                        const char *,
                                        char * *,
                                        char * *);
extern int pcre16_get_stringtable_entries(const pcre16 *,
                                          const unsigned short *,
                                          unsigned short * *,
                                          unsigned short * *);
extern int pcre32_get_stringtable_entries(const pcre32 *,
                                          const unsigned int *,
                                          unsigned int * *,
                                          unsigned int * *);
extern int pcre_get_substring(const char *,
                              int *,
                              int,
                              int,
                              const char * *);
extern int pcre16_get_substring(const unsigned short *,
                                int *,
                                int,
                                int,
                                const unsigned short * *);
extern int pcre32_get_substring(const unsigned int *,
                                int *,
                                int,
                                int,
                                const unsigned int * *);
extern int pcre_get_substring_list(const char *,
                                   int *,
                                   int,
                                   const char * * *);
extern int pcre16_get_substring_list(const unsigned short *,
                                     int *,
                                     int,
                                     const unsigned short * * *);
extern int pcre32_get_substring_list(const unsigned int *,
                                     int *,
                                     int,
                                     const unsigned int * * *);
extern const unsigned char * pcre_maketables(void);
extern const unsigned char * pcre16_maketables(void);
extern const unsigned char * pcre32_maketables(void);
extern int pcre_refcount(pcre *, int);
extern int pcre16_refcount(pcre16 *, int);
extern int pcre32_refcount(pcre32 *, int);
extern pcre_extra * pcre_study(const pcre *, int, const char * *);
extern pcre16_extra * pcre16_study(const pcre16 *,
                                   int,
                                   const char * *);
extern pcre32_extra * pcre32_study(const pcre32 *,
                                   int,
                                   const char * *);
extern void pcre_free_study(pcre_extra *);
extern void pcre16_free_study(pcre16_extra *);
extern void pcre32_free_study(pcre32_extra *);
extern const char * pcre_version(void);
extern const char * pcre16_version(void);
extern const char * pcre32_version(void);
extern int pcre_pattern_to_host_byte_order(pcre *,
                                           pcre_extra *,
                                           const unsigned char *);
extern int pcre16_pattern_to_host_byte_order(pcre16 *,
                                             pcre16_extra *,
                                             const unsigned char *);
extern int pcre32_pattern_to_host_byte_order(pcre32 *,
                                             pcre32_extra *,
                                             const unsigned char *);
extern int pcre16_utf16_to_host_byte_order(unsigned short *,
                                           const unsigned short *,
                                           int,
                                           int *,
                                           int);
extern int pcre32_utf32_to_host_byte_order(unsigned int *,
                                           const unsigned int *,
                                           int,
                                           int *,
                                           int);
extern pcre_jit_stack * pcre_jit_stack_alloc(int, int);
extern pcre16_jit_stack * pcre16_jit_stack_alloc(int, int);
extern pcre32_jit_stack * pcre32_jit_stack_alloc(int, int);
extern void pcre_jit_stack_free(pcre_jit_stack *);
extern void pcre16_jit_stack_free(pcre16_jit_stack *);
extern void pcre32_jit_stack_free(pcre32_jit_stack *);
extern void pcre_assign_jit_stack(pcre_extra *,
                                  pcre_jit_callback,
                                  void *);
extern void pcre16_assign_jit_stack(pcre16_extra *,
                                    pcre16_jit_callback,
                                    void *);
extern void pcre32_assign_jit_stack(pcre32_extra *,
                                    pcre32_jit_callback,
                                    void *);
extern void pcre_jit_free_unused_memory(void);
extern void pcre16_jit_free_unused_memory(void);
extern void pcre32_jit_free_unused_memory(void);
extern void _dl_mcount_wrapper_check(void * __selfpc) __attribute__((__nothrow__,__leaf__));
typedef long int Lmid_t;
extern void * dlopen(const char * __file,
                     int __mode) __attribute__((__nothrow__));
extern int dlclose(void * __handle) __attribute__((__nothrow__,__nonnull__(1)));
extern void * dlsym(void * __restrict __handle,
                    const char * __restrict __name) __attribute__((__nothrow__,__leaf__,__nonnull__(2)));
extern void * dlmopen(Lmid_t __nsid,
                      const char * __file,
                      int __mode) __attribute__((__nothrow__));
extern void * dlvsym(void * __restrict __handle,
                     const char * __restrict __name,
                     const char * __restrict __version) __attribute__((__nothrow__,__leaf__,__nonnull__(2, 3)));
extern char * dlerror(void) __attribute__((__nothrow__,__leaf__));
typedef struct {
            const char * dli_fname;
            void * dli_fbase;
            const char * dli_sname;
            void * dli_saddr;
        } Dl_info;
extern int dladdr(const void * __address,
                  Dl_info * __info) __attribute__((__nothrow__,__leaf__,__nonnull__(2)));
extern int dladdr1(const void * __address,
                   Dl_info * __info,
                   void * * __extra_info,
                   int __flags) __attribute__((__nothrow__,__leaf__,__nonnull__(2)));
enum {
    RTLD_DL_SYMENT = 1, RTLD_DL_LINKMAP = 2
};
extern int dlinfo(void * __restrict __handle,
                  int __request,
                  void * __restrict __arg) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 3)));
enum {
    RTLD_DI_LMID = 1,
    RTLD_DI_LINKMAP = 2,
    RTLD_DI_CONFIGADDR = 3,
    RTLD_DI_SERINFO = 4,
    RTLD_DI_SERINFOSIZE = 5,
    RTLD_DI_ORIGIN = 6,
    RTLD_DI_PROFILENAME = 7,
    RTLD_DI_PROFILEOUT = 8,
    RTLD_DI_TLS_MODID = 9,
    RTLD_DI_TLS_DATA = 10,
    RTLD_DI_MAX = 10
};
typedef struct {
            char * dls_name; unsigned int dls_flags;
        } Dl_serpath;
typedef struct {
            size_t dls_size; unsigned int dls_cnt; Dl_serpath dls_serpath[1];
        } Dl_serinfo;
typedef unsigned char cc_t;
typedef unsigned int speed_t;
typedef unsigned int tcflag_t;
struct termios {
    tcflag_t c_iflag;
    tcflag_t c_oflag;
    tcflag_t c_cflag;
    tcflag_t c_lflag;
    cc_t c_line;
    cc_t c_cc[32];
    speed_t c_ispeed;
    speed_t c_ospeed;
};
extern speed_t cfgetospeed(const struct termios * __termios_p) __attribute__((__nothrow__,__leaf__));
extern speed_t cfgetispeed(const struct termios * __termios_p) __attribute__((__nothrow__,__leaf__));
extern int cfsetospeed(struct termios * __termios_p,
                       speed_t __speed) __attribute__((__nothrow__,__leaf__));
extern int cfsetispeed(struct termios * __termios_p,
                       speed_t __speed) __attribute__((__nothrow__,__leaf__));
extern int cfsetspeed(struct termios * __termios_p,
                      speed_t __speed) __attribute__((__nothrow__,__leaf__));
extern int tcgetattr(int __fd,
                     struct termios * __termios_p) __attribute__((__nothrow__,__leaf__));
extern int tcsetattr(int __fd,
                     int __optional_actions,
                     const struct termios * __termios_p) __attribute__((__nothrow__,__leaf__));
extern void cfmakeraw(struct termios * __termios_p) __attribute__((__nothrow__,__leaf__));
extern int tcsendbreak(int __fd,
                       int __duration) __attribute__((__nothrow__,__leaf__));
extern int tcdrain(int __fd);
extern int tcflush(int __fd,
                   int __queue_selector) __attribute__((__nothrow__,__leaf__));
extern int tcflow(int __fd,
                  int __action) __attribute__((__nothrow__,__leaf__));
extern __pid_t tcgetsid(int __fd) __attribute__((__nothrow__,__leaf__));
extern void __assert_fail(const char * __assertion,
                          const char * __file,
                          unsigned int __line,
                          const char * __function) __attribute__((__nothrow__,__leaf__,__noreturn__));
extern void __assert_perror_fail(int __errnum,
                                 const char * __file,
                                 unsigned int __line,
                                 const char * __function) __attribute__((__nothrow__,__leaf__,__noreturn__));
extern void __assert(const char * __assertion,
                     const char * __file,
                     int __line) __attribute__((__nothrow__,__leaf__,__noreturn__));
void * xmalloc(size_t size);
char * xstrdup(char * str);
void * xrealloc(void * ptr, size_t size);
void * xcalloc(size_t count, size_t size);
void xfree(void * ptr);
struct sBufStruct {
    char * mBuf; int mSize; int mLen;
};
typedef struct sBufStruct sBuf;
void sBuf_init(sBuf * self);
void sBuf_append(sBuf * self, void * str, size_t size);
void sBuf_append_char(sBuf * self, char c);
void sBuf_append_str(sBuf * self, char * str);
void sBuf_append_int(sBuf * self, int value);
void sBuf_append_long(sBuf * self, long long value);
void sBuf_clone(sBuf * self, sBuf * buf);
extern char * xstrncpy(char * des, char * src, int size);
extern char * xstrncat(char * des, char * str, int size);
char * xwcstombs(wchar_t * wstr, int len);
typedef unsigned int CLObject;
union CLVALUEUnion {
    unsigned int mUIntValue;
    unsigned char mUByteValue;
    unsigned short mUShortValue;
    unsigned long long mULongValue;
    int mIntValue;
    char mByteValue;
    short mShortValue;
    long long mLongValue;
    CLObject mObjectValue;
    wchar_t mCharValue;
    float mFloatValue;
    double mDoubleValue;
    int mBoolValue;
    char * mPointerValue;
    void * LLVMValue;
};
typedef union CLVALUEUnion CLVALUE;
struct sByteCodeStruct {
    char * mCodes; unsigned int mLen; size_t mSize;
};
typedef struct sByteCodeStruct sByteCode;
void sByteCode_init(sByteCode * code);
void sByteCode_init_with_size(sByteCode * code, int size);
void sByteCode_free(sByteCode * code);
void append_value_to_code(sByteCode * code,
                          void * data,
                          size_t size,
                          int no_output);
void append_opecode_to_code(sByteCode * code,
                            unsigned int op,
                            int no_output);
void append_int_value_to_code(sByteCode * code,
                              int value,
                              int no_output);
void append_long_value_to_code(sByteCode * code,
                               long long value,
                               int no_output);
void append_double_value_to_code(sByteCode * code,
                                 double value,
                                 int no_output);
void append_float_value_to_code(sByteCode * code,
                                float value,
                                int no_output);
struct sConstStruct {
    char * mConst; int mSize; int mLen;
};
typedef struct sConstStruct sConst;
void sConst_init(sConst * self);
void sConst_init_with_size(sConst * self, int size);
void sConst_free(sConst * self);
int sConst_append(sConst * self,
                  void * data,
                  size_t size,
                  int no_output);
int append_int_value_to_constant_pool(sConst * constant,
                                      int n,
                                      int no_output);
int append_float_value_to_constant_pool(sConst * constant,
                                        float n,
                                        int no_output);
int append_double_value_to_constant_pool(sConst * constant,
                                         double n,
                                         int no_output);
int append_str_to_constant_pool(sConst * constant,
                                char * str,
                                int no_output);
void append_buffer_to_constant_pool_and_code(sConst * constant,
                                             sByteCode * code,
                                             char * buf,
                                             int size,
                                             int no_output);
int append_wstr_to_constant_pool(sConst * constant,
                                 char * str,
                                 int no_output);
void append_str_to_constant_pool_and_code(sConst * constant,
                                          sByteCode * code,
                                          char * str,
                                          int no_output);
struct sCLStackStruct {
    CLVALUE * mStack;
    CLVALUE * * mStackPtr;
    struct sCLStackStruct * mNextStack;
};
typedef struct sCLStackStruct sCLStack;
void stack_init();
void stack_final();
sCLStack * append_stack_to_stack_list(CLVALUE * stack_mem,
                                      CLVALUE * * stack_ptr);
int remove_stack_to_stack_list(sCLStack * stack);
int check_variables_existance_on_stack(CLVALUE * stack,
                                       CLVALUE * stack_ptr);
void push_value_to_global_stack(CLVALUE value);
CLVALUE pop_global_stack();
extern sCLStack * gHeadStack;
extern CLVALUE * gGlobalStack;
extern CLVALUE * gGlobalStackPtr;
struct sCLTypeStruct;
struct sCLBlockTypeStruct {
    struct sCLTypeStruct * mParams[32];
    int mNumParams;
    struct sCLTypeStruct * mResultType;
};
typedef struct sCLBlockTypeStruct sCLBlockType;
struct sCLTypeStruct {
    int mClassNameOffset;
    int mNumGenericsTypes;
    struct sCLTypeStruct * mGenericsTypes[32];
    int mArray;
    int mNullable;
    sCLBlockType * mBlockType;
};
typedef struct sCLTypeStruct sCLType;
struct sCLParamStruct {
    int mNameOffset; sCLType * mType; int mDefaultValueOffset;
};
typedef struct sCLParamStruct sCLParam;
struct sVMInfoStruct {
    char * try_catch_label_name;
    CLVALUE * current_stack;
    int current_var_num;
    char * sname;
    int sline;
    char * sname2;
    int sline2;
    int try_offset;
    char * * try_pc;
    sByteCode * try_code;
    struct sCLClassStruct * running_class;
    struct sCLMethodStruct * running_method;
    sCLStack * stack_id;
    char exception_message[1024];
    char * stack_trace_sname[32];
    int stack_trace_sline[32];
    int num_stack_trace;
};
typedef struct sVMInfoStruct sVMInfo;
typedef int (* fNativeMethod)(CLVALUE * * stack_ptr,
                              CLVALUE * lvar,
                              sVMInfo * info);
struct sCLMethodStruct {
    long long mFlags;
    int mNameOffset;
    int mPathOffset;
    int mMethodNameAndParamsOffset;
    int mMethodIndex;
    sCLParam mParams[32];
    int mNumParams;
    sCLType * mResultType;
    sByteCode mByteCodes;
    fNativeMethod mNativeMethod;
    char * mNativeFunName;
    int mVarNum;
    void * mJITDynamicSym;
    int mNumGenerics;
    int mGenericsParamTypeOffsets[32];
};
typedef struct sCLMethodStruct sCLMethod;
struct sCLFieldStruct {
    long long mFlags;
    int mNameOffset;
    sCLType * mResultType;
    CLVALUE mValue;
    int mInitializeValue;
    int mDelegatedMethodIndex[256];
    int mNumDelegatedMethod;
    int mNumGetterMethodIndex;
};
typedef struct sCLFieldStruct sCLField;
typedef void (* fFreeFun)(CLObject self);
struct sCLClassStruct {
    long long mFlags;
    int mGenericsParamClassNum;
    int mMethodGenericsParamClassNum;
    int mNumGenerics;
    int mGenericsParamTypeOffsets[32];
    sConst mConst;
    int mClassNameOffset;
    sCLMethod * mMethods;
    int mNumMethods;
    int mSizeMethods;
    sCLField * mFields;
    int mNumFields;
    int mSizeFields;
    sCLField * mClassFields;
    int mNumClassFields;
    int mSizeClassFields;
    int mClassInitializeMethodIndex;
    int mClassFinalizeMethodIndex;
    int mFinalizeMethodIndex;
    int mCallingMethodIndex;
    int mCallingClassMethodIndex;
    int mMethodIndexOnCompileTime;
    sCLMethod * mVirtualMethodTable[256];
    struct sCLClassStruct * mBoxingClass;
    struct sCLClassStruct * mUnboxingClass;
    void * mDynamicLibrary;
    fFreeFun mFreeFun;
    int mTypedefClassName1Offsets[64];
    int mTypedefClassName2Offsets[64];
    int mNumTypedef;
};
typedef struct sCLClassStruct sCLClass;
void class_init();
void class_init_on_compile_time();
void set_boxing_and_unboxing_classes();
void class_final();
sCLClass * get_class(char * name);
unsigned int get_hash_key(char * name, unsigned int max);
sCLClass * alloc_class(char * class_name,
                       int primitive_,
                       int generics_param_class_num,
                       int method_generics_param_class_num,
                       int generics_number,
                       sCLClass * * type_of_generics_params,
                       int interface,
                       int dynamic_class,
                       int no_free_object);
sCLType * create_cl_type(sCLClass * klass, sCLClass * klass2);
void free_cl_type(sCLType * cl_type);
sCLClass * load_class(char * class_name);
sCLMethod * search_for_method_from_virtual_method_table(sCLClass * klass,
                                                        char * method_name_and_params);
int is_valid_class(sCLClass * klass);
int put_class_to_table(char * class_name, sCLClass * klass);
int jit_compile_all_classes();
void remove_class(char * class_name);
sCLClass * load_class_from_class_file(char * class_name,
                                      char * class_file_name);
sCLClass * get_class_with_load(char * class_name);
struct sClassTableStruct {
    char * mName;
    sCLClass * mItem;
    int mFreed;
    struct sClassTableStruct * mNextClass;
};
typedef struct sClassTableStruct sClassTable;
extern sClassTable * gHeadClassTable;
struct sNodeBlockTypeStruct;
struct sNodeTypeStruct {
    sCLClass * mClass;
    struct sNodeTypeStruct * mGenericsTypes[32];
    int mNumGenericsTypes;
    int mArray;
    int mNullable;
    struct sNodeBlockTypeStruct * mBlockType;
};
typedef struct sNodeTypeStruct sNodeType;
void init_node_types();
void free_node_types();
sNodeType * alloc_node_type();
sNodeType * clone_node_type(sNodeType * node_type);
sNodeType * create_node_type_with_class_name(char * class_name);
sNodeType * create_node_type_with_generics_number(int generics_num);
sNodeType * create_node_type_with_method_generics_number(int generics_num);
sNodeType * create_node_type_from_cl_type(sCLType * cl_type,
                                          sCLClass * klass);
sNodeType * create_node_type_with_class_pointer(sCLClass * klass);
int is_exception_type(sNodeType * exception_type);
int substitution_posibility(sNodeType * left,
                            sNodeType * right,
                            sNodeType * left_generics_types,
                            sNodeType * right_generics_types,
                            sNodeType * left_method_generics,
                            sNodeType * right_method_generics);
int substitution_posibility_with_class_name(sNodeType * left,
                                            char * right_class_name);
int operand_posibility_with_class_name(sNodeType * left,
                                       char * right_class_name,
                                       char * op_string);
int operand_posibility(sNodeType * left,
                       sNodeType * right,
                       char * op_string);
int solve_generics_types_for_node_type(sNodeType * node_type,
                                       sNodeType * * result,
                                       sNodeType * generics_type,
                                       int solve_Self,
                                       int solve_method_generics);
struct sParserInfoStruct;
void solve_generics_for_variable_to_class(sCLClass * klass,
                                          sCLClass * * result,
                                          struct sParserInfoStruct * info);
void solve_method_generics_for_variable_to_class(sCLClass * klass,
                                                 sCLClass * * result,
                                                 struct sParserInfoStruct * info);
void solve_generics_for_variable(sNodeType * generics_type,
                                 sNodeType * * generics_type2,
                                 struct sParserInfoStruct * info);
int type_identify_with_class_name(sNodeType * left,
                                  char * right_class_name);
int type_identify(sNodeType * left, sNodeType * right);
int class_identify_with_class_name(sCLClass * klass,
                                   char * class_name);
void print_node_type(sNodeType * node_type);
int boxing_posibility(sNodeType * left_type,
                      sNodeType * right_type);
int unboxing_posibility(sNodeType * left_type,
                        sNodeType * right_type);
int unboxig_posibility(sCLClass * klass);
sNodeType * create_generics_types_from_generics_params(sCLClass * klass);
struct sCompileInfoStruct;
void boxing_to_lapper_class(sNodeType * * type_,
                            struct sCompileInfoStruct * info);
int unboxing_to_primitive_type(sNodeType * * left_type,
                               struct sCompileInfoStruct * info);
void make_boxing_type(sNodeType * type, sNodeType * * result);
int no_cast_types_for_binary_operator(sNodeType * left_type,
                                      sNodeType * right_type);
struct sNodeBlockTypeStruct {
    sNodeType * mParams[32];
    int mNumParams;
    struct sNodeTypeStruct * mResultType;
    int mLambda;
};
typedef struct sNodeBlockTypeStruct sNodeBlockType;
void init_node_block_types();
void free_node_block_types();
sNodeBlockType * alloc_node_block_type();
sNodeBlockType * clone_node_block_type(sNodeBlockType * block);
int substitution_posibility_for_node_block_type(sNodeBlockType * left_block,
                                                sNodeBlockType * right_block,
                                                sNodeType * left_generics_types,
                                                sNodeType * right_generics_types);
struct sVarStruct {
    char mName[64]; int mIndex; sNodeType * mType; int mBlockLevel;
};
typedef struct sVarStruct sVar;
struct sVarTableStruct {
    sVar mLocalVariables[128];
    int mVarNum;
    int mMaxBlockVarNum;
    int mBlockLevel;
    struct sVarTableStruct * mParent;
    struct sVarTableStruct * mNext;
};
typedef struct sVarTableStruct sVarTable;
void init_vtable();
void final_vtable();
sVarTable * init_block_vtable(sVarTable * lv_table);
sVarTable * init_var_table();
sVarTable * clone_var_table(sVarTable * lv_table);
void restore_var_table(sVarTable * left, sVarTable * right);
void set_max_block_var_num(sVarTable * new_table,
                           sVarTable * lv_table);
int get_variable_index(sVarTable * table, char * name);
void check_already_added_variable(sVarTable * table,
                                  char * name,
                                  struct sParserInfoStruct * info);
int add_variable_to_table(sVarTable * table,
                          char * name,
                          sNodeType * type_);
sVar * get_variable_from_table(sVarTable * table, char * name);
sVar * get_variable_from_index(sVarTable * table, int index);
int get_var_num(sVarTable * table);
void show_vtable(sVarTable * table);
int get_parent_var_num_of_sum(sVarTable * table);
extern int gInterpreter;
struct sGenericsParamInfoStruct {
    char mParamNames[32][64];
    int mNumParams;
    sCLClass * mInterface[32];
};
typedef struct sGenericsParamInfoStruct sGenericsParamInfo;
struct sCompileInfoStruct;
struct sParserInfoStruct {
    char * p;
    char * sname;
    int sline;
    int err_num;
    sVarTable * lv_table;
    int parse_phase;
    sCLClass * klass;
    sGenericsParamInfo generics_info;
    sGenericsParamInfo method_generics_info;
    struct sCompileInfoStruct * cinfo;
    int included_source;
    int get_type_for_interpreter;
    int next_command_is_to_bool;
    int exist_block_object_err;
};
typedef struct sParserInfoStruct sParserInfo;
extern char gCompilingSourceFileName[4096];
void parser_init();
void parser_final();
struct sParserParamStruct;
int parse_params_and_entry_to_lvtable(struct sParserParamStruct * params,
                                      int * num_params,
                                      sParserInfo * info,
                                      sVarTable * * new_table,
                                      sVarTable * parent_lv_table,
                                      int character_type);
void parser_err_msg(sParserInfo * info, const char * msg, ...);
int expression(unsigned int * node, sParserInfo * info);
void skip_spaces_and_lf(sParserInfo * info);
void expect_next_character_with_one_forward(char * characters,
                                            sParserInfo * info);
int parse_word(char * buf,
               int buf_size,
               sParserInfo * info,
               int print_out_err_msg,
               int no_skip_lf);
int parse_type(sNodeType * * result_type, sParserInfo * info);
int parse_class_type(sCLClass * * klass, sParserInfo * info);
struct sNodeBlockStruct {
    unsigned int * mNodes;
    unsigned int mSizeNodes;
    unsigned int mNumNodes;
    sVarTable * mLVTable;
    int mUnClosedBlock;
    sBuf mSource;
    char * mSName;
    int mSLine;
};
typedef struct sNodeBlockStruct sNodeBlock;
void sNodeBlock_free(sNodeBlock * block);
sNodeBlock * sNodeBlock_clone(sNodeBlock * block);
int parse_block(sNodeBlock * * node_block,
                sParserInfo * info,
                sVarTable * new_table,
                int block_object);
enum eNodeType {
    kNodeTypeOperand,
    kNodeTypeByteValue,
    kNodeTypeCByteValue,
    kNodeTypeUByteValue,
    kNodeTypeCUByteValue,
    kNodeTypeShortValue,
    kNodeTypeCShortValue,
    kNodeTypeUShortValue,
    kNodeTypeCUShortValue,
    kNodeTypeIntValue,
    kNodeTypeCIntValue,
    kNodeTypeUIntValue,
    kNodeTypeCUIntValue,
    kNodeTypeLongValue,
    kNodeTypeCLongValue,
    kNodeTypeULongValue,
    kNodeTypeCULongValue,
    kNodeTypeAssignVariable,
    kNodeTypeLoadVariable,
    kNodeTypeIf,
    kNodeTypeWhile,
    kNodeTypeBreak,
    kNodeTypeTrue,
    kNodeTypeFalse,
    kNodeTypeNull,
    kNodeTypeWildCard,
    kNodeTypeFor,
    kNodeTypeClassMethodCall,
    kNodeTypeMethodCall,
    kNodeTypeReturn,
    kNodeTypeNewOperator,
    kNodeTypeLoadField,
    kNodeTypeStoreField,
    kNodeTypeLoadClassField,
    kNodeTypeStoreClassField,
    kNodeTypeLoadValueFromPointer,
    kNodeTypeStoreValueToPointer,
    kNodeTypeIncrementOperand,
    kNodeTypeDecrementOperand,
    kNodeTypeIncrementWithValueOperand,
    kNodeTypeDecrementWithValueOperand,
    kNodeTypeMonadicIncrementOperand,
    kNodeTypeMonadicDecrementOperand,
    kNodeTypeLoadArrayElement,
    kNodeTypeStoreArrayElement,
    kNodeTypeChar,
    kNodeTypeString,
    kNodeTypeBuffer,
    kNodeTypeThrow,
    kNodeTypeTry,
    kNodeTypeBlockObject,
    kNodeTypeFunction,
    kNodeTypeBlockCall,
    kNodeTypeNormalBlock,
    kNodeTypeArrayValue,
    kNodeTypeAndAnd,
    kNodeTypeOrOr,
    kNodeTypeHashValue,
    kNodeTypeRegex,
    kNodeTypeListValue,
    kNodeTypeSortableListValue,
    kNodeTypeEqualableListValue,
    kNodeTypeTupleValue,
    kNodeTypeCArrayValue,
    kNodeTypeEqualableCArrayValue,
    kNodeTypeSortableCArrayValue,
    kNodeTypeImplements,
    kNodeTypeGetAddress,
    kNodeTypeInheritCall,
    kNodeTypeFloatValue,
    kNodeTypeCFloatValue,
    kNodeTypeDoubleValue,
    kNodeTypeCDoubleValue,
    kNodeTypePath,
    kNodeTypeWhen,
    kNodeTypeRange
};
enum eOperand {
    kOpAdd,
    kOpSub,
    kOpComplement,
    kOpLogicalDenial,
    kOpMult,
    kOpDiv,
    kOpMod,
    kOpLeftShift,
    kOpRightShift,
    kOpComparisonEqual,
    kOpComparisonNotEqual,
    kOpComparisonGreaterEqual,
    kOpComparisonLesserEqual,
    kOpComparisonGreater,
    kOpComparisonLesser,
    kOpAnd,
    kOpXor,
    kOpOr
};
struct sParserParamStruct {
    char mName[64]; sNodeType * mType; char mDefaultValue[1024];
};
typedef struct sParserParamStruct sParserParam;
struct sNodeTreeStruct {
    enum eNodeType mNodeType;
    unsigned int mLeft;
    unsigned int mRight;
    unsigned int mMiddle;
    char * mSName;
    int mLine;
    union {
        enum eOperand mOperand;
        char mByteValue;
        unsigned char mUByteValue;
        short mShortValue;
        unsigned short mUShortValue;
        int mIntValue;
        unsigned int mUIntValue;
        long long mLongValue;
        unsigned long long mULongValue;
        char mVarName[64];
        struct {
            char mVarName[64]; sCLClass * mClass;
        } sAssignVariable;
        struct {
            unsigned int mExpressionNode;
            sNodeBlock * mIfNodeBlock;
            unsigned int mElifExpressionNodes[32];
            sNodeBlock * mElifNodeBlocks[32];
            int mElifNum;
            sNodeBlock * mElseNodeBlock;
        } sIf;
        struct {
            unsigned int mExpressionNode;
            int mNumWhenBlock;
            int mValueNodes[64][64];
            int mNumValues[64];
            sNodeBlock * mWhenBlocks[64];
            sNodeType * mWhenTypes[64];
            sNodeType * mWhenTypes2[64];
            sNodeBlock * mElseBlock;
        } sWhen;
        struct {
            unsigned int mExpressionNode; sNodeBlock * mWhileNodeBlock;
        } sWhile;
        struct {
            unsigned int mExpressionNode;
            unsigned int mExpressionNode2;
            unsigned int mExpressionNode3;
            sNodeBlock * mForNodeBlock;
        } sFor;
        struct {
            sNodeBlock * mTryNodeBlock;
            sNodeBlock * mCatchNodeBlock;
            char mExceptionVarName[64];
        } sTry;
        struct {
            sNodeType * mClass;
            char mMethodName[64];
            unsigned int mParams[32];
            int mNumParams;
        } sClassMethodCall;
        struct {
            char mMethodName[64];
            unsigned int mParams[32];
            int mNumParams;
            int mNumMethodChains;
        } sMethodCall;
        struct {
            sNodeType * mType;
            unsigned int mParams[32];
            int mNumParams;
            unsigned int mArrayNum;
        } sNewOperator;
        struct {
            char mVarName[64]; sCLClass * mClass;
        } sClassField;
        wchar_t mCharacter;
        struct {
            char * mString;
            unsigned int mStringExpressions[32];
            int mStringExpressionOffsets[32];
            int mNumStringExpression;
        } sString;
        struct {
            char * mBuffer;
            int mLen;
            unsigned int mStringExpressions[32];
            int mStringExpressionOffsets[32];
            int mNumStringExpression;
        } sBuffer;
        struct {
            sParserParam mParams[32];
            int mNumParams;
            sNodeType * mResultType;
            sNodeBlock * mBlockObjectCode;
            int mLambda;
            int mOmitResultType;
            int mOmitParams;
            sVarTable * mOldTable;
        } sBlockObject;
        struct {
            char mName[64];
            sParserParam mParams[32];
            int mNumParams;
            sNodeType * mResultType;
            sNodeBlock * mBlockObjectCode;
            int mLambda;
        } sFunction;
        struct {
            unsigned int mParams[32]; int mNumParams;
        } sBlockCall;
        struct {
            unsigned int mParams[32]; int mNumParams; int mMethodIndex;
        } sInheritCall;
        sNodeBlock * mBlock;
        struct {
            unsigned int mArrayElements[256]; int mNumArrayElements;
        } sArrayValue;
        struct {
            unsigned int mListElements[256]; int mNumListElements;
        } sListValue;
        struct {
            unsigned int mTupleElements[256]; int mNumTupleElements;
        } sTupleValue;
        struct {
            unsigned int mHashKeys[256];
            unsigned int mHashItems[256];
            int mNumHashElements;
        } sHashValue;
        struct {
            char * mRegexStr;
            int mGlobal;
            int mIgnoreCase;
            int mMultiline;
            int mExtended;
            int mDotAll;
            int mAnchored;
            int mDollarEndOnly;
            int mUngreedy;
            unsigned int mStringExpressions[32];
            int mStringExpressionOffsets[32];
            int mNumStringExpression;
        } sRegex;
        float mFloatValue;
        double mDoubleValue;
    } uValue;
    sNodeType * mType;
    int mMaxMethodChains;
};
typedef struct sNodeTreeStruct sNodeTree;
struct sCompileInfoStruct {
    sByteCode * code;
    sConst * constant;
    int stack_num;
    sVarTable * lv_table;
    int no_output;
    int err_num;
    sParserInfo * pinfo;
    sNodeType * type;
    int * num_break_points;
    int * break_points;
    sCLMethod * method;
    sNodeType * block_result_type;
    sNodeType * return_type;
    int in_block;
    int omit_block_result_type;
    sNodeType * block_last_type;
    char * sname;
    int sline;
    int result_type_boxing;
    int omit_block_result_type2;
    sNodeType * return_type2;
    char * break_point_label_name;
    int no_pop_next;
};
typedef struct sCompileInfoStruct sCompileInfo;
extern sNodeTree * gNodes;
void init_nodes();
void free_nodes();
void show_node(unsigned int node);
unsigned int clone_node(unsigned int node);
void compile_err_msg(sCompileInfo * info, const char * msg, ...);
int compile(unsigned int node, sCompileInfo * info);
void append_class_name_to_constant_pool_and_code(sCompileInfo * info,
                                                 sCLClass * klass);
void create_type_name_from_node_type(char * type_name,
                                     int type_name_max,
                                     sNodeType * node_type);
int get_var_size(sNodeType * var_type);
unsigned int sNodeTree_create_operand(enum eOperand operand,
                                      unsigned int left,
                                      unsigned int right,
                                      unsigned int middle,
                                      sParserInfo * info);
unsigned int sNodeTree_when_expression(unsigned int expression_node,
                                       unsigned int value_nodes[64][64],
                                       int num_values[64],
                                       sNodeBlock * when_blocks[64],
                                       int num_when_block,
                                       sNodeBlock * else_block,
                                       sNodeType * when_types[64],
                                       sNodeType * when_types2[64],
                                       sParserInfo * info);
unsigned int sNodeTree_if_expression(unsigned int expression_node,
                                     sNodeBlock * if_node_block,
                                     unsigned int * elif_expression_nodes,
                                     sNodeBlock * * elif_node_blocks,
                                     int elif_num,
                                     sNodeBlock * else_node_block,
                                     sParserInfo * info);
unsigned int sNodeTree_create_range(unsigned int head,
                                    unsigned int tail,
                                    sParserInfo * info);
unsigned int sNodeTree_create_byte_value(char value,
                                         unsigned int left,
                                         unsigned int right,
                                         unsigned int middle,
                                         sParserInfo * info);
unsigned int sNodeTree_create_cbyte_value(char value,
                                          unsigned int left,
                                          unsigned int right,
                                          unsigned int middle,
                                          sParserInfo * info);
unsigned int sNodeTree_create_ubyte_value(unsigned char value,
                                          unsigned int left,
                                          unsigned int right,
                                          unsigned int middle,
                                          sParserInfo * info);
unsigned int sNodeTree_create_cubyte_value(unsigned char value,
                                           unsigned int left,
                                           unsigned int right,
                                           unsigned int middle,
                                           sParserInfo * info);
unsigned int sNodeTree_create_short_value(short value,
                                          unsigned int left,
                                          unsigned int right,
                                          unsigned int middle,
                                          sParserInfo * info);
unsigned int sNodeTree_create_cshort_value(short value,
                                           unsigned int left,
                                           unsigned int right,
                                           unsigned int middle,
                                           sParserInfo * info);
unsigned int sNodeTree_create_ushort_value(unsigned short value,
                                           unsigned int left,
                                           unsigned int right,
                                           unsigned int middle,
                                           sParserInfo * info);
unsigned int sNodeTree_create_cushort_value(unsigned short value,
                                            unsigned int left,
                                            unsigned int right,
                                            unsigned int middle,
                                            sParserInfo * info);
unsigned int sNodeTree_create_int_value(int value,
                                        unsigned int left,
                                        unsigned int right,
                                        unsigned int middle,
                                        sParserInfo * info);
unsigned int sNodeTree_create_cint_value(int value,
                                         unsigned int left,
                                         unsigned int right,
                                         unsigned int middle,
                                         sParserInfo * info);
unsigned int sNodeTree_create_uint_value(unsigned int value,
                                         unsigned int left,
                                         unsigned int right,
                                         unsigned int middle,
                                         sParserInfo * info);
unsigned int sNodeTree_create_cuint_value(unsigned int value,
                                          unsigned int left,
                                          unsigned int right,
                                          unsigned int middle,
                                          sParserInfo * info);
unsigned int sNodeTree_create_long_value(long long value,
                                         unsigned int left,
                                         unsigned int right,
                                         unsigned int middle,
                                         sParserInfo * info);
unsigned int sNodeTree_create_clong_value(long long value,
                                          unsigned int left,
                                          unsigned int right,
                                          unsigned int middle,
                                          sParserInfo * info);
unsigned int sNodeTree_create_ulong_value(unsigned long long value,
                                          unsigned int left,
                                          unsigned int right,
                                          unsigned int middle,
                                          sParserInfo * info);
unsigned int sNodeTree_create_culong_value(unsigned long long value,
                                           unsigned int left,
                                           unsigned int right,
                                           unsigned int middle,
                                           sParserInfo * info);
unsigned int sNodeTree_create_store_variable(char * var_name,
                                             sNodeType * node_type,
                                             int right,
                                             sCLClass * klass,
                                             sParserInfo * info);
unsigned int sNodeTree_create_assign_field(char * var_name,
                                           unsigned int left_node,
                                           unsigned int right_node,
                                           sParserInfo * info);
unsigned int sNodeTree_create_load_variable(char * var_name,
                                            sParserInfo * info);
unsigned int sNodeTree_create_return_expression(unsigned int expression_node,
                                                sParserInfo * info);
unsigned int sNodeTree_create_throw_expression(unsigned int expression_node,
                                               sParserInfo * info);
unsigned int sNodeTree_if_expression(unsigned int expression_node,
                                     sNodeBlock * if_node_block,
                                     unsigned int * elif_expression_node,
                                     sNodeBlock * * elif_node_block,
                                     int elif_num,
                                     sNodeBlock * else_node_block,
                                     sParserInfo * info);
unsigned int sNodeTree_while_expression(unsigned int expression_node,
                                        sNodeBlock * while_node_block,
                                        sParserInfo * info);
unsigned int sNodeTree_break_expression(sParserInfo * info);
unsigned int sNodeTree_false_expression(sParserInfo * info);
unsigned int sNodeTree_true_expression(sParserInfo * info);
unsigned int sNodeTree_null_expression(sParserInfo * info);
unsigned int sNodeTree_wildcard_expression(sParserInfo * info);
unsigned int sNodeTree_for_expression(unsigned int expression_node1,
                                      unsigned int expression_node2,
                                      unsigned int expression_node3,
                                      sNodeBlock * for_node_block,
                                      sParserInfo * info);
int check_node_is_variable(unsigned int node);
unsigned int sNodeTree_create_class_method_call(sNodeType * klass,
                                                char * method_name,
                                                unsigned int * params,
                                                int num_params,
                                                sParserInfo * info);
unsigned int sNodeTree_create_method_call(unsigned int object_node,
                                          char * method_name,
                                          unsigned int * params,
                                          int num_params,
                                          int num_method_chains,
                                          sParserInfo * info);
unsigned int sNodeTree_create_new_operator(sNodeType * node_type,
                                           unsigned int * params,
                                           int num_params,
                                           unsigned int array_num,
                                           sParserInfo * info);
unsigned int sNodeTree_create_fields(char * name,
                                     unsigned int left_node,
                                     sParserInfo * info);
unsigned int sNodeTree_create_class_fields(sCLClass * klass,
                                           char * name,
                                           sParserInfo * info);
unsigned int sNodeTree_create_assign_class_field(sCLClass * klass,
                                                 char * name,
                                                 unsigned int right_node,
                                                 sParserInfo * info);
unsigned int sNodeTree_create_store_value_to_pointer(unsigned int left_node,
                                                     sNodeType * node_type,
                                                     unsigned int right_node,
                                                     sParserInfo * info);
unsigned int sNodeTree_create_load_value_from_pointer(unsigned int left_node,
                                                      sNodeType * node_type,
                                                      sParserInfo * info);
int sNodeTree_create_decrement_operand(unsigned int left_node,
                                       sParserInfo * info);
int sNodeTree_create_increment_operand(unsigned int left_node,
                                       sParserInfo * info);
int sNodeTree_create_increment_operand_with_value(unsigned int left_node,
                                                  unsigned int value,
                                                  sParserInfo * info);
int sNodeTree_create_decrement_operand_with_value(unsigned int left_node,
                                                  unsigned int value,
                                                  sParserInfo * info);
int sNodeTree_create_monadic_decrement_operand(unsigned int right_node,
                                               sParserInfo * info);
int sNodeTree_create_monadic_increment_operand(unsigned int right_node,
                                               sParserInfo * info);
unsigned int sNodeTree_create_load_array_element(unsigned int array,
                                                 unsigned int index_node,
                                                 sParserInfo * info);
unsigned int sNodeTree_create_store_array_element(unsigned int array,
                                                  unsigned int index_ndoe,
                                                  unsigned int right_node,
                                                  sParserInfo * info);
unsigned int sNodeTree_create_character_value(wchar_t c,
                                              sParserInfo * info);
unsigned int sNodeTree_create_string_value(char * value,
                                           unsigned int * string_expressions,
                                           int * string_expression_offsets,
                                           int num_string_expression,
                                           sParserInfo * info);
unsigned int sNodeTree_create_buffer_value(char * value,
                                           int len,
                                           unsigned int * string_expressions,
                                           int * string_expression_offsets,
                                           int num_string_expression,
                                           sParserInfo * info);
unsigned int sNodeTree_try_expression(sNodeBlock * try_node_block,
                                      sNodeBlock * catch_node_block,
                                      char * exception_var_name,
                                      sParserInfo * info);
unsigned int sNodeTree_create_block_object(sParserParam * params,
                                           int num_params,
                                           sNodeType * result_type,
                                           sNodeBlock * node_block,
                                           int lambda,
                                           sParserInfo * info,
                                           int omit_result_type,
                                           int omit_params,
                                           sVarTable * old_table);
unsigned int sNodeTree_create_block_call(unsigned int block,
                                         int num_params,
                                         unsigned int params[],
                                         sParserInfo * info);
unsigned int sNodeTree_conditional_expression(unsigned int expression_node,
                                              unsigned int true_expression_node,
                                              unsigned int false_expression_node,
                                              sParserInfo * info);
unsigned int sNodeTree_create_normal_block(sNodeBlock * node_block,
                                           sParserInfo * info);
unsigned int sNodeTree_create_array_value(int num_elements,
                                          unsigned int array_elements[],
                                          sParserInfo * info);
unsigned int sNodeTree_create_list_value(int num_elements,
                                         unsigned int list_elements[],
                                         sParserInfo * info);
unsigned int sNodeTree_create_equalable_list_value(int num_elements,
                                                   unsigned int list_elements[],
                                                   sParserInfo * info);
unsigned int sNodeTree_create_sortable_list_value(int num_elements,
                                                  unsigned int list_elements[],
                                                  sParserInfo * info);
unsigned int sNodeTree_create_tuple_value(int num_elements,
                                          unsigned int tuple_elements[],
                                          sParserInfo * info);
unsigned int sNodeTree_create_or_or(unsigned int left_node,
                                    unsigned int right_node,
                                    sParserInfo * info);
unsigned int sNodeTree_create_and_and(unsigned int left_node,
                                      unsigned int right_node,
                                      sParserInfo * info);
unsigned int sNodeTree_create_hash_value(int num_elements,
                                         unsigned int hash_keys[],
                                         unsigned int hash_items[],
                                         sParserInfo * info);
unsigned int sNodeTree_create_regex(char * regex_str,
                                    int global,
                                    int ignore_case,
                                    int multiline,
                                    int extended,
                                    int dotall,
                                    int anchored,
                                    int dollar_endonly,
                                    int ungreedy,
                                    unsigned int * string_expressions,
                                    int * string_expression_offsets,
                                    int num_string_expression,
                                    sParserInfo * info);
unsigned int sNodeTree_create_carray_value(int num_elements,
                                           unsigned int array_elements[],
                                           sParserInfo * info);
unsigned int sNodeTree_create_equalable_carray_value(int num_elements,
                                                     unsigned int array_elements[],
                                                     sParserInfo * info);
unsigned int sNodeTree_create_sortable_carray_value(int num_elements,
                                                    unsigned int array_elements[],
                                                    sParserInfo * info);
unsigned int sNodeTree_create_implements(unsigned int lnode,
                                         char * interface_name,
                                         sParserInfo * info);
unsigned int sNodeTree_create_get_address(unsigned int node,
                                          sParserInfo * info);
unsigned int sNodeTree_create_inherit_call(int num_params,
                                           unsigned int params[],
                                           int method_index,
                                           sParserInfo * info);
unsigned int sNodeTree_create_float_value(float value,
                                          unsigned int left,
                                          unsigned int right,
                                          unsigned int middle,
                                          sParserInfo * info);
unsigned int sNodeTree_create_cfloat_value(float value,
                                           unsigned int left,
                                           unsigned int right,
                                           unsigned int middle,
                                           sParserInfo * info);
unsigned int sNodeTree_create_double_value(double value,
                                           unsigned int left,
                                           unsigned int right,
                                           unsigned int middle,
                                           sParserInfo * info);
unsigned int sNodeTree_create_cdouble_value(double value,
                                            unsigned int left,
                                            unsigned int right,
                                            unsigned int middle,
                                            sParserInfo * info);
unsigned int sNodeTree_create_path_value(char * value,
                                         int len,
                                         unsigned int * string_expressions,
                                         int * string_expression_offsets,
                                         int num_string_expression,
                                         sParserInfo * info);
unsigned int sNodeTree_create_function(char * fun_name,
                                       sParserParam * params,
                                       int num_params,
                                       sNodeType * result_type,
                                       sNodeBlock * node_block,
                                       int lambda,
                                       sParserInfo * info);
void arrange_stack(sCompileInfo * cinfo);
int compile_block(sNodeBlock * block, sCompileInfo * info);
int compile_block_with_result(sNodeBlock * block,
                              sCompileInfo * info);
int compile_script(char * fname, char * source);
int read_source(char * fname, sBuf * source);
int delete_comment(sBuf * source, sBuf * source2);
void append_cwd_for_path(char * fname, char * fname2);
int eval_file(char * fname, int stack_size);
void cast_right_type_to_byte(sNodeType * * right_type,
                             sCompileInfo * info);
void cast_right_type_to_short(sNodeType * * right_type,
                              sCompileInfo * info);
void cast_right_type_to_int(sNodeType * * right_type,
                            sCompileInfo * info);
void cast_right_type_to_long(sNodeType * * right_type,
                             sCompileInfo * info);
void cast_right_type_to_ubyte(sNodeType * * right_type,
                              sCompileInfo * info);
void cast_right_type_to_ushort(sNodeType * * right_type,
                               sCompileInfo * info);
void cast_right_type_to_uint(sNodeType * * right_type,
                             sCompileInfo * info);
void cast_right_type_to_ulong(sNodeType * * right_type,
                              sCompileInfo * info);
void cast_right_type_to_float(sNodeType * * right_type,
                              sCompileInfo * info);
void cast_right_type_to_double(sNodeType * * right_type,
                               sCompileInfo * info);
void cast_right_type_to_char(sNodeType * * right_type,
                             sCompileInfo * info);
void cast_right_type_to_bool(sNodeType * * right_type,
                             sCompileInfo * info);
void cast_right_type_to_pointer(sNodeType * * right_type,
                                sCompileInfo * info);
void cast_right_type_to_String(sNodeType * * right_type,
                               sCompileInfo * info);
void cast_right_type_to_Byte(sNodeType * * right_type,
                             sCompileInfo * info);
void cast_right_type_to_UByte(sNodeType * * right_type,
                              sCompileInfo * info);
void cast_right_type_to_Short(sNodeType * * right_type,
                              sCompileInfo * info);
void cast_right_type_to_UShort(sNodeType * * right_type,
                               sCompileInfo * info);
void cast_right_type_to_Integer(sNodeType * * right_type,
                                sCompileInfo * info);
void cast_right_type_to_UInteger(sNodeType * * right_type,
                                 sCompileInfo * info);
void cast_right_type_to_Long(sNodeType * * right_type,
                             sCompileInfo * info);
void cast_right_type_to_ULong(sNodeType * * right_type,
                              sCompileInfo * info);
void cast_right_type_to_Float(sNodeType * * right_type,
                              sCompileInfo * info);
void cast_right_type_to_Double(sNodeType * * right_type,
                               sCompileInfo * info);
void cast_right_type_to_Pointer(sNodeType * * right_type,
                                sCompileInfo * info);
void cast_right_type_to_Char(sNodeType * * right_type,
                             sCompileInfo * info);
void cast_right_type_to_Bool(sNodeType * * right_type,
                             sCompileInfo * info);
void cast_right_type_to_Array(sNodeType * * right_type,
                              sCompileInfo * info);
void cast_right_type_to_left_type(sNodeType * left_type,
                                  sNodeType * * right_type,
                                  sCompileInfo * info);
extern int gSigInt;
int vm(sByteCode * code,
       sConst * constant,
       CLVALUE * stack,
       int var_num,
       sCLClass * klass,
       sVMInfo * info);
void vm_mutex_on();
void vm_mutex_off();
void new_vm_mutex();
sCLClass * get_class_with_load_and_initialize(char * class_name);
void class_final_on_runtime();
int call_finalize_method_on_free_object(sCLClass * klass,
                                        CLObject self);
int invoke_method(sCLClass * klass,
                  sCLMethod * method,
                  CLVALUE * stack,
                  int var_num,
                  CLVALUE * * stack_ptr,
                  sVMInfo * info);
int invoke_block(CLObject block_object,
                 CLVALUE * stack,
                 int var_num,
                 int num_params,
                 CLVALUE * * stack_ptr,
                 sVMInfo * info,
                 int llvm_flag);
int class_init_on_runtime();
void show_stack(CLVALUE * stack,
                CLVALUE * stack_ptr,
                CLVALUE * lvar,
                int var_num);
void boxing_primitive_value_to_object(CLVALUE object,
                                      CLVALUE * result,
                                      sCLClass * klass);
void Self_convertion_of_method_name_and_params(char * method_name_and_params,
                                               char * method_name_and_params2,
                                               char * class_name);
int compile_class_source(char * fname, char * source);
void set_dependency_compile();
int dependency_check(char * fname);
int dependency_compile(char * cwd,
                       char * class_name,
                       char * class_file_name,
                       size_t class_file_name_size);
void dependency_final();
sCLClass * get_class_with_load_on_compile_time(char * class_name);
sCLClass * load_class_on_compile_time(char * class_name);
int add_method_to_class(sCLClass * klass,
                        char * method_name,
                        sParserParam * params,
                        int num_params,
                        sNodeType * result_type,
                        int native_,
                        int static_,
                        sGenericsParamInfo * ginfo);
int add_field_to_class(sCLClass * klass,
                       char * name,
                       int private_,
                       int protected_,
                       sNodeType * result_type);
int add_typedef_to_class(sCLClass * klass,
                         char * class_name1,
                         char * class_name2);
int add_class_field_to_class(sCLClass * klass,
                             char * name,
                             int private_,
                             int protected_,
                             sNodeType * result_type,
                             int initialize_value);
void add_code_to_method(sCLMethod * method,
                        sByteCode * code,
                        int var_num);
int write_all_modified_classes();
int search_for_method(sCLClass * klass,
                      char * method_name,
                      sNodeType * * param_types,
                      int num_params,
                      int search_for_class_method,
                      int start_point,
                      sNodeType * left_generics_type,
                      sNodeType * right_generics_type,
                      sNodeType * right_method_generics,
                      sNodeType * * result_type,
                      int lazy_lambda_compile,
                      int lazy_labda_compile2,
                      sNodeType * * method_generics_types);
int search_for_methods_from_method_name(int method_indexes[],
                                        int size_method_indexes,
                                        int * num_methods,
                                        sCLClass * klass,
                                        char * method_name,
                                        int start_point,
                                        int class_method);
int search_for_field(sCLClass * klass, char * field_name);
int search_for_class_field(sCLClass * klass, char * field_name);
void add_dependences_with_node_type(sCLClass * klass,
                                    sNodeType * node_type);
int parse_params(sParserParam * params,
                 int * num_params,
                 sParserInfo * info,
                 int chracter_type);
int check_implemented_methods_for_interface(sCLClass * left_class,
                                            sCLClass * right_class);
int method_name_existance(sCLClass * klass, char * method_name);
int field_name_existance(sCLClass * klass, char * field_name);
void create_method_name_and_params(char * result,
                                   int size_result,
                                   sCLClass * klass,
                                   char * method_name,
                                   sNodeType * param_types[32],
                                   int num_params);
int determine_method_generics_types(sNodeType * left_param,
                                    sNodeType * right_param,
                                    sNodeType * method_generics_types);
int is_method_param_name(char * name);
void native_method_init();
void native_method_final();
fNativeMethod get_native_method(char * path, char * * fun_name);
void put_fun_to_hash_for_native_method(char * path,
                                       char * fun_name,
                                       fNativeMethod fun);
void entry_exception_object_with_class_name(CLVALUE * * stack_ptr,
                                            CLVALUE * stack,
                                            int var_num,
                                            sVMInfo * info,
                                            char * class_name,
                                            char * msg, ...);
void entry_exception_object(CLObject exception, sVMInfo * info);
void show_exception_message(char * message);
void entry_exception_object_with_class_name2(CLVALUE * * stack_ptr,
                                             CLVALUE * stack,
                                             int var_num,
                                             sVMInfo * info,
                                             char * class_name,
                                             char * msg);
int compile_method(sCLMethod * method,
                   sParserParam * params,
                   int num_params,
                   sParserInfo * info,
                   sCompileInfo * cinfo);
int is_void_type(sCLType * cl_type, sCLClass * klass);
sCLClass * get_class_from_cl_type(sCLType * cl_type,
                                  sCLClass * klass);
int is_this_class_with_class_name(sCLClass * klass,
                                  char * class_name);
struct sCLHeapMemStruct {
    int mSize;
    sCLClass * mClass;
    char * mType;
    int mArrayNum;
    void * mMem;
};
typedef struct sCLHeapMemStruct sCLHeapMem;
void heap_init(int heap_size, int size_hadles);
void heap_final();
CLObject alloc_heap_mem(int size, sCLClass * klass, int array_num);
sCLHeapMem * get_object_pointer(CLObject obj);
void show_heap(sVMInfo * info);
void mark_object(CLObject obj, unsigned char * mark_flg);
int is_valid_object(CLObject obj);
struct sCLModuleStruct {
    int mModified;
    char mName[64 + 1];
    sBuf mBody;
    char mSName[4096];
    int mSLine;
};
typedef struct sCLModuleStruct sCLModule;
void module_init();
void module_final();
sCLModule * create_module(char * module_name,
                          char * sname,
                          int sline);
void unload_module(char * module_name);
void append_character_to_module(sCLModule * self, char c);
void append_str_to_module(sCLModule * self, char * str);
sCLModule * get_module(char * module_name);
char * get_module_body(sCLModule * module);
void write_all_modified_modules();
void this_module_is_modified(sCLModule * self);
int load_module_from_file(sCLModule * * self, char * module_name);
struct sCLObjectStruct {
    int mSize;
    sCLClass * mClass;
    char * mType;
    union {
        int mArrayNum; int mNumFields;
    };
    CLVALUE mFields[32];
};
typedef struct sCLObjectStruct sCLObject;
CLObject create_object(sCLClass * klass, char * type);
int free_object(CLObject self);
void object_mark_fun(CLObject self, unsigned char * mark_flg);
int object_implements_interface(CLObject object,
                                sCLClass * interface);
CLObject create_array_object(sCLClass * klass, int array_num);
void array_mark_fun(CLObject self, unsigned char * mark_flg);
void free_array(CLObject self);
CLObject create_hash_object(char * type_name);
int initialize_hash_object(CLObject hash_object,
                           int num_elements,
                           CLObject * keys,
                           CLObject * items,
                           CLVALUE * stack,
                           int var_num,
                           CLVALUE * * stack_ptr,
                           sVMInfo * info,
                           sCLClass * class_keys,
                           sCLClass * class_items);
struct sBlockObjectStruct {
    int mSize;
    sCLClass * mClass;
    char * mType;
    int mArrayNum;
    sByteCode mCodes;
    sConst mConstant;
    CLVALUE * mParentStack;
    int mParentVarNum;
    int mBlockVarNum;
    sCLStack * mStackID;
    int mLambda;
};
typedef struct sBlockObjectStruct sBlockObject;
CLObject create_block_object(sByteCode * codes,
                             sConst * constant,
                             CLVALUE * parent_stack,
                             int parent_var_num,
                             int block_var_num,
                             sCLStack * stack_id,
                             int lambda);
struct sRegexObjectStruct {
    int mSize;
    sCLClass * mClass;
    char * mType;
    int mArrayNum;
    pcre * mRegex;
    char * mRegexString;
    int mGlobal;
    int mIgnoreCase;
    int mMultiline;
    int mExtended;
    int mDotAll;
    int mAnchored;
    int mDollarEndOnly;
    int mUngreedy;
};
typedef struct sRegexObjectStruct sRegexObject;
CLObject create_regex_object(char * regex,
                             int global,
                             int ignore_case,
                             int multiline,
                             int extended,
                             int dotall,
                             int anchored,
                             int dollar_endonly,
                             int ungreedy);
void regex_free_fun(CLObject obj);
int regex_equals(CLObject left, CLObject right);
CLObject create_string_object(char * str);
CLObject create_buffer_object(char * buffer, size_t size);
CLObject create_path_object(char * path);
CLObject create_string_from_two_strings(CLObject left,
                                        CLObject right);
int get_length_from_string_object(CLObject str);
CLVALUE * get_str_array_from_string_object(CLObject str);
CLObject create_integer(int value);
CLObject create_uinteger(unsigned int value);
CLObject create_byte(char value);
CLObject create_ubyte(unsigned char value);
CLObject create_short(short value);
CLObject create_ushort(unsigned short value);
CLObject create_long(long long value);
CLObject create_ulong(unsigned long long value);
CLObject create_float(float value);
CLObject create_double(double value);
CLObject create_pointer(char * value);
CLObject create_char(wchar_t value);
CLObject create_bool(int value);
int System_exit(CLVALUE * * stack_ptr,
                CLVALUE * lvar,
                sVMInfo * info);
int System_assert(CLVALUE * * stack_ptr,
                  CLVALUE * lvar,
                  sVMInfo * info);
int System_malloc(CLVALUE * * stack_ptr,
                  CLVALUE * lvar,
                  sVMInfo * info);
int System_realloc(CLVALUE * * stack_ptr,
                   CLVALUE * lvar,
                   sVMInfo * info);
int System_calloc(CLVALUE * * stack_ptr,
                  CLVALUE * lvar,
                  sVMInfo * info);
int System_free(CLVALUE * * stack_ptr,
                CLVALUE * lvar,
                sVMInfo * info);
int System_strlen(CLVALUE * * stack_ptr,
                  CLVALUE * lvar,
                  sVMInfo * info);
int System_strlen2(CLVALUE * * stack_ptr,
                   CLVALUE * lvar,
                   sVMInfo * info);
int System_strcpy(CLVALUE * * stack_ptr,
                  CLVALUE * lvar,
                  sVMInfo * info);
int System_strncpy(CLVALUE * * stack_ptr,
                   CLVALUE * lvar,
                   sVMInfo * info);
int System_strdup(CLVALUE * * stack_ptr,
                  CLVALUE * lvar,
                  sVMInfo * info);
int System_print(CLVALUE * * stack_ptr,
                 CLVALUE * lvar,
                 sVMInfo * info);
int System_println(CLVALUE * * stack_ptr,
                   CLVALUE * lvar,
                   sVMInfo * info);
int System_printlnToError(CLVALUE * * stack_ptr,
                          CLVALUE * lvar,
                          sVMInfo * info);
int System_printToError(CLVALUE * * stack_ptr,
                        CLVALUE * lvar,
                        sVMInfo * info);
int System_sleep(CLVALUE * * stack_ptr,
                 CLVALUE * lvar,
                 sVMInfo * info);
int System_pcre_exec(CLVALUE * * stack_ptr,
                     CLVALUE * lvar,
                     sVMInfo * info);
int System_sprintf(CLVALUE * * stack_ptr,
                   CLVALUE * lvar,
                   sVMInfo * info);
int System_memcpy(CLVALUE * * stack_ptr,
                  CLVALUE * lvar,
                  sVMInfo * info);
int System_memcmp(CLVALUE * * stack_ptr,
                  CLVALUE * lvar,
                  sVMInfo * info);
int System_mbstowcs(CLVALUE * * stack_ptr,
                    CLVALUE * lvar,
                    sVMInfo * info);
int System_wcstombs(CLVALUE * * stack_ptr,
                    CLVALUE * lvar,
                    sVMInfo * info);
int System_atof(CLVALUE * * stack_ptr,
                CLVALUE * lvar,
                sVMInfo * info);
int System_atoi(CLVALUE * * stack_ptr,
                CLVALUE * lvar,
                sVMInfo * info);
int System_strtod(CLVALUE * * stack_ptr,
                  CLVALUE * lvar,
                  sVMInfo * info);
int System_strcmp(CLVALUE * * stack_ptr,
                  CLVALUE * lvar,
                  sVMInfo * info);
int System_strcasecmp(CLVALUE * * stack_ptr,
                      CLVALUE * lvar,
                      sVMInfo * info);
int System_strtol(CLVALUE * * stack_ptr,
                  CLVALUE * lvar,
                  sVMInfo * info);
int System_strtoul(CLVALUE * * stack_ptr,
                   CLVALUE * lvar,
                   sVMInfo * info);
int System_srand(CLVALUE * * stack_ptr,
                 CLVALUE * lvar,
                 sVMInfo * info);
int System_rand(CLVALUE * * stack_ptr,
                CLVALUE * lvar,
                sVMInfo * info);
int System_open(CLVALUE * * stack_ptr,
                CLVALUE * lvar,
                sVMInfo * info);
int System_close(CLVALUE * * stack_ptr,
                 CLVALUE * lvar,
                 sVMInfo * info);
int System_initialize_string_system(CLVALUE * * stack_ptr,
                                    CLVALUE * lvar,
                                    sVMInfo * info);
int System_initialize_file_system(CLVALUE * * stack_ptr,
                                  CLVALUE * lvar,
                                  sVMInfo * info);
int System_read(CLVALUE * * stack_ptr,
                CLVALUE * lvar,
                sVMInfo * info);
int System_write(CLVALUE * * stack_ptr,
                 CLVALUE * lvar,
                 sVMInfo * info);
int System_time(CLVALUE * * stack_ptr,
                CLVALUE * lvar,
                sVMInfo * info);
int System_localtime(CLVALUE * * stack_ptr,
                     CLVALUE * lvar,
                     sVMInfo * info);
int System_mktime(CLVALUE * * stack_ptr,
                  CLVALUE * lvar,
                  sVMInfo * info);
int System_stat(CLVALUE * * stack_ptr,
                CLVALUE * lvar,
                sVMInfo * info);
int System_lstat(CLVALUE * * stack_ptr,
                 CLVALUE * lvar,
                 sVMInfo * info);
int System_basename(CLVALUE * * stack_ptr,
                    CLVALUE * lvar,
                    sVMInfo * info);
int System_dirname(CLVALUE * * stack_ptr,
                   CLVALUE * lvar,
                   sVMInfo * info);
int System_realpath(CLVALUE * * stack_ptr,
                    CLVALUE * lvar,
                    sVMInfo * info);
int System_opendir(CLVALUE * * stack_ptr,
                   CLVALUE * lvar,
                   sVMInfo * info);
int System_readdir(CLVALUE * * stack_ptr,
                   CLVALUE * lvar,
                   sVMInfo * info);
int System_closedir(CLVALUE * * stack_ptr,
                    CLVALUE * lvar,
                    sVMInfo * info);
int System_initialize_command_system(CLVALUE * * stack_ptr,
                                     CLVALUE * lvar,
                                     sVMInfo * info);
int System_pipe(CLVALUE * * stack_ptr,
                CLVALUE * lvar,
                sVMInfo * info);
int System_fork(CLVALUE * * stack_ptr,
                CLVALUE * lvar,
                sVMInfo * info);
int System_dup2(CLVALUE * * stack_ptr,
                CLVALUE * lvar,
                sVMInfo * info);
int System_execvp(CLVALUE * * stack_ptr,
                  CLVALUE * lvar,
                  sVMInfo * info);
int System_execv(CLVALUE * * stack_ptr,
                 CLVALUE * lvar,
                 sVMInfo * info);
int System_waitpid(CLVALUE * * stack_ptr,
                   CLVALUE * lvar,
                   sVMInfo * info);
int System_WIFEXITED(CLVALUE * * stack_ptr,
                     CLVALUE * lvar,
                     sVMInfo * info);
int System_WEXITSTATUS(CLVALUE * * stack_ptr,
                       CLVALUE * lvar,
                       sVMInfo * info);
int System_WIFSIGNALED(CLVALUE * * stack_ptr,
                       CLVALUE * lvar,
                       sVMInfo * info);
int System_WTERMSIG(CLVALUE * * stack_ptr,
                    CLVALUE * lvar,
                    sVMInfo * info);
int System_WCOREDUMP(CLVALUE * * stack_ptr,
                     CLVALUE * lvar,
                     sVMInfo * info);
int System_WIFSTOPPED(CLVALUE * * stack_ptr,
                      CLVALUE * lvar,
                      sVMInfo * info);
int System_WSTOPSIG(CLVALUE * * stack_ptr,
                    CLVALUE * lvar,
                    sVMInfo * info);
int System_WIFCONTINUED(CLVALUE * * stack_ptr,
                        CLVALUE * lvar,
                        sVMInfo * info);
int System_getpid(CLVALUE * * stack_ptr,
                  CLVALUE * lvar,
                  sVMInfo * info);
int System_setpgid(CLVALUE * * stack_ptr,
                   CLVALUE * lvar,
                   sVMInfo * info);
int System_kill(CLVALUE * * stack_ptr,
                CLVALUE * lvar,
                sVMInfo * info);
int System_tcsetpgrp(CLVALUE * * stack_ptr,
                     CLVALUE * lvar,
                     sVMInfo * info);
int System_tcgetattr(CLVALUE * * stack_ptr,
                     CLVALUE * lvar,
                     sVMInfo * info);
int System_tcsetattr(CLVALUE * * stack_ptr,
                     CLVALUE * lvar,
                     sVMInfo * info);
int System_tcsendbreak(CLVALUE * * stack_ptr,
                       CLVALUE * lvar,
                       sVMInfo * info);
int System_tcdrain(CLVALUE * * stack_ptr,
                   CLVALUE * lvar,
                   sVMInfo * info);
int System_tcflush(CLVALUE * * stack_ptr,
                   CLVALUE * lvar,
                   sVMInfo * info);
int System_tcflow(CLVALUE * * stack_ptr,
                  CLVALUE * lvar,
                  sVMInfo * info);
int System_cfmakeraw(CLVALUE * * stack_ptr,
                     CLVALUE * lvar,
                     sVMInfo * info);
int System_cfgetispeed(CLVALUE * * stack_ptr,
                       CLVALUE * lvar,
                       sVMInfo * info);
int System_cfgetospeed(CLVALUE * * stack_ptr,
                       CLVALUE * lvar,
                       sVMInfo * info);
int System_cfsetispeed(CLVALUE * * stack_ptr,
                       CLVALUE * lvar,
                       sVMInfo * info);
int System_cfsetospeed(CLVALUE * * stack_ptr,
                       CLVALUE * lvar,
                       sVMInfo * info);
int System_cfsetspeed(CLVALUE * * stack_ptr,
                      CLVALUE * lvar,
                      sVMInfo * info);
int System_chmod(CLVALUE * * stack_ptr,
                 CLVALUE * lvar,
                 sVMInfo * info);
int System_lchmod(CLVALUE * * stack_ptr,
                  CLVALUE * lvar,
                  sVMInfo * info);
int System_fchmod(CLVALUE * * stack_ptr,
                  CLVALUE * lvar,
                  sVMInfo * info);
int System_chown(CLVALUE * * stack_ptr,
                 CLVALUE * lvar,
                 sVMInfo * info);
int System_lchown(CLVALUE * * stack_ptr,
                  CLVALUE * lvar,
                  sVMInfo * info);
int System_fchown(CLVALUE * * stack_ptr,
                  CLVALUE * lvar,
                  sVMInfo * info);
int System_unlink(CLVALUE * * stack_ptr,
                  CLVALUE * lvar,
                  sVMInfo * info);
int System_access(CLVALUE * * stack_ptr,
                  CLVALUE * lvar,
                  sVMInfo * info);
int System_utime(CLVALUE * * stack_ptr,
                 CLVALUE * lvar,
                 sVMInfo * info);
int System_fnmatch(CLVALUE * * stack_ptr,
                   CLVALUE * lvar,
                   sVMInfo * info);
int System_link(CLVALUE * * stack_ptr,
                CLVALUE * lvar,
                sVMInfo * info);
int System_symlink(CLVALUE * * stack_ptr,
                   CLVALUE * lvar,
                   sVMInfo * info);
int System_readlink(CLVALUE * * stack_ptr,
                    CLVALUE * lvar,
                    sVMInfo * info);
int System_rename(CLVALUE * * stack_ptr,
                  CLVALUE * lvar,
                  sVMInfo * info);
int System_truncate(CLVALUE * * stack_ptr,
                    CLVALUE * lvar,
                    sVMInfo * info);
int System_ftruncate(CLVALUE * * stack_ptr,
                     CLVALUE * lvar,
                     sVMInfo * info);
int System_chdir(CLVALUE * * stack_ptr,
                 CLVALUE * lvar,
                 sVMInfo * info);
int System_fchdir(CLVALUE * * stack_ptr,
                  CLVALUE * lvar,
                  sVMInfo * info);
int System_rmdir(CLVALUE * * stack_ptr,
                 CLVALUE * lvar,
                 sVMInfo * info);
int System_mkdir(CLVALUE * * stack_ptr,
                 CLVALUE * lvar,
                 sVMInfo * info);
int System_clock_getres(CLVALUE * * stack_ptr,
                        CLVALUE * lvar,
                        sVMInfo * info);
int System_clock_gettime(CLVALUE * * stack_ptr,
                         CLVALUE * lvar,
                         sVMInfo * info);
int System_clock_settime(CLVALUE * * stack_ptr,
                         CLVALUE * lvar,
                         sVMInfo * info);
int System_system(CLVALUE * * stack_ptr,
                  CLVALUE * lvar,
                  sVMInfo * info);
int System_getenv(CLVALUE * * stack_ptr,
                  CLVALUE * lvar,
                  sVMInfo * info);
int System_setenv(CLVALUE * * stack_ptr,
                  CLVALUE * lvar,
                  sVMInfo * info);
int System_unsetenv(CLVALUE * * stack_ptr,
                    CLVALUE * lvar,
                    sVMInfo * info);
int System_dlopen(CLVALUE * * stack_ptr,
                  CLVALUE * lvar,
                  sVMInfo * info);
int System_dlclose(CLVALUE * * stack_ptr,
                   CLVALUE * lvar,
                   sVMInfo * info);
int System_dlsym(CLVALUE * * stack_ptr,
                 CLVALUE * lvar,
                 sVMInfo * info);
int System_put_fun_to_hash_for_native_method(CLVALUE * * stack_ptr,
                                             CLVALUE * lvar,
                                             sVMInfo * info);
void alignment(unsigned int * size);
wchar_t * string_object_to_wchar_array(CLObject string_object);
char * string_object_to_char_array(CLObject string_object);
CLVALUE * get_element_from_array(CLObject array, int index);
CLVALUE * get_element_from_Array(CLObject array, int index);
int get_element_number_from_Array(CLObject array);
char get_value_from_Byte(CLObject object);
unsigned char get_value_from_UByte(CLObject object);
short get_value_from_Short(CLObject object);
unsigned short get_value_from_UShort(CLObject object);
int get_value_from_Integer(CLObject object);
unsigned int get_value_from_UInteger(CLObject object);
long long get_value_from_Long(CLObject object);
unsigned long long get_value_from_ULong(CLObject object);
wchar_t get_value_from_Char(CLObject object);
float get_value_from_Float(CLObject object);
double get_value_from_Double(CLObject object);
int get_value_from_Bool(CLObject object);
char * get_value_from_Pointer(CLObject object);
sCLClass * get_class_from_object(CLObject object);
void * get_pointer_from_buffer_object(CLObject buffer);
size_t get_size_from_buffer_object(CLObject buffer);
CLObject * list_to_array(CLObject list, int * num_elements);
void clover_termios_to_c_termios(CLObject terminfo_object,
                                 struct termios * terminfo_value);
void c_termios_to_clover_termios(struct termios * terminfo_value,
                                 CLObject terminfo_object);
CLObject create_list_object(char * type_name);
int initialize_list_object(CLObject list_object,
                           int num_elements,
                           CLObject * items,
                           CLVALUE * stack,
                           int var_num,
                           CLVALUE * * stack_ptr,
                           sVMInfo * info,
                           sCLClass * class_items);
CLObject create_sortable_list_object(char * type_name);
int initialize_sortable_list_object(CLObject list_object,
                                    int num_elements,
                                    CLObject * items,
                                    CLVALUE * stack,
                                    int var_num,
                                    CLVALUE * * stack_ptr,
                                    sVMInfo * info,
                                    sCLClass * class_items);
CLObject create_equalable_list_object(char * type_name);
int initialize_equalable_list_object(CLObject list_object,
                                     int num_elements,
                                     CLObject * items,
                                     CLVALUE * stack,
                                     int var_num,
                                     CLVALUE * * stack_ptr,
                                     sVMInfo * info,
                                     sCLClass * class_items);
CLObject create_tuple_object(int num_elements, char * type_name);
int initialize_tuple_object(CLObject tuple_object,
                            int num_elements,
                            CLObject * items,
                            CLVALUE * stack,
                            int var_num,
                            CLVALUE * * stack_ptr,
                            sVMInfo * info);
CLObject create_carray_object(char * type_name);
CLObject create_equalable_carray_object(char * type_name);
CLObject create_sortable_carray_object(char * type_name);
CLObject create_carray_object_with_elements(int num_elements,
                                            CLObject * elements);
int initialize_carray_object(CLObject array_object,
                             int num_elements,
                             CLObject * items,
                             CLVALUE * stack,
                             int var_num,
                             CLVALUE * * stack_ptr,
                             sVMInfo * info,
                             sCLClass * class_items);
CLObject create_equalable_carray_object_with_elements(int num_elements,
                                                      CLObject * elements);
int initialize_equalable_carray_object(CLObject array_object,
                                       int num_elements,
                                       CLObject * items,
                                       CLVALUE * stack,
                                       int var_num,
                                       CLVALUE * * stack_ptr,
                                       sVMInfo * info,
                                       sCLClass * class_items);
CLObject create_sortable_carray_object_with_elements(int num_elements,
                                                     CLObject * elements);
int initialize_sortable_carray_object(CLObject array_object,
                                      int num_elements,
                                      CLObject * items,
                                      CLVALUE * stack,
                                      int var_num,
                                      CLVALUE * * stack_ptr,
                                      sVMInfo * info,
                                      sCLClass * class_items);
int utf8_index_to_utf32_index(char * str, int utf8index);
int utf32_index_to_utf8_index(char * str, int utf32index);
int Clover_load(CLVALUE * * stack_ptr,
                CLVALUE * lvar,
                sVMInfo * info);
int jit(sByteCode * code,
        sConst * constant,
        CLVALUE * stack,
        int var_num,
        sCLClass * klass,
        sCLMethod * method,
        sVMInfo * info,
        CLVALUE * * stack_ptr);
void jit_init();
void jit_final();
int compile_jit_method(sCLClass * klass, sCLMethod * method);
int CLParser_initialize(CLVALUE * * stack_ptr,
                        CLVALUE * lvar,
                        sVMInfo * info);
typedef int Function() __attribute__((deprecated));
typedef void VFunction() __attribute__((deprecated));
typedef char * CPFunction() __attribute__((deprecated));
typedef char * * CPPFunction() __attribute__((deprecated));
typedef int rl_command_func_t(int, int);
typedef char * rl_compentry_func_t(const char *, int);
typedef char * * rl_completion_func_t(const char *, int, int);
typedef char * rl_quote_func_t(char *, int, char *);
typedef char * rl_dequote_func_t(char *, int);
typedef int rl_compignore_func_t(char * *);
typedef void rl_compdisp_func_t(char * *, int, int);
typedef int rl_hook_func_t(void);
typedef int rl_getc_func_t(FILE *);
typedef int rl_linebuf_func_t(char *, int);
typedef int rl_intfunc_t(int);
typedef int rl_icpfunc_t(char *);
typedef int rl_icppfunc_t(char * *);
typedef void rl_voidfunc_t(void);
typedef void rl_vintfunc_t(int);
typedef void rl_vcpfunc_t(char *);
typedef void rl_vcppfunc_t(char * *);
typedef char * rl_cpvfunc_t(void);
typedef char * rl_cpifunc_t(int);
typedef char * rl_cpcpfunc_t(char *);
typedef char * rl_cpcppfunc_t(char * *);
typedef struct _keymap_entry {
            char type; rl_command_func_t * function;
        } KEYMAP_ENTRY;
typedef KEYMAP_ENTRY KEYMAP_ENTRY_ARRAY[257];
typedef KEYMAP_ENTRY * Keymap;
extern KEYMAP_ENTRY_ARRAY emacs_standard_keymap, emacs_meta_keymap, emacs_ctlx_keymap;
extern KEYMAP_ENTRY_ARRAY vi_insertion_keymap, vi_movement_keymap;
extern Keymap rl_make_bare_keymap(void);
extern Keymap rl_copy_keymap(Keymap);
extern Keymap rl_make_keymap(void);
extern void rl_discard_keymap(Keymap);
extern Keymap rl_get_keymap_by_name(const char *);
extern Keymap rl_get_keymap(void);
extern void rl_set_keymap(Keymap);
typedef char * tilde_hook_func_t(char *);
extern tilde_hook_func_t * tilde_expansion_preexpansion_hook;
extern tilde_hook_func_t * tilde_expansion_failure_hook;
extern char * * tilde_additional_prefixes;
extern char * * tilde_additional_suffixes;
extern char * tilde_expand(const char *);
extern char * tilde_expand_word(const char *);
extern char * tilde_find_word(const char *, int, int *);
enum undo_code {
    UNDO_DELETE, UNDO_INSERT, UNDO_BEGIN, UNDO_END
};
typedef struct undo_list {
            struct undo_list * next;
            int start, end;
            char * text;
            enum undo_code what;
        } UNDO_LIST;
extern UNDO_LIST * rl_undo_list;
typedef struct _funmap {
            const char * name; rl_command_func_t * function;
        } FUNMAP;
extern FUNMAP * * funmap;
extern int rl_digit_argument(int, int);
extern int rl_universal_argument(int, int);
extern int rl_forward_byte(int, int);
extern int rl_forward_char(int, int);
extern int rl_forward(int, int);
extern int rl_backward_byte(int, int);
extern int rl_backward_char(int, int);
extern int rl_backward(int, int);
extern int rl_beg_of_line(int, int);
extern int rl_end_of_line(int, int);
extern int rl_forward_word(int, int);
extern int rl_backward_word(int, int);
extern int rl_refresh_line(int, int);
extern int rl_clear_screen(int, int);
extern int rl_skip_csi_sequence(int, int);
extern int rl_arrow_keys(int, int);
extern int rl_insert(int, int);
extern int rl_quoted_insert(int, int);
extern int rl_tab_insert(int, int);
extern int rl_newline(int, int);
extern int rl_do_lowercase_version(int, int);
extern int rl_rubout(int, int);
extern int rl_delete(int, int);
extern int rl_rubout_or_delete(int, int);
extern int rl_delete_horizontal_space(int, int);
extern int rl_delete_or_show_completions(int, int);
extern int rl_insert_comment(int, int);
extern int rl_upcase_word(int, int);
extern int rl_downcase_word(int, int);
extern int rl_capitalize_word(int, int);
extern int rl_transpose_words(int, int);
extern int rl_transpose_chars(int, int);
extern int rl_char_search(int, int);
extern int rl_backward_char_search(int, int);
extern int rl_beginning_of_history(int, int);
extern int rl_end_of_history(int, int);
extern int rl_get_next_history(int, int);
extern int rl_get_previous_history(int, int);
extern int rl_set_mark(int, int);
extern int rl_exchange_point_and_mark(int, int);
extern int rl_vi_editing_mode(int, int);
extern int rl_emacs_editing_mode(int, int);
extern int rl_overwrite_mode(int, int);
extern int rl_re_read_init_file(int, int);
extern int rl_dump_functions(int, int);
extern int rl_dump_macros(int, int);
extern int rl_dump_variables(int, int);
extern int rl_complete(int, int);
extern int rl_possible_completions(int, int);
extern int rl_insert_completions(int, int);
extern int rl_old_menu_complete(int, int);
extern int rl_menu_complete(int, int);
extern int rl_backward_menu_complete(int, int);
extern int rl_kill_word(int, int);
extern int rl_backward_kill_word(int, int);
extern int rl_kill_line(int, int);
extern int rl_backward_kill_line(int, int);
extern int rl_kill_full_line(int, int);
extern int rl_unix_word_rubout(int, int);
extern int rl_unix_filename_rubout(int, int);
extern int rl_unix_line_discard(int, int);
extern int rl_copy_region_to_kill(int, int);
extern int rl_kill_region(int, int);
extern int rl_copy_forward_word(int, int);
extern int rl_copy_backward_word(int, int);
extern int rl_yank(int, int);
extern int rl_yank_pop(int, int);
extern int rl_yank_nth_arg(int, int);
extern int rl_yank_last_arg(int, int);
extern int rl_bracketed_paste_begin(int, int);
extern int rl_reverse_search_history(int, int);
extern int rl_forward_search_history(int, int);
extern int rl_start_kbd_macro(int, int);
extern int rl_end_kbd_macro(int, int);
extern int rl_call_last_kbd_macro(int, int);
extern int rl_print_last_kbd_macro(int, int);
extern int rl_revert_line(int, int);
extern int rl_undo_command(int, int);
extern int rl_tilde_expand(int, int);
extern int rl_restart_output(int, int);
extern int rl_stop_output(int, int);
extern int rl_abort(int, int);
extern int rl_tty_status(int, int);
extern int rl_history_search_forward(int, int);
extern int rl_history_search_backward(int, int);
extern int rl_history_substr_search_forward(int, int);
extern int rl_history_substr_search_backward(int, int);
extern int rl_noninc_forward_search(int, int);
extern int rl_noninc_reverse_search(int, int);
extern int rl_noninc_forward_search_again(int, int);
extern int rl_noninc_reverse_search_again(int, int);
extern int rl_insert_close(int, int);
extern void rl_callback_handler_install(const char *,
                                        rl_vcpfunc_t *);
extern void rl_callback_read_char(void);
extern void rl_callback_handler_remove(void);
extern void rl_callback_sigcleanup(void);
extern int rl_vi_redo(int, int);
extern int rl_vi_undo(int, int);
extern int rl_vi_yank_arg(int, int);
extern int rl_vi_fetch_history(int, int);
extern int rl_vi_search_again(int, int);
extern int rl_vi_search(int, int);
extern int rl_vi_complete(int, int);
extern int rl_vi_tilde_expand(int, int);
extern int rl_vi_prev_word(int, int);
extern int rl_vi_next_word(int, int);
extern int rl_vi_end_word(int, int);
extern int rl_vi_insert_beg(int, int);
extern int rl_vi_append_mode(int, int);
extern int rl_vi_append_eol(int, int);
extern int rl_vi_eof_maybe(int, int);
extern int rl_vi_insertion_mode(int, int);
extern int rl_vi_insert_mode(int, int);
extern int rl_vi_movement_mode(int, int);
extern int rl_vi_arg_digit(int, int);
extern int rl_vi_change_case(int, int);
extern int rl_vi_put(int, int);
extern int rl_vi_column(int, int);
extern int rl_vi_delete_to(int, int);
extern int rl_vi_change_to(int, int);
extern int rl_vi_yank_to(int, int);
extern int rl_vi_yank_pop(int, int);
extern int rl_vi_rubout(int, int);
extern int rl_vi_delete(int, int);
extern int rl_vi_back_to_indent(int, int);
extern int rl_vi_unix_word_rubout(int, int);
extern int rl_vi_first_print(int, int);
extern int rl_vi_char_search(int, int);
extern int rl_vi_match(int, int);
extern int rl_vi_change_char(int, int);
extern int rl_vi_subst(int, int);
extern int rl_vi_overstrike(int, int);
extern int rl_vi_overstrike_delete(int, int);
extern int rl_vi_replace(int, int);
extern int rl_vi_set_mark(int, int);
extern int rl_vi_goto_mark(int, int);
extern int rl_vi_check(void);
extern int rl_vi_domove(int, int *);
extern int rl_vi_bracktype(int);
extern void rl_vi_start_inserting(int, int, int);
extern int rl_vi_fWord(int, int);
extern int rl_vi_bWord(int, int);
extern int rl_vi_eWord(int, int);
extern int rl_vi_fword(int, int);
extern int rl_vi_bword(int, int);
extern int rl_vi_eword(int, int);
extern char * readline(const char *);
extern int rl_set_prompt(const char *);
extern int rl_expand_prompt(char *);
extern int rl_initialize(void);
extern int rl_discard_argument(void);
extern int rl_add_defun(const char *, rl_command_func_t *, int);
extern int rl_bind_key(int, rl_command_func_t *);
extern int rl_bind_key_in_map(int, rl_command_func_t *, Keymap);
extern int rl_unbind_key(int);
extern int rl_unbind_key_in_map(int, Keymap);
extern int rl_bind_key_if_unbound(int, rl_command_func_t *);
extern int rl_bind_key_if_unbound_in_map(int,
                                         rl_command_func_t *,
                                         Keymap);
extern int rl_unbind_function_in_map(rl_command_func_t *, Keymap);
extern int rl_unbind_command_in_map(const char *, Keymap);
extern int rl_bind_keyseq(const char *, rl_command_func_t *);
extern int rl_bind_keyseq_in_map(const char *,
                                 rl_command_func_t *,
                                 Keymap);
extern int rl_bind_keyseq_if_unbound(const char *,
                                     rl_command_func_t *);
extern int rl_bind_keyseq_if_unbound_in_map(const char *,
                                            rl_command_func_t *,
                                            Keymap);
extern int rl_generic_bind(int, const char *, char *, Keymap);
extern char * rl_variable_value(const char *);
extern int rl_variable_bind(const char *, const char *);
extern int rl_set_key(const char *, rl_command_func_t *, Keymap);
extern int rl_macro_bind(const char *, const char *, Keymap);
extern int rl_translate_keyseq(const char *, char *, int *);
extern char * rl_untranslate_keyseq(int);
extern rl_command_func_t * rl_named_function(const char *);
extern rl_command_func_t * rl_function_of_keyseq(const char *,
                                                 Keymap,
                                                 int *);
extern void rl_list_funmap_names(void);
extern char * * rl_invoking_keyseqs_in_map(rl_command_func_t *,
                                           Keymap);
extern char * * rl_invoking_keyseqs(rl_command_func_t *);
extern void rl_function_dumper(int);
extern void rl_macro_dumper(int);
extern void rl_variable_dumper(int);
extern int rl_read_init_file(const char *);
extern int rl_parse_and_bind(char *);
extern Keymap rl_make_bare_keymap(void);
extern Keymap rl_copy_keymap(Keymap);
extern Keymap rl_make_keymap(void);
extern void rl_discard_keymap(Keymap);
extern void rl_free_keymap(Keymap);
extern Keymap rl_get_keymap_by_name(const char *);
extern char * rl_get_keymap_name(Keymap);
extern void rl_set_keymap(Keymap);
extern Keymap rl_get_keymap(void);
extern void rl_set_keymap_from_edit_mode(void);
extern char * rl_get_keymap_name_from_edit_mode(void);
extern int rl_add_funmap_entry(const char *, rl_command_func_t *);
extern const char * * rl_funmap_names(void);
extern void rl_initialize_funmap(void);
extern void rl_push_macro_input(char *);
extern void rl_add_undo(enum undo_code, int, int, char *);
extern void rl_free_undo_list(void);
extern int rl_do_undo(void);
extern int rl_begin_undo_group(void);
extern int rl_end_undo_group(void);
extern int rl_modifying(int, int);
extern void rl_redisplay(void);
extern int rl_on_new_line(void);
extern int rl_on_new_line_with_prompt(void);
extern int rl_forced_update_display(void);
extern int rl_clear_visible_line(void);
extern int rl_clear_message(void);
extern int rl_reset_line_state(void);
extern int rl_crlf(void);
extern int rl_message();
extern int rl_show_char(int);
extern int rl_character_len(int, int);
extern void rl_redraw_prompt_last_line(void);
extern void rl_save_prompt(void);
extern void rl_restore_prompt(void);
extern void rl_replace_line(const char *, int);
extern int rl_insert_text(const char *);
extern int rl_delete_text(int, int);
extern int rl_kill_text(int, int);
extern char * rl_copy_text(int, int);
extern void rl_prep_terminal(int);
extern void rl_deprep_terminal(void);
extern void rl_tty_set_default_bindings(Keymap);
extern void rl_tty_unset_default_bindings(Keymap);
extern int rl_reset_terminal(const char *);
extern void rl_resize_terminal(void);
extern void rl_set_screen_size(int, int);
extern void rl_get_screen_size(int *, int *);
extern void rl_reset_screen_size(void);
extern char * rl_get_termcap(const char *);
extern int rl_stuff_char(int);
extern int rl_execute_next(int);
extern int rl_clear_pending_input(void);
extern int rl_read_key(void);
extern int rl_getc(FILE *);
extern int rl_set_keyboard_input_timeout(int);
extern void rl_extend_line_buffer(int);
extern int rl_ding(void);
extern int rl_alphabetic(int);
extern void rl_free(void *);
extern int rl_set_signals(void);
extern int rl_clear_signals(void);
extern void rl_cleanup_after_signal(void);
extern void rl_reset_after_signal(void);
extern void rl_free_line_state(void);
extern int rl_pending_signal(void);
extern void rl_echo_signal_char(int);
extern int rl_set_paren_blink_timeout(int);
extern void rl_clear_history(void);
extern int rl_maybe_save_line(void);
extern int rl_maybe_unsave_line(void);
extern int rl_maybe_replace_line(void);
extern int rl_complete_internal(int);
extern void rl_display_match_list(char * *, int, int);
extern char * * rl_completion_matches(const char *,
                                      rl_compentry_func_t *);
extern char * rl_username_completion_function(const char *, int);
extern char * rl_filename_completion_function(const char *, int);
extern int rl_completion_mode(rl_command_func_t *);
extern const char * rl_library_version;
extern int rl_readline_version;
extern int rl_gnu_readline_p;
extern unsigned long rl_readline_state;
extern int rl_editing_mode;
extern int rl_insert_mode;
extern const char * rl_readline_name;
extern char * rl_prompt;
extern char * rl_display_prompt;
extern char * rl_line_buffer;
extern int rl_point;
extern int rl_end;
extern int rl_mark;
extern int rl_done;
extern int rl_pending_input;
extern int rl_dispatching;
extern int rl_explicit_arg;
extern int rl_numeric_arg;
extern rl_command_func_t * rl_last_func;
extern const char * rl_terminal_name;
extern FILE * rl_instream;
extern FILE * rl_outstream;
extern int rl_prefer_env_winsize;
extern rl_hook_func_t * rl_startup_hook;
extern rl_hook_func_t * rl_pre_input_hook;
extern rl_hook_func_t * rl_event_hook;
extern rl_hook_func_t * rl_signal_event_hook;
extern rl_hook_func_t * rl_input_available_hook;
extern rl_getc_func_t * rl_getc_function;
extern rl_voidfunc_t * rl_redisplay_function;
extern rl_vintfunc_t * rl_prep_term_function;
extern rl_voidfunc_t * rl_deprep_term_function;
extern Keymap rl_executing_keymap;
extern Keymap rl_binding_keymap;
extern int rl_executing_key;
extern char * rl_executing_keyseq;
extern int rl_key_sequence_length;
extern int rl_erase_empty_line;
extern int rl_already_prompted;
extern int rl_num_chars_to_read;
extern char * rl_executing_macro;
extern int rl_catch_signals;
extern int rl_catch_sigwinch;
extern int rl_change_environment;
extern rl_compentry_func_t * rl_completion_entry_function;
extern rl_compentry_func_t * rl_menu_completion_entry_function;
extern rl_compignore_func_t * rl_ignore_some_completions_function;
extern rl_completion_func_t * rl_attempted_completion_function;
extern const char * rl_basic_word_break_characters;
extern char * rl_completer_word_break_characters;
extern rl_cpvfunc_t * rl_completion_word_break_hook;
extern const char * rl_completer_quote_characters;
extern const char * rl_basic_quote_characters;
extern const char * rl_filename_quote_characters;
extern const char * rl_special_prefixes;
extern rl_icppfunc_t * rl_directory_completion_hook;
extern rl_icppfunc_t * rl_directory_rewrite_hook;
extern rl_icppfunc_t * rl_filename_stat_hook;
extern rl_dequote_func_t * rl_filename_rewrite_hook;
extern rl_compdisp_func_t * rl_completion_display_matches_hook;
extern int rl_filename_completion_desired;
extern int rl_filename_quoting_desired;
extern rl_quote_func_t * rl_filename_quoting_function;
extern rl_dequote_func_t * rl_filename_dequoting_function;
extern rl_linebuf_func_t * rl_char_is_quoted_p;
extern int rl_attempted_completion_over;
extern int rl_completion_type;
extern int rl_completion_invoking_key;
extern int rl_completion_query_items;
extern int rl_completion_append_character;
extern int rl_completion_suppress_append;
extern int rl_completion_quote_character;
extern int rl_completion_found_quote;
extern int rl_completion_suppress_quote;
extern int rl_sort_completion_matches;
extern int rl_completion_mark_symlink_dirs;
extern int rl_ignore_completion_duplicates;
extern int rl_inhibit_completion;
extern int rl_persistent_signal_handlers;
struct readline_state {
    int point;
    int end;
    int mark;
    int buflen;
    char * buffer;
    UNDO_LIST * ul;
    char * prompt;
    int rlstate;
    int done;
    Keymap kmap;
    rl_command_func_t * lastfunc;
    int insmode;
    int edmode;
    char * kseq;
    int kseqlen;
    int pendingin;
    FILE * inf;
    FILE * outf;
    char * macro;
    int catchsigs;
    int catchsigwinch;
    rl_compentry_func_t * entryfunc;
    rl_compentry_func_t * menuentryfunc;
    rl_compignore_func_t * ignorefunc;
    rl_completion_func_t * attemptfunc;
    char * wordbreakchars;
    char reserved[64];
};
extern int rl_save_state(struct readline_state *);
extern int rl_restore_state(struct readline_state *);
struct timex {
    unsigned int modes;
    __syscall_slong_t offset;
    __syscall_slong_t freq;
    __syscall_slong_t maxerror;
    __syscall_slong_t esterror;
    int status;
    __syscall_slong_t constant;
    __syscall_slong_t precision;
    __syscall_slong_t tolerance;
    struct timeval time;
    __syscall_slong_t tick;
    __syscall_slong_t ppsfreq;
    __syscall_slong_t jitter;
    int shift;
    __syscall_slong_t stabil;
    __syscall_slong_t jitcnt;
    __syscall_slong_t calcnt;
    __syscall_slong_t errcnt;
    __syscall_slong_t stbcnt;
    int tai;
    int : 32;
    int : 32;
    int : 32;
    int : 32;
    int : 32;
    int : 32;
    int : 32;
    int : 32;
    int : 32;
    int : 32;
    int : 32;
};
extern int clock_adjtime(__clockid_t __clock_id,
                         struct timex * __utx) __attribute__((__nothrow__,__leaf__));
struct tm {
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
    long int tm_gmtoff;
    const char * tm_zone;
};
struct itimerspec {
    struct timespec it_interval; struct timespec it_value;
};
struct sigevent;
extern clock_t clock(void) __attribute__((__nothrow__,__leaf__));
extern time_t time(time_t * __timer) __attribute__((__nothrow__,__leaf__));
extern double difftime(time_t __time1,
                       time_t __time0) __attribute__((__nothrow__,__leaf__,const));
extern time_t mktime(struct tm * __tp) __attribute__((__nothrow__,__leaf__));
extern size_t strftime(char * __restrict __s,
                       size_t __maxsize,
                       const char * __restrict __format,
                       const struct tm * __restrict __tp) __attribute__((__nothrow__,__leaf__));
extern char * strptime(const char * __restrict __s,
                       const char * __restrict __fmt,
                       struct tm * __tp) __attribute__((__nothrow__,__leaf__));
extern size_t strftime_l(char * __restrict __s,
                         size_t __maxsize,
                         const char * __restrict __format,
                         const struct tm * __restrict __tp,
                         __locale_t __loc) __attribute__((__nothrow__,__leaf__));
extern char * strptime_l(const char * __restrict __s,
                         const char * __restrict __fmt,
                         struct tm * __tp,
                         __locale_t __loc) __attribute__((__nothrow__,__leaf__));
extern struct tm * gmtime(const time_t * __timer) __attribute__((__nothrow__,__leaf__));
extern struct tm * localtime(const time_t * __timer) __attribute__((__nothrow__,__leaf__));
extern struct tm * gmtime_r(const time_t * __restrict __timer,
                            struct tm * __restrict __tp) __attribute__((__nothrow__,__leaf__));
extern struct tm * localtime_r(const time_t * __restrict __timer,
                               struct tm * __restrict __tp) __attribute__((__nothrow__,__leaf__));
extern char * asctime(const struct tm * __tp) __attribute__((__nothrow__,__leaf__));
extern char * ctime(const time_t * __timer) __attribute__((__nothrow__,__leaf__));
extern char * asctime_r(const struct tm * __restrict __tp,
                        char * __restrict __buf) __attribute__((__nothrow__,__leaf__));
extern char * ctime_r(const time_t * __restrict __timer,
                      char * __restrict __buf) __attribute__((__nothrow__,__leaf__));
extern char * __tzname[2];
extern int __daylight;
extern long int __timezone;
extern char * tzname[2];
extern void tzset(void) __attribute__((__nothrow__,__leaf__));
extern int daylight;
extern long int timezone;
extern int stime(const time_t * __when) __attribute__((__nothrow__,__leaf__));
extern time_t timegm(struct tm * __tp) __attribute__((__nothrow__,__leaf__));
extern time_t timelocal(struct tm * __tp) __attribute__((__nothrow__,__leaf__));
extern int dysize(int __year) __attribute__((__nothrow__,__leaf__,const));
extern int nanosleep(const struct timespec * __requested_time,
                     struct timespec * __remaining);
extern int clock_getres(clockid_t __clock_id,
                        struct timespec * __res) __attribute__((__nothrow__,__leaf__));
extern int clock_gettime(clockid_t __clock_id,
                         struct timespec * __tp) __attribute__((__nothrow__,__leaf__));
extern int clock_settime(clockid_t __clock_id,
                         const struct timespec * __tp) __attribute__((__nothrow__,__leaf__));
extern int clock_nanosleep(clockid_t __clock_id,
                           int __flags,
                           const struct timespec * __req,
                           struct timespec * __rem);
extern int clock_getcpuclockid(pid_t __pid,
                               clockid_t * __clock_id) __attribute__((__nothrow__,__leaf__));
extern int timer_create(clockid_t __clock_id,
                        struct sigevent * __restrict __evp,
                        timer_t * __restrict __timerid) __attribute__((__nothrow__,__leaf__));
extern int timer_delete(timer_t __timerid) __attribute__((__nothrow__,__leaf__));
extern int timer_settime(timer_t __timerid,
                         int __flags,
                         const struct itimerspec * __restrict __value,
                         struct itimerspec * __restrict __ovalue) __attribute__((__nothrow__,__leaf__));
extern int timer_gettime(timer_t __timerid,
                         struct itimerspec * __value) __attribute__((__nothrow__,__leaf__));
extern int timer_getoverrun(timer_t __timerid) __attribute__((__nothrow__,__leaf__));
extern int timespec_get(struct timespec * __ts,
                        int __base) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int getdate_err;
extern struct tm * getdate(const char * __string);
extern int getdate_r(const char * __restrict __string,
                     struct tm * __restrict __resbufp);
typedef void * histdata_t;
typedef struct _hist_entry {
            char * line; char * timestamp; histdata_t data;
        } HIST_ENTRY;
typedef struct _hist_state {
            HIST_ENTRY * * entries;
            int offset;
            int length;
            int size;
            int flags;
        } HISTORY_STATE;
extern void using_history(void);
extern HISTORY_STATE * history_get_history_state(void);
extern void history_set_history_state(HISTORY_STATE *);
extern void add_history(const char *);
extern void add_history_time(const char *);
extern HIST_ENTRY * remove_history(int);
extern HIST_ENTRY * alloc_history_entry(char *, char *);
extern HIST_ENTRY * copy_history_entry(HIST_ENTRY *);
extern histdata_t free_history_entry(HIST_ENTRY *);
extern HIST_ENTRY * replace_history_entry(int,
                                          const char *,
                                          histdata_t);
extern void clear_history(void);
extern void stifle_history(int);
extern int unstifle_history(void);
extern int history_is_stifled(void);
extern HIST_ENTRY * * history_list(void);
extern int where_history(void);
extern HIST_ENTRY * current_history(void);
extern HIST_ENTRY * history_get(int);
extern time_t history_get_time(HIST_ENTRY *);
extern int history_total_bytes(void);
extern int history_set_pos(int);
extern HIST_ENTRY * previous_history(void);
extern HIST_ENTRY * next_history(void);
extern int history_search(const char *, int);
extern int history_search_prefix(const char *, int);
extern int history_search_pos(const char *, int, int);
extern int read_history(const char *);
extern int read_history_range(const char *, int, int);
extern int write_history(const char *);
extern int append_history(int, const char *);
extern int history_truncate_file(const char *, int);
extern int history_expand(char *, char * *);
extern char * history_arg_extract(int, int, const char *);
extern char * get_history_event(const char *, int *, int);
extern char * * history_tokenize(const char *);
extern int history_base;
extern int history_length;
extern int history_max_entries;
extern int history_offset;
extern int history_lines_read_from_file;
extern int history_lines_written_to_file;
extern char history_expansion_char;
extern char history_subst_char;
extern char * history_word_delimiters;
extern char history_comment_char;
extern char * history_no_expand_chars;
extern char * history_search_delimiter_chars;
extern int history_quotes_inhibit_expansion;
extern int history_write_timestamps;
extern int history_multiline_entries;
extern int history_file_version;
extern int max_input_history;
extern rl_linebuf_func_t * history_inhibit_expansion_function;
extern int __sigismember(const __sigset_t *, int);
extern int __sigaddset(__sigset_t *, int);
extern int __sigdelset(__sigset_t *, int);
typedef __sig_atomic_t sig_atomic_t;
typedef union sigval {
            int sival_int; void * sival_ptr;
        } sigval_t;
typedef __clock_t __sigchld_clock_t;
typedef struct {
            int si_signo;
            int si_errno;
            int si_code;
            union {
                int _pad[128 / sizeof(int) - 4];
                struct {
                    __pid_t si_pid; __uid_t si_uid;
                } _kill;
                struct {
                    int si_tid; int si_overrun; sigval_t si_sigval;
                } _timer;
                struct {
                    __pid_t si_pid; __uid_t si_uid; sigval_t si_sigval;
                } _rt;
                struct {
                    __pid_t si_pid;
                    __uid_t si_uid;
                    int si_status;
                    __sigchld_clock_t si_utime;
                    __sigchld_clock_t si_stime;
                } _sigchld;
                struct {
                    void * si_addr;
                    short int si_addr_lsb;
                    struct {
                        void * _lower; void * _upper;
                    } si_addr_bnd;
                } _sigfault;
                struct {
                    long int si_band; int si_fd;
                } _sigpoll;
                struct {
                    void * _call_addr; int _syscall; unsigned int _arch;
                } _sigsys;
            } _sifields;
        } siginfo_t;
enum {
    SI_ASYNCNL = -60,
    SI_TKILL = -6,
    SI_SIGIO,
    SI_ASYNCIO,
    SI_MESGQ,
    SI_TIMER,
    SI_QUEUE,
    SI_USER,
    SI_KERNEL = 0x80
};
enum {
    ILL_ILLOPC = 1,
    ILL_ILLOPN,
    ILL_ILLADR,
    ILL_ILLTRP,
    ILL_PRVOPC,
    ILL_PRVREG,
    ILL_COPROC,
    ILL_BADSTK
};
enum {
    FPE_INTDIV = 1,
    FPE_INTOVF,
    FPE_FLTDIV,
    FPE_FLTOVF,
    FPE_FLTUND,
    FPE_FLTRES,
    FPE_FLTINV,
    FPE_FLTSUB
};
enum {
    SEGV_MAPERR = 1, SEGV_ACCERR
};
enum {
    BUS_ADRALN = 1,
    BUS_ADRERR,
    BUS_OBJERR,
    BUS_MCEERR_AR,
    BUS_MCEERR_AO
};
enum {
    TRAP_BRKPT = 1, TRAP_TRACE
};
enum {
    CLD_EXITED = 1,
    CLD_KILLED,
    CLD_DUMPED,
    CLD_TRAPPED,
    CLD_STOPPED,
    CLD_CONTINUED
};
enum {
    POLL_IN = 1, POLL_OUT, POLL_MSG, POLL_ERR, POLL_PRI, POLL_HUP
};
typedef struct sigevent {
            sigval_t sigev_value;
            int sigev_signo;
            int sigev_notify;
            union {
                int _pad[64 / sizeof(int) - 4];
                __pid_t _tid;
                struct {
                    void (* _function)(sigval_t); pthread_attr_t * _attribute;
                } _sigev_thread;
            } _sigev_un;
        } sigevent_t;
enum {
    SIGEV_SIGNAL = 0, SIGEV_NONE, SIGEV_THREAD, SIGEV_THREAD_ID = 4
};
typedef void (* __sighandler_t)(int);
extern __sighandler_t __sysv_signal(int __sig,
                                    __sighandler_t __handler) __attribute__((__nothrow__,__leaf__));
extern __sighandler_t sysv_signal(int __sig,
                                  __sighandler_t __handler) __attribute__((__nothrow__,__leaf__));
extern __sighandler_t signal(int __sig,
                             __sighandler_t __handler) __attribute__((__nothrow__,__leaf__));
extern __sighandler_t bsd_signal(int __sig,
                                 __sighandler_t __handler) __attribute__((__nothrow__,__leaf__));
extern int kill(__pid_t __pid,
                int __sig) __attribute__((__nothrow__,__leaf__));
extern int killpg(__pid_t __pgrp,
                  int __sig) __attribute__((__nothrow__,__leaf__));
extern int raise(int __sig) __attribute__((__nothrow__,__leaf__));
extern __sighandler_t ssignal(int __sig,
                              __sighandler_t __handler) __attribute__((__nothrow__,__leaf__));
extern int gsignal(int __sig) __attribute__((__nothrow__,__leaf__));
extern void psignal(int __sig, const char * __s);
extern void psiginfo(const siginfo_t * __pinfo, const char * __s);
extern int sigpause(int __sig) __asm__("__xpg_sigpause");
extern int sigblock(int __mask) __attribute__((__nothrow__,__leaf__,__deprecated__));
extern int sigsetmask(int __mask) __attribute__((__nothrow__,__leaf__,__deprecated__));
extern int siggetmask(void) __attribute__((__nothrow__,__leaf__,__deprecated__));
typedef __sighandler_t sighandler_t;
typedef __sighandler_t sig_t;
extern int sigemptyset(sigset_t * __set) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int sigfillset(sigset_t * __set) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int sigaddset(sigset_t * __set,
                     int __signo) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int sigdelset(sigset_t * __set,
                     int __signo) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int sigismember(const sigset_t * __set,
                       int __signo) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int sigisemptyset(const sigset_t * __set) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int sigandset(sigset_t * __set,
                     const sigset_t * __left,
                     const sigset_t * __right) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2, 3)));
extern int sigorset(sigset_t * __set,
                    const sigset_t * __left,
                    const sigset_t * __right) __attribute__((__nothrow__,__leaf__,__nonnull__(1, 2, 3)));
struct sigaction {
    union {
        __sighandler_t sa_handler;
        void (* sa_sigaction)(int, siginfo_t *, void *);
    } __sigaction_handler;
    __sigset_t sa_mask;
    int sa_flags;
    void (* sa_restorer)(void);
};
extern int sigprocmask(int __how,
                       const sigset_t * __restrict __set,
                       sigset_t * __restrict __oset) __attribute__((__nothrow__,__leaf__));
extern int sigsuspend(const sigset_t * __set) __attribute__((__nonnull__(1)));
extern int sigaction(int __sig,
                     const struct sigaction * __restrict __act,
                     struct sigaction * __restrict __oact) __attribute__((__nothrow__,__leaf__));
extern int sigpending(sigset_t * __set) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int sigwait(const sigset_t * __restrict __set,
                   int * __restrict __sig) __attribute__((__nonnull__(1, 2)));
extern int sigwaitinfo(const sigset_t * __restrict __set,
                       siginfo_t * __restrict __info) __attribute__((__nonnull__(1)));
extern int sigtimedwait(const sigset_t * __restrict __set,
                        siginfo_t * __restrict __info,
                        const struct timespec * __restrict __timeout) __attribute__((__nonnull__(1)));
extern int sigqueue(__pid_t __pid,
                    int __sig,
                    const union sigval __val) __attribute__((__nothrow__,__leaf__));
extern const char * const _sys_siglist[65];
extern const char * const sys_siglist[65];
struct _fpx_sw_bytes {
    __uint32_t magic1;
    __uint32_t extended_size;
    __uint64_t xstate_bv;
    __uint32_t xstate_size;
    __uint32_t padding[7];
};
struct _fpreg {
    unsigned short significand[4]; unsigned short exponent;
};
struct _fpxreg {
    unsigned short significand[4];
    unsigned short exponent;
    unsigned short padding[3];
};
struct _xmmreg {
    __uint32_t element[4];
};
struct _fpstate {
    __uint16_t cwd;
    __uint16_t swd;
    __uint16_t ftw;
    __uint16_t fop;
    __uint64_t rip;
    __uint64_t rdp;
    __uint32_t mxcsr;
    __uint32_t mxcr_mask;
    struct _fpxreg _st[8];
    struct _xmmreg _xmm[16];
    __uint32_t padding[24];
};
struct sigcontext {
    __uint64_t r8;
    __uint64_t r9;
    __uint64_t r10;
    __uint64_t r11;
    __uint64_t r12;
    __uint64_t r13;
    __uint64_t r14;
    __uint64_t r15;
    __uint64_t rdi;
    __uint64_t rsi;
    __uint64_t rbp;
    __uint64_t rbx;
    __uint64_t rdx;
    __uint64_t rax;
    __uint64_t rcx;
    __uint64_t rsp;
    __uint64_t rip;
    __uint64_t eflags;
    unsigned short cs;
    unsigned short gs;
    unsigned short fs;
    unsigned short __pad0;
    __uint64_t err;
    __uint64_t trapno;
    __uint64_t oldmask;
    __uint64_t cr2;
    union {
        struct _fpstate * fpstate; __uint64_t __fpstate_word;
    };
    __uint64_t __reserved1[8];
};
struct _xsave_hdr {
    __uint64_t xstate_bv;
    __uint64_t reserved1[2];
    __uint64_t reserved2[5];
};
struct _ymmh_state {
    __uint32_t ymmh_space[64];
};
struct _xstate {
    struct _fpstate fpstate;
    struct _xsave_hdr xstate_hdr;
    struct _ymmh_state ymmh;
};
extern int sigreturn(struct sigcontext * __scp) __attribute__((__nothrow__,__leaf__));
extern int siginterrupt(int __sig,
                        int __interrupt) __attribute__((__nothrow__,__leaf__));
struct sigstack {
    void * ss_sp; int ss_onstack;
};
enum {
    SS_ONSTACK = 1, SS_DISABLE
};
typedef struct sigaltstack {
            void * ss_sp; int ss_flags; size_t ss_size;
        } stack_t;
typedef long long int greg_t;
typedef greg_t gregset_t[23];
enum {
    REG_R8 = 0,
    REG_R9,
    REG_R10,
    REG_R11,
    REG_R12,
    REG_R13,
    REG_R14,
    REG_R15,
    REG_RDI,
    REG_RSI,
    REG_RBP,
    REG_RBX,
    REG_RDX,
    REG_RAX,
    REG_RCX,
    REG_RSP,
    REG_RIP,
    REG_EFL,
    REG_CSGSFS,
    REG_ERR,
    REG_TRAPNO,
    REG_OLDMASK,
    REG_CR2
};
struct _libc_fpxreg {
    unsigned short int significand[4];
    unsigned short int exponent;
    unsigned short int padding[3];
};
struct _libc_xmmreg {
    __uint32_t element[4];
};
struct _libc_fpstate {
    __uint16_t cwd;
    __uint16_t swd;
    __uint16_t ftw;
    __uint16_t fop;
    __uint64_t rip;
    __uint64_t rdp;
    __uint32_t mxcsr;
    __uint32_t mxcr_mask;
    struct _libc_fpxreg _st[8];
    struct _libc_xmmreg _xmm[16];
    __uint32_t padding[24];
};
typedef struct _libc_fpstate * fpregset_t;
typedef struct {
            gregset_t gregs;
            fpregset_t fpregs;
            unsigned long long __reserved1[8];
        } mcontext_t;
typedef struct ucontext {
            unsigned long int uc_flags;
            struct ucontext * uc_link;
            stack_t uc_stack;
            mcontext_t uc_mcontext;
            __sigset_t uc_sigmask;
            struct _libc_fpstate __fpregs_mem;
        } ucontext_t;
extern int sigstack(struct sigstack * __ss,
                    struct sigstack * __oss) __attribute__((__nothrow__,__leaf__,__deprecated__));
extern int sigaltstack(const struct sigaltstack * __restrict __ss,
                       struct sigaltstack * __restrict __oss) __attribute__((__nothrow__,__leaf__));
extern int sighold(int __sig) __attribute__((__nothrow__,__leaf__));
extern int sigrelse(int __sig) __attribute__((__nothrow__,__leaf__));
extern int sigignore(int __sig) __attribute__((__nothrow__,__leaf__));
extern __sighandler_t sigset(int __sig,
                             __sighandler_t __disp) __attribute__((__nothrow__,__leaf__));
extern int pthread_sigmask(int __how,
                           const __sigset_t * __restrict __newmask,
                           __sigset_t * __restrict __oldmask) __attribute__((__nothrow__,__leaf__));
extern int pthread_kill(pthread_t __threadid,
                        int __signo) __attribute__((__nothrow__,__leaf__));
extern int pthread_sigqueue(pthread_t __threadid,
                            int __signo,
                            const union sigval __value) __attribute__((__nothrow__,__leaf__));
extern int __libc_current_sigrtmin(void) __attribute__((__nothrow__,__leaf__));
extern int __libc_current_sigrtmax(void) __attribute__((__nothrow__,__leaf__));
struct winsize {
    unsigned short int ws_row;
    unsigned short int ws_col;
    unsigned short int ws_xpixel;
    unsigned short int ws_ypixel;
};
struct termio {
    unsigned short int c_iflag;
    unsigned short int c_oflag;
    unsigned short int c_cflag;
    unsigned short int c_lflag;
    unsigned char c_line;
    unsigned char c_cc[8];
};
extern int ioctl(int __fd,
                 unsigned long int __request, ...) __attribute__((__nothrow__,__leaf__));
struct dirent {
    __ino_t d_ino;
    __off_t d_off;
    unsigned short int d_reclen;
    unsigned char d_type;
    char d_name[256];
};
struct dirent64 {
    __ino64_t d_ino;
    __off64_t d_off;
    unsigned short int d_reclen;
    unsigned char d_type;
    char d_name[256];
};
enum {
    DT_UNKNOWN = 0,
    DT_FIFO = 1,
    DT_CHR = 2,
    DT_DIR = 4,
    DT_BLK = 6,
    DT_REG = 8,
    DT_LNK = 10,
    DT_SOCK = 12,
    DT_WHT = 14
};
typedef struct __dirstream DIR;
extern DIR * opendir(const char * __name) __attribute__((__nonnull__(1)));
extern DIR * fdopendir(int __fd);
extern int closedir(DIR * __dirp) __attribute__((__nonnull__(1)));
extern struct dirent * readdir(DIR * __dirp) __attribute__((__nonnull__(1)));
extern struct dirent64 * readdir64(DIR * __dirp) __attribute__((__nonnull__(1)));
extern int readdir_r(DIR * __restrict __dirp,
                     struct dirent * __restrict __entry,
                     struct dirent * * __restrict __result) __attribute__((__nonnull__(1, 2, 3),__deprecated__));
extern int readdir64_r(DIR * __restrict __dirp,
                       struct dirent64 * __restrict __entry,
                       struct dirent64 * * __restrict __result) __attribute__((__nonnull__(1, 2, 3),__deprecated__));
extern void rewinddir(DIR * __dirp) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern void seekdir(DIR * __dirp,
                    long int __pos) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern long int telldir(DIR * __dirp) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int dirfd(DIR * __dirp) __attribute__((__nothrow__,__leaf__,__nonnull__(1)));
extern int scandir(const char * __restrict __dir,
                   struct dirent * * * __restrict __namelist,
                   int (* __selector)(const struct dirent *),
                   int (* __cmp)(const struct dirent * *,
                                 const struct dirent * *)) __attribute__((__nonnull__(1, 2)));
extern int scandir64(const char * __restrict __dir,
                     struct dirent64 * * * __restrict __namelist,
                     int (* __selector)(const struct dirent64 *),
                     int (* __cmp)(const struct dirent64 * *,
                                   const struct dirent64 * *)) __attribute__((__nonnull__(1, 2)));
extern int scandirat(int __dfd,
                     const char * __restrict __dir,
                     struct dirent * * * __restrict __namelist,
                     int (* __selector)(const struct dirent *),
                     int (* __cmp)(const struct dirent * *,
                                   const struct dirent * *)) __attribute__((__nonnull__(2, 3)));
extern int scandirat64(int __dfd,
                       const char * __restrict __dir,
                       struct dirent64 * * * __restrict __namelist,
                       int (* __selector)(const struct dirent64 *),
                       int (* __cmp)(const struct dirent64 * *,
                                     const struct dirent64 * *)) __attribute__((__nonnull__(2, 3)));
extern int alphasort(const struct dirent * * __e1,
                     const struct dirent * * __e2) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1, 2)));
extern int alphasort64(const struct dirent64 * * __e1,
                       const struct dirent64 * * __e2) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1, 2)));
extern __ssize_t getdirentries(int __fd,
                               char * __restrict __buf,
                               size_t __nbytes,
                               __off_t * __restrict __basep) __attribute__((__nothrow__,__leaf__,__nonnull__(2, 4)));
extern __ssize_t getdirentries64(int __fd,
                                 char * __restrict __buf,
                                 size_t __nbytes,
                                 __off64_t * __restrict __basep) __attribute__((__nothrow__,__leaf__,__nonnull__(2, 4)));
extern int versionsort(const struct dirent * * __e1,
                       const struct dirent * * __e2) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1, 2)));
extern int versionsort64(const struct dirent64 * * __e1,
                         const struct dirent64 * * __e2) __attribute__((__nothrow__,__leaf__,__pure__,__nonnull__(1, 2)));
extern char * dirname(char * __path) __attribute__((__nothrow__,__leaf__));
extern char * __xpg_basename(char * __path) __attribute__((__nothrow__,__leaf__));
static int mgetmaxx()
{
    struct winsize ws;
    ioctl(1, 0x5413, &ws);
    return ws.ws_col;
}
static int mgetmaxy()
{
    struct winsize ws;
    ioctl(1, 0x5413, &ws);
    return ws.ws_row;
}
void display_candidates(char * * candidates)
{
    char * candidate;
    char * * p;
    int max_len;
    int maxx;
    int cols;
    int n;
    p = candidates;
    max_len = -1;
    while ((candidate = *p) != (void *) 0)
    {
        int len;
        len = strlen(candidate);
        if (len > max_len)
        {
            max_len = len;
        }
        p++;
    }
    maxx = mgetmaxx();
    cols = maxx / (max_len + 2);
    if (cols == 0)
    {
        cols = 1;
    }
    n = 0;
    puts("");
    p = candidates;
    while ((candidate = *p) != (void *) 0)
    {
        char format[128];
        format[0] = '%';
        format[1] = '-';
        snprintf(format + 2, 128 - 2, "%d", max_len + 2);
        xstrncat(format, "s", 128);
        printf(format, candidate);
        n++;
        if (n == cols)
        {
            puts("");
            n = 0;
        }
        p++;
    }
    puts("");
}
static char * cl_type_to_buffer(sCLType * cl_type,
                                sCLClass * klass);
static char * cl_block_type_to_buffer(sCLBlockType * cl_block_type,
                                      sCLClass * klass)
{
    sBuf buf;
    int i;
    sBuf_init(&buf);
    sBuf_append_str(&buf, "lambda(");
    for (i = 0; i < cl_block_type->mNumParams; i++)
    {
        sCLType * cl_type;
        char * cl_type_name;
        cl_type = cl_block_type->mParams[i];
        cl_type_name = cl_type_to_buffer(cl_type, klass);
        sBuf_append_str(&buf, cl_type_name);
        xfree(cl_type_name);
        if (i != cl_block_type->mNumParams - 1)
        {
            sBuf_append_str(&buf, ",");
        }
    }
    sBuf_append_str(&buf, ")");
    if (cl_block_type->mResultType)
    {
        sCLType * cl_type;
        char * cl_type_name;
        sBuf_append_str(&buf, ":");
        cl_type = cl_block_type->mResultType;
        cl_type_name = cl_type_to_buffer(cl_type, klass);
        sBuf_append_str(&buf, cl_type_name);
        xfree(cl_type_name);
    }
    return buf.mBuf;
}
static char * cl_type_to_buffer(sCLType * cl_type,
                                sCLClass * klass)
{
    int i;
    sBuf buf;
    sBuf_init(&buf);
    if (cl_type == (void *) 0)
    {
        sBuf_append_str(&buf, "NULL");
    }
    else if (cl_type->mNumGenericsTypes == 0)
    {
        if (cl_type->mBlockType)
        {
            char * block_type_str;
            block_type_str = cl_block_type_to_buffer(cl_type->mBlockType,
                                                     klass);
            sBuf_append_str(&buf, block_type_str);
            xfree(block_type_str);
        }
        else
        {
            sBuf_append_str(&buf,
                            (char *) ((&klass->mConst)->mConst + cl_type->mClassNameOffset));
        }
    }
    else
    {
        if (cl_type->mClassNameOffset == 0)
        {
            sBuf_append_str(&buf, "NULL<");
        }
        else
        {
            sBuf_append_str(&buf,
                            (char *) ((&klass->mConst)->mConst + cl_type->mClassNameOffset));
            sBuf_append_str(&buf, "<");
        }
        for (i = 0; i < cl_type->mNumGenericsTypes; i++)
        {
            char * result;
            result = cl_type_to_buffer(cl_type->mGenericsTypes[i], klass);
            sBuf_append_str(&buf, result);
            xfree(result);
            if (i != cl_type->mNumGenericsTypes - 1)
            {
                sBuf_append_str(&buf, ",");
            }
        }
        sBuf_append_str(&buf, ">");
    }
    return buf.mBuf;
}
char * * get_method_names_with_arguments(sCLClass * klass,
                                         int class_method,
                                         int * num_methods)
{
    int result_size;
    char * * result;
    int result_num;
    int i;
    result_size = 128;
    result = xcalloc(1, sizeof(char *) * result_size);
    result_num = 0;
    *num_methods = 0;
    for (i = 0; i < klass->mNumMethods; i++)
    {
        sCLMethod * method;
        method = klass->mMethods + i;
        if (class_method && method->mFlags & 0x2 || !class_method && !(method->mFlags & 0x2))
        {
            sBuf buf;
            int j;
            sBuf_init(&buf);
            sBuf_append_str(&buf,
                            (char *) ((&klass->mConst)->mConst + method->mNameOffset));
            sBuf_append_str(&buf, "(");
            for (j = 0; j < method->mNumParams; j++)
            {
                sCLParam * param;
                sCLType * param_type;
                char * argment_names;
                param = method->mParams + j;
                param_type = param->mType;
                argment_names = cl_type_to_buffer(param_type, klass);
                sBuf_append_str(&buf, argment_names);
                if (j != method->mNumParams - 1)
                {
                    sBuf_append_str(&buf, ",");
                }
                xfree(argment_names);
            }
            sBuf_append_str(&buf, ")");
            *(result + result_num) = buf.mBuf;
            result_num++;
            if (result_num >= result_size)
            {
                result_size *= 2;
                result = xrealloc(result, sizeof(char *) * result_size);
            }
        }
    }
    *(result + result_num) = xstrdup("toAnonymous()");
    result_num++;
    if (result_num >= result_size)
    {
        result_size *= 2;
        result = xrealloc(result, sizeof(char *) * result_size);
    }
    *(result + result_num) = xstrdup("identifyWith(Object)");
    result_num++;
    if (result_num >= result_size)
    {
        result_size *= 2;
        result = xrealloc(result, sizeof(char *) * result_size);
    }
    *(result + result_num) = xstrdup("className()");
    result_num++;
    *(result + result_num) = xstrdup("toNull()");
    result_num++;
    if (result_num >= result_size)
    {
        result_size *= 2;
        result = xrealloc(result, sizeof(char *) * result_size);
    }
    if (class_method)
    {
        for (i = 0; i < klass->mNumClassFields; i++)
        {
            sCLField * field;
            field = klass->mClassFields + i;
            *(result + result_num) = xstrdup((char *) ((&klass->mConst)->mConst + field->mNameOffset));
            result_num++;
            if (result_num >= result_size)
            {
                result_size *= 2;
                result = xrealloc(result, sizeof(char *) * result_size);
            }
        }
    }
    else
    {
        for (i = 0; i < klass->mNumFields; i++)
        {
            sCLField * field;
            field = klass->mFields + i;
            *(result + result_num) = xstrdup((char *) ((&klass->mConst)->mConst + field->mNameOffset));
            result_num++;
            if (result_num >= result_size)
            {
                result_size *= 2;
                result = xrealloc(result, sizeof(char *) * result_size);
            }
        }
    }
    *num_methods = result_num;
    *(result + result_num) = (void *) 0;
    result_num++;
    if (result_num >= result_size)
    {
        result_size *= 2;
        result = xrealloc(result, sizeof(char *) * result_size);
    }
    return result;
}
static char * line_buffer_from_head_to_cursor_point()
{
    char * result;
    ;
    result = xcalloc(1, strlen(rl_line_buffer) + 1);
    memcpy(result, rl_line_buffer, rl_point);
    result[rl_point] = 0;
    return result;
}
static int get_type(char * source,
                    char * fname,
                    sVarTable * lv_table,
                    CLVALUE * stack,
                    sNodeType * * type_,
                    sVarTable * * result_lv_table)
{
    sParserInfo info;
    sCompileInfo cinfo;
    sByteCode code;
    sConst constant;
    memset(&info, 0, sizeof(sParserInfo));
    info.p = source;
    info.sname = fname;
    info.sline = 1;
    info.lv_table = lv_table;
    info.parse_phase = 0;
    info.get_type_for_interpreter = 1;
    memset(&cinfo, 0, sizeof(sCompileInfo));
    sByteCode_init(&code);
    cinfo.code = &code;
    sConst_init(&constant);
    cinfo.constant = &constant;
    cinfo.lv_table = lv_table;
    cinfo.no_output = 1;
    cinfo.pinfo = &info;
    info.cinfo = &cinfo;
    while (*info.p)
    {
        unsigned int node;
        info.exist_block_object_err = 0;
        node = 0;
        (void) expression(&node, &info);
        *result_lv_table = info.lv_table;
        if (node != 0)
        {
            (void) compile(node, &cinfo);
            *type_ = cinfo.type;
            if (*info.p == ';')
            {
                info.p++;
                skip_spaces_and_lf(&info);
            }
        }
    }
    sByteCode_free(&code);
    sConst_free(&constant);
    return 1;
}
static void skip_curly(char * * p,
                       char * * head,
                       char * * comma,
                       char * * semi_colon);
static void skip_paren(char * * p,
                       char * * head,
                       char * * comma,
                       char * * semi_colon)
{
    char * head_before;
    int squort;
    int dquort;
    head_before = *head;
    *head = *p;
    *comma = (void *) 0;
    *semi_colon = (void *) 0;
    squort = 0;
    dquort = 0;
    while (* (*p))
    {
        if (!squort && !dquort && * (*p) == '{')
        {
            (*p)++;
            skip_curly(p, head, comma, semi_colon);
            if (*comma)
            {
                *head = *comma;
            }
            else if (*semi_colon)
            {
                *head = *semi_colon;
            }
        }
        else if (!squort && !dquort && * (*p) == '(')
        {
            (*p)++;
            skip_paren(p, head, comma, semi_colon);
            if (*comma)
            {
                *head = *comma;
            }
            else if (*semi_colon)
            {
                *head = *semi_colon;
            }
        }
        else if (!squort && !dquort && * (*p) == ')')
        {
            (*p)++;
            *head = head_before;
            *comma = (void *) 0;
            *semi_colon = (void *) 0;
            break;
        }
        else if (!squort && !dquort && * (*p) == ',')
        {
            (*p)++;
            *comma = *p;
        }
        else if (!squort && !dquort && * (*p) == '&' && *(*p + 1) == '&')
        {
            *p += 2;
            *head = *p;
        }
        else if (!squort && !dquort && * (*p) == '|' && *(*p + 1) == '|')
        {
            *p += 2;
            *head = *p;
        }
        else if (!squort && !dquort && * (*p) == '|')
        {
            (*p)++;
            *head = *p;
        }
        else if (!squort && !dquort && strstr(*p, "return") == *p)
        {
            *p += strlen("return");
            while (* (*p) == ' ' || * (*p) == '\t')
            {
                (*p)++;
            }
            *head = *p;
        }
        else if (* (*p) == '\'')
        {
            (*p)++;
            squort = !squort;
        }
        else if (* (*p) == '"')
        {
            (*p)++;
            dquort = !dquort;
        }
        else
        {
            (*p)++;
        }
    }
}
static void skip_curly(char * * p,
                       char * * head,
                       char * * comma,
                       char * * semi_colon)
{
    char * head_before;
    int squort;
    int dquort;
    head_before = *head;
    *head = *p;
    *comma = (void *) 0;
    *semi_colon = (void *) 0;
    squort = 0;
    dquort = 0;
    while (* (*p))
    {
        if (!squort && !dquort && * (*p) == '{')
        {
            (*p)++;
            skip_curly(p, head, comma, semi_colon);
            if (*comma)
            {
                *head = *comma;
            }
            else if (*semi_colon)
            {
                *head = *semi_colon;
            }
        }
        else if (!squort && !dquort && * (*p) == '(')
        {
            (*p)++;
            skip_paren(p, head, comma, semi_colon);
            if (*comma)
            {
                *head = *comma;
            }
            else if (*semi_colon)
            {
                *head = *semi_colon;
            }
        }
        else if (!squort && !dquort && * (*p) == '}')
        {
            (*p)++;
            *head = head_before;
            *comma = (void *) 0;
            *semi_colon = (void *) 0;
            break;
        }
        else if (!squort && !dquort && * (*p) == ',')
        {
            (*p)++;
            *comma = *p;
        }
        else if (!squort && !dquort && * (*p) == ';')
        {
            (*p)++;
            *semi_colon = *p;
        }
        else if (!squort && !dquort && * (*p) == '&' && *(*p + 1) == '&')
        {
            *p += 2;
            *head = *p;
        }
        else if (!squort && !dquort && * (*p) == '|' && *(*p + 1) == '|')
        {
            *p += 2;
            *head = *p;
        }
        else if (!squort && !dquort && * (*p) == '|')
        {
            (*p)++;
            *head = *p;
        }
        else if (!squort && !dquort && strstr(*p, "return") == *p)
        {
            *p += strlen("return");
            while (* (*p) == ' ' || * (*p) == '\t')
            {
                (*p)++;
            }
            *head = *p;
        }
        else if (* (*p) == '\'')
        {
            (*p)++;
            squort = !squort;
        }
        else if (* (*p) == '"')
        {
            (*p)++;
            dquort = !dquort;
        }
        else
        {
            (*p)++;
        }
    }
}
static char * get_one_expression(char * source)
{
    char * head;
    char * comma;
    char * semi_colon;
    int squort;
    int dquort;
    char * p;
    head = source;
    comma = (void *) 0;
    semi_colon = (void *) 0;
    squort = 0;
    dquort = 0;
    p = source + strlen(source);
    while (p >= source)
    {
        if (*p == ';')
        {
            break;
        }
        p--;
    }
    p++;
    while (*p == ' ' || *p == '\t')
    {
        p++;
    }
    head = p;
    while (*p)
    {
        if (!squort && !dquort && *p == '(')
        {
            p++;
            skip_paren(&p, &head, &comma, &semi_colon);
            if (comma)
            {
                head = comma;
            }
            else if (semi_colon)
            {
                head = semi_colon;
            }
        }
        else if (!squort && !dquort && *p == '{')
        {
            p++;
            skip_curly(&p, &head, &comma, &semi_colon);
            if (comma)
            {
                head = comma;
            }
            else if (semi_colon)
            {
                head = semi_colon;
            }
        }
        else if (*p == '&' && *(p + 1) == '&')
        {
            p += 2;
            head = p;
        }
        else if (*p == '|' && *(p + 1) == '|')
        {
            p += 2;
            head = p;
        }
        else if (*p == '|')
        {
            p++;
            head = p;
        }
        else if (*p == '=' || *p == '<')
        {
            p++;
            head = p;
        }
        else if (strstr(p, "return") == p)
        {
            p += strlen("return");
            while (*p == ' ' || *p == '\t')
            {
                p++;
            }
            head = p;
        }
        else if (strstr(p, "new") == p)
        {
            p += strlen("new");
            while (*p == ' ' || *p == '\t')
            {
                p++;
            }
            head = p;
        }
        else if (*p == '\'')
        {
            p++;
            squort = !squort;
        }
        else if (*p == '"')
        {
            p++;
            dquort = !dquort;
        }
        else if (*p == ';')
        {
            *p = '\000';
            break;
        }
        else
        {
            p++;
        }
    }
    return head;
}
char * * gCandidates = (void *) 0;
int gNumCandidates = 0;
int gInputingMethod = 0;
int gInputingPath = 0;
int gInputingCommandPath = 0;
CLVALUE * gStack = (void *) 0;
sVarTable * gLVTable = (void *) 0;
static void file_completion(char * line)
{
    DIR * result_opendir;
    char path[4096];
    char * p;
    p = (char *) line + strlen(line);
    while (p >= line)
    {
        if (*p == '"')
        {
            break;
        }
        else
        {
            p--;
        }
    }
    if (*(p + 1) == 0)
    {
        result_opendir = opendir(".");
        path[0] = 0;
    }
    else
    {
        char * text2;
        text2 = xstrdup(p + 1);
        if (text2[0] == '~')
        {
            char text3[4096];
            char * home;
            home = getenv("HOME");
            if (home)
            {
                if (text2[1] == '/')
                {
                    snprintf(text3, 4096, "%s/%s", home, text2 + 2);
                }
                else
                {
                    snprintf(text3, 4096, "%s/%s", home, text2 + 1);
                }
                rl_delete_text(rl_point - strlen(text2), rl_point);
                rl_point -= strlen(text2);
                rl_insert_text(text3);
                result_opendir = opendir(text3);
                xstrncpy(path, text3, 4096);
            }
            else
            {
                result_opendir = opendir(text2);
                xstrncpy(path, text2, 4096);
            }
        }
        if (text2[0] == '.' && text2[1] == '/')
        {
            result_opendir = opendir(".");
            xstrncpy(path, "./", 4096);
        }
        else if (text2[strlen(text2) - 1] == '/')
        {
            result_opendir = opendir(text2);
            xstrncpy(path, text2, 4096);
        }
        else
        {
            char * dirname_;
            dirname_ = dirname(text2);
            result_opendir = opendir(dirname_);
            if (strcmp(dirname_, ".") == 0)
            {
                path[0] = 0;
            }
            else
            {
                xstrncpy(path, dirname_, 4096);
                if (dirname_[strlen(dirname_) - 1] != '/')
                {
                    xstrncat(path, "/", 4096);
                }
            }
        }
        xfree(text2);
    }
    if (result_opendir)
    {
        int n;
        int size;
        n = 0;
        size = 128;
        gCandidates = xcalloc(1, sizeof(char *) * size);
        while (1)
        {
            struct dirent * result_readdir;
            int len;
            char * candidate;
            result_readdir = readdir(result_opendir);
            if (result_readdir == (void *) 0)
            {
                break;
            }
            if (strcmp(result_readdir->d_name,
                       ".") != 0 && strcmp(result_readdir->d_name, "..") != 0)
            {
                struct stat stat_;
                len = strlen(path) + strlen(result_readdir->d_name) + 2 + 1 + 1;
                candidate = xmalloc(len);
                xstrncpy(candidate, path, len);
                xstrncat(candidate, result_readdir->d_name, len);
                if (stat(candidate, &stat_) == 0)
                {
                    if ((stat_.st_mode & 0170000) == 040000)
                    {
                        xstrncat(candidate, "/", len);
                    }
                    gCandidates[n++] = candidate;
                    if (n >= size)
                    {
                        size *= 2;
                        gCandidates = xrealloc(gCandidates, sizeof(char *) * size);
                    }
                }
                else
                {
                    xfree(candidate);
                }
            }
        }
        gCandidates[n] = (void *) 0;
        gNumCandidates = n;
        closedir(result_opendir);
    }
    rl_completer_word_break_characters = "\t\n\"";
}
static void file_completion_command_line(char * text)
{
    DIR * result_opendir;
    char path[4096];
    char * p;
    p = (char *) text + strlen(text);
    while (p >= text)
    {
        if (*p == ' ' || *p == '\t')
        {
            p++;
            break;
        }
        else
        {
            p--;
        }
    }
    if (*p == 0)
    {
        result_opendir = opendir(".");
        path[0] = 0;
    }
    else
    {
        char * text2;
        text2 = xstrdup(p);
        if (text2[0] == '~')
        {
            char text3[4096];
            char * home;
            home = getenv("HOME");
            if (home)
            {
                if (text2[1] == '/')
                {
                    snprintf(text3, 4096, "%s/%s", home, text2 + 2);
                }
                else
                {
                    snprintf(text3, 4096, "%s/%s", home, text2 + 1);
                }
                rl_delete_text(rl_point - strlen(text2), rl_point);
                rl_point -= strlen(text2);
                rl_insert_text(text3);
                result_opendir = opendir(text3);
                xstrncpy(path, text3, 4096);
            }
            else
            {
                result_opendir = opendir(text2);
                xstrncpy(path, text2, 4096);
            }
        }
        if (text2[0] == '.' && text2[1] == '/')
        {
            result_opendir = opendir(".");
            xstrncpy(path, "./", 4096);
        }
        else if (text2[strlen(text2) - 1] == '/')
        {
            result_opendir = opendir(text2);
            xstrncpy(path, text2, 4096);
        }
        else
        {
            char * dirname_;
            dirname_ = dirname(text2);
            result_opendir = opendir(dirname_);
            if (strcmp(dirname_, ".") == 0)
            {
                path[0] = 0;
            }
            else
            {
                xstrncpy(path, dirname_, 4096);
                if (dirname_[strlen(dirname_) - 1] != '/')
                {
                    xstrncat(path, "/", 4096);
                }
            }
        }
        xfree(text2);
    }
    if (result_opendir)
    {
        int n;
        int size;
        n = 0;
        size = 128;
        gCandidates = xcalloc(1, sizeof(char *) * size);
        while (1)
        {
            struct dirent * result_readdir;
            int len;
            char * candidate;
            result_readdir = readdir(result_opendir);
            if (result_readdir == (void *) 0)
            {
                break;
            }
            if (strcmp(result_readdir->d_name,
                       ".") != 0 && strcmp(result_readdir->d_name, "..") != 0)
            {
                struct stat stat_;
                len = strlen(path) + strlen(result_readdir->d_name) + 2 + 1 + 1;
                candidate = xmalloc(len);
                xstrncpy(candidate, path, len);
                xstrncat(candidate, result_readdir->d_name, len);
                if (stat(candidate, &stat_) == 0)
                {
                    if ((stat_.st_mode & 0170000) == 040000)
                    {
                        xstrncat(candidate, "/", len);
                    }
                    gCandidates[n++] = candidate;
                    if (n >= size)
                    {
                        size *= 2;
                        gCandidates = xrealloc(gCandidates, sizeof(char *) * size);
                    }
                }
                else
                {
                    xfree(candidate);
                }
            }
        }
        gCandidates[n] = (void *) 0;
        gNumCandidates = n;
        closedir(result_opendir);
    }
}
void command_completion(char * line,
                        char * * candidates,
                        int num_candidates)
{
    int size;
    int i;
    int n;
    char * env;
    char path[4096];
    char * p;
    int len;
    size = 128 + num_candidates;
    gCandidates = xcalloc(1, sizeof(char *) * size);
    for (i = 0; i < num_candidates; i++)
    {
        gCandidates[i] = candidates[i];
    }
    n = num_candidates;
    env = getenv("PATH");
    p = path;
    len = strlen(env);
    for (i = 0; i < len; i++)
    {
        if (env[i] == ':')
        {
            *p = '\000';
            if (access(path, 0) == 0)
            {
                struct stat stat_;
                if (stat(path, &stat_) == 0 && (stat_.st_mode & 0170000) == 040000)
                {
                    DIR * dir;
                    dir = opendir(path);
                    if (dir)
                    {
                        while (1)
                        {
                            struct dirent * entry;
                            entry = readdir(dir);
                            if (entry == (void *) 0)
                            {
                                break;
                            }
                            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name,
                                                                          "..") != 0)
                            {
                                char path2[4096];
                                struct stat stat_;
                                xstrncpy(path2, path, 4096);
                                if (path[strlen(path) - 1] != '/')
                                {
                                    xstrncat(path2, "/", 4096);
                                }
                                xstrncat(path2, entry->d_name, 4096);
                                if (stat(path2, &stat_) == 0)
                                {
                                    if (stat_.st_mode & 0100)
                                    {
                                        char candidate[4096];
                                        snprintf(candidate, 4096, "%s(", entry->d_name);
                                        gCandidates[n++] = xstrdup(candidate);
                                        if (n >= size)
                                        {
                                            size *= 2;
                                            gCandidates = xrealloc(gCandidates,
                                                                   sizeof(char *) * size);
                                        }
                                        snprintf(candidate, 4096, "%s", entry->d_name);
                                        gCandidates[n++] = xstrdup(candidate);
                                        if (n >= size)
                                        {
                                            size *= 2;
                                            gCandidates = xrealloc(gCandidates,
                                                                   sizeof(char *) * size);
                                        }
                                    }
                                }
                            }
                        }
                        closedir(dir);
                    }
                }
            }
            p = path;
        }
        else
        {
            * (p++) = env[i];
            if (p - path >= 4096)
            {
                fprintf(stderr,
                        "The element of path in PATH environment variable is too long");
                return;
            }
        }
    }
    gCandidates[n] = (void *) 0;
    gNumCandidates = n;
}
void get_class_names(char * * candidates, int * num_candidates)
{
    sClassTable * p;
    p = gHeadClassTable;
    while (p)
    {
        candidates[*num_candidates] = xstrdup(p->mName);
        (*num_candidates)++;
        p = p->mNextClass;
    }
}
void get_global_method_names(char * * candidates,
                             int * num_candidates)
{
    sCLClass * global_class;
    int i;
    global_class = get_class("Global");
    ;
    for (i = 0; i < global_class->mNumMethods; i++)
    {
        sCLMethod * method;
        method = global_class->mMethods + i;
        if (method->mFlags & 0x2)
        {
            char * method_name;
            int len;
            char * candidate;
            method_name = (char *) ((&global_class->mConst)->mConst + method->mNameOffset);
            len = strlen(method_name) + 2;
            candidate = xmalloc(len);
            xstrncpy(candidate, method_name, len);
            xstrncat(candidate, "(", len);
            candidates[*num_candidates] = candidate;
            (*num_candidates)++;
        }
    }
}
void local_variable_completion(char * * candidates,
                               int * num_candidates,
                               int max_candidates)
{
    char * line2;
    sVarTable * lv_table;
    sNodeType * type_;
    sVarTable * tmp_lv_table;
    sVarTable * table;
    line2 = xcalloc(1, sizeof(char) * (rl_point + 1));
    memcpy(line2, rl_line_buffer, rl_point);
    line2[rl_point] = '\000';
    type_ = (void *) 0;
    tmp_lv_table = clone_var_table(gLVTable);
    (void) get_type(line2,
                    "iclover2",
                    tmp_lv_table,
                    gStack,
                    &type_,
                    &lv_table);
    table = lv_table;
    while (table)
    {
        int j;
        for (j = 0; j < 128; j++)
        {
            sVar * var;
            var = table->mLocalVariables + j;
            if (var->mName[0] != '\000')
            {
                if (*num_candidates < max_candidates)
                {
                    candidates[*num_candidates] = xstrdup(var->mName);
                    (*num_candidates)++;
                }
            }
        }
        table = table->mParent;
    }
    xfree(line2);
}
char * on_complete(const char * text, int a);
static int my_complete_internal(int count, int key)
{
    char * source;
    char * line;
    int in_double_quote;
    int in_single_quote;
    char * p;
    int inputing_command_line;
    int expression_is_void;
    int class_name_completion;
    gInputingMethod = 0;
    gInputingPath = 0;
    gInputingCommandPath = 0;
    gCandidates = (void *) 0;
    gNumCandidates = 0;
    source = line_buffer_from_head_to_cursor_point();
    line = get_one_expression(source);
    in_double_quote = 0;
    in_single_quote = 0;
    p = line;
    while (*p)
    {
        if (*p == '"')
        {
            p++;
            in_double_quote = !in_double_quote;
        }
        else if (*p == '\'')
        {
            p++;
            in_single_quote = !in_single_quote;
        }
        else if (*p == '\\')
        {
            p++;
            if (*p != '\000')
            {
                p++;
            }
        }
        else
        {
            p++;
        }
    }
    inputing_command_line = 0;
    p = line;
    while (*p)
    {
        if (*p == ' ' || *p == '\t')
        {
            p++;
        }
        else if ((*__ctype_b_loc())[(int) *p] & (unsigned short int) _ISalnum || *p == '-')
        {
            while ((*__ctype_b_loc())[(int) *p] & (unsigned short int) _ISalnum || *p == '-')
            {
                p++;
            }
            if (*p == ' ' || *p == '\t')
            {
                while (*p == ' ' || *p == '\t')
                {
                    p++;
                }
                if (*p != '(' && *p != '{')
                {
                    inputing_command_line = 1;
                    while (*p)
                    {
                        while (!(*p == ' ' || *p == '\t' || *p == '\000'))
                        {
                            p++;
                        }
                        while (*p == ' ' || *p == '\t')
                        {
                            p++;
                        }
                    }
                    break;
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    expression_is_void = 1;
    p = line;
    while (*p)
    {
        if (*p == ' ' || *p == '\t' || *p == '\n' || (*__ctype_b_loc())[(int) *p] & (unsigned short int) _ISalpha || *p == '(' || *p == '_')
        {
            p++;
        }
        else
        {
            expression_is_void = 0;
            p++;
        }
    }
    p = line + strlen(line) - 1;
    while (p >= line)
    {
        if ((*__ctype_b_loc())[(int) *p] & (unsigned short int) _ISalnum || *p == '_')
        {
            p--;
        }
        else
        {
            break;
        }
    }
    class_name_completion = 0;
    p = source + strlen(source) - 1;
    while (p >= source)
    {
        if ((*__ctype_b_loc())[(int) *p] & (unsigned short int) _ISalnum || *p == '_' || *p == ' ' || *p == '\t' || *p == ',')
        {
            p--;
        }
        else if (*p == ':' || *p == '<')
        {
            class_name_completion = 1;
            break;
        }
        else if (strstr(p, "new") == p)
        {
            class_name_completion = 1;
            break;
        }
        else
        {
            break;
        }
    }
    if (!in_double_quote && !in_single_quote && class_name_completion)
    {
        int num_candidates;
        int max_candidates;
        char * * candidates;
        int size;
        int i;
        num_candidates = 0;
        max_candidates = 512 + 128;
        candidates = xcalloc(1, sizeof(char *) * max_candidates);
        get_class_names(candidates, &num_candidates);
        size = 128 + num_candidates;
        gCandidates = xcalloc(1, sizeof(char *) * size);
        for (i = 0; i < num_candidates; i++)
        {
            gCandidates[i] = candidates[i];
        }
        gCandidates[i] = (void *) 0;
        gNumCandidates = i;
        xfree(candidates);
        gInputingMethod = 1;
        rl_completer_word_break_characters = "\t :<,";
    }
    else if (!in_double_quote && !in_single_quote && inputing_command_line)
    {
        rl_completion_entry_function = on_complete;
        file_completion_command_line(line);
        gInputingCommandPath = 1;
        rl_completer_word_break_characters = "\t ";
    }
    else if (expression_is_void)
    {
        char * words[];
        int num_words;
        int num_candidates;
        int max_candidates;
        char * * candidates;
        int i;
        rl_completion_entry_function = on_complete;
        num_words = 0;
        while (words[num_words])
        {
            num_words++;
        }
        num_candidates = 0;
        max_candidates = 512 + 256 + 128 + 128 * 3;
        candidates = xcalloc(1, sizeof(char *) * max_candidates);
        for (i = 0; i < num_words; i++)
        {
            candidates[i] = xstrdup(words[i]);
        }
        num_candidates += num_words;
        get_class_names(candidates, &num_candidates);
        get_global_method_names(candidates, &num_candidates);
        local_variable_completion(candidates,
                                  &num_candidates,
                                  max_candidates);
        command_completion(line, candidates, num_candidates);
        xfree(candidates);
        gInputingMethod = 1;
        rl_completer_word_break_characters = "\t\n.({ =";
    }
    else if (!in_double_quote && !in_single_quote && *p == '.')
    {
        char * p2;
        char * class_name;
        sCLClass * klass;
        rl_completion_entry_function = on_complete;
        p2 = p;
        p2--;
        while (p2 >= line)
        {
            if ((*__ctype_b_loc())[(int) *p2] & (unsigned short int) _ISalnum || *p2 == '_')
            {
                p2--;
            }
            else
            {
                break;
            }
        }
        p2++;
        class_name = xcalloc(1, sizeof(char) * (p - p2 + 1));
        memcpy(class_name, p2, p - p2);
        class_name[p - p2] = 0;
        klass = get_class(class_name);
        xfree(class_name);
        gCandidates = (void *) 0;
        gNumCandidates = 0;
        if (klass == (void *) 0)
        {
            char * line2;
            sNodeType * type_;
            sVarTable * result_lv_table;
            sVarTable * tmp_lv_table;
            line2 = xcalloc(1, sizeof(char) * (rl_point + 1));
            memcpy(line2, rl_line_buffer, rl_point);
            line2[rl_point] = '\000';
            type_ = (void *) 0;
            tmp_lv_table = clone_var_table(gLVTable);
            (void) get_type(line2,
                            "iclover2",
                            tmp_lv_table,
                            gStack,
                            &type_,
                            &result_lv_table);
            if (type_)
            {
                klass = type_->mClass;
                if (klass->mFlags & 0x1)
                {
                    klass = klass->mBoxingClass;
                }
                if (klass)
                {
                    if (strcmp((char *) ((&klass->mConst)->mConst + klass->mClassNameOffset),
                               "Command") == 0)
                    {
                        int num_methods;
                        char * * candidates;
                        num_methods = 0;
                        candidates = get_method_names_with_arguments(klass,
                                                                     0,
                                                                     &num_methods);
                        command_completion(line, candidates, num_methods);
                        xfree(candidates);
                    }
                    else
                    {
                        int num_methods;
                        num_methods = 0;
                        gCandidates = get_method_names_with_arguments(klass,
                                                                      0,
                                                                      &num_methods);
                        gNumCandidates = num_methods;
                    }
                }
            }
            xfree(line2);
        }
        else
        {
            int num_methods;
            num_methods = 0;
            gCandidates = get_method_names_with_arguments(klass,
                                                          1,
                                                          &num_methods);
            gNumCandidates = num_methods;
        }
        gInputingMethod = 1;
        rl_completer_word_break_characters = "\t\n.({";
    }
    else
    {
        rl_completion_entry_function = on_complete;
        file_completion(line);
        gInputingPath = 1;
        rl_completer_word_break_characters = "\t ";
    }
    xfree(source);
    return rl_complete(0, key);
}
static int name_sort(char * lfname, char * rfname)
{
    return strcmp(lfname, rfname) < 0;
}
static int quick_sort(int left, int right)
{
    int i;
    int j;
    if (left < right)
    {
        char * center_item;
        center_item = gCandidates[(left + right) / 2];
        i = left;
        j = right;
        do
        {
            while (1)
            {
                int ret;
                ret = name_sort(gCandidates[i], center_item);
                if (ret < 0)
                {
                    return 0;
                }
                if (gCandidates[i] == center_item || !ret)
                {
                    break;
                }
                i++;
            }
            while (1)
            {
                int ret;
                ret = name_sort(center_item, gCandidates[j]);
                if (ret < 0)
                {
                    return 0;
                }
                if (center_item == gCandidates[j] || !ret)
                {
                    break;
                }
                j--;
            }
            if (i <= j)
            {
                char * tmp;
                tmp = gCandidates[i];
                gCandidates[i] = gCandidates[j];
                gCandidates[j] = tmp;
                i++;
                j--;
            }
        }
        while (i <= j);
        if (!quick_sort(left, j))
        {
            return 0;
        }
        if (!quick_sort(i, right))
        {
            return 0;
        }
    }
    return 1;
}
void sort_candidates()
{
    quick_sort(0, gNumCandidates - 1);
}
char * on_complete(const char * text, int a)
{
    char * text2;
    text2 = xstrdup((char *) text);
    if (gInputingMethod)
    {
        char * p;
        rl_completion_append_character = '(';
        p = text2 + strlen(text2) - 1;
        while (p >= text2)
        {
            if (*p == '(')
            {
                char * tmp;
                tmp = xstrdup(p + 1);
                xfree(text2);
                text2 = tmp;
                break;
            }
            p--;
        }
    }
    else if (gInputingPath)
    {
        char * p;
        rl_completion_append_character = '"';
        p = text2 + strlen(text2) - 1;
        while (p >= text2)
        {
            if (*p == ' ' || *p == '\t' || *p == '"')
            {
                char * tmp;
                tmp = xstrdup(p + 1);
                xfree(text2);
                text2 = tmp;
                break;
            }
            p--;
        }
    }
    else if (gInputingCommandPath)
    {
        char * p;
        rl_completion_append_character = ' ';
        p = text2 + strlen(text2) - 1;
        while (p >= text2)
        {
            if (*p == ' ' || *p == '\t')
            {
                char * tmp;
                tmp = xstrdup(p + 1);
                xfree(text2);
                text2 = tmp;
                break;
            }
            p--;
        }
    }
    sort_candidates();
    if (gCandidates)
    {
        char * candidate;
        char * * p2;
        char * * candidates2;
        int num_candidates2;
        int j;
        p2 = gCandidates;
        candidates2 = xcalloc(1, sizeof(char *) * (gNumCandidates + 1));
        num_candidates2 = 0;
        while (p2 < gCandidates + gNumCandidates)
        {
            int len_candidate;
            int len_text;
            candidate = *p2;
            len_candidate = strlen(candidate);
            len_text = strlen(text2);
            if (len_candidate >= len_text && strncmp(candidate,
                                                     text2,
                                                     len_text) == 0)
            {
                candidates2[num_candidates2++] = candidate;
            }
            p2++;
        }
        candidates2[num_candidates2] = (void *) 0;
        if (num_candidates2 == 0)
        {
        }
        else if (num_candidates2 == 1)
        {
            char * appended_chars;
            int len_candidate;
            int len_text;
            char * parenthesis;
            char appended_chars2[32];
            int flg_field;
            candidate = *candidates2;
            flg_field = strstr(candidate,
                               "(") == (void *) 0 && !gInputingCommandPath;
            if (gInputingMethod)
            {
                parenthesis = strstr(candidate, "(");
                if (parenthesis)
                {
                    len_candidate = parenthesis - candidate;
                }
                else
                {
                    len_candidate = strlen(candidate);
                }
            }
            else
            {
                len_candidate = strlen(candidate);
            }
            len_text = strlen(text2);
            appended_chars = xcalloc(1, len_candidate - len_text + 2);
            memcpy(appended_chars,
                   candidate + len_text,
                   len_candidate - len_text);
            appended_chars[len_candidate - len_text] = 0;
            rl_insert_text(appended_chars);
            xfree(appended_chars);
            if (gInputingPath)
            {
                int len;
                len = strlen(candidate);
                if (candidate[len - 1] != '/')
                {
                    appended_chars2[0] = rl_completion_append_character;
                    appended_chars2[1] = 0;
                    rl_insert_text(appended_chars2);
                }
            }
            else if (gInputingCommandPath)
            {
                int len;
                len = strlen(candidate);
                if (candidate[len - 1] != '/')
                {
                    appended_chars2[0] = rl_completion_append_character;
                    appended_chars2[1] = 0;
                    rl_insert_text(appended_chars2);
                }
            }
            else if (gInputingMethod)
            {
                int len;
                len = strlen(candidate);
                if (candidate[len - 1] == '(')
                {
                    appended_chars2[0] = rl_completion_append_character;
                    appended_chars2[1] = 0;
                    rl_insert_text(appended_chars2);
                }
            }
            else if (flg_field)
            {
                appended_chars2[0] = '.';
                appended_chars2[1] = 0;
                rl_insert_text(appended_chars2);
            }
            else
            {
                rl_insert_text(appended_chars2);
            }
            display_candidates(candidates2);
            rl_forced_update_display();
        }
        else
        {
            char * candidate_before;
            int same_len;
            candidate_before = (void *) 0;
            same_len = -1;
            p2 = candidates2;
            while ((candidate = *p2) != (void *) 0)
            {
                int i;
                int len_candidate;
                int len_candidate_before;
                if (candidate_before)
                {
                    int len;
                    int same_len2;
                    char * parenthesis;
                    parenthesis = strstr(candidate, "(");
                    if (parenthesis)
                    {
                        len_candidate = parenthesis - candidate;
                    }
                    else
                    {
                        len_candidate = strlen(candidate);
                    }
                    parenthesis = strstr(candidate_before, "(");
                    if (parenthesis)
                    {
                        len_candidate_before = parenthesis - candidate_before;
                    }
                    else
                    {
                        len_candidate_before = strlen(candidate_before);
                    }
                    if (len_candidate < len_candidate_before)
                    {
                        len = len_candidate;
                    }
                    else
                    {
                        len = len_candidate_before;
                    }
                    same_len2 = len;
                    for (i = 0; i < len; i++)
                    {
                        if (candidate[i] != candidate_before[i])
                        {
                            same_len2 = i;
                            break;
                        }
                    }
                    if (same_len == -1 || same_len2 < same_len)
                    {
                        same_len = same_len2;
                    }
                }
                candidate_before = *p2;
                p2++;
            }
            candidate = *candidates2;
            if (same_len > 0)
            {
                char * appended_chars;
                int len_candidate;
                int len_text;
                len_candidate = strlen(candidate);
                len_text = strlen(text2);
                if (same_len - len_text == 0)
                {
                    display_candidates(candidates2);
                    rl_forced_update_display();
                }
                else
                {
                    appended_chars = xcalloc(1, same_len - len_text + 2);
                    memcpy(appended_chars, candidate + len_text, same_len - len_text);
                    appended_chars[same_len - len_text] = 0;
                    rl_insert_text(appended_chars);
                    xfree(appended_chars);
                }
            }
            else if (same_len == 0)
            {
                display_candidates(candidates2);
                rl_forced_update_display();
            }
        }
        xfree(candidates2);
        for (j = 0; j < gNumCandidates; j++)
        {
            xfree(gCandidates[j]);
        }
        xfree(gCandidates);
    }
    xfree(text2);
    return 0;
}
static int inputing_block_or_paren()
{
    char * source;
    char * p;
    int block_nest;
    int paren_nest;
    source = rl_line_buffer;
    p = source;
    block_nest = 0;
    paren_nest = 0;
    while (*p)
    {
        if (*p == '{')
        {
            p++;
            block_nest++;
        }
        else if (*p == '}')
        {
            p++;
            block_nest--;
        }
        else if (*p == '(')
        {
            p++;
            paren_nest++;
        }
        else if (*p == ')')
        {
            p++;
            paren_nest--;
        }
        else
        {
            p++;
        }
    }
    return block_nest > 0 || paren_nest > 0;
}
static int my_bind_cr(int count, int key)
{
    if (inputing_block_or_paren())
    {
        rl_insert_text("\n");
    }
    else
    {
        puts("");
        rl_done = 1;
    }
    return 0;
}
static void sig_int()
{
    gSigInt = 1;
    rl_reset_line_state();
    rl_replace_line("", 0);
    rl_point = 0;
    puts("");
    rl_redisplay();
}
static void set_signal_for_interpreter()
{
    struct sigaction sa;
    sigset_t signal_set;
    memset(&sa, 0, sizeof(sa));
    sa.sa_flags = 4;
    sa.__sigaction_handler.sa_handler = sig_int;
    if (sigaction(2, &sa, (void *) 0) < 0)
    {
        perror("sigaction2");
        exit(1);
    }
    sigemptyset(&signal_set);
    sigaddset(&signal_set, 22);
    sigaddset(&signal_set, 13);
    sigprocmask(0, &signal_set, (void *) 0);
}
static sByteCode gCodes[1024 * 4];
static sConst gConst[1024 * 4];
static int gNumCodes;
static void interpreter_init()
{
    gInterpreter = 1;
    memset(gCodes, 0, sizeof(sByteCode) * 1024 * 4);
    memset(gConst, 0, sizeof(sConst) * 1024 * 4);
    gNumCodes = 0;
}
static void interpreter_final()
{
    int i;
    for (i = 0; i < gNumCodes; i++)
    {
        sByteCode_free(&gCodes[i]);
        sConst_free(&gConst[i]);
    }
}
static int eval_str(char * source,
                    char * fname,
                    sVarTable * lv_table,
                    CLVALUE * stack)
{
    sParserInfo info;
    sCompileInfo cinfo;
    sByteCode * code;
    sConst * constant;
    int var_num;
    sVMInfo vinfo;
    memset(&info, 0, sizeof(sParserInfo));
    info.p = source;
    info.sname = fname;
    info.sline = 1;
    info.lv_table = lv_table;
    info.parse_phase = 0;
    info.get_type_for_interpreter = 0;
    memset(&cinfo, 0, sizeof(sCompileInfo));
    code = &gCodes[gNumCodes];
    sByteCode_init(code);
    cinfo.code = code;
    constant = &gConst[gNumCodes];
    sConst_init(constant);
    cinfo.constant = constant;
    gNumCodes++;
    if (gNumCodes >= 1024 * 4)
    {
        fprintf(stderr, "overflow code and constant size. reset iclover2");
        exit(1);
    }
    cinfo.lv_table = lv_table;
    cinfo.no_output = 0;
    cinfo.pinfo = &info;
    info.cinfo = &cinfo;
    while (*info.p)
    {
        unsigned int node;
        info.next_command_is_to_bool = 0;
        node = 0;
        info.exist_block_object_err = 0;
        if (!expression(&node, &info))
        {
            return 0;
        }
        cinfo.sname = gNodes[node].mSName;
        cinfo.sline = gNodes[node].mLine;
        if (info.err_num == 0 && node != 0)
        {
            sCLClass * klass;
            append_opecode_to_code(cinfo.code, 14, cinfo.no_output);
            append_opecode_to_code(cinfo.code, 15, cinfo.no_output);
            append_str_to_constant_pool_and_code(cinfo.constant,
                                                 cinfo.code,
                                                 cinfo.sname,
                                                 cinfo.no_output);
            append_int_value_to_code(cinfo.code, cinfo.sline, cinfo.no_output);
            if (!compile(node, &cinfo))
            {
                return 0;
            }
            klass = cinfo.type->mClass;
            if (klass->mFlags & 0x1)
            {
                cast_right_type_to_String(&cinfo.type, &cinfo);
                if (type_identify_with_class_name(cinfo.type, "String"))
                {
                    sCLClass * string_class;
                    sNodeType * result_type;
                    sNodeType * result_method_generics_types;
                    int method_index;
                    string_class = get_class("String");
                    ;
                    result_type = (void *) 0;
                    result_method_generics_types = (void *) 0;
                    method_index = search_for_method(string_class,
                                                     "chomp",
                                                     (void *) 0,
                                                     0,
                                                     0,
                                                     string_class->mNumMethods - 1,
                                                     (void *) 0,
                                                     (void *) 0,
                                                     (void *) 0,
                                                     &result_type,
                                                     0,
                                                     0,
                                                     &result_method_generics_types);
                    if (method_index != -1)
                    {
                        int size;
                        append_opecode_to_code(cinfo.code, 3000, cinfo.no_output);
                        append_class_name_to_constant_pool_and_code(&cinfo, string_class);
                        append_int_value_to_code(cinfo.code,
                                                 method_index,
                                                 cinfo.no_output);
                        size = get_var_size(result_type);
                        append_int_value_to_code(cinfo.code, size, cinfo.no_output);
                        cinfo.stack_num--;
                        cinfo.stack_num++;
                        cinfo.type = result_type;
                    }
                    result_method_generics_types = (void *) 0;
                    method_index = search_for_method(string_class,
                                                     "printlnWithoutNullString",
                                                     (void *) 0,
                                                     0,
                                                     0,
                                                     string_class->mNumMethods - 1,
                                                     (void *) 0,
                                                     (void *) 0,
                                                     (void *) 0,
                                                     &result_type,
                                                     0,
                                                     0,
                                                     &result_method_generics_types);
                    if (method_index != -1)
                    {
                        int size;
                        append_opecode_to_code(cinfo.code, 3000, cinfo.no_output);
                        append_class_name_to_constant_pool_and_code(&cinfo, string_class);
                        append_int_value_to_code(cinfo.code,
                                                 method_index,
                                                 cinfo.no_output);
                        size = get_var_size(result_type);
                        append_int_value_to_code(cinfo.code, size, cinfo.no_output);
                        cinfo.stack_num--;
                        cinfo.stack_num++;
                        cinfo.type = result_type;
                    }
                }
            }
            else
            {
                sNodeType * result_type;
                sNodeType * result_method_generics_types;
                int method_index;
                result_type = (void *) 0;
                result_method_generics_types = (void *) 0;
                method_index = search_for_method(klass,
                                                 "toString",
                                                 (void *) 0,
                                                 0,
                                                 0,
                                                 klass->mNumMethods - 1,
                                                 (void *) 0,
                                                 (void *) 0,
                                                 (void *) 0,
                                                 &result_type,
                                                 0,
                                                 0,
                                                 &result_method_generics_types);
                if (method_index != -1)
                {
                    int size;
                    sCLClass * string_class;
                    sNodeType * result_type;
                    sNodeType * result_method_generics_types;
                    int method_index;
                    append_opecode_to_code(cinfo.code, 3000, cinfo.no_output);
                    append_class_name_to_constant_pool_and_code(&cinfo, klass);
                    append_int_value_to_code(cinfo.code,
                                             method_index,
                                             cinfo.no_output);
                    size = get_var_size(result_type);
                    append_int_value_to_code(cinfo.code, size, cinfo.no_output);
                    cinfo.stack_num--;
                    cinfo.stack_num++;
                    cinfo.type = result_type;
                    string_class = get_class("String");
                    ;
                    result_type = (void *) 0;
                    result_method_generics_types = (void *) 0;
                    method_index = search_for_method(string_class,
                                                     "chomp",
                                                     (void *) 0,
                                                     0,
                                                     0,
                                                     string_class->mNumMethods - 1,
                                                     (void *) 0,
                                                     (void *) 0,
                                                     (void *) 0,
                                                     &result_type,
                                                     0,
                                                     0,
                                                     &result_method_generics_types);
                    if (method_index != -1)
                    {
                        int size;
                        append_opecode_to_code(cinfo.code, 3000, cinfo.no_output);
                        append_class_name_to_constant_pool_and_code(&cinfo, string_class);
                        append_int_value_to_code(cinfo.code,
                                                 method_index,
                                                 cinfo.no_output);
                        size = get_var_size(result_type);
                        append_int_value_to_code(cinfo.code, size, cinfo.no_output);
                        cinfo.stack_num--;
                        cinfo.stack_num++;
                        cinfo.type = result_type;
                    }
                    result_type = (void *) 0;
                    result_method_generics_types = (void *) 0;
                    method_index = search_for_method(string_class,
                                                     "printlnWithoutNullString",
                                                     (void *) 0,
                                                     0,
                                                     0,
                                                     string_class->mNumMethods - 1,
                                                     (void *) 0,
                                                     (void *) 0,
                                                     (void *) 0,
                                                     &result_type,
                                                     0,
                                                     0,
                                                     &result_method_generics_types);
                    if (method_index != -1)
                    {
                        int size;
                        append_opecode_to_code(cinfo.code, 3000, cinfo.no_output);
                        append_class_name_to_constant_pool_and_code(&cinfo, string_class);
                        append_int_value_to_code(cinfo.code,
                                                 method_index,
                                                 cinfo.no_output);
                        size = get_var_size(result_type);
                        append_int_value_to_code(cinfo.code, size, cinfo.no_output);
                        cinfo.stack_num--;
                        cinfo.stack_num++;
                        cinfo.type = result_type;
                    }
                }
            }
            arrange_stack(&cinfo);
        }
        if (*info.p == ';')
        {
            info.p++;
            skip_spaces_and_lf(&info);
        }
    }
    if (info.err_num > 0 || cinfo.err_num > 0)
    {
        fprintf(stderr,
                "Parser error number is %d. Compile error number is %d\n",
                info.err_num,
                cinfo.err_num);
        return 0;
    }
    var_num = get_var_num(info.lv_table);
    memset(&vinfo, 0, sizeof(sVMInfo));
    if (!vm(code, constant, stack, var_num, (void *) 0, &vinfo))
    {
        show_exception_message(vinfo.exception_message);
        return 0;
    }
    return 1;
}
static void clover2_init()
{
    native_method_init();
    class_init();
    heap_init(128, 128);
    stack_init();
    (void) class_init_on_runtime();
}
static void clover2_final()
{
    class_final_on_runtime();
    heap_final();
    stack_final();
    class_final();
    native_method_final();
}
static void compiler_init(int no_load_fudamental_classes)
{
    init_nodes();
    module_init();
}
static void compiler_final()
{
    module_final();
    free_nodes();
}
int main(int argc, char * * argv)
{
    char history_path[4096];
    sVarTable * lv_table;
    int stack_size;
    CLVALUE * stack;
    ;
    setlocale(6, "");
    srandom((unsigned) time((void *) 0));
    setsid();
    set_signal_for_interpreter();
    rl_basic_word_break_characters = "\t\n";
    rl_completion_entry_function = on_complete;
    snprintf(history_path,
             4096,
             "%s/.clover2/history",
             getenv("HOME"));
    if (access(history_path, 4) == 0)
    {
        read_history(history_path);
    }
    init_vtable();
    init_node_types();
    init_node_block_types();
    clover2_init();
    interpreter_init();
    parser_init();
    rl_bind_key('\t', my_complete_internal);
    rl_bind_key('\n', my_bind_cr);
    rl_bind_key('\r', my_bind_cr);
    printf("Welcome to Clover2\n");
    lv_table = init_var_table();
    stack_size = 512;
    stack = xcalloc(1, sizeof(CLVALUE) * stack_size);
    gStack = stack;
    gLVTable = lv_table;
    while (1)
    {
        char * line;
        char * p;
        compiler_init(0);
        line = readline("> ");
        if (line == (void *) 0)
        {
            compiler_final();
            break;
        }
        p = line + strlen(line) - 1;
        while (p >= line)
        {
            if (*p == ' ' || *p == '\t' || *p == '\n')
            {
                *p = '\000';
                p--;
            }
            else
            {
                break;
            }
        }
        if (line[strlen(line) - 1] == ';')
        {
            line[strlen(line) - 1] = '\000';
        }
        if (!eval_str(line, "iclover2", lv_table, stack))
        {
            fprintf(stderr, "compile or runtime error\n");
        }
        compiler_final();
        add_history(line);
        free(line);
    }
    parser_final();
    interpreter_final();
    clover2_final();
    final_vtable();
    free_node_types();
    free_node_block_types();
    xfree(stack);
    write_history(history_path);
    ;
    exit(0);
}
