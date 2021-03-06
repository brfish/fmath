#ifndef _FMATH_QUATERNION_H_
#define _FMATH_QUATERNION_H_

#include <array>
#include <istream>
#include <ostream>

#include "common.h"
#include "matrix.h"
#include "vector.h"

namespace fmath
{

template<typename T>
class Quat
{
public:
    using ValueType = T;
    static constexpr size_t DIMENSION = 4;
public:
    FMATH_CONSTEXPR Quat(const Quat &other);

    explicit FMATH_CONSTEXPR Quat(const ValueType &w = 0, const ValueType &x = 0, 
        const ValueType &y = 0, const ValueType &z = 0);

    explicit FMATH_CONSTEXPR Quat(const ValueType &s, const Vector3<ValueType> &v);

    explicit FMATH_CONSTEXPR Quat(const ValueType &s);

    template<typename VectorT,
        typename = std::enable_if_t<std::is_base_of_v<internal::VectorInterface, VectorT> && VectorT::DIMENSION == 3>>
    explicit FMATH_CONSTEXPR Quat(const VectorT &v);

    FMATH_CONSTEXPR Quat &operator=(const Quat &other);

    FMATH_CONSTEXPR Quat &operator=(const Vector3<T> &v);
    
    FMATH_INLINE FMATH_CONSTEXPR size_t size() const;

    FMATH_INLINE FMATH_CONSTEXPR const ValueType *data() const;

    FMATH_INLINE FMATH_CONSTEXPR ValueType *data();

    FMATH_INLINE FMATH_CONSTEXPR const ValueType &get(index_t index) const;

    FMATH_INLINE FMATH_CONSTEXPR ValueType &get(index_t index);
    
    FMATH_INLINE void set(index_t index, const ValueType &value);

    FMATH_INLINE FMATH_CONSTEXPR const ValueType &operator[](index_t index) const;

    FMATH_INLINE FMATH_CONSTEXPR ValueType &operator[](index_t index);

    FMATH_INLINE FMATH_CONSTEXPR ValueType angle() const;
    
    FMATH_INLINE FMATH_CONSTEXPR Vector3<T> axis() const;

    FMATH_INLINE FMATH_CONSTEXPR Quat operator+() const;

    FMATH_INLINE FMATH_CONSTEXPR Quat operator-() const;

    FMATH_INLINE Quat &operator+=(const Quat &other);

    FMATH_INLINE Quat &operator-=(const Quat &other);

    FMATH_INLINE Quat &operator*=(const Quat &other);

    FMATH_INLINE Quat &operator*=(const ValueType &value);

    FMATH_INLINE Quat &operator/=(const ValueType &value);

    FMATH_INLINE FMATH_CONSTEXPR Matrix4<T> toMatrix() const;

    static FMATH_CONSTEXPR Quat identity();

