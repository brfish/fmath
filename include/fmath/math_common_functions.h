#ifndef _FMATH_COMMON_MATH_FUNCTIONS_H_
#define _FMATH_COMMON_MATH_FUNCTIONS_H_

#include <cmath>
#include <limits>
#include <type_traits>

#include "internal/math_common_functions_impl.h"
#include "common.h"
#include "constants.h"

namespace fmath
{

template<typename T>
struct IsIEC559
{
    static constexpr bool value = std::numeric_limits<T>::is_iec559;
};

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool isNaN(const T &value)
{
    return std::isnan(value);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool isInfinite(const T &value)
{
    return std::isinf(value);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool isFinite(const T &value)
{
    return std::isfinite(value);
}

FMATH_INLINE FMATH_CONSTEXPR angle_t toDegree(angle_t radian)
{
    return radian / constants::Pi<angle_t>::value * static_cast<angle_t>(180);
}

FMATH_INLINE FMATH_CONSTEXPR angle_t toRadian(angle_t degree)
{
    return degree / static_cast<angle_t>(180) * constants::Pi<angle_t>::value;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T sin(const T &angle)
{
#if defined(FMATH_USE_DEGREE)
    return std::sin(toRadian(angle));
#else
    return std::sin(angle);
#endif
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T cos(const T &angle)
{
#if defined(FMATH_USE_DEGREE)
    return std::cos(toRadian(angle));
#else
    return std::cos(angle);
#endif
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T tan(const T &angle)
{
#if defined(FMATH_USE_DEGREE)
    return std::tan(toRadian(angle));
#else
    return std::tan(angle);
#endif
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T asin(const T &angle)
{
#if defined(FMATH_USE_DEGREE)
    return std::asin(toRadian(angle));
#else
    return std::asin(angle);
#endif
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T acos(const T &angle)
{
#if defined(FMATH_USE_DEGREE)
    return std::acos(toRadian(angle));
#else
    return std::acos(angle);
#endif
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T atan(const T &angle)
{
#if defined(FMATH_USE_DEGREE)
    return std::atan(toRadian(angle));
#else
    return std::atan(angle);
#endif
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T exp(const T &exponent)
{
    return std::exp(exponent);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T exp2(const T &exponent)
{
    return std::exp2(exponent);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T ln(const T &x)
{
    return std::log(x);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T log10(const T &x)
{
    return std::log10(x);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T log2(const T &x)
{
    return std::log2(x);
}

template<typename BaseT, typename ExponentT>
FMATH_INLINE FMATH_CONSTEXPR BaseT pow(const BaseT &base, const ExponentT &exponent)
{
    return std::pow(base, exponent);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T sqrt(const T &value)
{
    return std::sqrt(value);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T cbrt(const T &value)
{
    return std::cbrt(value);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T ceil(const T &value)
{
    return std::ceil(value);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T floor(const T &value)
{
    return std::floor(value);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T trunc(const T &value)
{
    return std::trunc(value);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T round(const T &value)
{
    return std::round(value);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T abs(const T &value)
{
    return std::abs(value);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T sign(const T &value)
{
    return internal::SignImpl<T>::compute(value);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T max(const T &a, const T &b)
{
    return internal::MaxImpl<T>::compute(a, b);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T min(const T &a, const T &b)
{
    return internal::MinImpl<T>::compute(a, b);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T clamp(const T &v, const T &minv, const T &maxv)
{
    return min(maxv, max(v, minv));
}

template<typename T, typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
FMATH_INLINE FMATH_CONSTEXPR T clamp(const T &v, const U &minv, const U &maxv)
{
    return min(static_cast<T>(maxv), max(v, static_cast<T>(minv)));
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T lerp(const T &a, const T &b, const T &t)
{
    static_assert(std::is_floating_point_v<T>);
    FMATH_ASSERT(!isInfinite(a) && !isInfinite(b) && !isInfinite(t));
    return a + t * (b - a);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool equal(const T &a, const T &b)
{
    return a == b;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool notEqual(const T &a, const T &b)
{
    return !equal(a, b);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool equalEpsilon(const T &a, const T &b, const T &epsilon = constants::Epsilon<T>::value)
{
    return abs(a - b) <= epsilon;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool notEqualEpsilon(const T &a, const T &b, const T &epsilon = constants::Epsilon<T>::value)
{
    return !equalEpsilon(a, b, epsilon);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool less(const T &a, const T &b)
{
    return a < b;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool greater(const T &a, const T &b)
{
    return a > b;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool lessOrEqual(const T &a, const T &b)
{
    return a <= b;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool greaterOrEqual(const T &a, const T &b)
{
    return a >= b;
}

}

#endif