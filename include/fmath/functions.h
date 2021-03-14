#ifndef _FMATH_FUNCTIONS_H_
#define _FMATH_FUNCTIONS_H_

#include <cmath>

#include "common.h"
#include "compile_config.h"
#include "constants.h"

namespace fmath
{

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR int32 sign(const T &value)
{
    return value == 0 ? 0 : (value > 0 ? 1 : -1);
}

template<typename T>
FMATH_CONSTEXPR T abs(const T &value)
{
    return value < 0 ? -value : value;
}

template<typename T>
FMATH_CONSTEXPR T max(const T &a, const T &b)
{
    return a > b ? a : b;
}

template<typename T>
FMATH_CONSTEXPR T min(const T &a, const T &b)
{
    return a < b ? a : b;
}

template<typename T>
FMATH_CONSTEXPR T sqrt(const T &value)
{
    return std::sqrt(value);
}

// Trigonometric functions
template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T sin(const T &value)
{
    return std::sin(value);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T cos(const T &value)
{
    return std::cos(value);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T tan(const T &value)
{
    return std::tan(value);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T asin(const T &value)
{
    return std::asin(value);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T acos(const T &value)
{
    return std::acos(value);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T atan(const T &value)
{
    return std::atan(value);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool equalEpsilon(const T &a, const T &b, const T &epsilon = Epsilon<T>::value)
{
    return abs(a - b) < epsilon;
}

}

#endif