#ifndef _FMATH_INTERNAL_MATH_COMMON_FUNCTIONS_H_
#define _FMATH_INTERNAL_MATH_COMMON_FUNCTIONS_H_

#include <cmath>
#include <type_traits>

#include "common.h"

namespace fmath
{
namespace internal
{

template<typename T, typename = void>
struct MaxImpl
{
    static FMATH_INLINE FMATH_CONSTEXPR T compute(const T &a, const T &b)
    {
        return a > b ? a : b;
    }
};

template<typename T>
struct MaxImpl<T, std::enable_if_t<std::is_integral_v<T>>>
{
    static FMATH_INLINE FMATH_CONSTEXPR T compute(const T &a, const T &b)
    {
        return  a ^ ((a ^ b) & -(a < b));
    }
};

template<typename T>
struct MaxImpl<T, std::enable_if_t<std::is_floating_point_v<T>>>
{
    static FMATH_INLINE FMATH_CONSTEXPR T compute(const T &a, const T &b)
    {
        return  std::fmax(a, b);
    }
};

template<typename T, typename = void>
struct MinImpl
{
    static FMATH_INLINE FMATH_CONSTEXPR T compute(const T &a, const T &b)
    {
        return a < b ? a : b;
    }
};

template<typename T>
struct MinImpl<T, std::enable_if_t<std::is_floating_point_v<T>>>
{
    static FMATH_INLINE FMATH_CONSTEXPR T compute(const T &a, const T &b)
    {
        return  std::fmin(a, b);
    }
};

template<typename T>
struct MinImpl<T, std::enable_if_t<std::is_integral_v<T>>>
{
    static FMATH_INLINE FMATH_CONSTEXPR T compute(const T &a, const T &b)
    {
        return  b ^ ((a ^ b) & -(a < b));
    }
};

template<typename T, typename = void>
struct SignImpl
{};

template<typename T>
struct SignImpl<T, std::enable_if_t<std::is_signed_v<T>>>
{
    static FMATH_INLINE FMATH_CONSTEXPR T sign(const T &value)
    {
        return static_cast<T>((value > static_cast<T>(0)) - (value < static_cast<T>(0)));
    }
};

template<typename T>
struct SignImpl<T, std::enable_if_t<std::is_unsigned_v<T>>>
{
    static FMATH_INLINE FMATH_CONSTEXPR T sign(const T &value)
    {
        return static_cast<T>(value > static_cast<T>(0));
    }
};

}
}

#endif