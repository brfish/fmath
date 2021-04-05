#ifndef _FMATH_PLANE_H_
#define _FMTHA_PLANE_H_

#include "common.h"
#include "point.h"
#include "vector.h"

namespace fmath
{

template<typename T>
class Plane
{
public:
    using ValueType = T;
    static constexpr size_t DIMENSION = 3;

public:
    FMATH_CONSTEXPR Plane(const Plane &other);
    
    explicit FMATH_CONSTEXPR Plane(const Vector3<ValueType> &normal, const ValueType &constant);

    FMATH_CONSTEXPR Plane(const Vector4<ValueType> &v);

    explicit FMATH_CONSTEXPR Plane(const Vector3<ValueType> &normal, const Point3<T> &point);

    // The points are given counterclockwise
    explicit FMATH_CONSTEXPR Plane(const Point3<ValueType> &p0, const Point3<ValueType> &p1, const Point3<ValueType> &p2);

    FMATH_CONSTEXPR Plane &operator=(const Plane &other);

    FMATH_INLINE FMATH_CONSTEXPR const Vector3<T> &normal() const;

    FMATH_INLINE FMATH_CONSTEXPR Vector3<T> &normal();

    FMATH_INLINE FMATH_CONSTEXPR const T &constant() const;

    FMATH_INLINE FMATH_CONSTEXPR T &constant();

    FMATH_INLINE FMATH_CONSTEXPR void setNormal(const Vector3<ValueType> &normal);

    FMATH_INLINE FMATH_CONSTEXPR void setConstant(const ValueType &constant);

private:
    Vector3<ValueType> normal_;
    ValueType constant_;
};

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool operator==(const Plane<T> &p1, const Plane<T> &p2)
{
    return p1.normal() == p2.normal() && p1.constant() == p2.constant();
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool operator!=(const Plane<T> &p1, const Plane<T> &p2)
{
    return !(p1 == p2);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool equal(const Plane<T> &p1, const Plane<T> &p2)
{
    return p1 == p2;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool notEqual(const Plane<T> &p1, const Plane<T> &p2)
{
    return p1 != p2;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool equalEpsilon(const Plane<T> &p1, const Plane<T> &p2, const T &epsilon = constants::Epsilon<T>::value)
{
    return equalEpsilon(p1.normal(), p2.normal(), epsilon) &&
        equalEpsilon(p1.constant(), p2.constant(), epsilon);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool notEqualEpsilon(const Plane<T> &p1, const Plane<T> &p2, const T &epsilon = constants::Epsilon<T>::value)
{
    return !equalEpsilon(p1, p2, epsilon);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T distance(const Plane<T> &plane, const Point3<T> &point)
{
    const Vector3<T> &v = *reinterpret_cast<const Vector3<T> *>(&point);
    return v * plane.normal() - plane.constant();
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T distance(const Point3<T> &point, const Plane<T> &plane)
{
    return distance(plane, point);
}

template<typename T>
FMATH_INLINE std::string toString(const Plane<T> &p, uint32 precision = 6)
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision);
    ss << '(' << toString(p.normal(), precision) << ',' << p.constant() << ')';
    return ss.str();
}

template<typename T>
FMATH_INLINE std::ostream &operator<<(std::ostream &output, const Plane<T> &p)
{
    output << toString(p);
    return output;
}

template<typename T>
FMATH_CONSTEXPR Plane<T>::Plane(const Plane &other)
    :   normal_(other.normal_),
        constant_(other.constant_)
{}

template<typename T>
FMATH_CONSTEXPR Plane<T>::Plane(const Vector3<ValueType> &normal, const ValueType &constant)
    :   normal_(normalize(normal)),
        constant_(constant)
{}

template<typename T>
FMATH_CONSTEXPR Plane<T>::Plane(const Vector4<ValueType> &v)
    :   normal_(normalize(Vector3<ValueType>(v[0], v[1], v[2]))),
        constant_(v[3])
{}

template<typename T>
FMATH_CONSTEXPR Plane<T>::Plane(const Vector3<ValueType> &normal, const Point3<ValueType> &point)
    :   normal_(normalize(normal))
{
    FMATH_ASSERT(notEqualEpsilon(normal, Vector3<ValueType>::zero()));
    const Vector3<ValueType> &v = *reinterpret_cast<const Point3<ValueType> *>(&point);
    constant_ = normal_ * v;
}

template<typename T>
FMATH_CONSTEXPR Plane<T>::Plane(const Point3<ValueType> &p0, const Point3<ValueType> &p1, const Point3<ValueType> &p2)
    :   Plane(cross(p2 - p0, p1 - p0), p0)
{}

template<typename T>
FMATH_CONSTEXPR Plane<T> &Plane<T>::operator=(const Plane &other)
{
    normal_ = other.normal_;
    constant_ = other.constant_;
    return *this;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR const Vector3<T> &Plane<T>::normal() const
{
    return normal_;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Vector3<T> &Plane<T>::normal()
{
    return normal_;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR const T &Plane<T>::constant() const
{
    return constant_;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T &Plane<T>::constant()
{
    return constant_;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR void Plane<T>::setNormal(const Vector3<ValueType> &normal)
{
    normal_ = normalize(normal);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR void Plane<T>::setConstant(const ValueType &constant)
{
    constant_ = constant;
}

using Plane3f = Plane<float>;
using Plane3lf = Plane<double>;

}

#endif