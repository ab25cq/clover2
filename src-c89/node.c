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
sNodeTree * gNodes;
static unsigned int gSizeNodes = 0;
static unsigned int gUsedNodes = 0;
static unsigned int gLabelNum = 0;
void init_nodes()
{
    const int node_size;
    node_size = 32;
    gLabelNum = 0;
    if (gUsedNodes == 0)
    {
        gNodes = xcalloc(1, sizeof(sNodeTree) * node_size);
        gSizeNodes = node_size;
        gUsedNodes = 1;
    }
}
void free_nodes()
{
    if (gUsedNodes > 0)
    {
        int i;
        for (i = 1; i < gUsedNodes; i++)
        {
            switch (gNodes[i].mNodeType)
            {
            case kNodeTypeIf:
                {
                    int j;
                    if (gNodes[i].uValue.sIf.mIfNodeBlock)
                    {
                        sNodeBlock_free(gNodes[i].uValue.sIf.mIfNodeBlock);
                    }
                    for (j = 0; j < gNodes[i].uValue.sIf.mElifNum; j++)
                    {
                        sNodeBlock * node_block;
                        node_block = gNodes[i].uValue.sIf.mElifNodeBlocks[j];
                        if (node_block)
                        {
                            sNodeBlock_free(node_block);
                        }
                    }
                    if (gNodes[i].uValue.sIf.mElseNodeBlock)
                    {
                        sNodeBlock_free(gNodes[i].uValue.sIf.mElseNodeBlock);
                    }
                }
                break;
            case kNodeTypeWhile:
                if (gNodes[i].uValue.sWhile.mWhileNodeBlock)
                {
                    sNodeBlock_free(gNodes[i].uValue.sWhile.mWhileNodeBlock);
                }
                break;
            case kNodeTypeTry:
                if (gNodes[i].uValue.sTry.mTryNodeBlock)
                {
                    sNodeBlock_free(gNodes[i].uValue.sTry.mTryNodeBlock);
                }
                if (gNodes[i].uValue.sTry.mCatchNodeBlock)
                {
                    sNodeBlock_free(gNodes[i].uValue.sTry.mCatchNodeBlock);
                }
                break;
            case kNodeTypeFor:
                if (gNodes[i].uValue.sFor.mForNodeBlock)
                {
                    sNodeBlock_free(gNodes[i].uValue.sFor.mForNodeBlock);
                }
                break;
            case kNodeTypeString:
                xfree(gNodes[i].uValue.sString.mString);
                break;
            case kNodeTypePath:
                xfree(gNodes[i].uValue.sString.mString);
                break;
            case kNodeTypeBuffer:
                xfree(gNodes[i].uValue.sBuffer.mBuffer);
                break;
            case kNodeTypeBlockObject:
                if (gNodes[i].uValue.sBlockObject.mBlockObjectCode)
                {
                    sNodeBlock_free(gNodes[i].uValue.sBlockObject.mBlockObjectCode);
                }
                break;
            case kNodeTypeNormalBlock:
                if (gNodes[i].uValue.mBlock)
                {
                    sNodeBlock_free(gNodes[i].uValue.mBlock);
                }
                break;
            case kNodeTypeRegex:
                xfree(gNodes[i].uValue.sRegex.mRegexStr);
                break;
            default:
                break;
            }
        }
        xfree(gNodes);
        gSizeNodes = 0;
        gUsedNodes = 0;
    }
}
int get_var_size(sNodeType * var_type)
{
    int size;
    size = 0;
    if (var_type->mClass->mFlags & 0x2)
    {
        size = 32;
    }
    else if (type_identify_with_class_name(var_type,
                                           "byte") || type_identify_with_class_name(var_type,
                                                                                    "ubyte"))
    {
        size = 8;
    }
    else if (type_identify_with_class_name(var_type,
                                           "short") || type_identify_with_class_name(var_type,
                                                                                     "ushort"))
    {
        size = 16;
    }
    else if (type_identify_with_class_name(var_type,
                                           "int") || type_identify_with_class_name(var_type,
                                                                                   "uint"))
    {
        size = 32;
    }
    else if (type_identify_with_class_name(var_type,
                                           "long") || type_identify_with_class_name(var_type,
                                                                                    "ulong"))
    {
        size = 64;
    }
    else if (type_identify_with_class_name(var_type, "float"))
    {
        size = 128;
    }
    else if (type_identify_with_class_name(var_type, "double"))
    {
        size = 256;
    }
    else if (type_identify_with_class_name(var_type, "bool"))
    {
        size = 1;
    }
    else if (type_identify_with_class_name(var_type, "char"))
    {
        size = 32;
    }
    else if (type_identify_with_class_name(var_type, "pointer"))
    {
        size = 1024;
    }
    else
    {
        size = 32;
    }
    return size;
}
static void create_label_name(char * prefix,
                              char * result,
                              size_t result_size,
                              int num)
{
    int n;
    xstrncpy(result, prefix, result_size);
    n = num;
    while (1)
    {
        if (n > 'z' - 'a')
        {
            xstrncat(result, "z", result_size);
            n -= 'z' - 'a';
        }
        else
        {
            char str[2];
            str[0] = n + 'a';
            str[1] = 0;
            xstrncat(result, str, result_size);
            break;
        }
    }
}
static void create_label_name2(char * prefix,
                               char * result,
                               size_t result_size,
                               int num,
                               int num2)
{
    int n;
    char buf[128];
    xstrncpy(result, prefix, result_size);
    n = num;
    while (1)
    {
        if (n > 'z' - 'a')
        {
            xstrncat(result, "z", result_size);
            n -= 'z' - 'a';
        }
        else
        {
            char str[2];
            str[0] = n + 'a';
            str[1] = 0;
            xstrncat(result, str, result_size);
            break;
        }
    }
    snprintf(buf, 128, "%da", num2);
    xstrncat(result, buf, result_size);
}
static unsigned int alloc_node()
{
    if (gSizeNodes == gUsedNodes)
    {
        int new_size;
        new_size = (gSizeNodes + 1) * 2;
        gNodes = xrealloc(gNodes, sizeof(sNodeTree) * new_size);
        memset(gNodes + gSizeNodes,
               0,
               sizeof(sNodeTree) * (new_size - gSizeNodes));
        gSizeNodes = new_size;
    }
    return gUsedNodes++;
}
unsigned int clone_node(unsigned int node)
{
    unsigned int result;
    result = alloc_node();
    memcpy(gNodes + result, gNodes + node, sizeof(sNodeTree));
    switch (gNodes[node].mNodeType)
    {
    case kNodeTypeIf:
        {
            int j;
            if (gNodes[node].uValue.sIf.mIfNodeBlock)
            {
                gNodes[result].uValue.sIf.mIfNodeBlock = sNodeBlock_clone(gNodes[node].uValue.sIf.mIfNodeBlock);
            }
            for (j = 0; j < gNodes[node].uValue.sIf.mElifNum; j++)
            {
                sNodeBlock * node_block;
                node_block = gNodes[node].uValue.sIf.mElifNodeBlocks[j];
                if (node_block)
                {
                    gNodes[result].uValue.sIf.mElifNodeBlocks[j] = sNodeBlock_clone(node_block);
                }
            }
            if (gNodes[node].uValue.sIf.mElseNodeBlock)
            {
                gNodes[result].uValue.sIf.mElseNodeBlock = sNodeBlock_clone(gNodes[node].uValue.sIf.mElseNodeBlock);
            }
        }
        break;
    case kNodeTypeWhile:
        if (gNodes[node].uValue.sWhile.mWhileNodeBlock)
        {
            gNodes[result].uValue.sWhile.mWhileNodeBlock = sNodeBlock_clone(gNodes[node].uValue.sWhile.mWhileNodeBlock);
        }
        break;
    case kNodeTypeTry:
        if (gNodes[node].uValue.sTry.mTryNodeBlock)
        {
            gNodes[result].uValue.sTry.mTryNodeBlock = sNodeBlock_clone(gNodes[node].uValue.sTry.mTryNodeBlock);
        }
        if (gNodes[node].uValue.sTry.mCatchNodeBlock)
        {
            gNodes[result].uValue.sTry.mCatchNodeBlock = sNodeBlock_clone(gNodes[node].uValue.sTry.mCatchNodeBlock);
        }
        break;
    case kNodeTypeFor:
        if (gNodes[node].uValue.sFor.mForNodeBlock)
        {
            gNodes[result].uValue.sFor.mForNodeBlock = sNodeBlock_clone(gNodes[node].uValue.sFor.mForNodeBlock);
        }
        break;
    case kNodeTypeString:
        gNodes[result].uValue.sString.mString = xstrdup(gNodes[node].uValue.sString.mString);
        break;
    case kNodeTypePath:
        gNodes[result].uValue.sString.mString = xstrdup(gNodes[node].uValue.sString.mString);
        break;
    case kNodeTypeBuffer:
        {
            int len;
            len = gNodes[node].uValue.sBuffer.mLen;
            gNodes[result].uValue.sBuffer.mBuffer = xcalloc(1, len);
            memcpy(gNodes[result].uValue.sBuffer.mBuffer,
                   gNodes[node].uValue.sBuffer.mBuffer,
                   len);
        }
        break;
    case kNodeTypeBlockObject:
        if (gNodes[node].uValue.sBlockObject.mBlockObjectCode)
        {
            gNodes[result].uValue.sBlockObject.mBlockObjectCode = sNodeBlock_clone(gNodes[node].uValue.sBlockObject.mBlockObjectCode);
        }
        break;
    case kNodeTypeNormalBlock:
        if (gNodes[node].uValue.mBlock)
        {
            gNodes[result].uValue.mBlock = sNodeBlock_clone(gNodes[node].uValue.mBlock);
        }
        break;
    case kNodeTypeRegex:
        gNodes[result].uValue.sRegex.mRegexStr = xstrdup(gNodes[node].uValue.sRegex.mRegexStr);
        break;
    default:
        break;
    }
    return result;
}
void append_class_name_to_constant_pool_and_code(sCompileInfo * info,
                                                 sCLClass * klass)
{
    char class_name[64];
    xstrncpy(class_name,
             (char *) ((&klass->mConst)->mConst + klass->mClassNameOffset),
             64);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         class_name,
                                         info->no_output);
}
static void append_type_name_to_constant_pool_and_code(sCompileInfo * info,
                                                       sNodeType * node_type)
{
    char type_name[128];
    xstrncpy(type_name, "", 128);
    create_type_name_from_node_type(type_name, 128, node_type);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         type_name,
                                         info->no_output);
}
static void append_method_name_and_params_to_constant_pool_and_code(sCompileInfo * info,
                                                                    sCLClass * klass,
                                                                    sCLMethod * method)
{
    int size_method_name_and_params;
    char method_name_and_params[size_method_name_and_params];
    size_method_name_and_params = 64 + 32 * 64 + 256;
    xstrncpy(method_name_and_params,
             (char *) ((&klass->mConst)->mConst + method->mMethodNameAndParamsOffset),
             size_method_name_and_params);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         method_name_and_params,
                                         info->no_output);
}
void compile_err_msg(sCompileInfo * info, const char * msg, ...)
{
    char msg2[1024];
    va_list args;
    __builtin_va_start(args, msg);
    vsnprintf(msg2, 1024, msg, args);
    __builtin_va_end(args);
    if (!info->pinfo->get_type_for_interpreter)
    {
        fprintf(stderr, "%s %d: %s\n", info->sname, info->sline, msg2);
    }
}
void arrange_stack(sCompileInfo * cinfo)
{
    if (cinfo->no_pop_next)
    {
        cinfo->no_pop_next = 0;
    }
    else if (cinfo->stack_num < 0)
    {
        compile_err_msg(cinfo,
                        "Unexpected error. Stack pointer is invalid(stack number is %d)",
                        cinfo->stack_num);
        cinfo->err_num++;
    }
    else if (cinfo->stack_num == 0)
    {
    }
    else if (cinfo->stack_num == 1)
    {
        append_opecode_to_code(cinfo->code, 1, cinfo->no_output);
    }
    else
    {
        append_opecode_to_code(cinfo->code, 2, cinfo->no_output);
        append_int_value_to_code(cinfo->code,
                                 cinfo->stack_num,
                                 cinfo->no_output);
    }
    cinfo->stack_num = 0;
}
static void err_msg_for_method_not_found(sCLClass * klass,
                                         char * method_name,
                                         sNodeType * * param_types,
                                         int num_params,
                                         int class_method,
                                         sCompileInfo * info)
{
    int i;
    compile_err_msg(info,
                    "%s.%s(%d prametors) is not found",
                    (char *) ((&klass->mConst)->mConst + klass->mClassNameOffset),
                    method_name,
                    num_params);
    for (i = 0; i < num_params; i++)
    {
        if (param_types[i] == (void *) 0 || param_types[i]->mClass == (void *) 0)
        {
            compile_err_msg(info,
                            "parametor#%d is NULL(unexpected parametor)",
                            i);
        }
        else
        {
            compile_err_msg(info,
                            "parametor#%d is %s",
                            i,
                            (char *) ((&param_types[i]->mClass->mConst)->mConst + param_types[i]->mClass->mClassNameOffset));
        }
    }
}
unsigned int sNodeTree_create_operand(enum eOperand operand,
                                      unsigned int left,
                                      unsigned int right,
                                      unsigned int middle,
                                      sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeOperand;
    gNodes[node].uValue.mOperand = operand;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;
    gNodes[node].mType = (void *) 0;
    return node;
}
static int single_operator(sNodeType * type,
                           int byte_operand,
                           int ubyte_operand,
                           int short_operand,
                           int ushort_operand,
                           int int_operand,
                           int uint_operand,
                           int long_operand,
                           int ulong_operand,
                           sCompileInfo * info)
{
    if (type_identify_with_class_name(type, "byte"))
    {
        append_opecode_to_code(info->code, byte_operand, info->no_output);
        info->type = create_node_type_with_class_name("byte");
    }
    else if (type_identify_with_class_name(type, "ubyte"))
    {
        append_opecode_to_code(info->code, ubyte_operand, info->no_output);
        info->type = create_node_type_with_class_name("ubyte");
    }
    else if (type_identify_with_class_name(type, "short"))
    {
        append_opecode_to_code(info->code, short_operand, info->no_output);
        info->type = create_node_type_with_class_name("short");
    }
    else if (type_identify_with_class_name(type, "ushort"))
    {
        append_opecode_to_code(info->code,
                               ushort_operand,
                               info->no_output);
        info->type = create_node_type_with_class_name("ushort");
    }
    else if (type_identify_with_class_name(type, "int"))
    {
        append_opecode_to_code(info->code, int_operand, info->no_output);
        info->type = create_node_type_with_class_name("int");
    }
    else if (type_identify_with_class_name(type, "uint"))
    {
        append_opecode_to_code(info->code, uint_operand, info->no_output);
        info->type = create_node_type_with_class_name("uint");
    }
    else if (type_identify_with_class_name(type, "long"))
    {
        append_opecode_to_code(info->code, long_operand, info->no_output);
        info->type = create_node_type_with_class_name("long");
    }
    else if (type_identify_with_class_name(type, "ulong"))
    {
        append_opecode_to_code(info->code, ulong_operand, info->no_output);
        info->type = create_node_type_with_class_name("ulong");
    }
    return 1;
}
static int binary_operator(sNodeType * left_type,
                           sNodeType * right_type,
                           int byte_operand,
                           int ubyte_operand,
                           int short_operand,
                           int ushort_operand,
                           int int_operand,
                           int uint_operand,
                           int long_operand,
                           int ulong_operand,
                           int float_operand,
                           int double_operand,
                           int pointer_operand,
                           int null_operand,
                           int char_operand,
                           int bool_operand,
                           int regex_operand,
                           char * op_string,
                           sCompileInfo * info)
{
    if (!no_cast_types_for_binary_operator(left_type, right_type))
    {
        cast_right_type_to_left_type(left_type, &right_type, info);
    }
    if (!operand_posibility(left_type, right_type, op_string))
    {
        compile_err_msg(info,
                        "Invalid type for operand(%s). The left type is %s. The right type is %s.",
                        op_string,
                        (char *) ((&left_type->mClass->mConst)->mConst + left_type->mClass->mClassNameOffset),
                        (char *) ((&right_type->mClass->mConst)->mConst + right_type->mClass->mClassNameOffset));
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    if (type_identify_with_class_name(left_type,
                                      "byte") && byte_operand != -1)
    {
        append_opecode_to_code(info->code, byte_operand, info->no_output);
        info->stack_num--;
        info->type = create_node_type_with_class_name("byte");
    }
    else if (type_identify_with_class_name(left_type,
                                           "ubyte") && ubyte_operand != -1)
    {
        append_opecode_to_code(info->code, ubyte_operand, info->no_output);
        info->stack_num--;
        info->type = create_node_type_with_class_name("ubyte");
    }
    else if (type_identify_with_class_name(left_type,
                                           "short") && short_operand != -1)
    {
        append_opecode_to_code(info->code, short_operand, info->no_output);
        info->stack_num--;
        info->type = create_node_type_with_class_name("short");
    }
    else if (type_identify_with_class_name(left_type,
                                           "ushort") && ushort_operand != -1)
    {
        append_opecode_to_code(info->code,
                               ushort_operand,
                               info->no_output);
        info->stack_num--;
        info->type = create_node_type_with_class_name("ushort");
    }
    else if (type_identify_with_class_name(left_type,
                                           "int") && int_operand != -1)
    {
        append_opecode_to_code(info->code, int_operand, info->no_output);
        info->stack_num--;
        info->type = create_node_type_with_class_name("int");
    }
    else if (type_identify_with_class_name(left_type,
                                           "uint") && uint_operand != -1)
    {
        append_opecode_to_code(info->code, uint_operand, info->no_output);
        info->stack_num--;
        info->type = create_node_type_with_class_name("uint");
    }
    else if (type_identify_with_class_name(left_type,
                                           "long") && long_operand != -1)
    {
        append_opecode_to_code(info->code, long_operand, info->no_output);
        info->stack_num--;
        info->type = create_node_type_with_class_name("long");
    }
    else if (type_identify_with_class_name(left_type,
                                           "ulong") && ulong_operand != -1)
    {
        append_opecode_to_code(info->code, ulong_operand, info->no_output);
        info->stack_num--;
        info->type = create_node_type_with_class_name("ulong");
    }
    else if (type_identify_with_class_name(left_type,
                                           "float") && float_operand != -1)
    {
        append_opecode_to_code(info->code, float_operand, info->no_output);
        info->stack_num--;
        info->type = create_node_type_with_class_name("float");
    }
    else if (type_identify_with_class_name(left_type,
                                           "double") && double_operand != -1)
    {
        append_opecode_to_code(info->code,
                               double_operand,
                               info->no_output);
        info->stack_num--;
        info->type = create_node_type_with_class_name("double");
    }
    else if (type_identify_with_class_name(left_type,
                                           "Null") && null_operand != -1)
    {
        append_opecode_to_code(info->code, null_operand, info->no_output);
        info->stack_num--;
        info->type = create_node_type_with_class_name("null");
    }
    else if (type_identify_with_class_name(left_type,
                                           "char") && char_operand != -1)
    {
        append_opecode_to_code(info->code, char_operand, info->no_output);
        info->stack_num--;
        info->type = create_node_type_with_class_name("char");
    }
    else if (type_identify_with_class_name(left_type,
                                           "bool") && bool_operand != -1)
    {
        append_opecode_to_code(info->code, bool_operand, info->no_output);
        info->stack_num--;
        info->type = create_node_type_with_class_name("bool");
    }
    else if (type_identify_with_class_name(left_type,
                                           "regex") && regex_operand != -1)
    {
        append_opecode_to_code(info->code, regex_operand, info->no_output);
        info->stack_num--;
        info->type = create_node_type_with_class_name("bool");
    }
    else if (type_identify_with_class_name(left_type,
                                           "pointer") && pointer_operand != -1)
    {
        if (strcmp(op_string, "-") == 0)
        {
            if (type_identify_with_class_name(right_type, "pointer"))
            {
                append_opecode_to_code(info->code, 602, info->no_output);
                info->stack_num--;
                info->type = create_node_type_with_class_name("ulong");
            }
            else
            {
                append_opecode_to_code(info->code,
                                       pointer_operand,
                                       info->no_output);
                info->stack_num--;
                info->type = create_node_type_with_class_name("pointer");
            }
        }
        else
        {
            append_opecode_to_code(info->code,
                                   pointer_operand,
                                   info->no_output);
            info->stack_num--;
            info->type = create_node_type_with_class_name("pointer");
        }
    }
    else
    {
        compile_err_msg(info,
                        "%s.%s is not implemented",
                        (char *) ((&left_type->mClass->mConst)->mConst + left_type->mClass->mClassNameOffset),
                        op_string);
        info->err_num++;
    }
    return 1;
}
static int binary_operator_for_bool(sNodeType * type,
                                    int bool_operand,
                                    sCompileInfo * info)
{
    if (type_identify_with_class_name(type, "bool"))
    {
        append_opecode_to_code(info->code, bool_operand, info->no_output);
        info->stack_num--;
        info->type = create_node_type_with_class_name("bool");
    }
    return 1;
}
static int compile_operand(unsigned int node, sCompileInfo * info)
{
    int left_node;
    sNodeType * left_type;
    int right_node;
    sNodeType * right_type;
    sNodeType * node_type;
    left_node = gNodes[node].mLeft;
    if (!compile(left_node, info))
    {
        return 0;
    }
    left_type = info->type;
    if (unboxig_posibility(left_type->mClass))
    {
        if (!unboxing_to_primitive_type(&left_type, info))
        {
            return 0;
        }
    }
    right_node = gNodes[node].mRight;
    if (!compile(right_node, info))
    {
        return 0;
    }
    right_type = info->type;
    node_type = left_type;
    switch (gNodes[node].uValue.mOperand)
    {
    case kOpAdd:
        if (!binary_operator(left_type,
                             right_type,
                             50,
                             80,
                             100,
                             150,
                             200,
                             251,
                             300,
                             400,
                             450,
                             500,
                             600,
                             -1,
                             700,
                             -1,
                             -1,
                             "+",
                             info))
        {
            return 0;
        }
        break;
    case kOpSub:
        {
            if (!binary_operator(left_type,
                                 right_type,
                                 51,
                                 81,
                                 101,
                                 151,
                                 201,
                                 250,
                                 301,
                                 401,
                                 451,
                                 501,
                                 601,
                                 -1,
                                 701,
                                 -1,
                                 -1,
                                 "-",
                                 info))
            {
                return 0;
            }
        }
        break;
    case kOpMult:
        if (!binary_operator(left_type,
                             right_type,
                             52,
                             82,
                             102,
                             152,
                             202,
                             252,
                             302,
                             402,
                             452,
                             502,
                             -1,
                             -1,
                             -1,
                             -1,
                             -1,
                             "*",
                             info))
        {
            return 0;
        }
        break;
    case kOpDiv:
        if (!binary_operator(left_type,
                             right_type,
                             53,
                             83,
                             103,
                             153,
                             203,
                             253,
                             303,
                             403,
                             453,
                             503,
                             -1,
                             -1,
                             -1,
                             -1,
                             -1,
                             "/",
                             info))
        {
            return 0;
        }
        break;
    case kOpMod:
        if (!binary_operator(left_type,
                             right_type,
                             54,
                             84,
                             104,
                             154,
                             204,
                             254,
                             304,
                             404,
                             -1,
                             -1,
                             -1,
                             -1,
                             -1,
                             -1,
                             -1,
                             "%",
                             info))
        {
            return 0;
        }
        break;
    case kOpLeftShift:
        if (!binary_operator(left_type,
                             right_type,
                             55,
                             85,
                             105,
                             155,
                             205,
                             255,
                             305,
                             405,
                             -1,
                             -1,
                             -1,
                             -1,
                             -1,
                             -1,
                             -1,
                             "<<",
                             info))
        {
            return 0;
        }
        break;
    case kOpRightShift:
        if (!binary_operator(left_type,
                             right_type,
                             56,
                             86,
                             106,
                             156,
                             206,
                             256,
                             306,
                             406,
                             -1,
                             -1,
                             -1,
                             -1,
                             -1,
                             -1,
                             -1,
                             ">>",
                             info))
        {
            return 0;
        }
        break;
    case kOpComparisonEqual:
        if (!binary_operator(left_type,
                             right_type,
                             1000,
                             1010,
                             1020,
                             1030,
                             1040,
                             1050,
                             1060,
                             1070,
                             1080,
                             1090,
                             1100,
                             1040,
                             1200,
                             1040,
                             1220,
                             "==",
                             info))
        {
            return 0;
        }
        info->type = create_node_type_with_class_name("bool");
        break;
    case kOpComparisonNotEqual:
        if (!binary_operator(left_type,
                             right_type,
                             1001,
                             1011,
                             1021,
                             1031,
                             1041,
                             1051,
                             1061,
                             1071,
                             1081,
                             1091,
                             1101,
                             1041,
                             1201,
                             1041,
                             1221,
                             "!=",
                             info))
        {
            return 0;
        }
        info->type = create_node_type_with_class_name("bool");
        break;
    case kOpComparisonGreaterEqual:
        if (!binary_operator(left_type,
                             right_type,
                             1004,
                             1014,
                             1024,
                             1034,
                             1044,
                             1054,
                             1064,
                             1074,
                             1084,
                             1094,
                             1104,
                             -1,
                             1204,
                             -1,
                             -1,
                             ">=",
                             info))
        {
            return 0;
        }
        info->type = create_node_type_with_class_name("bool");
        break;
    case kOpComparisonLesserEqual:
        if (!binary_operator(left_type,
                             right_type,
                             1005,
                             1015,
                             1025,
                             1035,
                             1045,
                             1055,
                             1065,
                             1075,
                             1085,
                             1095,
                             1105,
                             -1,
                             1205,
                             -1,
                             -1,
                             "<=",
                             info))
        {
            return 0;
        }
        info->type = create_node_type_with_class_name("bool");
        break;
    case kOpComparisonGreater:
        if (!binary_operator(left_type,
                             right_type,
                             1002,
                             1012,
                             1022,
                             1032,
                             1042,
                             1052,
                             1062,
                             1072,
                             1082,
                             1092,
                             1102,
                             -1,
                             1202,
                             -1,
                             -1,
                             ">",
                             info))
        {
            return 0;
        }
        info->type = create_node_type_with_class_name("bool");
        break;
    case kOpComparisonLesser:
        if (!binary_operator(left_type,
                             right_type,
                             1003,
                             1013,
                             1023,
                             1033,
                             1043,
                             1053,
                             1063,
                             1073,
                             1083,
                             1093,
                             1103,
                             -1,
                             1203,
                             -1,
                             -1,
                             "<",
                             info))
        {
            return 0;
        }
        info->type = create_node_type_with_class_name("bool");
        break;
    case kOpAnd:
        if (!binary_operator(left_type,
                             right_type,
                             57,
                             87,
                             107,
                             157,
                             207,
                             257,
                             307,
                             407,
                             -1,
                             -1,
                             -1,
                             -1,
                             -1,
                             -1,
                             -1,
                             "&",
                             info))
        {
            return 0;
        }
        break;
    case kOpXor:
        if (!binary_operator(left_type,
                             right_type,
                             58,
                             88,
                             108,
                             158,
                             208,
                             258,
                             308,
                             408,
                             -1,
                             -1,
                             -1,
                             -1,
                             -1,
                             -1,
                             -1,
                             "^",
                             info))
        {
            return 0;
        }
        break;
    case kOpOr:
        if (!binary_operator(left_type,
                             right_type,
                             59,
                             89,
                             109,
                             159,
                             209,
                             259,
                             309,
                             409,
                             -1,
                             -1,
                             -1,
                             -1,
                             -1,
                             -1,
                             -1,
                             "|",
                             info))
        {
            return 0;
        }
        break;
    case kOpComplement:
        if (!single_operator(node_type,
                             420,
                             421,
                             422,
                             423,
                             424,
                             425,
                             426,
                             427,
                             info))
        {
            return 0;
        }
        break;
    case kOpLogicalDenial:
        if (!type_identify_with_class_name(node_type, "bool"))
        {
            compile_err_msg(info, "require bool type for operator !");
            info->err_num++;
        }
        else
        {
            append_opecode_to_code(info->code, 2002, info->no_output);
            info->type = create_node_type_with_class_name("bool");
        }
        break;
    }
    return 1;
}
unsigned int sNodeTree_create_and_and(unsigned int left_node,
                                      unsigned int right_node,
                                      sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeAndAnd;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    return node;
}
static int compile_and_and(unsigned int node, sCompileInfo * info)
{
    int label_num;
    unsigned int left_node;
    sNodeType * left_type;
    int stack_num_before;
    int goto_point;
    char label_end_point[512];
    unsigned int right_node;
    sNodeType * right_type;
    label_num = gLabelNum++;
    left_node = gNodes[node].mLeft;
    if (!compile(left_node, info))
    {
        return 0;
    }
    left_type = info->type;
    if (unboxig_posibility(left_type->mClass))
    {
        if (!unboxing_to_primitive_type(&left_type, info))
        {
            return 0;
        }
    }
    if (!type_identify_with_class_name(left_type, "bool"))
    {
        compile_err_msg(info, "Left expression is not bool type");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    append_opecode_to_code(info->code, 4, info->no_output);
    info->stack_num++;
    append_opecode_to_code(info->code, 22, info->no_output);
    append_opecode_to_code(info->code, 5, info->no_output);
    append_int_value_to_code(info->code,
                             sizeof(int) * 4,
                             info->no_output);
    info->stack_num--;
    append_opecode_to_code(info->code, 23, info->no_output);
    stack_num_before = info->stack_num;
    append_opecode_to_code(info->code, 7, info->no_output);
    goto_point = info->code->mLen;
    append_int_value_to_code(info->code, 0, info->no_output);
    create_label_name("label_and_endpoint",
                      label_end_point,
                      512,
                      label_num);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         label_end_point,
                                         info->no_output);
    append_opecode_to_code(info->code, 25, info->no_output);
    right_node = gNodes[node].mRight;
    if (!compile(right_node, info))
    {
        return 0;
    }
    right_type = info->type;
    if (unboxig_posibility(right_type->mClass))
    {
        if (!unboxing_to_primitive_type(&right_type, info))
        {
            return 0;
        }
    }
    if (!type_identify_with_class_name(right_type, "bool"))
    {
        compile_err_msg(info, "Right expression is not bool type");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    append_opecode_to_code(info->code, 26, info->no_output);
    append_int_value_to_code(info->code, -2, info->no_output);
    append_opecode_to_code(info->code, 2000, info->no_output);
    info->stack_num--;
    append_opecode_to_code(info->code, 25, info->no_output);
    info->stack_num = stack_num_before;
    *(int *) (info->code->mCodes + goto_point) = info->code->mLen;
    append_opecode_to_code(info->code, 18, info->no_output);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         label_end_point,
                                         info->no_output);
    append_opecode_to_code(info->code, 27, info->no_output);
    info->type = create_node_type_with_class_name("bool");
    return 1;
}
unsigned int sNodeTree_create_or_or(unsigned int left_node,
                                    unsigned int right_node,
                                    sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeOrOr;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    return node;
}
static int compile_or_or(unsigned int node, sCompileInfo * info)
{
    int label_num;
    unsigned int left_node;
    sNodeType * left_type;
    int stack_num_before;
    int goto_point;
    char label_end_point[512];
    unsigned int right_node;
    sNodeType * right_type;
    label_num = gLabelNum++;
    left_node = gNodes[node].mLeft;
    if (!compile(left_node, info))
    {
        return 0;
    }
    left_type = info->type;
    if (unboxig_posibility(left_type->mClass))
    {
        if (!unboxing_to_primitive_type(&left_type, info))
        {
            return 0;
        }
    }
    if (!type_identify_with_class_name(left_type, "bool"))
    {
        compile_err_msg(info, "Left expression is not bool type");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    append_opecode_to_code(info->code, 4, info->no_output);
    info->stack_num++;
    append_opecode_to_code(info->code, 22, info->no_output);
    append_opecode_to_code(info->code, 6, info->no_output);
    append_int_value_to_code(info->code,
                             sizeof(int) * 4,
                             info->no_output);
    info->stack_num--;
    append_opecode_to_code(info->code, 25, info->no_output);
    stack_num_before = info->stack_num;
    append_opecode_to_code(info->code, 7, info->no_output);
    goto_point = info->code->mLen;
    append_int_value_to_code(info->code, 0, info->no_output);
    create_label_name("label_or_endpoint",
                      label_end_point,
                      512,
                      label_num);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         label_end_point,
                                         info->no_output);
    append_opecode_to_code(info->code, 23, info->no_output);
    right_node = gNodes[node].mRight;
    if (!compile(right_node, info))
    {
        return 0;
    }
    right_type = info->type;
    if (unboxig_posibility(right_type->mClass))
    {
        if (!unboxing_to_primitive_type(&right_type, info))
        {
            return 0;
        }
    }
    if (!type_identify_with_class_name(right_type, "bool"))
    {
        compile_err_msg(info, "Right expression is not bool type");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    append_opecode_to_code(info->code, 24, info->no_output);
    append_int_value_to_code(info->code, -2, info->no_output);
    append_opecode_to_code(info->code, 2001, info->no_output);
    info->stack_num--;
    append_opecode_to_code(info->code, 23, info->no_output);
    info->stack_num = stack_num_before;
    *(int *) (info->code->mCodes + goto_point) = info->code->mLen;
    append_opecode_to_code(info->code, 18, info->no_output);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         label_end_point,
                                         info->no_output);
    append_opecode_to_code(info->code, 27, info->no_output);
    info->type = create_node_type_with_class_name("bool");
    return 1;
}
unsigned int sNodeTree_create_byte_value(char value,
                                         unsigned int left,
                                         unsigned int right,
                                         unsigned int middle,
                                         sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeByteValue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].uValue.mByteValue = value;
    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;
    gNodes[node].mType = create_node_type_with_class_name("byte");
    return node;
}
static int compile_byte_value(unsigned int node,
                              sCompileInfo * info)
{
    append_opecode_to_code(info->code, 35, info->no_output);
    append_int_value_to_code(info->code,
                             gNodes[node].uValue.mByteValue,
                             info->no_output);
    info->stack_num++;
    info->type = gNodes[node].mType;
    return 1;
}
unsigned int sNodeTree_create_cbyte_value(char value,
                                          unsigned int left,
                                          unsigned int right,
                                          unsigned int middle,
                                          sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeCByteValue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].uValue.mByteValue = value;
    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;
    gNodes[node].mType = create_node_type_with_class_name("byte");
    return node;
}
static int compile_cbyte_value(unsigned int node,
                               sCompileInfo * info)
{
    char bvalue;
    sNodeType * generics_types2;
    sCLClass * klass;
    int num_params;
    sNodeType * param_types[32];
    char * method_name;
    bvalue = gNodes[node].uValue.mByteValue;
    generics_types2 = (void *) 0;
    klass = get_class("Byte");
    append_opecode_to_code(info->code, 4000, info->no_output);
    append_class_name_to_constant_pool_and_code(info, klass);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         "Byte",
                                         info->no_output);
    append_int_value_to_code(info->code, 0, info->no_output);
    info->stack_num++;
    num_params = 1;
    method_name = "initialize";
    append_opecode_to_code(info->code, 35, info->no_output);
    append_int_value_to_code(info->code,
                             gNodes[node].uValue.mByteValue,
                             info->no_output);
    info->stack_num++;
    param_types[0] = create_node_type_with_class_name("byte");
    if (!info->pinfo->exist_block_object_err)
    {
        sNodeType * right_method_generics_types;
        sNodeType * result_type;
        sNodeType * result_method_generics_types;
        int method_index;
        sNodeType * result_type2;
        int size;
        right_method_generics_types = (void *) 0;
        result_method_generics_types = (void *) 0;
        method_index = search_for_method(klass,
                                         method_name,
                                         param_types,
                                         num_params,
                                         0,
                                         klass->mNumMethods - 1,
                                         generics_types2,
                                         generics_types2,
                                         right_method_generics_types,
                                         &result_type,
                                         0,
                                         0,
                                         &result_method_generics_types);
        if (method_index == -1)
        {
            compile_err_msg(info, "method not found(11)");
            info->err_num++;
            err_msg_for_method_not_found(klass,
                                         method_name,
                                         param_types,
                                         num_params,
                                         0,
                                         info);
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        append_opecode_to_code(info->code, 16, info->no_output);
        append_str_to_constant_pool_and_code(info->constant,
                                             info->code,
                                             info->sname,
                                             info->no_output);
        append_int_value_to_code(info->code, info->sline, info->no_output);
        append_opecode_to_code(info->code, 3000, info->no_output);
        append_class_name_to_constant_pool_and_code(info, klass);
        append_int_value_to_code(info->code,
                                 method_index,
                                 info->no_output);
        result_type2 = create_node_type_with_class_name("Byte");
        size = get_var_size(result_type2);
        append_int_value_to_code(info->code, size, info->no_output);
        info->stack_num -= num_params + 1;
        info->stack_num++;
        info->type = result_type2;
    }
    return 1;
}
unsigned int sNodeTree_create_float_value(float value,
                                          unsigned int left,
                                          unsigned int right,
                                          unsigned int middle,
                                          sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeFloatValue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].uValue.mFloatValue = value;
    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;
    return node;
}
static int compile_float_value(unsigned int node,
                               sCompileInfo * info)
{
    append_opecode_to_code(info->code, 45, info->no_output);
    append_float_value_to_code(info->code,
                               gNodes[node].uValue.mFloatValue,
                               info->no_output);
    info->stack_num++;
    info->type = create_node_type_with_class_name("float");
    return 1;
}
unsigned int sNodeTree_create_cfloat_value(float value,
                                           unsigned int left,
                                           unsigned int right,
                                           unsigned int middle,
                                           sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeCFloatValue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].uValue.mFloatValue = value;
    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;
    return node;
}
static int compile_cfloat_value(unsigned int node,
                                sCompileInfo * info)
{
    float fvalue;
    sNodeType * generics_types2;
    sCLClass * klass;
    int num_params;
    sNodeType * param_types[32];
    char * method_name;
    fvalue = gNodes[node].uValue.mFloatValue;
    generics_types2 = (void *) 0;
    klass = get_class("Float");
    append_opecode_to_code(info->code, 4000, info->no_output);
    append_class_name_to_constant_pool_and_code(info, klass);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         "Float",
                                         info->no_output);
    append_int_value_to_code(info->code, 0, info->no_output);
    info->stack_num++;
    num_params = 1;
    method_name = "initialize";
    append_opecode_to_code(info->code, 45, info->no_output);
    append_float_value_to_code(info->code, fvalue, info->no_output);
    info->stack_num++;
    param_types[0] = create_node_type_with_class_name("float");
    if (!info->pinfo->exist_block_object_err)
    {
        sNodeType * right_method_generics_types;
        sNodeType * result_type;
        sNodeType * result_method_generics_types;
        int method_index;
        sNodeType * result_type2;
        int size;
        right_method_generics_types = (void *) 0;
        result_method_generics_types = (void *) 0;
        method_index = search_for_method(klass,
                                         method_name,
                                         param_types,
                                         num_params,
                                         0,
                                         klass->mNumMethods - 1,
                                         generics_types2,
                                         generics_types2,
                                         right_method_generics_types,
                                         &result_type,
                                         0,
                                         0,
                                         &result_method_generics_types);
        if (method_index == -1)
        {
            compile_err_msg(info, "method not found(12)");
            info->err_num++;
            err_msg_for_method_not_found(klass,
                                         method_name,
                                         param_types,
                                         num_params,
                                         0,
                                         info);
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        append_opecode_to_code(info->code, 16, info->no_output);
        append_str_to_constant_pool_and_code(info->constant,
                                             info->code,
                                             info->sname,
                                             info->no_output);
        append_int_value_to_code(info->code, info->sline, info->no_output);
        append_opecode_to_code(info->code, 3000, info->no_output);
        append_class_name_to_constant_pool_and_code(info, klass);
        append_int_value_to_code(info->code,
                                 method_index,
                                 info->no_output);
        result_type2 = create_node_type_with_class_name("Float");
        size = get_var_size(result_type2);
        append_int_value_to_code(info->code, size, info->no_output);
        info->stack_num -= num_params + 1;
        info->stack_num++;
        info->type = result_type2;
    }
    return 1;
}
unsigned int sNodeTree_create_double_value(double value,
                                           unsigned int left,
                                           unsigned int right,
                                           unsigned int middle,
                                           sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeDoubleValue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].uValue.mDoubleValue = value;
    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;
    return node;
}
static int compile_double_value(unsigned int node,
                                sCompileInfo * info)
{
    append_opecode_to_code(info->code, 46, info->no_output);
    append_double_value_to_code(info->code,
                                gNodes[node].uValue.mDoubleValue,
                                info->no_output);
    info->stack_num++;
    info->type = create_node_type_with_class_name("double");
    return 1;
}
unsigned int sNodeTree_create_cdouble_value(double value,
                                            unsigned int left,
                                            unsigned int right,
                                            unsigned int middle,
                                            sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeCDoubleValue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].uValue.mDoubleValue = value;
    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;
    return node;
}
static int compile_cdouble_value(unsigned int node,
                                 sCompileInfo * info)
{
    double dvalue;
    sNodeType * generics_types2;
    sCLClass * klass;
    int num_params;
    sNodeType * param_types[32];
    char * method_name;
    dvalue = gNodes[node].uValue.mDoubleValue;
    generics_types2 = (void *) 0;
    klass = get_class("Double");
    append_opecode_to_code(info->code, 4000, info->no_output);
    append_class_name_to_constant_pool_and_code(info, klass);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         "Double",
                                         info->no_output);
    append_int_value_to_code(info->code, 0, info->no_output);
    info->stack_num++;
    num_params = 1;
    method_name = "initialize";
    append_opecode_to_code(info->code, 46, info->no_output);
    append_double_value_to_code(info->code, dvalue, info->no_output);
    info->stack_num++;
    param_types[0] = create_node_type_with_class_name("double");
    if (!info->pinfo->exist_block_object_err)
    {
        sNodeType * right_method_generics_types;
        sNodeType * result_type;
        sNodeType * result_method_generics_types;
        int method_index;
        sNodeType * result_type2;
        int size;
        right_method_generics_types = (void *) 0;
        result_method_generics_types = (void *) 0;
        method_index = search_for_method(klass,
                                         method_name,
                                         param_types,
                                         num_params,
                                         0,
                                         klass->mNumMethods - 1,
                                         generics_types2,
                                         generics_types2,
                                         right_method_generics_types,
                                         &result_type,
                                         0,
                                         0,
                                         &result_method_generics_types);
        if (method_index == -1)
        {
            compile_err_msg(info, "method not found(13)");
            info->err_num++;
            err_msg_for_method_not_found(klass,
                                         method_name,
                                         param_types,
                                         num_params,
                                         0,
                                         info);
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        append_opecode_to_code(info->code, 16, info->no_output);
        append_str_to_constant_pool_and_code(info->constant,
                                             info->code,
                                             info->sname,
                                             info->no_output);
        append_int_value_to_code(info->code, info->sline, info->no_output);
        append_opecode_to_code(info->code, 3000, info->no_output);
        append_class_name_to_constant_pool_and_code(info, klass);
        append_int_value_to_code(info->code,
                                 method_index,
                                 info->no_output);
        result_type2 = create_node_type_with_class_name("Double");
        size = get_var_size(result_type2);
        append_int_value_to_code(info->code, size, info->no_output);
        info->stack_num -= num_params + 1;
        info->stack_num++;
        info->type = result_type2;
    }
    return 1;
}
unsigned int sNodeTree_create_ubyte_value(unsigned char value,
                                          unsigned int left,
                                          unsigned int right,
                                          unsigned int middle,
                                          sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeUByteValue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].uValue.mUByteValue = value;
    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;
    gNodes[node].mType = create_node_type_with_class_name("ubyte");
    return node;
}
static int compile_ubyte_value(unsigned int node,
                               sCompileInfo * info)
{
    append_opecode_to_code(info->code, 36, info->no_output);
    append_int_value_to_code(info->code,
                             gNodes[node].uValue.mUByteValue,
                             info->no_output);
    info->stack_num++;
    info->type = gNodes[node].mType;
    return 1;
}
unsigned int sNodeTree_create_cubyte_value(unsigned char value,
                                           unsigned int left,
                                           unsigned int right,
                                           unsigned int middle,
                                           sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeCUByteValue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].uValue.mUByteValue = value;
    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;
    gNodes[node].mType = create_node_type_with_class_name("ubyte");
    return node;
}
static int compile_cubyte_value(unsigned int node,
                                sCompileInfo * info)
{
    unsigned char ubvalue;
    sNodeType * generics_types2;
    sCLClass * klass;
    int num_params;
    sNodeType * param_types[32];
    char * method_name;
    ubvalue = gNodes[node].uValue.mUByteValue;
    generics_types2 = (void *) 0;
    klass = get_class("UByte");
    append_opecode_to_code(info->code, 4000, info->no_output);
    append_class_name_to_constant_pool_and_code(info, klass);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         "UByte",
                                         info->no_output);
    append_int_value_to_code(info->code, 0, info->no_output);
    info->stack_num++;
    num_params = 1;
    method_name = "initialize";
    append_opecode_to_code(info->code, 36, info->no_output);
    append_double_value_to_code(info->code, ubvalue, info->no_output);
    info->stack_num++;
    param_types[0] = create_node_type_with_class_name("ubyte");
    if (!info->pinfo->exist_block_object_err)
    {
        sNodeType * right_method_generics_types;
        sNodeType * result_type;
        sNodeType * result_method_generics_types;
        int method_index;
        sNodeType * result_type2;
        int size;
        right_method_generics_types = (void *) 0;
        result_method_generics_types = (void *) 0;
        method_index = search_for_method(klass,
                                         method_name,
                                         param_types,
                                         num_params,
                                         0,
                                         klass->mNumMethods - 1,
                                         generics_types2,
                                         generics_types2,
                                         right_method_generics_types,
                                         &result_type,
                                         0,
                                         0,
                                         &result_method_generics_types);
        if (method_index == -1)
        {
            compile_err_msg(info, "method not found(14)");
            info->err_num++;
            err_msg_for_method_not_found(klass,
                                         method_name,
                                         param_types,
                                         num_params,
                                         0,
                                         info);
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        append_opecode_to_code(info->code, 16, info->no_output);
        append_str_to_constant_pool_and_code(info->constant,
                                             info->code,
                                             info->sname,
                                             info->no_output);
        append_int_value_to_code(info->code, info->sline, info->no_output);
        append_opecode_to_code(info->code, 3000, info->no_output);
        append_class_name_to_constant_pool_and_code(info, klass);
        append_int_value_to_code(info->code,
                                 method_index,
                                 info->no_output);
        result_type2 = create_node_type_with_class_name("UByte");
        size = get_var_size(result_type2);
        append_int_value_to_code(info->code, size, info->no_output);
        info->stack_num -= num_params + 1;
        info->stack_num++;
        info->type = result_type2;
    }
    return 1;
}
unsigned int sNodeTree_create_short_value(short value,
                                          unsigned int left,
                                          unsigned int right,
                                          unsigned int middle,
                                          sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeShortValue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].uValue.mShortValue = value;
    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;
    gNodes[node].mType = create_node_type_with_class_name("short");
    return node;
}
static int compile_short_value(unsigned int node,
                               sCompileInfo * info)
{
    append_opecode_to_code(info->code, 37, info->no_output);
    append_int_value_to_code(info->code,
                             gNodes[node].uValue.mShortValue,
                             info->no_output);
    info->stack_num++;
    info->type = gNodes[node].mType;
    return 1;
}
unsigned int sNodeTree_create_cshort_value(short value,
                                           unsigned int left,
                                           unsigned int right,
                                           unsigned int middle,
                                           sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeCShortValue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].uValue.mShortValue = value;
    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;
    gNodes[node].mType = create_node_type_with_class_name("short");
    return node;
}
static int compile_cshort_value(unsigned int node,
                                sCompileInfo * info)
{
    short svalue;
    sNodeType * generics_types2;
    sCLClass * klass;
    int num_params;
    sNodeType * param_types[32];
    char * method_name;
    svalue = gNodes[node].uValue.mShortValue;
    generics_types2 = (void *) 0;
    klass = get_class("Short");
    append_opecode_to_code(info->code, 4000, info->no_output);
    append_class_name_to_constant_pool_and_code(info, klass);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         "UByte",
                                         info->no_output);
    append_int_value_to_code(info->code, 0, info->no_output);
    info->stack_num++;
    num_params = 1;
    method_name = "initialize";
    append_opecode_to_code(info->code, 37, info->no_output);
    append_int_value_to_code(info->code, svalue, info->no_output);
    info->stack_num++;
    param_types[0] = create_node_type_with_class_name("short");
    if (!info->pinfo->exist_block_object_err)
    {
        sNodeType * right_method_generics_types;
        sNodeType * result_type;
        sNodeType * result_method_generics_types;
        int method_index;
        sNodeType * result_type2;
        int size;
        right_method_generics_types = (void *) 0;
        result_method_generics_types = (void *) 0;
        method_index = search_for_method(klass,
                                         method_name,
                                         param_types,
                                         num_params,
                                         0,
                                         klass->mNumMethods - 1,
                                         generics_types2,
                                         generics_types2,
                                         right_method_generics_types,
                                         &result_type,
                                         0,
                                         0,
                                         &result_method_generics_types);
        if (method_index == -1)
        {
            compile_err_msg(info, "method not found(15)");
            info->err_num++;
            err_msg_for_method_not_found(klass,
                                         method_name,
                                         param_types,
                                         num_params,
                                         0,
                                         info);
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        append_opecode_to_code(info->code, 16, info->no_output);
        append_str_to_constant_pool_and_code(info->constant,
                                             info->code,
                                             info->sname,
                                             info->no_output);
        append_int_value_to_code(info->code, info->sline, info->no_output);
        append_opecode_to_code(info->code, 3000, info->no_output);
        append_class_name_to_constant_pool_and_code(info, klass);
        append_int_value_to_code(info->code,
                                 method_index,
                                 info->no_output);
        result_type2 = create_node_type_with_class_name("Short");
        size = get_var_size(result_type2);
        append_int_value_to_code(info->code, size, info->no_output);
        info->stack_num -= num_params + 1;
        info->stack_num++;
        info->type = result_type2;
    }
    return 1;
}
unsigned int sNodeTree_create_ushort_value(unsigned short value,
                                           unsigned int left,
                                           unsigned int right,
                                           unsigned int middle,
                                           sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeUShortValue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].uValue.mUShortValue = value;
    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;
    gNodes[node].mType = create_node_type_with_class_name("ushort");
    return node;
}
static int compile_ushort_value(unsigned int node,
                                sCompileInfo * info)
{
    append_opecode_to_code(info->code, 38, info->no_output);
    append_int_value_to_code(info->code,
                             gNodes[node].uValue.mUShortValue,
                             info->no_output);
    info->stack_num++;
    info->type = gNodes[node].mType;
    return 1;
}
unsigned int sNodeTree_create_cushort_value(unsigned short value,
                                            unsigned int left,
                                            unsigned int right,
                                            unsigned int middle,
                                            sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeCUShortValue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].uValue.mUShortValue = value;
    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;
    gNodes[node].mType = create_node_type_with_class_name("ushort");
    return node;
}
static int compile_cushort_value(unsigned int node,
                                 sCompileInfo * info)
{
    unsigned short usvalue;
    sNodeType * generics_types2;
    sCLClass * klass;
    int num_params;
    sNodeType * param_types[32];
    char * method_name;
    usvalue = gNodes[node].uValue.mUShortValue;
    generics_types2 = (void *) 0;
    klass = get_class("UShort");
    append_opecode_to_code(info->code, 4000, info->no_output);
    append_class_name_to_constant_pool_and_code(info, klass);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         "UShort",
                                         info->no_output);
    append_int_value_to_code(info->code, 0, info->no_output);
    info->stack_num++;
    num_params = 1;
    method_name = "initialize";
    append_opecode_to_code(info->code, 38, info->no_output);
    append_int_value_to_code(info->code, usvalue, info->no_output);
    info->stack_num++;
    param_types[0] = create_node_type_with_class_name("ushort");
    if (!info->pinfo->exist_block_object_err)
    {
        sNodeType * right_method_generics_types;
        sNodeType * result_type;
        sNodeType * result_method_generics_types;
        int method_index;
        sNodeType * result_type2;
        int size;
        right_method_generics_types = (void *) 0;
        result_method_generics_types = (void *) 0;
        method_index = search_for_method(klass,
                                         method_name,
                                         param_types,
                                         num_params,
                                         0,
                                         klass->mNumMethods - 1,
                                         generics_types2,
                                         generics_types2,
                                         right_method_generics_types,
                                         &result_type,
                                         0,
                                         0,
                                         &result_method_generics_types);
        if (method_index == -1)
        {
            compile_err_msg(info, "method not found(16)");
            info->err_num++;
            err_msg_for_method_not_found(klass,
                                         method_name,
                                         param_types,
                                         num_params,
                                         0,
                                         info);
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        append_opecode_to_code(info->code, 16, info->no_output);
        append_str_to_constant_pool_and_code(info->constant,
                                             info->code,
                                             info->sname,
                                             info->no_output);
        append_int_value_to_code(info->code, info->sline, info->no_output);
        append_opecode_to_code(info->code, 3000, info->no_output);
        append_class_name_to_constant_pool_and_code(info, klass);
        append_int_value_to_code(info->code,
                                 method_index,
                                 info->no_output);
        result_type2 = create_node_type_with_class_name("UShort");
        size = get_var_size(result_type2);
        append_int_value_to_code(info->code, size, info->no_output);
        info->stack_num -= num_params + 1;
        info->stack_num++;
        info->type = result_type2;
    }
    return 1;
}
unsigned int sNodeTree_create_int_value(int value,
                                        unsigned int left,
                                        unsigned int right,
                                        unsigned int middle,
                                        sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeIntValue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].uValue.mIntValue = value;
    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;
    gNodes[node].mType = create_node_type_with_class_name("int");
    return node;
}
static int compile_int_value(unsigned int node,
                             sCompileInfo * info)
{
    append_opecode_to_code(info->code, 39, info->no_output);
    append_int_value_to_code(info->code,
                             gNodes[node].uValue.mIntValue,
                             info->no_output);
    info->stack_num++;
    info->type = create_node_type_with_class_name("int");
    return 1;
}
unsigned int sNodeTree_create_cint_value(int value,
                                         unsigned int left,
                                         unsigned int right,
                                         unsigned int middle,
                                         sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeCIntValue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].uValue.mIntValue = value;
    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;
    gNodes[node].mType = create_node_type_with_class_name("int");
    return node;
}
static int compile_cint_value(unsigned int node,
                              sCompileInfo * info)
{
    int ivalue;
    sNodeType * generics_types2;
    sCLClass * klass;
    int num_params;
    sNodeType * param_types[32];
    char * method_name;
    ivalue = gNodes[node].uValue.mIntValue;
    generics_types2 = (void *) 0;
    klass = get_class("Integer");
    append_opecode_to_code(info->code, 4000, info->no_output);
    append_class_name_to_constant_pool_and_code(info, klass);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         "Integer",
                                         info->no_output);
    append_int_value_to_code(info->code, 0, info->no_output);
    info->stack_num++;
    num_params = 1;
    method_name = "initialize";
    append_opecode_to_code(info->code, 39, info->no_output);
    append_int_value_to_code(info->code, ivalue, info->no_output);
    info->stack_num++;
    param_types[0] = create_node_type_with_class_name("int");
    if (!info->pinfo->exist_block_object_err)
    {
        sNodeType * right_method_generics_types;
        sNodeType * result_type;
        sNodeType * result_method_generics_types;
        int method_index;
        sNodeType * result_type2;
        int size;
        right_method_generics_types = (void *) 0;
        result_method_generics_types = (void *) 0;
        method_index = search_for_method(klass,
                                         method_name,
                                         param_types,
                                         num_params,
                                         0,
                                         klass->mNumMethods - 1,
                                         generics_types2,
                                         generics_types2,
                                         right_method_generics_types,
                                         &result_type,
                                         0,
                                         0,
                                         &result_method_generics_types);
        if (method_index == -1)
        {
            compile_err_msg(info, "method not found(17)");
            info->err_num++;
            err_msg_for_method_not_found(klass,
                                         method_name,
                                         param_types,
                                         num_params,
                                         0,
                                         info);
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        append_opecode_to_code(info->code, 16, info->no_output);
        append_str_to_constant_pool_and_code(info->constant,
                                             info->code,
                                             info->sname,
                                             info->no_output);
        append_int_value_to_code(info->code, info->sline, info->no_output);
        append_opecode_to_code(info->code, 3000, info->no_output);
        append_class_name_to_constant_pool_and_code(info, klass);
        append_int_value_to_code(info->code,
                                 method_index,
                                 info->no_output);
        result_type2 = create_node_type_with_class_name("Integer");
        size = get_var_size(result_type2);
        append_int_value_to_code(info->code, size, info->no_output);
        info->stack_num -= num_params + 1;
        info->stack_num++;
        info->type = result_type2;
    }
    return 1;
}
unsigned int sNodeTree_create_uint_value(unsigned int value,
                                         unsigned int left,
                                         unsigned int right,
                                         unsigned int middle,
                                         sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeUIntValue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].uValue.mUIntValue = value;
    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;
    gNodes[node].mType = create_node_type_with_class_name("uint");
    return node;
}
static int compile_uint_value(unsigned int node,
                              sCompileInfo * info)
{
    append_opecode_to_code(info->code, 40, info->no_output);
    append_int_value_to_code(info->code,
                             gNodes[node].uValue.mUIntValue,
                             info->no_output);
    info->stack_num++;
    info->type = gNodes[node].mType;
    return 1;
}
unsigned int sNodeTree_create_cuint_value(unsigned int value,
                                          unsigned int left,
                                          unsigned int right,
                                          unsigned int middle,
                                          sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeCUIntValue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].uValue.mUIntValue = value;
    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;
    gNodes[node].mType = create_node_type_with_class_name("uint");
    return node;
}
static int compile_cuint_value(unsigned int node,
                               sCompileInfo * info)
{
    unsigned int uivalue;
    sNodeType * generics_types2;
    sCLClass * klass;
    int num_params;
    sNodeType * param_types[32];
    char * method_name;
    uivalue = gNodes[node].uValue.mUIntValue;
    generics_types2 = (void *) 0;
    klass = get_class("UInteger");
    append_opecode_to_code(info->code, 4000, info->no_output);
    append_class_name_to_constant_pool_and_code(info, klass);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         "UInteger",
                                         info->no_output);
    append_int_value_to_code(info->code, 0, info->no_output);
    info->stack_num++;
    num_params = 1;
    method_name = "initialize";
    append_opecode_to_code(info->code, 40, info->no_output);
    append_int_value_to_code(info->code, uivalue, info->no_output);
    info->stack_num++;
    param_types[0] = create_node_type_with_class_name("uint");
    if (!info->pinfo->exist_block_object_err)
    {
        sNodeType * right_method_generics_types;
        sNodeType * result_type;
        sNodeType * result_method_generics_types;
        int method_index;
        sNodeType * result_type2;
        int size;
        right_method_generics_types = (void *) 0;
        result_method_generics_types = (void *) 0;
        method_index = search_for_method(klass,
                                         method_name,
                                         param_types,
                                         num_params,
                                         0,
                                         klass->mNumMethods - 1,
                                         generics_types2,
                                         generics_types2,
                                         right_method_generics_types,
                                         &result_type,
                                         0,
                                         0,
                                         &result_method_generics_types);
        if (method_index == -1)
        {
            compile_err_msg(info, "method not found(18)");
            info->err_num++;
            err_msg_for_method_not_found(klass,
                                         method_name,
                                         param_types,
                                         num_params,
                                         0,
                                         info);
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        append_opecode_to_code(info->code, 16, info->no_output);
        append_str_to_constant_pool_and_code(info->constant,
                                             info->code,
                                             info->sname,
                                             info->no_output);
        append_int_value_to_code(info->code, info->sline, info->no_output);
        append_opecode_to_code(info->code, 3000, info->no_output);
        append_class_name_to_constant_pool_and_code(info, klass);
        append_int_value_to_code(info->code,
                                 method_index,
                                 info->no_output);
        result_type2 = create_node_type_with_class_name("UInteger");
        size = get_var_size(result_type2);
        append_int_value_to_code(info->code, size, info->no_output);
        info->stack_num -= num_params + 1;
        info->stack_num++;
        info->type = result_type2;
    }
    return 1;
}
unsigned int sNodeTree_create_long_value(long long value,
                                         unsigned int left,
                                         unsigned int right,
                                         unsigned int middle,
                                         sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeLongValue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].uValue.mLongValue = value;
    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;
    gNodes[node].mType = create_node_type_with_class_name("long");
    return node;
}
static int compile_long_value(unsigned int node,
                              sCompileInfo * info)
{
    append_opecode_to_code(info->code, 41, info->no_output);
    append_long_value_to_code(info->code,
                              gNodes[node].uValue.mLongValue,
                              info->no_output);
    info->stack_num++;
    info->type = gNodes[node].mType;
    return 1;
}
unsigned int sNodeTree_create_clong_value(long long value,
                                          unsigned int left,
                                          unsigned int right,
                                          unsigned int middle,
                                          sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeCLongValue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].uValue.mLongValue = value;
    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;
    gNodes[node].mType = create_node_type_with_class_name("long");
    return node;
}
static int compile_clong_value(unsigned int node,
                               sCompileInfo * info)
{
    long lvalue;
    sNodeType * generics_types2;
    sCLClass * klass;
    int num_params;
    sNodeType * param_types[32];
    char * method_name;
    lvalue = gNodes[node].uValue.mLongValue;
    generics_types2 = (void *) 0;
    klass = get_class("Long");
    append_opecode_to_code(info->code, 4000, info->no_output);
    append_class_name_to_constant_pool_and_code(info, klass);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         "Long",
                                         info->no_output);
    append_int_value_to_code(info->code, 0, info->no_output);
    info->stack_num++;
    num_params = 1;
    method_name = "initialize";
    append_opecode_to_code(info->code, 41, info->no_output);
    append_long_value_to_code(info->code, lvalue, info->no_output);
    info->stack_num++;
    param_types[0] = create_node_type_with_class_name("long");
    if (!info->pinfo->exist_block_object_err)
    {
        sNodeType * right_method_generics_types;
        sNodeType * result_type;
        sNodeType * result_method_generics_types;
        int method_index;
        sNodeType * result_type2;
        int size;
        right_method_generics_types = (void *) 0;
        result_method_generics_types = (void *) 0;
        method_index = search_for_method(klass,
                                         method_name,
                                         param_types,
                                         num_params,
                                         0,
                                         klass->mNumMethods - 1,
                                         generics_types2,
                                         generics_types2,
                                         right_method_generics_types,
                                         &result_type,
                                         0,
                                         0,
                                         &result_method_generics_types);
        if (method_index == -1)
        {
            compile_err_msg(info, "method not found(19)");
            info->err_num++;
            err_msg_for_method_not_found(klass,
                                         method_name,
                                         param_types,
                                         num_params,
                                         0,
                                         info);
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        append_opecode_to_code(info->code, 16, info->no_output);
        append_str_to_constant_pool_and_code(info->constant,
                                             info->code,
                                             info->sname,
                                             info->no_output);
        append_int_value_to_code(info->code, info->sline, info->no_output);
        append_opecode_to_code(info->code, 3000, info->no_output);
        append_class_name_to_constant_pool_and_code(info, klass);
        append_int_value_to_code(info->code,
                                 method_index,
                                 info->no_output);
        result_type2 = create_node_type_with_class_name("Long");
        size = get_var_size(result_type2);
        append_int_value_to_code(info->code, size, info->no_output);
        info->stack_num -= num_params + 1;
        info->stack_num++;
        info->type = result_type2;
    }
    return 1;
}
unsigned int sNodeTree_create_ulong_value(unsigned long long value,
                                          unsigned int left,
                                          unsigned int right,
                                          unsigned int middle,
                                          sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeULongValue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].uValue.mULongValue = value;
    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;
    gNodes[node].mType = create_node_type_with_class_name("ulong");
    return node;
}
static int compile_ulong_value(unsigned int node,
                               sCompileInfo * info)
{
    append_opecode_to_code(info->code, 42, info->no_output);
    append_long_value_to_code(info->code,
                              gNodes[node].uValue.mULongValue,
                              info->no_output);
    info->stack_num++;
    info->type = gNodes[node].mType;
    return 1;
}
unsigned int sNodeTree_create_culong_value(unsigned long long value,
                                           unsigned int left,
                                           unsigned int right,
                                           unsigned int middle,
                                           sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeCULongValue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].uValue.mULongValue = value;
    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;
    gNodes[node].mType = create_node_type_with_class_name("ulong");
    return node;
}
static int compile_culong_value(unsigned int node,
                                sCompileInfo * info)
{
    unsigned long ulvalue;
    sNodeType * generics_types2;
    sCLClass * klass;
    int num_params;
    sNodeType * param_types[32];
    char * method_name;
    ulvalue = gNodes[node].uValue.mULongValue;
    generics_types2 = (void *) 0;
    klass = get_class("ULong");
    append_opecode_to_code(info->code, 4000, info->no_output);
    append_class_name_to_constant_pool_and_code(info, klass);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         "ULong",
                                         info->no_output);
    append_int_value_to_code(info->code, 0, info->no_output);
    info->stack_num++;
    num_params = 1;
    method_name = "initialize";
    append_opecode_to_code(info->code, 42, info->no_output);
    append_long_value_to_code(info->code, ulvalue, info->no_output);
    info->stack_num++;
    param_types[0] = create_node_type_with_class_name("ulong");
    if (!info->pinfo->exist_block_object_err)
    {
        sNodeType * right_method_generics_types;
        sNodeType * result_type;
        sNodeType * result_method_generics_types;
        int method_index;
        sNodeType * result_type2;
        int size;
        right_method_generics_types = (void *) 0;
        result_method_generics_types = (void *) 0;
        method_index = search_for_method(klass,
                                         method_name,
                                         param_types,
                                         num_params,
                                         0,
                                         klass->mNumMethods - 1,
                                         generics_types2,
                                         generics_types2,
                                         right_method_generics_types,
                                         &result_type,
                                         0,
                                         0,
                                         &result_method_generics_types);
        if (method_index == -1)
        {
            compile_err_msg(info, "method not found(20)");
            info->err_num++;
            err_msg_for_method_not_found(klass,
                                         method_name,
                                         param_types,
                                         num_params,
                                         0,
                                         info);
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        append_opecode_to_code(info->code, 16, info->no_output);
        append_str_to_constant_pool_and_code(info->constant,
                                             info->code,
                                             info->sname,
                                             info->no_output);
        append_int_value_to_code(info->code, info->sline, info->no_output);
        append_opecode_to_code(info->code, 3000, info->no_output);
        append_class_name_to_constant_pool_and_code(info, klass);
        append_int_value_to_code(info->code,
                                 method_index,
                                 info->no_output);
        result_type2 = create_node_type_with_class_name("ULong");
        size = get_var_size(result_type2);
        append_int_value_to_code(info->code, size, info->no_output);
        info->stack_num -= num_params + 1;
        info->stack_num++;
        info->type = result_type2;
    }
    return 1;
}
unsigned int sNodeTree_create_store_variable(char * var_name,
                                             sNodeType * node_type,
                                             int right,
                                             sCLClass * klass,
                                             sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeAssignVariable;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    xstrncpy(gNodes[node].uValue.sAssignVariable.mVarName,
             var_name,
             64);
    gNodes[node].uValue.sAssignVariable.mClass = klass;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = node_type;
    return node;
}
static int compile_store_variable(unsigned int node,
                                  sCompileInfo * info)
{
    sVar * var;
    unsigned int right_node;
    sNodeType * right_type;
    sNodeType * left_type;
    sNodeType * left_type2;
    int var_index;
    var = get_variable_from_table(info->lv_table,
                                  gNodes[node].uValue.sAssignVariable.mVarName);
    if (var == (void *) 0)
    {
        compile_err_msg(info,
                        "undeclared variable %s",
                        gNodes[node].uValue.sAssignVariable.mVarName);
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    right_node = gNodes[node].mRight;
    if (!compile(right_node, info))
    {
        return 0;
    }
    right_type = info->type;
    if (gNodes[node].mType == (void *) 0)
    {
        gNodes[node].mType = right_type;
    }
    if (var->mType == (void *) 0)
    {
        var->mType = right_type;
    }
    left_type = var->mType;
    if (gNodes[node].mType->mClass == (void *) 0 || left_type == (void *) 0 || right_type == (void *) 0 || left_type->mClass == (void *) 0 || right_type->mClass == (void *) 0)
    {
        compile_err_msg(info, "invalid type(1)");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    solve_generics_for_variable(left_type, &left_type2, info->pinfo);
    cast_right_type_to_left_type(left_type2, &right_type, info);
    if (!substitution_posibility(left_type2,
                                 right_type,
                                 (void *) 0,
                                 (void *) 0,
                                 (void *) 0,
                                 (void *) 0))
    {
        compile_err_msg(info,
                        "The different type between left type and right type(1). Left type is %s. Right type is %s.",
                        (char *) ((&left_type2->mClass->mConst)->mConst + left_type2->mClass->mClassNameOffset),
                        (char *) ((&right_type->mClass->mConst)->mConst + right_type->mClass->mClassNameOffset));
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    var_index = get_variable_index(info->lv_table,
                                   gNodes[node].uValue.sAssignVariable.mVarName);
    ;
    append_opecode_to_code(info->code, 31, info->no_output);
    append_int_value_to_code(info->code, var_index, info->no_output);
    info->type = left_type2;
    return 1;
}
unsigned int sNodeTree_create_load_variable(char * var_name,
                                            sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeLoadVariable;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    xstrncpy(gNodes[node].uValue.mVarName, var_name, 64);
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    return node;
}
static int compile_load_variable(unsigned int node,
                                 sCompileInfo * info)
{
    sVar * var;
    int var_index;
    sNodeType * var_type;
    int size;
    sNodeType * result_type;
    sNodeType * result_type2;
    var = get_variable_from_table(info->lv_table,
                                  gNodes[node].uValue.mVarName);
    if (var == (void *) 0)
    {
        compile_err_msg(info,
                        "undeclared variable %s",
                        gNodes[node].uValue.mVarName);
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    gNodes[node].mType = var->mType;
    var_index = get_variable_index(info->lv_table,
                                   gNodes[node].uValue.mVarName);
    if (var_index == -1 || var == (void *) 0 || var->mType == (void *) 0)
    {
        compile_err_msg(info,
                        "can't get type of %s",
                        gNodes[node].uValue.mVarName);
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    ;
    var_type = var->mType;
    append_opecode_to_code(info->code, 32, info->no_output);
    append_int_value_to_code(info->code, var_index, info->no_output);
    size = get_var_size(var_type);
    append_int_value_to_code(info->code, size, info->no_output);
    info->stack_num++;
    result_type = var->mType;
    if (result_type == (void *) 0 || result_type->mClass == (void *) 0)
    {
        compile_err_msg(info,
                        "null type %s",
                        gNodes[node].uValue.mVarName);
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    solve_generics_for_variable(result_type,
                                &result_type2,
                                info->pinfo);
    info->type = result_type2;
    return 1;
}
unsigned int sNodeTree_if_expression(unsigned int expression_node,
                                     sNodeBlock * if_node_block,
                                     unsigned int * elif_expression_nodes,
                                     sNodeBlock * * elif_node_blocks,
                                     int elif_num,
                                     sNodeBlock * else_node_block,
                                     sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeIf;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].uValue.sIf.mExpressionNode = expression_node;
    gNodes[node].uValue.sIf.mIfNodeBlock = if_node_block;
    memcpy(gNodes[node].uValue.sIf.mElifExpressionNodes,
           elif_expression_nodes,
           sizeof(unsigned int) * elif_num);
    memcpy(gNodes[node].uValue.sIf.mElifNodeBlocks,
           elif_node_blocks,
           sizeof(sNodeBlock *) * elif_num);
    gNodes[node].uValue.sIf.mElifNum = elif_num;
    gNodes[node].uValue.sIf.mElseNodeBlock = else_node_block;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    return node;
}
static int compile_if_expression(unsigned int node,
                                 sCompileInfo * info)
{
    int label_num;
    sNodeBlock * else_node_block;
    char label_name_elif[512];
    char label_name_else[512];
    char label_end_point[512];
    sVarTable * lv_table;
    unsigned int expression_node;
    int goto_point;
    sNodeBlock * if_block;
    sNodeType * if_result_type;
    int end_points[32 + 1];
    int num_end_points;
    int i;
    label_num = gLabelNum++;
    else_node_block = gNodes[node].uValue.sIf.mElseNodeBlock;
    create_label_name2("label_elif",
                       label_name_elif,
                       512,
                       label_num,
                       1);
    create_label_name("label_else", label_name_else, 512, label_num);
    create_label_name("label_if_end", label_end_point, 512, label_num);
    lv_table = clone_var_table(info->lv_table);
    expression_node = gNodes[node].uValue.sIf.mExpressionNode;
    if (!compile(expression_node, info))
    {
        return 0;
    }
    if (!type_identify_with_class_name(info->type, "bool"))
    {
        compile_err_msg(info, "This conditional type is not bool");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    append_opecode_to_code(info->code, 5, info->no_output);
    append_int_value_to_code(info->code,
                             sizeof(int) * 3,
                             info->no_output);
    info->stack_num--;
    append_opecode_to_code(info->code, 7, info->no_output);
    goto_point = info->code->mLen;
    append_int_value_to_code(info->code, 0, info->no_output);
    if (gNodes[node].uValue.sIf.mElifNum > 0)
    {
        append_str_to_constant_pool_and_code(info->constant,
                                             info->code,
                                             label_name_elif,
                                             info->no_output);
    }
    else
    {
        append_str_to_constant_pool_and_code(info->constant,
                                             info->code,
                                             label_name_else,
                                             info->no_output);
    }
    if_block = gNodes[node].uValue.sIf.mIfNodeBlock;
    if (!compile_block_with_result(if_block, info))
    {
        return 0;
    }
    restore_var_table(info->lv_table, lv_table);
    append_opecode_to_code(info->code, 29, info->no_output);
    info->stack_num--;
    if_result_type = info->type;
    append_opecode_to_code(info->code, 7, info->no_output);
    end_points[0] = info->code->mLen;
    num_end_points = 1;
    append_int_value_to_code(info->code, 0, info->no_output);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         label_end_point,
                                         info->no_output);
    if (gNodes[node].uValue.sIf.mElifNum > 0)
    {
        int j;
        *(int *) (info->code->mCodes + goto_point) = info->code->mLen;
        append_opecode_to_code(info->code, 18, info->no_output);
        append_str_to_constant_pool_and_code(info->constant,
                                             info->code,
                                             label_name_elif,
                                             info->no_output);
        for (j = 0; j < gNodes[node].uValue.sIf.mElifNum; j++)
        {
            unsigned int elif_expression_node;
            int goto_point;
            char label_name[512];
            sNodeBlock * elif_block;
            sNodeType * elif_result_type;
            lv_table = clone_var_table(info->lv_table);
            elif_expression_node = gNodes[node].uValue.sIf.mElifExpressionNodes[j];
            if (!compile(elif_expression_node, info))
            {
                return 0;
            }
            if (!type_identify_with_class_name(info->type, "bool"))
            {
                compile_err_msg(info, "This conditional type is not bool");
                info->err_num++;
                info->type = create_node_type_with_class_name("int");
                return 1;
            }
            append_opecode_to_code(info->code, 5, info->no_output);
            append_int_value_to_code(info->code,
                                     sizeof(int) * 5,
                                     info->no_output);
            info->stack_num--;
            append_opecode_to_code(info->code, 43, info->no_output);
            info->stack_num++;
            append_opecode_to_code(info->code, 29, info->no_output);
            info->stack_num--;
            append_opecode_to_code(info->code, 7, info->no_output);
            goto_point = info->code->mLen;
            append_int_value_to_code(info->code, 0, info->no_output);
            create_label_name2("label_if_elif", label_name, 512, label_num, j);
            append_str_to_constant_pool_and_code(info->constant,
                                                 info->code,
                                                 label_name,
                                                 info->no_output);
            elif_block = gNodes[node].uValue.sIf.mElifNodeBlocks[j];
            if (!compile_block_with_result(elif_block, info))
            {
                return 0;
            }
            restore_var_table(info->lv_table, lv_table);
            append_opecode_to_code(info->code, 29, info->no_output);
            info->stack_num--;
            elif_result_type = info->type;
            if (!type_identify(if_result_type, elif_result_type))
            {
                if_result_type = create_node_type_with_class_name("Anonymous");
            }
            append_opecode_to_code(info->code, 7, info->no_output);
            end_points[num_end_points] = info->code->mLen;
            num_end_points++;
            append_int_value_to_code(info->code, 0, info->no_output);
            append_str_to_constant_pool_and_code(info->constant,
                                                 info->code,
                                                 label_end_point,
                                                 info->no_output);
            ;
            *(int *) (info->code->mCodes + goto_point) = info->code->mLen;
            append_opecode_to_code(info->code, 18, info->no_output);
            append_str_to_constant_pool_and_code(info->constant,
                                                 info->code,
                                                 label_name,
                                                 info->no_output);
        }
    }
    else
    {
        *(int *) (info->code->mCodes + goto_point) = info->code->mLen;
    }
    if (else_node_block)
    {
        sNodeType * else_result_type;
        append_opecode_to_code(info->code, 18, info->no_output);
        append_str_to_constant_pool_and_code(info->constant,
                                             info->code,
                                             label_name_else,
                                             info->no_output);
        if (!compile_block_with_result(else_node_block, info))
        {
            return 0;
        }
        append_opecode_to_code(info->code, 29, info->no_output);
        info->stack_num--;
        else_result_type = info->type;
        if (!type_identify(if_result_type, else_result_type))
        {
            if_result_type = create_node_type_with_class_name("Anonymous");
        }
        append_opecode_to_code(info->code, 7, info->no_output);
        end_points[num_end_points] = info->code->mLen;
        num_end_points++;
        append_int_value_to_code(info->code, 0, info->no_output);
        append_str_to_constant_pool_and_code(info->constant,
                                             info->code,
                                             label_end_point,
                                             info->no_output);
    }
    else
    {
        append_opecode_to_code(info->code, 18, info->no_output);
        append_str_to_constant_pool_and_code(info->constant,
                                             info->code,
                                             label_name_else,
                                             info->no_output);
        append_opecode_to_code(info->code, 43, info->no_output);
        info->stack_num++;
        append_opecode_to_code(info->code, 29, info->no_output);
        info->stack_num--;
        append_opecode_to_code(info->code, 7, info->no_output);
        end_points[num_end_points] = info->code->mLen;
        num_end_points++;
        append_int_value_to_code(info->code, 0, info->no_output);
        append_str_to_constant_pool_and_code(info->constant,
                                             info->code,
                                             label_end_point,
                                             info->no_output);
    }
    for (i = 0; i < num_end_points; i++)
    {
        *(int *) (info->code->mCodes + end_points[i]) = info->code->mLen;
    }
    append_opecode_to_code(info->code, 18, info->no_output);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         label_end_point,
                                         info->no_output);
    if (info->pinfo->err_num == 0)
    {
        int size;
        append_opecode_to_code(info->code, 30, info->no_output);
        size = get_var_size(if_result_type);
        append_int_value_to_code(info->code, size, info->no_output);
        info->stack_num++;
        info->type = if_result_type;
    }
    return 1;
}
unsigned int sNodeTree_when_expression(unsigned int expression_node,
                                       unsigned int value_nodes[64][64],
                                       int num_values[64],
                                       sNodeBlock * when_blocks[64],
                                       int num_when_block,
                                       sNodeBlock * else_block,
                                       sNodeType * when_types[64],
                                       sNodeType * when_types2[64],
                                       sParserInfo * info)
{
    unsigned node;
    int i;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeWhen;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].uValue.sWhen.mExpressionNode = expression_node;
    gNodes[node].uValue.sWhen.mNumWhenBlock = num_when_block;
    gNodes[node].uValue.sWhen.mElseBlock = else_block;
    for (i = 0; i < num_when_block; i++)
    {
        int j;
        gNodes[node].uValue.sWhen.mWhenBlocks[i] = when_blocks[i];
        gNodes[node].uValue.sWhen.mNumValues[i] = num_values[i];
        gNodes[node].uValue.sWhen.mWhenTypes[i] = when_types[i];
        gNodes[node].uValue.sWhen.mWhenTypes2[i] = when_types2[i];
        for (j = 0; j < num_values[i]; j++)
        {
            gNodes[node].uValue.sWhen.mValueNodes[i][j] = value_nodes[i][j];
        }
    }
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    return node;
}
static int compile_when_expression(unsigned int node,
                                   sCompileInfo * info)
{
    unsigned int expression_node;
    int num_when_block;
    sNodeBlock * else_block;
    unsigned int value_nodes[64][64];
    int num_values[64];
    sNodeBlock * when_blocks[64];
    sNodeType * when_types[64];
    sNodeType * when_types2[64];
    int i;
    char label_end_point[512];
    sNodeType * when_result_type;
    int end_points[64][64];
    expression_node = gNodes[node].uValue.sWhen.mExpressionNode;
    num_when_block = gNodes[node].uValue.sWhen.mNumWhenBlock;
    else_block = gNodes[node].uValue.sWhen.mElseBlock;
    for (i = 0; i < num_when_block; i++)
    {
        int j;
        num_values[i] = gNodes[node].uValue.sWhen.mNumValues[i];
        when_blocks[i] = gNodes[node].uValue.sWhen.mWhenBlocks[i];
        when_types[i] = gNodes[node].uValue.sWhen.mWhenTypes[i];
        when_types2[i] = gNodes[node].uValue.sWhen.mWhenTypes2[i];
        for (j = 0; j < num_values[i]; j++)
        {
            value_nodes[i][j] = gNodes[node].uValue.sWhen.mValueNodes[i][j];
        }
    }
    create_label_name("label_when_end",
                      label_end_point,
                      512,
                      gLabelNum++);
    when_result_type = (void *) 0;
    for (i = 0; i < num_when_block; i++)
    {
        if (when_types[i] || when_types2[i])
        {
            sNodeType * node_type;
            char * str;
            int num_string_expression;
            sCLClass * string_class;
            char * method_name;
            sNodeType * param_types[32];
            int num_params;
            sNodeType * result_type;
            sNodeType * result_method_generics_types;
            int method_index;
            int size;
            sNodeType * var_type;
            int goto_point;
            int label_num;
            char label_name_next_when[512];
            if (when_types[i])
            {
                node_type = when_types[i];
            }
            else
            {
                node_type = when_types2[i];
            }
            if (!compile(expression_node, info))
            {
                return 0;
            }
            append_opecode_to_code(info->code, 1301, info->no_output);
            info->type = create_node_type_with_class_name("String");
            info->stack_num--;
            info->stack_num++;
            str = (char *) ((&node_type->mClass->mConst)->mConst + node_type->mClass->mClassNameOffset);
            num_string_expression = 0;
            append_opecode_to_code(info->code, 9000, info->no_output);
            append_str_to_constant_pool_and_code(info->constant,
                                                 info->code,
                                                 str,
                                                 info->no_output);
            append_int_value_to_code(info->code,
                                     num_string_expression,
                                     info->no_output);
            info->stack_num++;
            info->type = create_node_type_with_class_name("String");
            string_class = get_class("String");
            method_name = "equals";
            num_params = 1;
            param_types[0] = create_node_type_with_class_name("String");
            result_type = (void *) 0;
            result_method_generics_types = (void *) 0;
            method_index = search_for_method(string_class,
                                             "equals",
                                             param_types,
                                             num_params,
                                             0,
                                             string_class->mNumMethods - 1,
                                             (void *) 0,
                                             (void *) 0,
                                             (void *) 0,
                                             &result_type,
                                             0,
                                             0,
                                             &result_method_generics_types);
            if (method_index == -1)
            {
                compile_err_msg(info, "method not found(4)");
                info->err_num++;
                err_msg_for_method_not_found(string_class,
                                             method_name,
                                             param_types,
                                             num_params,
                                             0,
                                             info);
                info->type = create_node_type_with_class_name("int");
                return 1;
            }
            append_opecode_to_code(info->code, 16, info->no_output);
            append_str_to_constant_pool_and_code(info->constant,
                                                 info->code,
                                                 info->sname,
                                                 info->no_output);
            append_int_value_to_code(info->code, info->sline, info->no_output);
            append_opecode_to_code(info->code, 3000, info->no_output);
            append_class_name_to_constant_pool_and_code(info, string_class);
            append_int_value_to_code(info->code,
                                     method_index,
                                     info->no_output);
            size = get_var_size(result_type);
            append_int_value_to_code(info->code, size, info->no_output);
            info->stack_num -= 2;
            info->stack_num++;
            info->type = result_type;
            var_type = (void *) 0;
            if (when_types[i])
            {
                if (gNodes[expression_node].mNodeType == kNodeTypeLoadVariable)
                {
                    sVar * var;
                    var = get_variable_from_table(info->lv_table,
                                                  gNodes[expression_node].uValue.mVarName);
                    var_type = var->mType;
                    var->mType = node_type;
                }
            }
            if (when_types[i])
            {
                append_opecode_to_code(info->code, 5, info->no_output);
            }
            else
            {
                append_opecode_to_code(info->code, 6, info->no_output);
            }
            append_int_value_to_code(info->code,
                                     sizeof(int) * 3,
                                     info->no_output);
            info->stack_num--;
            append_opecode_to_code(info->code, 7, info->no_output);
            goto_point = info->code->mLen;
            append_int_value_to_code(info->code, 0, info->no_output);
            label_num = gLabelNum++;
            create_label_name2("label_name_next_when",
                               label_name_next_when,
                               512,
                               label_num,
                               1);
            append_str_to_constant_pool_and_code(info->constant,
                                                 info->code,
                                                 label_name_next_when,
                                                 info->no_output);
            if (!compile_block_with_result(when_blocks[i], info))
            {
                return 0;
            }
            append_opecode_to_code(info->code, 29, info->no_output);
            info->stack_num--;
            if (when_result_type && type_identify_with_class_name(when_result_type,
                                                                  "Anonymous"))
            {
            }
            else if (when_result_type && !type_identify(info->type,
                                                        when_result_type))
            {
                when_result_type = create_node_type_with_class_name("Anonymous");
            }
            else
            {
                when_result_type = info->type;
            }
            append_opecode_to_code(info->code, 7, info->no_output);
            end_points[i][0] = info->code->mLen;
            append_int_value_to_code(info->code, 0, info->no_output);
            append_str_to_constant_pool_and_code(info->constant,
                                                 info->code,
                                                 label_end_point,
                                                 info->no_output);
            *(int *) (info->code->mCodes + goto_point) = info->code->mLen;
            append_opecode_to_code(info->code, 18, info->no_output);
            append_str_to_constant_pool_and_code(info->constant,
                                                 info->code,
                                                 label_name_next_when,
                                                 info->no_output);
            if (var_type)
            {
                sVar * var;
                var = get_variable_from_table(info->lv_table,
                                              gNodes[expression_node].uValue.mVarName);
                var->mType = var_type;
            }
        }
        else
        {
            int j;
            for (j = 0; j < num_values[i]; j++)
            {
                sNodeType * left_type;
                sCLClass * klass;
                int goto_point;
                int label_num;
                char label_name_next_when[512];
                if (!compile(expression_node, info))
                {
                    return 0;
                }
                left_type = info->type;
                klass = left_type->mClass;
                if (klass->mFlags & 0x1)
                {
                    sNodeType * right_type;
                    if (!compile(value_nodes[i][j], info))
                    {
                        return 0;
                    }
                    right_type = info->type;
                    if (!type_identify(left_type, right_type))
                    {
                        compile_err_msg(info,
                                        "When value type and when type is the different.");
                        info->err_num++;
                        info->type = create_node_type_with_class_name("int");
                        return 1;
                    }
                    if (!binary_operator(left_type,
                                         right_type,
                                         1000,
                                         1010,
                                         1020,
                                         1030,
                                         1040,
                                         1050,
                                         1060,
                                         1070,
                                         1080,
                                         1090,
                                         1100,
                                         1040,
                                         1200,
                                         1040,
                                         1220,
                                         "==",
                                         info))
                    {
                        return 0;
                    }
                    info->type = create_node_type_with_class_name("bool");
                }
                else
                {
                    sCLClass * iequalable;
                    iequalable = get_class("IEqualable");
                    if (!check_implemented_methods_for_interface(iequalable, klass))
                    {
                        compile_err_msg(info,
                                        "Require IEqualable implemented for when value classs(%s)",
                                        (char *) ((&klass->mConst)->mConst + klass->mClassNameOffset));
                        info->err_num++;
                    }
                    if (klass->mFlags & 0x10)
                    {
                        compile_err_msg(info, "Dynamic class type can't be when argument");
                        info->err_num++;
                        info->type = create_node_type_with_class_name("int");
                        return 1;
                    }
                    else if (class_identify_with_class_name(klass, "Anonymous"))
                    {
                        sNodeType * right_type;
                        sNodeType * param_types[32];
                        int num_params;
                        char * method_name;
                        info->pinfo->exist_block_object_err = 0;
                        if (!compile(value_nodes[i][j], info))
                        {
                            return 0;
                        }
                        right_type = info->type;
                        num_params = 1;
                        method_name = "equals";
                        param_types[0] = right_type;
                        if (!info->pinfo->exist_block_object_err)
                        {
                            int num_real_params;
                            int size_method_name_and_params;
                            char method_name_and_params[size_method_name_and_params];
                            sNodeType * result_type;
                            int size;
                            num_real_params = num_params + 1;
                            size_method_name_and_params = 64 + 32 * 64 + 256;
                            create_method_name_and_params(method_name_and_params,
                                                          size_method_name_and_params,
                                                          klass,
                                                          method_name,
                                                          param_types,
                                                          num_params);
                            append_opecode_to_code(info->code, 16, info->no_output);
                            append_str_to_constant_pool_and_code(info->constant,
                                                                 info->code,
                                                                 info->sname,
                                                                 info->no_output);
                            append_int_value_to_code(info->code, info->sline, info->no_output);
                            append_opecode_to_code(info->code, 3001, info->no_output);
                            append_int_value_to_code(info->code,
                                                     num_real_params,
                                                     info->no_output);
                            append_str_to_constant_pool_and_code(info->constant,
                                                                 info->code,
                                                                 method_name_and_params,
                                                                 info->no_output);
                            result_type = create_node_type_with_class_name("bool");
                            size = get_var_size(result_type);
                            append_int_value_to_code(info->code, size, info->no_output);
                            info->stack_num -= num_params + 1;
                            info->stack_num++;
                            info->type = result_type;
                        }
                    }
                    else if (klass->mFlags & 0x2)
                    {
                        sNodeType * right_type;
                        sNodeType * param_types[32];
                        int num_params;
                        char * method_name;
                        info->pinfo->exist_block_object_err = 0;
                        if (!compile(value_nodes[i][j], info))
                        {
                            return 0;
                        }
                        right_type = info->type;
                        if (!type_identify(left_type, right_type))
                        {
                            compile_err_msg(info,
                                            "When value type and when type is the different.");
                            info->err_num++;
                            info->type = create_node_type_with_class_name("int");
                            return 1;
                        }
                        num_params = 1;
                        method_name = "equals";
                        param_types[0] = right_type;
                        if (!info->pinfo->exist_block_object_err)
                        {
                            int num_real_params;
                            int size_method_name_and_params;
                            char method_name_and_params[size_method_name_and_params];
                            sNodeType * result_type;
                            int size;
                            num_real_params = num_params + 1;
                            size_method_name_and_params = 64 + 32 * 64 + 256;
                            create_method_name_and_params(method_name_and_params,
                                                          size_method_name_and_params,
                                                          klass,
                                                          method_name,
                                                          param_types,
                                                          num_params);
                            append_opecode_to_code(info->code, 16, info->no_output);
                            append_str_to_constant_pool_and_code(info->constant,
                                                                 info->code,
                                                                 info->sname,
                                                                 info->no_output);
                            append_int_value_to_code(info->code, info->sline, info->no_output);
                            append_opecode_to_code(info->code, 3001, info->no_output);
                            append_int_value_to_code(info->code,
                                                     num_real_params,
                                                     info->no_output);
                            append_str_to_constant_pool_and_code(info->constant,
                                                                 info->code,
                                                                 method_name_and_params,
                                                                 info->no_output);
                            result_type = create_node_type_with_class_name("bool");
                            size = get_var_size(result_type);
                            append_int_value_to_code(info->code, size, info->no_output);
                            info->stack_num -= num_params + 1;
                            info->stack_num++;
                            info->type = result_type;
                        }
                    }
                    else
                    {
                        sNodeType * right_type;
                        sNodeType * param_types[32];
                        int num_params;
                        char * method_name;
                        sNodeType * result_type;
                        sNodeType * result_method_generics_types;
                        int method_index2;
                        sCLMethod * method;
                        int size;
                        info->pinfo->exist_block_object_err = 0;
                        if (!compile(value_nodes[i][j], info))
                        {
                            return 0;
                        }
                        right_type = info->type;
                        if (!type_identify(left_type, right_type))
                        {
                            compile_err_msg(info,
                                            "When value type and when type is the different.");
                            info->err_num++;
                            info->type = create_node_type_with_class_name("int");
                            return 1;
                        }
                        num_params = 1;
                        method_name = "equals";
                        result_type = (void *) 0;
                        param_types[0] = right_type;
                        result_method_generics_types = (void *) 0;
                        method_index2 = search_for_method(klass,
                                                          method_name,
                                                          param_types,
                                                          num_params,
                                                          0,
                                                          klass->mNumMethods - 1,
                                                          (void *) 0,
                                                          (void *) 0,
                                                          (void *) 0,
                                                          &result_type,
                                                          0,
                                                          0,
                                                          &result_method_generics_types);
                        method = klass->mMethods + method_index2;
                        append_opecode_to_code(info->code, 16, info->no_output);
                        append_str_to_constant_pool_and_code(info->constant,
                                                             info->code,
                                                             info->sname,
                                                             info->no_output);
                        append_int_value_to_code(info->code, info->sline, info->no_output);
                        append_opecode_to_code(info->code, 3000, info->no_output);
                        append_class_name_to_constant_pool_and_code(info, klass);
                        append_int_value_to_code(info->code,
                                                 method_index2,
                                                 info->no_output);
                        size = get_var_size(result_type);
                        append_int_value_to_code(info->code, size, info->no_output);
                        info->stack_num -= num_params + 1;
                        info->stack_num++;
                        info->type = result_type;
                    }
                }
                append_opecode_to_code(info->code, 5, info->no_output);
                append_int_value_to_code(info->code,
                                         sizeof(int) * 3,
                                         info->no_output);
                info->stack_num--;
                append_opecode_to_code(info->code, 7, info->no_output);
                goto_point = info->code->mLen;
                append_int_value_to_code(info->code, 0, info->no_output);
                label_num = gLabelNum++;
                create_label_name2("label_name_next_when",
                                   label_name_next_when,
                                   512,
                                   label_num,
                                   1);
                append_str_to_constant_pool_and_code(info->constant,
                                                     info->code,
                                                     label_name_next_when,
                                                     info->no_output);
                if (!compile_block_with_result(when_blocks[i], info))
                {
                    return 0;
                }
                append_opecode_to_code(info->code, 29, info->no_output);
                info->stack_num--;
                if (when_result_type && type_identify_with_class_name(when_result_type,
                                                                      "Anonymous"))
                {
                }
                else if (when_result_type && !type_identify(info->type,
                                                            when_result_type))
                {
                    when_result_type = create_node_type_with_class_name("Anonymous");
                }
                else
                {
                    when_result_type = info->type;
                }
                append_opecode_to_code(info->code, 7, info->no_output);
                end_points[i][j] = info->code->mLen;
                append_int_value_to_code(info->code, 0, info->no_output);
                append_str_to_constant_pool_and_code(info->constant,
                                                     info->code,
                                                     label_end_point,
                                                     info->no_output);
                *(int *) (info->code->mCodes + goto_point) = info->code->mLen;
                append_opecode_to_code(info->code, 18, info->no_output);
                append_str_to_constant_pool_and_code(info->constant,
                                                     info->code,
                                                     label_name_next_when,
                                                     info->no_output);
            }
        }
    }
    if (else_block)
    {
        if (!compile_block_with_result(else_block, info))
        {
            return 0;
        }
        append_opecode_to_code(info->code, 29, info->no_output);
        info->stack_num--;
        if (when_result_type && type_identify_with_class_name(when_result_type,
                                                              "Anonymous"))
        {
        }
        else if (when_result_type && !type_identify(info->type,
                                                    when_result_type))
        {
            when_result_type = create_node_type_with_class_name("Anonymous");
        }
        else
        {
            when_result_type = info->type;
        }
    }
    else
    {
        append_opecode_to_code(info->code, 43, info->no_output);
        info->stack_num++;
        append_opecode_to_code(info->code, 29, info->no_output);
        info->stack_num--;
    }
    for (i = 0; i < num_when_block; i++)
    {
        int j;
        for (j = 0; j < num_values[i]; j++)
        {
            *(int *) (info->code->mCodes + end_points[i][j]) = info->code->mLen;
        }
    }
    append_opecode_to_code(info->code, 18, info->no_output);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         label_end_point,
                                         info->no_output);
    if (info->pinfo->err_num == 0)
    {
        int size;
        append_opecode_to_code(info->code, 30, info->no_output);
        if (when_result_type == (void *) 0)
        {
            compile_err_msg(info, "When result type is NULL");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        size = get_var_size(when_result_type);
        append_int_value_to_code(info->code, size, info->no_output);
        info->stack_num++;
        info->type = when_result_type;
    }
    return 1;
}
unsigned int sNodeTree_while_expression(unsigned int expression_node,
                                        sNodeBlock * while_node_block,
                                        sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeWhile;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].uValue.sWhile.mExpressionNode = expression_node;
    gNodes[node].uValue.sWhile.mWhileNodeBlock = while_node_block;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    return node;
}
static int compile_while_expression(unsigned int node,
                                    sCompileInfo * info)
{
    int label_num;
    unsigned int expression_node;
    int start_point;
    char start_point_label_name[512];
    int end_point;
    char label_end_point[512];
    char * break_point_label_name_before;
    int num_break_points;
    int break_points[32 + 1];
    int * num_break_points_before;
    int * break_points_before;
    sNodeBlock * while_block;
    int i;
    label_num = gLabelNum++;
    expression_node = gNodes[node].uValue.sWhile.mExpressionNode;
    start_point = info->code->mLen;
    create_label_name("while_start_point",
                      start_point_label_name,
                      512,
                      label_num);
    append_opecode_to_code(info->code, 18, info->no_output);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         start_point_label_name,
                                         info->no_output);
    if (!compile(expression_node, info))
    {
        return 0;
    }
    if (!type_identify_with_class_name(info->type, "bool"))
    {
        compile_err_msg(info, "This conditional type is not bool");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    append_opecode_to_code(info->code, 5, info->no_output);
    append_int_value_to_code(info->code,
                             sizeof(int) * 3,
                             info->no_output);
    info->stack_num--;
    append_opecode_to_code(info->code, 7, info->no_output);
    end_point = info->code->mLen;
    append_int_value_to_code(info->code, 0, info->no_output);
    create_label_name("label_while", label_end_point, 512, label_num);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         label_end_point,
                                         info->no_output);
    break_point_label_name_before = info->break_point_label_name;
    info->break_point_label_name = label_end_point;
    num_break_points = 0;
    memset(break_points, 0, sizeof(int) * 32);
    num_break_points_before = info->num_break_points;
    break_points_before = info->break_points;
    info->num_break_points = &num_break_points;
    info->break_points = break_points;
    while_block = gNodes[node].uValue.sWhile.mWhileNodeBlock;
    if (!compile_block(while_block, info))
    {
        return 0;
    }
    info->num_break_points = num_break_points_before;
    info->break_points = break_points_before;
    info->break_point_label_name = break_point_label_name_before;
    append_opecode_to_code(info->code, 7, info->no_output);
    append_int_value_to_code(info->code, start_point, info->no_output);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         start_point_label_name,
                                         info->no_output);
    *(int *) (info->code->mCodes + end_point) = info->code->mLen;
    for (i = 0; i < num_break_points; i++)
    {
        *(int *) (info->code->mCodes + break_points[i]) = info->code->mLen;
    }
    append_opecode_to_code(info->code, 18, info->no_output);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         label_end_point,
                                         info->no_output);
    if (info->pinfo->err_num == 0)
    {
        append_opecode_to_code(info->code, 43, info->no_output);
        info->stack_num++;
        info->type = create_node_type_with_class_name("Null");
    }
    return 1;
}
unsigned int sNodeTree_for_expression(unsigned int expression_node1,
                                      unsigned int expression_node2,
                                      unsigned int expression_node3,
                                      sNodeBlock * for_node_block,
                                      sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeFor;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].uValue.sFor.mExpressionNode = expression_node1;
    gNodes[node].uValue.sFor.mExpressionNode2 = expression_node2;
    gNodes[node].uValue.sFor.mExpressionNode3 = expression_node3;
    gNodes[node].uValue.sFor.mForNodeBlock = for_node_block;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    return node;
}
static int compile_for_expression(unsigned int node,
                                  sCompileInfo * info)
{
    int label_num;
    unsigned int expression_node;
    unsigned int expression_node2;
    int start_point;
    char start_point_label_name[512];
    int end_point;
    char label_end_point[512];
    char * break_point_label_name_before;
    int num_break_points;
    int break_points[32 + 1];
    int * num_break_points_before;
    int * break_points_before;
    sNodeBlock * for_block;
    sNodeType * expresson_type_in_block;
    unsigned int expression_node3;
    int i;
    label_num = gLabelNum++;
    expression_node = gNodes[node].uValue.sFor.mExpressionNode;
    if (!compile(expression_node, info))
    {
        return 0;
    }
    arrange_stack(info);
    expression_node2 = gNodes[node].uValue.sFor.mExpressionNode2;
    start_point = info->code->mLen;
    create_label_name("for_start_point",
                      start_point_label_name,
                      512,
                      label_num);
    append_opecode_to_code(info->code, 18, info->no_output);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         start_point_label_name,
                                         info->no_output);
    if (!compile(expression_node2, info))
    {
        return 0;
    }
    if (!type_identify_with_class_name(info->type, "bool"))
    {
        compile_err_msg(info, "This conditional type is not bool");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    append_opecode_to_code(info->code, 5, info->no_output);
    append_int_value_to_code(info->code,
                             sizeof(int) * 3,
                             info->no_output);
    info->stack_num--;
    append_opecode_to_code(info->code, 7, info->no_output);
    end_point = info->code->mLen;
    append_int_value_to_code(info->code, 0, info->no_output);
    create_label_name("label_for_end",
                      label_end_point,
                      512,
                      label_num);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         label_end_point,
                                         info->no_output);
    break_point_label_name_before = info->break_point_label_name;
    info->break_point_label_name = label_end_point;
    num_break_points = 0;
    memset(break_points, 0, sizeof(int) * 32);
    num_break_points_before = info->num_break_points;
    break_points_before = info->break_points;
    info->num_break_points = &num_break_points;
    info->break_points = break_points;
    for_block = gNodes[node].uValue.sFor.mForNodeBlock;
    if (!compile_block(for_block, info))
    {
        return 0;
    }
    expresson_type_in_block = info->type;
    info->num_break_points = num_break_points_before;
    info->break_points = break_points_before;
    info->break_point_label_name = break_point_label_name_before;
    expression_node3 = gNodes[node].uValue.sFor.mExpressionNode3;
    if (!compile(expression_node3, info))
    {
        return 0;
    }
    arrange_stack(info);
    append_opecode_to_code(info->code, 7, info->no_output);
    append_int_value_to_code(info->code, start_point, info->no_output);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         start_point_label_name,
                                         info->no_output);
    *(int *) (info->code->mCodes + end_point) = info->code->mLen;
    append_opecode_to_code(info->code, 18, info->no_output);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         label_end_point,
                                         info->no_output);
    for (i = 0; i < num_break_points; i++)
    {
        *(int *) (info->code->mCodes + break_points[i]) = info->code->mLen;
    }
    if (info->pinfo->err_num == 0)
    {
        append_opecode_to_code(info->code, 43, info->no_output);
        info->stack_num++;
        info->type = create_node_type_with_class_name("Null");
    }
    else
    {
        info->type = expresson_type_in_block;
    }
    return 1;
}
unsigned int sNodeTree_break_expression(sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeBreak;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    return node;
}
static int compile_break_expression(unsigned int node,
                                    sCompileInfo * info)
{
    append_opecode_to_code(info->code, 7, info->no_output);
    info->break_points[*info->num_break_points] = info->code->mLen;
    (*info->num_break_points)++;
    if (*info->num_break_points >= 32)
    {
        compile_err_msg(info, "overflow break number");
        return 0;
    }
    append_int_value_to_code(info->code, 0, info->no_output);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         info->break_point_label_name,
                                         info->no_output);
    append_opecode_to_code(info->code, 43, info->no_output);
    info->stack_num++;
    info->type = create_node_type_with_class_name("Null");
    return 1;
}
unsigned int sNodeTree_true_expression(sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeTrue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    return node;
}
static int compile_true_expression(unsigned int node,
                                   sCompileInfo * info)
{
    append_opecode_to_code(info->code, 39, info->no_output);
    append_int_value_to_code(info->code, 1, info->no_output);
    info->stack_num++;
    info->type = create_node_type_with_class_name("bool");
    return 1;
}
unsigned int sNodeTree_false_expression(sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeFalse;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    return node;
}
static int compile_false_expression(unsigned int node,
                                    sCompileInfo * info)
{
    append_opecode_to_code(info->code, 39, info->no_output);
    append_int_value_to_code(info->code, 0, info->no_output);
    info->stack_num++;
    info->type = create_node_type_with_class_name("bool");
    return 1;
}
unsigned int sNodeTree_null_expression(sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeNull;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    return node;
}
static int compile_null_expression(unsigned int node,
                                   sCompileInfo * info)
{
    append_opecode_to_code(info->code, 43, info->no_output);
    info->stack_num++;
    info->type = create_node_type_with_class_name("Null");
    return 1;
}
unsigned int sNodeTree_wildcard_expression(sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeWildCard;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    return node;
}
static int compile_wildcard_expression(unsigned int node,
                                       sCompileInfo * info)
{
    sCLClass * klass;
    klass = get_class("WildCard");
    ;
    append_opecode_to_code(info->code, 4000, info->no_output);
    append_class_name_to_constant_pool_and_code(info, klass);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         "WildCard",
                                         info->no_output);
    append_int_value_to_code(info->code, 0, info->no_output);
    info->stack_num++;
    info->type = create_node_type_with_class_name("WildCard");
    return 1;
}
unsigned int sNodeTree_create_class_method_call(sNodeType * klass,
                                                char * method_name,
                                                unsigned int * params,
                                                int num_params,
                                                sParserInfo * info)
{
    unsigned int node;
    int i;
    node = alloc_node();
    gNodes[node].uValue.sClassMethodCall.mClass = klass;
    xstrncpy(gNodes[node].uValue.sClassMethodCall.mMethodName,
             method_name,
             64);
    gNodes[node].uValue.sClassMethodCall.mNumParams = num_params;
    for (i = 0; i < num_params; i++)
    {
        gNodes[node].uValue.sClassMethodCall.mParams[i] = params[i];
    }
    gNodes[node].mNodeType = kNodeTypeClassMethodCall;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    return node;
}
static sNodeType * get_generics_type_of_inner_class(sParserInfo * pinfo)
{
    sNodeType * result;
    result = (void *) 0;
    if (pinfo->generics_info.mNumParams != 0)
    {
        sGenericsParamInfo * generics_param;
        int i;
        generics_param = &pinfo->generics_info;
        result = alloc_node_type();
        result->mNumGenericsTypes = generics_param->mNumParams;
        for (i = 0; i < generics_param->mNumParams; i++)
        {
            result->mGenericsTypes[i] = create_node_type_with_class_pointer(generics_param->mInterface[i]);
        }
    }
    return result;
}
static sNodeType * get_methocs_generics_type(sParserInfo * info)
{
    sNodeType * result;
    result = (void *) 0;
    if (info->method_generics_info.mNumParams != 0)
    {
        sGenericsParamInfo * generics_param;
        int i;
        generics_param = &info->method_generics_info;
        result = alloc_node_type();
        result->mNumGenericsTypes = generics_param->mNumParams;
        for (i = 0; i < generics_param->mNumParams; i++)
        {
            result->mGenericsTypes[i] = create_node_type_with_class_pointer(generics_param->mInterface[i]);
        }
    }
    return result;
}
int compile_params_method_default_value(sCLClass * klass,
                                        char * method_name,
                                        int * num_params,
                                        unsigned int params[32],
                                        sNodeType * param_types[32],
                                        sNodeType * generics_types,
                                        sCompileInfo * info,
                                        int size_method_indexes,
                                        int method_indexes[],
                                        int num_methods)
{
    int i;
    for (i = 0; i < num_methods; i++)
    {
        sCLMethod * method;
        method = klass->mMethods + method_indexes[i];
        if (method->mNumParams > *num_params)
        {
            int j;
            for (j = 0; j < *num_params; j++)
            {
                sNodeType * param;
                sNodeType * solved_param;
                param = create_node_type_from_cl_type(method->mParams[j].mType,
                                                      klass);
                if (!solve_generics_types_for_node_type(param,
                                                        &solved_param,
                                                        generics_types,
                                                        1,
                                                        0))
                {
                    return 0;
                }
                if (!substitution_posibility(solved_param,
                                             param_types[j],
                                             (void *) 0,
                                             (void *) 0,
                                             (void *) 0,
                                             (void *) 0))
                {
                    break;
                }
            }
            if (j == *num_params)
            {
                int k;
                for (k = *num_params; k < method->mNumParams; k++)
                {
                    sCLParam * param;
                    char * source;
                    param = method->mParams + k;
                    source = (char *) ((&klass->mConst)->mConst + param->mDefaultValueOffset);
                    if (source[0] != '\000')
                    {
                        sParserInfo info2;
                        unsigned int node;
                        info2.p = source;
                        info2.sname = info->pinfo->sname;
                        info2.sline = info->pinfo->sline;
                        info2.err_num = info->pinfo->err_num;
                        info2.lv_table = (void *) 0;
                        info2.parse_phase = info->pinfo->parse_phase;
                        info2.klass = info->pinfo->klass;
                        info2.generics_info = info->pinfo->generics_info;
                        info2.method_generics_info = info->pinfo->method_generics_info;
                        info2.cinfo = info;
                        info2.included_source = 0;
                        info2.get_type_for_interpreter = info->pinfo->get_type_for_interpreter;
                        info2.next_command_is_to_bool = 0;
                        info2.exist_block_object_err = info->pinfo->exist_block_object_err;
                        node = 0;
                        if (!expression(&node, &info2))
                        {
                            return 0;
                        }
                        if (!compile(node, info))
                        {
                            return 0;
                        }
                        param_types[k] = info->type;
                        (*num_params)++;
                    }
                }
                break;
            }
        }
    }
    return 1;
}
static int compile_params(sCLClass * klass,
                          char * method_name,
                          int * num_params,
                          unsigned int params[32],
                          sNodeType * param_types[32],
                          sNodeType * generics_types,
                          sCompileInfo * info,
                          int lazy_lambda_compile,
                          int * exist_lazy_lamda_compile,
                          int class_method)
{
    int size_method_indexes;
    int method_indexes[size_method_indexes];
    int num_methods;
    int i;
    size_method_indexes = 128;
    num_methods = 0;
    if (!search_for_methods_from_method_name(method_indexes,
                                             size_method_indexes,
                                             &num_methods,
                                             klass,
                                             method_name,
                                             klass->mNumMethods - 1,
                                             class_method))
    {
        compile_err_msg(info, "overflow number of the same name methods");
        return 0;
    }
    for (i = 0; i < *num_params; i++)
    {
        int node2;
        enum eNodeType node2_type;
        node2 = params[i];
        node2_type = gNodes[node2].mNodeType;
        if (lazy_lambda_compile && i == *num_params - 1 && node2_type == kNodeTypeBlockObject)
        {
            *exist_lazy_lamda_compile = 1;
        }
        else
        {
            int j;
            if (!compile(node2, info))
            {
                return 0;
            }
            param_types[i] = info->type;
            for (j = 0; j < num_methods; j++)
            {
                sCLMethod * method;
                method = klass->mMethods + method_indexes[j];
                if (*num_params == method->mNumParams && i < method->mNumParams)
                {
                    sNodeType * param;
                    sNodeType * solved_param;
                    param = create_node_type_from_cl_type(method->mParams[i].mType,
                                                          klass);
                    if (!solve_generics_types_for_node_type(param,
                                                            &solved_param,
                                                            generics_types,
                                                            1,
                                                            0))
                    {
                        return 0;
                    }
                    if (solved_param->mClass->mFlags & 0x2)
                    {
                        boxing_to_lapper_class(&param_types[i], info);
                    }
                    else
                    {
                        if (boxing_posibility(solved_param, param_types[i]))
                        {
                            cast_right_type_to_left_type(solved_param, &param_types[i], info);
                        }
                        if (substitution_posibility_with_class_name(solved_param, "Null"))
                        {
                            if (type_identify_with_class_name(param_types[i], "Null"))
                            {
                                param_types[i] = solved_param;
                            }
                        }
                    }
                }
            }
            for (j = 0; j < num_methods; j++)
            {
                sCLMethod * method;
                method = klass->mMethods + method_indexes[j];
                if (*num_params == method->mNumParams && i < method->mNumParams)
                {
                    sNodeType * param;
                    sNodeType * solved_param;
                    param = create_node_type_from_cl_type(method->mParams[i].mType,
                                                          klass);
                    if (!solve_generics_types_for_node_type(param,
                                                            &solved_param,
                                                            generics_types,
                                                            1,
                                                            0))
                    {
                        return 0;
                    }
                    if (unboxing_posibility(solved_param, param_types[i]))
                    {
                        cast_right_type_to_left_type(solved_param, &param_types[i], info);
                    }
                }
            }
        }
    }
    if (! (*exist_lazy_lamda_compile))
    {
        if (!compile_params_method_default_value(klass,
                                                 method_name,
                                                 num_params,
                                                 params,
                                                 param_types,
                                                 generics_types,
                                                 info,
                                                 size_method_indexes,
                                                 method_indexes,
                                                 num_methods))
        {
            return 0;
        }
    }
    return 1;
}
static int compile_class_method_call(unsigned int node,
                                     sCompileInfo * info)
{
    sNodeType * param_types[32];
    sNodeType * klass_type;
    sCLClass * klass;
    int num_params;
    char method_name[64];
    sNodeType * generics_types;
    sNodeType * right_method_generics_types;
    unsigned int params[32];
    int i;
    int exist_lazy_lamda_compile;
    sNodeType * result_type;
    sNodeType * result_method_generics_types;
    int method_index;
    klass_type = gNodes[node].uValue.sClassMethodCall.mClass;
    klass = klass_type->mClass;
    num_params = gNodes[node].uValue.sClassMethodCall.mNumParams;
    xstrncpy(method_name,
             gNodes[node].uValue.sClassMethodCall.mMethodName,
             64);
    if (info->pinfo->klass && klass == info->pinfo->klass)
    {
        generics_types = get_generics_type_of_inner_class(info->pinfo);
    }
    else
    {
        generics_types = klass_type;
    }
    right_method_generics_types = get_methocs_generics_type(info->pinfo);
    info->pinfo->exist_block_object_err = 0;
    for (i = 0; i < num_params; i++)
    {
        params[i] = gNodes[node].uValue.sClassMethodCall.mParams[i];
    }
    exist_lazy_lamda_compile = 0;
    if (!compile_params(klass,
                        method_name,
                        &num_params,
                        params,
                        param_types,
                        generics_types,
                        info,
                        0,
                        &exist_lazy_lamda_compile,
                        1))
    {
        return 0;
    }
    result_method_generics_types = (void *) 0;
    method_index = search_for_method(klass,
                                     method_name,
                                     param_types,
                                     num_params,
                                     1,
                                     klass->mNumMethods - 1,
                                     generics_types,
                                     (void *) 0,
                                     right_method_generics_types,
                                     &result_type,
                                     0,
                                     0,
                                     &result_method_generics_types);
    if (method_index != -1)
    {
        if (!info->pinfo->exist_block_object_err)
        {
            int size;
            append_opecode_to_code(info->code, 16, info->no_output);
            append_str_to_constant_pool_and_code(info->constant,
                                                 info->code,
                                                 info->sname,
                                                 info->no_output);
            append_int_value_to_code(info->code, info->sline, info->no_output);
            append_opecode_to_code(info->code, 3000, info->no_output);
            append_class_name_to_constant_pool_and_code(info, klass);
            append_int_value_to_code(info->code,
                                     method_index,
                                     info->no_output);
            size = get_var_size(result_type);
            append_int_value_to_code(info->code, size, info->no_output);
            info->stack_num -= num_params;
            info->stack_num++;
            info->type = result_type;
        }
    }
    else
    {
        if (klass->mFlags & 0x10)
        {
            int num_method_chains;
            int max_method_chains;
            num_method_chains = 0;
            max_method_chains = gNodes[node].mMaxMethodChains;
            if (!info->pinfo->exist_block_object_err)
            {
                sCLMethod * method;
                sNodeType * result_type;
                int size;
                if (klass->mCallingClassMethodIndex == -1)
                {
                    compile_err_msg(info,
                                    "require calllingClasMethod class method for dynamic class");
                    info->err_num++;
                    info->type = create_node_type_with_class_name("int");
                    return 1;
                }
                method = klass->mMethods + klass->mCallingClassMethodIndex;
                if (num_params >= 256)
                {
                    compile_err_msg(info, "overflow parametor number");
                    return 0;
                }
                append_opecode_to_code(info->code, 16, info->no_output);
                append_str_to_constant_pool_and_code(info->constant,
                                                     info->code,
                                                     info->sname,
                                                     info->no_output);
                append_int_value_to_code(info->code, info->sline, info->no_output);
                append_opecode_to_code(info->code, 3002, info->no_output);
                append_class_name_to_constant_pool_and_code(info, klass);
                append_str_to_constant_pool_and_code(info->constant,
                                                     info->code,
                                                     method_name,
                                                     info->no_output);
                append_int_value_to_code(info->code, num_params, info->no_output);
                append_int_value_to_code(info->code, 1, info->no_output);
                append_int_value_to_code(info->code,
                                         num_method_chains,
                                         info->no_output);
                append_int_value_to_code(info->code,
                                         max_method_chains,
                                         info->no_output);
                result_type = create_node_type_from_cl_type(method->mResultType,
                                                            klass);
                size = get_var_size(result_type);
                append_int_value_to_code(info->code, size, info->no_output);
                info->stack_num -= num_params;
                info->stack_num++;
                info->type = result_type;
            }
        }
        else
        {
            if (info->pinfo->exist_block_object_err == 0)
            {
                compile_err_msg(info, "method not found(1)");
                info->err_num++;
                err_msg_for_method_not_found(klass,
                                             method_name,
                                             param_types,
                                             num_params,
                                             1,
                                             info);
                info->type = create_node_type_with_class_name("int");
            }
            return 1;
        }
    }
    return 1;
}
unsigned int sNodeTree_create_method_call(unsigned int object_node,
                                          char * method_name,
                                          unsigned int * params,
                                          int num_params,
                                          int num_method_chains,
                                          sParserInfo * info)
{
    unsigned int node;
    int i;
    node = alloc_node();
    xstrncpy(gNodes[node].uValue.sMethodCall.mMethodName,
             method_name,
             64);
    gNodes[node].uValue.sMethodCall.mNumParams = num_params;
    for (i = 0; i < num_params; i++)
    {
        gNodes[node].uValue.sMethodCall.mParams[i] = params[i];
    }
    gNodes[node].uValue.sMethodCall.mNumMethodChains = num_method_chains;
    gNodes[node].mNodeType = kNodeTypeMethodCall;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = object_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    return node;
}
struct sCastMethods {
    char * method_name; char * type_;
};
struct sCastMethods gCastMethods[] = { { "to_byte", "byte" }, { "to_ubyte", "ubyte" }, { "to_short", "short" }, { "to_ushort", "ushort" }, { "to_int", "int" }, { "to_uint", "uint" }, { "to_long", "long" }, { "to_ulong", "ulong" }, { "to_float", "float" }, { "to_double", "double" }, { "to_char", "char" }, { "to_pointer", "pointer" }, { "to_bool", "bool" }, { (void *) 0, (void *) 0 } };
static int call_normal_method(unsigned int node,
                              sCompileInfo * info,
                              sNodeType * object_type,
                              sNodeType * generics_types,
                              sCLClass * klass,
                              sNodeType * param_types[32],
                              int num_params,
                              char * method_name,
                              unsigned int params[32],
                              int num_method_chains,
                              int max_method_chains)
{
    if (klass->mFlags & 0x10)
    {
        int no_output_before;
        int stack_num_before;
        int exist_lazy_lamda_compile;
        no_output_before = info->no_output;
        info->no_output = 1;
        stack_num_before = info->stack_num;
        info->pinfo->exist_block_object_err = 0;
        exist_lazy_lamda_compile = 0;
        if (!compile_params(klass,
                            method_name,
                            &num_params,
                            params,
                            param_types,
                            generics_types,
                            info,
                            0,
                            &exist_lazy_lamda_compile,
                            0))
        {
            return 0;
        }
        info->no_output = no_output_before;
        info->stack_num = stack_num_before;
        if (!info->pinfo->exist_block_object_err)
        {
            sNodeType * right_method_generics_types;
            sNodeType * result_type;
            sNodeType * result_method_generics_types;
            int method_index2;
            right_method_generics_types = get_methocs_generics_type(info->pinfo);
            result_method_generics_types = (void *) 0;
            method_index2 = search_for_method(klass,
                                              method_name,
                                              param_types,
                                              num_params,
                                              0,
                                              klass->mNumMethods - 1,
                                              generics_types,
                                              generics_types,
                                              right_method_generics_types,
                                              &result_type,
                                              0,
                                              0,
                                              &result_method_generics_types);
            if (method_index2 != -1)
            {
                int exist_lazy_lamda_compile;
                info->pinfo->exist_block_object_err = 0;
                exist_lazy_lamda_compile = 0;
                if (!compile_params(klass,
                                    method_name,
                                    &num_params,
                                    params,
                                    param_types,
                                    generics_types,
                                    info,
                                    0,
                                    &exist_lazy_lamda_compile,
                                    0))
                {
                    return 0;
                }
                if (!info->pinfo->exist_block_object_err)
                {
                    sCLMethod * method;
                    int size;
                    method = klass->mMethods + method_index2;
                    append_opecode_to_code(info->code, 16, info->no_output);
                    append_str_to_constant_pool_and_code(info->constant,
                                                         info->code,
                                                         info->sname,
                                                         info->no_output);
                    append_int_value_to_code(info->code, info->sline, info->no_output);
                    append_opecode_to_code(info->code, 3000, info->no_output);
                    append_class_name_to_constant_pool_and_code(info, klass);
                    append_int_value_to_code(info->code,
                                             method_index2,
                                             info->no_output);
                    size = get_var_size(result_type);
                    append_int_value_to_code(info->code, size, info->no_output);
                    info->stack_num -= num_params + 1;
                    info->stack_num++;
                    info->type = result_type;
                }
            }
            else if (klass->mCallingMethodIndex != -1)
            {
                int i;
                sCLMethod * method;
                int num_real_params;
                info->pinfo->exist_block_object_err = 0;
                for (i = 0; i < num_params; i++)
                {
                    int node2;
                    node2 = gNodes[node].uValue.sMethodCall.mParams[i];
                    if (!compile(node2, info))
                    {
                        return 0;
                    }
                    if (info->type->mClass->mFlags & 0x1)
                    {
                        boxing_to_lapper_class(&info->type, info);
                    }
                    param_types[i] = info->type;
                }
                method = klass->mMethods + klass->mCallingMethodIndex;
                if (num_params >= 256)
                {
                    compile_err_msg(info, "overflow parametor number");
                    return 0;
                }
                num_real_params = num_params + 1;
                if (num_params >= 256)
                {
                    compile_err_msg(info, "overflow parametor number");
                    return 0;
                }
                if (!info->pinfo->exist_block_object_err)
                {
                    sNodeType * result_type;
                    int size;
                    append_opecode_to_code(info->code, 16, info->no_output);
                    append_str_to_constant_pool_and_code(info->constant,
                                                         info->code,
                                                         info->sname,
                                                         info->no_output);
                    append_int_value_to_code(info->code, info->sline, info->no_output);
                    append_opecode_to_code(info->code, 3002, info->no_output);
                    append_class_name_to_constant_pool_and_code(info, klass);
                    append_str_to_constant_pool_and_code(info->constant,
                                                         info->code,
                                                         method_name,
                                                         info->no_output);
                    append_int_value_to_code(info->code, num_params, info->no_output);
                    append_int_value_to_code(info->code, 0, info->no_output);
                    append_int_value_to_code(info->code,
                                             num_method_chains,
                                             info->no_output);
                    append_int_value_to_code(info->code,
                                             max_method_chains,
                                             info->no_output);
                    result_type = create_node_type_from_cl_type(method->mResultType,
                                                                klass);
                    size = get_var_size(result_type);
                    append_int_value_to_code(info->code, size, info->no_output);
                    info->stack_num -= num_real_params;
                    info->stack_num++;
                    info->type = result_type;
                }
            }
            else
            {
                compile_err_msg(info,
                                "Require the calllingMethod method for dynamic class");
                info->err_num++;
                info->type = create_node_type_with_class_name("int");
                return 1;
            }
        }
    }
    else if (class_identify_with_class_name(klass, "Anonymous"))
    {
        int exist_lazy_lamda_compile;
        info->pinfo->exist_block_object_err = 0;
        exist_lazy_lamda_compile = 0;
        if (!compile_params(klass,
                            method_name,
                            &num_params,
                            params,
                            param_types,
                            generics_types,
                            info,
                            0,
                            &exist_lazy_lamda_compile,
                            0))
        {
            return 0;
        }
        if (!info->pinfo->exist_block_object_err)
        {
            int num_real_params;
            int size_method_name_and_params;
            char method_name_and_params[size_method_name_and_params];
            sNodeType * result_type;
            int size;
            num_real_params = num_params + 1;
            size_method_name_and_params = 64 + 32 * 64 + 256;
            create_method_name_and_params(method_name_and_params,
                                          size_method_name_and_params,
                                          klass,
                                          method_name,
                                          param_types,
                                          num_params);
            append_opecode_to_code(info->code, 16, info->no_output);
            append_str_to_constant_pool_and_code(info->constant,
                                                 info->code,
                                                 info->sname,
                                                 info->no_output);
            append_int_value_to_code(info->code, info->sline, info->no_output);
            append_opecode_to_code(info->code, 3001, info->no_output);
            append_int_value_to_code(info->code,
                                     num_real_params,
                                     info->no_output);
            append_str_to_constant_pool_and_code(info->constant,
                                                 info->code,
                                                 method_name_and_params,
                                                 info->no_output);
            result_type = create_node_type_with_class_name("Anonymous");
            size = get_var_size(result_type);
            append_int_value_to_code(info->code, size, info->no_output);
            info->stack_num -= num_params + 1;
            info->stack_num++;
            info->type = result_type;
        }
    }
    else if (klass->mFlags & 0x2)
    {
        int exist_lazy_lamda_compile;
        info->pinfo->exist_block_object_err = 0;
        exist_lazy_lamda_compile = 0;
        if (!compile_params(klass,
                            method_name,
                            &num_params,
                            params,
                            param_types,
                            generics_types,
                            info,
                            0,
                            &exist_lazy_lamda_compile,
                            0))
        {
            return 0;
        }
        if (!info->pinfo->exist_block_object_err)
        {
            sNodeType * right_method_generics_types;
            sNodeType * result_type;
            sNodeType * result_method_generics_types;
            int method_index2;
            sCLMethod * method;
            int num_real_params;
            int size;
            right_method_generics_types = get_methocs_generics_type(info->pinfo);
            result_method_generics_types = (void *) 0;
            method_index2 = search_for_method(klass,
                                              method_name,
                                              param_types,
                                              num_params,
                                              0,
                                              klass->mNumMethods - 1,
                                              generics_types,
                                              generics_types,
                                              right_method_generics_types,
                                              &result_type,
                                              0,
                                              0,
                                              &result_method_generics_types);
            if (method_index2 == -1)
            {
                compile_err_msg(info, "method not found(2)");
                info->err_num++;
                err_msg_for_method_not_found(klass,
                                             method_name,
                                             param_types,
                                             num_params,
                                             0,
                                             info);
                info->type = create_node_type_with_class_name("int");
                return 1;
            }
            method = klass->mMethods + method_index2;
            num_real_params = method->mNumParams + 1;
            append_opecode_to_code(info->code, 16, info->no_output);
            append_str_to_constant_pool_and_code(info->constant,
                                                 info->code,
                                                 info->sname,
                                                 info->no_output);
            append_int_value_to_code(info->code, info->sline, info->no_output);
            append_opecode_to_code(info->code, 3001, info->no_output);
            append_int_value_to_code(info->code,
                                     num_real_params,
                                     info->no_output);
            append_method_name_and_params_to_constant_pool_and_code(info,
                                                                    klass,
                                                                    method);
            size = get_var_size(result_type);
            append_int_value_to_code(info->code, size, info->no_output);
            info->stack_num -= num_params + 1;
            info->stack_num++;
            info->type = result_type;
        }
    }
    else
    {
        int lazy_lambda_compile;
        int exist_lazy_lamda_compile;
        info->pinfo->exist_block_object_err = 0;
        lazy_lambda_compile = 1;
        exist_lazy_lamda_compile = 0;
        if (!compile_params(klass,
                            method_name,
                            &num_params,
                            params,
                            param_types,
                            generics_types,
                            info,
                            lazy_lambda_compile,
                            &exist_lazy_lamda_compile,
                            0))
        {
            return 0;
        }
        if (!info->pinfo->exist_block_object_err)
        {
            sNodeType * right_method_generics_types;
            sNodeType * result_type;
            sNodeType * result_method_generics_types;
            int method_index2;
            right_method_generics_types = get_methocs_generics_type(info->pinfo);
            result_method_generics_types = (void *) 0;
            method_index2 = search_for_method(klass,
                                              method_name,
                                              param_types,
                                              num_params,
                                              0,
                                              klass->mNumMethods - 1,
                                              generics_types,
                                              generics_types,
                                              right_method_generics_types,
                                              &result_type,
                                              exist_lazy_lamda_compile,
                                              0,
                                              &result_method_generics_types);
            if (method_index2 != -1 && exist_lazy_lamda_compile)
            {
                int node2;
                sCLMethod * method2;
                unsigned int tmp;
                sNodeTree * node_tree;
                int omit_block_result_type;
                sCLParam * param;
                sNodeType * node_type;
                sNodeBlockType * node_block_type;
                sNodeType * block_result_type;
                sNodeBlock * node_block;
                int num_block_params;
                int omit_params;
                int result_type_boxing;
                sNodeType * block_last_type_before;
                int result_type_boxing_before;
                int omit_block_result_type_before;
                sNodeType * return_type2_before;
                node2 = params[num_params - 1];
                method2 = klass->mMethods + method_index2;
                tmp = clone_node(node2);
                node_tree = gNodes + tmp;
                omit_block_result_type = 0;
                param = method2->mParams + method2->mNumParams - 1;
                node_type = create_node_type_from_cl_type(param->mType, klass);
                node_block_type = node_type->mBlockType;
                block_result_type = node_block_type->mResultType;
                node_block = node_tree->uValue.sBlockObject.mBlockObjectCode;
                num_block_params = node_block_type->mNumParams;
                if (node_tree->uValue.sBlockObject.mOmitResultType)
                {
                    if (!type_identify_with_class_name(block_result_type, "Null"))
                    {
                        omit_block_result_type = 1;
                    }
                }
                omit_params = node_tree->uValue.sBlockObject.mOmitParams;
                result_type_boxing = 0;
                if (num_block_params > 0 && omit_params)
                {
                    sNodeType * method_generics_types;
                    sNodeType * generics_types;
                    sVarTable * old_table;
                    sVarTable * new_table;
                    sParserParam block_params[32];
                    int i;
                    sParserInfo info2;
                    int lambda;
                    sNodeBlock * node_block;
                    int omit_result_type;
                    sNodeType * result_type;
                    sNodeType * result_type2;
                    sNodeType * result_type3;
                    method_generics_types = result_method_generics_types;
                    generics_types = info->type;
                    old_table = node_tree->uValue.sBlockObject.mOldTable;
                    new_table = init_block_vtable(old_table);
                    if (num_block_params >= 16)
                    {
                        compile_err_msg(info, "overflow method block parametor max");
                        info->err_num++;
                        return 0;
                    }
                    for (i = 0; i < num_block_params; i++)
                    {
                        sNodeType * block_param;
                        sNodeType * block_param2;
                        sNodeType * block_param3;
                        if (i == 0)
                        {
                            snprintf(block_params[i].mName, 64, "it");
                        }
                        else
                        {
                            snprintf(block_params[i].mName, 64, "it%d", i + 1);
                        }
                        block_param = node_block_type->mParams[i];
                        block_param2 = (void *) 0;
                        if (method_generics_types)
                        {
                            if (!solve_generics_types_for_node_type(block_param,
                                                                    &block_param2,
                                                                    method_generics_types,
                                                                    0,
                                                                    1))
                            {
                                return 0;
                            }
                        }
                        else
                        {
                            block_param2 = block_param;
                        }
                        block_param3 = (void *) 0;
                        if (generics_types)
                        {
                            if (!solve_generics_types_for_node_type(block_param2,
                                                                    &block_param3,
                                                                    generics_types,
                                                                    0,
                                                                    0))
                            {
                                return 0;
                            }
                        }
                        else
                        {
                            block_param3 = block_param2;
                        }
                        block_params[i].mType = block_param3;
                        if (!add_variable_to_table(new_table,
                                                   block_params[i].mName,
                                                   block_params[i].mType))
                        {
                            return 0;
                        }
                    }
                    info2.p = node_block->mSource.mBuf;
                    info2.sname = node_block->mSName;
                    info2.sline = node_block->mSLine;
                    info2.err_num = 0;
                    info2.lv_table = old_table;
                    info2.parse_phase = 0;
                    info2.klass = info->pinfo->klass;
                    info2.generics_info = info->pinfo->generics_info;
                    info2.method_generics_info = info->pinfo->method_generics_info;
                    info2.cinfo = info;
                    info2.included_source = 0;
                    info2.get_type_for_interpreter = info->pinfo->get_type_for_interpreter;
                    info2.next_command_is_to_bool = 0;
                    info2.exist_block_object_err = info->pinfo->exist_block_object_err;
                    lambda = 0;
                    node_block = (void *) 0;
                    if (!parse_block(&node_block, &info2, new_table, 1))
                    {
                        return 0;
                    }
                    info->err_num += info2.err_num;
                    info->pinfo->exist_block_object_err = info2.exist_block_object_err;
                    omit_result_type = 0;
                    result_type = block_result_type;
                    result_type2 = (void *) 0;
                    if (method_generics_types)
                    {
                        if (!solve_generics_types_for_node_type(result_type,
                                                                &result_type2,
                                                                method_generics_types,
                                                                0,
                                                                1))
                        {
                            return 0;
                        }
                    }
                    else
                    {
                        result_type2 = result_type;
                    }
                    result_type3 = (void *) 0;
                    if (generics_types)
                    {
                        if (!solve_generics_types_for_node_type(result_type2,
                                                                &result_type3,
                                                                generics_types,
                                                                0,
                                                                0))
                        {
                            return 0;
                        }
                    }
                    else
                    {
                        result_type3 = result_type2;
                    }
                    if (result_type3 && result_type3->mClass && !(result_type3->mClass->mFlags & 0x1))
                    {
                        result_type_boxing = 1;
                    }
                    node2 = sNodeTree_create_block_object(block_params,
                                                          num_block_params,
                                                          result_type3,
                                                          node_block,
                                                          lambda,
                                                          &info2,
                                                          omit_result_type,
                                                          0,
                                                          old_table);
                }
                block_last_type_before = info->block_last_type;
                info->block_last_type = (void *) 0;
                result_type_boxing_before = info->result_type_boxing;
                info->result_type_boxing = result_type_boxing;
                omit_block_result_type_before = info->omit_block_result_type;
                info->omit_block_result_type2 = omit_block_result_type;
                return_type2_before = info->return_type2;
                info->return_type2 = (void *) 0;
                info->pinfo->exist_block_object_err = 0;
                if (!compile(node2, info))
                {
                    info->block_last_type = block_last_type_before;
                    info->result_type_boxing = result_type_boxing_before;
                    info->omit_block_result_type2 = omit_block_result_type_before;
                    info->return_type2 = return_type2_before;
                    return 0;
                }
                if (!info->pinfo->exist_block_object_err)
                {
                    if (omit_block_result_type)
                    {
                        sNodeType * node_type;
                        int param_class_num;
                        node_type = info->type;
                        if (node_type)
                        {
                            sNodeBlockType * node_block_type;
                            node_block_type = node_type->mBlockType;
                            if (node_block_type && info->return_type2 != (void *) 0)
                            {
                                node_block_type->mResultType = info->return_type2;
                            }
                            else if (node_block_type && type_identify_with_class_name(node_block_type->mResultType,
                                                                                      "Null"))
                            {
                                node_block_type->mResultType = info->block_last_type;
                            }
                        }
                        param_class_num = block_result_type->mClass->mMethodGenericsParamClassNum;
                        if (param_class_num != -1)
                        {
                            result_method_generics_types->mGenericsTypes[param_class_num] = info->block_last_type;
                            result_method_generics_types->mNumGenericsTypes = param_class_num + 1;
                        }
                    }
                    param_types[num_params - 1] = info->type;
                    info->block_last_type = block_last_type_before;
                    info->result_type_boxing = result_type_boxing_before;
                    info->omit_block_result_type2 = omit_block_result_type_before;
                    info->return_type2 = return_type2_before;
                    method_index2 = search_for_method(klass,
                                                      method_name,
                                                      param_types,
                                                      num_params,
                                                      0,
                                                      klass->mNumMethods - 1,
                                                      generics_types,
                                                      generics_types,
                                                      right_method_generics_types,
                                                      &result_type,
                                                      0,
                                                      1,
                                                      &result_method_generics_types);
                }
            }
            else
            {
                if (exist_lazy_lamda_compile)
                {
                    int node2;
                    node2 = params[num_params - 1];
                    if (!compile(node2, info))
                    {
                        return 0;
                    }
                }
            }
            if (!info->pinfo->exist_block_object_err)
            {
                sCLMethod * method;
                int size;
                if (method_index2 == -1)
                {
                    int cast_method_index;
                    int i;
                    cast_method_index = -1;
                    for (i = 0; gCastMethods[i].method_name != (void *) 0; i++)
                    {
                        if (strcmp(method_name, gCastMethods[i].method_name) == 0)
                        {
                            cast_method_index = i;
                            break;
                        }
                    }
                    if (cast_method_index != -1)
                    {
                        char * cast_type_name;
                        sNodeType * left_type;
                        sNodeType * right_type;
                        if (num_params != 0)
                        {
                            compile_err_msg(info, "A cast method doesn't require params");
                            info->err_num++;
                            info->type = create_node_type_with_class_name("int");
                            return 1;
                        }
                        cast_type_name = gCastMethods[cast_method_index].type_;
                        left_type = object_type;
                        right_type = create_node_type_with_class_name(cast_type_name);
                        cast_right_type_to_left_type(left_type, &right_type, info);
                        info->type = right_type;
                        return 1;
                    }
                    else
                    {
                        compile_err_msg(info, "method not found(5)");
                        info->err_num++;
                        err_msg_for_method_not_found(klass,
                                                     method_name,
                                                     param_types,
                                                     num_params,
                                                     0,
                                                     info);
                        info->type = create_node_type_with_class_name("int");
                        return 1;
                    }
                }
                method = klass->mMethods + method_index2;
                append_opecode_to_code(info->code, 16, info->no_output);
                append_str_to_constant_pool_and_code(info->constant,
                                                     info->code,
                                                     info->sname,
                                                     info->no_output);
                append_int_value_to_code(info->code, info->sline, info->no_output);
                append_opecode_to_code(info->code, 3000, info->no_output);
                append_class_name_to_constant_pool_and_code(info, klass);
                append_int_value_to_code(info->code,
                                         method_index2,
                                         info->no_output);
                size = get_var_size(result_type);
                append_int_value_to_code(info->code, size, info->no_output);
                info->stack_num -= num_params + 1;
                info->stack_num++;
                info->type = result_type;
            }
        }
    }
    return 1;
}
static int compile_method_call(unsigned int node,
                               sCompileInfo * info)
{
    unsigned int lnode;
    int num_method_chains;
    int max_method_chains;
    sNodeType * method_generics_types;
    sNodeType * generics_types;
    sNodeType * generics_types2;
    sCLClass * klass;
    sNodeType * object_type;
    sNodeType * param_types[32];
    int num_params;
    char method_name[64];
    unsigned int params[32];
    lnode = gNodes[node].mLeft;
    if (!compile(lnode, info))
    {
        return 0;
    }
    if (info->type == (void *) 0 || type_identify_with_class_name(info->type,
                                                                  "Null"))
    {
        compile_err_msg(info, "no type for method call");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    num_method_chains = gNodes[node].uValue.sMethodCall.mNumMethodChains;
    max_method_chains = gNodes[node].mMaxMethodChains;
    if (info->type->mClass->mFlags & 0x1)
    {
        boxing_to_lapper_class(&info->type, info);
    }
    if (info->type->mClass->mFlags & 0x1)
    {
        compile_err_msg(info, "Primitive class can't be called to method");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    if (info->pinfo->klass)
    {
        method_generics_types = get_methocs_generics_type(info->pinfo);
    }
    else
    {
        method_generics_types = (void *) 0;
    }
    generics_types = info->type;
    if (!solve_generics_types_for_node_type(generics_types,
                                            &generics_types2,
                                            method_generics_types,
                                            1,
                                            1))
    {
        return 0;
    }
    klass = generics_types2->mClass;
    object_type = generics_types2;
    num_params = gNodes[node].uValue.sMethodCall.mNumParams;
    xstrncpy(method_name,
             gNodes[node].uValue.sMethodCall.mMethodName,
             64);
    memcpy(params,
           gNodes[node].uValue.sMethodCall.mParams,
           sizeof(unsigned int) * 32);
    if (strcmp(method_name, "identifyWith") == 0)
    {
        int exist_lazy_lamda_compile;
        sCLClass * param_class;
        exist_lazy_lamda_compile = 0;
        if (!compile_params(klass,
                            method_name,
                            &num_params,
                            params,
                            param_types,
                            generics_types2,
                            info,
                            0,
                            &exist_lazy_lamda_compile,
                            0))
        {
            return 0;
        }
        if (num_params != 1)
        {
            compile_err_msg(info,
                            "identify method require one none primitive class param");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        param_class = param_types[0]->mClass;
        if (param_class->mFlags & 0x1 && !type_identify_with_class_name(param_types[0],
                                                                        "Null"))
        {
            compile_err_msg(info,
                            "Identify method require one none primitive class param");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        append_opecode_to_code(info->code, 1300, info->no_output);
        info->stack_num -= num_params + 1;
        info->stack_num++;
        info->type = create_node_type_with_class_name("bool");
    }
    else if (strcmp(method_name, "className") == 0)
    {
        if (num_params != 0)
        {
            compile_err_msg(info, "className method doesn't require params");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        append_opecode_to_code(info->code, 1301, info->no_output);
        info->stack_num -= num_params + 1;
        info->stack_num++;
        info->type = create_node_type_with_class_name("String");
    }
    else if (strcmp(method_name, "toNull") == 0)
    {
        if (num_params != 0)
        {
            compile_err_msg(info, "toNull method doesn't require params");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        append_opecode_to_code(info->code, 1, info->no_output);
        info->stack_num--;
        append_opecode_to_code(info->code, 43, info->no_output);
        info->stack_num++;
        info->type = create_node_type_with_class_name("Null");
        return 1;
    }
    else if (strcmp(method_name, "ID") == 0)
    {
        if (num_params != 0)
        {
            compile_err_msg(info, "ID method doesn't require params");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    else if (strcmp(method_name, "toAnonymous") == 0)
    {
        if (num_params != 0)
        {
            compile_err_msg(info, "toAnonymous method doesn't require params");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        info->type = create_node_type_with_class_name("Anonymous");
    }
    else if (type_identify_with_class_name(object_type,
                                           "Anonymous") && strcmp(method_name, "cast") == 0)
    {
        char * class_name;
        if (!(num_params == 1 && gNodes[params[0]].mNodeType == kNodeTypeString))
        {
            compile_err_msg(info,
                            "cast method require one String Constant param");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        class_name = gNodes[params[0]].uValue.sString.mString;
        info->type = create_node_type_with_class_name(class_name);
        return 1;
    }
    else if (strcmp(method_name, "is") == 0)
    {
        int exist_lazy_lamda_compile;
        char * class_name;
        if (!(num_params == 1 && gNodes[params[0]].mNodeType == kNodeTypeString))
        {
            compile_err_msg(info,
                            "is method require one String Constant param");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        exist_lazy_lamda_compile = 0;
        if (!compile_params(klass,
                            method_name,
                            &num_params,
                            params,
                            param_types,
                            generics_types2,
                            info,
                            0,
                            &exist_lazy_lamda_compile,
                            0))
        {
            return 0;
        }
        append_opecode_to_code(info->code, 1302, info->no_output);
        info->stack_num -= 2;
        info->stack_num++;
        info->type = create_node_type_with_class_name("bool");
        class_name = gNodes[params[0]].uValue.sString.mString;
        if (gNodes[lnode].mNodeType == kNodeTypeLoadVariable)
        {
            sVar * var;
            var = get_variable_from_table(info->lv_table,
                                          gNodes[lnode].uValue.mVarName);
            var->mType = create_node_type_with_class_name(class_name);
        }
    }
    else
    {
        if (!call_normal_method(node,
                                info,
                                object_type,
                                generics_types2,
                                klass,
                                param_types,
                                num_params,
                                method_name,
                                params,
                                num_method_chains,
                                max_method_chains))
        {
            return 0;
            ;
        }
    }
    return 1;
}
unsigned int sNodeTree_create_new_operator(sNodeType * node_type,
                                           unsigned int * params,
                                           int num_params,
                                           unsigned int array_num,
                                           sParserInfo * info)
{
    unsigned int node;
    int i;
    node = alloc_node();
    gNodes[node].uValue.sNewOperator.mType = node_type;
    gNodes[node].uValue.sNewOperator.mNumParams = num_params;
    for (i = 0; i < num_params; i++)
    {
        gNodes[node].uValue.sNewOperator.mParams[i] = params[i];
    }
    gNodes[node].uValue.sNewOperator.mArrayNum = array_num;
    gNodes[node].mNodeType = kNodeTypeNewOperator;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mType = (void *) 0;
    return node;
}
static int compile_new_operator(unsigned int node,
                                sCompileInfo * info)
{
    sNodeType * generics_types;
    sNodeType * generics_types2;
    sCLClass * klass;
    unsigned int array_num;
    sNodeType * node_type;
    generics_types = gNodes[node].uValue.sNewOperator.mType;
    if (generics_types->mClass == (void *) 0)
    {
        compile_err_msg(info, "Class not found for new operator");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    solve_generics_for_variable(generics_types,
                                &generics_types2,
                                info->pinfo);
    klass = generics_types2->mClass;
    array_num = gNodes[node].uValue.sNewOperator.mArrayNum;
    if (array_num > 0)
    {
        if (!compile(array_num, info))
        {
            return 0;
        }
    }
    node_type = generics_types2;
    append_opecode_to_code(info->code, 4000, info->no_output);
    append_class_name_to_constant_pool_and_code(info, klass);
    append_type_name_to_constant_pool_and_code(info, node_type);
    append_int_value_to_code(info->code,
                             array_num ? 1 : 0,
                             info->no_output);
    info->stack_num++;
    if (array_num > 0)
    {
        int num_params;
        num_params = gNodes[node].uValue.sNewOperator.mNumParams;
        if (num_params > 0)
        {
            compile_err_msg(info, "Array can't create with initialize method");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        info->type = generics_types2;
        info->type->mArray = 1;
        info->stack_num--;
    }
    else
    {
        sNodeType * param_types[32];
        int num_params;
        char * method_name;
        unsigned int params[32];
        int exist_lazy_lamda_compile;
        num_params = gNodes[node].uValue.sNewOperator.mNumParams;
        method_name = "initialize";
        memcpy(params,
               gNodes[node].uValue.sNewOperator.mParams,
               sizeof(unsigned int) * 32);
        info->pinfo->exist_block_object_err = 0;
        exist_lazy_lamda_compile = 0;
        if (!compile_params(klass,
                            method_name,
                            &num_params,
                            params,
                            param_types,
                            generics_types2,
                            info,
                            0,
                            &exist_lazy_lamda_compile,
                            0))
        {
            return 0;
        }
        if (!info->pinfo->exist_block_object_err)
        {
            sNodeType * right_method_generics_types;
            sNodeType * result_type;
            sNodeType * result_method_generics_types;
            int method_index;
            int size;
            right_method_generics_types = get_methocs_generics_type(info->pinfo);
            result_method_generics_types = (void *) 0;
            method_index = search_for_method(klass,
                                             method_name,
                                             param_types,
                                             num_params,
                                             0,
                                             klass->mNumMethods - 1,
                                             generics_types2,
                                             generics_types2,
                                             right_method_generics_types,
                                             &result_type,
                                             0,
                                             0,
                                             &result_method_generics_types);
            if (method_index == -1)
            {
                compile_err_msg(info, "method not found(6)");
                info->err_num++;
                err_msg_for_method_not_found(klass,
                                             method_name,
                                             param_types,
                                             num_params,
                                             0,
                                             info);
                info->type = create_node_type_with_class_name("int");
                return 1;
            }
            append_opecode_to_code(info->code, 16, info->no_output);
            append_str_to_constant_pool_and_code(info->constant,
                                                 info->code,
                                                 info->sname,
                                                 info->no_output);
            append_int_value_to_code(info->code, info->sline, info->no_output);
            append_opecode_to_code(info->code, 3000, info->no_output);
            append_class_name_to_constant_pool_and_code(info, klass);
            append_int_value_to_code(info->code,
                                     method_index,
                                     info->no_output);
            size = get_var_size(generics_types2);
            append_int_value_to_code(info->code, size, info->no_output);
            info->stack_num -= num_params + 1;
            info->stack_num++;
            info->type = generics_types2;
        }
    }
    return 1;
}
unsigned int sNodeTree_create_return_expression(unsigned int expression_node,
                                                sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeReturn;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = expression_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    return node;
}
static int compile_return_expression(unsigned int node,
                                     sCompileInfo * info)
{
    unsigned int expression_node;
    sNodeType * value_result_type;
    sCLClass * klass;
    sCLMethod * method;
    sNodeType * result_type;
    sNodeType * result_type2;
    expression_node = gNodes[node].mLeft;
    if (expression_node != 0)
    {
        if (!compile(expression_node, info))
        {
            return 0;
        }
        value_result_type = info->type;
    }
    else
    {
        value_result_type = create_node_type_with_class_name("Null");
    }
    klass = info->pinfo->klass;
    method = info->method;
    if (method == (void *) 0 && !info->in_block)
    {
        compile_err_msg(info,
                        "Return expression should be in a method definition or in a block object");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    if (!info->in_block && klass && (!(method->mFlags & 0x2) && strcmp((char *) ((&klass->mConst)->mConst + method->mNameOffset),
                                                                       "initialize") == 0) && (!(method->mFlags & 0x2) && strcmp((char *) ((&klass->mConst)->mConst + method->mNameOffset),
                                                                                                                                 "finalize") == 0))
    {
        compile_err_msg(info,
                        "There is in the initialize or finalize method");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    result_type = (void *) 0;
    if (info->omit_block_result_type2)
    {
        info->return_type = value_result_type;
        result_type = value_result_type;
    }
    else if (info->omit_block_result_type)
    {
        info->return_type = value_result_type;
        result_type = value_result_type;
    }
    else if (info->in_block)
    {
        result_type = info->block_result_type;
    }
    else
    {
        result_type = create_node_type_from_cl_type(info->method->mResultType,
                                                    info->pinfo->klass);
    }
    result_type2 = (void *) 0;
    solve_generics_for_variable(result_type,
                                &result_type2,
                                info->pinfo);
    if (!type_identify_with_class_name(result_type2,
                                       "Null") && expression_node == 0 || type_identify_with_class_name(result_type2,
                                                                                                        "Null") && expression_node != 0)
    {
        compile_err_msg(info, "Invalid type of return value(1)");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    if (type_identify_with_class_name(result_type2, "Null"))
    {
        append_opecode_to_code(info->code, 43, info->no_output);
        info->stack_num++;
    }
    else
    {
        cast_right_type_to_left_type(result_type2,
                                     &value_result_type,
                                     info);
        if (!substitution_posibility(result_type2,
                                     value_result_type,
                                     (void *) 0,
                                     (void *) 0,
                                     (void *) 0,
                                     (void *) 0))
        {
            compile_err_msg(info,
                            "Invalid type of return value(2). Left type is %s. Right type is %s.",
                            (char *) ((&result_type2->mClass->mConst)->mConst + result_type2->mClass->mClassNameOffset),
                            (char *) ((&value_result_type->mClass->mConst)->mConst + value_result_type->mClass->mClassNameOffset));
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
    }
    if (info->stack_num != 1)
    {
        compile_err_msg(info, "Invalid type of return value(4)");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    append_opecode_to_code(info->code, 8, info->no_output);
    if (info->pinfo->err_num == 0)
    {
        info->stack_num = 0;
        info->type = create_node_type_with_class_name("Null");
    }
    return 1;
}
unsigned int sNodeTree_create_throw_expression(unsigned int expression_node,
                                               sParserInfo * info)
{
    unsigned node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeThrow;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = expression_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    return node;
}
static int compile_throw_expression(unsigned int node,
                                    sCompileInfo * info)
{
    unsigned int expression_node;
    sNodeType * exception_type;
    expression_node = gNodes[node].mLeft;
    if (expression_node != 0)
    {
        if (!compile(expression_node, info))
        {
            return 0;
        }
    }
    if (info->method == (void *) 0)
    {
        compile_err_msg(info,
                        "Throw expressioin should be in a method definition");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    exception_type = info->type;
    if (!is_exception_type(exception_type))
    {
        compile_err_msg(info, "Invalid type of exception value");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    if (info->stack_num != 1)
    {
        compile_err_msg(info, "Invalid stack num in the throw expression");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    append_opecode_to_code(info->code, 9, info->no_output);
    info->stack_num = 0;
    info->type = create_node_type_with_class_name("Null");
    return 1;
}
unsigned int sNodeTree_try_expression(sNodeBlock * try_node_block,
                                      sNodeBlock * catch_node_block,
                                      char * exception_var_name,
                                      sParserInfo * info)
{
    unsigned int node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeTry;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    gNodes[node].uValue.sTry.mTryNodeBlock = try_node_block;
    gNodes[node].uValue.sTry.mCatchNodeBlock = catch_node_block;
    xstrncpy(gNodes[node].uValue.sTry.mExceptionVarName,
             exception_var_name,
             64);
    return node;
}
static int compile_try_expression(unsigned int node,
                                  sCompileInfo * info)
{
    int label_num;
    int try_offset_point;
    char label_catch_name[512];
    sNodeBlock * try_node_block;
    int goto_point;
    char label_name[512];
    sNodeBlock * catch_node_block;
    label_num = gLabelNum++;
    append_opecode_to_code(info->code, 10, info->no_output);
    try_offset_point = info->code->mLen;
    append_int_value_to_code(info->code, 0, info->no_output);
    create_label_name("catch_label", label_catch_name, 512, label_num);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         label_catch_name,
                                         info->no_output);
    try_node_block = gNodes[node].uValue.sTry.mTryNodeBlock;
    if (!compile_block(try_node_block, info))
    {
        return 0;
    }
    append_opecode_to_code(info->code, 11, info->no_output);
    append_opecode_to_code(info->code, 7, info->no_output);
    goto_point = info->code->mLen;
    append_int_value_to_code(info->code, 0, info->no_output);
    create_label_name("try_end", label_name, 512, label_num);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         label_name,
                                         info->no_output);
    *(int *) (info->code->mCodes + try_offset_point) = info->code->mLen;
    append_opecode_to_code(info->code, 18, info->no_output);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         label_catch_name,
                                         info->no_output);
    catch_node_block = gNodes[node].uValue.sTry.mCatchNodeBlock;
    if (catch_node_block)
    {
        sVarTable * catch_block_var_table;
        char * var_name;
        int var_index;
        catch_block_var_table = catch_node_block->mLVTable;
        var_name = gNodes[node].uValue.sTry.mExceptionVarName;
        var_index = get_variable_index(catch_block_var_table, var_name);
        ;
        append_opecode_to_code(info->code, 13, info->no_output);
        append_int_value_to_code(info->code, var_index, info->no_output);
        append_opecode_to_code(info->code, 12, info->no_output);
        if (!compile_block(catch_node_block, info))
        {
            return 0;
        }
        *(int *) (info->code->mCodes + goto_point) = info->code->mLen;
        append_opecode_to_code(info->code, 18, info->no_output);
        append_str_to_constant_pool_and_code(info->constant,
                                             info->code,
                                             label_name,
                                             info->no_output);
        if (info->pinfo->err_num == 0)
        {
            append_opecode_to_code(info->code, 43, info->no_output);
            info->stack_num++;
            info->type = create_node_type_with_class_name("Null");
        }
    }
    return 1;
}
unsigned int sNodeTree_create_fields(char * name,
                                     unsigned int left_node,
                                     sParserInfo * info)
{
    unsigned int node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeLoadField;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    xstrncpy(gNodes[node].uValue.mVarName, name, 64);
    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    return node;
}
static int compile_load_field(unsigned int node,
                              sCompileInfo * info)
{
    unsigned int lnode;
    sCLClass * klass;
    char field_name[64];
    int array;
    sNodeType * generics_types;
    sCLClass * regex_class;
    sCLClass * char_class;
    lnode = gNodes[node].mLeft;
    if (!compile(lnode, info))
    {
        return 0;
    }
    if (info->type == (void *) 0 || type_identify_with_class_name(info->type,
                                                                  "Null"))
    {
        compile_err_msg(info, "no type for loading field");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    klass = info->type->mClass;
    xstrncpy(field_name, gNodes[node].uValue.mVarName, 64);
    array = info->type->mArray;
    generics_types = info->type;
    if (klass->mGenericsParamClassNum != -1)
    {
        sGenericsParamInfo * generics_info;
        generics_info = &info->pinfo->generics_info;
        if (klass->mGenericsParamClassNum < generics_info->mNumParams)
        {
            klass = generics_info->mInterface[klass->mGenericsParamClassNum];
        }
        else
        {
            compile_err_msg(info, "invalid generics interface method call");
            info->err_num++;
        }
    }
    regex_class = get_class("regex");
    char_class = get_class("char");
    if (array && strcmp(field_name, "length") == 0)
    {
        append_opecode_to_code(info->code, 8000, info->no_output);
        info->stack_num--;
        info->stack_num++;
        info->type = create_node_type_with_class_name("int");
    }
    else if (array && strcmp(field_name, "toArray") == 0)
    {
        cast_right_type_to_Array(&info->type, info);
    }
    else if (klass == char_class && strcmp(field_name,
                                           "to_upper") == 0)
    {
        append_opecode_to_code(info->code, 8150, info->no_output);
        info->type = create_node_type_with_class_name("char");
    }
    else if (klass == char_class && strcmp(field_name,
                                           "to_lower") == 0)
    {
        append_opecode_to_code(info->code, 8151, info->no_output);
        info->type = create_node_type_with_class_name("char");
    }
    else if (klass == regex_class && strcmp(field_name, "global") == 0)
    {
        append_opecode_to_code(info->code, 8100, info->no_output);
        info->type = create_node_type_with_class_name("bool");
    }
    else if (klass == regex_class && strcmp(field_name,
                                            "ignoreCase") == 0)
    {
        append_opecode_to_code(info->code, 8101, info->no_output);
        info->type = create_node_type_with_class_name("bool");
    }
    else if (klass == regex_class && strcmp(field_name,
                                            "multiline") == 0)
    {
        append_opecode_to_code(info->code, 8102, info->no_output);
        info->type = create_node_type_with_class_name("bool");
    }
    else if (klass == regex_class && strcmp(field_name,
                                            "extended") == 0)
    {
        append_opecode_to_code(info->code, 8103, info->no_output);
        info->type = create_node_type_with_class_name("bool");
    }
    else if (klass == regex_class && strcmp(field_name, "dotAll") == 0)
    {
        append_opecode_to_code(info->code, 8104, info->no_output);
        info->type = create_node_type_with_class_name("bool");
    }
    else if (klass == regex_class && strcmp(field_name,
                                            "anchored") == 0)
    {
        append_opecode_to_code(info->code, 8105, info->no_output);
        info->type = create_node_type_with_class_name("bool");
    }
    else if (klass == regex_class && strcmp(field_name,
                                            "dollarEndOnly") == 0)
    {
        append_opecode_to_code(info->code, 8106, info->no_output);
        info->type = create_node_type_with_class_name("bool");
    }
    else if (klass == regex_class && strcmp(field_name,
                                            "ungreedy") == 0)
    {
        append_opecode_to_code(info->code, 8107, info->no_output);
        info->type = create_node_type_with_class_name("bool");
    }
    else if ((klass->mFlags & 0x1 || strcmp((char *) ((&klass->mConst)->mConst + klass->mClassNameOffset),
                                            "regex") == 0) && strcmp(field_name, "toString") == 0)
    {
        cast_right_type_to_String(&info->type, info);
    }
    else if (klass->mFlags & 0x1 && strcmp(field_name,
                                           "toString") == 0)
    {
        cast_right_type_to_String(&info->type, info);
    }
    else if (klass->mFlags & 0x1 && strcmp(field_name, "toByte") == 0)
    {
        cast_right_type_to_Byte(&info->type, info);
    }
    else if (klass->mFlags & 0x1 && strcmp(field_name, "toUByte") == 0)
    {
        cast_right_type_to_UByte(&info->type, info);
    }
    else if (klass->mFlags & 0x1 && strcmp(field_name, "toShort") == 0)
    {
        cast_right_type_to_Short(&info->type, info);
    }
    else if (klass->mFlags & 0x1 && strcmp(field_name,
                                           "toUShort") == 0)
    {
        cast_right_type_to_UShort(&info->type, info);
    }
    else if (klass->mFlags & 0x1 && strcmp(field_name,
                                           "toInteger") == 0)
    {
        cast_right_type_to_Integer(&info->type, info);
    }
    else if (klass->mFlags & 0x1 && strcmp(field_name,
                                           "toUInteger") == 0)
    {
        cast_right_type_to_UInteger(&info->type, info);
    }
    else if (klass->mFlags & 0x1 && strcmp(field_name, "toLong") == 0)
    {
        cast_right_type_to_Long(&info->type, info);
    }
    else if (klass->mFlags & 0x1 && strcmp(field_name, "toULong") == 0)
    {
        cast_right_type_to_ULong(&info->type, info);
    }
    else if (klass->mFlags & 0x1 && strcmp(field_name, "toFloat") == 0)
    {
        cast_right_type_to_Float(&info->type, info);
    }
    else if (klass->mFlags & 0x1 && strcmp(field_name,
                                           "toDouble") == 0)
    {
        cast_right_type_to_Double(&info->type, info);
    }
    else if (klass->mFlags & 0x1 && strcmp(field_name,
                                           "toPointer") == 0)
    {
        cast_right_type_to_Pointer(&info->type, info);
    }
    else if (klass->mFlags & 0x1 && strcmp(field_name, "toChar") == 0)
    {
        cast_right_type_to_Char(&info->type, info);
    }
    else if (klass->mFlags & 0x1 && strcmp(field_name, "toBool") == 0)
    {
        cast_right_type_to_Bool(&info->type, info);
    }
    else if (klass->mFlags & 0x1 && strcmp(field_name, "to_byte") == 0)
    {
        cast_right_type_to_byte(&info->type, info);
    }
    else if (klass->mFlags & 0x1 && strcmp(field_name,
                                           "to_ubyte") == 0)
    {
        cast_right_type_to_ubyte(&info->type, info);
    }
    else if (klass->mFlags & 0x1 && strcmp(field_name,
                                           "to_short") == 0)
    {
        cast_right_type_to_short(&info->type, info);
    }
    else if (klass->mFlags & 0x1 && strcmp(field_name,
                                           "to_ushort") == 0)
    {
        cast_right_type_to_ushort(&info->type, info);
    }
    else if (klass->mFlags & 0x1 && strcmp(field_name, "to_int") == 0)
    {
        cast_right_type_to_int(&info->type, info);
    }
    else if (klass->mFlags & 0x1 && strcmp(field_name, "to_uint") == 0)
    {
        cast_right_type_to_uint(&info->type, info);
    }
    else if (klass->mFlags & 0x1 && strcmp(field_name, "to_long") == 0)
    {
        cast_right_type_to_long(&info->type, info);
    }
    else if (klass->mFlags & 0x1 && strcmp(field_name,
                                           "to_ulong") == 0)
    {
        cast_right_type_to_ulong(&info->type, info);
    }
    else if (klass->mFlags & 0x1 && strcmp(field_name,
                                           "to_float") == 0)
    {
        cast_right_type_to_float(&info->type, info);
    }
    else if (klass->mFlags & 0x1 && strcmp(field_name,
                                           "to_double") == 0)
    {
        cast_right_type_to_double(&info->type, info);
    }
    else if (klass->mFlags & 0x1 && strcmp(field_name, "to_char") == 0)
    {
        cast_right_type_to_char(&info->type, info);
    }
    else if (klass->mFlags & 0x1 && strcmp(field_name,
                                           "to_pointer") == 0)
    {
        cast_right_type_to_pointer(&info->type, info);
    }
    else if (klass->mFlags & 0x1 && strcmp(field_name, "to_bool") == 0)
    {
        cast_right_type_to_bool(&info->type, info);
    }
    else
    {
        int field_index;
        sCLField * field;
        sNodeType * field_type;
        sNodeType * solved_field_type;
        int size;
        field_index = search_for_field(klass, field_name);
        if (field_index == -1)
        {
            compile_err_msg(info,
                            "There is no field(%s) in this class(%s)(6)",
                            field_name,
                            (char *) ((&klass->mConst)->mConst + klass->mClassNameOffset));
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        field = klass->mFields + field_index;
        field_type = create_node_type_from_cl_type(field->mResultType,
                                                   klass);
        if (!solve_generics_types_for_node_type(field_type,
                                                &solved_field_type,
                                                generics_types,
                                                1,
                                                0))
        {
            return 0;
        }
        append_opecode_to_code(info->code, 4001, info->no_output);
        append_int_value_to_code(info->code, field_index, info->no_output);
        size = get_var_size(field_type);
        append_int_value_to_code(info->code, size, info->no_output);
        info->stack_num--;
        info->stack_num++;
        info->type = solved_field_type;
    }
    return 1;
}
unsigned int sNodeTree_create_assign_field(char * var_name,
                                           unsigned int left_node,
                                           unsigned int right_node,
                                           sParserInfo * info)
{
    unsigned int node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeStoreField;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    xstrncpy(gNodes[node].uValue.mVarName, var_name, 64);
    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    return node;
}
static int compile_store_field(unsigned int node,
                               sCompileInfo * info)
{
    unsigned int lnode;
    sNodeType * left_type;
    sNodeType * generics_types;
    unsigned int rnode;
    sNodeType * right_type;
    sCLClass * klass;
    char field_name[64];
    int field_index;
    sCLField * field;
    sNodeType * field_type;
    sNodeType * solved_field_type;
    lnode = gNodes[node].mLeft;
    if (!compile(lnode, info))
    {
        return 0;
    }
    left_type = info->type;
    generics_types = left_type;
    if (left_type == (void *) 0 || type_identify_with_class_name(left_type,
                                                                 "Null"))
    {
        compile_err_msg(info, "no type for object");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    rnode = gNodes[node].mRight;
    if (!compile(rnode, info))
    {
        return 0;
    }
    right_type = info->type;
    if (right_type == (void *) 0)
    {
        compile_err_msg(info, "no type for right object type");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    klass = left_type->mClass;
    xstrncpy(field_name, gNodes[node].uValue.mVarName, 64);
    field_index = search_for_field(klass, field_name);
    if (field_index == -1)
    {
        compile_err_msg(info,
                        "There is no field(%s) in this class(%s)(1)",
                        field_name,
                        (char *) ((&klass->mConst)->mConst + klass->mClassNameOffset));
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    field = klass->mFields + field_index;
    field_type = create_node_type_from_cl_type(field->mResultType,
                                               klass);
    if (!solve_generics_types_for_node_type(field_type,
                                            &solved_field_type,
                                            generics_types,
                                            1,
                                            0))
    {
        return 0;
    }
    cast_right_type_to_left_type(solved_field_type, &right_type, info);
    if (!substitution_posibility(solved_field_type,
                                 right_type,
                                 generics_types,
                                 (void *) 0,
                                 (void *) 0,
                                 (void *) 0))
    {
        compile_err_msg(info,
                        "The different type between left type and right type(2). %s and %s",
                        (char *) ((&solved_field_type->mClass->mConst)->mConst + solved_field_type->mClass->mClassNameOffset),
                        (char *) ((&right_type->mClass->mConst)->mConst + right_type->mClass->mClassNameOffset));
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    append_opecode_to_code(info->code, 4003, info->no_output);
    append_int_value_to_code(info->code, field_index, info->no_output);
    info->stack_num--;
    info->type = solved_field_type;
    return 1;
}
unsigned int sNodeTree_create_class_fields(sCLClass * klass,
                                           char * name,
                                           sParserInfo * info)
{
    unsigned int node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeLoadClassField;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    xstrncpy(gNodes[node].uValue.sClassField.mVarName, name, 64);
    gNodes[node].uValue.sClassField.mClass = klass;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    return node;
}
static int compile_load_class_field(unsigned int node,
                                    sCompileInfo * info)
{
    sCLClass * klass;
    char field_name[64];
    int field_index;
    sCLField * field;
    sNodeType * field_type;
    int size;
    klass = gNodes[node].uValue.sClassField.mClass;
    xstrncpy(field_name, gNodes[node].uValue.sClassField.mVarName, 64);
    field_index = search_for_class_field(klass, field_name);
    if (field_index == -1)
    {
        compile_err_msg(info,
                        "There is no field(%s) in this class(%s)(2)",
                        field_name,
                        (char *) ((&klass->mConst)->mConst + klass->mClassNameOffset));
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    field = klass->mClassFields + field_index;
    field_type = create_node_type_from_cl_type(field->mResultType,
                                               klass);
    append_opecode_to_code(info->code, 4004, info->no_output);
    append_class_name_to_constant_pool_and_code(info, klass);
    append_int_value_to_code(info->code, field_index, info->no_output);
    size = get_var_size(field_type);
    append_int_value_to_code(info->code, size, info->no_output);
    info->stack_num++;
    info->type = field_type;
    return 1;
}
unsigned int sNodeTree_create_assign_class_field(sCLClass * klass,
                                                 char * name,
                                                 unsigned int right_node,
                                                 sParserInfo * info)
{
    unsigned int node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeStoreClassField;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    xstrncpy(gNodes[node].uValue.sClassField.mVarName, name, 64);
    gNodes[node].uValue.sClassField.mClass = klass;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    return node;
}
static int compile_store_class_field(unsigned int node,
                                     sCompileInfo * info)
{
    unsigned int rnode;
    sNodeType * right_type;
    sCLClass * klass;
    char field_name[64];
    int field_index;
    sCLField * field;
    sNodeType * field_type;
    rnode = gNodes[node].mRight;
    if (!compile(rnode, info))
    {
        return 0;
    }
    right_type = info->type;
    if (right_type == (void *) 0)
    {
        compile_err_msg(info, "no type for right object type");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    klass = gNodes[node].uValue.sClassField.mClass;
    xstrncpy(field_name, gNodes[node].uValue.sClassField.mVarName, 64);
    field_index = search_for_class_field(klass, field_name);
    if (field_index == -1)
    {
        compile_err_msg(info,
                        "There is no field(%s) in this class(%s)(3)",
                        field_name,
                        (char *) ((&klass->mConst)->mConst + klass->mClassNameOffset));
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    field = klass->mClassFields + field_index;
    field_type = create_node_type_from_cl_type(field->mResultType,
                                               klass);
    cast_right_type_to_left_type(field_type, &right_type, info);
    if (!substitution_posibility(field_type,
                                 right_type,
                                 (void *) 0,
                                 (void *) 0,
                                 (void *) 0,
                                 (void *) 0))
    {
        compile_err_msg(info,
                        "The different type between left type and right type(3). Left type is %s. Right type is %s.",
                        (char *) ((&field_type->mClass->mConst)->mConst + field_type->mClass->mClassNameOffset),
                        (char *) ((&right_type->mClass->mConst)->mConst + right_type->mClass->mClassNameOffset));
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    append_opecode_to_code(info->code, 4006, info->no_output);
    append_class_name_to_constant_pool_and_code(info, klass);
    append_int_value_to_code(info->code, field_index, info->no_output);
    info->type = field_type;
    return 1;
}
unsigned int sNodeTree_create_store_value_to_pointer(unsigned int left_node,
                                                     sNodeType * node_type,
                                                     unsigned int right_node,
                                                     sParserInfo * info)
{
    unsigned int node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeStoreValueToPointer;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = node_type;
    return node;
}
int compile_store_value_to_pointer(unsigned int node,
                                   sCompileInfo * info)
{
    sNodeType * node_type;
    unsigned int lnode;
    sNodeType * left_type;
    unsigned int rnode;
    sNodeType * right_type;
    node_type = gNodes[node].mType;
    lnode = gNodes[node].mLeft;
    if (!compile(lnode, info))
    {
        return 0;
    }
    left_type = info->type;
    if (left_type == (void *) 0 || !type_identify_with_class_name(left_type,
                                                                  "pointer"))
    {
        compile_err_msg(info, "Left node requires the pointer class");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    rnode = gNodes[node].mRight;
    if (!compile(rnode, info))
    {
        return 0;
    }
    right_type = info->type;
    if (right_type == (void *) 0 || !substitution_posibility(node_type,
                                                             right_type,
                                                             (void *) 0,
                                                             (void *) 0,
                                                             (void *) 0,
                                                             (void *) 0))
    {
        if (right_type == (void *) 0 || node_type->mClass == (void *) 0)
        {
            compile_err_msg(info,
                            "The different type between left type and right type(4). NULL type.");
        }
        else
        {
            compile_err_msg(info,
                            "The different type between left type and right type(4). Left type is %s. right type is %s",
                            (char *) ((&node_type->mClass->mConst)->mConst + node_type->mClass->mClassNameOffset),
                            (char *) ((&right_type->mClass->mConst)->mConst + right_type->mClass->mClassNameOffset));
        }
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    if (node_type->mArray)
    {
        append_opecode_to_code(info->code, 5013, info->no_output);
    }
    else if (type_identify_with_class_name(node_type, "int"))
    {
        append_opecode_to_code(info->code, 5000, info->no_output);
    }
    else if (type_identify_with_class_name(node_type, "uint"))
    {
        append_opecode_to_code(info->code, 5001, info->no_output);
    }
    else if (type_identify_with_class_name(node_type, "byte"))
    {
        append_opecode_to_code(info->code, 5002, info->no_output);
    }
    else if (type_identify_with_class_name(node_type, "ubyte"))
    {
        append_opecode_to_code(info->code, 5003, info->no_output);
    }
    else if (type_identify_with_class_name(node_type, "short"))
    {
        append_opecode_to_code(info->code, 5004, info->no_output);
    }
    else if (type_identify_with_class_name(node_type, "ushort"))
    {
        append_opecode_to_code(info->code, 5005, info->no_output);
    }
    else if (type_identify_with_class_name(node_type, "long"))
    {
        append_opecode_to_code(info->code, 5006, info->no_output);
    }
    else if (type_identify_with_class_name(node_type, "ulong"))
    {
        append_opecode_to_code(info->code, 5007, info->no_output);
    }
    else if (type_identify_with_class_name(node_type, "float"))
    {
        append_opecode_to_code(info->code, 5008, info->no_output);
    }
    else if (type_identify_with_class_name(node_type, "double"))
    {
        append_opecode_to_code(info->code, 5009, info->no_output);
    }
    else if (type_identify_with_class_name(node_type, "pointer"))
    {
        append_opecode_to_code(info->code, 5010, info->no_output);
    }
    else if (type_identify_with_class_name(node_type, "char"))
    {
        append_opecode_to_code(info->code, 5011, info->no_output);
    }
    else if (type_identify_with_class_name(node_type, "bool"))
    {
        append_opecode_to_code(info->code, 5012, info->no_output);
    }
    else
    {
        append_opecode_to_code(info->code, 5013, info->no_output);
    }
    info->stack_num--;
    info->type = right_type;
    return 1;
}
unsigned int sNodeTree_create_load_value_from_pointer(unsigned int left_node,
                                                      sNodeType * node_type,
                                                      sParserInfo * info)
{
    unsigned int node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeLoadValueFromPointer;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = node_type;
    return node;
}
int compile_load_value_from_pointer(unsigned int node,
                                    sCompileInfo * info)
{
    sNodeType * node_type;
    unsigned int lnode;
    sNodeType * left_type;
    node_type = gNodes[node].mType;
    lnode = gNodes[node].mLeft;
    if (!compile(lnode, info))
    {
        return 0;
    }
    left_type = info->type;
    if (left_type == (void *) 0 || !type_identify_with_class_name(left_type,
                                                                  "pointer"))
    {
        compile_err_msg(info, "Left node requires the pointer class");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    if (node_type->mArray)
    {
        append_opecode_to_code(info->code, 6013, info->no_output);
    }
    else if (type_identify_with_class_name(node_type, "int"))
    {
        append_opecode_to_code(info->code, 6000, info->no_output);
    }
    else if (type_identify_with_class_name(node_type, "uint"))
    {
        append_opecode_to_code(info->code, 6001, info->no_output);
    }
    else if (type_identify_with_class_name(node_type, "byte"))
    {
        append_opecode_to_code(info->code, 6002, info->no_output);
    }
    else if (type_identify_with_class_name(node_type, "ubyte"))
    {
        append_opecode_to_code(info->code, 6003, info->no_output);
    }
    else if (type_identify_with_class_name(node_type, "short"))
    {
        append_opecode_to_code(info->code, 6004, info->no_output);
    }
    else if (type_identify_with_class_name(node_type, "ushort"))
    {
        append_opecode_to_code(info->code, 6005, info->no_output);
    }
    else if (type_identify_with_class_name(node_type, "long"))
    {
        append_opecode_to_code(info->code, 6006, info->no_output);
    }
    else if (type_identify_with_class_name(node_type, "ulong"))
    {
        append_opecode_to_code(info->code, 6007, info->no_output);
    }
    else if (type_identify_with_class_name(node_type, "float"))
    {
        append_opecode_to_code(info->code, 6008, info->no_output);
    }
    else if (type_identify_with_class_name(node_type, "double"))
    {
        append_opecode_to_code(info->code, 6009, info->no_output);
    }
    else if (type_identify_with_class_name(node_type, "pointer"))
    {
        append_opecode_to_code(info->code, 6010, info->no_output);
    }
    else if (type_identify_with_class_name(node_type, "char"))
    {
        append_opecode_to_code(info->code, 6011, info->no_output);
    }
    else if (type_identify_with_class_name(node_type, "bool"))
    {
        append_opecode_to_code(info->code, 6012, info->no_output);
    }
    else
    {
        append_opecode_to_code(info->code, 6013, info->no_output);
    }
    info->type = node_type;
    return 1;
}
int sNodeTree_create_increment_operand(unsigned int left_node,
                                       sParserInfo * info)
{
    unsigned int node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeIncrementOperand;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    return node;
}
static void increment_operand_core(unsigned int node,
                                   sCompileInfo * info,
                                   unsigned int lnode,
                                   int add_operand,
                                   int sub_operand,
                                   int ldc_operand,
                                   int monadic,
                                   int with_value)
{
    char var_name[64];
    int var_index;
    if (!with_value)
    {
        append_opecode_to_code(info->code, ldc_operand, info->no_output);
        if (ldc_operand == 41 || ldc_operand == 42)
        {
            long long lvalue;
            lvalue = 1;
            append_long_value_to_code(info->code, lvalue, info->no_output);
        }
        else
        {
            append_int_value_to_code(info->code, 1, info->no_output);
        }
        info->stack_num++;
    }
    append_opecode_to_code(info->code, add_operand, info->no_output);
    info->stack_num--;
    xstrncpy(var_name, gNodes[lnode].uValue.mVarName, 64);
    var_index = get_variable_index(info->lv_table, var_name);
    ;
    append_opecode_to_code(info->code, 31, info->no_output);
    append_int_value_to_code(info->code, var_index, info->no_output);
    if (!monadic)
    {
        append_opecode_to_code(info->code, ldc_operand, info->no_output);
        if (ldc_operand == 41 || ldc_operand == 42)
        {
            long long lvalue;
            lvalue = 1;
            append_long_value_to_code(info->code, lvalue, info->no_output);
        }
        else
        {
            append_int_value_to_code(info->code, 1, info->no_output);
        }
        info->stack_num++;
        append_opecode_to_code(info->code, sub_operand, info->no_output);
        info->stack_num--;
    }
}
static int increment_operand_core_for_field(unsigned int node,
                                            sCompileInfo * info,
                                            unsigned int lnode,
                                            int add_operand,
                                            int sub_operand,
                                            int ldc_operand,
                                            int monadic,
                                            int with_value)
{
    unsigned int llnode;
    sCLClass * klass;
    char field_name[64];
    int field_index;
    sCLField * field;
    if (!with_value)
    {
        append_opecode_to_code(info->code, ldc_operand, info->no_output);
        if (ldc_operand == 41 || ldc_operand == 42)
        {
            long long lvalue;
            lvalue = 1;
            append_long_value_to_code(info->code, lvalue, info->no_output);
        }
        else
        {
            append_int_value_to_code(info->code, 1, info->no_output);
        }
        info->stack_num++;
    }
    append_opecode_to_code(info->code, add_operand, info->no_output);
    info->stack_num--;
    llnode = gNodes[lnode].mLeft;
    if (!compile(llnode, info))
    {
        return 0;
    }
    klass = info->type->mClass;
    xstrncpy(field_name, gNodes[lnode].uValue.mVarName, 64);
    field_index = search_for_field(klass, field_name);
    ;
    field = klass->mFields + field_index;
    append_opecode_to_code(info->code, 3, info->no_output);
    append_opecode_to_code(info->code, 4003, info->no_output);
    append_int_value_to_code(info->code, field_index, info->no_output);
    info->stack_num--;
    if (!monadic)
    {
        append_opecode_to_code(info->code, ldc_operand, info->no_output);
        if (ldc_operand == 41 || ldc_operand == 42)
        {
            long long lvalue;
            lvalue = 1;
            append_long_value_to_code(info->code, lvalue, info->no_output);
        }
        else
        {
            append_int_value_to_code(info->code, 1, info->no_output);
        }
        info->stack_num++;
        append_opecode_to_code(info->code, sub_operand, info->no_output);
        info->stack_num--;
    }
    return 1;
}
int compile_increment_operand(unsigned int node,
                              sCompileInfo * info)
{
    unsigned int lnode;
    sNodeType * node_type;
    lnode = gNodes[node].mLeft;
    if (!compile(lnode, info))
    {
        return 0;
    }
    if (gNodes[lnode].mNodeType != kNodeTypeLoadVariable && gNodes[lnode].mNodeType != kNodeTypeLoadField || info->type == (void *) 0)
    {
        compile_err_msg(info, "Invalid increment operand");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    node_type = info->type;
    if (gNodes[lnode].mNodeType == kNodeTypeLoadVariable)
    {
        if (type_identify_with_class_name(node_type, "int"))
        {
            increment_operand_core(node, info, lnode, 200, 201, 39, 0, 0);
            info->type = create_node_type_with_class_name("int");
        }
        else if (type_identify_with_class_name(node_type, "uint"))
        {
            increment_operand_core(node, info, lnode, 251, 250, 40, 0, 0);
            info->type = create_node_type_with_class_name("uint");
        }
        else if (type_identify_with_class_name(node_type, "byte"))
        {
            increment_operand_core(node, info, lnode, 50, 51, 35, 0, 0);
            info->type = create_node_type_with_class_name("byte");
        }
        else if (type_identify_with_class_name(node_type, "ubyte"))
        {
            increment_operand_core(node, info, lnode, 80, 81, 36, 0, 0);
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if (type_identify_with_class_name(node_type, "short"))
        {
            increment_operand_core(node, info, lnode, 100, 101, 37, 0, 0);
            info->type = create_node_type_with_class_name("short");
        }
        else if (type_identify_with_class_name(node_type, "ushort"))
        {
            increment_operand_core(node, info, lnode, 150, 151, 38, 0, 0);
            info->type = create_node_type_with_class_name("ushort");
        }
        else if (type_identify_with_class_name(node_type, "long"))
        {
            increment_operand_core(node, info, lnode, 300, 301, 41, 0, 0);
            info->type = create_node_type_with_class_name("long");
        }
        else if (type_identify_with_class_name(node_type, "ulong"))
        {
            increment_operand_core(node, info, lnode, 400, 401, 42, 0, 0);
            info->type = create_node_type_with_class_name("ulong");
        }
        else if (type_identify_with_class_name(node_type, "pointer"))
        {
            increment_operand_core(node, info, lnode, 600, 601, 42, 0, 0);
            info->type = create_node_type_with_class_name("pointer");
        }
        else if (type_identify_with_class_name(node_type, "char"))
        {
            increment_operand_core(node, info, lnode, 700, 701, 39, 0, 0);
            info->type = create_node_type_with_class_name("char");
        }
        else
        {
            compile_err_msg(info, "Invalid type for increment operand");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
    }
    else
    {
        if (type_identify_with_class_name(node_type, "int"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  200,
                                                  201,
                                                  39,
                                                  0,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("int");
        }
        else if (type_identify_with_class_name(node_type, "uint"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  251,
                                                  250,
                                                  40,
                                                  0,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("uint");
        }
        else if (type_identify_with_class_name(node_type, "byte"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  50,
                                                  51,
                                                  35,
                                                  0,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("byte");
        }
        else if (type_identify_with_class_name(node_type, "ubyte"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  80,
                                                  81,
                                                  36,
                                                  0,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if (type_identify_with_class_name(node_type, "short"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  100,
                                                  101,
                                                  37,
                                                  0,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("short");
        }
        else if (type_identify_with_class_name(node_type, "ushort"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  150,
                                                  151,
                                                  38,
                                                  0,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("ushort");
        }
        else if (type_identify_with_class_name(node_type, "long"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  300,
                                                  301,
                                                  41,
                                                  0,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("long");
        }
        else if (type_identify_with_class_name(node_type, "ulong"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  400,
                                                  401,
                                                  42,
                                                  0,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("ulong");
        }
        else if (type_identify_with_class_name(node_type, "pointer"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  600,
                                                  601,
                                                  42,
                                                  0,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("pointer");
        }
        else if (type_identify_with_class_name(node_type, "char"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  700,
                                                  701,
                                                  39,
                                                  0,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("char");
        }
        else
        {
            compile_err_msg(info, "Invalid type for increment operand");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
    }
    return 1;
}
int sNodeTree_create_monadic_increment_operand(unsigned int right_node,
                                               sParserInfo * info)
{
    unsigned int node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeMonadicIncrementOperand;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    return node;
}
static int compile_monadic_increment_operand(unsigned int node,
                                             sCompileInfo * info)
{
    unsigned int rnode;
    sNodeType * node_type;
    rnode = gNodes[node].mRight;
    if (!compile(rnode, info))
    {
        return 0;
    }
    if (gNodes[rnode].mNodeType != kNodeTypeLoadVariable && gNodes[rnode].mNodeType != kNodeTypeLoadField || info->type == (void *) 0)
    {
        compile_err_msg(info, "Invalid monadic increment operand");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    node_type = info->type;
    if (gNodes[rnode].mNodeType == kNodeTypeLoadVariable)
    {
        if (type_identify_with_class_name(node_type, "int"))
        {
            increment_operand_core(node, info, rnode, 200, 201, 39, 1, 0);
            info->type = create_node_type_with_class_name("int");
        }
        else if (type_identify_with_class_name(node_type, "uint"))
        {
            increment_operand_core(node, info, rnode, 251, 250, 40, 1, 0);
            info->type = create_node_type_with_class_name("uint");
        }
        else if (type_identify_with_class_name(node_type, "byte"))
        {
            increment_operand_core(node, info, rnode, 50, 51, 35, 1, 0);
            info->type = create_node_type_with_class_name("byte");
        }
        else if (type_identify_with_class_name(node_type, "ubyte"))
        {
            increment_operand_core(node, info, rnode, 80, 81, 36, 1, 0);
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if (type_identify_with_class_name(node_type, "short"))
        {
            increment_operand_core(node, info, rnode, 100, 101, 37, 1, 0);
            info->type = create_node_type_with_class_name("short");
        }
        else if (type_identify_with_class_name(node_type, "ushort"))
        {
            increment_operand_core(node, info, rnode, 150, 151, 38, 1, 0);
            info->type = create_node_type_with_class_name("ushort");
        }
        else if (type_identify_with_class_name(node_type, "long"))
        {
            increment_operand_core(node, info, rnode, 300, 301, 41, 1, 0);
            info->type = create_node_type_with_class_name("long");
        }
        else if (type_identify_with_class_name(node_type, "ulong"))
        {
            increment_operand_core(node, info, rnode, 400, 401, 42, 1, 0);
            info->type = create_node_type_with_class_name("ulong");
        }
        else if (type_identify_with_class_name(node_type, "pointer"))
        {
            increment_operand_core(node, info, rnode, 600, 601, 42, 1, 0);
            info->type = create_node_type_with_class_name("pointer");
        }
        else if (type_identify_with_class_name(node_type, "char"))
        {
            increment_operand_core(node, info, rnode, 700, 701, 39, 1, 0);
            info->type = create_node_type_with_class_name("char");
        }
        else
        {
            compile_err_msg(info, "Invalid type for increment operand");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
    }
    else
    {
        if (type_identify_with_class_name(node_type, "int"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  rnode,
                                                  200,
                                                  201,
                                                  39,
                                                  1,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("int");
        }
        else if (type_identify_with_class_name(node_type, "uint"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  rnode,
                                                  251,
                                                  250,
                                                  40,
                                                  1,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("uint");
        }
        else if (type_identify_with_class_name(node_type, "byte"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  rnode,
                                                  50,
                                                  51,
                                                  35,
                                                  1,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("byte");
        }
        else if (type_identify_with_class_name(node_type, "ubyte"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  rnode,
                                                  80,
                                                  81,
                                                  36,
                                                  1,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if (type_identify_with_class_name(node_type, "short"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  rnode,
                                                  100,
                                                  101,
                                                  37,
                                                  1,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("short");
        }
        else if (type_identify_with_class_name(node_type, "ushort"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  rnode,
                                                  150,
                                                  151,
                                                  38,
                                                  1,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("ushort");
        }
        else if (type_identify_with_class_name(node_type, "long"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  rnode,
                                                  300,
                                                  301,
                                                  41,
                                                  1,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("long");
        }
        else if (type_identify_with_class_name(node_type, "ulong"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  rnode,
                                                  400,
                                                  401,
                                                  42,
                                                  1,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("ulong");
        }
        else if (type_identify_with_class_name(node_type, "pointer"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  rnode,
                                                  600,
                                                  601,
                                                  42,
                                                  1,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("pointer");
        }
        else if (type_identify_with_class_name(node_type, "char"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  rnode,
                                                  700,
                                                  701,
                                                  39,
                                                  1,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("char");
        }
        else
        {
            compile_err_msg(info, "Invalid type for increment operand");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
    }
    return 1;
}
int sNodeTree_create_increment_operand_with_value(unsigned int left_node,
                                                  unsigned int value,
                                                  sParserInfo * info)
{
    unsigned int node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeIncrementWithValueOperand;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = value;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    return node;
}
int compile_increment_operand_with_value(unsigned int node,
                                         sCompileInfo * info)
{
    unsigned int lnode;
    sNodeType * left_type;
    unsigned int rnode;
    sNodeType * right_type;
    lnode = gNodes[node].mLeft;
    if (!compile(lnode, info))
    {
        return 0;
    }
    if (gNodes[lnode].mNodeType != kNodeTypeLoadVariable && gNodes[lnode].mNodeType != kNodeTypeLoadField || info->type == (void *) 0)
    {
        compile_err_msg(info, "Invalid increment operand");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    left_type = info->type;
    rnode = gNodes[node].mRight;
    if (!compile(rnode, info))
    {
        return 0;
    }
    right_type = info->type;
    cast_right_type_to_left_type(left_type, &right_type, info);
    if (!substitution_posibility(left_type,
                                 right_type,
                                 (void *) 0,
                                 (void *) 0,
                                 (void *) 0,
                                 (void *) 0))
    {
        compile_err_msg(info,
                        "The different type between left type and right type(5). Left type is %s. Right type is %s.",
                        (char *) ((&left_type->mClass->mConst)->mConst + left_type->mClass->mClassNameOffset),
                        (char *) ((&right_type->mClass->mConst)->mConst + right_type->mClass->mClassNameOffset));
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    if (gNodes[lnode].mNodeType == kNodeTypeLoadVariable)
    {
        if (type_identify_with_class_name(left_type, "int"))
        {
            increment_operand_core(node, info, lnode, 200, 201, 39, 0, 1);
            info->type = create_node_type_with_class_name("int");
        }
        else if (type_identify_with_class_name(left_type, "uint"))
        {
            increment_operand_core(node, info, lnode, 251, 250, 40, 0, 1);
            info->type = create_node_type_with_class_name("uint");
        }
        else if (type_identify_with_class_name(left_type, "byte"))
        {
            increment_operand_core(node, info, lnode, 50, 51, 35, 0, 1);
            info->type = create_node_type_with_class_name("byte");
        }
        else if (type_identify_with_class_name(left_type, "ubyte"))
        {
            increment_operand_core(node, info, lnode, 80, 81, 36, 0, 1);
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if (type_identify_with_class_name(left_type, "short"))
        {
            increment_operand_core(node, info, lnode, 100, 101, 37, 0, 1);
            info->type = create_node_type_with_class_name("short");
        }
        else if (type_identify_with_class_name(left_type, "ushort"))
        {
            increment_operand_core(node, info, lnode, 150, 151, 38, 0, 1);
            info->type = create_node_type_with_class_name("ushort");
        }
        else if (type_identify_with_class_name(left_type, "long"))
        {
            increment_operand_core(node, info, lnode, 300, 301, 41, 0, 1);
            info->type = create_node_type_with_class_name("long");
        }
        else if (type_identify_with_class_name(left_type, "ulong"))
        {
            increment_operand_core(node, info, lnode, 400, 401, 42, 0, 1);
            info->type = create_node_type_with_class_name("ulong");
        }
        else if (type_identify_with_class_name(left_type, "pointer"))
        {
            increment_operand_core(node, info, lnode, 600, 601, 42, 0, 1);
            info->type = create_node_type_with_class_name("pointer");
        }
        else if (type_identify_with_class_name(left_type, "char"))
        {
            increment_operand_core(node, info, lnode, 700, 701, 39, 0, 1);
            info->type = create_node_type_with_class_name("char");
        }
        else
        {
            compile_err_msg(info, "Invalid type for increment operand");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
    }
    else
    {
        if (type_identify_with_class_name(left_type, "int"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  200,
                                                  201,
                                                  39,
                                                  0,
                                                  1))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("int");
        }
        else if (type_identify_with_class_name(left_type, "uint"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  251,
                                                  250,
                                                  40,
                                                  0,
                                                  1))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("uint");
        }
        else if (type_identify_with_class_name(left_type, "byte"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  50,
                                                  51,
                                                  35,
                                                  0,
                                                  1))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("byte");
        }
        else if (type_identify_with_class_name(left_type, "ubyte"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  80,
                                                  81,
                                                  36,
                                                  0,
                                                  1))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if (type_identify_with_class_name(left_type, "short"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  100,
                                                  101,
                                                  37,
                                                  0,
                                                  1))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("short");
        }
        else if (type_identify_with_class_name(left_type, "ushort"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  150,
                                                  151,
                                                  38,
                                                  0,
                                                  1))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("ushort");
        }
        else if (type_identify_with_class_name(left_type, "long"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  300,
                                                  301,
                                                  41,
                                                  0,
                                                  1))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("long");
        }
        else if (type_identify_with_class_name(left_type, "ulong"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  400,
                                                  401,
                                                  42,
                                                  0,
                                                  1))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("ulong");
        }
        else if (type_identify_with_class_name(left_type, "pointer"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  600,
                                                  601,
                                                  42,
                                                  0,
                                                  1))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("pointer");
        }
        else if (type_identify_with_class_name(left_type, "char"))
        {
            if (!increment_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  700,
                                                  701,
                                                  39,
                                                  0,
                                                  1))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("char");
        }
        else
        {
            compile_err_msg(info, "Invalid type for increment operand");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
    }
    return 1;
}
static void decrement_operand_core(unsigned int node,
                                   sCompileInfo * info,
                                   unsigned int lnode,
                                   int add_operand,
                                   int sub_operand,
                                   int ldc_operand,
                                   int monadic,
                                   int with_value)
{
    char var_name[64];
    int var_index;
    if (!with_value)
    {
        append_opecode_to_code(info->code, ldc_operand, info->no_output);
        if (ldc_operand == 41 || ldc_operand == 42 || ldc_operand == 44)
        {
            long long lvalue;
            lvalue = 1;
            append_long_value_to_code(info->code, lvalue, info->no_output);
        }
        else
        {
            append_int_value_to_code(info->code, 1, info->no_output);
        }
        info->stack_num++;
    }
    append_opecode_to_code(info->code, sub_operand, info->no_output);
    info->stack_num--;
    xstrncpy(var_name, gNodes[lnode].uValue.mVarName, 64);
    var_index = get_variable_index(info->lv_table, var_name);
    ;
    append_opecode_to_code(info->code, 31, info->no_output);
    append_int_value_to_code(info->code, var_index, info->no_output);
    if (!monadic)
    {
        append_opecode_to_code(info->code, ldc_operand, info->no_output);
        if (ldc_operand == 41 || ldc_operand == 42)
        {
            long long lvalue;
            lvalue = 1;
            append_long_value_to_code(info->code, lvalue, info->no_output);
        }
        else
        {
            append_int_value_to_code(info->code, 1, info->no_output);
        }
        info->stack_num++;
        append_opecode_to_code(info->code, add_operand, info->no_output);
        info->stack_num--;
    }
}
static int decrement_operand_core_for_field(unsigned int node,
                                            sCompileInfo * info,
                                            unsigned int lnode,
                                            int add_operand,
                                            int sub_operand,
                                            int ldc_operand,
                                            int monadic,
                                            int with_value)
{
    unsigned int llnode;
    sCLClass * klass;
    char field_name[64];
    int field_index;
    sCLField * field;
    if (!with_value)
    {
        append_opecode_to_code(info->code, ldc_operand, info->no_output);
        if (ldc_operand == 41 || ldc_operand == 42 || ldc_operand == 44)
        {
            long long lvalue;
            lvalue = 1;
            append_long_value_to_code(info->code, lvalue, info->no_output);
        }
        else
        {
            append_int_value_to_code(info->code, 1, info->no_output);
        }
        info->stack_num++;
    }
    append_opecode_to_code(info->code, sub_operand, info->no_output);
    info->stack_num--;
    llnode = gNodes[lnode].mLeft;
    if (!compile(llnode, info))
    {
        return 0;
    }
    klass = info->type->mClass;
    xstrncpy(field_name, gNodes[lnode].uValue.mVarName, 64);
    field_index = search_for_field(klass, field_name);
    ;
    field = klass->mFields + field_index;
    append_opecode_to_code(info->code, 3, info->no_output);
    append_opecode_to_code(info->code, 4003, info->no_output);
    append_int_value_to_code(info->code, field_index, info->no_output);
    info->stack_num--;
    if (!monadic)
    {
        append_opecode_to_code(info->code, ldc_operand, info->no_output);
        if (ldc_operand == 41 || ldc_operand == 42)
        {
            long long lvalue;
            lvalue = 1;
            append_long_value_to_code(info->code, lvalue, info->no_output);
        }
        else
        {
            append_int_value_to_code(info->code, 1, info->no_output);
        }
        info->stack_num++;
        append_opecode_to_code(info->code, add_operand, info->no_output);
        info->stack_num--;
    }
    return 1;
}
int sNodeTree_create_decrement_operand(unsigned int left_node,
                                       sParserInfo * info)
{
    unsigned int node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeDecrementOperand;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    return node;
}
int compile_decrement_operand(unsigned int node,
                              sCompileInfo * info)
{
    unsigned int lnode;
    sNodeType * node_type;
    lnode = gNodes[node].mLeft;
    if (!compile(lnode, info))
    {
        return 0;
    }
    if (gNodes[lnode].mNodeType != kNodeTypeLoadVariable && gNodes[lnode].mNodeType != kNodeTypeLoadField || info->type == (void *) 0)
    {
        compile_err_msg(info, "Invalid increment operand");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    node_type = info->type;
    if (gNodes[lnode].mNodeType == kNodeTypeLoadVariable)
    {
        if (type_identify_with_class_name(node_type, "int"))
        {
            decrement_operand_core(node, info, lnode, 200, 201, 39, 0, 0);
            info->type = create_node_type_with_class_name("int");
        }
        else if (type_identify_with_class_name(node_type, "uint"))
        {
            decrement_operand_core(node, info, lnode, 251, 250, 40, 0, 0);
            info->type = create_node_type_with_class_name("uint");
        }
        else if (type_identify_with_class_name(node_type, "byte"))
        {
            decrement_operand_core(node, info, lnode, 50, 51, 35, 0, 0);
            info->type = create_node_type_with_class_name("byte");
        }
        else if (type_identify_with_class_name(node_type, "ubyte"))
        {
            decrement_operand_core(node, info, lnode, 80, 81, 36, 0, 0);
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if (type_identify_with_class_name(node_type, "short"))
        {
            decrement_operand_core(node, info, lnode, 100, 101, 37, 0, 0);
            info->type = create_node_type_with_class_name("short");
        }
        else if (type_identify_with_class_name(node_type, "ushort"))
        {
            decrement_operand_core(node, info, lnode, 150, 151, 38, 0, 0);
            info->type = create_node_type_with_class_name("ushort");
        }
        else if (type_identify_with_class_name(node_type, "long"))
        {
            decrement_operand_core(node, info, lnode, 300, 301, 41, 0, 0);
            info->type = create_node_type_with_class_name("long");
        }
        else if (type_identify_with_class_name(node_type, "ulong"))
        {
            decrement_operand_core(node, info, lnode, 400, 401, 42, 0, 0);
            info->type = create_node_type_with_class_name("ulong");
        }
        else if (type_identify_with_class_name(node_type, "pointer"))
        {
            decrement_operand_core(node, info, lnode, 600, 601, 42, 0, 0);
            info->type = create_node_type_with_class_name("pointer");
        }
        else if (type_identify_with_class_name(node_type, "char"))
        {
            decrement_operand_core(node, info, lnode, 700, 701, 39, 0, 0);
            info->type = create_node_type_with_class_name("char");
        }
        else
        {
            compile_err_msg(info, "Invalid type for increment operand");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
    }
    else
    {
        if (type_identify_with_class_name(node_type, "int"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  200,
                                                  201,
                                                  39,
                                                  0,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("int");
        }
        else if (type_identify_with_class_name(node_type, "uint"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  251,
                                                  250,
                                                  40,
                                                  0,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("uint");
        }
        else if (type_identify_with_class_name(node_type, "byte"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  50,
                                                  51,
                                                  35,
                                                  0,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("byte");
        }
        else if (type_identify_with_class_name(node_type, "ubyte"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  80,
                                                  81,
                                                  36,
                                                  0,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if (type_identify_with_class_name(node_type, "short"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  100,
                                                  101,
                                                  37,
                                                  0,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("short");
        }
        else if (type_identify_with_class_name(node_type, "ushort"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  150,
                                                  151,
                                                  38,
                                                  0,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("ushort");
        }
        else if (type_identify_with_class_name(node_type, "long"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  300,
                                                  301,
                                                  41,
                                                  0,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("long");
        }
        else if (type_identify_with_class_name(node_type, "ulong"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  400,
                                                  401,
                                                  42,
                                                  0,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("ulong");
        }
        else if (type_identify_with_class_name(node_type, "pointer"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  600,
                                                  601,
                                                  42,
                                                  0,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("pointer");
        }
        else if (type_identify_with_class_name(node_type, "char"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  700,
                                                  701,
                                                  39,
                                                  0,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("char");
        }
        else
        {
            compile_err_msg(info, "Invalid type for increment operand");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
    }
    return 1;
}
int sNodeTree_create_monadic_decrement_operand(unsigned int right_node,
                                               sParserInfo * info)
{
    unsigned int node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeMonadicDecrementOperand;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    return node;
}
static int compile_monadic_decrement_operand(unsigned int node,
                                             sCompileInfo * info)
{
    unsigned int rnode;
    sNodeType * node_type;
    rnode = gNodes[node].mRight;
    if (!compile(rnode, info))
    {
        return 0;
    }
    if (gNodes[rnode].mNodeType != kNodeTypeLoadVariable && gNodes[rnode].mNodeType != kNodeTypeLoadField || info->type == (void *) 0)
    {
        compile_err_msg(info, "Invalid increment operand");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    node_type = info->type;
    if (gNodes[rnode].mNodeType == kNodeTypeLoadVariable)
    {
        if (type_identify_with_class_name(node_type, "int"))
        {
            decrement_operand_core(node, info, rnode, 200, 201, 39, 1, 0);
            info->type = create_node_type_with_class_name("int");
        }
        else if (type_identify_with_class_name(node_type, "uint"))
        {
            decrement_operand_core(node, info, rnode, 251, 250, 40, 1, 0);
            info->type = create_node_type_with_class_name("uint");
        }
        else if (type_identify_with_class_name(node_type, "byte"))
        {
            decrement_operand_core(node, info, rnode, 50, 51, 35, 1, 0);
            info->type = create_node_type_with_class_name("byte");
        }
        else if (type_identify_with_class_name(node_type, "ubyte"))
        {
            decrement_operand_core(node, info, rnode, 80, 81, 36, 1, 0);
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if (type_identify_with_class_name(node_type, "short"))
        {
            decrement_operand_core(node, info, rnode, 100, 101, 37, 1, 0);
            info->type = create_node_type_with_class_name("short");
        }
        else if (type_identify_with_class_name(node_type, "ushort"))
        {
            decrement_operand_core(node, info, rnode, 150, 151, 38, 1, 0);
            info->type = create_node_type_with_class_name("ushort");
        }
        else if (type_identify_with_class_name(node_type, "long"))
        {
            decrement_operand_core(node, info, rnode, 300, 301, 41, 1, 0);
            info->type = create_node_type_with_class_name("long");
        }
        else if (type_identify_with_class_name(node_type, "ulong"))
        {
            decrement_operand_core(node, info, rnode, 400, 401, 42, 1, 0);
            info->type = create_node_type_with_class_name("ulong");
        }
        else if (type_identify_with_class_name(node_type, "pointer"))
        {
            decrement_operand_core(node, info, rnode, 600, 601, 42, 1, 0);
            info->type = create_node_type_with_class_name("pointer");
        }
        else if (type_identify_with_class_name(node_type, "char"))
        {
            decrement_operand_core(node, info, rnode, 700, 701, 39, 1, 0);
            info->type = create_node_type_with_class_name("char");
        }
        else
        {
            compile_err_msg(info, "Invalid type for increment operand");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
    }
    else
    {
        if (type_identify_with_class_name(node_type, "int"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  rnode,
                                                  200,
                                                  201,
                                                  39,
                                                  1,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("int");
        }
        else if (type_identify_with_class_name(node_type, "uint"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  rnode,
                                                  251,
                                                  250,
                                                  40,
                                                  1,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("uint");
        }
        else if (type_identify_with_class_name(node_type, "byte"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  rnode,
                                                  50,
                                                  51,
                                                  35,
                                                  1,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("byte");
        }
        else if (type_identify_with_class_name(node_type, "ubyte"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  rnode,
                                                  80,
                                                  81,
                                                  36,
                                                  1,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if (type_identify_with_class_name(node_type, "short"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  rnode,
                                                  100,
                                                  101,
                                                  37,
                                                  1,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("short");
        }
        else if (type_identify_with_class_name(node_type, "ushort"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  rnode,
                                                  150,
                                                  151,
                                                  38,
                                                  1,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("ushort");
        }
        else if (type_identify_with_class_name(node_type, "long"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  rnode,
                                                  300,
                                                  301,
                                                  41,
                                                  1,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("long");
        }
        else if (type_identify_with_class_name(node_type, "ulong"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  rnode,
                                                  400,
                                                  401,
                                                  42,
                                                  1,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("ulong");
        }
        else if (type_identify_with_class_name(node_type, "pointer"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  rnode,
                                                  600,
                                                  601,
                                                  42,
                                                  1,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("pointer");
        }
        else if (type_identify_with_class_name(node_type, "char"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  rnode,
                                                  700,
                                                  701,
                                                  39,
                                                  1,
                                                  0))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("char");
        }
        else
        {
            compile_err_msg(info, "Invalid type for increment operand");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
    }
    return 1;
}
int sNodeTree_create_decrement_operand_with_value(unsigned int left_node,
                                                  unsigned int value,
                                                  sParserInfo * info)
{
    unsigned int node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeDecrementWithValueOperand;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = value;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    return node;
}
int compile_decrement_operand_with_value(unsigned int node,
                                         sCompileInfo * info)
{
    unsigned int lnode;
    sNodeType * left_type;
    unsigned int rnode;
    sNodeType * right_type;
    lnode = gNodes[node].mLeft;
    if (!compile(lnode, info))
    {
        return 0;
    }
    if (gNodes[lnode].mNodeType != kNodeTypeLoadVariable && gNodes[lnode].mNodeType != kNodeTypeLoadField || info->type == (void *) 0)
    {
        compile_err_msg(info, "Invalid increment operand");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    left_type = info->type;
    rnode = gNodes[node].mRight;
    if (!compile(rnode, info))
    {
        return 0;
    }
    right_type = info->type;
    cast_right_type_to_left_type(left_type, &right_type, info);
    if (!substitution_posibility(left_type,
                                 right_type,
                                 (void *) 0,
                                 (void *) 0,
                                 (void *) 0,
                                 (void *) 0))
    {
        compile_err_msg(info,
                        "The different type between left type and right type(6). Left type is %s. Right type is %s.",
                        (char *) ((&left_type->mClass->mConst)->mConst + left_type->mClass->mClassNameOffset),
                        (char *) ((&right_type->mClass->mConst)->mConst + right_type->mClass->mClassNameOffset));
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    if (gNodes[lnode].mNodeType == kNodeTypeLoadVariable)
    {
        if (type_identify_with_class_name(left_type, "int"))
        {
            decrement_operand_core(node, info, lnode, 200, 201, 39, 0, 1);
            info->type = create_node_type_with_class_name("int");
        }
        else if (type_identify_with_class_name(left_type, "uint"))
        {
            decrement_operand_core(node, info, lnode, 251, 250, 40, 0, 1);
            info->type = create_node_type_with_class_name("uint");
        }
        else if (type_identify_with_class_name(left_type, "byte"))
        {
            decrement_operand_core(node, info, lnode, 50, 51, 35, 0, 1);
            info->type = create_node_type_with_class_name("byte");
        }
        else if (type_identify_with_class_name(left_type, "ubyte"))
        {
            decrement_operand_core(node, info, lnode, 80, 81, 36, 0, 1);
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if (type_identify_with_class_name(left_type, "short"))
        {
            decrement_operand_core(node, info, lnode, 100, 101, 37, 0, 1);
            info->type = create_node_type_with_class_name("short");
        }
        else if (type_identify_with_class_name(left_type, "ushort"))
        {
            decrement_operand_core(node, info, lnode, 150, 151, 38, 0, 1);
            info->type = create_node_type_with_class_name("ushort");
        }
        else if (type_identify_with_class_name(left_type, "long"))
        {
            decrement_operand_core(node, info, lnode, 300, 301, 41, 0, 1);
            info->type = create_node_type_with_class_name("long");
        }
        else if (type_identify_with_class_name(left_type, "ulong"))
        {
            decrement_operand_core(node, info, lnode, 400, 401, 42, 0, 1);
            info->type = create_node_type_with_class_name("ulong");
        }
        else if (type_identify_with_class_name(left_type, "pointer"))
        {
            decrement_operand_core(node, info, lnode, 600, 601, 42, 0, 1);
            info->type = create_node_type_with_class_name("pointer");
        }
        else if (type_identify_with_class_name(left_type, "char"))
        {
            decrement_operand_core(node, info, lnode, 700, 701, 39, 0, 1);
            info->type = create_node_type_with_class_name("char");
        }
        else
        {
            compile_err_msg(info, "Invalid type for increment operand");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
    }
    else
    {
        if (type_identify_with_class_name(left_type, "int"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  200,
                                                  201,
                                                  39,
                                                  0,
                                                  1))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("int");
        }
        else if (type_identify_with_class_name(left_type, "uint"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  251,
                                                  250,
                                                  40,
                                                  0,
                                                  1))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("uint");
        }
        else if (type_identify_with_class_name(left_type, "byte"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  50,
                                                  51,
                                                  35,
                                                  0,
                                                  1))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("byte");
        }
        else if (type_identify_with_class_name(left_type, "ubyte"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  80,
                                                  81,
                                                  36,
                                                  0,
                                                  1))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("ubyte");
        }
        else if (type_identify_with_class_name(left_type, "short"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  100,
                                                  101,
                                                  37,
                                                  0,
                                                  1))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("short");
        }
        else if (type_identify_with_class_name(left_type, "ushort"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  150,
                                                  151,
                                                  38,
                                                  0,
                                                  1))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("ushort");
        }
        else if (type_identify_with_class_name(left_type, "long"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  300,
                                                  301,
                                                  41,
                                                  0,
                                                  1))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("long");
        }
        else if (type_identify_with_class_name(left_type, "ulong"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  400,
                                                  401,
                                                  42,
                                                  0,
                                                  1))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("ulong");
        }
        else if (type_identify_with_class_name(left_type, "pointer"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  600,
                                                  601,
                                                  42,
                                                  0,
                                                  1))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("pointer");
        }
        else if (type_identify_with_class_name(left_type, "char"))
        {
            if (!decrement_operand_core_for_field(node,
                                                  info,
                                                  lnode,
                                                  700,
                                                  701,
                                                  39,
                                                  0,
                                                  1))
            {
                return 0;
            }
            info->type = create_node_type_with_class_name("char");
        }
        else
        {
            compile_err_msg(info, "Invalid type for increment operand");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
    }
    return 1;
}
unsigned int sNodeTree_create_load_array_element(unsigned int array,
                                                 unsigned int index_node,
                                                 sParserInfo * info)
{
    unsigned int node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeLoadArrayElement;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = array;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = index_node;
    gNodes[node].mType = (void *) 0;
    return node;
}
int compile_load_array_element(unsigned int node,
                               sCompileInfo * info)
{
    unsigned int lnode;
    sNodeType * left_type;
    unsigned int mnode;
    sNodeType * middle_type;
    sNodeType * int_type;
    sNodeType * var_type;
    int size;
    lnode = gNodes[node].mLeft;
    if (!compile(lnode, info))
    {
        return 0;
    }
    left_type = info->type;
    if (left_type == (void *) 0 || type_identify_with_class_name(left_type,
                                                                 "Null"))
    {
        compile_err_msg(info, "no type for loading element");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    if (left_type->mArray == 0)
    {
        compile_err_msg(info,
                        "Clover2 can't get an element from this type.");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    mnode = gNodes[node].mMiddle;
    if (!compile(mnode, info))
    {
        return 0;
    }
    middle_type = info->type;
    if (middle_type == (void *) 0 || type_identify_with_class_name(middle_type,
                                                                   "Null"))
    {
        compile_err_msg(info, "no type for element index");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    int_type = create_node_type_with_class_name("int");
    cast_right_type_to_left_type(int_type, &middle_type, info);
    if (!substitution_posibility_with_class_name(middle_type, "int"))
    {
        compile_err_msg(info, "Type of index should be number");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    var_type = clone_node_type(left_type);
    var_type->mArray = 0;
    append_opecode_to_code(info->code, 4007, info->no_output);
    size = get_var_size(var_type);
    append_int_value_to_code(info->code, size, info->no_output);
    info->stack_num -= 2;
    info->stack_num++;
    info->type = clone_node_type(left_type);
    info->type->mArray = 0;
    return 1;
}
unsigned int sNodeTree_create_store_array_element(unsigned int array,
                                                  unsigned int index_node,
                                                  unsigned int right_node,
                                                  sParserInfo * info)
{
    unsigned int node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeStoreArrayElement;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = array;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = index_node;
    gNodes[node].mType = (void *) 0;
    return node;
}
int compile_store_array_element(unsigned int node,
                                sCompileInfo * info)
{
    unsigned int lnode;
    sNodeType * left_type;
    unsigned int mnode;
    sNodeType * middle_type;
    sNodeType * int_type;
    unsigned int rnode;
    sNodeType * right_type;
    sNodeType * left_type2;
    lnode = gNodes[node].mLeft;
    if (!compile(lnode, info))
    {
        return 0;
    }
    left_type = info->type;
    if (left_type == (void *) 0 || type_identify_with_class_name(left_type,
                                                                 "Null"))
    {
        compile_err_msg(info, "no type for object");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    if (left_type->mArray == 0)
    {
        compile_err_msg(info,
                        "Clover2 can't get an element from this type.");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    mnode = gNodes[node].mMiddle;
    if (!compile(mnode, info))
    {
        return 0;
    }
    middle_type = info->type;
    if (middle_type == (void *) 0 || type_identify_with_class_name(middle_type,
                                                                   "Null"))
    {
        compile_err_msg(info, "no type for element index");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    int_type = create_node_type_with_class_name("int");
    cast_right_type_to_left_type(int_type, &middle_type, info);
    if (!substitution_posibility_with_class_name(middle_type, "int"))
    {
        compile_err_msg(info, "Type of index should be number");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    rnode = gNodes[node].mRight;
    if (!compile(rnode, info))
    {
        return 0;
    }
    right_type = info->type;
    if (right_type == (void *) 0)
    {
        compile_err_msg(info, "no type for right object type");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    left_type2 = clone_node_type(left_type);
    left_type2->mArray = 0;
    cast_right_type_to_left_type(left_type2, &right_type, info);
    if (!substitution_posibility(left_type2,
                                 right_type,
                                 (void *) 0,
                                 (void *) 0,
                                 (void *) 0,
                                 (void *) 0))
    {
        compile_err_msg(info,
                        "The different type between left type and right type(7). %s and %s",
                        (char *) ((&left_type2->mClass->mConst)->mConst + left_type2->mClass->mClassNameOffset),
                        (char *) ((&right_type->mClass->mConst)->mConst + right_type->mClass->mClassNameOffset));
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    append_opecode_to_code(info->code, 4008, info->no_output);
    info->stack_num -= 2;
    info->type = right_type;
    return 1;
}
unsigned int sNodeTree_create_character_value(wchar_t c,
                                              sParserInfo * info)
{
    unsigned int node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeChar;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    gNodes[node].uValue.mCharacter = c;
    return node;
}
int compile_char_value(unsigned int node, sCompileInfo * info)
{
    wchar_t c;
    c = gNodes[node].uValue.mCharacter;
    append_opecode_to_code(info->code, 39, info->no_output);
    append_int_value_to_code(info->code, (int) c, info->no_output);
    info->stack_num++;
    info->type = create_node_type_with_class_name("char");
    return 1;
}
unsigned int sNodeTree_create_string_value(char * value,
                                           unsigned int * string_expressions,
                                           int * string_expression_offsets,
                                           int num_string_expression,
                                           sParserInfo * info)
{
    unsigned int node;
    int i;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeString;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    gNodes[node].uValue.sString.mString = value;
    for (i = 0; i < num_string_expression; i++)
    {
        gNodes[node].uValue.sString.mStringExpressions[i] = string_expressions[i];
        gNodes[node].uValue.sString.mStringExpressionOffsets[i] = string_expression_offsets[i];
    }
    gNodes[node].uValue.sString.mNumStringExpression = num_string_expression;
    return node;
}
int compile_string_value(unsigned int node, sCompileInfo * info)
{
    char * str;
    int num_string_expression;
    unsigned int * string_expressions;
    int * string_expression_offsets;
    int i;
    str = gNodes[node].uValue.sString.mString;
    num_string_expression = gNodes[node].uValue.sString.mNumStringExpression;
    string_expressions = gNodes[node].uValue.sString.mStringExpressions;
    string_expression_offsets = gNodes[node].uValue.sString.mStringExpressionOffsets;
    for (i = 0; i < num_string_expression; i++)
    {
        sCLClass * klass;
        if (!compile(string_expressions[i], info))
        {
            return 0;
        }
        if (info->type == (void *) 0)
        {
            compile_err_msg(info, "String expression requires String object");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        klass = info->type->mClass;
        if (!type_identify_with_class_name(info->type, "String"))
        {
            sNodeType * result_type;
            sNodeType * result_method_generics_types;
            int method_index;
            int size;
            boxing_to_lapper_class(&info->type, info);
            klass = info->type->mClass;
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
            if (method_index == -1)
            {
                compile_err_msg(info, "String expression requires String object");
                info->err_num++;
                info->type = create_node_type_with_class_name("int");
                return 1;
            }
            append_opecode_to_code(info->code, 16, info->no_output);
            append_str_to_constant_pool_and_code(info->constant,
                                                 info->code,
                                                 info->sname,
                                                 info->no_output);
            append_int_value_to_code(info->code, info->sline, info->no_output);
            append_opecode_to_code(info->code, 3000, info->no_output);
            append_class_name_to_constant_pool_and_code(info, klass);
            append_int_value_to_code(info->code,
                                     method_index,
                                     info->no_output);
            size = get_var_size(result_type);
            append_int_value_to_code(info->code, size, info->no_output);
            info->stack_num--;
            info->stack_num++;
            info->type = result_type;
        }
    }
    append_opecode_to_code(info->code, 9000, info->no_output);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         str,
                                         info->no_output);
    append_int_value_to_code(info->code,
                             num_string_expression,
                             info->no_output);
    for (i = 0; i < num_string_expression; i++)
    {
        append_int_value_to_code(info->code,
                                 string_expression_offsets[i],
                                 info->no_output);
    }
    info->stack_num++;
    info->stack_num -= num_string_expression;
    info->type = create_node_type_with_class_name("String");
    return 1;
}
unsigned int sNodeTree_create_buffer_value(char * value,
                                           int len,
                                           unsigned int * string_expressions,
                                           int * string_expression_offsets,
                                           int num_string_expression,
                                           sParserInfo * info)
{
    unsigned int node;
    int i;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeBuffer;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    gNodes[node].uValue.sBuffer.mBuffer = value;
    gNodes[node].uValue.sBuffer.mLen = len;
    for (i = 0; i < num_string_expression; i++)
    {
        gNodes[node].uValue.sBuffer.mStringExpressions[i] = string_expressions[i];
        gNodes[node].uValue.sBuffer.mStringExpressionOffsets[i] = string_expression_offsets[i];
    }
    gNodes[node].uValue.sBuffer.mNumStringExpression = num_string_expression;
    return node;
}
int compile_buffer_value(unsigned int node, sCompileInfo * info)
{
    char * buf;
    int size;
    int num_string_expression;
    unsigned int * string_expressions;
    int * string_expression_offsets;
    int i;
    buf = gNodes[node].uValue.sBuffer.mBuffer;
    size = gNodes[node].uValue.sBuffer.mLen;
    num_string_expression = gNodes[node].uValue.sBuffer.mNumStringExpression;
    string_expressions = gNodes[node].uValue.sBuffer.mStringExpressions;
    string_expression_offsets = gNodes[node].uValue.sBuffer.mStringExpressionOffsets;
    for (i = 0; i < num_string_expression; i++)
    {
        sCLClass * klass;
        if (!compile(string_expressions[i], info))
        {
            return 0;
        }
        if (info->type == (void *) 0)
        {
            compile_err_msg(info, "String expression requires String object");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        if (info->type == (void *) 0)
        {
            compile_err_msg(info, "String expression requires String object");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        klass = info->type->mClass;
        if (!type_identify_with_class_name(info->type, "String"))
        {
            sNodeType * result_type;
            sNodeType * result_method_generics_types;
            int method_index;
            int size;
            boxing_to_lapper_class(&info->type, info);
            klass = info->type->mClass;
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
            if (method_index == -1)
            {
                compile_err_msg(info, "String expression requires String object");
                info->err_num++;
                info->type = create_node_type_with_class_name("int");
                return 1;
            }
            append_opecode_to_code(info->code, 16, info->no_output);
            append_str_to_constant_pool_and_code(info->constant,
                                                 info->code,
                                                 info->sname,
                                                 info->no_output);
            append_int_value_to_code(info->code, info->sline, info->no_output);
            append_opecode_to_code(info->code, 3000, info->no_output);
            append_class_name_to_constant_pool_and_code(info, klass);
            append_int_value_to_code(info->code,
                                     method_index,
                                     info->no_output);
            size = get_var_size(result_type);
            append_int_value_to_code(info->code, size, info->no_output);
            info->stack_num--;
            info->stack_num++;
            info->type = result_type;
        }
    }
    append_opecode_to_code(info->code, 9001, info->no_output);
    append_buffer_to_constant_pool_and_code(info->constant,
                                            info->code,
                                            buf,
                                            size,
                                            info->no_output);
    append_int_value_to_code(info->code, size, info->no_output);
    append_int_value_to_code(info->code,
                             num_string_expression,
                             info->no_output);
    for (i = 0; i < num_string_expression; i++)
    {
        append_int_value_to_code(info->code,
                                 string_expression_offsets[i],
                                 info->no_output);
    }
    info->stack_num++;
    info->stack_num -= num_string_expression;
    info->type = create_node_type_with_class_name("Buffer");
    return 1;
}
unsigned int sNodeTree_create_path_value(char * value,
                                         int len,
                                         unsigned int * string_expressions,
                                         int * string_expression_offsets,
                                         int num_string_expression,
                                         sParserInfo * info)
{
    unsigned int node;
    int i;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypePath;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    gNodes[node].uValue.sString.mString = value;
    for (i = 0; i < num_string_expression; i++)
    {
        gNodes[node].uValue.sString.mStringExpressions[i] = string_expressions[i];
        gNodes[node].uValue.sString.mStringExpressionOffsets[i] = string_expression_offsets[i];
    }
    gNodes[node].uValue.sString.mNumStringExpression = num_string_expression;
    return node;
}
int compile_path_value(unsigned int node, sCompileInfo * info)
{
    char * buf;
    int num_string_expression;
    unsigned int * string_expressions;
    int * string_expression_offsets;
    int i;
    buf = gNodes[node].uValue.sString.mString;
    num_string_expression = gNodes[node].uValue.sString.mNumStringExpression;
    string_expressions = gNodes[node].uValue.sString.mStringExpressions;
    string_expression_offsets = gNodes[node].uValue.sString.mStringExpressionOffsets;
    for (i = 0; i < num_string_expression; i++)
    {
        sCLClass * klass;
        if (!compile(string_expressions[i], info))
        {
            return 0;
        }
        if (info->type == (void *) 0)
        {
            compile_err_msg(info, "String expression requires String object");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        if (info->type == (void *) 0)
        {
            compile_err_msg(info, "String expression requires String object");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        klass = info->type->mClass;
        if (!type_identify_with_class_name(info->type, "String"))
        {
            sNodeType * result_type;
            sNodeType * result_method_generics_types;
            int method_index;
            int size;
            boxing_to_lapper_class(&info->type, info);
            klass = info->type->mClass;
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
            if (method_index == -1)
            {
                compile_err_msg(info, "String expression requires String object");
                info->err_num++;
                info->type = create_node_type_with_class_name("int");
                return 1;
            }
            append_opecode_to_code(info->code, 16, info->no_output);
            append_str_to_constant_pool_and_code(info->constant,
                                                 info->code,
                                                 info->sname,
                                                 info->no_output);
            append_int_value_to_code(info->code, info->sline, info->no_output);
            append_opecode_to_code(info->code, 3000, info->no_output);
            append_class_name_to_constant_pool_and_code(info, klass);
            append_int_value_to_code(info->code,
                                     method_index,
                                     info->no_output);
            size = get_var_size(result_type);
            append_int_value_to_code(info->code, size, info->no_output);
            info->stack_num--;
            info->stack_num++;
            info->type = result_type;
        }
    }
    append_opecode_to_code(info->code, 9002, info->no_output);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         buf,
                                         info->no_output);
    append_int_value_to_code(info->code,
                             num_string_expression,
                             info->no_output);
    for (i = 0; i < num_string_expression; i++)
    {
        append_int_value_to_code(info->code,
                                 string_expression_offsets[i],
                                 info->no_output);
    }
    info->stack_num++;
    info->stack_num -= num_string_expression;
    info->type = create_node_type_with_class_name("Path");
    return 1;
}
unsigned int sNodeTree_create_get_address(unsigned int rnode,
                                          sParserInfo * info)
{
    unsigned int node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeGetAddress;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = rnode;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    return node;
}
int compile_get_address(unsigned int node, sCompileInfo * info)
{
    unsigned int lnode;
    lnode = gNodes[node].mLeft;
    if (gNodes[lnode].mNodeType == kNodeTypeLoadVariable)
    {
        sVar * var;
        int var_index;
        var = get_variable_from_table(info->lv_table,
                                      gNodes[lnode].uValue.mVarName);
        if (var == (void *) 0)
        {
            compile_err_msg(info,
                            "undeclared variable %s",
                            gNodes[lnode].uValue.mVarName);
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        var_index = get_variable_index(info->lv_table,
                                       gNodes[lnode].uValue.mVarName);
        ;
        append_opecode_to_code(info->code, 33, info->no_output);
        append_int_value_to_code(info->code, var_index, info->no_output);
        info->stack_num++;
        info->type = create_node_type_with_class_name("pointer");
    }
    else if (gNodes[lnode].mNodeType == kNodeTypeLoadField)
    {
        unsigned int llnode;
        sCLClass * klass;
        char field_name[64];
        int field_index;
        llnode = gNodes[lnode].mLeft;
        if (!compile(llnode, info))
        {
            return 0;
        }
        if (info->type == (void *) 0 || type_identify_with_class_name(info->type,
                                                                      "Null"))
        {
            compile_err_msg(info, "no type for loading field address");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        klass = info->type->mClass;
        xstrncpy(field_name, gNodes[lnode].uValue.mVarName, 64);
        field_index = search_for_field(klass, field_name);
        if (field_index == -1)
        {
            compile_err_msg(info,
                            "There is no field(%s) in this class(%s)(4)",
                            field_name,
                            (char *) ((&klass->mConst)->mConst + klass->mClassNameOffset));
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        append_opecode_to_code(info->code, 4002, info->no_output);
        append_int_value_to_code(info->code, field_index, info->no_output);
        info->stack_num--;
        info->stack_num++;
        info->type = create_node_type_with_class_name("pointer");
    }
    else if (gNodes[lnode].mNodeType == kNodeTypeLoadClassField)
    {
        sCLClass * klass;
        char field_name[64];
        int field_index;
        sCLField * field;
        klass = gNodes[lnode].uValue.sClassField.mClass;
        xstrncpy(field_name,
                 gNodes[lnode].uValue.sClassField.mVarName,
                 64);
        field_index = search_for_class_field(klass, field_name);
        if (field_index == -1)
        {
            compile_err_msg(info,
                            "There is no field(%s) in this class(%s)(5)",
                            field_name,
                            (char *) ((&klass->mConst)->mConst + klass->mClassNameOffset));
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        field = klass->mClassFields + field_index;
        append_opecode_to_code(info->code, 4005, info->no_output);
        append_class_name_to_constant_pool_and_code(info, klass);
        append_int_value_to_code(info->code, field_index, info->no_output);
        info->stack_num++;
        info->type = create_node_type_with_class_name("pointer");
    }
    else
    {
        compile_err_msg(info, "Require variable name for getting address");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
    }
    return 1;
}
unsigned int sNodeTree_create_array_value(int num_elements,
                                          unsigned int array_elements[],
                                          sParserInfo * info)
{
    unsigned int node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeArrayValue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    memcpy(gNodes[node].uValue.sArrayValue.mArrayElements,
           array_elements,
           sizeof(unsigned int) * 256);
    gNodes[node].uValue.sArrayValue.mNumArrayElements = num_elements;
    return node;
}
int compile_array_value(unsigned int node, sCompileInfo * info)
{
    unsigned int * elements;
    int num_elements;
    unsigned int first_element_node;
    sNodeType * element_type;
    int i;
    elements = gNodes[node].uValue.sArrayValue.mArrayElements;
    num_elements = gNodes[node].uValue.sArrayValue.mNumArrayElements;
    if (num_elements == 0)
    {
        compile_err_msg(info, "require element in array value");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    first_element_node = elements[0];
    if (!compile(first_element_node, info))
    {
        return 0;
    }
    element_type = info->type;
    for (i = 1; i < num_elements; i++)
    {
        unsigned int element_node;
        element_node = elements[i];
        if (!compile(element_node, info))
        {
            return 0;
        }
        if (!type_identify(element_type, info->type))
        {
            compile_err_msg(info,
                            "Invalid element type. Left type is %s. Right type is %s",
                            (char *) ((&element_type->mClass->mConst)->mConst + element_type->mClass->mClassNameOffset),
                            (char *) ((&info->type->mClass->mConst)->mConst + info->type->mClass->mClassNameOffset));
            info->err_num++;
        }
    }
    append_opecode_to_code(info->code, 9003, info->no_output);
    append_int_value_to_code(info->code,
                             num_elements,
                             info->no_output);
    append_class_name_to_constant_pool_and_code(info,
                                                element_type->mClass);
    info->stack_num -= num_elements;
    info->stack_num++;
    info->type = element_type;
    info->type->mArray = 1;
    return 1;
}
unsigned int sNodeTree_create_carray_value(int num_elements,
                                           unsigned int array_elements[],
                                           sParserInfo * info)
{
    unsigned int node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeCArrayValue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    memcpy(gNodes[node].uValue.sArrayValue.mArrayElements,
           array_elements,
           sizeof(unsigned int) * 256);
    gNodes[node].uValue.sArrayValue.mNumArrayElements = num_elements;
    return node;
}
static int compile_carray_value(unsigned int node,
                                sCompileInfo * info)
{
    unsigned int * elements;
    int num_elements;
    unsigned int first_element_node;
    sNodeType * element_type;
    int generics_type_is_object;
    int i;
    sNodeType * array_type;
    elements = gNodes[node].uValue.sArrayValue.mArrayElements;
    num_elements = gNodes[node].uValue.sArrayValue.mNumArrayElements;
    if (num_elements == 0)
    {
        compile_err_msg(info, "require element in array value");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    first_element_node = elements[0];
    if (!compile(first_element_node, info))
    {
        return 0;
    }
    boxing_to_lapper_class(&info->type, info);
    element_type = info->type;
    generics_type_is_object = 0;
    for (i = 1; i < num_elements; i++)
    {
        unsigned int element_node;
        element_node = elements[i];
        if (!compile(element_node, info))
        {
            return 0;
        }
        boxing_to_lapper_class(&info->type, info);
        if (!type_identify(element_type, info->type))
        {
            generics_type_is_object = 1;
        }
    }
    array_type = create_node_type_with_class_name("Array");
    array_type->mNumGenericsTypes = 1;
    if (generics_type_is_object)
    {
        array_type->mGenericsTypes[0] = create_node_type_with_class_name("Object");
    }
    else
    {
        array_type->mGenericsTypes[0] = element_type;
    }
    append_opecode_to_code(info->code, 9004, info->no_output);
    append_int_value_to_code(info->code,
                             num_elements,
                             info->no_output);
    append_class_name_to_constant_pool_and_code(info,
                                                element_type->mClass);
    append_type_name_to_constant_pool_and_code(info, array_type);
    info->stack_num -= num_elements;
    info->stack_num++;
    info->type = array_type;
    return 1;
}
unsigned int sNodeTree_create_equalable_carray_value(int num_elements,
                                                     unsigned int array_elements[],
                                                     sParserInfo * info)
{
    unsigned int node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeEqualableCArrayValue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    memcpy(gNodes[node].uValue.sArrayValue.mArrayElements,
           array_elements,
           sizeof(unsigned int) * 256);
    gNodes[node].uValue.sArrayValue.mNumArrayElements = num_elements;
    return node;
}
static int compile_equalable_carray_value(unsigned int node,
                                          sCompileInfo * info)
{
    unsigned int * elements;
    int num_elements;
    unsigned int first_element_node;
    sNodeType * element_type;
    int generics_type_is_object;
    int i;
    sCLClass * iequalable;
    sNodeType * array_type;
    elements = gNodes[node].uValue.sArrayValue.mArrayElements;
    num_elements = gNodes[node].uValue.sArrayValue.mNumArrayElements;
    if (num_elements == 0)
    {
        compile_err_msg(info, "require element in array value");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    first_element_node = elements[0];
    if (!compile(first_element_node, info))
    {
        return 0;
    }
    boxing_to_lapper_class(&info->type, info);
    element_type = info->type;
    generics_type_is_object = 0;
    for (i = 1; i < num_elements; i++)
    {
        unsigned int element_node;
        element_node = elements[i];
        if (!compile(element_node, info))
        {
            return 0;
        }
        boxing_to_lapper_class(&info->type, info);
        if (!type_identify(element_type, info->type))
        {
            generics_type_is_object = 1;
        }
    }
    iequalable = get_class("IEqualable");
    if (!check_implemented_methods_for_interface(iequalable,
                                                 element_type->mClass))
    {
        compile_err_msg(info,
                        "Require IEqualable implemented for array element type(%s).",
                        (char *) ((&element_type->mClass->mConst)->mConst + element_type->mClass->mClassNameOffset));
        info->err_num++;
    }
    array_type = create_node_type_with_class_name("EqualableArray");
    array_type->mNumGenericsTypes = 1;
    if (generics_type_is_object)
    {
        array_type->mGenericsTypes[0] = create_node_type_with_class_name("Object");
    }
    else
    {
        array_type->mGenericsTypes[0] = element_type;
    }
    append_opecode_to_code(info->code, 9006, info->no_output);
    append_int_value_to_code(info->code,
                             num_elements,
                             info->no_output);
    append_class_name_to_constant_pool_and_code(info,
                                                element_type->mClass);
    append_type_name_to_constant_pool_and_code(info, array_type);
    info->stack_num -= num_elements;
    info->stack_num++;
    info->type = array_type;
    return 1;
}
unsigned int sNodeTree_create_sortable_carray_value(int num_elements,
                                                    unsigned int array_elements[],
                                                    sParserInfo * info)
{
    unsigned int node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeSortableCArrayValue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    memcpy(gNodes[node].uValue.sArrayValue.mArrayElements,
           array_elements,
           sizeof(unsigned int) * 256);
    gNodes[node].uValue.sArrayValue.mNumArrayElements = num_elements;
    return node;
}
static int compile_sortable_carray_value(unsigned int node,
                                         sCompileInfo * info)
{
    unsigned int * elements;
    int num_elements;
    unsigned int first_element_node;
    sNodeType * element_type;
    int generics_type_is_object;
    int i;
    sCLClass * isortable;
    sNodeType * array_type;
    elements = gNodes[node].uValue.sArrayValue.mArrayElements;
    num_elements = gNodes[node].uValue.sArrayValue.mNumArrayElements;
    if (num_elements == 0)
    {
        compile_err_msg(info, "require element in array value");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    first_element_node = elements[0];
    if (!compile(first_element_node, info))
    {
        return 0;
    }
    boxing_to_lapper_class(&info->type, info);
    element_type = info->type;
    generics_type_is_object = 0;
    for (i = 1; i < num_elements; i++)
    {
        unsigned int element_node;
        element_node = elements[i];
        if (!compile(element_node, info))
        {
            return 0;
        }
        boxing_to_lapper_class(&info->type, info);
        if (!type_identify(element_type, info->type))
        {
            generics_type_is_object = 1;
        }
    }
    isortable = get_class("ISortable");
    if (!check_implemented_methods_for_interface(isortable,
                                                 element_type->mClass))
    {
        compile_err_msg(info,
                        "Require IEqualable implemented for array element type(%s).",
                        (char *) ((&element_type->mClass->mConst)->mConst + element_type->mClass->mClassNameOffset));
        info->err_num++;
    }
    array_type = create_node_type_with_class_name("SortableArray");
    array_type->mNumGenericsTypes = 1;
    if (generics_type_is_object)
    {
        array_type->mGenericsTypes[0] = create_node_type_with_class_name("Object");
    }
    else
    {
        array_type->mGenericsTypes[0] = element_type;
    }
    append_opecode_to_code(info->code, 9005, info->no_output);
    append_int_value_to_code(info->code,
                             num_elements,
                             info->no_output);
    append_class_name_to_constant_pool_and_code(info,
                                                element_type->mClass);
    append_type_name_to_constant_pool_and_code(info, array_type);
    info->stack_num -= num_elements;
    info->stack_num++;
    info->type = array_type;
    return 1;
}
unsigned int sNodeTree_create_hash_value(int num_elements,
                                         unsigned int hash_keys[],
                                         unsigned int hash_items[],
                                         sParserInfo * info)
{
    unsigned int node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeHashValue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    memcpy(gNodes[node].uValue.sHashValue.mHashKeys,
           hash_keys,
           sizeof(unsigned int) * 256);
    memcpy(gNodes[node].uValue.sHashValue.mHashItems,
           hash_items,
           sizeof(unsigned int) * 256);
    gNodes[node].uValue.sHashValue.mNumHashElements = num_elements;
    return node;
}
unsigned int sNodeTree_create_list_value(int num_elements,
                                         unsigned int list_elements[],
                                         sParserInfo * info)
{
    unsigned int node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeListValue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    memcpy(gNodes[node].uValue.sListValue.mListElements,
           list_elements,
           sizeof(unsigned int) * 256);
    gNodes[node].uValue.sListValue.mNumListElements = num_elements;
    return node;
}
int compile_list_value(unsigned int node, sCompileInfo * info)
{
    unsigned int * elements;
    int num_elements;
    unsigned int first_element_node;
    sNodeType * element_type;
    int i;
    sNodeType * list_type;
    elements = gNodes[node].uValue.sListValue.mListElements;
    num_elements = gNodes[node].uValue.sListValue.mNumListElements;
    if (num_elements == 0)
    {
        compile_err_msg(info, "require element in list value");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    first_element_node = elements[0];
    if (!compile(first_element_node, info))
    {
        return 0;
    }
    boxing_to_lapper_class(&info->type, info);
    element_type = info->type;
    for (i = 1; i < num_elements; i++)
    {
        unsigned int element_node;
        element_node = elements[i];
        if (!compile(element_node, info))
        {
            return 0;
        }
        boxing_to_lapper_class(&info->type, info);
        if (!type_identify(element_type, info->type))
        {
            compile_err_msg(info,
                            "Invalid element type. Left type is %s. Right type is %s",
                            (char *) ((&element_type->mClass->mConst)->mConst + element_type->mClass->mClassNameOffset),
                            (char *) ((&info->type->mClass->mConst)->mConst + info->type->mClass->mClassNameOffset));
            info->err_num++;
        }
    }
    list_type = create_node_type_with_class_name("List");
    list_type->mNumGenericsTypes = 1;
    list_type->mGenericsTypes[0] = element_type;
    append_opecode_to_code(info->code, 9007, info->no_output);
    append_int_value_to_code(info->code,
                             num_elements,
                             info->no_output);
    append_class_name_to_constant_pool_and_code(info,
                                                element_type->mClass);
    append_type_name_to_constant_pool_and_code(info, list_type);
    info->stack_num -= num_elements;
    info->stack_num++;
    info->type = list_type;
    return 1;
}
unsigned int sNodeTree_create_sortable_list_value(int num_elements,
                                                  unsigned int list_elements[],
                                                  sParserInfo * info)
{
    unsigned int node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeSortableListValue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    memcpy(gNodes[node].uValue.sListValue.mListElements,
           list_elements,
           sizeof(unsigned int) * 256);
    gNodes[node].uValue.sListValue.mNumListElements = num_elements;
    return node;
}
int compile_sortable_list_value(unsigned int node,
                                sCompileInfo * info)
{
    unsigned int * elements;
    int num_elements;
    unsigned int first_element_node;
    sNodeType * element_type;
    int i;
    sCLClass * isortable;
    sNodeType * list_type;
    elements = gNodes[node].uValue.sListValue.mListElements;
    num_elements = gNodes[node].uValue.sListValue.mNumListElements;
    if (num_elements == 0)
    {
        compile_err_msg(info, "require element in list value");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    first_element_node = elements[0];
    if (!compile(first_element_node, info))
    {
        return 0;
    }
    boxing_to_lapper_class(&info->type, info);
    element_type = info->type;
    for (i = 1; i < num_elements; i++)
    {
        unsigned int element_node;
        element_node = elements[i];
        if (!compile(element_node, info))
        {
            return 0;
        }
        boxing_to_lapper_class(&info->type, info);
        if (!type_identify(element_type, info->type))
        {
            compile_err_msg(info,
                            "Invalid element type. Left type is %s. Right type is %s",
                            (char *) ((&element_type->mClass->mConst)->mConst + element_type->mClass->mClassNameOffset),
                            (char *) ((&info->type->mClass->mConst)->mConst + info->type->mClass->mClassNameOffset));
            info->err_num++;
        }
    }
    isortable = get_class("ISortable");
    if (!check_implemented_methods_for_interface(isortable,
                                                 element_type->mClass))
    {
        compile_err_msg(info,
                        "Require ISortable implemented for list element type(%s).",
                        (char *) ((&element_type->mClass->mConst)->mConst + element_type->mClass->mClassNameOffset));
        info->err_num++;
    }
    list_type = create_node_type_with_class_name("SortableList");
    list_type->mNumGenericsTypes = 1;
    list_type->mGenericsTypes[0] = element_type;
    append_opecode_to_code(info->code, 9008, info->no_output);
    append_int_value_to_code(info->code,
                             num_elements,
                             info->no_output);
    append_class_name_to_constant_pool_and_code(info,
                                                element_type->mClass);
    append_type_name_to_constant_pool_and_code(info, list_type);
    info->stack_num -= num_elements;
    info->stack_num++;
    info->type = list_type;
    return 1;
}
unsigned int sNodeTree_create_equalable_list_value(int num_elements,
                                                   unsigned int list_elements[],
                                                   sParserInfo * info)
{
    unsigned int node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeEqualableListValue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    memcpy(gNodes[node].uValue.sListValue.mListElements,
           list_elements,
           sizeof(unsigned int) * 256);
    gNodes[node].uValue.sListValue.mNumListElements = num_elements;
    return node;
}
int compile_equalable_list_value(unsigned int node,
                                 sCompileInfo * info)
{
    unsigned int * elements;
    int num_elements;
    unsigned int first_element_node;
    sNodeType * element_type;
    int i;
    sCLClass * iequalable;
    sNodeType * list_type;
    elements = gNodes[node].uValue.sListValue.mListElements;
    num_elements = gNodes[node].uValue.sListValue.mNumListElements;
    if (num_elements == 0)
    {
        compile_err_msg(info, "require element in list value");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    first_element_node = elements[0];
    if (!compile(first_element_node, info))
    {
        return 0;
    }
    boxing_to_lapper_class(&info->type, info);
    element_type = info->type;
    for (i = 1; i < num_elements; i++)
    {
        unsigned int element_node;
        element_node = elements[i];
        if (!compile(element_node, info))
        {
            return 0;
        }
        boxing_to_lapper_class(&info->type, info);
        if (!type_identify(element_type, info->type))
        {
            compile_err_msg(info,
                            "Invalid element type. Left type is %s. Right type is %s",
                            (char *) ((&element_type->mClass->mConst)->mConst + element_type->mClass->mClassNameOffset),
                            (char *) ((&info->type->mClass->mConst)->mConst + info->type->mClass->mClassNameOffset));
            info->err_num++;
        }
    }
    iequalable = get_class("IEqualable");
    if (!check_implemented_methods_for_interface(iequalable,
                                                 element_type->mClass))
    {
        compile_err_msg(info,
                        "Require IEqualable implemented for list element type(%s).",
                        (char *) ((&element_type->mClass->mConst)->mConst + element_type->mClass->mClassNameOffset));
        info->err_num++;
    }
    list_type = create_node_type_with_class_name("EqualableList");
    list_type->mNumGenericsTypes = 1;
    list_type->mGenericsTypes[0] = element_type;
    append_opecode_to_code(info->code, 9009, info->no_output);
    append_int_value_to_code(info->code,
                             num_elements,
                             info->no_output);
    append_class_name_to_constant_pool_and_code(info,
                                                element_type->mClass);
    append_type_name_to_constant_pool_and_code(info, list_type);
    info->stack_num -= num_elements;
    info->stack_num++;
    info->type = list_type;
    return 1;
}
unsigned int sNodeTree_create_tuple_value(int num_elements,
                                          unsigned int tuple_elements[],
                                          sParserInfo * info)
{
    unsigned int node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeTupleValue;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    memcpy(gNodes[node].uValue.sTupleValue.mTupleElements,
           tuple_elements,
           sizeof(unsigned int) * 256);
    gNodes[node].uValue.sTupleValue.mNumTupleElements = num_elements;
    return node;
}
static int compile_tuple_value(unsigned int node,
                               sCompileInfo * info)
{
    unsigned int * elements;
    int num_elements;
    sNodeType * element_types[256];
    int i;
    char class_name[64 + 1];
    sNodeType * tuple_type;
    elements = gNodes[node].uValue.sTupleValue.mTupleElements;
    num_elements = gNodes[node].uValue.sTupleValue.mNumTupleElements;
    if (num_elements == 0)
    {
        compile_err_msg(info, "require element in tuple value");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    for (i = 0; i < num_elements; i++)
    {
        unsigned int element_node;
        element_node = elements[i];
        if (!compile(element_node, info))
        {
            return 0;
        }
        boxing_to_lapper_class(&info->type, info);
        element_types[i] = info->type;
    }
    snprintf(class_name, 64, "Tuple%d", num_elements);
    tuple_type = create_node_type_with_class_name(class_name);
    tuple_type->mNumGenericsTypes = num_elements;
    for (i = 0; i < num_elements; i++)
    {
        tuple_type->mGenericsTypes[i] = element_types[i];
    }
    append_opecode_to_code(info->code, 9010, info->no_output);
    append_int_value_to_code(info->code,
                             num_elements,
                             info->no_output);
    append_type_name_to_constant_pool_and_code(info, tuple_type);
    info->stack_num -= num_elements;
    info->stack_num++;
    info->type = tuple_type;
    return 1;
}
int compile_hash_value(unsigned int node, sCompileInfo * info)
{
    unsigned int * keys;
    unsigned int * items;
    int num_elements;
    unsigned int first_key_node;
    sNodeType * key_type;
    unsigned int first_item_node;
    sNodeType * item_type;
    int i;
    sNodeType * hash_type;
    keys = gNodes[node].uValue.sHashValue.mHashKeys;
    items = gNodes[node].uValue.sHashValue.mHashItems;
    num_elements = gNodes[node].uValue.sHashValue.mNumHashElements;
    if (num_elements == 0)
    {
        compile_err_msg(info, "require element in hash value");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    first_key_node = keys[0];
    if (!compile(first_key_node, info))
    {
        return 0;
    }
    key_type = info->type;
    boxing_to_lapper_class(&key_type, info);
    first_item_node = items[0];
    if (!compile(first_item_node, info))
    {
        return 0;
    }
    item_type = info->type;
    boxing_to_lapper_class(&item_type, info);
    for (i = 1; i < num_elements; i++)
    {
        unsigned int key;
        unsigned int item;
        key = keys[i];
        if (!compile(key, info))
        {
            return 0;
        }
        boxing_to_lapper_class(&info->type, info);
        if (!type_identify(key_type, info->type))
        {
            compile_err_msg(info,
                            "Invalid key type. Left type is %s. Right type is %s",
                            (char *) ((&key_type->mClass->mConst)->mConst + key_type->mClass->mClassNameOffset),
                            (char *) ((&info->type->mClass->mConst)->mConst + info->type->mClass->mClassNameOffset));
            info->err_num++;
        }
        item = items[i];
        if (!compile(item, info))
        {
            return 0;
        }
        boxing_to_lapper_class(&info->type, info);
        if (!type_identify(item_type, info->type))
        {
            compile_err_msg(info,
                            "Invalid item type. Left type is %s. Right type is %s",
                            (char *) ((&item_type->mClass->mConst)->mConst + item_type->mClass->mClassNameOffset),
                            (char *) ((&info->type->mClass->mConst)->mConst + info->type->mClass->mClassNameOffset));
            info->err_num++;
        }
    }
    hash_type = create_node_type_with_class_name("Hash");
    hash_type->mNumGenericsTypes = 2;
    hash_type->mGenericsTypes[0] = key_type;
    hash_type->mGenericsTypes[1] = item_type;
    append_opecode_to_code(info->code, 9011, info->no_output);
    append_int_value_to_code(info->code,
                             num_elements,
                             info->no_output);
    append_class_name_to_constant_pool_and_code(info,
                                                key_type->mClass);
    append_class_name_to_constant_pool_and_code(info,
                                                item_type->mClass);
    append_type_name_to_constant_pool_and_code(info, hash_type);
    info->stack_num -= num_elements * 2;
    info->stack_num++;
    info->type = hash_type;
    return 1;
}
unsigned int sNodeTree_create_block_object(sParserParam * params,
                                           int num_params,
                                           sNodeType * result_type,
                                           sNodeBlock * node_block,
                                           int lambda,
                                           sParserInfo * info,
                                           int omit_result_type,
                                           int omit_params,
                                           sVarTable * old_table)
{
    unsigned int node;
    int i;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeBlockObject;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    for (i = 0; i < num_params; i++)
    {
        gNodes[node].uValue.sBlockObject.mParams[i] = params[i];
    }
    gNodes[node].uValue.sBlockObject.mNumParams = num_params;
    gNodes[node].uValue.sBlockObject.mResultType = result_type;
    gNodes[node].uValue.sBlockObject.mBlockObjectCode = node_block;
    gNodes[node].uValue.sBlockObject.mLambda = lambda;
    gNodes[node].uValue.sBlockObject.mOmitResultType = omit_result_type;
    gNodes[node].uValue.sBlockObject.mOmitParams = omit_params;
    gNodes[node].uValue.sBlockObject.mOldTable = old_table;
    return node;
}
int compile_block_object(unsigned int node, sCompileInfo * info)
{
    int num_params;
    sParserParam * params[32];
    int i;
    sNodeType * result_type;
    sNodeBlock * node_block;
    int omit_result_type;
    int lambda;
    sVarTable * old_table;
    sByteCode codes;
    sConst constant;
    sByteCode * codes_before;
    sConst * constant_before;
    int in_block_before;
    sNodeType * block_result_type_before;
    sNodeType * return_type_before;
    int omit_block_result_type_before;
    sNodeType * return_type;
    int offset;
    int offset2;
    int var_num;
    num_params = gNodes[node].uValue.sBlockObject.mNumParams;
    for (i = 0; i < num_params; i++)
    {
        params[i] = gNodes[node].uValue.sBlockObject.mParams + i;
    }
    result_type = gNodes[node].uValue.sBlockObject.mResultType;
    node_block = gNodes[node].uValue.sBlockObject.mBlockObjectCode;
    omit_result_type = gNodes[node].uValue.sBlockObject.mOmitResultType;
    lambda = gNodes[node].uValue.sBlockObject.mLambda;
    old_table = gNodes[node].uValue.sBlockObject.mOldTable;
    sByteCode_init(&codes);
    sConst_init(&constant);
    codes_before = info->code;
    constant_before = info->constant;
    info->code = &codes;
    info->constant = &constant;
    in_block_before = info->in_block;
    info->in_block = 1;
    block_result_type_before = info->block_result_type;
    info->block_result_type = result_type;
    return_type_before = info->return_type;
    info->return_type = (void *) 0;
    omit_block_result_type_before = info->omit_block_result_type;
    info->omit_block_result_type = omit_result_type;
    if (!compile_block(node_block, info))
    {
        sByteCode_free(&codes);
        sConst_free(&constant);
        info->code = codes_before;
        info->constant = constant_before;
        info->block_result_type = block_result_type_before;
        info->in_block = in_block_before;
        info->omit_block_result_type = omit_block_result_type_before;
        info->return_type = return_type_before;
        return 0;
    }
    return_type = info->return_type;
    info->return_type2 = info->return_type;
    info->code = codes_before;
    info->constant = constant_before;
    info->block_result_type = block_result_type_before;
    info->in_block = in_block_before;
    info->omit_block_result_type = omit_block_result_type_before;
    info->return_type = return_type_before;
    append_opecode_to_code(info->code, 9012, info->no_output);
    offset = sConst_append(info->constant,
                           codes.mCodes,
                           codes.mLen,
                           info->no_output);
    append_int_value_to_code(info->code, offset, info->no_output);
    append_int_value_to_code(info->code, codes.mLen, info->no_output);
    offset2 = sConst_append(info->constant,
                            constant.mConst,
                            constant.mLen,
                            info->no_output);
    append_int_value_to_code(info->code, offset2, info->no_output);
    append_int_value_to_code(info->code,
                             constant.mLen,
                             info->no_output);
    if (node_block->mLVTable)
    {
        var_num = get_var_num(node_block->mLVTable);
    }
    else
    {
        var_num = 0;
    }
    append_int_value_to_code(info->code, var_num, info->no_output);
    if (lambda)
    {
        int parent_var_num;
        parent_var_num = 0;
        append_int_value_to_code(info->code,
                                 parent_var_num,
                                 info->no_output);
        append_int_value_to_code(info->code, 1, info->no_output);
    }
    else
    {
        int parent_var_num;
        parent_var_num = get_parent_var_num_of_sum(node_block->mLVTable);
        append_int_value_to_code(info->code,
                                 parent_var_num,
                                 info->no_output);
        append_int_value_to_code(info->code, 0, info->no_output);
    }
    info->stack_num++;
    if (!node_block->mUnClosedBlock)
    {
        sNodeBlockType * node_block_type;
        info->type = create_node_type_with_class_name("lambda");
        node_block_type = alloc_node_block_type();
        node_block_type->mNumParams = num_params;
        if (omit_result_type)
        {
            if (return_type == (void *) 0)
            {
                node_block_type->mResultType = create_node_type_with_class_name("Null");
            }
            else
            {
                node_block_type->mResultType = return_type;
            }
        }
        else
        {
            node_block_type->mResultType = result_type;
        }
        for (i = 0; i < num_params; i++)
        {
            node_block_type->mParams[i] = params[i]->mType;
        }
        node_block_type->mLambda = lambda;
        info->type->mBlockType = node_block_type;
    }
    sByteCode_free(&codes);
    sConst_free(&constant);
    info->pinfo->exist_block_object_err = node_block->mUnClosedBlock;
    return 1;
}
unsigned int sNodeTree_create_function(char * fun_name,
                                       sParserParam * params,
                                       int num_params,
                                       sNodeType * result_type,
                                       sNodeBlock * node_block,
                                       int lambda,
                                       sParserInfo * info)
{
    unsigned int node;
    int i;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeFunction;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    xstrncpy(gNodes[node].uValue.sFunction.mName, fun_name, 64);
    for (i = 0; i < num_params; i++)
    {
        gNodes[node].uValue.sFunction.mParams[i] = params[i];
    }
    gNodes[node].uValue.sFunction.mNumParams = num_params;
    gNodes[node].uValue.sFunction.mResultType = result_type;
    gNodes[node].uValue.sFunction.mBlockObjectCode = node_block;
    gNodes[node].uValue.sFunction.mLambda = lambda;
    return node;
}
int compile_function(unsigned int node, sCompileInfo * info)
{
    int num_params;
    sParserParam * params[32];
    int i;
    sNodeType * result_type;
    sNodeBlock * node_block;
    int lambda;
    sNodeType * lambda_type;
    sNodeBlockType * node_block_type;
    sVar * var;
    sNodeType * right_type;
    sByteCode codes;
    sConst constant;
    sByteCode * codes_before;
    sConst * constant_before;
    int in_block_before;
    sNodeType * block_result_type_before;
    sNodeType * expresson_type_in_block;
    int offset;
    int offset2;
    int var_num;
    sNodeType * left_type;
    sNodeType * left_type2;
    int var_index;
    num_params = gNodes[node].uValue.sFunction.mNumParams;
    for (i = 0; i < num_params; i++)
    {
        params[i] = gNodes[node].uValue.sFunction.mParams + i;
    }
    result_type = gNodes[node].uValue.sFunction.mResultType;
    node_block = gNodes[node].uValue.sFunction.mBlockObjectCode;
    lambda = gNodes[node].uValue.sFunction.mLambda;
    lambda_type = create_node_type_with_class_name("lambda");
    node_block_type = alloc_node_block_type();
    node_block_type->mNumParams = num_params;
    node_block_type->mResultType = result_type;
    for (i = 0; i < num_params; i++)
    {
        node_block_type->mParams[i] = params[i]->mType;
    }
    node_block_type->mLambda = lambda;
    lambda_type->mBlockType = node_block_type;
    var = get_variable_from_table(info->lv_table,
                                  gNodes[node].uValue.sFunction.mName);
    if (var == (void *) 0)
    {
        compile_err_msg(info,
                        "undeclared variable %s",
                        gNodes[node].uValue.sFunction.mName);
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    right_type = lambda_type;
    if (gNodes[node].mType == (void *) 0)
    {
        gNodes[node].mType = right_type;
    }
    if (var->mType == (void *) 0)
    {
        var->mType = right_type;
    }
    sByteCode_init(&codes);
    sConst_init(&constant);
    codes_before = info->code;
    constant_before = info->constant;
    info->code = &codes;
    info->constant = &constant;
    in_block_before = info->in_block;
    info->in_block = 1;
    block_result_type_before = info->block_result_type;
    info->block_result_type = result_type;
    if (!compile_block(node_block, info))
    {
        sByteCode_free(&codes);
        sConst_free(&constant);
        info->code = codes_before;
        info->constant = constant_before;
        info->block_result_type = block_result_type_before;
        info->in_block = in_block_before;
        return 0;
    }
    info->block_result_type = block_result_type_before;
    info->in_block = in_block_before;
    expresson_type_in_block = info->type;
    info->code = codes_before;
    info->constant = constant_before;
    info->block_result_type = block_result_type_before;
    append_opecode_to_code(info->code, 9012, info->no_output);
    offset = sConst_append(info->constant,
                           codes.mCodes,
                           codes.mLen,
                           info->no_output);
    append_int_value_to_code(info->code, offset, info->no_output);
    append_int_value_to_code(info->code, codes.mLen, info->no_output);
    offset2 = sConst_append(info->constant,
                            constant.mConst,
                            constant.mLen,
                            info->no_output);
    append_int_value_to_code(info->code, offset2, info->no_output);
    append_int_value_to_code(info->code,
                             constant.mLen,
                             info->no_output);
    if (node_block->mLVTable)
    {
        var_num = get_var_num(node_block->mLVTable);
    }
    else
    {
        var_num = 0;
    }
    append_int_value_to_code(info->code, var_num, info->no_output);
    if (lambda)
    {
        int parent_var_num;
        parent_var_num = 0;
        append_int_value_to_code(info->code,
                                 parent_var_num,
                                 info->no_output);
        append_int_value_to_code(info->code, 1, info->no_output);
    }
    else
    {
        int parent_var_num;
        parent_var_num = get_parent_var_num_of_sum(node_block->mLVTable);
        append_int_value_to_code(info->code,
                                 parent_var_num,
                                 info->no_output);
        append_int_value_to_code(info->code, 0, info->no_output);
    }
    info->stack_num++;
    sByteCode_free(&codes);
    sConst_free(&constant);
    left_type = var->mType;
    if (gNodes[node].mType->mClass == (void *) 0 || left_type == (void *) 0 || right_type == (void *) 0 || left_type->mClass == (void *) 0 || right_type->mClass == (void *) 0)
    {
        compile_err_msg(info, "invalid type(2)");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    solve_generics_for_variable(left_type, &left_type2, info->pinfo);
    cast_right_type_to_left_type(left_type2, &right_type, info);
    if (!substitution_posibility(left_type2,
                                 right_type,
                                 (void *) 0,
                                 (void *) 0,
                                 (void *) 0,
                                 (void *) 0))
    {
        compile_err_msg(info,
                        "The different type between left type and right type(1). Left type is %s. Right type is %s.",
                        (char *) ((&left_type2->mClass->mConst)->mConst + left_type2->mClass->mClassNameOffset),
                        (char *) ((&right_type->mClass->mConst)->mConst + right_type->mClass->mClassNameOffset));
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    var_index = get_variable_index(info->lv_table,
                                   gNodes[node].uValue.sFunction.mName);
    ;
    append_opecode_to_code(info->code, 31, info->no_output);
    append_int_value_to_code(info->code, var_index, info->no_output);
    if (info->pinfo->err_num == 0)
    {
        info->type = left_type2;
    }
    else
    {
        info->type = expresson_type_in_block;
    }
    return 1;
}
unsigned int sNodeTree_create_normal_block(sNodeBlock * node_block,
                                           sParserInfo * info)
{
    unsigned int node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeNormalBlock;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    gNodes[node].uValue.mBlock = node_block;
    return node;
}
static int compile_normal_block(unsigned int node,
                                sCompileInfo * info)
{
    sNodeBlock * node_block;
    node_block = gNodes[node].uValue.mBlock;
    if (!compile_block_with_result(node_block, info))
    {
        return 0;
    }
    return 1;
}
unsigned int sNodeTree_create_block_call(unsigned int block,
                                         int num_params,
                                         unsigned int params[],
                                         sParserInfo * info)
{
    unsigned int node;
    int i;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeBlockCall;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = block;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    gNodes[node].uValue.sBlockCall.mNumParams = num_params;
    for (i = 0; i < gNodes[node].uValue.sBlockCall.mNumParams; i++)
    {
        gNodes[node].uValue.sBlockCall.mParams[i] = params[i];
    }
    return node;
}
int compile_block_call(unsigned int node, sCompileInfo * info)
{
    unsigned int lnode;
    sNodeType * var_type;
    sNodeType * param_types[32];
    int num_params;
    int i;
    sNodeBlockType * block_type;
    sNodeType * result_type2;
    int size;
    lnode = gNodes[node].mLeft;
    if (!compile(lnode, info))
    {
        return 0;
    }
    if (info->type == (void *) 0 || type_identify_with_class_name(info->type,
                                                                  "Null"))
    {
        compile_err_msg(info, "no type for block call");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    var_type = info->type;
    if (var_type == (void *) 0 || !type_identify_with_class_name(var_type,
                                                                 "lambda"))
    {
        compile_err_msg(info,
                        "No block type, clover2 can call block object only");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    num_params = gNodes[node].uValue.sBlockCall.mNumParams;
    for (i = 0; i < num_params; i++)
    {
        unsigned int node2;
        node2 = gNodes[node].uValue.sBlockCall.mParams[i];
        if (!compile(node2, info))
        {
            return 0;
        }
        param_types[i] = info->type;
    }
    if (num_params != var_type->mBlockType->mNumParams)
    {
        compile_err_msg(info, "Type error for block call");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    for (i = 0; i < num_params; i++)
    {
        sNodeType * left_type;
        sNodeType * right_type;
        sCLClass * klass;
        left_type = var_type->mBlockType->mParams[i];
        right_type = param_types[i];
        klass = info->pinfo->klass;
        if (klass)
        {
            sNodeType * generics_types;
            sNodeType * method_generics_types;
            generics_types = create_generics_types_from_generics_params(klass);
            if (info->pinfo->klass)
            {
                method_generics_types = get_methocs_generics_type(info->pinfo);
            }
            else
            {
                method_generics_types = (void *) 0;
            }
            if (!substitution_posibility(left_type,
                                         right_type,
                                         generics_types,
                                         (void *) 0,
                                         method_generics_types,
                                         method_generics_types))
            {
                compile_err_msg(info, "Type error for block call");
                info->err_num++;
            }
        }
        else
        {
            if (!substitution_posibility(left_type,
                                         right_type,
                                         (void *) 0,
                                         (void *) 0,
                                         (void *) 0,
                                         (void *) 0))
            {
                compile_err_msg(info, "Type error for block call");
                info->err_num++;
            }
        }
    }
    block_type = var_type->mBlockType;
    append_opecode_to_code(info->code, 3003, info->no_output);
    append_int_value_to_code(info->code, num_params, info->no_output);
    result_type2 = block_type->mResultType;
    size = get_var_size(result_type2);
    append_int_value_to_code(info->code, size, info->no_output);
    info->stack_num -= num_params + 1;
    info->stack_num++;
    info->type = block_type->mResultType;
    return 1;
}
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
                                    sParserInfo * info)
{
    unsigned int node;
    int i;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeRegex;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    gNodes[node].uValue.sRegex.mRegexStr = regex_str;
    gNodes[node].uValue.sRegex.mGlobal = global;
    gNodes[node].uValue.sRegex.mIgnoreCase = ignore_case;
    gNodes[node].uValue.sRegex.mMultiline = multiline;
    gNodes[node].uValue.sRegex.mExtended = extended;
    gNodes[node].uValue.sRegex.mDotAll = dotall;
    gNodes[node].uValue.sRegex.mAnchored = anchored;
    gNodes[node].uValue.sRegex.mDollarEndOnly = dollar_endonly;
    gNodes[node].uValue.sRegex.mUngreedy = ungreedy;
    for (i = 0; i < num_string_expression; i++)
    {
        gNodes[node].uValue.sRegex.mStringExpressions[i] = string_expressions[i];
        gNodes[node].uValue.sRegex.mStringExpressionOffsets[i] = string_expression_offsets[i];
    }
    gNodes[node].uValue.sRegex.mNumStringExpression = num_string_expression;
    return node;
}
static int compile_regex(unsigned int node, sCompileInfo * info)
{
    char * str;
    int global;
    int ignore_case;
    int multiline;
    int extended;
    int dotall;
    int anchored;
    int dollar_endonly;
    int ungreedy;
    int num_string_expression;
    unsigned int * string_expressions;
    int * string_expression_offsets;
    int i;
    str = gNodes[node].uValue.sRegex.mRegexStr;
    global = gNodes[node].uValue.sRegex.mGlobal;
    ignore_case = gNodes[node].uValue.sRegex.mIgnoreCase;
    multiline = gNodes[node].uValue.sRegex.mMultiline;
    extended = gNodes[node].uValue.sRegex.mExtended;
    dotall = gNodes[node].uValue.sRegex.mDotAll;
    anchored = gNodes[node].uValue.sRegex.mAnchored;
    dollar_endonly = gNodes[node].uValue.sRegex.mDollarEndOnly;
    ungreedy = gNodes[node].uValue.sRegex.mUngreedy;
    num_string_expression = gNodes[node].uValue.sRegex.mNumStringExpression;
    string_expressions = gNodes[node].uValue.sRegex.mStringExpressions;
    string_expression_offsets = gNodes[node].uValue.sRegex.mStringExpressionOffsets;
    for (i = 0; i < num_string_expression; i++)
    {
        sCLClass * klass;
        if (!compile(string_expressions[i], info))
        {
            return 0;
        }
        if (info->type == (void *) 0)
        {
            compile_err_msg(info, "String expression requires String object");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        if (info->type == (void *) 0)
        {
            compile_err_msg(info, "String expression requires String object");
            info->err_num++;
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        klass = info->type->mClass;
        if (!type_identify_with_class_name(info->type, "String"))
        {
            sNodeType * result_type;
            sNodeType * result_method_generics_types;
            int method_index;
            int size;
            boxing_to_lapper_class(&info->type, info);
            klass = info->type->mClass;
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
            if (method_index == -1)
            {
                compile_err_msg(info, "String expression requires String object");
                info->err_num++;
                info->type = create_node_type_with_class_name("int");
                return 1;
            }
            append_opecode_to_code(info->code, 16, info->no_output);
            append_str_to_constant_pool_and_code(info->constant,
                                                 info->code,
                                                 info->sname,
                                                 info->no_output);
            append_int_value_to_code(info->code, info->sline, info->no_output);
            append_opecode_to_code(info->code, 3000, info->no_output);
            append_class_name_to_constant_pool_and_code(info, klass);
            append_int_value_to_code(info->code,
                                     method_index,
                                     info->no_output);
            size = get_var_size(result_type);
            append_int_value_to_code(info->code, size, info->no_output);
            info->stack_num--;
            info->stack_num++;
            info->type = result_type;
        }
    }
    append_opecode_to_code(info->code, 9013, info->no_output);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         str,
                                         info->no_output);
    append_int_value_to_code(info->code, global, info->no_output);
    append_int_value_to_code(info->code, ignore_case, info->no_output);
    append_int_value_to_code(info->code, multiline, info->no_output);
    append_int_value_to_code(info->code, extended, info->no_output);
    append_int_value_to_code(info->code, dotall, info->no_output);
    append_int_value_to_code(info->code, anchored, info->no_output);
    append_int_value_to_code(info->code,
                             dollar_endonly,
                             info->no_output);
    append_int_value_to_code(info->code, ungreedy, info->no_output);
    append_int_value_to_code(info->code,
                             num_string_expression,
                             info->no_output);
    for (i = 0; i < num_string_expression; i++)
    {
        append_int_value_to_code(info->code,
                                 string_expression_offsets[i],
                                 info->no_output);
    }
    info->stack_num++;
    info->stack_num -= num_string_expression;
    info->type = create_node_type_with_class_name("regex");
    return 1;
}
unsigned int sNodeTree_create_implements(unsigned int lnode,
                                         char * interface_name,
                                         sParserInfo * info)
{
    unsigned int node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeImplements;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = lnode;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    xstrncpy(gNodes[node].uValue.mVarName, interface_name, 64);
    return node;
}
static int compile_implements(unsigned int node,
                              sCompileInfo * info)
{
    char * interface_name;
    unsigned int lnode;
    sCLClass * klass;
    interface_name = gNodes[node].uValue.mVarName;
    lnode = gNodes[node].mLeft;
    if (!compile(lnode, info))
    {
        return 0;
    }
    if (info->type == (void *) 0 || type_identify_with_class_name(info->type,
                                                                  "Null"))
    {
        compile_err_msg(info, "no type for implements");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    klass = info->type->mClass;
    if (klass->mFlags & 0x1)
    {
        compile_err_msg(info, "Primitive value doesn't have class info");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    info->stack_num--;
    append_opecode_to_code(info->code, 1303, info->no_output);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         interface_name,
                                         info->no_output);
    info->type = create_node_type_with_class_name("bool");
    info->stack_num++;
    return 1;
}
unsigned int sNodeTree_create_inherit_call(int num_params,
                                           unsigned int params[],
                                           int method_index,
                                           sParserInfo * info)
{
    unsigned int node;
    int i;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeInheritCall;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    gNodes[node].uValue.sInheritCall.mNumParams = num_params;
    for (i = 0; i < gNodes[node].uValue.sInheritCall.mNumParams; i++)
    {
        gNodes[node].uValue.sInheritCall.mParams[i] = params[i];
    }
    gNodes[node].uValue.sInheritCall.mMethodIndex = method_index;
    return node;
}
static int compile_inherit_call(unsigned int node,
                                sCompileInfo * info)
{
    sCLClass * klass;
    sCLMethod * method;
    char * method_name;
    int method_index;
    int class_method;
    sNodeType * param_types[32];
    int num_params;
    int i;
    klass = info->pinfo->klass;
    method = info->method;
    method_name = (char *) ((&klass->mConst)->mConst + method->mNameOffset);
    if (method == (void *) 0)
    {
        compile_err_msg(info, "inherit call must be in method");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    method_index = gNodes[node].uValue.sInheritCall.mMethodIndex;
    class_method = method->mFlags & 0x2;
    if (!class_method)
    {
        append_opecode_to_code(info->code, 32, info->no_output);
        append_int_value_to_code(info->code, 0, info->no_output);
        append_int_value_to_code(info->code, 4, info->no_output);
        info->stack_num++;
    }
    info->pinfo->exist_block_object_err = 0;
    num_params = gNodes[node].uValue.sInheritCall.mNumParams;
    for (i = 0; i < num_params; i++)
    {
        int node2;
        node2 = gNodes[node].uValue.sInheritCall.mParams[i];
        if (!compile(node2, info))
        {
            return 0;
        }
        param_types[i] = info->type;
    }
    if (!info->pinfo->exist_block_object_err)
    {
        sNodeType * generics_types;
        sNodeType * right_method_generics_types;
        sNodeType * result_type;
        sNodeType * result_method_generics_types;
        int method_index2;
        int size;
        if (info->pinfo->klass)
        {
            generics_types = get_generics_type_of_inner_class(info->pinfo);
        }
        else
        {
            generics_types = (void *) 0;
        }
        right_method_generics_types = get_methocs_generics_type(info->pinfo);
        result_method_generics_types = (void *) 0;
        method_index2 = search_for_method(klass,
                                          method_name,
                                          param_types,
                                          num_params,
                                          class_method,
                                          method_index - 1,
                                          generics_types,
                                          (void *) 0,
                                          right_method_generics_types,
                                          &result_type,
                                          0,
                                          0,
                                          &result_method_generics_types);
        if (method_index2 == -1)
        {
            compile_err_msg(info, "method not found(30)");
            info->err_num++;
            err_msg_for_method_not_found(klass,
                                         method_name,
                                         param_types,
                                         num_params,
                                         1,
                                         info);
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        append_opecode_to_code(info->code, 16, info->no_output);
        append_str_to_constant_pool_and_code(info->constant,
                                             info->code,
                                             info->sname,
                                             info->no_output);
        append_int_value_to_code(info->code, info->sline, info->no_output);
        append_opecode_to_code(info->code, 3000, info->no_output);
        append_class_name_to_constant_pool_and_code(info, klass);
        append_int_value_to_code(info->code,
                                 method_index2,
                                 info->no_output);
        size = get_var_size(result_type);
        append_int_value_to_code(info->code, size, info->no_output);
        if (!class_method)
        {
            info->stack_num -= num_params + 1;
        }
        else
        {
            info->stack_num -= num_params;
        }
        info->stack_num++;
        info->type = result_type;
    }
    return 1;
}
unsigned int sNodeTree_create_range(unsigned int head,
                                    unsigned int tail,
                                    sParserInfo * info)
{
    unsigned int node;
    node = alloc_node();
    gNodes[node].mNodeType = kNodeTypeRange;
    gNodes[node].mSName = info->sname;
    gNodes[node].mLine = info->sline;
    gNodes[node].mLeft = head;
    gNodes[node].mRight = tail;
    gNodes[node].mMiddle = 0;
    gNodes[node].mType = (void *) 0;
    return node;
}
static int compile_range(unsigned int node, sCompileInfo * info)
{
    sCLClass * klass;
    sNodeType * param_types[32];
    int num_params;
    int no_output_before;
    int stack_num_before;
    int head_node;
    sNodeType * head_type;
    int tail_node;
    sNodeType * tail_type;
    sNodeType * node_type;
    klass = get_class("Range");
    num_params = 2;
    ;
    no_output_before = info->no_output;
    info->no_output = 1;
    stack_num_before = info->stack_num;
    info->pinfo->exist_block_object_err = 0;
    head_node = gNodes[node].mLeft;
    if (!compile(head_node, info))
    {
        return 0;
    }
    if (info->type->mClass->mFlags & 0x1)
    {
        boxing_to_lapper_class(&info->type, info);
    }
    head_type = info->type;
    info->pinfo->exist_block_object_err = 0;
    tail_node = gNodes[node].mRight;
    if (!compile(tail_node, info))
    {
        return 0;
    }
    if (info->type->mClass->mFlags & 0x1)
    {
        boxing_to_lapper_class(&info->type, info);
    }
    tail_type = info->type;
    info->no_output = no_output_before;
    info->stack_num = stack_num_before;
    if (!type_identify(head_type, tail_type))
    {
        compile_err_msg(info, "Range value type is the diffrent.");
        info->err_num++;
        info->type = create_node_type_with_class_name("int");
        return 1;
    }
    node_type = create_node_type_with_class_name("Range");
    node_type->mNumGenericsTypes = 1;
    node_type->mGenericsTypes[0] = head_type;
    append_opecode_to_code(info->code, 4000, info->no_output);
    append_str_to_constant_pool_and_code(info->constant,
                                         info->code,
                                         "Range",
                                         info->no_output);
    append_type_name_to_constant_pool_and_code(info, node_type);
    append_int_value_to_code(info->code, 0, info->no_output);
    info->stack_num++;
    info->pinfo->exist_block_object_err = 0;
    if (!compile(head_node, info))
    {
        return 0;
    }
    if (info->type->mClass->mFlags & 0x1)
    {
        boxing_to_lapper_class(&info->type, info);
    }
    param_types[0] = info->type;
    if (!compile(tail_node, info))
    {
        return 0;
    }
    if (info->type->mClass->mFlags & 0x1)
    {
        boxing_to_lapper_class(&info->type, info);
    }
    param_types[1] = info->type;
    if (!info->pinfo->exist_block_object_err)
    {
        char * method_name;
        sNodeType * generics_types2;
        sNodeType * result_type;
        sNodeType * result_method_generics_types;
        int method_index;
        int size;
        method_name = "initialize";
        generics_types2 = node_type;
        result_method_generics_types = (void *) 0;
        method_index = search_for_method(klass,
                                         method_name,
                                         param_types,
                                         num_params,
                                         0,
                                         klass->mNumMethods - 1,
                                         generics_types2,
                                         generics_types2,
                                         (void *) 0,
                                         &result_type,
                                         0,
                                         0,
                                         &result_method_generics_types);
        if (method_index == -1)
        {
            compile_err_msg(info, "method not found(30)");
            info->err_num++;
            err_msg_for_method_not_found(klass,
                                         method_name,
                                         param_types,
                                         num_params,
                                         0,
                                         info);
            info->type = create_node_type_with_class_name("int");
            return 1;
        }
        append_opecode_to_code(info->code, 16, info->no_output);
        append_str_to_constant_pool_and_code(info->constant,
                                             info->code,
                                             info->sname,
                                             info->no_output);
        append_int_value_to_code(info->code, info->sline, info->no_output);
        append_opecode_to_code(info->code, 3000, info->no_output);
        append_class_name_to_constant_pool_and_code(info, klass);
        append_int_value_to_code(info->code,
                                 method_index,
                                 info->no_output);
        size = get_var_size(node_type);
        append_int_value_to_code(info->code, size, info->no_output);
        info->stack_num -= num_params + 1;
        info->stack_num++;
        info->type = node_type;
    }
    return 1;
}
void show_node(unsigned int node)
{
    if (node == 0)
    {
        return;
    }
    switch (gNodes[node].mNodeType)
    {
    case kNodeTypeOperand:
        printf("operand value %d\n", gNodes[node].uValue.mOperand);
        puts("left");
        show_node(gNodes[node].mLeft);
        puts("right");
        show_node(gNodes[node].mRight);
        break;
    case kNodeTypeAndAnd:
        puts("and and operator");
        break;
    case kNodeTypeOrOr:
        puts("or or operator");
        break;
    case kNodeTypeByteValue:
        printf("byte value %d\n", gNodes[node].uValue.mByteValue);
        break;
    case kNodeTypeCByteValue:
        printf("cbyte value %d\n", gNodes[node].uValue.mByteValue);
        break;
    case kNodeTypeUByteValue:
        printf("ubyte value %u\n", gNodes[node].uValue.mUByteValue);
        break;
    case kNodeTypeCUByteValue:
        printf("ubyte value %u\n", gNodes[node].uValue.mUByteValue);
        break;
    case kNodeTypeShortValue:
        printf("short value %d\n", gNodes[node].uValue.mShortValue);
        break;
    case kNodeTypeCShortValue:
        printf("short value %d\n", gNodes[node].uValue.mShortValue);
        break;
    case kNodeTypeUShortValue:
        printf("ushort value %u\n", gNodes[node].uValue.mUShortValue);
        break;
    case kNodeTypeCUShortValue:
        printf("ushort value %u\n", gNodes[node].uValue.mUShortValue);
        break;
    case kNodeTypeIntValue:
        printf("int value %d\n", gNodes[node].uValue.mIntValue);
        break;
    case kNodeTypeCIntValue:
        printf("int value %d\n", gNodes[node].uValue.mIntValue);
        break;
    case kNodeTypeUIntValue:
        printf("uint value %u\n", gNodes[node].uValue.mUIntValue);
        break;
    case kNodeTypeCUIntValue:
        printf("uint value %u\n", gNodes[node].uValue.mUIntValue);
        break;
    case kNodeTypeLongValue:
        printf("long value %lld\n", gNodes[node].uValue.mLongValue);
        break;
    case kNodeTypeCLongValue:
        printf("long value %lld\n", gNodes[node].uValue.mLongValue);
        break;
    case kNodeTypeULongValue:
        printf("long value %llu\n", gNodes[node].uValue.mULongValue);
        break;
    case kNodeTypeCULongValue:
        printf("long value %llu\n", gNodes[node].uValue.mULongValue);
        break;
    case kNodeTypeFloatValue:
        printf("float value %f\n", gNodes[node].uValue.mFloatValue);
        break;
    case kNodeTypeDoubleValue:
        printf("double value %lf\n", gNodes[node].uValue.mDoubleValue);
        break;
    case kNodeTypeCFloatValue:
        printf("Float value %f\n", gNodes[node].uValue.mFloatValue);
        break;
    case kNodeTypeCDoubleValue:
        printf("Double value %lf\n", gNodes[node].uValue.mDoubleValue);
        break;
    case kNodeTypeAssignVariable:
        printf("var name %s\n", gNodes[node].uValue.mVarName);
        break;
    case kNodeTypeLoadVariable:
        printf("var name %s\n", gNodes[node].uValue.mVarName);
        break;
    case kNodeTypeIf:
        puts("if expression");
        break;
    case kNodeTypeWhile:
        puts("while expression");
        break;
    case kNodeTypeWhen:
        puts("when expression");
        break;
    case kNodeTypeFor:
        puts("for expression");
        break;
    case kNodeTypeBreak:
        puts("break");
        break;
    case kNodeTypeTrue:
        puts("true");
        break;
    case kNodeTypeFalse:
        puts("false");
        break;
    case kNodeTypeNull:
        puts("null");
        break;
    case kNodeTypeWildCard:
        puts("wildcard");
        break;
    case kNodeTypeClassMethodCall:
        puts("class method call");
        break;
    case kNodeTypeMethodCall:
        puts("method call");
        break;
    case kNodeTypeNewOperator:
        puts("new operator");
        break;
    case kNodeTypeReturn:
        puts("return");
        break;
    case kNodeTypeThrow:
        puts("throw");
        break;
    case kNodeTypeLoadField:
        {
            puts("load field");
        }
        break;
    case kNodeTypeStoreField:
        puts("store field");
        break;
    case kNodeTypeLoadClassField:
        puts("load field");
        break;
    case kNodeTypeStoreClassField:
        puts("store class field");
        break;
    case kNodeTypeStoreValueToPointer:
        puts("store value to pointer");
        break;
    case kNodeTypeLoadValueFromPointer:
        puts("load value from pointer");
        break;
    case kNodeTypeIncrementOperand:
        puts("increment operand");
        break;
    case kNodeTypeDecrementOperand:
        puts("decrement operand");
        break;
    case kNodeTypeIncrementWithValueOperand:
        puts("increment operand with value");
        break;
    case kNodeTypeDecrementWithValueOperand:
        puts("decrement operand with value");
        break;
    case kNodeTypeMonadicIncrementOperand:
        puts("monadic increment operand");
        break;
    case kNodeTypeMonadicDecrementOperand:
        puts("monadic decrement operand");
        break;
    case kNodeTypeStoreArrayElement:
        puts("load element");
        break;
    case kNodeTypeChar:
        puts("char");
        break;
    case kNodeTypeString:
        puts("string");
        break;
    case kNodeTypeBuffer:
        puts("buffer");
        break;
    case kNodeTypePath:
        puts("path");
        break;
    case kNodeTypeGetAddress:
        puts("get address");
        break;
    case kNodeTypeArrayValue:
        puts("array value");
        break;
    case kNodeTypeCArrayValue:
        puts("carray value");
        break;
    case kNodeTypeEqualableCArrayValue:
        puts("equalable carray value");
        break;
    case kNodeTypeSortableCArrayValue:
        puts("sortable carray value");
        break;
    case kNodeTypeHashValue:
        puts("hash value");
        break;
    case kNodeTypeListValue:
        puts("list value");
        break;
    case kNodeTypeSortableListValue:
        puts("sortable list value");
        break;
    case kNodeTypeEqualableListValue:
        puts("equalable list value");
        break;
    case kNodeTypeTupleValue:
        puts("tuple value");
        break;
    case kNodeTypeTry:
        puts("try");
        break;
    case kNodeTypeBlockObject:
        puts("lambda");
        break;
    case kNodeTypeFunction:
        puts("function");
        break;
    case kNodeTypeNormalBlock:
        puts("block");
        break;
    case kNodeTypeLoadArrayElement:
        puts("load element");
        break;
    case kNodeTypeBlockCall:
        puts("block call");
        break;
    case kNodeTypeRegex:
        puts("regex");
        break;
    case kNodeTypeImplements:
        puts("implements");
        break;
    case kNodeTypeInheritCall:
        puts("inherit");
        break;
    case kNodeTypeRange:
        puts("range");
        break;
    }
}
int compile(unsigned int node, sCompileInfo * info)
{
    if (node == 0)
    {
        return 1;
    }
    info->sname = gNodes[node].mSName;
    info->sline = gNodes[node].mLine;
    switch (gNodes[node].mNodeType)
    {
    case kNodeTypeOperand:
        if (!compile_operand(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeAndAnd:
        if (!compile_and_and(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeOrOr:
        if (!compile_or_or(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeByteValue:
        if (!compile_byte_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeCByteValue:
        if (!compile_cbyte_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeUByteValue:
        if (!compile_ubyte_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeCUByteValue:
        if (!compile_cubyte_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeFloatValue:
        if (!compile_float_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeDoubleValue:
        if (!compile_double_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeCFloatValue:
        if (!compile_cfloat_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeCDoubleValue:
        if (!compile_cdouble_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeShortValue:
        if (!compile_short_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeUShortValue:
        if (!compile_ushort_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeCShortValue:
        if (!compile_cshort_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeCUShortValue:
        if (!compile_cushort_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeIntValue:
        if (!compile_int_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeCIntValue:
        if (!compile_cint_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeUIntValue:
        if (!compile_uint_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeCUIntValue:
        if (!compile_cuint_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeLongValue:
        if (!compile_long_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeCLongValue:
        if (!compile_clong_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeULongValue:
        if (!compile_ulong_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeCULongValue:
        if (!compile_culong_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeAssignVariable:
        if (!compile_store_variable(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeLoadVariable:
        if (!compile_load_variable(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeIf:
        if (!compile_if_expression(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeWhen:
        if (!compile_when_expression(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeWhile:
        if (!compile_while_expression(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeFor:
        if (!compile_for_expression(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeBreak:
        if (!compile_break_expression(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeTrue:
        if (!compile_true_expression(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeFalse:
        if (!compile_false_expression(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeNull:
        if (!compile_null_expression(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeWildCard:
        if (!compile_wildcard_expression(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeClassMethodCall:
        if (!compile_class_method_call(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeMethodCall:
        if (!compile_method_call(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeNewOperator:
        if (!compile_new_operator(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeReturn:
        if (!compile_return_expression(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeThrow:
        if (!compile_throw_expression(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeLoadField:
        if (!compile_load_field(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeStoreField:
        if (!compile_store_field(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeLoadClassField:
        if (!compile_load_class_field(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeStoreClassField:
        if (!compile_store_class_field(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeStoreValueToPointer:
        if (!compile_store_value_to_pointer(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeLoadValueFromPointer:
        if (!compile_load_value_from_pointer(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeIncrementOperand:
        if (!compile_increment_operand(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeDecrementOperand:
        if (!compile_decrement_operand(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeIncrementWithValueOperand:
        if (!compile_increment_operand_with_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeDecrementWithValueOperand:
        if (!compile_decrement_operand_with_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeMonadicIncrementOperand:
        if (!compile_monadic_increment_operand(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeMonadicDecrementOperand:
        if (!compile_monadic_decrement_operand(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeLoadArrayElement:
        if (!compile_load_array_element(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeStoreArrayElement:
        if (!compile_store_array_element(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeChar:
        if (!compile_char_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeString:
        if (!compile_string_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeBuffer:
        if (!compile_buffer_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypePath:
        if (!compile_path_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeGetAddress:
        if (!compile_get_address(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeArrayValue:
        if (!compile_array_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeCArrayValue:
        if (!compile_carray_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeEqualableCArrayValue:
        if (!compile_equalable_carray_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeSortableCArrayValue:
        if (!compile_sortable_carray_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeListValue:
        if (!compile_list_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeEqualableListValue:
        if (!compile_equalable_list_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeSortableListValue:
        if (!compile_sortable_list_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeTupleValue:
        if (!compile_tuple_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeHashValue:
        if (!compile_hash_value(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeTry:
        if (!compile_try_expression(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeBlockObject:
        if (!compile_block_object(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeFunction:
        if (!compile_function(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeNormalBlock:
        if (!compile_normal_block(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeBlockCall:
        if (!compile_block_call(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeRegex:
        if (!compile_regex(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeImplements:
        if (!compile_implements(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeInheritCall:
        if (!compile_inherit_call(node, info))
        {
            return 0;
        }
        break;
    case kNodeTypeRange:
        if (!compile_range(node, info))
        {
            return 0;
        }
        break;
    }
    return 1;
}
int check_node_is_variable(unsigned int node)
{
    return gNodes[node].mNodeType == kNodeTypeLoadVariable;
}
void create_type_name_from_node_type(char * type_name,
                                     int type_name_max,
                                     sNodeType * node_type)
{
    sCLClass * klass;
    klass = node_type->mClass;
    xstrncat(type_name,
             (char *) ((&klass->mConst)->mConst + klass->mClassNameOffset),
             type_name_max);
    if (node_type->mBlockType)
    {
        sNodeBlockType * node_block_type;
        node_block_type = node_type->mBlockType;
        xstrncat(type_name, "(", type_name_max);
        if (node_block_type->mNumParams > 0)
        {
            int i;
            for (i = 0; i < node_block_type->mNumParams; i++)
            {
                create_type_name_from_node_type(type_name,
                                                type_name_max,
                                                node_block_type->mParams[i]);
                if (i != node_block_type->mNumParams - 1)
                {
                    xstrncat(type_name, ",", type_name_max);
                }
            }
        }
        xstrncat(type_name, ")", type_name_max);
        xstrncat(type_name, ":", type_name_max);
        create_type_name_from_node_type(type_name,
                                        type_name_max,
                                        node_block_type->mResultType);
    }
    if (node_type->mArray)
    {
        xstrncat(type_name, "[]", type_name_max);
    }
    if (node_type->mNullable)
    {
        xstrncat(type_name, "?", type_name_max);
    }
    if (node_type->mNumGenericsTypes > 0)
    {
        int i;
        xstrncat(type_name, "<", type_name_max);
        for (i = 0; i < node_type->mNumGenericsTypes; i++)
        {
            create_type_name_from_node_type(type_name,
                                            type_name_max,
                                            node_type->mGenericsTypes[i]);
            if (i != node_type->mNumGenericsTypes - 1)
            {
                xstrncat(type_name, ",", type_name_max);
            }
        }
        xstrncat(type_name, ">", type_name_max);
    }
}
