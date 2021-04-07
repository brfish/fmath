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

    FMATH_INLINE FMATH_CONSTEXPR Point<T, N> at(const ValueType &t) const;

    FMATH_INLINE FMATH_CONSTEXPR Point<T, N> operator()(const ValueType &t) const;

    FMATH_INLINE FMATH_CONSTEXPR Line<T, N> toLine(const ValueType &t0, const ValueType &t1) const;

    FMATH_INLINE FMATH_CONSTEXPR Line<T, N> toLine(const ValueType &t) const;

    FMATH_INLINE FMATH_CONSTEXPR Ray<T, N> negate() const;

    FMATH_INLINE void setOrigin(const Point<T, N> &origin);

    FMATH_INLINE void setDirection(const Vector<T, N> &direction);

private:
    Point<ValueType, DIMENSION> origin_;
    Vector<ValueType, DIMENSION> direction_;
};

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool operator==(const Ray<T, N> &r1, const Ray<T, N> &r2)
{
    return r1.origin() == r2.origin() && r1.direction() == r2.direction();
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool operator!=(const Ray<T, N> &r1, const Ray<T, N> &r2)
{
    return !(r1 == r2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool equal(const Ray<T, N> &r1, const Ray<T, N> &r2)
{
    return r1 == r2;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool notEqual(const Ray<T, N> &r1, const Ray<T, N> &r2)
{
    return r1 != r2;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool equalEpsilon(const Ray<T, N> &r1, const Ray<T, N> &r2, const T &epsilon = constants::Epsilon<T>::value)
{
    return equalEpsilon(r1.origin(), r2.origin(), epsilon) &&
        equalEpsilon(r1.direction(), r2.direction(), epsilon);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool notEqualEpsilon(const Ray<T, N> &r1, const Ray<T, N> &r2, const T &epsilon = constants::Epsilon<T>::value)
{
    return !equalEpsilon(r1, r2, epsilon);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T distance2(const Ray<T, N> &r, const Point<T, N> &p)
{
    Vector3<T> hypotenuse = r.origin() - p;
    Vector3<T> direction = r.direction();

    return length2(hypotenuse - (hypotenuse * direction) * direction);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T distance2(const Point<T, N> &p, const Ray<T, N> &r)
{
    return distance2(r, p);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T distance(const Ray<T, N> &r, const Point<T, N> &p)
{
    Vector3<T> hypotenuse = r.origin() - p;
    Vector3<T> direction = r.direction();

    return length(hypotenuse - (hypotenuse * direction) * direction);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T distance(const Point<T, N> &p, const Ray<T, N> &r)
{
    return distance(r, p);
}

template<typename T, size_t N>
FMATH_INLINE std::string toString(const Ray<T, N> &r, uint32 precision = 6)
{
    std::stringstream ss;
    ss << '(' << toString(r.origin(), precision) << ',' << toString(r.direction(), precision) << ')';
    return ss.str();
}

template<typename T, size_t N>
FMATH_INLINE std::ostream &operator<<(std::ostream &output, const Ray<T, N> &r)
{
    output << '(' << r.origin() << ',' << r.direction() << ')';
    return output;
}

template<typename T, size_t N>
FMATH_CONSTEXPR Ray<T, N>::Ray(const Ray &other)
    :   origin_(other.origin_),
        direction_(other.direction_)
{}

template<typename T, size_t N>
FMATH_CONSTEXPR Ray<T, N>::Ray(const Point<T, N> &origin, const Vector<T, N> &direction)
    :   origin_(origin),
        direction_(normalize(direction))
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
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> Ray<T, N>::at(const ValueType &t) const
{
    return origin_ + direction_ * t;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> Ray<T, N>::operator()(const ValueType &t) const
{
    return at(t);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Line<T, N> Ray<T, N>::toLine(const ValueType &t0, const ValueType &t1) const
{
    return Line<T, N>(origin_ + direction_ * t0, origin_ + direction_ * t1);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Line<T, N> Ray<T, N>::toLine(const ValueType &t) const
{
    return toLine(static_cast<T>(0), t);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Ray<T, N> Ray<T, N>::negate() const
{
    return Ray(origin_, -direction_);
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