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
int gSigInt = 0;
void show_stack(CLVALUE * stack,
                CLVALUE * stack_ptr,
                CLVALUE * lvar,
                int var_num)
{
    int i;
    if (lvar == (void *) 0)
    {
        lvar = stack + var_num;
    }
    if (stack_ptr == lvar + var_num)
    {
        puts("stack is empty");
    }
    if (stack_ptr < stack)
    {
        puts("stack is invalid. abort.");
        exit(3);
    }
    for (i = 0; i < 30; i++)
    {
        if (stack + i < stack_ptr)
        {
            if (stack_ptr == stack + i)
            {
                printf("![%d] %d on %p\n", i, stack[i].mIntValue, stack + i);
            }
            else
            {
                printf("[%d] %d on %p\n", i, stack[i].mIntValue, stack + i);
            }
        }
    }
}
static void show_inst(unsigned inst)
{
    switch (inst)
    {
    case 1:
        puts("OP_POP");
        break;
    case 2:
        puts("OP_POP_N");
        break;
    case 3:
        puts("OP_REVERSE");
        break;
    case 4:
        puts("OP_DUPE");
        break;
    case 5:
        puts("OP_COND_JUMP");
        break;
    case 6:
        puts("OP_COND_NOT_JUMP");
        break;
    case 7:
        puts("OP_GOTO");
        break;
    case 18:
        puts("OP_LABEL");
        break;
    case 29:
        puts("OP_STORE_VALUE_TO_GLOBAL");
        break;
    case 7425:
        puts("OP_UINT_TO_UINTEGER_CAST");
        break;
    case 30:
        puts("OP_POP_VALUE_FROM_GLOBAL");
        break;
    case 8:
        puts("OP_RETURN");
        break;
    case 14:
        puts("OP_HEAD_OF_EXPRESSION");
        break;
    case 17:
        puts("OP_SIGINT");
        break;
    case 9:
        puts("OP_THROW");
        break;
    case 31:
        puts("OP_STORE");
        break;
    case 32:
        puts("OP_LOAD");
        break;
    case 35:
        puts("OP_LDCBYTE");
        break;
    case 36:
        puts("OP_LDCUBYTE");
        break;
    case 37:
        puts("OP_LDCSHORT");
        break;
    case 38:
        puts("OP_LDCUSHORT");
        break;
    case 39:
        puts("OP_LDCINT");
        break;
    case 47:
        puts("OP_LDCBOOL");
        break;
    case 40:
        puts("OP_LDCUINT");
        break;
    case 41:
        puts("OP_LDCLONG");
        break;
    case 42:
        puts("OP_LDCULONG");
        break;
    case 43:
        puts("OP_LDCNULL");
        break;
    case 44:
        puts("OP_LDCPOINTER");
        break;
    case 45:
        puts("OP_LDCFLOAT");
        break;
    case 46:
        puts("OP_LDCDOUBLE");
        break;
    case 50:
        puts("OP_BADD");
        break;
    case 80:
        puts("OP_UBADD");
        break;
    case 100:
        puts("OP_SADD");
        break;
    case 150:
        puts("OP_USADD");
        break;
    case 200:
        puts("OP_IADD");
        break;
    case 251:
        puts("OP_UIADD");
        break;
    case 300:
        puts("OP_LADD");
        break;
    case 400:
        puts("OP_ULADD");
        break;
    case 450:
        puts("OP_FADD");
        break;
    case 500:
        puts("OP_DADD");
        break;
    case 600:
        puts("OP_PADD");
        break;
    case 700:
        puts("OP_CADD");
        break;
    case 51:
        puts("OP_BSUB");
        break;
    case 81:
        puts("OP_UBSUB");
        break;
    case 101:
        puts("OP_SSUB");
        break;
    case 151:
        puts("OP_USSUB");
        break;
    case 201:
        puts("OP_ISUB");
        break;
    case 250:
        puts("OP_UISUB");
        break;
    case 301:
        puts("OP_LSUB");
        break;
    case 401:
        puts("OP_ULSUB");
        break;
    case 451:
        puts("OP_FSUB");
        break;
    case 501:
        puts("OP_DSUB");
        break;
    case 601:
        puts("OP_PSUB");
        break;
    case 701:
        puts("OP_CSUB");
        break;
    case 1040:
        puts("OP_IEQ");
        break;
    case 1041:
        puts("OP_INOTEQ");
        break;
    case 1220:
        puts("OP_REGEQ");
        break;
    case 1221:
        puts("OP_REGNOTEQ");
        break;
    case 2000:
        puts("OP_ANDAND");
        break;
    case 2001:
        puts("OP_OROR");
        break;
    case 2002:
        puts("OP_LOGICAL_DENIAL");
        break;
    case 3000:
        puts("OP_INVOKE_METHOD");
        break;
    case 3001:
        puts("OP_INVOKE_VIRTUAL_METHOD");
        break;
    case 3002:
        puts("OP_INVOKE_VIRTUAL_METHOD");
        break;
    case 3003:
        puts("OP_INVOKE_BLOCK");
        break;
    case 4000:
        puts("OP_NEW");
        break;
    case 4001:
        puts("OP_LOAD_FIELD");
        break;
    case 4002:
        puts("OP_LOAD_FIELD_ADDRESS");
        break;
    case 4003:
        puts("OP_STORE_FIELD");
        break;
    case 4004:
        puts("OP_LOAD_CLASS_FIELD");
        break;
    case 4006:
        puts("OP_STORE_CLASS_FIELD");
        break;
    case 4007:
        puts("OP_LOAD_ELEMENT");
        break;
    case 4008:
        puts("OP_STORE_ELEMENT");
        break;
    case 5000:
        puts("OP_STORE_VALUE_TO_INT_ADDRESS");
        break;
    case 5001:
        puts("OP_STORE_VALUE_TO_UINT_ADDRESS:");
        break;
    case 5002:
        puts("OP_STORE_VALUE_TO_BYTE_ADDRESS:");
        break;
    case 5003:
        puts("OP_STORE_VALUE_TO_UBYTE_ADDRESS:");
        break;
    case 5004:
        puts("OP_STORE_VALUE_TO_SHORT_ADDRESS:");
        break;
    case 5005:
        puts("OP_STORE_VALUE_TO_USHORT_ADDRESS:");
        break;
    case 5006:
        puts("OP_STORE_VALUE_TO_LONG_ADDRESS:");
        break;
    case 9000:
        puts("OP_CREATE_STRING");
        break;
    case 9001:
        puts("OP_CREATE_BUFFER");
        break;
    case 9002:
        puts("OP_CREATE_PATH");
        break;
    case 9012:
        puts("OP_CREATE_BLOCK_OBJECT");
        break;
    case 7360:
        puts("OP_BYTE_TO_STRING_CAST");
        break;
    case 7361:
        puts("OP_SHORT_TO_STRING_CAST");
        break;
    case 7362:
        puts("OP_INT_TO_STRING_CAST");
        break;
    case 7363:
        puts("OP_LONG_TO_STRING_CAST");
        break;
    case 7364:
        puts("OP_UBYTE_TO_STRING_CAST");
        break;
    case 7365:
        puts("OP_USHORT_TO_STRING_CAST");
        break;
    case 7366:
        puts("OP_UINT_TO_STRING_CAST");
        break;
    case 7367:
        puts("OP_ULONG_TO_STRING_CAST");
        break;
    case 7368:
        puts("OP_FLOAT_TO_STRING_CAST");
        break;
    case 7369:
        puts("OP_DOUBLE_TO_STRING_CAST");
        break;
    case 7370:
        puts("OP_BOOL_TO_STRING_CAST");
        break;
    case 7372:
        puts("OP_POINTER_TO_STRING_CAST");
        break;
    case 7373:
        puts("OP_CHAR_TO_STRING_CAST");
        break;
    default:
        printf("inst %d\n", inst);
        break;
    }
}
void vm_mutex_on()
{
}
void vm_mutex_off()
{
}
void new_vm_mutex()
{
}
int invoke_method(sCLClass * klass,
                  sCLMethod * method,
                  CLVALUE * stack,
                  int var_num,
                  CLVALUE * * stack_ptr,
                  sVMInfo * info)
{
    sCLClass * running_class;
    sCLMethod * running_method;
    int num_global_stack;
    char * sname2;
    int sline2;
    running_class = info->running_class;
    running_method = info->running_method;
    num_global_stack = gGlobalStackPtr - gGlobalStack;
    info->running_class = klass;
    info->running_method = method;
    sname2 = info->sname2;
    sline2 = info->sline2;
    if (sname2)
    {
        if (info->num_stack_trace < 32 - 1)
        {
            info->stack_trace_sname[info->num_stack_trace] = sname2;
            info->stack_trace_sline[info->num_stack_trace] = sline2;
            info->num_stack_trace++;
        }
        else
        {
            int i;
            for (i = 0; i < info->num_stack_trace - 1; i++)
            {
                info->stack_trace_sname[i] = info->stack_trace_sname[i + 1];
                info->stack_trace_sline[i] = info->stack_trace_sline[i + 1];
            }
            info->num_stack_trace--;
            info->stack_trace_sname[info->num_stack_trace] = sname2;
            info->stack_trace_sline[info->num_stack_trace] = sline2;
            info->num_stack_trace++;
        }
    }
    if (method->mFlags & 0x1)
    {
        CLVALUE * lvar;
        lvar = *stack_ptr - method->mNumParams;
        if (method->mNativeMethod == (void *) 0)
        {
            char * path;
            char * fun_name;
            fNativeMethod native_method;
            path = (char *) ((&klass->mConst)->mConst + method->mPathOffset);
            native_method = get_native_method(path, &fun_name);
            if (native_method == (void *) 0)
            {
                entry_exception_object_with_class_name(stack_ptr,
                                                       stack,
                                                       var_num,
                                                       info,
                                                       "Exception",
                                                       "Native method not found");
                gGlobalStackPtr = gGlobalStack + num_global_stack;
                return 0;
            }
            method->mNativeMethod = native_method;
            method->mNativeFunName = fun_name;
        }
        info->current_stack = stack;
        info->current_var_num = var_num;
        if (!(method->mNativeMethod)(stack_ptr, lvar, info))
        {
            CLVALUE result;
            result = *(*stack_ptr - 1);
            *stack_ptr = lvar;
            * (*stack_ptr) = result;
            (*stack_ptr)++;
            gGlobalStackPtr = gGlobalStack + num_global_stack;
            return 0;
        }
        if (is_void_type(method->mResultType, klass))
        {
            *stack_ptr = lvar;
            (*stack_ptr)->mLongValue = 0;
            (*stack_ptr)->mIntValue = 0;
            (*stack_ptr)++;
        }
        else
        {
            CLVALUE result;
            result = *(*stack_ptr - 1);
            *stack_ptr = lvar;
            * (*stack_ptr) = result;
            (*stack_ptr)++;
        }
    }
    else
    {
        int real_param_num;
        CLVALUE * lvar;
        sByteCode * code;
        sConst * constant;
        CLVALUE * new_stack;
        int new_var_num;
        real_param_num = method->mNumParams + (method->mFlags & 0x2 ? 0 : 1);
        lvar = *stack_ptr - real_param_num;
        code = &method->mByteCodes;
        constant = &klass->mConst;
        new_stack = lvar;
        new_var_num = method->mVarNum;
        memset(lvar + real_param_num,
               0,
               sizeof(CLVALUE) * (new_var_num - real_param_num));
        if (!vm(code, constant, new_stack, new_var_num, klass, info))
        {
            *stack_ptr = lvar;
            * (*stack_ptr) = *(new_stack + new_var_num);
            (*stack_ptr)++;
            gGlobalStackPtr = gGlobalStack + num_global_stack;
            return 0;
        }
        *stack_ptr = lvar;
        * (*stack_ptr) = *(new_stack + new_var_num);
        (*stack_ptr)++;
    }
    info->running_class = running_class;
    info->running_method = running_method;
    gGlobalStackPtr = gGlobalStack + num_global_stack;
    if (sname2)
    {
        info->num_stack_trace--;
    }
    return 1;
}
int invoke_block(CLObject block_object,
                 CLVALUE * stack,
                 int var_num,
                 int num_params,
                 CLVALUE * * stack_ptr,
                 sVMInfo * info,
                 int llvm_flag)
{
    sBlockObject * object_data;
    sByteCode code;
    sConst constant;
    CLVALUE * new_stack;
    int new_var_num;
    int lambda;
    sCLClass * klass;
    object_data = (sBlockObject *) get_object_pointer(block_object);
    code = object_data->mCodes;
    constant = object_data->mConstant;
    new_stack = *stack_ptr;
    new_var_num = object_data->mBlockVarNum + object_data->mParentVarNum;
    lambda = object_data->mLambda;
    memset(new_stack + num_params,
           0,
           sizeof(CLVALUE) * (new_var_num - num_params));
    klass = (void *) 0;
    if (lambda)
    {
        memcpy(new_stack,
               *stack_ptr - num_params,
               sizeof(CLVALUE) * num_params);
        if (!vm(&code, &constant, new_stack, new_var_num, klass, info))
        {
            * (*stack_ptr) = *new_stack;
            (*stack_ptr)++;
            return 0;
        }
    }
    else
    {
        if (!check_variables_existance_on_stack(stack, *stack_ptr))
        {
            object_data = (sBlockObject *) get_object_pointer(block_object);
            memcpy(object_data->mParentStack,
                   new_stack,
                   sizeof(CLVALUE) * object_data->mParentVarNum);
            entry_exception_object_with_class_name(stack_ptr,
                                                   stack,
                                                   var_num,
                                                   info,
                                                   "Exception",
                                                   "Parent variables doesn't exist. ID is %p",
                                                   object_data->mStackID);
            return 0;
        }
        memcpy(new_stack,
               object_data->mParentStack,
               sizeof(CLVALUE) * object_data->mParentVarNum);
        memcpy(new_stack + object_data->mParentVarNum,
               *stack_ptr - num_params,
               sizeof(CLVALUE) * num_params);
        if (!vm(&code, &constant, new_stack, new_var_num, klass, info))
        {
            object_data = (sBlockObject *) get_object_pointer(block_object);
            memcpy(object_data->mParentStack,
                   new_stack,
                   sizeof(CLVALUE) * object_data->mParentVarNum);
            * (*stack_ptr) = *new_stack;
            (*stack_ptr)++;
            return 0;
        }
        object_data = (sBlockObject *) get_object_pointer(block_object);
        memcpy(object_data->mParentStack,
               new_stack,
               sizeof(CLVALUE) * object_data->mParentVarNum);
    }
    * (*stack_ptr) = *(new_stack + new_var_num);
    (*stack_ptr)++;
    return 1;
}
static int initialize_class(sCLClass * klass)
{
    int i;
    if (klass->mClassInitializeMethodIndex != -1)
    {
        sCLMethod * initialize_method;
        const int stack_size;
        CLVALUE * stack;
        CLVALUE * stack_ptr;
        sVMInfo info;
        initialize_method = klass->mMethods + klass->mClassInitializeMethodIndex;
        stack_size = 512;
        stack = xcalloc(1, sizeof(CLVALUE) * stack_size);
        stack_ptr = stack;
        memset(&info, 0, sizeof(sVMInfo));
        if (!invoke_method(klass,
                           initialize_method,
                           stack,
                           0,
                           &stack_ptr,
                           &info))
        {
            show_exception_message(info.exception_message);
            xfree(stack);
            return 0;
        }
        xfree(stack);
    }
    for (i = 0; i < klass->mNumClassFields; i++)
    {
        sCLField * field;
        field = klass->mClassFields + i;
        if (field->mInitializeValue != -1)
        {
            field->mValue.mIntValue = field->mInitializeValue;
        }
    }
    return 1;
}
static int load_class_with_initialize(char * class_name)
{
    sCLClass * klass;
    klass = load_class(class_name);
    if (klass)
    {
        if (!initialize_class(klass))
        {
            return 0;
        }
    }
    return 1;
}
static int load_fundamental_classes_on_runtime()
{
    if (!load_class_with_initialize("PcreOVec"))
    {
        return 0;
    }
    if (!load_class_with_initialize("System"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Global"))
    {
        return 0;
    }
    if (!load_class_with_initialize("String"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Buffer"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Exception"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Object"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Range"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Byte"))
    {
        return 0;
    }
    if (!load_class_with_initialize("UByte"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Short"))
    {
        return 0;
    }
    if (!load_class_with_initialize("UShort"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Integer"))
    {
        return 0;
    }
    if (!load_class_with_initialize("UInteger"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Long"))
    {
        return 0;
    }
    if (!load_class_with_initialize("ULong"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Float"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Double"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Pointer"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Char"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Bool"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Array"))
    {
        return 0;
    }
    if (!load_class_with_initialize("EqualableArray"))
    {
        return 0;
    }
    if (!load_class_with_initialize("SortableArray"))
    {
        return 0;
    }
    if (!load_class_with_initialize("IHashKey"))
    {
        return 0;
    }
    if (!load_class_with_initialize("IEqualable"))
    {
        return 0;
    }
    if (!load_class_with_initialize("ISortable"))
    {
        return 0;
    }
    if (!load_class_with_initialize("HashItem"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Hash"))
    {
        return 0;
    }
    if (!load_class_with_initialize("ListItem"))
    {
        return 0;
    }
    if (!load_class_with_initialize("List"))
    {
        return 0;
    }
    if (!load_class_with_initialize("SortableList"))
    {
        return 0;
    }
    if (!load_class_with_initialize("EqualableList"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Tuple1"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Tuple2"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Tuple3"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Tuple4"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Tuple5"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Tuple6"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Tuple7"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Tuple8"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Tuple9"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Tuple10"))
    {
        return 0;
    }
    if (!load_class_with_initialize("File"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Path"))
    {
        return 0;
    }
    if (!load_class_with_initialize("tm"))
    {
        return 0;
    }
    if (!load_class_with_initialize("stat"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Directory"))
    {
        return 0;
    }
    if (!load_class_with_initialize("termios"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Job"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Command"))
    {
        return 0;
    }
    if (!load_class_with_initialize("Clover"))
    {
        return 0;
    }
    return 1;
}
static void set_free_fun_to_classes()
{
    sCLClass * klass;
    klass = get_class("regex");
    klass->mFreeFun = regex_free_fun;
}
int class_init_on_runtime()
{
    if (!load_fundamental_classes_on_runtime())
    {
        return 0;
    }
    set_boxing_and_unboxing_classes();
    set_free_fun_to_classes();
    return 1;
}
static int finalize_class(sCLClass * klass)
{
    if (klass->mClassFinalizeMethodIndex != -1)
    {
        sCLMethod * finalize_method;
        const int stack_size;
        CLVALUE * stack;
        CLVALUE * stack_ptr;
        sVMInfo info;
        finalize_method = klass->mMethods + klass->mClassFinalizeMethodIndex;
        stack_size = 512;
        stack = xcalloc(1, sizeof(CLVALUE) * stack_size);
        stack_ptr = stack;
        memset(&info, 0, sizeof(sVMInfo));
        if (!invoke_method(klass,
                           finalize_method,
                           stack,
                           0,
                           &stack_ptr,
                           &info))
        {
            show_exception_message(info.exception_message);
            xfree(stack);
            return 0;
        }
        xfree(stack);
    }
    return 1;
}
int call_finalize_method_on_free_object(sCLClass * klass,
                                        CLObject self)
{
    if (klass->mFinalizeMethodIndex != -1)
    {
        sCLMethod * finalize_method;
        const int stack_size;
        CLVALUE * stack;
        CLVALUE * stack_ptr;
        sVMInfo info;
        finalize_method = klass->mMethods + klass->mFinalizeMethodIndex;
        stack_size = 512;
        stack = xcalloc(1, sizeof(CLVALUE) * stack_size);
        stack_ptr = stack;
        memset(&info, 0, sizeof(sVMInfo));
        stack_ptr->mLongValue = 0;
        stack_ptr->mObjectValue = self;
        stack_ptr++;
        if (!invoke_method(klass,
                           finalize_method,
                           stack,
                           0,
                           &stack_ptr,
                           &info))
        {
            show_exception_message(info.exception_message);
            xfree(stack);
            return 0;
        }
        xfree(stack);
    }
    return 1;
}
void class_final_on_runtime()
{
    sClassTable * p;
    p = gHeadClassTable;
    while (p)
    {
        (void) finalize_class(p->mItem);
        p = p->mNextClass;
    }
}
sCLClass * get_class_with_load_and_initialize(char * class_name)
{
    sCLClass * result;
    result = get_class(class_name);
    if (result == (void *) 0)
    {
        result = load_class(class_name);
        if (result == (void *) 0)
        {
            fprintf(stderr, "Clover2 can't load %s\n", class_name);
            return (void *) 0;
        }
        if (!initialize_class(result))
        {
            return (void *) 0;
        }
    }
    return result;
}
void boxing_primitive_value_to_object(CLVALUE object,
                                      CLVALUE * result,
                                      sCLClass * klass)
{
    if (klass->mFlags & 0x1)
    {
        if (is_this_class_with_class_name(klass, "byte"))
        {
            char value;
            CLObject obj;
            value = object.mByteValue;
            obj = create_byte((char) value);
            result->mLongValue = 0;
            result->mObjectValue = obj;
        }
        else if (is_this_class_with_class_name(klass, "ubyte"))
        {
            unsigned char value;
            CLObject obj;
            value = object.mUByteValue;
            obj = create_ubyte((unsigned char) value);
            result->mLongValue = 0;
            result->mObjectValue = obj;
        }
        else if (is_this_class_with_class_name(klass, "short"))
        {
            short value;
            CLObject obj;
            value = object.mShortValue;
            obj = create_short((short) value);
            result->mLongValue = 0;
            result->mObjectValue = obj;
        }
        else if (is_this_class_with_class_name(klass, "ushort"))
        {
            unsigned short value;
            CLObject obj;
            value = object.mUShortValue;
            obj = create_ushort((unsigned short) value);
            result->mLongValue = 0;
            result->mObjectValue = obj;
        }
        else if (is_this_class_with_class_name(klass, "int"))
        {
            int value;
            CLObject obj;
            value = object.mIntValue;
            obj = create_integer((int) value);
            result->mLongValue = 0;
            result->mObjectValue = obj;
        }
        else if (is_this_class_with_class_name(klass, "uint"))
        {
            unsigned int value;
            CLObject obj;
            value = object.mUIntValue;
            obj = create_uinteger(value);
            result->mLongValue = 0;
            result->mObjectValue = obj;
        }
        else if (is_this_class_with_class_name(klass, "long"))
        {
            long long value;
            CLObject obj;
            value = object.mLongValue;
            obj = create_long((long long) value);
            result->mLongValue = 0;
            result->mObjectValue = obj;
        }
        else if (is_this_class_with_class_name(klass, "ulong"))
        {
            unsigned long long value;
            CLObject obj;
            value = object.mULongValue;
            obj = create_ulong((unsigned long long) value);
            result->mLongValue = 0;
            result->mObjectValue = obj;
        }
        else if (is_this_class_with_class_name(klass, "float"))
        {
            float value;
            CLObject obj;
            value = object.mFloatValue;
            obj = create_float((float) value);
            result->mLongValue = 0;
            result->mObjectValue = obj;
        }
        else if (is_this_class_with_class_name(klass, "double"))
        {
            double value;
            CLObject obj;
            value = object.mDoubleValue;
            obj = create_double((double) value);
            result->mLongValue = 0;
            result->mObjectValue = obj;
        }
        else if (is_this_class_with_class_name(klass, "pointer"))
        {
            char * value;
            CLObject obj;
            value = object.mPointerValue;
            obj = create_pointer((char *) value);
            result->mLongValue = 0;
            result->mObjectValue = obj;
        }
        else if (is_this_class_with_class_name(klass, "char"))
        {
            wchar_t value;
            CLObject obj;
            value = object.mCharValue;
            obj = create_char((wchar_t) value);
            result->mLongValue = 0;
            result->mObjectValue = obj;
        }
        else if (is_this_class_with_class_name(klass, "bool"))
        {
            int value;
            CLObject obj;
            value = object.mBoolValue;
            obj = create_bool((int) value);
            result->mLongValue = 0;
            result->mObjectValue = obj;
        }
    }
    else
    {
        *result = object;
    }
}
void Self_convertion_of_method_name_and_params(char * method_name_and_params,
                                               char * method_name_and_params2,
                                               char * class_name)
{
    char * p;
    char * p2;
    char * result;
    p = method_name_and_params;
    p2 = method_name_and_params2;
    result = strstr(p, "(");
    memcpy(p2, p, result - p);
    p2 += result - p;
    p = result;
    while (1)
    {
        char * result;
        result = strstr(p, class_name);
        if (result == (void *) 0)
        {
            memcpy(p2, p, strlen(p));
            p2[strlen(p)] = '\000';
            break;
        }
        memcpy(p2, p, result - p);
        p2 += result - p;
        memcpy(p2, "Self", 4);
        p2 += 4;
        p = result + strlen(class_name);
    }
}
static int string_expression(char * str,
                             sBuf * buf,
                             int * string_expression_offsets,
                             CLObject * string_expression_object,
                             int num_string_expression,
                             CLVALUE * * stack_ptr,
                             CLVALUE * stack,
                             int var_num,
                             sVMInfo * info)
{
    int offset_before;
    int i;
    offset_before = 0;
    for (i = 0; i < num_string_expression; i++)
    {
        int offset;
        CLObject object;
        char * str2;
        offset = string_expression_offsets[i];
        sBuf_append(buf, str + offset_before, offset - offset_before);
        object = string_expression_object[i];
        if (object == 0)
        {
            entry_exception_object_with_class_name(stack_ptr,
                                                   stack,
                                                   var_num,
                                                   info,
                                                   "Exception",
                                                   "Null pointer exception(10)");
            return 0;
        }
        str2 = string_object_to_char_array(object);
        sBuf_append_str(buf, str2);
        xfree(str2);
        offset_before = offset;
    }
    sBuf_append(buf, str + offset_before, strlen(str) - offset_before);
    return 1;
}
int vm(sByteCode * code,
       sConst * constant,
       CLVALUE * stack,
       int var_num,
       sCLClass * klass,
       sVMInfo * info)
{
    register char * pc;
    CLVALUE * stack_ptr;
    CLVALUE * lvar;
    sCLStack * stack_id;
    pc = code->mCodes;
    stack_ptr = stack + var_num;
    lvar = stack;
    stack_id = append_stack_to_stack_list(stack, &stack_ptr);
    while (pc - code->mCodes < code->mLen)
    {
        unsigned int inst;
        inst = *(unsigned int *) pc;
        pc += sizeof(int);
        switch (inst)
        {
        case 28:
            break;
        case 1:
            vm_mutex_on();
            stack_ptr--;
            vm_mutex_off();
            break;
        case 2:
            {
                int value;
                vm_mutex_on();
                value = *(int *) pc;
                pc += sizeof(int);
                stack_ptr -= value;
                vm_mutex_off();
            }
            break;
        case 3:
            {
                CLVALUE value;
                vm_mutex_on();
                value = *(stack_ptr - 2);
                *(stack_ptr - 2) = *(stack_ptr - 1);
                *(stack_ptr - 1) = value;
                vm_mutex_off();
            }
            break;
        case 4:
            {
                CLVALUE value;
                vm_mutex_on();
                value = *(stack_ptr - 1);
                *stack_ptr = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 5:
            {
                int jump_value;
                int conditional_value;
                vm_mutex_on();
                jump_value = *(int *) pc;
                pc += sizeof(int);
                conditional_value = (stack_ptr - 1)->mBoolValue;
                stack_ptr--;
                if (conditional_value)
                {
                    pc += jump_value;
                }
                vm_mutex_off();
            }
            break;
        case 6:
            {
                int jump_value;
                int conditional_value;
                vm_mutex_on();
                jump_value = *(int *) pc;
                pc += sizeof(int);
                conditional_value = (stack_ptr - 1)->mBoolValue;
                stack_ptr--;
                if (!conditional_value)
                {
                    pc += jump_value;
                }
                vm_mutex_off();
            }
            break;
        case 7:
            {
                int jump_value;
                int label_offset;
                vm_mutex_on();
                jump_value = *(int *) pc;
                pc += sizeof(int);
                label_offset = *(int *) pc;
                pc += sizeof(int);
                pc = code->mCodes + jump_value;
                vm_mutex_off();
            }
            break;
        case 8:
            *(stack + var_num) = *(stack_ptr - 1);
            remove_stack_to_stack_list(stack_id);
            return 1;
        case 9:
            {
                CLObject exception;
                *stack = *(stack_ptr - 1);
                remove_stack_to_stack_list(stack_id);
                exception = stack->mObjectValue;
                entry_exception_object(exception, info);
            }
            return 0;
        case 10:
            {
                int catch_label_name_offset;
                int try_exception_var_index;
                vm_mutex_on();
                info->try_offset = *(int *) pc;
                pc += sizeof(int);
                info->try_code = code;
                catch_label_name_offset = *(int *) pc;
                pc += sizeof(int);
                try_exception_var_index = *(int *) pc;
                pc += sizeof(int);
                vm_mutex_off();
            }
            break;
        case 11:
            vm_mutex_on();
            info->try_code = (void *) 0;
            info->try_offset = 0;
            vm_mutex_off();
            break;
        case 12:
            vm_mutex_on();
            stack_ptr--;
            vm_mutex_off();
            break;
        case 13:
            {
                int index;
                vm_mutex_on();
                index = *(int *) pc;
                pc += sizeof(int);
                lvar[index] = *(stack_ptr - 1);
                vm_mutex_off();
            }
            break;
        case 14:
            vm_mutex_on();
            gSigInt = 0;
            vm_mutex_off();
            break;
        case 15:
            {
                int offset;
                char * sname;
                int sline;
                offset = *(int *) pc;
                pc += sizeof(int);
                sname = (char *) (constant->mConst + offset);
                sline = *(int *) pc;
                pc += sizeof(int);
                info->sname = sname;
                info->sline = sline;
            }
            break;
        case 16:
            {
                int offset;
                char * sname;
                int sline;
                offset = *(int *) pc;
                pc += sizeof(int);
                sname = (char *) (constant->mConst + offset);
                sline = *(int *) pc;
                pc += sizeof(int);
                info->sname2 = sname;
                info->sline2 = sline;
            }
            break;
        case 17:
            vm_mutex_on();
            if (gSigInt)
            {
                gSigInt = 0;
                vm_mutex_off();
                entry_exception_object_with_class_name(&stack_ptr,
                                                       stack,
                                                       var_num,
                                                       info,
                                                       "Exception",
                                                       "Signal Interrupt");
                remove_stack_to_stack_list(stack_id);
                return 0;
            }
            vm_mutex_off();
            break;
        case 18:
            {
                int offset;
                offset = *(int *) pc;
                pc += sizeof(int);
            }
            break;
        case 29:
            {
                CLVALUE value;
                value = *(stack_ptr - 1);
                stack_ptr--;
                push_value_to_global_stack(value);
            }
            break;
        case 30:
            {
                int size;
                CLVALUE value;
                size = *(int *) pc;
                pc += sizeof(int);
                value = pop_global_stack();
                *stack_ptr = value;
                stack_ptr++;
            }
            break;
        case 19:
            break;
        case 21:
            break;
        case 20:
            {
                int size;
                size = *(int *) pc;
                pc += sizeof(int);
            }
            break;
        case 24:
            {
                int offset;
                offset = *(int *) pc;
                pc += sizeof(int);
            }
            break;
        case 26:
            {
                int offset;
                offset = *(int *) pc;
                pc += sizeof(int);
            }
            break;
        case 31:
            {
                int index;
                vm_mutex_on();
                index = *(int *) pc;
                pc += sizeof(int);
                lvar[index] = *(stack_ptr - 1);
                vm_mutex_off();
            }
            break;
        case 32:
            {
                int index;
                int tmp;
                vm_mutex_on();
                index = *(int *) pc;
                pc += sizeof(int);
                tmp = *(int *) pc;
                pc += sizeof(int);
                *stack_ptr = lvar[index];
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 33:
            {
                int index;
                vm_mutex_on();
                index = *(int *) pc;
                pc += sizeof(int);
                stack_ptr->mLongValue = 0;
                stack_ptr->mPointerValue = (char *) &lvar[index];
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 35:
            {
                int value;
                vm_mutex_on();
                value = *(int *) pc;
                pc += sizeof(int);
                stack_ptr->mLongValue = 0;
                stack_ptr->mByteValue = (char) value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 36:
            {
                int value;
                vm_mutex_on();
                value = *(int *) pc;
                pc += sizeof(int);
                stack_ptr->mLongValue = 0;
                stack_ptr->mUByteValue = (unsigned char) value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 37:
            {
                int value;
                vm_mutex_on();
                value = *(int *) pc;
                pc += sizeof(int);
                stack_ptr->mLongValue = 0;
                stack_ptr->mShortValue = (short) value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 38:
            {
                int value;
                vm_mutex_on();
                value = *(int *) pc;
                pc += sizeof(int);
                stack_ptr->mLongValue = 0;
                stack_ptr->mUShortValue = (unsigned short) value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 39:
            {
                int value;
                vm_mutex_on();
                value = *(int *) pc;
                pc += sizeof(int);
                stack_ptr->mLongValue = 0;
                stack_ptr->mIntValue = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 47:
            {
                int value;
                vm_mutex_on();
                value = *(int *) pc;
                pc += sizeof(int);
                stack_ptr->mLongValue = 0;
                stack_ptr->mIntValue = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 40:
            {
                unsigned int value;
                vm_mutex_on();
                value = *(unsigned int *) pc;
                pc += sizeof(int);
                stack_ptr->mLongValue = 0;
                stack_ptr->mUIntValue = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 41:
            {
                int value1;
                int value2;
                long long lvalue;
                vm_mutex_on();
                value1 = *(int *) pc;
                pc += sizeof(int);
                value2 = *(int *) pc;
                pc += sizeof(int);
                memcpy(&lvalue, &value1, sizeof(int));
                memcpy((char *) &lvalue + sizeof(int), &value2, sizeof(int));
                stack_ptr->mLongValue = lvalue;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 42:
            {
                int value1;
                int value2;
                unsigned long long lvalue;
                vm_mutex_on();
                value1 = *(int *) pc;
                pc += sizeof(int);
                value2 = *(int *) pc;
                pc += sizeof(int);
                memcpy(&lvalue, &value1, sizeof(int));
                memcpy((char *) &lvalue + sizeof(int), &value2, sizeof(int));
                stack_ptr->mULongValue = lvalue;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 43:
            {
                vm_mutex_on();
                stack_ptr->mLongValue = 0;
                stack_ptr->mIntValue = 0;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 44:
            {
                int value1;
                int value2;
                void * lvalue;
                vm_mutex_on();
                value1 = *(int *) pc;
                pc += sizeof(int);
                value2 = *(int *) pc;
                pc += sizeof(int);
                memcpy(&lvalue, &value1, sizeof(int));
                memcpy((char *) &lvalue + sizeof(int), &value2, sizeof(int));
                stack_ptr->mLongValue = 0;
                stack_ptr->mPointerValue = lvalue;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 45:
            {
                float value1;
                vm_mutex_on();
                value1 = *(float *) pc;
                pc += sizeof(float);
                stack_ptr->mLongValue = 0;
                stack_ptr->mFloatValue = value1;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 46:
            {
                int value1;
                int value2;
                double lvalue;
                vm_mutex_on();
                value1 = *(int *) pc;
                pc += sizeof(int);
                value2 = *(int *) pc;
                pc += sizeof(int);
                memcpy(&lvalue, &value1, sizeof(int));
                memcpy((char *) &lvalue + sizeof(int), &value2, sizeof(int));
                stack_ptr->mDoubleValue = lvalue;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 50:
            {
                char left;
                char right;
                char result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mByteValue;
                right = (stack_ptr - 1)->mByteValue;
                result = left + right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mByteValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 51:
            {
                char left;
                char right;
                char result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mByteValue;
                right = (stack_ptr - 1)->mByteValue;
                result = left - right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mByteValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 52:
            {
                char left;
                char right;
                char result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mByteValue;
                right = (stack_ptr - 1)->mByteValue;
                result = left * right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mByteValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 53:
            {
                char left;
                char right;
                char result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mByteValue;
                right = (stack_ptr - 1)->mByteValue;
                if (right == 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "division by zero");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                result = left / right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mByteValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 54:
            {
                char left;
                char right;
                char result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mByteValue;
                right = (stack_ptr - 1)->mByteValue;
                if (right == 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "division by zero");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                result = left % right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mByteValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 55:
            {
                char left;
                char right;
                char result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mByteValue;
                right = (stack_ptr - 1)->mByteValue;
                result = left << right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mByteValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 56:
            {
                char left;
                char right;
                char result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mByteValue;
                right = (stack_ptr - 1)->mByteValue;
                result = left >> right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mByteValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 57:
            {
                char left;
                char right;
                char result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mByteValue;
                right = (stack_ptr - 1)->mByteValue;
                result = left & right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mByteValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 58:
            {
                char left;
                char right;
                char result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mByteValue;
                right = (stack_ptr - 1)->mByteValue;
                result = left ^ right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mByteValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 59:
            {
                char left;
                char right;
                char result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mByteValue;
                right = (stack_ptr - 1)->mByteValue;
                result = left | right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mByteValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 80:
            {
                unsigned char left;
                unsigned char right;
                unsigned char result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mByteValue;
                right = (stack_ptr - 1)->mByteValue;
                result = left + right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUByteValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 81:
            {
                unsigned char left;
                unsigned char right;
                unsigned char result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mByteValue;
                right = (stack_ptr - 1)->mByteValue;
                result = left - right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUByteValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 82:
            {
                unsigned char left;
                unsigned char right;
                unsigned char result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mByteValue;
                right = (stack_ptr - 1)->mByteValue;
                result = left * right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUByteValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 83:
            {
                unsigned char left;
                unsigned char right;
                unsigned char result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mByteValue;
                right = (stack_ptr - 1)->mByteValue;
                if (right == 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "division by zero");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                result = left / right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUByteValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 84:
            {
                unsigned char left;
                unsigned char right;
                unsigned char result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mByteValue;
                right = (stack_ptr - 1)->mByteValue;
                if (right == 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "division by zero");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                result = left % right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUByteValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 85:
            {
                unsigned char left;
                unsigned char right;
                unsigned char result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mByteValue;
                right = (stack_ptr - 1)->mByteValue;
                result = left << right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUByteValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 86:
            {
                unsigned char left;
                unsigned char right;
                unsigned char result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mByteValue;
                right = (stack_ptr - 1)->mByteValue;
                result = left >> right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUByteValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 87:
            {
                unsigned char left;
                unsigned char right;
                unsigned char result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mByteValue;
                right = (stack_ptr - 1)->mByteValue;
                result = left & right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUByteValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 88:
            {
                unsigned char left;
                unsigned char right;
                unsigned char result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mByteValue;
                right = (stack_ptr - 1)->mByteValue;
                result = left ^ right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUByteValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 89:
            {
                unsigned char left;
                unsigned char right;
                unsigned char result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mByteValue;
                right = (stack_ptr - 1)->mByteValue;
                result = left | right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUByteValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 100:
            {
                short left;
                short right;
                short result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mShortValue;
                right = (stack_ptr - 1)->mShortValue;
                result = left + right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mShortValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 101:
            {
                short left;
                short right;
                short result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mShortValue;
                right = (stack_ptr - 1)->mShortValue;
                result = left - right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mShortValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 102:
            {
                short left;
                short right;
                short result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mShortValue;
                right = (stack_ptr - 1)->mShortValue;
                result = left * right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mShortValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 103:
            {
                short left;
                short right;
                short result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mShortValue;
                right = (stack_ptr - 1)->mShortValue;
                if (right == 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "division by zero");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                result = left / right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mShortValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 104:
            {
                short left;
                short right;
                short result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mShortValue;
                right = (stack_ptr - 1)->mShortValue;
                if (right == 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "division by zero");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                result = left % right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mShortValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 105:
            {
                short left;
                short right;
                short result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mShortValue;
                right = (stack_ptr - 1)->mShortValue;
                result = left << right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mShortValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 106:
            {
                short left;
                short right;
                short result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mShortValue;
                right = (stack_ptr - 1)->mShortValue;
                result = left >> right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mShortValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 107:
            {
                short left;
                short right;
                short result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mShortValue;
                right = (stack_ptr - 1)->mShortValue;
                result = left & right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mShortValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 108:
            {
                short left;
                short right;
                short result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mShortValue;
                right = (stack_ptr - 1)->mShortValue;
                result = left ^ right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mShortValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 109:
            {
                short left;
                short right;
                short result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mShortValue;
                right = (stack_ptr - 1)->mShortValue;
                result = left | right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mShortValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 150:
            {
                unsigned short left;
                unsigned short right;
                unsigned short result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUShortValue;
                right = (stack_ptr - 1)->mUShortValue;
                result = left + right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUShortValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 151:
            {
                unsigned short left;
                unsigned short right;
                unsigned short result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUShortValue;
                right = (stack_ptr - 1)->mUShortValue;
                result = left - right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUShortValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 152:
            {
                unsigned short left;
                unsigned short right;
                unsigned short result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUShortValue;
                right = (stack_ptr - 1)->mUShortValue;
                result = left * right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUShortValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 153:
            {
                unsigned short left;
                unsigned short right;
                unsigned short result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUShortValue;
                right = (stack_ptr - 1)->mUShortValue;
                if (right == 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "division by zero");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                result = left / right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUShortValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 154:
            {
                unsigned short left;
                unsigned short right;
                unsigned short result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUShortValue;
                right = (stack_ptr - 1)->mUShortValue;
                if (right == 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "division by zero");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                result = left % right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUShortValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 155:
            {
                unsigned short left;
                unsigned short right;
                unsigned short result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUShortValue;
                right = (stack_ptr - 1)->mUShortValue;
                result = left << right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUShortValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 156:
            {
                unsigned short left;
                unsigned short right;
                unsigned short result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUShortValue;
                right = (stack_ptr - 1)->mUShortValue;
                result = left >> right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUShortValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 157:
            {
                unsigned short left;
                unsigned short right;
                unsigned short result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUShortValue;
                right = (stack_ptr - 1)->mUShortValue;
                result = left & right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUShortValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 158:
            {
                unsigned short left;
                unsigned short right;
                unsigned short result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUShortValue;
                right = (stack_ptr - 1)->mUShortValue;
                result = left ^ right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUShortValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 159:
            {
                unsigned short left;
                unsigned short right;
                unsigned short result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUShortValue;
                right = (stack_ptr - 1)->mUShortValue;
                result = left | right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUShortValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 200:
            {
                int left;
                int right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mIntValue;
                right = (stack_ptr - 1)->mIntValue;
                result = left + right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mIntValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 201:
            {
                int left;
                int right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mIntValue;
                right = (stack_ptr - 1)->mIntValue;
                result = left - right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mIntValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 202:
            {
                int left;
                int right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mIntValue;
                right = (stack_ptr - 1)->mIntValue;
                result = left * right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mIntValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 203:
            {
                int left;
                int right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mIntValue;
                right = (stack_ptr - 1)->mIntValue;
                if (right == 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "division by zero");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                result = left / right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mIntValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 204:
            {
                int left;
                int right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mIntValue;
                right = (stack_ptr - 1)->mIntValue;
                if (right == 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "division by zero");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                result = left % right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mIntValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 205:
            {
                int left;
                int right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mIntValue;
                right = (stack_ptr - 1)->mIntValue;
                result = left << right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mIntValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 206:
            {
                int left;
                int right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mIntValue;
                right = (stack_ptr - 1)->mIntValue;
                result = left >> right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mIntValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 207:
            {
                int left;
                int right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mIntValue;
                right = (stack_ptr - 1)->mIntValue;
                result = left & right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mIntValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 208:
            {
                int left;
                int right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mIntValue;
                right = (stack_ptr - 1)->mIntValue;
                result = left ^ right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mIntValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 209:
            {
                int left;
                int right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mIntValue;
                right = (stack_ptr - 1)->mIntValue;
                result = left | right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mIntValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 251:
            {
                unsigned int left;
                unsigned int right;
                unsigned int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUIntValue;
                right = (stack_ptr - 1)->mUIntValue;
                result = left + right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUIntValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 250:
            {
                unsigned int left;
                unsigned int right;
                unsigned int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUIntValue;
                right = (stack_ptr - 1)->mUIntValue;
                result = left - right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUIntValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 252:
            {
                unsigned int left;
                unsigned int right;
                unsigned int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUIntValue;
                right = (stack_ptr - 1)->mUIntValue;
                result = left * right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUIntValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 253:
            {
                unsigned int left;
                unsigned int right;
                unsigned int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUIntValue;
                right = (stack_ptr - 1)->mUIntValue;
                if (right == 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "division by zero");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                result = left / right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUIntValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 254:
            {
                unsigned int left;
                unsigned int right;
                unsigned int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUIntValue;
                right = (stack_ptr - 1)->mUIntValue;
                if (right == 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "division by zero");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                result = left % right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUIntValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 255:
            {
                unsigned int left;
                unsigned int right;
                unsigned int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUIntValue;
                right = (stack_ptr - 1)->mUIntValue;
                result = left << right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUIntValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 256:
            {
                unsigned int left;
                unsigned int right;
                unsigned int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUIntValue;
                right = (stack_ptr - 1)->mUIntValue;
                result = left >> right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUIntValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 257:
            {
                unsigned int left;
                unsigned int right;
                unsigned int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUIntValue;
                right = (stack_ptr - 1)->mUIntValue;
                result = left & right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUIntValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 258:
            {
                unsigned int left;
                unsigned int right;
                unsigned int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUIntValue;
                right = (stack_ptr - 1)->mUIntValue;
                result = left ^ right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUIntValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 259:
            {
                unsigned int left;
                unsigned int right;
                unsigned int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUIntValue;
                right = (stack_ptr - 1)->mUIntValue;
                result = left | right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUIntValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 300:
            {
                long long left;
                long long right;
                long long result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mLongValue;
                right = (stack_ptr - 1)->mLongValue;
                result = left + right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 301:
            {
                long long left;
                long long right;
                long long result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mLongValue;
                right = (stack_ptr - 1)->mLongValue;
                result = left - right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 302:
            {
                long long left;
                long long right;
                long long result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mLongValue;
                right = (stack_ptr - 1)->mLongValue;
                result = left * right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 303:
            {
                long long left;
                long long right;
                long long result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mLongValue;
                right = (stack_ptr - 1)->mLongValue;
                if (right == 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "division by zero");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                result = left / right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 304:
            {
                long long left;
                long long right;
                long long result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mLongValue;
                right = (stack_ptr - 1)->mLongValue;
                if (right == 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "division by zero");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                result = left % right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 305:
            {
                long long left;
                long long right;
                long long result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mLongValue;
                right = (stack_ptr - 1)->mLongValue;
                result = left << right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 306:
            {
                long long left;
                long long right;
                long long result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mLongValue;
                right = (stack_ptr - 1)->mLongValue;
                result = left >> right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 307:
            {
                long long left;
                long long right;
                long long result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mLongValue;
                right = (stack_ptr - 1)->mLongValue;
                result = left & right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 308:
            {
                long long left;
                long long right;
                long long result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mLongValue;
                right = (stack_ptr - 1)->mLongValue;
                result = left ^ right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 309:
            {
                long long left;
                long long right;
                long long result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mLongValue;
                right = (stack_ptr - 1)->mLongValue;
                result = left | right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 400:
            {
                unsigned long long left;
                unsigned long long right;
                unsigned long long result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mULongValue;
                right = (stack_ptr - 1)->mULongValue;
                result = left + right;
                stack_ptr -= 2;
                stack_ptr->mULongValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 401:
            {
                unsigned long long left;
                unsigned long long right;
                unsigned long long result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mULongValue;
                right = (stack_ptr - 1)->mULongValue;
                result = left - right;
                stack_ptr -= 2;
                stack_ptr->mULongValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 402:
            {
                unsigned long long left;
                unsigned long long right;
                unsigned long long result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mULongValue;
                right = (stack_ptr - 1)->mULongValue;
                result = left * right;
                stack_ptr -= 2;
                stack_ptr->mULongValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 403:
            {
                unsigned long long left;
                unsigned long long right;
                unsigned long long result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mULongValue;
                right = (stack_ptr - 1)->mULongValue;
                if (right == 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "division by zero");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                result = left / right;
                stack_ptr -= 2;
                stack_ptr->mULongValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 404:
            {
                unsigned long long left;
                unsigned long long right;
                unsigned long long result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mULongValue;
                right = (stack_ptr - 1)->mULongValue;
                if (right == 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "division by zero");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                result = left % right;
                stack_ptr -= 2;
                stack_ptr->mULongValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 405:
            {
                unsigned long long left;
                unsigned long long right;
                unsigned long long result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mULongValue;
                right = (stack_ptr - 1)->mULongValue;
                result = left << right;
                stack_ptr -= 2;
                stack_ptr->mULongValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 406:
            {
                unsigned long long left;
                unsigned long long right;
                unsigned long long result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mULongValue;
                right = (stack_ptr - 1)->mULongValue;
                result = left >> right;
                stack_ptr -= 2;
                stack_ptr->mULongValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 407:
            {
                unsigned long long left;
                unsigned long long right;
                unsigned long long result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mULongValue;
                right = (stack_ptr - 1)->mULongValue;
                result = left | right;
                stack_ptr -= 2;
                stack_ptr->mULongValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 408:
            {
                unsigned long long left;
                unsigned long long right;
                unsigned long long result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mULongValue;
                right = (stack_ptr - 1)->mULongValue;
                result = left ^ right;
                stack_ptr -= 2;
                stack_ptr->mULongValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 409:
            {
                unsigned long long left;
                unsigned long long right;
                unsigned long long result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mULongValue;
                right = (stack_ptr - 1)->mULongValue;
                result = left | right;
                stack_ptr -= 2;
                stack_ptr->mULongValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 420:
            {
                char value;
                vm_mutex_on();
                value = (stack_ptr - 1)->mByteValue;
                value = ~value;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mByteValue = value;
                vm_mutex_off();
            }
            break;
        case 421:
            {
                unsigned char value;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUByteValue;
                value = ~value;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUByteValue = value;
                vm_mutex_off();
            }
            break;
        case 422:
            {
                short value;
                vm_mutex_on();
                value = (stack_ptr - 1)->mShortValue;
                value = ~value;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mShortValue = value;
                vm_mutex_off();
            }
            break;
        case 423:
            {
                unsigned short value;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUShortValue;
                value = ~value;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUShortValue = value;
                vm_mutex_off();
            }
            break;
        case 424:
            {
                int value;
                vm_mutex_on();
                value = (stack_ptr - 1)->mIntValue;
                value = ~value;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mIntValue = value;
                vm_mutex_off();
            }
            break;
        case 425:
            {
                unsigned int value;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUIntValue;
                value = ~value;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mIntValue = value;
                vm_mutex_off();
            }
            break;
        case 426:
            {
                long long value;
                vm_mutex_on();
                value = (stack_ptr - 1)->mLongValue;
                value = ~value;
                (stack_ptr - 1)->mLongValue = value;
                vm_mutex_off();
            }
            break;
        case 427:
            {
                unsigned long long value;
                vm_mutex_on();
                value = (stack_ptr - 1)->mULongValue;
                value = ~value;
                (stack_ptr - 1)->mULongValue = value;
                vm_mutex_off();
            }
            break;
        case 450:
            {
                float left;
                float right;
                float result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mFloatValue;
                right = (stack_ptr - 1)->mFloatValue;
                result = left + right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mFloatValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 451:
            {
                float left;
                float right;
                float result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mFloatValue;
                right = (stack_ptr - 1)->mFloatValue;
                result = left - right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mFloatValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 452:
            {
                float left;
                float right;
                float result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mFloatValue;
                right = (stack_ptr - 1)->mFloatValue;
                result = left * right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mFloatValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 453:
            {
                float left;
                float right;
                float result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mFloatValue;
                right = (stack_ptr - 1)->mFloatValue;
                if (right == 0.0f)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "division by zero");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                result = left / right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mFloatValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 500:
            {
                double left;
                double right;
                double result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mDoubleValue;
                right = (stack_ptr - 1)->mDoubleValue;
                result = left + right;
                stack_ptr -= 2;
                stack_ptr->mDoubleValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 501:
            {
                double left;
                double right;
                double result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mDoubleValue;
                right = (stack_ptr - 1)->mDoubleValue;
                result = left - right;
                stack_ptr -= 2;
                stack_ptr->mDoubleValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 502:
            {
                double left;
                double right;
                double result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mDoubleValue;
                right = (stack_ptr - 1)->mDoubleValue;
                result = left * right;
                stack_ptr -= 2;
                stack_ptr->mDoubleValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 503:
            {
                double left;
                double right;
                double result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mDoubleValue;
                right = (stack_ptr - 1)->mDoubleValue;
                if (right == 0.0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "division by zero");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                result = left / right;
                stack_ptr -= 2;
                stack_ptr->mDoubleValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 600:
            {
                char * left;
                unsigned long long right;
                char * result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mPointerValue;
                right = (stack_ptr - 1)->mULongValue;
                result = left + right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mPointerValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 601:
            {
                char * left;
                unsigned long long right;
                char * result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mPointerValue;
                right = (stack_ptr - 1)->mULongValue;
                result = left - right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mPointerValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 602:
            {
                char * left;
                char * right;
                unsigned long long result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mPointerValue;
                right = (stack_ptr - 1)->mPointerValue;
                result = left - right;
                stack_ptr -= 2;
                stack_ptr->mULongValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 700:
            {
                wchar_t left;
                wchar_t right;
                wchar_t result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mCharValue;
                right = (stack_ptr - 1)->mCharValue;
                result = left + right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mCharValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 701:
            {
                wchar_t left;
                int right;
                wchar_t result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mCharValue;
                right = (stack_ptr - 1)->mIntValue;
                result = left - right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mCharValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1000:
            {
                char left;
                char right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mByteValue;
                right = (stack_ptr - 1)->mByteValue;
                result = left == right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1001:
            {
                char left;
                char right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mByteValue;
                right = (stack_ptr - 1)->mByteValue;
                result = left != right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1002:
            {
                char left;
                char right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mByteValue;
                right = (stack_ptr - 1)->mByteValue;
                result = left > right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1003:
            {
                char left;
                char right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mByteValue;
                right = (stack_ptr - 1)->mByteValue;
                result = left < right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1004:
            {
                char left;
                char right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mByteValue;
                right = (stack_ptr - 1)->mByteValue;
                result = left >= right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1005:
            {
                char left;
                char right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mByteValue;
                right = (stack_ptr - 1)->mByteValue;
                result = left <= right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1010:
            {
                unsigned char left;
                unsigned char right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUByteValue;
                right = (stack_ptr - 1)->mUByteValue;
                result = left == right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1011:
            {
                unsigned char left;
                unsigned char right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUByteValue;
                right = (stack_ptr - 1)->mUByteValue;
                result = left != right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1012:
            {
                unsigned char left;
                unsigned char right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUByteValue;
                right = (stack_ptr - 1)->mUByteValue;
                result = left > right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1013:
            {
                unsigned char left;
                unsigned char right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUByteValue;
                right = (stack_ptr - 1)->mUByteValue;
                result = left < right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1014:
            {
                unsigned char left;
                unsigned char right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUByteValue;
                right = (stack_ptr - 1)->mUByteValue;
                result = left >= right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1015:
            {
                unsigned char left;
                unsigned char right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUByteValue;
                right = (stack_ptr - 1)->mUByteValue;
                result = left <= right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1020:
            {
                short left;
                short right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mShortValue;
                right = (stack_ptr - 1)->mShortValue;
                result = left == right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1021:
            {
                short left;
                short right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mShortValue;
                right = (stack_ptr - 1)->mShortValue;
                result = left != right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1022:
            {
                short left;
                short right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mShortValue;
                right = (stack_ptr - 1)->mShortValue;
                result = left > right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1023:
            {
                short left;
                short right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mShortValue;
                right = (stack_ptr - 1)->mShortValue;
                result = left < right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1024:
            {
                short left;
                short right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mShortValue;
                right = (stack_ptr - 1)->mShortValue;
                result = left >= right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1025:
            {
                short left;
                short right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mShortValue;
                right = (stack_ptr - 1)->mShortValue;
                result = left <= right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1030:
            {
                unsigned short left;
                unsigned short right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUShortValue;
                right = (stack_ptr - 1)->mUShortValue;
                result = left == right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1031:
            {
                unsigned short left;
                unsigned short right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mShortValue;
                right = (stack_ptr - 1)->mShortValue;
                result = left != right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1032:
            {
                unsigned short left;
                unsigned short right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUShortValue;
                right = (stack_ptr - 1)->mUShortValue;
                result = left > right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1033:
            {
                unsigned short left;
                unsigned short right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUShortValue;
                right = (stack_ptr - 1)->mUShortValue;
                result = left < right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1034:
            {
                unsigned short left;
                unsigned short right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUShortValue;
                right = (stack_ptr - 1)->mUShortValue;
                result = left >= right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1035:
            {
                unsigned short left;
                unsigned short right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUShortValue;
                right = (stack_ptr - 1)->mUShortValue;
                result = left <= right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1040:
            {
                int left;
                int right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mIntValue;
                right = (stack_ptr - 1)->mIntValue;
                result = left == right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1041:
            {
                int left;
                int right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mIntValue;
                right = (stack_ptr - 1)->mIntValue;
                result = left != right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1042:
            {
                int left;
                int right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mIntValue;
                right = (stack_ptr - 1)->mIntValue;
                result = left > right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1043:
            {
                int left;
                int right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mIntValue;
                right = (stack_ptr - 1)->mIntValue;
                result = left < right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1044:
            {
                int left;
                int right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mIntValue;
                right = (stack_ptr - 1)->mIntValue;
                result = left >= right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1045:
            {
                int left;
                int right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mIntValue;
                right = (stack_ptr - 1)->mIntValue;
                result = left <= right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1050:
            {
                unsigned int left;
                unsigned int right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUIntValue;
                right = (stack_ptr - 1)->mUIntValue;
                result = left == right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1051:
            {
                unsigned int left;
                unsigned int right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUIntValue;
                right = (stack_ptr - 1)->mUIntValue;
                result = left != right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1052:
            {
                unsigned int left;
                unsigned int right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUIntValue;
                right = (stack_ptr - 1)->mUIntValue;
                result = left > right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1053:
            {
                unsigned int left;
                unsigned int right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUIntValue;
                right = (stack_ptr - 1)->mUIntValue;
                result = left < right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1054:
            {
                unsigned int left;
                unsigned int right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUIntValue;
                right = (stack_ptr - 1)->mUIntValue;
                result = left >= right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1055:
            {
                unsigned int left;
                unsigned int right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mUIntValue;
                right = (stack_ptr - 1)->mUIntValue;
                result = left <= right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1060:
            {
                long long left;
                long long right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mLongValue;
                right = (stack_ptr - 1)->mLongValue;
                result = left == right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1061:
            {
                long long left;
                long long right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mLongValue;
                right = (stack_ptr - 1)->mLongValue;
                result = left != right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1062:
            {
                long long left;
                long long right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mLongValue;
                right = (stack_ptr - 1)->mLongValue;
                result = left > right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1063:
            {
                long long left;
                long long right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mLongValue;
                right = (stack_ptr - 1)->mLongValue;
                result = left < right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1064:
            {
                long long left;
                long long right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mLongValue;
                right = (stack_ptr - 1)->mLongValue;
                result = left >= right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1065:
            {
                long long left;
                long long right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mLongValue;
                right = (stack_ptr - 1)->mLongValue;
                result = left <= right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1070:
            {
                unsigned long long left;
                unsigned long long right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mULongValue;
                right = (stack_ptr - 1)->mULongValue;
                result = left == right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1071:
            {
                unsigned long long left;
                unsigned long long right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mULongValue;
                right = (stack_ptr - 1)->mULongValue;
                result = left != right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1072:
            {
                unsigned long long left;
                unsigned long long right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mULongValue;
                right = (stack_ptr - 1)->mULongValue;
                result = left > right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1073:
            {
                unsigned long long left;
                unsigned long long right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mULongValue;
                right = (stack_ptr - 1)->mULongValue;
                result = left < right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1074:
            {
                unsigned long long left;
                unsigned long long right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mULongValue;
                right = (stack_ptr - 1)->mULongValue;
                result = left >= right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1075:
            {
                unsigned long long left;
                unsigned long long right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mULongValue;
                right = (stack_ptr - 1)->mULongValue;
                result = left <= right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1080:
            {
                float left;
                float right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mFloatValue;
                right = (stack_ptr - 1)->mFloatValue;
                result = left == right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1081:
            {
                float left;
                float right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mFloatValue;
                right = (stack_ptr - 1)->mFloatValue;
                result = left != right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1082:
            {
                float left;
                float right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mFloatValue;
                right = (stack_ptr - 1)->mFloatValue;
                result = left > right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1083:
            {
                float left;
                float right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mFloatValue;
                right = (stack_ptr - 1)->mFloatValue;
                result = left < right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1084:
            {
                float left;
                float right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mFloatValue;
                right = (stack_ptr - 1)->mFloatValue;
                result = left >= right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1085:
            {
                float left;
                float right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mFloatValue;
                right = (stack_ptr - 1)->mFloatValue;
                result = left <= right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1090:
            {
                double left;
                double right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mDoubleValue;
                right = (stack_ptr - 1)->mDoubleValue;
                result = left == right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1091:
            {
                double left;
                double right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mDoubleValue;
                right = (stack_ptr - 1)->mDoubleValue;
                result = left != right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 1092:
            {
                double left;
                double right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mDoubleValue;
                right = (stack_ptr - 1)->mDoubleValue;
                result = left > right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1093:
            {
                double left;
                double right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mDoubleValue;
                right = (stack_ptr - 1)->mDoubleValue;
                result = left < right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1094:
            {
                double left;
                double right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mDoubleValue;
                right = (stack_ptr - 1)->mDoubleValue;
                result = left >= right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1095:
            {
                double left;
                double right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mDoubleValue;
                right = (stack_ptr - 1)->mDoubleValue;
                result = left <= right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1100:
            {
                char * left;
                char * right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mPointerValue;
                right = (stack_ptr - 1)->mPointerValue;
                result = left == right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1101:
            {
                char * left;
                char * right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mPointerValue;
                right = (stack_ptr - 1)->mPointerValue;
                result = left != right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1102:
            {
                char * left;
                char * right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mPointerValue;
                right = (stack_ptr - 1)->mPointerValue;
                result = left > right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1103:
            {
                char * left;
                char * right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mPointerValue;
                right = (stack_ptr - 1)->mPointerValue;
                result = left < right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1104:
            {
                char * left;
                char * right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mPointerValue;
                right = (stack_ptr - 1)->mPointerValue;
                result = left >= right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1105:
            {
                char * left;
                char * right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mPointerValue;
                right = (stack_ptr - 1)->mPointerValue;
                result = left <= right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1200:
            {
                wchar_t left;
                wchar_t right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mCharValue;
                right = (stack_ptr - 1)->mCharValue;
                result = left == right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1201:
            {
                wchar_t left;
                wchar_t right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mCharValue;
                right = (stack_ptr - 1)->mCharValue;
                result = left != right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1202:
            {
                wchar_t left;
                wchar_t right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mCharValue;
                right = (stack_ptr - 1)->mCharValue;
                result = left > right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1203:
            {
                wchar_t left;
                wchar_t right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mCharValue;
                right = (stack_ptr - 1)->mCharValue;
                result = left < right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1204:
            {
                wchar_t left;
                wchar_t right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mCharValue;
                right = (stack_ptr - 1)->mCharValue;
                result = left >= right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1205:
            {
                wchar_t left;
                wchar_t right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mCharValue;
                right = (stack_ptr - 1)->mCharValue;
                result = left <= right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1220:
            {
                CLObject left;
                CLObject right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mObjectValue;
                right = (stack_ptr - 1)->mObjectValue;
                result = regex_equals(left, right);
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1221:
            {
                CLObject left;
                CLObject right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mObjectValue;
                right = (stack_ptr - 1)->mObjectValue;
                result = !regex_equals(left, right);
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1300:
            {
                CLObject left;
                CLObject right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mObjectValue;
                right = (stack_ptr - 1)->mObjectValue;
                result = left == right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1301:
            {
                CLObject left;
                sCLObject * object_data;
                CLObject result;
                vm_mutex_on();
                left = (stack_ptr - 1)->mObjectValue;
                if (left == 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "Null pointer exception(1)");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                object_data = (sCLObject *) get_object_pointer(left);
                result = create_string_object(object_data->mType);
                stack_ptr--;
                stack_ptr->mLongValue = 0;
                stack_ptr->mObjectValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 1302:
            {
                CLObject left;
                CLObject right;
                sCLObject * object_data;
                char * left_class_name;
                char * right_class_name;
                vm_mutex_on();
                left = (stack_ptr - 2)->mObjectValue;
                right = (stack_ptr - 1)->mObjectValue;
                if (left == 0 || right == 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "Null pointer exception(1)");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                object_data = (sCLObject *) get_object_pointer(left);
                left_class_name = object_data->mType;
                right_class_name = string_object_to_char_array(right);
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = strcmp(left_class_name,
                                               right_class_name) == 0;
                stack_ptr++;
                xfree(right_class_name);
                vm_mutex_off();
            }
            break;
        case 1303:
            {
                int offset;
                char * class_name;
                sCLClass * klass;
                CLObject left;
                int result;
                vm_mutex_on();
                offset = *(int *) pc;
                pc += sizeof(int);
                class_name = (char *) (constant->mConst + offset);
                klass = get_class_with_load_and_initialize(class_name);
                if (klass == (void *) 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "class not found(1)");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                left = (stack_ptr - 1)->mObjectValue;
                if (left == 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "Null pointer exception(2)");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                result = object_implements_interface(left, klass);
                stack_ptr--;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 2000:
            {
                int left;
                int right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mBoolValue;
                right = (stack_ptr - 1)->mBoolValue;
                result = left && right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 2001:
            {
                int left;
                int right;
                int result;
                vm_mutex_on();
                left = (stack_ptr - 2)->mBoolValue;
                right = (stack_ptr - 1)->mBoolValue;
                result = left || right;
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 2002:
            {
                int value;
                int result;
                vm_mutex_on();
                value = (stack_ptr - 1)->mBoolValue;
                result = !value;
                stack_ptr--;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = result;
                stack_ptr++;
                vm_mutex_on();
            }
            break;
        case 3000:
            {
                int offset;
                int method_index;
                int size;
                char * class_name;
                sCLClass * klass;
                sCLMethod * method;
                vm_mutex_on();
                offset = *(int *) pc;
                pc += sizeof(int);
                method_index = *(int *) pc;
                pc += sizeof(int);
                size = *(int *) pc;
                pc += sizeof(int);
                class_name = (char *) (constant->mConst + offset);
                klass = get_class_with_load_and_initialize(class_name);
                if (klass == (void *) 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "class not found(2)");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                if (method_index < 0 || method_index >= klass->mNumMethods)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "OP_INVOKE_METHOD: Method not found");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                method = klass->mMethods + method_index;
                if (!invoke_method(klass,
                                   method,
                                   stack,
                                   var_num,
                                   &stack_ptr,
                                   info))
                {
                    if (info->try_code == code && info->try_offset != 0)
                    {
                        pc = code->mCodes + info->try_offset;
                        info->try_offset = 0;
                        info->try_code = (void *) 0;
                    }
                    else
                    {
                        vm_mutex_off();
                        remove_stack_to_stack_list(stack_id);
                        return 0;
                    }
                }
                vm_mutex_off();
            }
            break;
        case 3001:
            {
                int num_real_params;
                int offset;
                int size;
                CLObject object;
                sCLObject * object_data;
                sCLClass * klass;
                char * method_name_and_params;
                char method_name_and_params2[64 + num_real_params * 64 + 128];
                sCLMethod * method;
                vm_mutex_on();
                num_real_params = *(int *) pc;
                pc += sizeof(int);
                offset = *(int *) pc;
                pc += sizeof(int);
                size = *(int *) pc;
                pc += sizeof(int);
                object = (stack_ptr - num_real_params)->mObjectValue;
                if (object == 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "Null pointer exception(3-1)");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                object_data = (sCLObject *) get_object_pointer(object);
                klass = object_data->mClass;
                ;
                method_name_and_params = (char *) (constant->mConst + offset);
                Self_convertion_of_method_name_and_params(method_name_and_params,
                                                          method_name_and_params2,
                                                          (char *) ((&klass->mConst)->mConst + klass->mClassNameOffset));
                method = search_for_method_from_virtual_method_table(klass,
                                                                     method_name_and_params2);
                if (method == (void *) 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "OP_INVOKE_VIRTUAL_METHOD: Method not found(%s.%s)",
                                                           (char *) ((&klass->mConst)->mConst + klass->mClassNameOffset),
                                                           method_name_and_params);
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                else
                {
                    if (!invoke_method(klass,
                                       method,
                                       stack,
                                       var_num,
                                       &stack_ptr,
                                       info))
                    {
                        if (info->try_code == code && info->try_offset != 0)
                        {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = (void *) 0;
                        }
                        else
                        {
                            vm_mutex_off();
                            remove_stack_to_stack_list(stack_id);
                            return 0;
                        }
                    }
                }
                vm_mutex_off();
            }
            break;
        case 3002:
            {
                int offset;
                int offset2;
                int num_params;
                int static_;
                int num_method_chains;
                int max_method_chains;
                int size;
                vm_mutex_on();
                offset = *(int *) pc;
                pc += sizeof(int);
                offset2 = *(int *) pc;
                pc += sizeof(int);
                num_params = *(int *) pc;
                pc += sizeof(int);
                static_ = *(int *) pc;
                pc += sizeof(int);
                num_method_chains = *(int *) pc;
                pc += sizeof(int);
                max_method_chains = *(int *) pc;
                pc += sizeof(int);
                size = *(int *) pc;
                pc += sizeof(int);
                if (static_ == 0)
                {
                    int num_real_params;
                    char * method_name;
                    CLObject object;
                    sCLObject * object_data;
                    sCLClass * klass;
                    sCLMethod * method;
                    CLObject elements[256];
                    int i;
                    CLObject carray;
                    CLVALUE cl_value;
                    num_real_params = num_params + 1;
                    method_name = (char *) (constant->mConst + offset2);
                    object = (stack_ptr - num_real_params)->mObjectValue;
                    object_data = (sCLObject *) get_object_pointer(object);
                    klass = object_data->mClass;
                    ;
                    if (klass->mCallingMethodIndex == -1)
                    {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr,
                                                               stack,
                                                               var_num,
                                                               info,
                                                               "Exception",
                                                               "OP_INVOKE_DYNAMIC_METHOD: Method not found(1)");
                        remove_stack_to_stack_list(stack_id);
                        return 0;
                    }
                    method = klass->mMethods + klass->mCallingMethodIndex;
                    for (i = 0; i < num_params; i++)
                    {
                        CLObject object;
                        object = (stack_ptr - num_params + i)->mObjectValue;
                        elements[i] = object;
                    }
                    carray = create_carray_object_with_elements(num_params, elements);
                    cl_value.mLongValue = 0;
                    cl_value.mObjectValue = carray;
                    push_value_to_global_stack(cl_value);
                    stack_ptr -= num_params;
                    stack_ptr->mLongValue = 0;
                    stack_ptr->mObjectValue = create_string_object(method_name);
                    stack_ptr++;
                    stack_ptr->mLongValue = 0;
                    stack_ptr->mObjectValue = carray;
                    stack_ptr++;
                    stack_ptr->mLongValue = 0;
                    stack_ptr->mIntValue = num_method_chains;
                    stack_ptr++;
                    stack_ptr->mLongValue = 0;
                    stack_ptr->mIntValue = max_method_chains;
                    stack_ptr++;
                    pop_global_stack();
                    if (!invoke_method(klass,
                                       method,
                                       stack,
                                       var_num,
                                       &stack_ptr,
                                       info))
                    {
                        if (info->try_code == code && info->try_offset != 0)
                        {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = (void *) 0;
                        }
                        else
                        {
                            vm_mutex_off();
                            remove_stack_to_stack_list(stack_id);
                            return 0;
                        }
                    }
                }
                else
                {
                    char * class_name;
                    char * method_name;
                    sCLClass * klass;
                    sCLMethod * method;
                    CLObject elements[256];
                    int i;
                    CLObject carray;
                    CLVALUE cl_value;
                    class_name = (char *) (constant->mConst + offset);
                    method_name = (char *) (constant->mConst + offset2);
                    klass = get_class_with_load_and_initialize(class_name);
                    if (klass == (void *) 0)
                    {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr,
                                                               stack,
                                                               var_num,
                                                               info,
                                                               "Exception",
                                                               "class not found(3)");
                        remove_stack_to_stack_list(stack_id);
                        return 0;
                    }
                    if (klass->mCallingClassMethodIndex == -1)
                    {
                        vm_mutex_off();
                        entry_exception_object_with_class_name(&stack_ptr,
                                                               stack,
                                                               var_num,
                                                               info,
                                                               "Exception",
                                                               "OP_INVOKE_DYNAMIC_METHOD: Method not found(2)");
                        remove_stack_to_stack_list(stack_id);
                        return 0;
                    }
                    method = klass->mMethods + klass->mCallingClassMethodIndex;
                    for (i = 0; i < num_params; i++)
                    {
                        CLObject object;
                        object = (stack_ptr - num_params + i)->mObjectValue;
                        elements[i] = object;
                    }
                    carray = create_carray_object_with_elements(num_params, elements);
                    cl_value.mLongValue = 0;
                    cl_value.mObjectValue = carray;
                    push_value_to_global_stack(cl_value);
                    stack_ptr -= num_params;
                    stack_ptr->mLongValue = 0;
                    stack_ptr->mObjectValue = create_string_object(method_name);
                    stack_ptr++;
                    stack_ptr->mLongValue = 0;
                    stack_ptr->mObjectValue = carray;
                    stack_ptr++;
                    stack_ptr->mLongValue = 0;
                    stack_ptr->mIntValue = num_method_chains;
                    stack_ptr++;
                    stack_ptr->mLongValue = 0;
                    stack_ptr->mIntValue = max_method_chains;
                    stack_ptr++;
                    pop_global_stack();
                    if (!invoke_method(klass,
                                       method,
                                       stack,
                                       var_num,
                                       &stack_ptr,
                                       info))
                    {
                        if (info->try_code == code && info->try_offset != 0)
                        {
                            pc = code->mCodes + info->try_offset;
                            info->try_offset = 0;
                            info->try_code = (void *) 0;
                        }
                        else
                        {
                            vm_mutex_off();
                            remove_stack_to_stack_list(stack_id);
                            return 0;
                        }
                    }
                }
                vm_mutex_off();
            }
            break;
        case 3003:
            {
                int num_params;
                int size;
                CLObject block_object;
                CLVALUE result;
                vm_mutex_on();
                num_params = *(int *) pc;
                pc += sizeof(int);
                size = *(int *) pc;
                pc += sizeof(int);
                block_object = (stack_ptr - num_params - 1)->mObjectValue;
                if (!invoke_block(block_object,
                                  stack,
                                  var_num,
                                  num_params,
                                  &stack_ptr,
                                  info,
                                  0))
                {
                    vm_mutex_off();
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                result = *(stack_ptr - 1);
                stack_ptr -= num_params + 1 + 1;
                *stack_ptr = result;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 4000:
            {
                int offset;
                int offset2;
                int flg_array;
                char * class_name;
                sCLClass * klass;
                char * type_name;
                vm_mutex_on();
                offset = *(int *) pc;
                pc += sizeof(int);
                offset2 = *(int *) pc;
                pc += sizeof(int);
                flg_array = *(int *) pc;
                pc += sizeof(int);
                class_name = (char *) (constant->mConst + offset);
                klass = get_class_with_load_and_initialize(class_name);
                if (klass == (void *) 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "class not found(3)");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                type_name = (char *) (constant->mConst + offset2);
                if (flg_array)
                {
                    int array_num;
                    CLObject array;
                    array_num = (stack_ptr - 1)->mIntValue;
                    stack_ptr--;
                    array = create_array_object(klass, array_num);
                    stack_ptr->mLongValue = 0;
                    stack_ptr->mObjectValue = array;
                    stack_ptr++;
                }
                else
                {
                    CLObject obj;
                    obj = create_object(klass, type_name);
                    stack_ptr->mLongValue = 0;
                    stack_ptr->mObjectValue = obj;
                    stack_ptr++;
                }
                vm_mutex_off();
            }
            break;
        case 4001:
            {
                int field_index;
                int tmp;
                CLObject obj;
                sCLObject * object_pointer;
                sCLClass * klass;
                CLVALUE value;
                vm_mutex_on();
                field_index = *(int *) pc;
                pc += sizeof(int);
                tmp = *(int *) pc;
                pc += sizeof(int);
                obj = (stack_ptr - 1)->mObjectValue;
                stack_ptr--;
                if (obj == 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "Null pointer exception(3)");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                object_pointer = (sCLObject *) get_object_pointer(obj);
                klass = object_pointer->mClass;
                if (klass == (void *) 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "class not found(4)");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                if (field_index < 0 || field_index >= klass->mNumFields)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "field index is invalid(1). Field index is %d",
                                                           field_index);
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                value = object_pointer->mFields[field_index];
                *stack_ptr = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 4002:
            {
                int field_index;
                CLObject obj;
                sCLObject * object_pointer;
                sCLClass * klass;
                char * value;
                vm_mutex_on();
                field_index = *(int *) pc;
                pc += sizeof(int);
                obj = (stack_ptr - 1)->mObjectValue;
                stack_ptr--;
                if (obj == 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "Null pointer exception(4)");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                object_pointer = (sCLObject *) get_object_pointer(obj);
                klass = object_pointer->mClass;
                if (klass == (void *) 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "class not found(5)");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                if (field_index < 0 || field_index >= klass->mNumFields)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "field index is invalid(2). Field index is %d",
                                                           field_index);
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                value = (char *) &object_pointer->mFields[field_index];
                stack_ptr->mLongValue = 0;
                stack_ptr->mPointerValue = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 4003:
            {
                int field_index;
                CLObject obj;
                CLVALUE value;
                sCLObject * object_pointer;
                sCLClass * klass;
                vm_mutex_on();
                field_index = *(int *) pc;
                pc += sizeof(int);
                obj = (stack_ptr - 2)->mObjectValue;
                value = *(stack_ptr - 1);
                if (obj == 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "Null pointer exception(5)");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                object_pointer = (sCLObject *) get_object_pointer(obj);
                klass = object_pointer->mClass;
                if (klass == (void *) 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "class not found(6)");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                if (field_index < 0 || field_index >= klass->mNumFields)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "field index is invalid(3). Field index is %d",
                                                           field_index);
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                object_pointer->mFields[field_index] = value;
                stack_ptr -= 2;
                *stack_ptr = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 4004:
            {
                int offset;
                int field_index;
                int tmp;
                char * class_name;
                sCLClass * klass;
                sCLField * field;
                vm_mutex_on();
                offset = *(int *) pc;
                pc += sizeof(int);
                field_index = *(int *) pc;
                pc += sizeof(int);
                tmp = *(int *) pc;
                pc += sizeof(int);
                class_name = (char *) (constant->mConst + offset);
                klass = get_class_with_load_and_initialize(class_name);
                if (klass == (void *) 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "class not found(7)");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                if (field_index < 0 || field_index >= klass->mNumClassFields)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "field index is invalid(4). Field index is %d",
                                                           field_index);
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                field = klass->mClassFields + field_index;
                *stack_ptr = field->mValue;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 4005:
            {
                int offset;
                int field_index;
                char * class_name;
                sCLClass * klass;
                sCLField * field;
                char * value;
                vm_mutex_on();
                offset = *(int *) pc;
                pc += sizeof(int);
                field_index = *(int *) pc;
                pc += sizeof(int);
                class_name = (char *) (constant->mConst + offset);
                klass = get_class_with_load_and_initialize(class_name);
                if (klass == (void *) 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "class not found(8)");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                if (field_index < 0 || field_index >= klass->mNumClassFields)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "field index is invalid(55555). Field index is %d",
                                                           field_index);
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                field = klass->mClassFields + field_index;
                value = (char *) &field->mValue;
                stack_ptr->mLongValue = 0;
                stack_ptr->mPointerValue = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 4006:
            {
                int offset;
                int field_index;
                char * class_name;
                sCLClass * klass;
                CLVALUE value;
                sCLField * field;
                vm_mutex_on();
                offset = *(int *) pc;
                pc += sizeof(int);
                field_index = *(int *) pc;
                pc += sizeof(int);
                class_name = (char *) (constant->mConst + offset);
                klass = get_class_with_load_and_initialize(class_name);
                if (klass == (void *) 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "class not found(9)");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                if (field_index < 0 || field_index >= klass->mNumClassFields)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "field index is invalid(6). Field index is %d",
                                                           field_index);
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                value = *(stack_ptr - 1);
                field = klass->mClassFields + field_index;
                field->mValue = value;
                vm_mutex_off();
            }
            break;
        case 4007:
            {
                int tmp;
                CLObject array;
                int element_num;
                sCLObject * object_pointer;
                CLVALUE value;
                vm_mutex_on();
                tmp = *(int *) pc;
                pc += sizeof(int);
                array = (stack_ptr - 2)->mObjectValue;
                element_num = (stack_ptr - 1)->mIntValue;
                stack_ptr -= 2;
                if (array == 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "Null pointer exception(7)");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                object_pointer = (sCLObject *) get_object_pointer(array);
                if (element_num < 0 || element_num >= object_pointer->mArrayNum)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "element index is invalid");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                value = object_pointer->mFields[element_num];
                *stack_ptr = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 4008:
            {
                CLObject array;
                int element_num;
                CLVALUE value;
                sCLObject * object_pointer;
                vm_mutex_on();
                array = (stack_ptr - 3)->mObjectValue;
                element_num = (stack_ptr - 2)->mIntValue;
                value = *(stack_ptr - 1);
                if (array == 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "Null pointer exception(8)");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                object_pointer = (sCLObject *) get_object_pointer(array);
                if (element_num < 0 || element_num >= object_pointer->mArrayNum)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "element index is invalid");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                object_pointer->mFields[element_num] = value;
                stack_ptr -= 3;
                *stack_ptr = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 5000:
            {
                CLVALUE address;
                CLVALUE value;
                CLVALUE * pointer;
                vm_mutex_on();
                address = *(stack_ptr - 2);
                value = *(stack_ptr - 1);
                pointer = (CLVALUE *) address.mPointerValue;
                pointer->mLongValue = 0;
                pointer->mIntValue = value.mIntValue;
                stack_ptr -= 2;
                *stack_ptr = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 5001:
            {
                CLVALUE address;
                CLVALUE value;
                vm_mutex_on();
                address = *(stack_ptr - 2);
                value = *(stack_ptr - 1);
                *(unsigned int *) address.mPointerValue = value.mUIntValue;
                stack_ptr -= 2;
                *stack_ptr = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 5002:
            {
                CLVALUE address;
                CLVALUE value;
                vm_mutex_on();
                address = *(stack_ptr - 2);
                value = *(stack_ptr - 1);
                *(char *) address.mPointerValue = value.mByteValue;
                stack_ptr -= 2;
                *stack_ptr = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 5003:
            {
                CLVALUE address;
                CLVALUE value;
                vm_mutex_on();
                address = *(stack_ptr - 2);
                value = *(stack_ptr - 1);
                *(unsigned char *) address.mPointerValue = value.mUByteValue;
                stack_ptr -= 2;
                *stack_ptr = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 5004:
            {
                CLVALUE address;
                CLVALUE value;
                vm_mutex_on();
                address = *(stack_ptr - 2);
                value = *(stack_ptr - 1);
                *(short *) address.mPointerValue = value.mShortValue;
                stack_ptr -= 2;
                *stack_ptr = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 5005:
            {
                CLVALUE address;
                CLVALUE value;
                vm_mutex_on();
                address = *(stack_ptr - 2);
                value = *(stack_ptr - 1);
                *(unsigned short *) address.mPointerValue = value.mUShortValue;
                stack_ptr -= 2;
                *stack_ptr = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 5006:
            {
                CLVALUE address;
                CLVALUE value;
                vm_mutex_on();
                address = *(stack_ptr - 2);
                value = *(stack_ptr - 1);
                *(long long *) address.mPointerValue = value.mLongValue;
                stack_ptr -= 2;
                *stack_ptr = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 5007:
            {
                CLVALUE address;
                CLVALUE value;
                vm_mutex_on();
                address = *(stack_ptr - 2);
                value = *(stack_ptr - 1);
                *(unsigned long long *) address.mPointerValue = value.mULongValue;
                stack_ptr -= 2;
                *stack_ptr = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 5008:
            {
                CLVALUE address;
                CLVALUE value;
                vm_mutex_on();
                address = *(stack_ptr - 2);
                value = *(stack_ptr - 1);
                *(float *) address.mPointerValue = value.mFloatValue;
                stack_ptr -= 2;
                *stack_ptr = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 5009:
            {
                CLVALUE address;
                CLVALUE value;
                vm_mutex_on();
                address = *(stack_ptr - 2);
                value = *(stack_ptr - 1);
                *(double *) address.mPointerValue = value.mDoubleValue;
                stack_ptr -= 2;
                *stack_ptr = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 5010:
            {
                CLVALUE address;
                CLVALUE value;
                vm_mutex_on();
                address = *(stack_ptr - 2);
                value = *(stack_ptr - 1);
                *(char * *) address.mPointerValue = value.mPointerValue;
                stack_ptr -= 2;
                *stack_ptr = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 5011:
            {
                CLVALUE address;
                CLVALUE value;
                vm_mutex_on();
                address = *(stack_ptr - 2);
                value = *(stack_ptr - 1);
                *(wchar_t *) address.mPointerValue = value.mCharValue;
                stack_ptr -= 2;
                *stack_ptr = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 5012:
            {
                CLVALUE address;
                CLVALUE value;
                vm_mutex_on();
                address = *(stack_ptr - 2);
                value = *(stack_ptr - 1);
                *(int *) address.mPointerValue = value.mBoolValue;
                stack_ptr -= 2;
                *stack_ptr = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 5013:
            {
                CLVALUE address;
                CLVALUE value;
                vm_mutex_on();
                address = *(stack_ptr - 2);
                value = *(stack_ptr - 1);
                *(CLObject *) address.mPointerValue = value.mObjectValue;
                stack_ptr -= 2;
                *stack_ptr = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 6000:
            {
                CLVALUE address;
                int value;
                vm_mutex_on();
                address = *(stack_ptr - 1);
                stack_ptr--;
                value = *(int *) address.mPointerValue;
                stack_ptr->mLongValue = 0;
                stack_ptr->mIntValue = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 6001:
            {
                CLVALUE address;
                unsigned int value;
                vm_mutex_on();
                address = *(stack_ptr - 1);
                stack_ptr--;
                value = *(unsigned int *) address.mPointerValue;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUIntValue = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 6002:
            {
                CLVALUE address;
                char value;
                vm_mutex_on();
                address = *(stack_ptr - 1);
                stack_ptr--;
                value = *(char *) address.mPointerValue;
                stack_ptr->mLongValue = 0;
                stack_ptr->mByteValue = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 6003:
            {
                CLVALUE address;
                unsigned char value;
                vm_mutex_on();
                address = *(stack_ptr - 1);
                stack_ptr--;
                value = *(unsigned char *) address.mPointerValue;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUByteValue = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 6004:
            {
                CLVALUE address;
                short value;
                vm_mutex_on();
                address = *(stack_ptr - 1);
                stack_ptr--;
                value = *(short *) address.mPointerValue;
                stack_ptr->mLongValue = 0;
                stack_ptr->mShortValue = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 6005:
            {
                CLVALUE address;
                unsigned short value;
                vm_mutex_on();
                address = *(stack_ptr - 1);
                stack_ptr--;
                value = *(unsigned short *) address.mPointerValue;
                stack_ptr->mLongValue = 0;
                stack_ptr->mUShortValue = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 6006:
            {
                CLVALUE address;
                long long value;
                vm_mutex_on();
                address = *(stack_ptr - 1);
                stack_ptr--;
                value = *(long long *) address.mPointerValue;
                stack_ptr->mLongValue = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 6007:
            {
                CLVALUE address;
                unsigned long long value;
                vm_mutex_on();
                address = *(stack_ptr - 1);
                stack_ptr--;
                value = *(unsigned long long *) address.mPointerValue;
                stack_ptr->mULongValue = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 6008:
            {
                CLVALUE address;
                float value;
                vm_mutex_on();
                address = *(stack_ptr - 1);
                stack_ptr--;
                value = *(float *) address.mPointerValue;
                stack_ptr->mLongValue = 0;
                stack_ptr->mFloatValue = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 6009:
            {
                CLVALUE address;
                double value;
                vm_mutex_on();
                address = *(stack_ptr - 1);
                stack_ptr--;
                value = *(double *) address.mPointerValue;
                stack_ptr->mDoubleValue = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 6010:
            {
                CLVALUE address;
                char * value;
                vm_mutex_on();
                address = *(stack_ptr - 1);
                stack_ptr--;
                value = *(char * *) address.mPointerValue;
                stack_ptr->mLongValue = 0;
                stack_ptr->mPointerValue = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 6011:
            {
                CLVALUE address;
                wchar_t value;
                vm_mutex_on();
                address = *(stack_ptr - 1);
                stack_ptr--;
                value = *(wchar_t *) address.mPointerValue;
                stack_ptr->mLongValue = 0;
                stack_ptr->mCharValue = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 6012:
            {
                CLVALUE address;
                int value;
                vm_mutex_on();
                address = *(stack_ptr - 1);
                stack_ptr--;
                value = *(int *) address.mPointerValue;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 6013:
            {
                CLVALUE address;
                CLObject value;
                vm_mutex_on();
                address = *(stack_ptr - 1);
                stack_ptr--;
                value = *(CLObject *) address.mPointerValue;
                stack_ptr->mLongValue = 0;
                stack_ptr->mObjectValue = value;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 7000:
            {
                char value;
                vm_mutex_on();
                value = (char) (stack_ptr - 1)->mUByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7001:
            {
                char value;
                vm_mutex_on();
                value = (char) (stack_ptr - 1)->mShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7002:
            {
                char value;
                vm_mutex_on();
                value = (char) (stack_ptr - 1)->mUShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7003:
            {
                char value;
                vm_mutex_on();
                value = (char) (stack_ptr - 1)->mIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7004:
            {
                char value;
                vm_mutex_on();
                value = (char) (stack_ptr - 1)->mUIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7005:
            {
                char value;
                vm_mutex_on();
                value = (char) (stack_ptr - 1)->mLongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7006:
            {
                char value;
                vm_mutex_on();
                value = (char) (stack_ptr - 1)->mULongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7007:
            {
                char value;
                vm_mutex_on();
                value = (char) (stack_ptr - 1)->mFloatValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7008:
            {
                char value;
                vm_mutex_on();
                value = (char) (stack_ptr - 1)->mDoubleValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7009:
            {
                char value;
                vm_mutex_on();
                value = (char) (stack_ptr - 1)->mPointerValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7010:
            {
                char value;
                vm_mutex_on();
                value = (char) (stack_ptr - 1)->mCharValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7011:
            {
                CLObject obj;
                sCLObject * obj_data;
                char value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (char) obj_data->mFields[0].mByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7012:
            {
                CLObject obj;
                sCLObject * obj_data;
                char value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (char) obj_data->mFields[0].mUByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7013:
            {
                CLObject obj;
                sCLObject * obj_data;
                char value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (char) obj_data->mFields[0].mShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7014:
            {
                CLObject obj;
                sCLObject * obj_data;
                char value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (char) obj_data->mFields[0].mUShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7015:
            {
                CLObject obj;
                sCLObject * obj_data;
                char value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (char) obj_data->mFields[0].mIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7016:
            {
                CLObject obj;
                sCLObject * obj_data;
                char value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (char) obj_data->mFields[0].mUIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7017:
            {
                CLObject obj;
                sCLObject * obj_data;
                char value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (char) obj_data->mFields[0].mLongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7018:
            {
                CLObject obj;
                sCLObject * obj_data;
                char value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (char) obj_data->mFields[0].mULongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7019:
            {
                CLObject obj;
                sCLObject * obj_data;
                char value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (char) obj_data->mFields[0].mFloatValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7020:
            {
                CLObject obj;
                sCLObject * obj_data;
                char value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (char) obj_data->mFields[0].mDoubleValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7021:
            {
                CLObject obj;
                sCLObject * obj_data;
                char value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (char) obj_data->mFields[0].mPointerValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7022:
            {
                CLObject obj;
                sCLObject * obj_data;
                char value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (char) obj_data->mFields[0].mCharValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7023:
            {
                CLObject obj;
                sCLObject * obj_data;
                char value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (char) obj_data->mFields[0].mBoolValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7030:
            {
                short value;
                vm_mutex_on();
                value = (short) (stack_ptr - 1)->mByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7031:
            {
                short value;
                vm_mutex_on();
                value = (short) (stack_ptr - 1)->mUByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7036:
            {
                short value;
                vm_mutex_on();
                value = (short) (stack_ptr - 1)->mUShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7032:
            {
                short value;
                vm_mutex_on();
                value = (short) (stack_ptr - 1)->mIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7033:
            {
                short value;
                vm_mutex_on();
                value = (short) (stack_ptr - 1)->mUIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7034:
            {
                short value;
                vm_mutex_on();
                value = (short) (stack_ptr - 1)->mLongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7035:
            {
                short value;
                vm_mutex_on();
                value = (short) (stack_ptr - 1)->mULongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7037:
            {
                short value;
                vm_mutex_on();
                value = (short) (stack_ptr - 1)->mFloatValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7038:
            {
                short value;
                vm_mutex_on();
                value = (short) (stack_ptr - 1)->mDoubleValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7039:
            {
                short value;
                vm_mutex_on();
                value = (short) (stack_ptr - 1)->mPointerValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7040:
            {
                short value;
                vm_mutex_on();
                value = (short) (stack_ptr - 1)->mCharValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7041:
            {
                CLObject obj;
                sCLObject * obj_data;
                short value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (short) obj_data->mFields[0].mByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7042:
            {
                CLObject obj;
                sCLObject * obj_data;
                short value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (short) obj_data->mFields[0].mUByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7043:
            {
                CLObject obj;
                sCLObject * obj_data;
                short value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (short) obj_data->mFields[0].mShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7044:
            {
                CLObject obj;
                sCLObject * obj_data;
                short value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (short) obj_data->mFields[0].mUShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7045:
            {
                CLObject obj;
                sCLObject * obj_data;
                short value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (short) obj_data->mFields[0].mIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7046:
            {
                CLObject obj;
                sCLObject * obj_data;
                short value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (short) obj_data->mFields[0].mUIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7047:
            {
                CLObject obj;
                sCLObject * obj_data;
                short value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (short) obj_data->mFields[0].mLongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7048:
            {
                CLObject obj;
                sCLObject * obj_data;
                short value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (short) obj_data->mFields[0].mULongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7049:
            {
                CLObject obj;
                sCLObject * obj_data;
                short value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (short) obj_data->mFields[0].mFloatValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7050:
            {
                CLObject obj;
                sCLObject * obj_data;
                short value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (short) obj_data->mFields[0].mDoubleValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7051:
            {
                CLObject obj;
                sCLObject * obj_data;
                short value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (short) obj_data->mFields[0].mPointerValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7052:
            {
                CLObject obj;
                sCLObject * obj_data;
                short value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (short) obj_data->mFields[0].mCharValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7053:
            {
                CLObject obj;
                sCLObject * obj_data;
                short value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (short) obj_data->mFields[0].mBoolValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7060:
            {
                int value;
                vm_mutex_on();
                value = (int) (stack_ptr - 1)->mByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7061:
            {
                int value;
                vm_mutex_on();
                value = (int) (stack_ptr - 1)->mUByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7062:
            {
                int value;
                vm_mutex_on();
                value = (int) (stack_ptr - 1)->mShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7063:
            {
                int value;
                vm_mutex_on();
                value = (int) (stack_ptr - 1)->mUShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7066:
            {
                int value;
                vm_mutex_on();
                value = (int) (stack_ptr - 1)->mUIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7064:
            {
                int value;
                vm_mutex_on();
                value = (int) (stack_ptr - 1)->mLongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7065:
            {
                int value;
                vm_mutex_on();
                value = (int) (stack_ptr - 1)->mULongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7067:
            {
                int value;
                vm_mutex_on();
                value = (int) (stack_ptr - 1)->mFloatValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7068:
            {
                int value;
                vm_mutex_on();
                value = (int) (stack_ptr - 1)->mDoubleValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7069:
            {
                int value;
                vm_mutex_on();
                value = (int) (stack_ptr - 1)->mPointerValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7070:
            {
                int value;
                vm_mutex_on();
                value = (int) (stack_ptr - 1)->mCharValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7071:
            {
                CLObject obj;
                sCLObject * obj_data;
                int value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (int) obj_data->mFields[0].mByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7072:
            {
                CLObject obj;
                sCLObject * obj_data;
                int value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (int) obj_data->mFields[0].mUByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7073:
            {
                CLObject obj;
                sCLObject * obj_data;
                int value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (int) obj_data->mFields[0].mShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7074:
            {
                CLObject obj;
                sCLObject * obj_data;
                int value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (int) obj_data->mFields[0].mUShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7075:
            {
                CLObject obj;
                sCLObject * obj_data;
                int value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (int) obj_data->mFields[0].mIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7076:
            {
                CLObject obj;
                sCLObject * obj_data;
                int value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (int) obj_data->mFields[0].mUIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7077:
            {
                CLObject obj;
                sCLObject * obj_data;
                int value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (int) obj_data->mFields[0].mLongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7078:
            {
                CLObject obj;
                sCLObject * obj_data;
                int value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (int) obj_data->mFields[0].mULongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7079:
            {
                CLObject obj;
                sCLObject * obj_data;
                int value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (int) obj_data->mFields[0].mFloatValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7080:
            {
                CLObject obj;
                sCLObject * obj_data;
                int value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (int) obj_data->mFields[0].mDoubleValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7081:
            {
                CLObject obj;
                sCLObject * obj_data;
                int value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (int) obj_data->mFields[0].mPointerValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7082:
            {
                CLObject obj;
                sCLObject * obj_data;
                int value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (int) obj_data->mFields[0].mCharValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7083:
            {
                CLObject obj;
                sCLObject * obj_data;
                int value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (int) obj_data->mFields[0].mBoolValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7090:
            {
                long long value;
                vm_mutex_on();
                value = (long long) (stack_ptr - 1)->mByteValue;
                (stack_ptr - 1)->mLongValue = value;
                vm_mutex_off();
            }
            break;
        case 7091:
            {
                long long value;
                vm_mutex_on();
                value = (long long) (stack_ptr - 1)->mUByteValue;
                (stack_ptr - 1)->mLongValue = value;
                vm_mutex_off();
            }
            break;
        case 7092:
            {
                long long value;
                vm_mutex_on();
                value = (long long) (stack_ptr - 1)->mShortValue;
                (stack_ptr - 1)->mLongValue = value;
                vm_mutex_off();
            }
            break;
        case 7093:
            {
                long long value;
                vm_mutex_on();
                value = (long long) (stack_ptr - 1)->mUShortValue;
                (stack_ptr - 1)->mLongValue = value;
                vm_mutex_off();
            }
            break;
        case 7094:
            {
                long long value;
                vm_mutex_on();
                value = (long long) (stack_ptr - 1)->mIntValue;
                (stack_ptr - 1)->mLongValue = value;
                vm_mutex_off();
            }
            break;
        case 7095:
            {
                long long value;
                vm_mutex_on();
                value = (long long) (stack_ptr - 1)->mUIntValue;
                (stack_ptr - 1)->mLongValue = value;
                vm_mutex_off();
            }
            break;
        case 7096:
            {
                long long value;
                vm_mutex_on();
                value = (long long) (stack_ptr - 1)->mULongValue;
                (stack_ptr - 1)->mLongValue = value;
                vm_mutex_off();
            }
            break;
        case 7097:
            {
                long long value;
                vm_mutex_on();
                value = (long long) (stack_ptr - 1)->mFloatValue;
                (stack_ptr - 1)->mLongValue = value;
                vm_mutex_off();
            }
            break;
        case 7098:
            {
                long long value;
                vm_mutex_on();
                value = (long long) (stack_ptr - 1)->mDoubleValue;
                (stack_ptr - 1)->mLongValue = value;
                vm_mutex_off();
            }
            break;
        case 7099:
            {
                long long value;
                vm_mutex_on();
                value = (long long) (stack_ptr - 1)->mPointerValue;
                (stack_ptr - 1)->mLongValue = value;
                vm_mutex_off();
            }
            break;
        case 7100:
            {
                long long value;
                vm_mutex_on();
                value = (long long) (stack_ptr - 1)->mCharValue;
                (stack_ptr - 1)->mLongValue = value;
                vm_mutex_off();
            }
            break;
        case 7101:
            {
                CLObject obj;
                sCLObject * obj_data;
                long long value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (long long) obj_data->mFields[0].mByteValue;
                (stack_ptr - 1)->mLongValue = value;
                vm_mutex_off();
            }
            break;
        case 7102:
            {
                CLObject obj;
                sCLObject * obj_data;
                long long value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (long long) obj_data->mFields[0].mUByteValue;
                (stack_ptr - 1)->mLongValue = value;
                vm_mutex_off();
            }
            break;
        case 7103:
            {
                CLObject obj;
                sCLObject * obj_data;
                long long value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (long long) obj_data->mFields[0].mShortValue;
                (stack_ptr - 1)->mLongValue = value;
                vm_mutex_off();
            }
            break;
        case 7104:
            {
                CLObject obj;
                sCLObject * obj_data;
                long long value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (long long) obj_data->mFields[0].mUShortValue;
                (stack_ptr - 1)->mLongValue = value;
                vm_mutex_off();
            }
            break;
        case 7105:
            {
                CLObject obj;
                sCLObject * obj_data;
                long long value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (long long) obj_data->mFields[0].mIntValue;
                (stack_ptr - 1)->mLongValue = value;
                vm_mutex_off();
            }
            break;
        case 7106:
            {
                CLObject obj;
                sCLObject * obj_data;
                long long value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (long long) obj_data->mFields[0].mUIntValue;
                (stack_ptr - 1)->mLongValue = value;
                vm_mutex_off();
            }
            break;
        case 7107:
            {
                CLObject obj;
                sCLObject * obj_data;
                long long value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (long long) obj_data->mFields[0].mLongValue;
                (stack_ptr - 1)->mLongValue = value;
                vm_mutex_off();
            }
            break;
        case 7108:
            {
                CLObject obj;
                sCLObject * obj_data;
                long long value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (long long) obj_data->mFields[0].mULongValue;
                (stack_ptr - 1)->mLongValue = value;
                vm_mutex_off();
            }
            break;
        case 7109:
            {
                CLObject obj;
                sCLObject * obj_data;
                long long value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (long long) obj_data->mFields[0].mFloatValue;
                (stack_ptr - 1)->mLongValue = value;
                vm_mutex_off();
            }
            break;
        case 7110:
            {
                CLObject obj;
                sCLObject * obj_data;
                long long value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (long long) obj_data->mFields[0].mDoubleValue;
                (stack_ptr - 1)->mLongValue = value;
                vm_mutex_off();
            }
            break;
        case 7111:
            {
                CLObject obj;
                sCLObject * obj_data;
                long long value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (long long) obj_data->mFields[0].mPointerValue;
                (stack_ptr - 1)->mLongValue = value;
                vm_mutex_off();
            }
            break;
        case 7112:
            {
                CLObject obj;
                sCLObject * obj_data;
                long long value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (long long) obj_data->mFields[0].mCharValue;
                (stack_ptr - 1)->mLongValue = value;
                vm_mutex_off();
            }
            break;
        case 7113:
            {
                CLObject obj;
                sCLObject * obj_data;
                long long value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (long long) obj_data->mFields[0].mBoolValue;
                (stack_ptr - 1)->mLongValue = value;
                vm_mutex_off();
            }
            break;
        case 7120:
            {
                unsigned char value;
                vm_mutex_on();
                value = (unsigned char) (stack_ptr - 1)->mByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7121:
            {
                unsigned char value;
                vm_mutex_on();
                value = (unsigned char) (stack_ptr - 1)->mShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7122:
            {
                unsigned char value;
                vm_mutex_on();
                value = (unsigned char) (stack_ptr - 1)->mUShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7123:
            {
                unsigned char value;
                vm_mutex_on();
                value = (unsigned char) (stack_ptr - 1)->mIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7124:
            {
                unsigned char value;
                vm_mutex_on();
                value = (unsigned char) (stack_ptr - 1)->mUIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7125:
            {
                unsigned char value;
                vm_mutex_on();
                value = (unsigned char) (stack_ptr - 1)->mLongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7126:
            {
                unsigned char value;
                vm_mutex_on();
                value = (unsigned char) (stack_ptr - 1)->mULongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7127:
            {
                unsigned char value;
                vm_mutex_on();
                value = (unsigned char) (stack_ptr - 1)->mFloatValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7128:
            {
                unsigned char value;
                vm_mutex_on();
                value = (unsigned char) (stack_ptr - 1)->mDoubleValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7129:
            {
                unsigned char value;
                vm_mutex_on();
                value = (unsigned char) (stack_ptr - 1)->mPointerValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7130:
            {
                unsigned char value;
                vm_mutex_on();
                value = (unsigned char) (stack_ptr - 1)->mCharValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7131:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned char value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned char) obj_data->mFields[0].mByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7132:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned char value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned char) obj_data->mFields[0].mUByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7133:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned char value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned char) obj_data->mFields[0].mShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7134:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned char value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned char) obj_data->mFields[0].mUShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7135:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned char value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned char) obj_data->mFields[0].mIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7136:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned char value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned char) obj_data->mFields[0].mUIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7137:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned char value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned char) obj_data->mFields[0].mLongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7138:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned char value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned char) obj_data->mFields[0].mULongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7139:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned char value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned char) obj_data->mFields[0].mFloatValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7140:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned char value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned char) obj_data->mFields[0].mDoubleValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7141:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned char value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned char) obj_data->mFields[0].mPointerValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7142:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned char value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned char) obj_data->mFields[0].mCharValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7143:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned char value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned char) obj_data->mFields[0].mBoolValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUByteValue = value;
                vm_mutex_off();
            }
            break;
        case 7150:
            {
                unsigned short value;
                vm_mutex_on();
                value = (unsigned short) (stack_ptr - 1)->mByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7151:
            {
                unsigned short value;
                vm_mutex_on();
                value = (unsigned short) (stack_ptr - 1)->mUByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7152:
            {
                unsigned short value;
                vm_mutex_on();
                value = (unsigned short) (stack_ptr - 1)->mShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7153:
            {
                unsigned short value;
                vm_mutex_on();
                value = (unsigned short) (stack_ptr - 1)->mIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7154:
            {
                unsigned short value;
                vm_mutex_on();
                value = (unsigned short) (stack_ptr - 1)->mUIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7155:
            {
                unsigned short value;
                vm_mutex_on();
                value = (unsigned short) (stack_ptr - 1)->mLongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7156:
            {
                unsigned short value;
                vm_mutex_on();
                value = (unsigned short) (stack_ptr - 1)->mULongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7157:
            {
                unsigned short value;
                vm_mutex_on();
                value = (unsigned short) (stack_ptr - 1)->mFloatValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7158:
            {
                unsigned short value;
                vm_mutex_on();
                value = (unsigned short) (stack_ptr - 1)->mDoubleValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7159:
            {
                unsigned short value;
                vm_mutex_on();
                value = (unsigned short) (stack_ptr - 1)->mPointerValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7160:
            {
                unsigned short value;
                vm_mutex_on();
                value = (unsigned short) (stack_ptr - 1)->mCharValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7161:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned short value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned short) obj_data->mFields[0].mByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7162:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned short value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned short) obj_data->mFields[0].mUByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7163:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned short value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned short) obj_data->mFields[0].mShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7164:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned short value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned short) obj_data->mFields[0].mUShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7165:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned short value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned short) obj_data->mFields[0].mIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7166:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned short value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned short) obj_data->mFields[0].mUIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7167:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned short value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned short) obj_data->mFields[0].mLongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7168:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned short value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned short) obj_data->mFields[0].mULongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7169:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned short value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned short) obj_data->mFields[0].mFloatValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7170:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned short value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned short) obj_data->mFields[0].mDoubleValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7171:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned short value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned short) obj_data->mFields[0].mPointerValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7172:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned short value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned short) obj_data->mFields[0].mCharValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7173:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned short value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned short) obj_data->mFields[0].mBoolValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUShortValue = value;
                vm_mutex_off();
            }
            break;
        case 7200:
            {
                unsigned int value;
                vm_mutex_on();
                value = (unsigned int) (stack_ptr - 1)->mByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7201:
            {
                unsigned int value;
                vm_mutex_on();
                value = (unsigned int) (stack_ptr - 1)->mUByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7202:
            {
                unsigned int value;
                vm_mutex_on();
                value = (unsigned int) (stack_ptr - 1)->mShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7203:
            {
                unsigned int value;
                vm_mutex_on();
                value = (unsigned int) (stack_ptr - 1)->mUShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7204:
            {
                unsigned int value;
                vm_mutex_on();
                value = (unsigned int) (stack_ptr - 1)->mIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7205:
            {
                unsigned int value;
                vm_mutex_on();
                value = (unsigned int) (stack_ptr - 1)->mLongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7206:
            {
                unsigned int value;
                vm_mutex_on();
                value = (unsigned int) (stack_ptr - 1)->mULongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7207:
            {
                unsigned int value;
                vm_mutex_on();
                value = (unsigned int) (stack_ptr - 1)->mFloatValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7208:
            {
                unsigned int value;
                vm_mutex_on();
                value = (unsigned int) (stack_ptr - 1)->mDoubleValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7209:
            {
                unsigned int value;
                vm_mutex_on();
                value = (unsigned int) (stack_ptr - 1)->mPointerValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7210:
            {
                unsigned int value;
                vm_mutex_on();
                value = (unsigned int) (stack_ptr - 1)->mCharValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7211:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned int value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned int) obj_data->mFields[0].mByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7212:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned int value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned int) obj_data->mFields[0].mUByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7213:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned int value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned int) obj_data->mFields[0].mShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7214:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned int value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned int) obj_data->mFields[0].mUShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7215:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned int value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned int) obj_data->mFields[0].mIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7216:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned int value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned int) obj_data->mFields[0].mUIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7217:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned int value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned int) obj_data->mFields[0].mLongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7218:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned int value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned int) obj_data->mFields[0].mULongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7219:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned int value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned int) obj_data->mFields[0].mFloatValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7220:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned int value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned int) obj_data->mFields[0].mDoubleValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7221:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned int value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned int) obj_data->mFields[0].mPointerValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7222:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned int value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned int) obj_data->mFields[0].mCharValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7223:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned int value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned int) obj_data->mFields[0].mBoolValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mUIntValue = value;
                vm_mutex_off();
            }
            break;
        case 7230:
            {
                unsigned long long value;
                vm_mutex_on();
                value = (unsigned long long) (stack_ptr - 1)->mByteValue;
                (stack_ptr - 1)->mULongValue = value;
                vm_mutex_off();
            }
            break;
        case 7231:
            {
                unsigned long long value;
                vm_mutex_on();
                value = (unsigned long long) (stack_ptr - 1)->mUByteValue;
                (stack_ptr - 1)->mULongValue = value;
                vm_mutex_off();
            }
            break;
        case 7232:
            {
                unsigned long long value;
                vm_mutex_on();
                value = (unsigned long long) (stack_ptr - 1)->mShortValue;
                (stack_ptr - 1)->mULongValue = value;
                vm_mutex_off();
            }
            break;
        case 7233:
            {
                unsigned long long value;
                vm_mutex_on();
                value = (unsigned long long) (stack_ptr - 1)->mUShortValue;
                (stack_ptr - 1)->mULongValue = value;
                vm_mutex_off();
            }
            break;
        case 7234:
            {
                unsigned long long value;
                vm_mutex_on();
                value = (unsigned long long) (stack_ptr - 1)->mIntValue;
                (stack_ptr - 1)->mULongValue = value;
                vm_mutex_off();
            }
            break;
        case 7235:
            {
                unsigned long long value;
                vm_mutex_on();
                value = (unsigned long long) (stack_ptr - 1)->mUIntValue;
                (stack_ptr - 1)->mULongValue = value;
                vm_mutex_off();
            }
            break;
        case 7236:
            {
                unsigned long long value;
                vm_mutex_on();
                value = (unsigned long long) (stack_ptr - 1)->mLongValue;
                (stack_ptr - 1)->mULongValue = value;
                vm_mutex_off();
            }
            break;
        case 7237:
            {
                unsigned long long value;
                vm_mutex_on();
                value = (unsigned long long) (stack_ptr - 1)->mFloatValue;
                (stack_ptr - 1)->mULongValue = value;
                vm_mutex_off();
            }
            break;
        case 7238:
            {
                unsigned long long value;
                vm_mutex_on();
                value = (unsigned long long) (stack_ptr - 1)->mDoubleValue;
                (stack_ptr - 1)->mULongValue = value;
                vm_mutex_off();
            }
            break;
        case 7239:
            {
                unsigned long long value;
                vm_mutex_on();
                value = (unsigned long long) (stack_ptr - 1)->mPointerValue;
                (stack_ptr - 1)->mULongValue = value;
                vm_mutex_off();
            }
            break;
        case 7240:
            {
                unsigned long long value;
                vm_mutex_on();
                value = (unsigned long long) (stack_ptr - 1)->mCharValue;
                (stack_ptr - 1)->mULongValue = value;
                vm_mutex_off();
            }
            break;
        case 7241:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned long long value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned long long) obj_data->mFields[0].mByteValue;
                (stack_ptr - 1)->mULongValue = value;
                vm_mutex_off();
            }
            break;
        case 7242:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned long long value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned long long) obj_data->mFields[0].mUByteValue;
                (stack_ptr - 1)->mULongValue = value;
                vm_mutex_off();
            }
            break;
        case 7243:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned long long value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned long long) obj_data->mFields[0].mShortValue;
                (stack_ptr - 1)->mULongValue = value;
                vm_mutex_off();
            }
            break;
        case 7244:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned long long value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned long long) obj_data->mFields[0].mUShortValue;
                (stack_ptr - 1)->mULongValue = value;
                vm_mutex_off();
            }
            break;
        case 7245:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned long long value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned long long) obj_data->mFields[0].mIntValue;
                (stack_ptr - 1)->mULongValue = value;
                vm_mutex_off();
            }
            break;
        case 7246:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned long long value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned long long) obj_data->mFields[0].mUIntValue;
                (stack_ptr - 1)->mULongValue = value;
                vm_mutex_off();
            }
            break;
        case 7247:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned long long value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned long long) obj_data->mFields[0].mLongValue;
                (stack_ptr - 1)->mULongValue = value;
                vm_mutex_off();
            }
            break;
        case 7248:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned long long value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned long long) obj_data->mFields[0].mULongValue;
                (stack_ptr - 1)->mULongValue = value;
                vm_mutex_off();
            }
            break;
        case 7249:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned long long value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned long long) obj_data->mFields[0].mFloatValue;
                (stack_ptr - 1)->mULongValue = value;
                vm_mutex_off();
            }
            break;
        case 7250:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned long long value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned long long) obj_data->mFields[0].mDoubleValue;
                (stack_ptr - 1)->mULongValue = value;
                vm_mutex_off();
            }
            break;
        case 7251:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned long long value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned long long) obj_data->mFields[0].mPointerValue;
                (stack_ptr - 1)->mULongValue = value;
                vm_mutex_off();
            }
            break;
        case 7252:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned long long value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned long long) obj_data->mFields[0].mCharValue;
                (stack_ptr - 1)->mULongValue = value;
                vm_mutex_off();
            }
            break;
        case 7253:
            {
                CLObject obj;
                sCLObject * obj_data;
                unsigned long long value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (unsigned long long) obj_data->mFields[0].mBoolValue;
                (stack_ptr - 1)->mULongValue = value;
                vm_mutex_off();
            }
            break;
        case 7260:
            {
                float value;
                vm_mutex_on();
                value = (float) (stack_ptr - 1)->mByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mFloatValue = value;
                vm_mutex_off();
            }
            break;
        case 7261:
            {
                float value;
                vm_mutex_on();
                value = (float) (stack_ptr - 1)->mUByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mFloatValue = value;
                vm_mutex_off();
            }
            break;
        case 7262:
            {
                float value;
                vm_mutex_on();
                value = (float) (stack_ptr - 1)->mShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mFloatValue = value;
                vm_mutex_off();
            }
            break;
        case 7263:
            {
                float value;
                vm_mutex_on();
                value = (float) (stack_ptr - 1)->mUShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mFloatValue = value;
                vm_mutex_off();
            }
            break;
        case 7264:
            {
                float value;
                vm_mutex_on();
                value = (float) (stack_ptr - 1)->mIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mFloatValue = value;
                vm_mutex_off();
            }
            break;
        case 7265:
            {
                float value;
                vm_mutex_on();
                value = (float) (stack_ptr - 1)->mUIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mFloatValue = value;
                vm_mutex_off();
            }
            break;
        case 7266:
            {
                float value;
                vm_mutex_on();
                value = (float) (stack_ptr - 1)->mLongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mFloatValue = value;
                vm_mutex_off();
            }
            break;
        case 7267:
            {
                float value;
                vm_mutex_on();
                value = (float) (stack_ptr - 1)->mULongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mFloatValue = value;
                vm_mutex_off();
            }
            break;
        case 7268:
            {
                float value;
                vm_mutex_on();
                value = (float) (stack_ptr - 1)->mDoubleValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mFloatValue = value;
                vm_mutex_off();
            }
            break;
        case 7269:
            {
                float value;
                vm_mutex_on();
                value = (float) (stack_ptr - 1)->mCharValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mFloatValue = value;
                vm_mutex_off();
            }
            break;
        case 7270:
            {
                CLObject obj;
                sCLObject * obj_data;
                float value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (float) obj_data->mFields[0].mByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mFloatValue = value;
                vm_mutex_off();
            }
            break;
        case 7271:
            {
                CLObject obj;
                sCLObject * obj_data;
                float value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (float) obj_data->mFields[0].mUByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mFloatValue = value;
                vm_mutex_off();
            }
            break;
        case 7272:
            {
                CLObject obj;
                sCLObject * obj_data;
                float value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (float) obj_data->mFields[0].mShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mFloatValue = value;
                vm_mutex_off();
            }
            break;
        case 7273:
            {
                CLObject obj;
                sCLObject * obj_data;
                float value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (float) obj_data->mFields[0].mUShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mFloatValue = value;
                vm_mutex_off();
            }
            break;
        case 7274:
            {
                CLObject obj;
                sCLObject * obj_data;
                float value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (float) obj_data->mFields[0].mIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mFloatValue = value;
                vm_mutex_off();
            }
            break;
        case 7275:
            {
                CLObject obj;
                sCLObject * obj_data;
                float value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (float) obj_data->mFields[0].mUIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mFloatValue = value;
                vm_mutex_off();
            }
            break;
        case 7276:
            {
                CLObject obj;
                sCLObject * obj_data;
                float value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (float) obj_data->mFields[0].mLongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mFloatValue = value;
                vm_mutex_off();
            }
            break;
        case 7277:
            {
                CLObject obj;
                sCLObject * obj_data;
                float value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (float) obj_data->mFields[0].mULongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mFloatValue = value;
                vm_mutex_off();
            }
            break;
        case 7278:
            {
                CLObject obj;
                sCLObject * obj_data;
                float value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (float) obj_data->mFields[0].mFloatValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mFloatValue = value;
                vm_mutex_off();
            }
            break;
        case 7279:
            {
                CLObject obj;
                sCLObject * obj_data;
                float value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (float) obj_data->mFields[0].mDoubleValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mFloatValue = value;
                vm_mutex_off();
            }
            break;
        case 7281:
            {
                CLObject obj;
                sCLObject * obj_data;
                float value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (float) obj_data->mFields[0].mCharValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mFloatValue = value;
                vm_mutex_off();
            }
            break;
        case 7282:
            {
                CLObject obj;
                sCLObject * obj_data;
                float value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (float) obj_data->mFields[0].mBoolValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mFloatValue = value;
                vm_mutex_off();
            }
            break;
        case 7290:
            {
                double value;
                vm_mutex_on();
                value = (double) (stack_ptr - 1)->mByteValue;
                (stack_ptr - 1)->mDoubleValue = value;
                vm_mutex_off();
            }
            break;
        case 7291:
            {
                double value;
                vm_mutex_on();
                value = (double) (stack_ptr - 1)->mUByteValue;
                (stack_ptr - 1)->mDoubleValue = value;
                vm_mutex_off();
            }
            break;
        case 7292:
            {
                double value;
                vm_mutex_on();
                value = (double) (stack_ptr - 1)->mShortValue;
                (stack_ptr - 1)->mDoubleValue = value;
                vm_mutex_off();
            }
            break;
        case 7293:
            {
                double value;
                vm_mutex_on();
                value = (double) (stack_ptr - 1)->mUShortValue;
                (stack_ptr - 1)->mDoubleValue = value;
                vm_mutex_off();
            }
            break;
        case 7294:
            {
                double value;
                vm_mutex_on();
                value = (double) (stack_ptr - 1)->mIntValue;
                (stack_ptr - 1)->mDoubleValue = value;
                vm_mutex_off();
            }
            break;
        case 7295:
            {
                double value;
                vm_mutex_on();
                value = (double) (stack_ptr - 1)->mUIntValue;
                (stack_ptr - 1)->mDoubleValue = value;
                vm_mutex_off();
            }
            break;
        case 7296:
            {
                double value;
                vm_mutex_on();
                value = (double) (stack_ptr - 1)->mLongValue;
                (stack_ptr - 1)->mDoubleValue = value;
                vm_mutex_off();
            }
            break;
        case 7297:
            {
                double value;
                vm_mutex_on();
                value = (double) (stack_ptr - 1)->mULongValue;
                (stack_ptr - 1)->mDoubleValue = value;
                vm_mutex_off();
            }
            break;
        case 7298:
            {
                double value;
                vm_mutex_on();
                value = (double) (stack_ptr - 1)->mFloatValue;
                (stack_ptr - 1)->mDoubleValue = value;
                vm_mutex_off();
            }
            break;
        case 7299:
            {
                double value;
                vm_mutex_on();
                value = (double) (stack_ptr - 1)->mCharValue;
                (stack_ptr - 1)->mDoubleValue = value;
                vm_mutex_off();
            }
            break;
        case 7300:
            {
                CLObject obj;
                sCLObject * obj_data;
                double value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (double) obj_data->mFields[0].mByteValue;
                (stack_ptr - 1)->mDoubleValue = value;
                vm_mutex_off();
            }
            break;
        case 7301:
            {
                CLObject obj;
                sCLObject * obj_data;
                double value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (double) obj_data->mFields[0].mUByteValue;
                (stack_ptr - 1)->mDoubleValue = value;
                vm_mutex_off();
            }
            break;
        case 7302:
            {
                CLObject obj;
                sCLObject * obj_data;
                double value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (double) obj_data->mFields[0].mShortValue;
                (stack_ptr - 1)->mDoubleValue = value;
                vm_mutex_off();
            }
            break;
        case 7303:
            {
                CLObject obj;
                sCLObject * obj_data;
                double value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (double) obj_data->mFields[0].mUShortValue;
                (stack_ptr - 1)->mDoubleValue = value;
                vm_mutex_off();
            }
            break;
        case 7304:
            {
                CLObject obj;
                sCLObject * obj_data;
                double value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (double) obj_data->mFields[0].mIntValue;
                (stack_ptr - 1)->mDoubleValue = value;
                vm_mutex_off();
            }
            break;
        case 7305:
            {
                CLObject obj;
                sCLObject * obj_data;
                double value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (double) obj_data->mFields[0].mUIntValue;
                (stack_ptr - 1)->mDoubleValue = value;
                vm_mutex_off();
            }
            break;
        case 7306:
            {
                CLObject obj;
                sCLObject * obj_data;
                double value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (double) obj_data->mFields[0].mLongValue;
                (stack_ptr - 1)->mDoubleValue = value;
                vm_mutex_off();
            }
            break;
        case 7307:
            {
                CLObject obj;
                sCLObject * obj_data;
                double value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (double) obj_data->mFields[0].mULongValue;
                (stack_ptr - 1)->mDoubleValue = value;
                vm_mutex_off();
            }
            break;
        case 7308:
            {
                CLObject obj;
                sCLObject * obj_data;
                double value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (double) obj_data->mFields[0].mFloatValue;
                (stack_ptr - 1)->mDoubleValue = value;
                vm_mutex_off();
            }
            break;
        case 7309:
            {
                CLObject obj;
                sCLObject * obj_data;
                double value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (double) obj_data->mFields[0].mDoubleValue;
                (stack_ptr - 1)->mDoubleValue = value;
                vm_mutex_off();
            }
            break;
        case 7311:
            {
                CLObject obj;
                sCLObject * obj_data;
                double value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (double) obj_data->mFields[0].mCharValue;
                (stack_ptr - 1)->mDoubleValue = value;
                vm_mutex_off();
            }
            break;
        case 7312:
            {
                CLObject obj;
                sCLObject * obj_data;
                double value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (double) obj_data->mFields[0].mBoolValue;
                (stack_ptr - 1)->mDoubleValue = value;
                vm_mutex_off();
            }
            break;
        case 7320:
            {
                char * value;
                vm_mutex_on();
                value = (char *) (stack_ptr - 1)->mByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mPointerValue = value;
                vm_mutex_off();
            }
            break;
        case 7321:
            {
                char * value;
                vm_mutex_on();
                value = (char *) (stack_ptr - 1)->mUByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mPointerValue = value;
                vm_mutex_off();
            }
            break;
        case 7322:
            {
                char * value;
                vm_mutex_on();
                value = (char *) (stack_ptr - 1)->mShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mPointerValue = value;
                vm_mutex_off();
            }
            break;
        case 7323:
            {
                char * value;
                vm_mutex_on();
                value = (char *) (stack_ptr - 1)->mUShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mPointerValue = value;
                vm_mutex_off();
            }
            break;
        case 7324:
            {
                char * value;
                vm_mutex_on();
                value = (char *) (stack_ptr - 1)->mIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mPointerValue = value;
                vm_mutex_off();
            }
            break;
        case 7325:
            {
                char * value;
                vm_mutex_on();
                value = (char *) (stack_ptr - 1)->mUIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mPointerValue = value;
                vm_mutex_off();
            }
            break;
        case 7326:
            {
                char * value;
                vm_mutex_on();
                value = (char *) (stack_ptr - 1)->mLongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mPointerValue = value;
                vm_mutex_off();
            }
            break;
        case 7327:
            {
                char * value;
                vm_mutex_on();
                value = (char *) (stack_ptr - 1)->mULongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mPointerValue = value;
                vm_mutex_off();
            }
            break;
        case 7328:
            {
                char * value;
                vm_mutex_on();
                value = (char *) (stack_ptr - 1)->mCharValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mPointerValue = value;
                vm_mutex_off();
            }
            break;
        case 7330:
            {
                wchar_t value;
                vm_mutex_on();
                value = (wchar_t) (stack_ptr - 1)->mByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mCharValue = value;
                vm_mutex_off();
            }
            break;
        case 7331:
            {
                wchar_t value;
                vm_mutex_on();
                value = (wchar_t) (stack_ptr - 1)->mUByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mCharValue = value;
                vm_mutex_off();
            }
            break;
        case 7332:
            {
                wchar_t value;
                vm_mutex_on();
                value = (wchar_t) (stack_ptr - 1)->mShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mCharValue = value;
                vm_mutex_off();
            }
            break;
        case 7333:
            {
                wchar_t value;
                vm_mutex_on();
                value = (wchar_t) (stack_ptr - 1)->mUShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mCharValue = value;
                vm_mutex_off();
            }
            break;
        case 7334:
            {
                wchar_t value;
                vm_mutex_on();
                value = (wchar_t) (stack_ptr - 1)->mIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mCharValue = value;
                vm_mutex_off();
            }
            break;
        case 7335:
            {
                wchar_t value;
                vm_mutex_on();
                value = (wchar_t) (stack_ptr - 1)->mUIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mCharValue = value;
                vm_mutex_off();
            }
            break;
        case 7336:
            {
                wchar_t value;
                vm_mutex_on();
                value = (wchar_t) (stack_ptr - 1)->mLongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mCharValue = value;
                vm_mutex_off();
            }
            break;
        case 7337:
            {
                wchar_t value;
                vm_mutex_on();
                value = (wchar_t) (stack_ptr - 1)->mULongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mCharValue = value;
                vm_mutex_off();
            }
            break;
        case 7338:
            {
                wchar_t value;
                vm_mutex_on();
                value = (wchar_t) (stack_ptr - 1)->mFloatValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mCharValue = value;
                vm_mutex_off();
            }
            break;
        case 7339:
            {
                wchar_t value;
                vm_mutex_on();
                value = (wchar_t) (stack_ptr - 1)->mDoubleValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mCharValue = value;
                vm_mutex_off();
            }
            break;
        case 7340:
            {
                wchar_t value;
                vm_mutex_on();
                value = (wchar_t) (stack_ptr - 1)->mPointerValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mCharValue = value;
                vm_mutex_off();
            }
            break;
        case 7341:
            {
                CLObject obj;
                sCLObject * obj_data;
                wchar_t value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (wchar_t) obj_data->mFields[0].mByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mCharValue = value;
                vm_mutex_off();
            }
            break;
        case 7342:
            {
                CLObject obj;
                sCLObject * obj_data;
                wchar_t value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (wchar_t) obj_data->mFields[0].mUByteValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mCharValue = value;
                vm_mutex_off();
            }
            break;
        case 7343:
            {
                CLObject obj;
                sCLObject * obj_data;
                wchar_t value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (wchar_t) obj_data->mFields[0].mShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mCharValue = value;
                vm_mutex_off();
            }
            break;
        case 7344:
            {
                CLObject obj;
                sCLObject * obj_data;
                wchar_t value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (wchar_t) obj_data->mFields[0].mUShortValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mCharValue = value;
                vm_mutex_off();
            }
            break;
        case 7345:
            {
                CLObject obj;
                sCLObject * obj_data;
                wchar_t value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (wchar_t) obj_data->mFields[0].mIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mCharValue = value;
                vm_mutex_off();
            }
            break;
        case 7346:
            {
                CLObject obj;
                sCLObject * obj_data;
                wchar_t value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (wchar_t) obj_data->mFields[0].mUIntValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mCharValue = value;
                vm_mutex_off();
            }
            break;
        case 7347:
            {
                CLObject obj;
                sCLObject * obj_data;
                wchar_t value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (wchar_t) obj_data->mFields[0].mLongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mCharValue = value;
                vm_mutex_off();
            }
            break;
        case 7348:
            {
                CLObject obj;
                sCLObject * obj_data;
                wchar_t value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (wchar_t) obj_data->mFields[0].mULongValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mCharValue = value;
                vm_mutex_off();
            }
            break;
        case 7349:
            {
                CLObject obj;
                sCLObject * obj_data;
                wchar_t value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (wchar_t) obj_data->mFields[0].mFloatValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mCharValue = value;
                vm_mutex_off();
            }
            break;
        case 7350:
            {
                CLObject obj;
                sCLObject * obj_data;
                wchar_t value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (wchar_t) obj_data->mFields[0].mDoubleValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mCharValue = value;
                vm_mutex_off();
            }
            break;
        case 7351:
            {
                CLObject obj;
                sCLObject * obj_data;
                wchar_t value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (wchar_t) obj_data->mFields[0].mPointerValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mCharValue = value;
                vm_mutex_off();
            }
            break;
        case 7352:
            {
                CLObject obj;
                sCLObject * obj_data;
                wchar_t value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (wchar_t) obj_data->mFields[0].mCharValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mCharValue = value;
                vm_mutex_off();
            }
            break;
        case 7353:
            {
                CLObject obj;
                sCLObject * obj_data;
                wchar_t value;
                vm_mutex_on();
                obj = (stack_ptr - 1)->mObjectValue;
                obj_data = (sCLObject *) get_object_pointer(obj);
                value = (wchar_t) obj_data->mFields[0].mBoolValue;
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mCharValue = value;
                vm_mutex_off();
            }
            break;
        case 7360:
            {
                char value;
                char buf[32];
                CLObject str;
                vm_mutex_on();
                value = (stack_ptr - 1)->mCharValue;
                snprintf(buf, 32, "%d", value);
                str = create_string_object(buf);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = str;
                vm_mutex_off();
            }
            break;
        case 7361:
            {
                short value;
                char buf[32];
                CLObject str;
                vm_mutex_on();
                value = (stack_ptr - 1)->mShortValue;
                snprintf(buf, 32, "%d", value);
                str = create_string_object(buf);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = str;
                vm_mutex_off();
            }
            break;
        case 7362:
            {
                int value;
                char buf[32];
                CLObject str;
                vm_mutex_on();
                value = (stack_ptr - 1)->mIntValue;
                snprintf(buf, 32, "%d", value);
                str = create_string_object(buf);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = str;
                vm_mutex_off();
            }
            break;
        case 7363:
            {
                long long value;
                char buf[32];
                CLObject str;
                vm_mutex_on();
                value = (stack_ptr - 1)->mLongValue;
                snprintf(buf, 32, "%lld", value);
                str = create_string_object(buf);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = str;
                vm_mutex_off();
            }
            break;
        case 7364:
            {
                unsigned char value;
                char buf[32];
                CLObject str;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUByteValue;
                snprintf(buf, 32, "%u", value);
                str = create_string_object(buf);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = str;
                vm_mutex_off();
            }
            break;
        case 7365:
            {
                unsigned short value;
                char buf[32];
                CLObject str;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUShortValue;
                snprintf(buf, 32, "%u", value);
                str = create_string_object(buf);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = str;
                vm_mutex_off();
            }
            break;
        case 7366:
            {
                unsigned int value;
                char buf[32];
                CLObject str;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUIntValue;
                snprintf(buf, 32, "%u", value);
                str = create_string_object(buf);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = str;
                vm_mutex_off();
            }
            break;
        case 7367:
            {
                unsigned long long value;
                char buf[32];
                CLObject str;
                vm_mutex_on();
                value = (stack_ptr - 1)->mULongValue;
                snprintf(buf, 32, "%llu", value);
                str = create_string_object(buf);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = str;
                vm_mutex_off();
            }
            break;
        case 7368:
            {
                float value;
                char buf[32];
                CLObject str;
                vm_mutex_on();
                value = (stack_ptr - 1)->mFloatValue;
                snprintf(buf, 32, "%f", value);
                str = create_string_object(buf);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = str;
                vm_mutex_off();
            }
            break;
        case 7369:
            {
                double value;
                char buf[32];
                CLObject str;
                vm_mutex_on();
                value = (stack_ptr - 1)->mDoubleValue;
                snprintf(buf, 32, "%lf", value);
                str = create_string_object(buf);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = str;
                vm_mutex_off();
            }
            break;
        case 7370:
            {
                int value;
                char buf[32];
                CLObject str;
                vm_mutex_on();
                value = (stack_ptr - 1)->mBoolValue;
                if (value)
                {
                    snprintf(buf, 32, "true");
                }
                else
                {
                    snprintf(buf, 32, "false");
                }
                str = create_string_object(buf);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = str;
                vm_mutex_off();
            }
            break;
        case 7371:
            {
                CLObject regex;
                sRegexObject * object_data;
                CLObject str;
                vm_mutex_on();
                regex = (stack_ptr - 1)->mObjectValue;
                object_data = (sRegexObject *) get_object_pointer(regex);
                str = create_string_object(object_data->mRegexString);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = str;
                vm_mutex_off();
            }
            break;
        case 7372:
            {
                char * value;
                char buf[32];
                CLObject str;
                vm_mutex_on();
                value = (stack_ptr - 1)->mPointerValue;
                snprintf(buf, 32, "%p", value);
                str = create_string_object(buf);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = str;
                vm_mutex_off();
            }
            break;
        case 7373:
            {
                wchar_t value;
                char buf[32];
                CLObject str;
                vm_mutex_on();
                value = (stack_ptr - 1)->mCharValue;
                snprintf(buf, 32, "%lc", value);
                str = create_string_object(buf);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = str;
                vm_mutex_off();
            }
            break;
        case 7400:
            {
                char value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mByteValue;
                obj = create_integer((int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7401:
            {
                unsigned char value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUByteValue;
                obj = create_integer((int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7402:
            {
                short value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mShortValue;
                obj = create_integer((int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7403:
            {
                unsigned short value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUShortValue;
                obj = create_integer((int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7404:
            {
                int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mIntValue;
                obj = create_integer(value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7405:
            {
                unsigned int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUIntValue;
                obj = create_integer((int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7406:
            {
                long long value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mLongValue;
                obj = create_integer((int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7407:
            {
                unsigned long long value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mULongValue;
                obj = create_integer((int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7408:
            {
                float value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mFloatValue;
                obj = create_integer((int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7409:
            {
                double value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mDoubleValue;
                obj = create_integer((int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7410:
            {
                wchar_t value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mCharValue;
                obj = create_integer((int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7411:
            {
                char * value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mPointerValue;
                obj = create_integer((int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7412:
            {
                int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mBoolValue;
                obj = create_integer((int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7420:
            {
                char value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mByteValue;
                obj = create_uinteger((unsigned int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7421:
            {
                unsigned char value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUByteValue;
                obj = create_uinteger((unsigned int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7422:
            {
                short value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mShortValue;
                obj = create_uinteger((unsigned int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7423:
            {
                unsigned short value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUShortValue;
                obj = create_uinteger((unsigned int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7424:
            {
                int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mIntValue;
                obj = create_uinteger((unsigned int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7425:
            {
                unsigned int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUIntValue;
                obj = create_uinteger(value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7426:
            {
                long long value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mLongValue;
                obj = create_uinteger((unsigned int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7427:
            {
                unsigned long long value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mULongValue;
                obj = create_uinteger((unsigned int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7428:
            {
                float value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mFloatValue;
                obj = create_uinteger((unsigned int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7429:
            {
                double value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mDoubleValue;
                obj = create_uinteger((unsigned int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7430:
            {
                wchar_t value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mCharValue;
                obj = create_uinteger((unsigned int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7431:
            {
                char * value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mPointerValue;
                obj = create_uinteger((unsigned int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7432:
            {
                int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mBoolValue;
                obj = create_uinteger((unsigned int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7440:
            {
                char value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mByteValue;
                obj = create_byte((char) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7441:
            {
                unsigned char value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUByteValue;
                obj = create_byte((char) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7442:
            {
                short value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mShortValue;
                obj = create_byte((char) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7443:
            {
                unsigned short value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUShortValue;
                obj = create_byte((char) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7444:
            {
                int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mIntValue;
                obj = create_byte((char) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7445:
            {
                unsigned int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUIntValue;
                obj = create_byte((char) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7446:
            {
                long long value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mLongValue;
                obj = create_byte((char) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7447:
            {
                unsigned long long value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mULongValue;
                obj = create_byte((char) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7448:
            {
                float value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mFloatValue;
                obj = create_byte((char) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7449:
            {
                double value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mDoubleValue;
                obj = create_byte((char) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7450:
            {
                wchar_t value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mCharValue;
                obj = create_byte((char) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7451:
            {
                char * value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mPointerValue;
                obj = create_byte((char) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7452:
            {
                int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mBoolValue;
                obj = create_byte((char) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7460:
            {
                char value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mByteValue;
                obj = create_ubyte((unsigned char) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7461:
            {
                unsigned char value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUByteValue;
                obj = create_ubyte((unsigned char) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7462:
            {
                short value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mShortValue;
                obj = create_ubyte((unsigned char) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7463:
            {
                unsigned short value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUShortValue;
                obj = create_ubyte((unsigned char) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7464:
            {
                int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mIntValue;
                obj = create_ubyte((unsigned char) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7465:
            {
                unsigned int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUIntValue;
                obj = create_ubyte((unsigned char) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7466:
            {
                long long value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mLongValue;
                obj = create_ubyte((unsigned char) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7467:
            {
                unsigned long long value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mULongValue;
                obj = create_ubyte((unsigned char) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7468:
            {
                float value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mFloatValue;
                obj = create_ubyte((unsigned char) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7469:
            {
                double value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mDoubleValue;
                obj = create_ubyte((unsigned char) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7470:
            {
                wchar_t value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mCharValue;
                obj = create_ubyte((unsigned char) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7471:
            {
                char * value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mPointerValue;
                obj = create_ubyte((unsigned char) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7472:
            {
                int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mBoolValue;
                obj = create_ubyte((unsigned char) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7480:
            {
                char value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mByteValue;
                obj = create_short((short) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7481:
            {
                unsigned char value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUByteValue;
                obj = create_short((short) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7482:
            {
                short value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mShortValue;
                obj = create_short((short) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7483:
            {
                unsigned short value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUShortValue;
                obj = create_short((short) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7484:
            {
                int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mIntValue;
                obj = create_short((short) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7485:
            {
                unsigned int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUIntValue;
                obj = create_short((short) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7486:
            {
                long long value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mLongValue;
                obj = create_short((short) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7487:
            {
                unsigned long long value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mULongValue;
                obj = create_short((short) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7488:
            {
                float value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mFloatValue;
                obj = create_short((short) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7489:
            {
                double value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mDoubleValue;
                obj = create_short((short) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7490:
            {
                wchar_t value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mCharValue;
                obj = create_short((short) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7491:
            {
                char * value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mPointerValue;
                obj = create_short((short) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7492:
            {
                int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mBoolValue;
                obj = create_short((short) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7500:
            {
                char value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mByteValue;
                obj = create_ushort((unsigned short) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7501:
            {
                unsigned char value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUByteValue;
                obj = create_ushort((unsigned short) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7502:
            {
                short value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mShortValue;
                obj = create_ushort((unsigned short) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7503:
            {
                unsigned short value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUShortValue;
                obj = create_ushort((unsigned short) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7504:
            {
                int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mIntValue;
                obj = create_ushort((unsigned short) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7505:
            {
                unsigned int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUIntValue;
                obj = create_ushort((unsigned short) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7506:
            {
                long long value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mLongValue;
                obj = create_ushort((unsigned short) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7507:
            {
                unsigned long long value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mULongValue;
                obj = create_ushort((unsigned short) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7508:
            {
                float value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mFloatValue;
                obj = create_ushort((unsigned short) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7509:
            {
                double value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mDoubleValue;
                obj = create_ushort((unsigned short) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7510:
            {
                wchar_t value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mCharValue;
                obj = create_ushort((unsigned short) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7511:
            {
                char * value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mPointerValue;
                obj = create_ushort((unsigned short) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7512:
            {
                int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mBoolValue;
                obj = create_ushort((unsigned short) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7520:
            {
                char value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mByteValue;
                obj = create_long((long long) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7521:
            {
                unsigned char value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUByteValue;
                obj = create_long((long long) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7522:
            {
                short value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mShortValue;
                obj = create_long((long long) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7523:
            {
                unsigned short value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUShortValue;
                obj = create_long((long long) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7524:
            {
                int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mIntValue;
                obj = create_long((long long) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7525:
            {
                unsigned int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUIntValue;
                obj = create_long((long long) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7526:
            {
                long long value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mLongValue;
                obj = create_long((long long) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7527:
            {
                unsigned long long value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mULongValue;
                obj = create_long((long long) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7528:
            {
                float value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mFloatValue;
                obj = create_long((long long) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7529:
            {
                double value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mDoubleValue;
                obj = create_long((long long) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7530:
            {
                wchar_t value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mCharValue;
                obj = create_long((long long) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7531:
            {
                char * value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mPointerValue;
                obj = create_long((long long) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7532:
            {
                int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mBoolValue;
                obj = create_long((long long) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7540:
            {
                char value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mByteValue;
                obj = create_ulong((unsigned long long) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7541:
            {
                unsigned char value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUByteValue;
                obj = create_ulong((unsigned long long) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7542:
            {
                short value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mShortValue;
                obj = create_ulong((unsigned long long) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7543:
            {
                unsigned short value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUShortValue;
                obj = create_ulong((unsigned long long) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7544:
            {
                int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mIntValue;
                obj = create_ulong((unsigned long long) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7545:
            {
                unsigned int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUIntValue;
                obj = create_ulong((unsigned long long) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7546:
            {
                long long value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mLongValue;
                obj = create_ulong((unsigned long long) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7547:
            {
                unsigned long long value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mULongValue;
                obj = create_ulong((unsigned long long) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7548:
            {
                float value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mFloatValue;
                obj = create_ulong((unsigned long long) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7549:
            {
                double value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mDoubleValue;
                obj = create_ulong((unsigned long long) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7550:
            {
                wchar_t value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mCharValue;
                obj = create_ulong((unsigned long long) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7551:
            {
                char * value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mPointerValue;
                obj = create_ulong((unsigned long long) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7552:
            {
                int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mBoolValue;
                obj = create_ulong((unsigned long long) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7560:
            {
                char value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mByteValue;
                obj = create_float((float) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7561:
            {
                unsigned char value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUByteValue;
                obj = create_float((float) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7562:
            {
                short value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mShortValue;
                obj = create_float((float) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7563:
            {
                unsigned short value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUShortValue;
                obj = create_float((float) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7564:
            {
                int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mIntValue;
                obj = create_float((float) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7565:
            {
                unsigned int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUIntValue;
                obj = create_float((float) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7566:
            {
                long long value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mLongValue;
                obj = create_float((float) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7567:
            {
                unsigned long long value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mULongValue;
                obj = create_float((float) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7568:
            {
                float value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mFloatValue;
                obj = create_float((float) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7569:
            {
                double value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mDoubleValue;
                obj = create_float((float) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7570:
            {
                wchar_t value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mCharValue;
                obj = create_float((float) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7572:
            {
                int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mBoolValue;
                obj = create_float((float) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7580:
            {
                char value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mByteValue;
                obj = create_double((double) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7581:
            {
                unsigned char value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUByteValue;
                obj = create_double((double) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7582:
            {
                short value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mShortValue;
                obj = create_double((double) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7583:
            {
                unsigned short value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUShortValue;
                obj = create_double((double) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7584:
            {
                int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mIntValue;
                obj = create_double((double) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7585:
            {
                unsigned int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUIntValue;
                obj = create_double((double) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7586:
            {
                long long value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mLongValue;
                obj = create_double((double) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7587:
            {
                unsigned long long value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mULongValue;
                obj = create_double((double) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7588:
            {
                float value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mFloatValue;
                obj = create_double((double) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7589:
            {
                double value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mDoubleValue;
                obj = create_double((double) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7590:
            {
                wchar_t value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mCharValue;
                obj = create_double((double) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7592:
            {
                int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mBoolValue;
                obj = create_double((double) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7600:
            {
                char value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mByteValue;
                obj = create_pointer((char *) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7601:
            {
                unsigned char value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUByteValue;
                obj = create_pointer((char *) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7602:
            {
                short value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mShortValue;
                obj = create_pointer((char *) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7603:
            {
                unsigned short value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUShortValue;
                obj = create_pointer((char *) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7604:
            {
                int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mIntValue;
                obj = create_pointer((char *) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7605:
            {
                unsigned int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUIntValue;
                obj = create_pointer((char *) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7606:
            {
                long long value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mLongValue;
                obj = create_pointer((char *) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7607:
            {
                unsigned long long value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mULongValue;
                obj = create_pointer((char *) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7610:
            {
                wchar_t value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mCharValue;
                obj = create_pointer((char *) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7611:
            {
                char * value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mPointerValue;
                obj = create_pointer((char *) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7612:
            {
                int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mBoolValue;
                obj = create_pointer((char *) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7620:
            {
                char value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mByteValue;
                obj = create_char((wchar_t) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7621:
            {
                unsigned char value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUByteValue;
                obj = create_char((wchar_t) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7622:
            {
                short value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mShortValue;
                obj = create_char((wchar_t) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7623:
            {
                unsigned short value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUShortValue;
                obj = create_char((wchar_t) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7624:
            {
                int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mIntValue;
                obj = create_char((wchar_t) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7625:
            {
                unsigned int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUIntValue;
                obj = create_char((wchar_t) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7626:
            {
                long long value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mLongValue;
                obj = create_char((wchar_t) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7627:
            {
                unsigned long long value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mULongValue;
                obj = create_char((wchar_t) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7628:
            {
                float value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mFloatValue;
                obj = create_char((wchar_t) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7629:
            {
                double value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mDoubleValue;
                obj = create_char((wchar_t) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7630:
            {
                wchar_t value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mCharValue;
                obj = create_char((wchar_t) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7631:
            {
                char * value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mPointerValue;
                obj = create_char((wchar_t) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7632:
            {
                int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mBoolValue;
                obj = create_char((wchar_t) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7640:
            {
                char value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mByteValue;
                obj = create_bool((int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7641:
            {
                unsigned char value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUByteValue;
                obj = create_bool((int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7642:
            {
                short value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mShortValue;
                obj = create_bool((int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7643:
            {
                unsigned short value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUShortValue;
                obj = create_bool((int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7644:
            {
                int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mIntValue;
                obj = create_bool((int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7645:
            {
                unsigned int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mUIntValue;
                obj = create_bool((int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7646:
            {
                long long value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mLongValue;
                obj = create_bool((int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7647:
            {
                unsigned long long value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mULongValue;
                obj = create_bool((int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7648:
            {
                float value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mFloatValue;
                obj = create_bool((int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7649:
            {
                double value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mDoubleValue;
                obj = create_bool((int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7650:
            {
                wchar_t value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mCharValue;
                obj = create_bool((int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7651:
            {
                char * value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mPointerValue;
                obj = create_bool((int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7652:
            {
                int value;
                CLObject obj;
                vm_mutex_on();
                value = (stack_ptr - 1)->mBoolValue;
                obj = create_bool((int) value);
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mObjectValue = obj;
                vm_mutex_off();
            }
            break;
        case 7700:
            {
                int offset;
                char * class_name;
                sCLClass * klass;
                CLObject array;
                sCLObject * array_data;
                int array_num;
                sCLClass * klass2;
                char type_name[128];
                CLObject new_array;
                CLObject new_primitive_array;
                sCLObject * new_array_data;
                int i;
                vm_mutex_on();
                offset = *(int *) pc;
                pc += sizeof(int);
                class_name = (char *) (constant->mConst + offset);
                klass = get_class_with_load_and_initialize(class_name);
                if (klass == (void *) 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "class not found(10)");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                array = (stack_ptr - 1)->mObjectValue;
                array_data = (sCLObject *) get_object_pointer(array);
                array_num = array_data->mArrayNum;
                klass2 = get_class("Array");
                ;
                snprintf(type_name,
                         128,
                         "Array<%s>",
                         (char *) ((&klass->mConst)->mConst + klass->mClassNameOffset));
                new_array = create_object(klass2, type_name);
                stack_ptr->mLongValue = 0;
                stack_ptr->mObjectValue = new_array;
                stack_ptr++;
                if (klass->mFlags & 0x1)
                {
                    new_primitive_array = create_array_object(klass->mBoxingClass,
                                                              array_num);
                }
                else
                {
                    new_primitive_array = create_array_object(klass, array_num);
                }
                new_array_data = (sCLObject *) get_object_pointer(new_array);
                new_array_data->mFields[0].mLongValue = 0;
                new_array_data->mFields[0].mObjectValue = new_primitive_array;
                for (i = 0; i < array_num; i++)
                {
                    CLVALUE element;
                    sCLObject * new_primitive_array_data;
                    array_data = (sCLObject *) get_object_pointer(array);
                    boxing_primitive_value_to_object(array_data->mFields[i],
                                                     &element,
                                                     klass);
                    new_primitive_array_data = (sCLObject *) get_object_pointer(new_primitive_array);
                    new_primitive_array_data->mFields[i] = element;
                }
                stack_ptr -= 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mObjectValue = new_array;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 8000:
            {
                CLObject array;
                sCLObject * array_data;
                vm_mutex_on();
                array = (stack_ptr - 1)->mObjectValue;
                array_data = (sCLObject *) get_object_pointer(array);
                stack_ptr--;
                stack_ptr->mLongValue = 0;
                stack_ptr->mIntValue = array_data->mArrayNum;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 8100:
            {
                CLObject regex;
                sRegexObject * regex_object;
                vm_mutex_on();
                regex = (stack_ptr - 1)->mObjectValue;
                regex_object = (sRegexObject *) get_object_pointer(regex);
                stack_ptr--;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = regex_object->mGlobal;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 8101:
            {
                CLObject regex;
                sRegexObject * regex_object;
                vm_mutex_on();
                regex = (stack_ptr - 1)->mObjectValue;
                regex_object = (sRegexObject *) get_object_pointer(regex);
                stack_ptr--;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = regex_object->mIgnoreCase;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 8102:
            {
                CLObject regex;
                sRegexObject * regex_object;
                vm_mutex_on();
                regex = (stack_ptr - 1)->mObjectValue;
                regex_object = (sRegexObject *) get_object_pointer(regex);
                stack_ptr--;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = regex_object->mMultiline;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 8103:
            {
                CLObject regex;
                sRegexObject * regex_object;
                vm_mutex_on();
                regex = (stack_ptr - 1)->mObjectValue;
                regex_object = (sRegexObject *) get_object_pointer(regex);
                stack_ptr--;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = regex_object->mExtended;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 8104:
            {
                CLObject regex;
                sRegexObject * regex_object;
                vm_mutex_on();
                regex = (stack_ptr - 1)->mObjectValue;
                regex_object = (sRegexObject *) get_object_pointer(regex);
                stack_ptr--;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = regex_object->mDotAll;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 8105:
            {
                CLObject regex;
                sRegexObject * regex_object;
                vm_mutex_on();
                regex = (stack_ptr - 1)->mObjectValue;
                regex_object = (sRegexObject *) get_object_pointer(regex);
                stack_ptr--;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = regex_object->mAnchored;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 8106:
            {
                CLObject regex;
                sRegexObject * regex_object;
                vm_mutex_on();
                regex = (stack_ptr - 1)->mObjectValue;
                regex_object = (sRegexObject *) get_object_pointer(regex);
                stack_ptr--;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = regex_object->mDollarEndOnly;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 8107:
            {
                CLObject regex;
                sRegexObject * regex_object;
                vm_mutex_on();
                regex = (stack_ptr - 1)->mObjectValue;
                regex_object = (sRegexObject *) get_object_pointer(regex);
                stack_ptr--;
                stack_ptr->mLongValue = 0;
                stack_ptr->mBoolValue = regex_object->mUngreedy;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 8150:
            {
                wchar_t c;
                wchar_t result;
                vm_mutex_on();
                c = (stack_ptr - 1)->mCharValue;
                result = c;
                if (c >= 'a' && c <= 'z')
                {
                    result = c - 'a' + 'A';
                }
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mCharValue = result;
                vm_mutex_off();
            }
            break;
        case 8151:
            {
                wchar_t c;
                wchar_t result;
                vm_mutex_on();
                c = (stack_ptr - 1)->mCharValue;
                result = c;
                if (c >= 'A' && c <= 'Z')
                {
                    result = c - 'A' + 'a';
                }
                (stack_ptr - 1)->mLongValue = 0;
                (stack_ptr - 1)->mCharValue = result;
                vm_mutex_off();
            }
            break;
        case 9000:
            {
                int offset;
                int num_string_expression;
                char * str;
                vm_mutex_on();
                offset = *(int *) pc;
                pc += sizeof(int);
                num_string_expression = *(int *) pc;
                pc += sizeof(int);
                str = (char *) (constant->mConst + offset);
                if (num_string_expression == 0)
                {
                    CLObject string_object;
                    string_object = create_string_object(str);
                    stack_ptr->mLongValue = 0;
                    stack_ptr->mObjectValue = string_object;
                    stack_ptr++;
                }
                else
                {
                    int string_expression_offsets[32];
                    CLObject string_expression_object[32];
                    int i;
                    sBuf buf;
                    CLObject string_object;
                    for (i = 0; i < num_string_expression; i++)
                    {
                        string_expression_offsets[i] = *(int *) pc;
                        pc += sizeof(int);
                        string_expression_object[i] = (stack_ptr - num_string_expression + i)->mObjectValue;
                    }
                    sBuf_init(&buf);
                    if (!string_expression(str,
                                           &buf,
                                           string_expression_offsets,
                                           string_expression_object,
                                           num_string_expression,
                                           &stack_ptr,
                                           stack,
                                           var_num,
                                           info))
                    {
                        vm_mutex_off();
                        remove_stack_to_stack_list(stack_id);
                        xfree(buf.mBuf);
                        return 0;
                    }
                    stack_ptr -= num_string_expression;
                    string_object = create_string_object(buf.mBuf);
                    stack_ptr->mLongValue = 0;
                    stack_ptr->mObjectValue = string_object;
                    stack_ptr++;
                    xfree(buf.mBuf);
                }
                vm_mutex_off();
            }
            break;
        case 9001:
            {
                int offset;
                int size;
                int num_string_expression;
                char * str;
                vm_mutex_on();
                offset = *(int *) pc;
                pc += sizeof(int);
                size = *(int *) pc;
                pc += sizeof(int);
                num_string_expression = *(int *) pc;
                pc += sizeof(int);
                str = (char *) (constant->mConst + offset);
                if (num_string_expression == 0)
                {
                    CLObject buffer_object;
                    buffer_object = create_buffer_object(str, size);
                    stack_ptr->mLongValue = 0;
                    stack_ptr->mObjectValue = buffer_object;
                    stack_ptr++;
                }
                else
                {
                    int string_expression_offsets[32];
                    CLObject string_expression_object[32];
                    int i;
                    sBuf buf;
                    CLObject buffer_object;
                    for (i = 0; i < num_string_expression; i++)
                    {
                        string_expression_offsets[i] = *(int *) pc;
                        pc += sizeof(int);
                        string_expression_object[i] = (stack_ptr - num_string_expression + i)->mObjectValue;
                    }
                    sBuf_init(&buf);
                    if (!string_expression(str,
                                           &buf,
                                           string_expression_offsets,
                                           string_expression_object,
                                           num_string_expression,
                                           &stack_ptr,
                                           stack,
                                           var_num,
                                           info))
                    {
                        vm_mutex_off();
                        remove_stack_to_stack_list(stack_id);
                        xfree(buf.mBuf);
                        return 0;
                    }
                    stack_ptr -= num_string_expression;
                    buffer_object = create_buffer_object(buf.mBuf, buf.mLen);
                    stack_ptr->mLongValue = 0;
                    stack_ptr->mObjectValue = buffer_object;
                    stack_ptr++;
                    xfree(buf.mBuf);
                }
                vm_mutex_off();
            }
            break;
        case 9002:
            {
                int offset;
                int num_string_expression;
                char * str;
                vm_mutex_on();
                offset = *(int *) pc;
                pc += sizeof(int);
                num_string_expression = *(int *) pc;
                pc += sizeof(int);
                str = (char *) (constant->mConst + offset);
                if (num_string_expression == 0)
                {
                    CLObject path_object;
                    path_object = create_path_object(str);
                    stack_ptr->mLongValue = 0;
                    stack_ptr->mObjectValue = path_object;
                    stack_ptr++;
                }
                else
                {
                    int string_expression_offsets[32];
                    CLObject string_expression_object[32];
                    int i;
                    sBuf buf;
                    CLObject path_object;
                    for (i = 0; i < num_string_expression; i++)
                    {
                        string_expression_offsets[i] = *(int *) pc;
                        pc += sizeof(int);
                        string_expression_object[i] = (stack_ptr - num_string_expression + i)->mObjectValue;
                    }
                    sBuf_init(&buf);
                    if (!string_expression(str,
                                           &buf,
                                           string_expression_offsets,
                                           string_expression_object,
                                           num_string_expression,
                                           &stack_ptr,
                                           stack,
                                           var_num,
                                           info))
                    {
                        vm_mutex_off();
                        remove_stack_to_stack_list(stack_id);
                        xfree(buf.mBuf);
                        return 0;
                    }
                    stack_ptr -= num_string_expression;
                    path_object = create_path_object(buf.mBuf);
                    stack_ptr->mLongValue = 0;
                    stack_ptr->mObjectValue = path_object;
                    stack_ptr++;
                    xfree(buf.mBuf);
                }
                vm_mutex_off();
            }
            break;
        case 9003:
            {
                int num_elements;
                int offset;
                char * class_name;
                sCLClass * klass;
                CLObject array_object;
                sCLObject * object_data;
                int i;
                vm_mutex_on();
                num_elements = *(int *) pc;
                pc += sizeof(int);
                offset = *(int *) pc;
                pc += sizeof(int);
                class_name = (char *) (constant->mConst + offset);
                klass = get_class_with_load_and_initialize(class_name);
                if (klass == (void *) 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "class not found(11)");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                array_object = create_array_object(klass, num_elements);
                stack_ptr->mLongValue = 0;
                stack_ptr->mObjectValue = array_object;
                stack_ptr++;
                object_data = (sCLObject *) get_object_pointer(array_object);
                for (i = 0; i < num_elements; i++)
                {
                    object_data->mFields[i] = *(stack_ptr - 1 - num_elements + i);
                }
                stack_ptr--;
                stack_ptr -= num_elements;
                stack_ptr->mLongValue = 0;
                stack_ptr->mObjectValue = array_object;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 9004:
            {
                int num_elements;
                int offset;
                int offset2;
                char * class_name;
                sCLClass * klass;
                char * type_name;
                CLObject array_object;
                CLObject items[256];
                int i;
                vm_mutex_on();
                num_elements = *(int *) pc;
                pc += sizeof(int);
                offset = *(int *) pc;
                pc += sizeof(int);
                offset2 = *(int *) pc;
                pc += sizeof(int);
                class_name = (char *) (constant->mConst + offset);
                klass = get_class_with_load_and_initialize(class_name);
                if (klass == (void *) 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "class not found(12)");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                type_name = (char *) (constant->mConst + offset2);
                array_object = create_carray_object(type_name);
                stack_ptr->mLongValue = 0;
                stack_ptr->mObjectValue = array_object;
                stack_ptr++;
                for (i = 0; i < num_elements; i++)
                {
                    CLVALUE element;
                    element = *(stack_ptr - 1 - num_elements + i);
                    items[i] = (*(stack_ptr - 1 - num_elements + i)).mObjectValue;
                }
                if (!initialize_carray_object(array_object,
                                              num_elements,
                                              items,
                                              stack,
                                              var_num,
                                              &stack_ptr,
                                              info,
                                              klass))
                {
                    vm_mutex_off();
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                stack_ptr--;
                stack_ptr -= num_elements;
                stack_ptr->mLongValue = 0;
                stack_ptr->mObjectValue = array_object;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 9006:
            {
                int num_elements;
                int offset;
                int offset2;
                char * class_name;
                sCLClass * klass;
                char * type_name;
                CLObject array_object;
                CLObject items[256];
                int i;
                vm_mutex_on();
                num_elements = *(int *) pc;
                pc += sizeof(int);
                offset = *(int *) pc;
                pc += sizeof(int);
                offset2 = *(int *) pc;
                pc += sizeof(int);
                class_name = (char *) (constant->mConst + offset);
                klass = get_class_with_load_and_initialize(class_name);
                if (klass == (void *) 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "class not found(12)");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                type_name = (char *) (constant->mConst + offset2);
                array_object = create_equalable_carray_object(type_name);
                stack_ptr->mLongValue = 0;
                stack_ptr->mObjectValue = array_object;
                stack_ptr++;
                for (i = 0; i < num_elements; i++)
                {
                    CLVALUE element;
                    element = *(stack_ptr - 1 - num_elements + i);
                    items[i] = (*(stack_ptr - 1 - num_elements + i)).mObjectValue;
                }
                if (!initialize_equalable_carray_object(array_object,
                                                        num_elements,
                                                        items,
                                                        stack,
                                                        var_num,
                                                        &stack_ptr,
                                                        info,
                                                        klass))
                {
                    vm_mutex_off();
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                stack_ptr--;
                stack_ptr -= num_elements;
                stack_ptr->mLongValue = 0;
                stack_ptr->mObjectValue = array_object;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 9005:
            {
                int num_elements;
                int offset;
                int offset2;
                char * class_name;
                sCLClass * klass;
                char * type_name;
                CLObject array_object;
                CLObject items[256];
                int i;
                vm_mutex_on();
                num_elements = *(int *) pc;
                pc += sizeof(int);
                offset = *(int *) pc;
                pc += sizeof(int);
                offset2 = *(int *) pc;
                pc += sizeof(int);
                class_name = (char *) (constant->mConst + offset);
                klass = get_class_with_load_and_initialize(class_name);
                if (klass == (void *) 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "class not found(12)");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                type_name = (char *) (constant->mConst + offset2);
                array_object = create_sortable_carray_object(type_name);
                stack_ptr->mLongValue = 0;
                stack_ptr->mObjectValue = array_object;
                stack_ptr++;
                for (i = 0; i < num_elements; i++)
                {
                    CLVALUE element;
                    element = *(stack_ptr - 1 - num_elements + i);
                    items[i] = (*(stack_ptr - 1 - num_elements + i)).mObjectValue;
                }
                if (!initialize_sortable_carray_object(array_object,
                                                       num_elements,
                                                       items,
                                                       stack,
                                                       var_num,
                                                       &stack_ptr,
                                                       info,
                                                       klass))
                {
                    vm_mutex_off();
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                stack_ptr--;
                stack_ptr -= num_elements;
                stack_ptr->mLongValue = 0;
                stack_ptr->mObjectValue = array_object;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 9007:
            {
                int num_elements;
                int offset;
                int offset2;
                char * class_name;
                sCLClass * klass;
                char * type_name;
                CLObject list_object;
                CLObject items[256];
                int i;
                vm_mutex_on();
                num_elements = *(int *) pc;
                pc += sizeof(int);
                offset = *(int *) pc;
                pc += sizeof(int);
                offset2 = *(int *) pc;
                pc += sizeof(int);
                class_name = (char *) (constant->mConst + offset);
                klass = get_class_with_load_and_initialize(class_name);
                if (klass == (void *) 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "class not found(13)");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                type_name = (char *) (constant->mConst + offset2);
                list_object = create_list_object(type_name);
                stack_ptr->mLongValue = 0;
                stack_ptr->mObjectValue = list_object;
                stack_ptr++;
                for (i = 0; i < num_elements; i++)
                {
                    CLVALUE element;
                    element = *(stack_ptr - 1 - num_elements + i);
                    items[i] = (*(stack_ptr - 1 - num_elements + i)).mObjectValue;
                }
                if (!initialize_list_object(list_object,
                                            num_elements,
                                            items,
                                            stack,
                                            var_num,
                                            &stack_ptr,
                                            info,
                                            klass))
                {
                    vm_mutex_off();
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                stack_ptr--;
                stack_ptr -= num_elements;
                stack_ptr->mLongValue = 0;
                stack_ptr->mObjectValue = list_object;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 9008:
            {
                int num_elements;
                int offset;
                int offset2;
                char * class_name;
                sCLClass * klass;
                char * type_name;
                CLObject list_object;
                CLObject items[256];
                int i;
                vm_mutex_on();
                num_elements = *(int *) pc;
                pc += sizeof(int);
                offset = *(int *) pc;
                pc += sizeof(int);
                offset2 = *(int *) pc;
                pc += sizeof(int);
                class_name = (char *) (constant->mConst + offset);
                klass = get_class_with_load_and_initialize(class_name);
                if (klass == (void *) 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "class not found(13)");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                type_name = (char *) (constant->mConst + offset2);
                list_object = create_sortable_list_object(type_name);
                stack_ptr->mLongValue = 0;
                stack_ptr->mObjectValue = list_object;
                stack_ptr++;
                for (i = 0; i < num_elements; i++)
                {
                    CLVALUE element;
                    element = *(stack_ptr - 1 - num_elements + i);
                    items[i] = (*(stack_ptr - 1 - num_elements + i)).mObjectValue;
                }
                if (!initialize_sortable_list_object(list_object,
                                                     num_elements,
                                                     items,
                                                     stack,
                                                     var_num,
                                                     &stack_ptr,
                                                     info,
                                                     klass))
                {
                    vm_mutex_off();
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                stack_ptr--;
                stack_ptr -= num_elements;
                stack_ptr->mLongValue = 0;
                stack_ptr->mObjectValue = list_object;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 9009:
            {
                int num_elements;
                int offset;
                int offset2;
                char * class_name;
                sCLClass * klass;
                char * type_name;
                CLObject list_object;
                CLObject items[256];
                int i;
                vm_mutex_on();
                num_elements = *(int *) pc;
                pc += sizeof(int);
                offset = *(int *) pc;
                pc += sizeof(int);
                offset2 = *(int *) pc;
                pc += sizeof(int);
                class_name = (char *) (constant->mConst + offset);
                klass = get_class_with_load_and_initialize(class_name);
                if (klass == (void *) 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "class not found(13)");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                type_name = (char *) (constant->mConst + offset2);
                list_object = create_equalable_list_object(type_name);
                stack_ptr->mLongValue = 0;
                stack_ptr->mObjectValue = list_object;
                stack_ptr++;
                for (i = 0; i < num_elements; i++)
                {
                    CLVALUE element;
                    element = *(stack_ptr - 1 - num_elements + i);
                    items[i] = (*(stack_ptr - 1 - num_elements + i)).mObjectValue;
                }
                if (!initialize_equalable_list_object(list_object,
                                                      num_elements,
                                                      items,
                                                      stack,
                                                      var_num,
                                                      &stack_ptr,
                                                      info,
                                                      klass))
                {
                    vm_mutex_off();
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                stack_ptr--;
                stack_ptr -= num_elements;
                stack_ptr->mLongValue = 0;
                stack_ptr->mObjectValue = list_object;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 9010:
            {
                int num_elements;
                int offset;
                char * type_name;
                CLObject tuple_object;
                CLObject items[256];
                int i;
                vm_mutex_on();
                num_elements = *(int *) pc;
                pc += sizeof(int);
                offset = *(int *) pc;
                pc += sizeof(int);
                type_name = (char *) (constant->mConst + offset);
                tuple_object = create_tuple_object(num_elements, type_name);
                stack_ptr->mLongValue = 0;
                stack_ptr->mObjectValue = tuple_object;
                stack_ptr++;
                for (i = 0; i < num_elements; i++)
                {
                    CLVALUE element;
                    element = *(stack_ptr - 1 - num_elements + i);
                    items[i] = (*(stack_ptr - 1 - num_elements + i)).mObjectValue;
                }
                if (!initialize_tuple_object(tuple_object,
                                             num_elements,
                                             items,
                                             stack,
                                             var_num,
                                             &stack_ptr,
                                             info))
                {
                    vm_mutex_off();
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                stack_ptr--;
                stack_ptr -= num_elements;
                stack_ptr->mLongValue = 0;
                stack_ptr->mObjectValue = tuple_object;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 9011:
            {
                int num_elements;
                int offset;
                char * class_name;
                sCLClass * klass;
                int offset2;
                int offset3;
                char * class_name2;
                sCLClass * klass2;
                CLObject keys[256];
                int i;
                CLObject items[256];
                char * type_name;
                CLObject hash_object;
                vm_mutex_on();
                num_elements = *(int *) pc;
                pc += sizeof(int);
                offset = *(int *) pc;
                pc += sizeof(int);
                class_name = (char *) (constant->mConst + offset);
                klass = get_class_with_load_and_initialize(class_name);
                if (klass == (void *) 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "class not found(14)");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                offset2 = *(int *) pc;
                pc += sizeof(int);
                offset3 = *(int *) pc;
                pc += sizeof(int);
                class_name2 = (char *) (constant->mConst + offset2);
                klass2 = get_class_with_load_and_initialize(class_name2);
                if (klass2 == (void *) 0)
                {
                    vm_mutex_off();
                    entry_exception_object_with_class_name(&stack_ptr,
                                                           stack,
                                                           var_num,
                                                           info,
                                                           "Exception",
                                                           "class not found(15)");
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                for (i = 0; i < num_elements; i++)
                {
                    keys[i] = (stack_ptr - num_elements * 2 + i * 2)->mObjectValue;
                }
                for (i = 0; i < num_elements; i++)
                {
                    items[i] = (stack_ptr - num_elements * 2 + i * 2 + 1)->mObjectValue;
                }
                type_name = (char *) (constant->mConst + offset3);
                hash_object = create_hash_object(type_name);
                stack_ptr->mLongValue = 0;
                stack_ptr->mObjectValue = hash_object;
                stack_ptr++;
                if (!initialize_hash_object(hash_object,
                                            num_elements,
                                            keys,
                                            items,
                                            stack,
                                            var_num,
                                            &stack_ptr,
                                            info,
                                            klass,
                                            klass2))
                {
                    vm_mutex_off();
                    remove_stack_to_stack_list(stack_id);
                    return 0;
                }
                stack_ptr--;
                stack_ptr -= num_elements * 2;
                stack_ptr->mLongValue = 0;
                stack_ptr->mObjectValue = hash_object;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 9012:
            {
                int code_offset;
                int code_len;
                sByteCode codes2;
                int constant_offset;
                int constant_len;
                sConst constant2;
                int block_var_num;
                int parent_var_num;
                int lambda;
                CLVALUE * parent_stack;
                CLObject block_object;
                vm_mutex_on();
                code_offset = *(int *) pc;
                pc += sizeof(int);
                code_len = *(int *) pc;
                pc += sizeof(int);
                codes2.mCodes = (char *) (constant->mConst + code_offset);
                codes2.mLen = code_len;
                constant_offset = *(int *) pc;
                pc += sizeof(int);
                constant_len = *(int *) pc;
                pc += sizeof(int);
                constant2.mConst = (char *) (constant->mConst + constant_offset);
                constant2.mLen = constant_len;
                block_var_num = *(int *) pc;
                pc += sizeof(int);
                parent_var_num = *(int *) pc;
                pc += sizeof(int);
                lambda = *(int *) pc;
                pc += sizeof(int);
                parent_stack = stack;
                block_object = create_block_object(&codes2,
                                                   &constant2,
                                                   parent_stack,
                                                   parent_var_num,
                                                   block_var_num,
                                                   stack_id,
                                                   lambda);
                stack_ptr->mLongValue = 0;
                stack_ptr->mObjectValue = block_object;
                stack_ptr++;
                vm_mutex_off();
            }
            break;
        case 9013:
            {
                int offset;
                int global;
                int ignore_case;
                int multiline;
                int extended;
                int dotall;
                int anchored;
                int dollar_endonly;
                int ungreedy;
                int num_string_expression;
                char * str;
                vm_mutex_on();
                offset = *(int *) pc;
                pc += sizeof(int);
                global = *(int *) pc;
                pc += sizeof(int);
                ignore_case = *(int *) pc;
                pc += sizeof(int);
                multiline = *(int *) pc;
                pc += sizeof(int);
                extended = *(int *) pc;
                pc += sizeof(int);
                dotall = *(int *) pc;
                pc += sizeof(int);
                anchored = *(int *) pc;
                pc += sizeof(int);
                dollar_endonly = *(int *) pc;
                pc += sizeof(int);
                ungreedy = *(int *) pc;
                pc += sizeof(int);
                num_string_expression = *(int *) pc;
                pc += sizeof(int);
                str = (char *) (constant->mConst + offset);
                if (num_string_expression == 0)
                {
                    CLObject regex_object;
                    regex_object = create_regex_object(str,
                                                       global,
                                                       ignore_case,
                                                       multiline,
                                                       extended,
                                                       dotall,
                                                       anchored,
                                                       dollar_endonly,
                                                       ungreedy);
                    stack_ptr->mLongValue = 0;
                    stack_ptr->mObjectValue = regex_object;
                    stack_ptr++;
                }
                else
                {
                    int string_expression_offsets[32];
                    CLObject string_expression_object[32];
                    int i;
                    sBuf buf;
                    CLObject regex_object;
                    for (i = 0; i < num_string_expression; i++)
                    {
                        string_expression_offsets[i] = *(int *) pc;
                        pc += sizeof(int);
                        string_expression_object[i] = (stack_ptr - num_string_expression + i)->mObjectValue;
                    }
                    sBuf_init(&buf);
                    if (!string_expression(str,
                                           &buf,
                                           string_expression_offsets,
                                           string_expression_object,
                                           num_string_expression,
                                           &stack_ptr,
                                           stack,
                                           var_num,
                                           info))
                    {
                        vm_mutex_off();
                        remove_stack_to_stack_list(stack_id);
                        xfree(buf.mBuf);
                        return 0;
                    }
                    stack_ptr -= num_string_expression;
                    regex_object = create_regex_object(buf.mBuf,
                                                       global,
                                                       ignore_case,
                                                       multiline,
                                                       extended,
                                                       dotall,
                                                       anchored,
                                                       dollar_endonly,
                                                       ungreedy);
                    stack_ptr->mLongValue = 0;
                    stack_ptr->mObjectValue = regex_object;
                    stack_ptr++;
                    xfree(buf.mBuf);
                }
                vm_mutex_off();
            }
            break;
        }
    }
    remove_stack_to_stack_list(stack_id);
    return 1;
}
