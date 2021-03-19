#ifndef _FMATH_NORMAL_H_
#define _FMATH_NORMAL_H_

#include "internal/vector_base.h"
#include "internal/vector_traits.h"
#include "common.h"

namespace fmath
{

template<typename T, size_t N>
class Normal : public internal::VectorBase<T, N>
{
public:
    using ValueType = T;
    static constexpr size_t SIZE = N;

public:
    using internal::VectorBase<T, N>::VectorBase;

    FMATH_INLINE FMATH_CONSTEXPR Normal operator+() const;
    FMATH_INLINE FMATH_CONSTEXPR Normal operator-() const;

    FMATH_INLINE Normal &operator+=(const Normal &other);
    FMATH_INLINE Normal &operator+=(const ValueType &value);
    FMATH_INLINE Normal &operator-=(const Normal &other);
    FMATH_INLINE Normal &operator-=(const ValueType &value);
    FMATH_INLINE Normal &operator*=(const ValueType &value);
    FMATH_INLINE Normal &operator/=(const ValueType &value);

    static FMATH_CONSTEXPR Normal zero();
};

namespace internal
{

template<typename T, size_t N>
struct NormalTraits :
    VectorTraits_Compare<T, N>,
    VectorTraits_Norm<T, N>,
    VectorTraits_Print<T, N>,
    VectorTraits_Scale<T, N, Normal<T, N>>
{};

}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool operator==(const Normal<T, N> &n1, const Normal<T, N> &n2)
{
    return internal::NormalTraits<T, N>::equal(n1, n2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool operator!=(const Normal<T, N> &n1, const Normal<T, N> &n2)
{
    return !internal::NormalTraits<T, N>::equal(n1, n2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool equal(const Normal<T, N> &n1, const Normal<T, N> &n2)
{
    return internal::NormalTraits<T, N>::equal(n1, n2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool equalEpsilon(const Normal<T, N> &n1, const Normal<T, N> &n2, const T &epsilon = number::Epsilon<T>::value)
{
    return internal::NormalTraits<T, N>::equalEpsilon(n1, n2, epsilon);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Normal<T, N> operator+(const Normal<T, N> &n1, const Normal<T, N> &n2)
{
    return internal::NormalTraits<T, N>::add(n1, n2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Normal<T, N> operator+(const Normal<T, N> &n, const T &value)
{
    return internal::NormalTraits<T, N>::add(n, value);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Normal<T, N> operator-(const Normal<T, N> &n1, const Normal<T, N> &n2)
{
    return internal::NormalTraits<T, N>::sub(n1, n2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Normal<T, N> operator-(const Normal<T, N> &n, const T &value)
{
    return internal::NormalTraits<T, N>::sub(n, value);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Normal<T, N> operator*(const Normal<T, N> &n, const T &value)
{
    return internal::NormalTraits<T, N>::mul(n, value);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Normal<T, N> operator*(const T &value, const Normal<T, N> &n)
{
    return internal::NormalTraits<T, N>::mul(n, value);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Normal<T, N> operator/(const Normal<T, N> &n, const T &value)
{
    return internal::NormalTraits<T, N>::div(n, value);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T length2(const Normal<T, N> &n)
{
    return internal::NormalTraits<T, N>::length2(n);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T length(const Normal<T, N> &n)
{
    static_assert(std::is_floating_point_v<T>);
    return sqrt(internal::NormalTraits<T, N>::length2(n));
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Normal<T, N> normalize(const Normal<T, N> &n)
{
    static_assert(std::is_floating_point_v<T>);
    return internal::NormalTraits<T, N>::div(n, length(n));
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Normal<T, N> Normal<T, N>::operator+() const
{
    return Normal();
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Normal<T, N> Normal<T, N>::operator-() const
{
    return zero() - Normal();
}

template<typename T, size_t N>
FMATH_INLINE Normal<T, N> &Normal<T, N>::operator+=(const Normal &other)
{
    *this = (*this) + other;
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE Normal<T, N> &Normal<T, N>::operator+=(const ValueType &value)
{
    *this = (*this) + value;
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE Normal<T, N> &Normal<T, N>::operator-=(const Normal &other)
{
    *this = (*this) - other;
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE Normal<T, N> &Normal<T, N>::operator-=(const ValueType &value)
{
    *this = (*this) - value;
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE Normal<T, N> &Normal<T, N>::operator*=(const ValueType &value)
{
    *this = (*this) * value;
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE Normal<T, N> &Normal<T, N>::operator/=(const ValueType &value)
{
    *this = (*this) / value;
    return *this;
}

template<typename T, size_t N>
FMATH_CONSTEXPR Normal<T, N> Normal<T, N>::zero()
{
    return Normal();
}

template<typename T>
using Normal3 = Normal<T, 3>;

using Normal3u = Normal3<uint32>;
using Normal3i = Normal3<int32>;
using Normal3f = Normal3<float>;
using Normal3lf = Normal3<double>;

}

#endif