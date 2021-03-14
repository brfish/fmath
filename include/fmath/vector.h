#ifndef _FMATH_VECTOR_H_
#define _FMATH_VECTOR_H_

#include <ostream>
#include <type_traits>

#include "internal/vector_storage.h"
#include "common.h"
#include "compile_config.h"
#include "constants.h"

namespace fmath
{

template<typename T, size_t N>
class Vector : public internal::VectorStorage<T, N>
{
public:
    using ValueType = T;
    static constexpr size_t SIZE = N;

public:
    using internal::VectorStorage<T, N>::VectorStorage;

    FMATH_CONSTEXPR Vector(const Vector &other);
    explicit FMATH_CONSTEXPR Vector(const ValueType *data, size_t n);

    template<typename U, size_t M, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
    FMATH_CONSTEXPR Vector(const Vector<U, M> &other);
    
    FMATH_CONSTEXPR Vector &operator=(const Vector &other);

    template<typename U, size_t M, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
    FMATH_CONSTEXPR Vector &operator=(const Vector<U, M> &other);

    FMATH_INLINE FMATH_CONSTEXPR bool equals(const Vector &other) const;

    FMATH_INLINE FMATH_CONSTEXPR size_t size() const;

    FMATH_INLINE FMATH_CONSTEXPR const ValueType *data() const;

    FMATH_INLINE FMATH_CONSTEXPR ValueType *data();

    FMATH_INLINE FMATH_CONSTEXPR const ValueType &get(index_t index) const;

    FMATH_INLINE FMATH_CONSTEXPR ValueType &get(index_t index);

    FMATH_INLINE void set(index_t index, const ValueType &value);

    FMATH_INLINE FMATH_CONSTEXPR const ValueType &operator[](index_t index) const;

    FMATH_INLINE FMATH_CONSTEXPR ValueType &operator[](index_t index);

    FMATH_INLINE FMATH_CONSTEXPR Vector operator+() const;

    FMATH_INLINE FMATH_CONSTEXPR Vector operator-() const;

    Vector &operator+=(const Vector &other);

    Vector &operator+=(const ValueType &value);

    Vector &operator-=(const Vector &other);

    Vector &operator-=(const ValueType &value);

    Vector &operator*=(const ValueType &value);

    Vector &operator/=(const ValueType &value);

    static Vector zero();
};

namespace internal
{

template<typename T, size_t N>
struct VectorTraits
{
    using ValueType = T;
    using VectorType = Vector<T, N>;
    static constexpr size_t SIZE = N;

    static FMATH_CONSTEXPR bool equal(const Vector<T, N> &v1, const Vector<T, N> &v2);
    static FMATH_CONSTEXPR bool equalEpsilon(const Vector<T, N> &v1, const Vector<T, N> &v2, const T &epsilon = Epsilon<T>::value);

