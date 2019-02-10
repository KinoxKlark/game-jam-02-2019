#ifndef INTRINSIC_H
#define INTRINSIC_H

#include <cmath>
#include <stdint.h>
#include <SFML/System/Vector2.hpp>

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

typedef sf::Vector2<r32> vector;

inline
r32 norm(vector const& vec)
{
	r32 norm = std::sqrt(vec.x*vec.x + vec.y*vec.y);
	return norm;
}

inline
r32 dot_product(vector u, vector v)
{
	r32 result = u.x*v.x + u.y*v.y;
	return result;
}

inline
vector safe_normalise(vector vec)
{
	r32 vec_norm = norm(vec);
	if(vec_norm > 0.001)
		vec /= vec_norm;
	return vec;
}

#endif
