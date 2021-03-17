#ifndef _FMATH_VECTOR_H_
#define _FMATH_VECTOR_H_

#include <ostream>
#include <type_traits>

#include "internal/vector_base.h"
#include "common.h"
#include "compile_config.h"
#include "constants.h"
#include "scalar.h"

namespace fmath
{

template<typename T, size_t N>
class Vector : public internal::VectorBase<T, N>
{
public:
    using ValueType = T;
    static constexpr size_t SIZE = N;

public:
    using internal::VectorBase<T, N>::VectorBase;

    template<typename U, size_t M, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
    Vector(const Vector<U, M> &other);

    template<typename U, size_t M, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
    Vector &operator=(const Vector<U, M> &other);

    FMATH_INLINE FMATH_CONSTEXPR Vector operator+() const;

    FMATH_INLINE FMATH_CONSTEXPR Vector operator-() const;

    FMATH_INLINE Vector &operator+=(const Vector &other);

    FMATH_INLINE Vector &operator+=(const ValueType &value);

    FMATH_INLINE Vector &operator-=(const Vector &other);

    FMATH_INLINE Vector &operator-=(const ValueType &value);

    FMATH_INLINE Vector &operator*=(const ValueType &value);

    FMATH_INLINE Vector &operator/=(const ValueType &value);

