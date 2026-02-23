#ifndef COMMON_H
#define COMMON_H

#include "include_asm.h"

typedef char s8;
typedef short s16;
typedef int s32;
typedef long s64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

typedef float f32;

#define UNK_TYPE s32
#define UNK_PTR void*
#define UNK_RET void
#define UNK_FUN_ARG void(*)(void)
#define UNK_FUN_PTR(name) void(*name)(void)
#define UNK_ARGS

#ifndef NULL
#define NULL  0
#endif
#ifndef TRUE
#define TRUE  1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))

#define GS_X_COORD(x) ((2048 - (640 / 2) + x) << 4)
#define GS_Y_COORD(y) ((2048 - (224 / 2) + y) << 4)

#define PR_EXTERN extern "C"

#define PR_SIZEOF(x) (int)(sizeof(x))
#define PR_ARRAYSIZEU(arr) (sizeof(arr) / sizeof(arr[0]))
#define PR_ARRAYSIZE(arr)  (s32)(sizeof(arr) / sizeof(arr[0]))
#define PR_CONCAT(x, y) ((x << 16) | (y))
#define PR_BIT(x) (1 << x)

#define PR_SCOPE()    {
#define PR_SCOPEEND() }

#define PR_ALIGNU(size, align) ((u_int)(size + (align - 1)) & ~(align - 1))
#define PR_ALIGN(size, align) ((size + (align - 1)) & ~(align - 1))

#define PR_ALIGNED(x) __attribute__((aligned(x)))

#define PR_UNCACHED(addr)      ((u_int)(addr) | 0x20000000)
#define PR_UNCACHEDACCEL(addr) ((u_int)(addr) | 0x30000000)

#define PR_PADDING(name, x) char name[x]

#define PR_BREAK() asm("break")

/* 3.14159265358979323846f */
#define PR_PI (float)M_PI

#endif /* COMMON_H */
