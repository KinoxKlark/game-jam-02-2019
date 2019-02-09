#ifndef INTRINSIC_H
#define INTRINSIC_H

#ifdef WIN32

#include <stdint.h>

typedef float r32;
typedef double r64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef int8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#else

typedef float r32;
typedef double r64;

typedef char i8;
typedef short int i16;
typedef int i32;
typedef long int i64;

typedef unsigned char  u8;
typedef unsigned short int u16;
typedef unsigned int u32;
typedef unsigned long int u64;

#endif

#endif
