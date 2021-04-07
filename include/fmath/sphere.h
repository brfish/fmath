#ifndef _FMATH_SPHERE_H_
#define _FMATH_SPHERE_H_

#include "box.h"
#include "common.h"
#include "point.h"

namespace fmath
{

template<typename T, size_t N>
class Sphere
{
public:
    using ValueType = T;
    static constexpr size_t DIMENSION = N;

public:
    FMATH_CONSTEXPR Sphere(const Sphere &other);
    explicit FMATH_CONSTEXPR Sphere(const Point<ValueType, N> &center, const ValueType &radius);

    FMATH_CONSTEXPR Sphere &operator=(const Sphere &other);

    FMATH_INLINE FMATH_CONSTEXPR const Point<T, N> &center() const;

    FMATH_INLINE FMATH_CONSTEXPR Point<T, N> &center();

    FMATH_INLINE FMATH_CONSTEXPR const T &radius() const;

    FMATH_INLINE FMATH_CONSTEXPR T &radius();

    FMATH_INLINE FMATH_CONSTEXPR Box<T, N> bound() const;

    FMATH_INLINE FMATH_CONSTEXPR bool contains(const Point<ValueType, N> &point) const;

    FMATH_INLINE FMATH_CONSTEXPR bool contains(const Sphere &other) const;

    FMATH_INLINE FMATH_CONSTEXPR bool overlaps(const Sphere &other) const;

    FMATH_INLINE void setCenter(const Point<ValueType, N> &center);

    FMATH_INLINE void setRadius(const ValueType &radius);

private:
    Point<ValueType, N> center_;
    ValueType radius_;
};

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool operator==(const Sphere<T, N> &s1, const Sphere<T, N> &s2)
{
    return s1.radius() == s2.radius() && s1.center() == s2.center();
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool operator!=(const Sphere<T, N> &s1, const Sphere<T, N> &s2)
{
    return s1.radius() != s2.radius() || s1.center() != s2.center();
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool equal(const Sphere<T, N> &s1, const Sphere<T, N> &s2)
{
    return s1 == s2;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool notEqual(const Sphere<T, N> &s1, const Sphere<T, N> &s2)
{
    return s1 != s2;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Sphere<T, N> operator+(const Sphere<T, N> &s, const Point<T, N> &p)
{
    Sphere<T, N> result(s);
    result += p;
    return result;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Sphere<T, N> operator+(const Sphere<T, N> &s1, const Sphere<T, N> &s2)
{
    Sphere<T, N> result(s1);
    result += s2;
    return result;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T distance2(const Sphere<T, N> &s1, const Sphere<T, N> &s2)
{
    return distance2(s1.center(), s2.center());
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T distance(const Sphere<T, N> &s1, const Sphere<T, N> &s2)
{
    return distance(s1.center(), s2.center());
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR std::string toString(const Sphere<T, N> &s, uint32 precision = 6)
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision);
    ss << '(' << s.center() << ',' << s.radius() << ')';
    return ss.str();
}

template<typename T, size_t N>
FMATH_INLINE std::ostream &operator<<(std::ostream &output, const Sphere<T, N> &s)
{
    output << toString(s);
    return output;
}

template<typename T, size_t N>
FMATH_CONSTEXPR Sphere<T, N>::Sphere(const Sphere &other)
    :   center_(other.center_),
        radius_(other.radius_)
{}

template<typename T, size_t N>
FMATH_CONSTEXPR Sphere<T, N>::Sphere(const Point<ValueType, N> &center, const ValueType &radius)
    :   center_(center),
        radius_(radius)
{}

template<typename T, size_t N>
FMATH_CONSTEXPR Sphere<T, N> &Sphere<T, N>::operator=(const Sphere &other)
{
    center_ = other.center_;
    radius_ = other.radius_;
    
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR const Point<T, N> &Sphere<T, N>::center() const
{
    return center_;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> &Sphere<T, N>::center()
{
    return center_;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR const typename Sphere<T, N>::ValueType &Sphere<T, N>::radius() const
{
    return radius_;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR typename Sphere<T, N>::ValueType &Sphere<T, N>::radius()
{
    return radius_;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Box<T, N> Sphere<T, N>::bound() const
{
    return Box<T, N>(center_ - radius_, center_ + radius_);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool Sphere<T, N>::contains(const Point<T, N> &point) const
{
    return distance2(point, center_) <= radius_ * radius_;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool Sphere<T, N>::contains(const Sphere &other) const
{
    return distance2(*this, other) <= (radius_ - other.radius_) * (radius_ - other.radius_);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool Sphere<T, N>::overlaps(const Sphere &other) const
{
    return distance2(*this, other) <= (radius_ + other.radius_) * (radius_ + other.radius_);
}

template<typename T, size_t N>
FMATH_INLINE void Sphere<T, N>::setCenter(const Point<T, N> &center)
{
    center_ = center;
}

template<typename T, size_t N>
FMATH_INLINE void Sphere<T, N>::setRadius(const ValueType &radius)
{
    radius_ = radius;
}

template<typename T>
using Circle2 = Sphere<T, 2>;

template<typename T>
using Sphere3 = Sphere<T, 3>;

using Circle2f = Circle2<float>;
using Circle2lf = Circle2<double>;

using Sphere3f = Sphere3<float>;
using Sphere3lf = Sphere3<double>;

}

#endif