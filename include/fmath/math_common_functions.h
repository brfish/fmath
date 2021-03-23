#ifndef _FMATH_COMMON_MATH_FUNCTIONS_H_
#define _FMATH_COMMON_MATH_FUNCTIONS_H_

#include <cmath>
#include <limits>

#include "internal/math_common_functions_impl.h"
#include "common.h"
#include "vector.h"

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
FMATH_INLINE FMATH_CONSTEXPR bool isInf(const T &value)
{
    return std::isinf(value);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool isFinite(const T &value)
{
    return std::isfinite(value);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T sin(const T &radian)
{
    return std::sin(radian);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T cos(const T &radian)
{
    return std::cos(radian);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T tan(const T &radian)
{
    return std::tan(radian);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T asin(const T &radian)
{
    return std::asin(radian);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T acos(const T &radian)
{
    return std::acos(radian);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T atan(const T &radian)
{
    return std::atan(radian);
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

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T lerp(const T &a, const T &b, double t)
{
    static_assert(std::is_floating_point_v<T>);
    FMATH_ASSERT(!isInf(a) && !isInf(b) && !isInf(t));
    return a + t * (b - a);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T lerp(const T &a, const T &b, float t)
{
    return lerp(a, b, static_cast<double>(t));
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
FMATH_INLINE FMATH_CONSTEXPR bool equalEpsilon(const T &a, const T &b, const T &epsilon = number::Epsilon<T>::value)
{
    return abs(a - b) <= epsilon;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool notEqualEpsilon(const T &a, const T &b, const T &epsilon = number::Epsilon<T>::value)
{
    return !equalEpsilon(a, b, epsilon);
}

FMATH_INLINE FMATH_CONSTEXPR angle_t toDegree(angle_t radian)
{
    return radian / number::Pi<angle_t>::value * static_cast<angle_t>(180);
}

FMATH_INLINE FMATH_CONSTEXPR angle_t toRadian(angle_t degree)
{
    return degree / static_cast<angle_t>(180) * number::Pi<angle_t>::value;
}

}

#endif