    static FMATH_CONSTEXPR Vector<T, N> add(const Vector<T, N> &v1, const Vector<T, N> &v2);
    static FMATH_CONSTEXPR Vector<T, N> add(const Vector<T, N> &v, const T &value);
    static FMATH_CONSTEXPR Vector<T, N> sub(const Vector<T, N> &v1, const Vector<T, N> &v2);
    static FMATH_CONSTEXPR Vector<T, N> sub(const Vector<T, N> &v, const T &value);
    static FMATH_CONSTEXPR Vector<T, N> mul(const Vector<T, N> &v, const T &value);
    static FMATH_CONSTEXPR Vector<T, N> div(const Vector<T, N> &v, const T &value);
    static FMATH_CONSTEXPR T dot(const Vector<T, N> &v1, const Vector<T, N> &v2);
    static FMATH_CONSTEXPR Vector<T, N> hadamardMul(const Vector<T, N> &v1, const Vector<T, N> &v2);
    static FMATH_CONSTEXPR Vector<T, N> hadamardDiv(const Vector<T, N> &v1, const Vector<T, N> &v2);
    static FMATH_CONSTEXPR T length2(const Vector<T, N> &v);
};

template<typename T, size_t N>
FMATH_CONSTEXPR bool VectorTraits<T, N>::equal(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    for (index_t i = 0; i < N; ++i)
    {
        if (v1[i] != v2[i])
            return false;
    }
    return true;
}

template<typename T, size_t N>
FMATH_CONSTEXPR bool VectorTraits<T, N>::equalEpsilon(const Vector<T, N> &v1, const Vector<T, N> &v2, const T &epsilon)
{
    for (index_t i = 0; i < N; ++i)
    {
        if (abs(v1[i] - v2[i]) >= epsilon)
            return false;
    }
    return true;
}

template<typename T, size_t N>
FMATH_CONSTEXPR Vector<T, N> VectorTraits<T, N>::add(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    Vector<T, N> result;
    for (index_t i = 0; i < N; ++i)
        result[i] = v1[i] + v2[i];
    return result;
}

template<typename T, size_t N>
FMATH_CONSTEXPR Vector<T, N> VectorTraits<T, N>::add(const Vector<T, N> &v, const T &value)
{
    Vector<T, N> result;
    for (index_t i = 0; i < N; ++i)
        result[i] = v[i] + value;
    return result;
}

template<typename T, size_t N>
FMATH_CONSTEXPR Vector<T, N> VectorTraits<T, N>::sub(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    Vector<T, N> result;
    for (index_t i = 0; i < N; ++i)
        result[i] = v1[i] - v2[i];
    return result;
}

template<typename T, size_t N>
FMATH_CONSTEXPR Vector<T, N> VectorTraits<T, N>::sub(const Vector<T, N> &v, const T &value)
{
    Vector<T, N> result;
    for (index_t i = 0; i < N; ++i)
        result[i] = v[i] - value;
    return result;
}

template<typename T, size_t N>
FMATH_CONSTEXPR Vector<T, N> VectorTraits<T, N>::mul(const Vector<T, N> &v, const T &value)
{
    Vector<T, N> result;
    for (index_t i = 0; i < N; ++i)
        result[i] = v[i] * value;
    return result;
}

template<typename T, size_t N>
FMATH_CONSTEXPR Vector<T, N> VectorTraits<T, N>::div(const Vector<T, N> &v, const T &value)
{
    Vector<T, N> result;
    for (index_t i = 0; i < N; ++i)
        result[i] = v[i] / value;
    return result;
}

template<typename T, size_t N>
FMATH_CONSTEXPR T VectorTraits<T, N>::dot(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    T result = 0;
    for (index_t i = 0; i < N; ++i)
        result += v1[i] * v2[i];
    return result;
}

template<typename T, size_t N>
FMATH_CONSTEXPR Vector<T, N> VectorTraits<T, N>::hadamardMul(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    Vector<T, N> result;
    for (index_t i = 0; i < N; ++i)
        result[i] = v1[i] * v2[i];
    return result;
}

template<typename T, size_t N>
FMATH_CONSTEXPR Vector<T, N> VectorTraits<T, N>::hadamardDiv(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    Vector<T, N> result;
    for (index_t i = 0; i < N; ++i)
        result[i] = v1[i] / v2[i];
    return result;
}

template<typename T, size_t N>
FMATH_CONSTEXPR T VectorTraits<T, N>::length2(const Vector<T, N> &v)
{
    T result = 0;
    for (index_t i = 0; i < N; ++i)
        result += v[i] * v[i];
    return result;
}

template<typename T>
struct VectorTraits<T, 2>
{
    using ValueType = T;
    using VectorType = Vector<T, 2>;
    static constexpr size_t SIZE = 2;

    static FMATH_CONSTEXPR bool equal(const Vector<T, 2> &v1, const Vector<T, 2> &v2);
    static FMATH_CONSTEXPR bool equalEpsilon(const Vector<T, 2> &v1, const Vector<T, 2> &v2, const T &epsilon = Epsilon<T>::value);

    static FMATH_CONSTEXPR Vector<T, 2> add(const Vector<T, 2> &v1, const Vector<T, 2> &v2);
    static FMATH_CONSTEXPR Vector<T, 2> add(const Vector<T, 2> &v, const T &value);
    static FMATH_CONSTEXPR Vector<T, 2> sub(const Vector<T, 2> &v1, const Vector<T, 2> &v2);
    static FMATH_CONSTEXPR Vector<T, 2> sub(const Vector<T, 2> &v, const T &value);
    static FMATH_CONSTEXPR Vector<T, 2> mul(const Vector<T, 2> &v, const T &value);
    static FMATH_CONSTEXPR Vector<T, 2> div(const Vector<T, 2> &v, const T &value);
    static FMATH_CONSTEXPR T dot(const Vector<T, 2> &v1, const Vector<T, 2> &v2);
    static FMATH_CONSTEXPR Vector<T, 2> hadamardMul(const Vector<T, 2> &v1, const Vector<T, 2> &v2);
    static FMATH_CONSTEXPR Vector<T, 2> hadamardDiv(const Vector<T, 2> &v1, const Vector<T, 2> &v2);
    static FMATH_CONSTEXPR T length2(const Vector<T, 2> &v);
    
