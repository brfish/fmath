#ifndef _FMATH_RAY_H_
#define _FMATH_RAY_H_

#include "point.h"
#include "vector.h"
#include "line.h"

namespace fmath
{

template<typename T, size_t N>
class Ray
{
public:
    using ValueType = T;
    static constexpr size_t DIMENSION = N;

public:
    FMATH_CONSTEXPR Ray(const Ray &other);

    explicit FMATH_CONSTEXPR Ray(const Point<ValueType, N> &origin, const Vector<ValueType, N> &direction);

    FMATH_CONSTEXPR Ray &operator=(const Ray &other);

    FMATH_INLINE FMATH_CONSTEXPR const Point<T, N> &origin() const;

    FMATH_INLINE FMATH_CONSTEXPR Point<T, N> &origin();

    FMATH_INLINE FMATH_CONSTEXPR const Vector<T, N> &direction() const;

    FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> &direction();

    FMATH_INLINE FMATH_CONSTEXPR Point<T, N> at(const ValueType &t);

    FMATH_INLINE FMATH_CONSTEXPR Point<T, N> operator()(const ValueType &t);

    FMATH_INLINE FMATH_CONSTEXPR Line<T, N> toLine(const ValueType &t0, const ValueType &t1);

    FMATH_INLINE void setOrigin(const Point<T, N> &origin);

    FMATH_INLINE void setDirection(const Vector<T, N> &direction);

private:
    Point<ValueType, DIMENSION> origin_;
    Vector<ValueType, DIMENSION> direction_;
};

template<typename T, size_t N>
bool operator==(const Ray<T, N> &r1, const Ray<T, N> &r2)
{
    return r1.origin() == r2.origin() && r1.direction() == r2.direction();
}

template<typename T, size_t N>
bool operator!=(const Ray<T, N> &r1, const Ray<T, N> &r2)
{
    return !(r1 == r2);
}

template<typename T, size_t N>
bool equal(const Ray<T, N> &r1, const Ray<T, N> &r2)
{
    return r1 == r2;
}

template<typename T, size_t N>
bool notEqual(const Ray<T, N> &r1, const Ray<T, N> &r2)
{
    return r1 != r2;
}

template<typename T, size_t N>
bool equalEpsilon(const Ray<T, N> &r1, const Ray<T, N> &r2, const T &epsilon = constants::Epsilon<T>::value)
{
    return equalEpsilon(r1.origin(), r2.origin(), epsilon) &&
        equalEpsilon(r1.direction(), r2.direction(), epsilon);
}

template<typename T, size_t N>
bool notEqualEpsilon(const Ray<T, N> &r1, const Ray<T, N> &r2, const T &epsilon = constants::Epsilon<T>::value)
{
    return !equalEpsilon(r1, r2, epsilon);
}

template<typename T, size_t N>
FMATH_CONSTEXPR Ray<T, N>::Ray(const Ray &other)
    :   origin_(other.origin_),
        direction_(other.direction_)
{}

template<typename T, size_t N>
FMATH_CONSTEXPR Ray<T, N>::Ray(const Point<T, N> &origin, const Vector<T, N> &direction)
    :   origin_(origin),
        direction_(direction)
{}

template<typename T, size_t N>
FMATH_CONSTEXPR Ray<T, N> &Ray<T, N>::operator=(const Ray &other)
{
    origin_ = other.origin_;
    direction_ = other.direction_;
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR const Point<T, N> &Ray<T, N>::origin() const
{
    return origin_;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> &Ray<T, N>::origin()
{
    return origin_;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR const Vector<T, N> &Ray<T, N>::direction() const
{
    return direction_;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> &Ray<T, N>::direction()
{
    return direction_;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> Ray<T, N>::at(const ValueType &t)
{
    return origin_ + direction_ * t;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> Ray<T, N>::operator()(const ValueType &t)
{
    return at(t);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Line<T, N> Ray<T, N>::toLine(const ValueType &t0, const ValueType &t1)
{
    return Line<T, N>(origin_ + direction_ * t0, origin_ + direction_ * t1);
}

template<typename T, size_t N>
FMATH_INLINE void Ray<T, N>::setOrigin(const Point<T, N> &origin)
{
    origin_ = origin;
}

template<typename T, size_t N>
FMATH_INLINE void Ray<T, N>::setDirection(const Vector<T, N> &direction)
{
    direction_ = normalize(direction);
}

template<typename T>
using Ray2 = Ray<T, 2>;

template<typename T>
using Ray3 = Ray<T, 3>;

using Ray2f = Ray2<float>;
using Ray3lf = Ray2<double>;

using Ray3f = Ray3<float>;
using Ray3lf = Ray3<double>;

}

#endif