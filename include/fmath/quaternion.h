#ifndef _FMATH_QUATERNION_H_
#define _FMATH_QUATERNION_H_

#include <array>

#include "compile_config.h"
#include "vector.h"

namespace fmath
{

template<typename T>
class Quat
{
public:
    using ValueType = T;
    static constexpr size_t SIZE = 4;
public:
    FMATH_CONSTEXPR Quat(const Quat &other);

    explicit FMATH_CONSTEXPR Quat(const ValueType &w = 0, const ValueType &x = 0, 
        const ValueType &y = 0, const ValueType &z = 0);

    explicit FMATH_CONSTEXPR Quat(const ValueType &s, const Vector3<ValueType> &v);

    FMATH_CONSTEXPR Quat &operator=(const Quat &other);
    
    FMATH_INLINE FMATH_CONSTEXPR size_t size() const;

    FMATH_CONSTEXPR FMATH_INLINE const ValueType *data() const;

    FMATH_INLINE ValueType *data();

    FMATH_INLINE FMATH_CONSTEXPR const ValueType &get(index_t index) const;

    FMATH_INLINE FMATH_CONSTEXPR ValueType &get(index_t index);
    
    FMATH_INLINE void set(index_t index, const ValueType &value);

    FMATH_INLINE FMATH_CONSTEXPR const ValueType &operator[](index_t index) const;

    FMATH_INLINE FMATH_CONSTEXPR ValueType &operator[](index_t index);

    FMATH_INLINE Quat &operator+=(const Quat &other);

    FMATH_INLINE Quat &operator-=(const Quat &other);

    FMATH_INLINE Quat &operator*=(ValueType value);

    FMATH_INLINE Quat &operator/=(ValueType value);

public:
    union
    {
        std::array<ValueType, 4> values;
        struct { ValueType w, x, y, z; };
        struct { ValueType s; Vector3<T> v; };
    };
};

template<typename T>
FMATH_CONSTEXPR FMATH_INLINE Quat<T> operator+(const Quat<T> &p, const Quat<T> &q)
{
    return Quat<T>(p[0] + q[0], p[1] + q[1], p[2] + q[2], p[3] + q[3]);
}

template<typename T>
FMATH_CONSTEXPR FMATH_INLINE Quat<T> operator-(const Quat<T> &p, const Quat<T> &q)
{
    return Quat<T>(p[0] - q[0], p[1] - q[1], p[2] - q[2], p[3] - q[3]);
}

template<typename T>
FMATH_CONSTEXPR FMATH_INLINE Quat<T> operator*(const Quat<T> &q, const Quat<T> &p)
{
    return Quat<T>(q[0] * p[0] - q[1] * p[1] - q[2] * p[2] - q[3] * p[3],
        q[1] * p[0] + q[0] * p[1] + q[3] * p[2] - q[2] * p[3],
        q[2] * p[0] + q[0] * p[2] + q[1] * p[3] - q[3] * p[1],
        q[3] * p[0] + p[3] * q[0] + q[2] * p[1] - q[1] * p[2]
    );
}

template<typename T>
FMATH_CONSTEXPR FMATH_INLINE Quat<T> operator*(const Quat<T> &q, const T &value)
{
    return Quat<T>(q[0] * value, q[1] * value, q[2] * value, q[3] * value);
}

template<typename T>
FMATH_CONSTEXPR FMATH_INLINE Quat<T> operator/(const Quat<T> &q, const T &value)
{
    FMATH_ASSERT(value != 0);
    return Quat<T>(q[0] / value, q[1] / value, q[2] / value, q[3] / value);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T dot(const Quat<T> &p, const Quat<T> &q)
{
    return p[0] * q[0] + p[1] * q[1] + p[2] * q[2] + p[3] * q[3];
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Vector3<T> cross(const Quat<T> &p, const Quat<T> &q)
{
    return Vector3<T>(p[1] * q[2] - p[2] * q[1],
        p[2] * q[0] - p[0] * q[2],
        p[0] * q[1] - p[1] * q[0]
    );
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Quat<T> conjugate(const Quat<T> &q)
{
    return Quat<T>(q[0], -q[1], -q[2], -q[3]);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T length2(const Quat<T> &q)
{
    return q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3];
}

template<typename T>
T length(const Quat<T> &q)
{
    return sqrt(length2(q));
}

template<typename T>
Quat<T> normalize(const Quat<T> &q)
{
    return q / length(q);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Quat<T> inverse(const Quat<T> &q)
{
    return conjugate(q) / length2(q);
}

template<typename T>
FMATH_INLINE std::ostream &operator<<(std::ostream &output, const Quat<T> &q)
{
    output << '[' << q[0] << ',' << q[1] << ',' << q[2] << ',' << q[3] << ']';
    return output;
}

template<typename T>
FMATH_CONSTEXPR Quat<T>::Quat(const Quat &other)
    :   values { other[0], other[1], other[2], other[3] }
{}

template<typename T>
FMATH_CONSTEXPR Quat<T>::Quat(const ValueType &w, const ValueType &x, 
    const ValueType &y, const ValueType &z)
    :   values { w, x, y, z }
{}

template<typename T>
FMATH_CONSTEXPR Quat<T>::Quat(const ValueType &s, const Vector3<ValueType> &v)
    :   values { s, v.x, v.y, v.z }
{}

template<typename T>
FMATH_CONSTEXPR Quat<T> &Quat<T>::operator=(const Quat &other)
{
    values = other.values;
    return *this;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR size_t Quat<T>::size() const
{
    return SIZE;
}

template<typename T>
FMATH_CONSTEXPR FMATH_INLINE const typename Quat<T>::ValueType *Quat<T>::data() const
{
    return values.data();
}

template<typename T>
FMATH_INLINE typename Quat<T>::ValueType *Quat<T>::data()
{
    return values.data();
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR const typename Quat<T>::ValueType &Quat<T>::get(index_t index) const
{
    return values[index];
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR typename Quat<T>::ValueType &Quat<T>::get(index_t index)
{
    return values[index];
}

template<typename T>
FMATH_INLINE void Quat<T>::set(index_t index, const ValueType &value)
{
    values[index] = value;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR const typename Quat<T>::ValueType &Quat<T>::operator[](index_t index) const
{
    return values[index];
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR typename Quat<T>::ValueType &Quat<T>::operator[](index_t index)
{
    return values[index];
}

template<typename T>
FMATH_INLINE Quat<T> &Quat<T>::operator+=(const Quat &other)
{
    *this = (*this) + other;
    return *this;
}

template<typename T>
FMATH_INLINE Quat<T> &Quat<T>::operator-=(const Quat &other)
{
    *this = (*this) + other;
    return *this;
}

template<typename T>
FMATH_INLINE Quat<T> &Quat<T>::operator*=(ValueType value)
{
    *this = (*this) * value;
    return this;
}

template<typename T>
FMATH_INLINE Quat<T> &Quat<T>::operator/=(ValueType value)
{
    *this = (*this) / value;
    return this;
}

using Quatf = Quat<float>;
using Quatlf = Quat<double>;

}

#endif