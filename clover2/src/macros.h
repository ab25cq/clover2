#ifndef MACROS_H
#define MACROS_H

#ifndef BOOL 
#define BOOL int
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef ALLOC
#define ALLOC                   // indicates this memory should be freed after used
#endif

#ifndef MANAGED
#define MANAGED                 // indicates this memory is managed inside the function
#endif

#ifndef NULLABLE
#define NULLABLE
#endif

#endif
