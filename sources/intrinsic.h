#ifndef INTRINSIC_H
#define INTRINSIC_H

#ifdef WIN32

typedef float r32;
typedef double r64;

typedef  __int8 i8;
typedef __int16 i16;
typedef __int32 i32;
typedef __int64 i64;

typedef unsigned __int8  u8;
typedef unsigned __int16 u16;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;

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