    static FMATH_CONSTEXPR T cross(const Vector<T, 2> &v1, const Vector<T, 2> &v2);
};

template<typename T>
FMATH_CONSTEXPR bool VectorTraits<T, 2>::equal(const Vector<T, 2> &v1, const Vector<T, 2> &v2)
{
    return v1.x == v2.x && v1.y == v2.y;
}

template<typename T>
FMATH_CONSTEXPR bool VectorTraits<T, 2>::equalEpsilon(const Vector<T, 2> &v1, const Vector<T, 2> &v2, const T &epsilon)
{
    return equalEpsilon(v1.x, v2.x, epsilon) && equalEpsilon(v1.y, v2.y, epsilon);
}

template<typename T>
FMATH_CONSTEXPR Vector<T, 2> VectorTraits<T, 2>::add(const Vector<T, 2> &v1, const Vector<T, 2> &v2)
{
    return Vector<T, 2>(v1.x + v2.x, v1. y + v2.y);
}

template<typename T>
FMATH_CONSTEXPR Vector<T, 2> VectorTraits<T, 2>::add(const Vector<T, 2> &v, const T &value)
{
    return Vector<T, 2>(v.x + value, v.y + value);
}

template<typename T>
FMATH_CONSTEXPR Vector<T, 2> VectorTraits<T, 2>::sub(const Vector<T, 2> &v1, const Vector<T, 2> &v2)
{
    return Vector<T, 2>(v1.x - v2.x, v1.y - v2.y);
}

template<typename T>
FMATH_CONSTEXPR Vector<T, 2> VectorTraits<T, 2>::sub(const Vector<T, 2> &v, const T &value)
{
    return Vector<T, 2>(v.x - value, v.y - value);
}

template<typename T>
FMATH_CONSTEXPR Vector<T, 2> VectorTraits<T, 2>::mul(const Vector<T, 2> &v, const T &value)
{
    return Vector<T, 2>(v.x * value, v.y * value);
}

template<typename T>
FMATH_CONSTEXPR Vector<T, 2> VectorTraits<T, 2>::div(const Vector<T, 2> &v, const T &value)
{
    return Vector<T, 2>(v.x / value, v.y / value);
}

template<typename T>
FMATH_CONSTEXPR T VectorTraits<T, 2>::dot(const Vector<T, 2> &v1, const Vector<T, 2> &v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

template<typename T>
FMATH_CONSTEXPR Vector<T, 2> VectorTraits<T, 2>::hadamardMul(const Vector<T, 2> &v1, const Vector<T, 2> &v2)
{
    return Vector<T, 2>(v1.x * v2.x, v1.y * v2.y);
}

template<typename T>
FMATH_CONSTEXPR Vector<T, 2> VectorTraits<T, 2>::hadamardDiv(const Vector<T, 2> &v1, const Vector<T, 2> &v2)
{
    return Vector<T, 2>(v1.x / v2.x, v1.y / v2.y);
}

template<typename T>
FMATH_CONSTEXPR T VectorTraits<T, 2>::length2(const Vector<T, 2> &v)
{
    return v.x * v.x + v.y * v.y;
}

template<typename T>
FMATH_CONSTEXPR T VectorTraits<T, 2>::cross(const Vector<T, 2> &v1, const Vector<T, 2> &v2)
{
    return v1.x * v2.y - v1.y * v2.x;
}

template<typename T>
struct VectorTraits<T, 3>
{
    using ValueType = T;
    using VectorType = Vector<T, 3>;
    static constexpr size_t SIZE = 3;

    static FMATH_CONSTEXPR bool equal(const Vector<T, 3> &v1, const Vector<T, 3> &v2);
    static FMATH_CONSTEXPR bool equalEpsilon(const Vector<T, 3> &v1, const Vector<T, 3> &v2, const T &epsilon = Epsilon<T>::value);

    static FMATH_CONSTEXPR Vector<T, 3> add(const Vector<T, 3> &v1, const Vector<T, 3> &v2);
    static FMATH_CONSTEXPR Vector<T, 3> add(const Vector<T, 3> &v, const T &value);
    static FMATH_CONSTEXPR Vector<T, 3> sub(const Vector<T, 3> &v1, const Vector<T, 3> &v2);
    static FMATH_CONSTEXPR Vector<T, 3> sub(const Vector<T, 3> &v, const T &value);
    static FMATH_CONSTEXPR Vector<T, 3> mul(const Vector<T, 3> &v, const T &value);
    static FMATH_CONSTEXPR Vector<T, 3> div(const Vector<T, 3> &v, const T &value);
    static FMATH_CONSTEXPR T dot(const Vector<T, 3> &v1, const Vector<T, 3> &v2);
    static FMATH_CONSTEXPR Vector<T, 3> hadamardMul(const Vector<T, 3> &v1, const Vector<T, 3> &v2);
    static FMATH_CONSTEXPR Vector<T, 3> hadamardDiv(const Vector<T, 3> &v1, const Vector<T, 3> &v2);
    static FMATH_CONSTEXPR T length2(const Vector<T, 3> &v);

    static FMATH_CONSTEXPR Vector<T, 3> cross(const Vector<T, 3> &v1, const Vector<T, 3> &v2);
};

template<typename T>
FMATH_CONSTEXPR bool VectorTraits<T, 3>::equal(const Vector<T, 3> &v1, const Vector<T, 3> &v2)
{
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

template<typename T>
FMATH_CONSTEXPR bool VectorTraits<T, 3>::equalEpsilon(const Vector<T, 3> &v1, const Vector<T, 3> &v2, const T &epsilon)
{
    return equalEpsilon(v1.x, v2.x, epsilon) && 
        equalEpsilon(v1.y, v2.y, epsilon) &&
        equalEpsilon(v1.z, v2.z, epsilon);
}

template<typename T>
FMATH_CONSTEXPR Vector<T, 3> VectorTraits<T, 3>::add(const Vector<T, 3> &v1, const Vector<T, 3> &v2)
{
    return Vector<T, 3>(v1.x + v2.x, v1. y + v2.y, v1.z + v2.z);
}

template<typename T>
FMATH_CONSTEXPR Vector<T, 3> VectorTraits<T, 3>::add(const Vector<T, 3> &v, const T &value)
{
    return Vector<T, 3>(v.x + value, v.y + value, v.z + value);
}

template<typename T>
FMATH_CONSTEXPR Vector<T, 3> VectorTraits<T, 3>::sub(const Vector<T, 3> &v1, const Vector<T, 3> &v2)
{
    return Vector<T, 3>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

template<typename T>
FMATH_CONSTEXPR Vector<T, 3> VectorTraits<T, 3>::sub(const Vector<T, 3> &v, const T &value)
{
    return Vector<T, 3>(v.x - value, v.y - value, v.z - value);
}

template<typename T>
FMATH_CONSTEXPR Vector<T, 3> VectorTraits<T, 3>::mul(const Vector<T, 3> &v, const T &value)
{
    return Vector<T, 3>(v.x * value, v.y * value, v.z * value);
}

template<typename T>
FMATH_CONSTEXPR Vector<T, 3> VectorTraits<T, 3>::div(const Vector<T, 3> &v, const T &value)
{
    return Vector<T, 3>(v.x / value, v.y / value, v.z / value);
}

template<typename T>
FMATH_CONSTEXPR T VectorTraits<T, 3>::dot(const Vector<T, 3> &v1, const Vector<T, 3> &v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template<typename T>
FMATH_CONSTEXPR Vector<T, 3> VectorTraits<T, 3>::hadamardMul(const Vector<T, 3> &v1, const Vector<T, 3> &v2)
{
    return Vector<T, 3>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

template<typename T>
FMATH_CONSTEXPR Vector<T, 3> VectorTraits<T, 3>::hadamardDiv(const Vector<T, 3> &v1, const Vector<T, 3> &v2)
{
    return Vector<T, 3>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

template<typename T>
FMATH_CONSTEXPR T VectorTraits<T, 3>::length2(const Vector<T, 3> &v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

template<typename T>
FMATH_CONSTEXPR Vector<T, 3> VectorTraits<T, 3>::cross(const Vector<T, 3> &v1, const Vector<T, 3> &v2)
{
    return Vector<T, 3>(v1[1] * v2[2] - v1[2] * v2[1],
        v1[2] * v2[0] - v1[0] * v2[2],
        v1[0] * v2[1] - v1[1] * v2[0]);
}

template<typename T>
struct VectorTraits<T, 4>
{
    using ValueType = T;
    using VectorType = Vector<T, 4>;
    static constexpr size_t SIZE = 4;

    static FMATH_CONSTEXPR bool equal(const Vector<T, 4> &v1, const Vector<T, 4> &v2);
    static FMATH_CONSTEXPR bool equalEpsilon(const Vector<T, 4> &v1, const Vector<T, 4> &v2, const T &epsilon = Epsilon<T>::value);

    static FMATH_CONSTEXPR Vector<T, 4> add(const Vector<T, 4> &v1, const Vector<T, 4> &v2);
    static FMATH_CONSTEXPR Vector<T, 4> add(const Vector<T, 4> &v, const T &value);
    static FMATH_CONSTEXPR Vector<T, 4> sub(const Vector<T, 4> &v1, const Vector<T, 4> &v2);
    static FMATH_CONSTEXPR Vector<T, 4> sub(const Vector<T, 4> &v, const T &value);
    static FMATH_CONSTEXPR Vector<T, 4> mul(const Vector<T, 4> &v, const T &value);
    static FMATH_CONSTEXPR Vector<T, 4> div(const Vector<T, 4> &v, const T &value);
    static FMATH_CONSTEXPR T dot(const Vector<T, 4> &v1, const Vector<T, 4> &v2);
    static FMATH_CONSTEXPR Vector<T, 4> hadamardMul(const Vector<T, 4> &v1, const Vector<T, 4> &v2);
    static FMATH_CONSTEXPR Vector<T, 4> hadamardDiv(const Vector<T, 4> &v1, const Vector<T, 4> &v2);
    static FMATH_CONSTEXPR T length2(const Vector<T, 4> &v);
};

template<typename T>
FMATH_CONSTEXPR bool VectorTraits<T, 4>::equal(const Vector<T, 4> &v1, const Vector<T, 4> &v2)
{
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w;
}

template<typename T>
FMATH_CONSTEXPR bool VectorTraits<T, 4>::equalEpsilon(const Vector<T, 4> &v1, const Vector<T, 4> &v2, const T &epsilon)
{
    return equalEpsilon(v1.x, v2.x, epsilon) && 
        equalEpsilon(v1.y, v2.y, epsilon) &&
        equalEpsilon(v1.z, v2.z, epsilon) &&
        equalEpsilon(v1.w, v2.w, epsilon);
}

template<typename T>
FMATH_CONSTEXPR Vector<T, 4> VectorTraits<T, 4>::add(const Vector<T, 4> &v1, const Vector<T, 4> &v2)
{
    return Vector<T, 4>(v1.x + v2.x, v1. y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

template<typename T>
FMATH_CONSTEXPR Vector<T, 4> VectorTraits<T, 4>::add(const Vector<T, 4> &v, const T &value)
{
    return Vector<T, 4>(v.x + value, v.y + value, v.z + value, v.w + value);
}

template<typename T>
FMATH_CONSTEXPR Vector<T, 4> VectorTraits<T, 4>::sub(const Vector<T, 4> &v1, const Vector<T, 4> &v2)
{
    return Vector<T, 4>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

template<typename T>
FMATH_CONSTEXPR Vector<T, 4> VectorTraits<T, 4>::sub(const Vector<T, 4> &v, const T &value)
{
    return Vector<T, 4>(v.x - value, v.y - value, v.z - value, v.w - value);
}

template<typename T>
FMATH_CONSTEXPR Vector<T, 4> VectorTraits<T, 4>::mul(const Vector<T, 4> &v, const T &value)
{
    return Vector<T, 4>(v.x * value, v.y * value, v.z * value, v.w * value);
}

template<typename T>
FMATH_CONSTEXPR Vector<T, 4> VectorTraits<T, 4>::div(const Vector<T, 4> &v, const T &value)
{
    return Vector<T, 4>(v.x / value, v.y / value, v.z / value, v.w / value);
}

template<typename T>
FMATH_CONSTEXPR T VectorTraits<T, 4>::dot(const Vector<T, 4> &v1, const Vector<T, 4> &v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

template<typename T>
FMATH_CONSTEXPR Vector<T, 4> VectorTraits<T, 4>::hadamardMul(const Vector<T, 4> &v1, const Vector<T, 4> &v2)
{
    return Vector<T, 4>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}

template<typename T>
FMATH_CONSTEXPR Vector<T, 4> VectorTraits<T, 4>::hadamardDiv(const Vector<T, 4> &v1, const Vector<T, 4> &v2)
{
    return Vector<T, 4>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
}

template<typename T>
FMATH_CONSTEXPR T VectorTraits<T, 4>::length2(const Vector<T, 4> &v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
}

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
FMATH_INLINE FMATH_CONSTEXPR T operator*(const Vector<T, N> &a, const Vector<T, N> &b)
{
    return internal::VectorTraits<T, N>::dot(a, b);
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
    return internal::VectorTraits<T, 2>::cross(v1, v2);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, 3> cross(const Vector<T, 3> &v1, const Vector<T, 3> &v2)
{
    return internal::VectorTraits<T, 3>::cross(v1, v2);
}


template<typename T, size_t N>
FMATH_CONSTEXPR Vector<T, N>::Vector(const Vector &other)
{
    memcpy(data(), other.data(), sizeof(ValueType) * SIZE);
}

template<typename T, size_t N>
FMATH_CONSTEXPR Vector<T, N>::Vector(const ValueType *data, size_t n)
    :   Vector()
{
    memcpy(data(), data, sizeof(ValueType) * min(SIZE, n));
}

template<typename T, size_t N>
    template<typename U, size_t M, typename>
FMATH_CONSTEXPR Vector<T, N>::Vector(const Vector<U, M> &other)
    :   Vector()
{
    FMATH_CONSTEXPR size_t REAL = min(SIZE, M);
    for (index_t i = 0; i < REAL; ++i)
        this->values[i] = static_cast<ValueType>(other[i]);
}

template<typename T, size_t N>
FMATH_CONSTEXPR Vector<T, N> &Vector<T, N>::operator=(const Vector &other)
{
    memcpy(data(), other.data(), sizeof(ValueType) * SIZE);
    return *this;
}

template<typename T, size_t N>
    template<typename U, size_t M, typename>
FMATH_CONSTEXPR Vector<T, N> &Vector<T, N>::operator=(const Vector<U, M> &other)
{
    FMATH_CONSTEXPR size_t REAL = min(SIZE, M);
    for (index_t i = 0; i < REAL; ++i)
        this->values[i] = static_cast<ValueType>(other[i]);
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR size_t Vector<T, N>::size() const
{
    return SIZE;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR const typename Vector<T, N>::ValueType *Vector<T, N>::data() const
{
    return this->values.data();
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR typename Vector<T, N>::ValueType *Vector<T, N>::data()
{
    return this->values.data();
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR const typename Vector<T, N>::ValueType &Vector<T, N>::get(index_t index) const
{
    return this->values[index];
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR typename Vector<T, N>::ValueType &Vector<T, N>::get(index_t index)
{
    return this->values[index];
}

template<typename T, size_t N>
FMATH_INLINE void Vector<T, N>::set(index_t index, const ValueType &value)
{
    this->values[index] = value;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR const typename Vector<T, N>::ValueType &Vector<T, N>::operator[](index_t index) const
{
    return this->values[index];
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR typename Vector<T, N>::ValueType &Vector<T, N>::operator[](index_t index)
{
    return this->values[index];
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
Vector<T, N> &Vector<T, N>::operator+=(const Vector &other)
{
    *this = internal::VectorTraits<T, N>::add(*this, other);
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
Vector<T, N> Vector<T, N>::zero()
{
    return Vector();
}

template<typename T, size_t N>
std::ostream &operator<<(std::ostream &output, const Vector<T, N> &vec)
{
    output << '[';
    for (index_t i = 0; i < N; ++i)
        output << vec[i] << ("," + (i == N - 1));
    output << ']';
    return output;
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