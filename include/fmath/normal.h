#ifndef _FMATH_NORMAL_H_
#define _FMATH_NORMAL_H_

#include "internal/vector_base.h"
#include "internal/vector_traits.h"
#include "common.h"
#include "vector.h"

namespace fmath
{

template<typename T, size_t N>
class Normal : public internal::VectorBase<T, N>
{
public:
    using ValueType = T;
    static constexpr size_t DIMENSION = N;

public:
    using internal::VectorBase<T, N>::VectorBase;

    template<typename VectorU>
    FMATH_CONSTEXPR Normal(const VectorU &other);

    template<typename VectorU>
    FMATH_CONSTEXPR Normal &operator=(const VectorU &other);

    FMATH_INLINE FMATH_CONSTEXPR Normal operator+() const;

    FMATH_INLINE FMATH_CONSTEXPR Normal operator-() const;

    FMATH_INLINE Normal &operator+=(const Normal &other);

    FMATH_INLINE Normal &operator+=(const Vector<T, N> &vec);

    FMATH_INLINE Normal &operator+=(const ValueType &value);

    FMATH_INLINE Normal &operator-=(const Normal &other);

    FMATH_INLINE Normal &operator-=(const Vector<T, N> &vec);

    FMATH_INLINE Normal &operator-=(const ValueType &value);

    FMATH_INLINE Normal &operator*=(const ValueType &value);

    FMATH_INLINE Normal &operator/=(const ValueType &value);

    static FMATH_CONSTEXPR Normal zero();
};

namespace internal
{

template<typename T, size_t N>
struct VectorTraits_TypeInfo<Normal<T, N>>
{
    template<typename U, size_t M>
    using VectorType = Normal<U, M>;