    static FMATH_CONSTEXPR Vector zero();
};

namespace internal
{

template<typename T, size_t N>
struct VectorTraits : 
    VectorTraits_Add<T, N, Vector<T, N>>,
    VectorTraits_Compare<T, N>,
    VectorTraits_Dot<T, N>,
    VectorTraits_Hadamard<T, N, Vector<T, N>>,
    VectorTraits_Norm<T, N>,
    VectorTraits_Print<T, N>,
    VectorTraits_Scale<T, N, Vector<T, N>>
{};

}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool operator==(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return internal::VectorTraits<T, N>::equal(v1, v2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool operator!=(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return !internal::VectorTraits<T, N>::equal(v1, v2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool equal(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return internal::VectorTraits<T, N>::equal(v1, v2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool equalEpsilon(const Vector<T, N> &v1, const Vector<T, N> &v2, const T epsilon = number::Epsilon<T>::value)
{
    return internal::VectorTraits<T, N>::equalEpsilon(v1, v2, epsilon);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> operator+(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return internal::VectorTraits<T, N>::add(v1, v2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> operator+(const Vector<T, N> &vec, const T &value)
{
    return internal::VectorTraits<T, N>::add(vec, value);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> operator-(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return internal::VectorTraits<T, N>::sub(v1, v2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> operator-(const Vector<T, N> &vec, const T &value)
{
    return internal::VectorTraits<T, N>::sub(vec, value);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T operator*(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return internal::VectorTraits<T, N>::dot(v1, v2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> operator*(const Vector<T, N> &vec, const T &value)
{
    return internal::VectorTraits<T, N>::mul(vec, value);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> operator*(T value, const Vector<T, N> &vec)
{
    return internal::VectorTraits<T, N>::mul(vec, value);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> operator/(const Vector<T, N> &vec, const T &value)
{
    return internal::VectorTraits<T, N>::div(vec, value);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> add(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return v1 + v2;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> add(const Vector<T, N> &vec, const T &value)
{
    return vec + value;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> sub(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return v1 - v2;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> sub(const Vector<T, N> &vec, const T &value)
{
    return vec - value;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> mul(const Vector<T, N> &vec, const T &value)
{
    return vec * value;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> div(const Vector<T, N> &vec, const T &value)
{
    return vec / value;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T dot(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return internal::VectorTraits<T, N>::dot(v1, v2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> hadamardMul(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return internal::VectorTraits<T, N>::hadamardMul(v1, v2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> hadamardDiv(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return internal::VectorTraits<T, N>::hadamardDiv(v1, v2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T length2(const Vector<T, N> &vec)
{
    return internal::VectorTraits<T, N>::length2(vec);
}

template<typename T, size_t N>
FMATH_CONSTEXPR T length(const Vector<T, N> &vec)
{
    static_assert(std::is_floating_point_v<T>);
    return sqrt(length2(vec));
}

template<typename T, size_t N>
Vector<T, N> normalize(const Vector<T, N> &vec)
{
    static_assert(std::is_floating_point_v<T>);
    return internal::VectorTraits<T, N>::div(vec, length(vec));
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T cross(const Vector<T, 2> &v1, const Vector<T, 2> &v2)
{
    return v1.x * v2.y - v1.y * v2.x;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, 3> cross(const Vector<T, 3> &v1, const Vector<T, 3> &v2)
{
    return Vector<T, 3>(v1[1] * v2[2] - v1[2] * v2[1],
        v1[2] * v2[0] - v1[0] * v2[2],
        v1[0] * v2[1] - v1[1] * v2[0]
    );
}

template<typename T, size_t N>
std::ostream &operator<<(std::ostream &output, const Vector<T, N> &vec)
{
    internal::VectorTraits<T, N>::print(output, vec);
    return output;
}

template<typename T, size_t N>
    template<typename U, size_t M, typename>
Vector<T, N>::Vector(const Vector<U, M> &other)
    :   Vector()
{
    constexpr size_t REAL = min(SIZE, M);
    for (index_t i = 0; i < REAL; ++i)
        this->values[i] = static_cast<ValueType>(other[i]);
}

template<typename T, size_t N>
    template<typename U, size_t M, typename>
Vector<T, N> &Vector<T, N>::operator=(const Vector<U, M> &other)
{
    constexpr size_t REAL = min(SIZE, M);
    for (index_t i = 0; i < REAL; ++i)
        this->values[i] = static_cast<ValueType>(other[i]);
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> Vector<T, N>::operator+() const
{
    return Vector(*this);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> Vector<T, N>::operator-() const
{
    return zero() - (*this);
}

template<typename T, size_t N>
FMATH_INLINE Vector<T, N> &Vector<T, N>::operator+=(const Vector &other)
{
    *this = internal::VectorTraits<T, N>::add(*this, other);
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE Vector<T, N> &Vector<T, N>::operator+=(const ValueType &value)
{
    *this = internal::VectorTraits<T, N>::add(*this, value);
    return *this;
}

template<typename T, size_t N>
Vector<T, N> &Vector<T, N>::operator-=(const Vector &other)
{
    *this = internal::VectorTraits<T, N>::sub(*this, other);
    return *this;
}

template<typename T, size_t N>
Vector<T, N> &Vector<T, N>::operator*=(const ValueType &value)
{
    *this = internal::VectorTraits<T, N>::mul(*this, value);
    return *this;
}

template<typename T, size_t N>
Vector<T, N> &Vector<T, N>::operator/=(const ValueType &value)
{
    *this = internal::VectorTraits<T, N>::div(*this, value);
    return *this;
}

template<typename T, size_t N>
FMATH_CONSTEXPR Vector<T, N> Vector<T, N>::zero()
{
    return Vector();
}

template<typename T>
using Vector2 = Vector<T, 2>;

template<typename T>
using Vector3 = Vector<T, 3>;

template<typename T>
using Vector4 = Vector<T, 4>;

using Vector2u  = Vector2<uint32>;
using Vector2i  = Vector2<int32>;
using Vector2f  = Vector2<float>;
using Vector2lf = Vector2<double>;

using Vector3u  = Vector3<uint32>;
using Vector3i  = Vector3<int32>;
using Vector3f  = Vector3<float>;
using Vector3lf = Vector3<double>;

using Vector4u  = Vector4<uint32>;
using Vector4i  = Vector4<int32>;
using Vector4f  = Vector4<float>;
using Vector4lf = Vector4<double>;

}

#endif