    static FMATH_CONSTEXPR Quat makeRotation(const Vector3<T> &axis, const T &angle);

public:
    union
    {
        Vector4<T> values;
        struct { ValueType w, x, y, z; };
        struct { ValueType s; Vector3<T> v; };
    };
};

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool operator==(const Quat<T> &q1, const Quat<T> &q2)
{
    return q1[0] == q2[0] && q1[1] == q2[1] &&
        q1[2] == q2[2] && q1[3] == q2[3]; 
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool operator!=(const Quat<T> &q1, const Quat<T> &q2)
{
    return !(q1 == q2);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool equal(const Quat<T> &q1, const Quat<T> &q2)
{
    return q1 == q2;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool notEqual(const Quat<T> &q1, const Quat<T> &q2)
{
    return q1 != q2;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool equalEpsilon(const Quat<T> &q1, const Quat<T> &q2, const T &epsilon = constants::Epsilon<T>::value)
{
    return fmath::equalEpsilon(q1[0], q2[0], epsilon) &&
        fmath::equalEpsilon(q1[1], q2[1], epsilon) &&
        fmath::equalEpsilon(q1[2], q2[2], epsilon) &&
        fmath::equalEpsilon(q1[3], q2[3], epsilon);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool notEqualEpsilon(const Quat<T> &q1, const Quat<T> &q2, const T &epsilon = constants::Epsilon<T>::value)
{
    return !equalEpsilon(q1, q2, epsilon);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Quat<T> operator+(const Quat<T> &q1, const Quat<T> &q2)
{
    return Quat<T>(q1[0] + q2[0], q1[1] + q2[1], q1[2] + q2[2], q1[3] + q2[3]);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Quat<T> operator-(const Quat<T> &q1, const Quat<T> &q2)
{
    return Quat<T>(q1[0] - q2[0], q1[1] - q2[1], q1[2] - q2[2], q1[3] - q2[3]);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Quat<T> operator*(const Quat<T> &q1, const Quat<T> &q2)
{
    return Quat<T>(q1[0] * q2[0] - q1[1] * q2[1] - q1[2] * q2[2] - q1[3] * q2[3],
        q1[1] * q2[0] + q1[0] * q2[1] + q1[3] * q2[2] - q1[2] * q2[3],
        q1[2] * q2[0] + q1[0] * q2[2] + q1[1] * q2[3] - q1[3] * q2[1],
        q1[3] * q2[0] + q2[3] * q1[0] + q1[2] * q2[1] - q1[1] * q2[2]
    );
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Quat<T> operator*(const Quat<T> &q, const T &value)
{
    return Quat<T>(q[0] * value, q[1] * value, q[2] * value, q[3] * value);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Quat<T> operator*(const T &value, const Quat<T> &q)
{
    return q * value;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Quat<T> operator/(const Quat<T> &q, const T &value)
{
    FMATH_ASSERT(value != 0);
    return Quat<T>(q[0] / value, q[1] / value, q[2] / value, q[3] / value);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T dot(const Quat<T> &q1, const Quat<T> &q2)
{
    return q1[0] * q2[0] + q1[1] * q2[1] + q1[2] * q2[2] + q1[3] * q2[3];
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Vector3<T> cross(const Quat<T> &q1, const Quat<T> &q2)
{
    return Vector3<T>(q1[1] * q2[2] - q1[2] * q2[1],
        q1[2] * q2[0] - q1[0] * q2[2],
        q1[0] * q2[1] - q1[1] * q2[0]
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
FMATH_INLINE FMATH_CONSTEXPR T length(const Quat<T> &q)
{
    return sqrt(length2(q));
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Quat<T> normalize(const Quat<T> &q)
{
    return q / length(q);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Quat<T> inverse(const Quat<T> &q)
{
    return conjugate(q) / length2(q);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Quat<T> opposite(const Quat<T> &q)
{
    return -q;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Quat<T> log(const Quat<T> &q)
{
    T alpha = q.angle() / static_cast<T>(2);
    return Quat<T>(0, alpha * q.axis());
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Quat<T> exp(const Quat<T> &q)
{
    T alpha = q.angle() / static_cast<T>(2);
    return Quat<T>(cos(alpha), sin(alpha) * q.axis());
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Quat<T> pow(const Quat<T> &q, const T &t)
{
    return exp(t * log(q));
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Quat<T> slerp(const Quat<T> &q1, const Quat<T> &q2);

template<typename T>
FMATH_INLINE std::ostream &operator<<(std::ostream &output, const Quat<T> &q)
{
    output << '[' << q[0] << ',' << q[1] << ',' << q[2] << ',' << q[3] << ']';
    return output;
}

template<typename T>
FMATH_INLINE std::istream &operator>>(std::istream &input, Quat<T> &q)
{
    input >> q[0] >> q[1] >> q[2] >> q[3];
    return input;
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
    :   values { s, v[0], v[1], v[2] }
{}

template<typename T>
FMATH_CONSTEXPR Quat<T>::Quat(const ValueType &s)
    :   values { s, static_cast<T>(0), static_cast<T>(0), static_cast<T>(0) }
{}

template<typename T>
    template<typename VectorT, typename>
FMATH_CONSTEXPR Quat<T>::Quat(const VectorT &v)
    :   values { static_cast<T>(0), v[0], v[1], v[2] }
{}

template<typename T>
FMATH_CONSTEXPR Quat<T> &Quat<T>::operator=(const Quat &other)
{
    values = other.values;
    return *this;
}

template<typename T>
FMATH_CONSTEXPR Quat<T> &Quat<T>::operator=(const Vector3<T> &v)
{
    values[0] = v[0];
    values[1] = v[1];
    values[2] = v[2];
    return *this;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR size_t Quat<T>::size() const
{
    return DIMENSION;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR const typename Quat<T>::ValueType *Quat<T>::data() const
{
    return values.data();
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR typename Quat<T>::ValueType *Quat<T>::data()
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
FMATH_INLINE FMATH_CONSTEXPR typename Quat<T>::ValueType Quat<T>::angle() const
{
    return static_cast<T>(2) * acos(values[0]);
}

template<typename T>   
FMATH_INLINE FMATH_CONSTEXPR Vector3<T> Quat<T>::axis() const
{
    return Vector3<T>(static_cast<T>(2) * asin(values[1]),
        static_cast<T>(2) * asin(values[2]),
        static_cast<T>(2) * asin(values[3])
    );
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Quat<T> Quat<T>::operator+() const
{
    return Quat(*this);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Quat<T> Quat<T>::operator-() const
{
    return Quat(-values[0], -values[1], -values[2], -values[3]);
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
FMATH_INLINE Quat<T> &Quat<T>::operator*=(const Quat &other)
{
    *this = (*this) * other;
    return *this;
}

template<typename T>
FMATH_INLINE Quat<T> &Quat<T>::operator*=(const ValueType &value)
{
    *this = (*this) * value;
    return this;
}

template<typename T>
FMATH_INLINE Quat<T> &Quat<T>::operator/=(const ValueType &value)
{
    *this = (*this) / value;
    return this;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Matrix4<T> Quat<T>::toMatrix() const
{
    Quat<T> q = normalize(*this);

    T wx = q[0] * q[1];
    T wy = q[0] * q[2];
    T wz = q[0] * q[3];

    T xx = q[1] * q[1];
    T xy = q[1] * q[2];
    T xz = q[1] * q[3];

    T yy = q[2] * q[2];
    T yz = q[2] * q[3];

    T zz = q[3] * q[3];

    const T one = static_cast<T>(1);
    const T two = static_cast<T>(2);

    Matrix4<T> r;
    r[0][0] = one - two * (yy + zz);
    r[0][1] = two * (xy + wz);
    r[0][2] = two * (xz - wy);

    r[1][0] = two * (xy - wz);
    r[1][1] = one - two * (xx + zz);
    r[1][2] = two * (yz + wx);

    r[2][0] = two * (xz - wy);
    r[2][1] = two * (yz - wx);
    r[2][2] = one - two * (xx + yy);

    r[3][3] = one;

    return r;
}

template<typename T>
FMATH_CONSTEXPR Quat<T> Quat<T>::identity()
{
    return Quat<T>(1, 0, 0, 0);
}

template<typename T>
FMATH_CONSTEXPR Quat<T> Quat<T>::makeRotation(const Vector3<T> &axis, const T &angle)
{
    return Quat<T>(cos(angle / static_cast<T>(2)), axis * sin(angle / static_cast<T>(2)));
}

using Quatf = Quat<float>;
using Quatlf = Quat<double>;

}

#endif