    using ValueType = T;
    static constexpr size_t DIMENSION = N;
};

template<typename T, size_t N>
struct NormalTraits :
    VectorTraits_Add<T, N, Normal<T, N>>,
    VectorTraits_Assign<T, N, Normal<T, N>>,
    VectorTraits_Clamp<T, N, Normal<T, N>>,
    VectorTraits_Compare<T, N>,
    VectorTraits_ComponentWise<T, N, Normal<T, N>>,
    VectorTraits_Constants<T, N, Normal<T, N>>,
    VectorTraits_Input<T, N>,
    VectorTraits_Norm<T, N>,
    VectorTraits_Output<T, N>,
    VectorTraits_Scale<T, N, Normal<T, N>>,
    VectorTraits_Stringify<T, N>
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
FMATH_INLINE FMATH_CONSTEXPR bool operator<(const Normal<T, N> &n1, const Normal<T, N> &n2)
{
    return internal::NormalTraits<T, N>::less(n1, n2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool operator>(const Normal<T, N> &n1, const Normal<T, N> &n2)
{
    return internal::NormalTraits<T, N>::greater(n1, n2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool operator<=(const Normal<T, N> &n1, const Normal<T, N> &n2)
{
    return internal::NormalTraits<T, N>::lessOrEqual(n1, n2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool operator>=(const Normal<T, N> &n1, const Normal<T, N> &n2)
{
    return internal::NormalTraits<T, N>::greaterOrEqual(n1, n2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool equal(const Normal<T, N> &n1, const Normal<T, N> &n2)
{
    return internal::NormalTraits<T, N>::equal(n1, n2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool notEqual(const Normal<T, N> &n1, const Normal<T, N> &n2)
{
    return !equal(n1, n2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool equalEpsilon(const Normal<T, N> &n1, const Normal<T, N> &n2, const T &epsilon = constants::Epsilon<T>::value)
{
    return internal::NormalTraits<T, N>::equalEpsilon(n1, n2, epsilon);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool notEqualEpsilon(const Normal<T, N> &n1, const Normal<T, N> &n2, const T &epsilon = constants::Epsilon<T>::value)
{
    return !equalEpsilon(n1, n2, epsilon);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool less(const Normal<T, N> &n1, const Normal<T, N> &n2)
{
    return n1 < n2;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool greater(const Normal<T, N> &n1, const Normal<T, N> &n2)
{
    return n1 > n2;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool lessOrEqual(const Normal<T, N> &n1, const Normal<T, N> &n2)
{
    return n1 <= n2;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool greaterOrEqual(const Normal<T, N> &n1, const Normal<T, N> &n2)
{
    return n1 >= n2;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T minComponent(const Normal<T, N> &n)
{
    return internal::NormalTraits<T, N>::minComponent(n);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T maxComponent(const Normal<T, N> &n)
{
    return internal::NormalTraits<T, N>::maxComponent(n);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Normal<T, N> operator+(const Normal<T, N> &n1, const Normal<T, N> &n2)
{
    return internal::NormalTraits<T, N>::add(n1, n2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Normal<T, N> operator+(const Normal<T, N> &n, const Vector<T, N> &v)
{
    return internal::NormalTraits<T, N>::add(n, v);
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
FMATH_INLINE FMATH_CONSTEXPR Normal<T, N> operator-(const Normal<T, N> &n, const Vector<T, N> &v)
{
    return internal::NormalTraits<T, N>::sub(n, v);
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
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> reflect(const Vector<T, N> &v, const Normal<T, N> &n)
{
    return static_cast<T>(2) * (n * v) * n - v;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR std::string toString(const Normal<T, N> &vec, uint32 precision = 6)
{
    return internal::NormalTraits<T, N>::toString(vec, precision);
}

template<typename T, size_t N>
FMATH_INLINE std::ostream &operator<<(std::ostream &output, const Normal<T, N> &n)
{
    internal::NormalTraits<T, N>::write(output, n);
    return output;
}

template<typename T, size_t N>
FMATH_INLINE std::istream &operator>>(std::istream &input, Normal<T, N> &n)
{
    internal::NormalTraits<T, N>::read(input, n);
    return input;
}

template<typename T, size_t N>
    template<typename VectorU>
FMATH_CONSTEXPR Normal<T, N>::Normal(const VectorU &other)
{
    internal::NormalTraits<T, N>::template assign(*this, other);
}

template<typename T, size_t N>
    template<typename VectorU>
FMATH_CONSTEXPR Normal<T, N> &Normal<T, N>::operator=(const VectorU &other)
{
    internal::NormalTraits<T, N>::template assign(*this, other);
    return *this;
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
FMATH_INLINE Normal<T, N> &Normal<T, N>::operator+=(const Vector<T, N> &vec)
{
    *this = (*this) + vec;
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
FMATH_INLINE Normal<T, N> &Normal<T, N>::operator-=(const Vector<T, N> &vec)
{
    *this = (*this) - vec;
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

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Normal<T, N> clamp(const Normal<T, N> &normal, const Normal<T, N> &minv, const Normal<T, N> &maxv)
{
    return internal::NormalTraits<T, N>::clamp(normal, minv, maxv);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Normal<T, N> clamp(const Normal<T, N> &normal, const T &minv, const T &maxv)
{
    return internal::NormalTraits<T, N>::clamp(normal, minv, maxv);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Normal<T, N> lerp(const Normal<T, N> &n1, const Normal<T, N> &n2, const T &t)
{
    return n1 + (n2 - n1) * t;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Normal<T, N> componentWiseMin(const Normal<T, N> &n1, const Normal<T, N> &n2)
{
    return internal::NormalTraits<T, N>::componentWiseMin(n1, n2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Normal<T, N> componentWiseMax(const Normal<T, N> &n1, const Normal<T, N> &n2)
{
    return internal::NormalTraits<T, N>::componentWiseMax(n1, n2);
}

namespace constants
{

template<typename T, size_t N>
struct MinValue<Normal<T, N>>
{
    static constexpr Normal<T, N> value = internal::NormalTraits<T, N>::MIN_VALUE;
};

template<typename T, size_t N>
struct MaxValue<Normal<T, N>>
{
    static constexpr Normal<T, N> value = internal::NormalTraits<T, N>::MAX_VALUE;
};

}

template<typename T>
using Normal3 = Normal<T, 3>;

using Normal3u = Normal3<uint32>;
using Normal3i = Normal3<int32>;
using Normal3f = Normal3<float>;
using Normal3lf = Normal3<double>;

}

#endif