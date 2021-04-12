#ifndef _FMATH_TRIANGLE_H_
#define _FMATH_TRIANGLE_H_

#include <array>

#include "common.h"
#include "constants.h"
#include "plane.h"
#include "point.h"

namespace fmath
{

template<typename T, size_t N>
class Triangle
{
public:
    using ValueType = T;
    static constexpr size_t DIMENSION = N;

public:
    FMATH_CONSTEXPR Triangle(const Triangle &other);

    FMATH_CONSTEXPR Triangle();

    // The points are given counterclockwise
    explicit FMATH_CONSTEXPR Triangle(const Point<T, N> &v0, const Point<T, N> &v1, const Point<T, N> &v2);

    FMATH_CONSTEXPR Triangle &operator=(const Triangle &other);

    FMATH_INLINE FMATH_CONSTEXPR const Point<T, N> &operator[](index_t index) const;

    FMATH_INLINE FMATH_CONSTEXPR Point<T, N> &operator[](index_t index);

    FMATH_INLINE FMATH_CONSTEXPR const Point<T, N> &get(index_t index) const;

    FMATH_INLINE FMATH_CONSTEXPR Point<T, N> &get(index_t index);

    FMATH_INLINE FMATH_CONSTEXPR T area() const;
    
    FMATH_INLINE FMATH_CONSTEXPR Point<T, N> midpoint() const;

    FMATH_INLINE FMATH_CONSTEXPR Point<T, 3> barycoord(const Point<T, N> &p) const;

    FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> normal() const;

    FMATH_INLINE FMATH_CONSTEXPR bool contains(const Point<T, N> &point) const;

    FMATH_INLINE FMATH_CONSTEXPR void set(index_t index, const Point<T, N> &point);

    FMATH_INLINE FMATH_CONSTEXPR Plane<T> toPlane() const;

private:
    std::array<Point<ValueType, DIMENSION>, 3> vertices_;
};

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool operator==(const Triangle<T, N> &t1, const Triangle<T, N> &t2)
{
    return t1[0] == t2[0] && t1[1] == t2[1] && t1[2] == t2[2];
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool operator!=(const Triangle<T, N> &t1, const Triangle<T, N> &t2)
{
    return !(t1 == t2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool equal(const Triangle<T, N> &t1, const Triangle<T, N> &t2)
{
    return t1 == t2;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool notEqual(const Triangle<T, N> &t1, const Triangle<T, N> &t2)
{
    return t1 != t2;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool equalEpsilon(const Triangle<T, N> &t1, const Triangle<T, N> &t2, 
    const T epsilon = constants::Epsilon<T>::value)
{
    return equalEpsilon(t1[0], t2[0], epsilon) &&
        equalEpsilon(t1[1], t2[1], epsilon) &&
        equalEpsilon(t1[2], t2[2], epsilon);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool notEqualEpsilon(const Triangle<T, N> &t1, const Triangle<T, N> &t2, 
    const T epsilon = constants::Epsilon<T>::value)
{
    return !equalEpsilon(t1, t2, epsilon);
}

template<typename T, size_t N>
FMATH_INLINE std::string toString(const Triangle<T, N> &t, uint32 precision = 6)
{
    std::stringstream ss;
    ss << '(' << toString(t[0], precision) << ',' 
        << toString(t[1], precision) << ',' 
        << toString(t[2], precision) << ')';
    return ss.str();
}

template<typename T, size_t N>
FMATH_INLINE std::ostream &operator<<(std::ostream &output, const Triangle<T, N> &t)
{
    output << '(' << t[0] << ',' << t[1] << ',' << t[2] << ')';
    return output;
}

template<typename T, size_t N>
FMATH_CONSTEXPR Triangle<T, N>::Triangle(const Triangle &other)
    :   vertices_(other.vertices_)
{}

template<typename T, size_t N>
FMATH_CONSTEXPR Triangle<T, N>::Triangle()
    :   vertices_ { fmath::Point3f::zero(), fmath::Point3f::zero(), fmath::Point3f::zero() }
{}

template<typename T, size_t N>
FMATH_CONSTEXPR Triangle<T, N>::Triangle(const Point<T, N> &v0, const Point<T, N> &v1, const Point<T, N> &v2)
    :   vertices_ { v0, v1, v2 }
{}

template<typename T, size_t N>
FMATH_CONSTEXPR Triangle<T, N> &Triangle<T, N>::operator=(const Triangle &other)
{
    vertices_ = other.vertices_;
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR const Point<T, N> &Triangle<T, N>::operator[](index_t index) const
{
    return vertices_[index];
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> &Triangle<T, N>::operator[](index_t index)
{
    return vertices_[index];
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR const Point<T, N> &Triangle<T, N>::get(index_t index) const
{
    FMATH_ASSERT(index >= 0 && index < N);
    return vertices_[index];
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> &Triangle<T, N>::get(index_t index)
{
    FMATH_ASSERT(index >= 0 && index < N);
    return vertices_[index];
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T Triangle<T, N>::area() const
{
    return length(cross(vertices_[0] - vertices_[1], vertices_[0] - vertices_[2])) / static_cast<ValueType>(2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> Triangle<T, N>::midpoint() const
{
    return (vertices_[0] + vertices_[1] + vertices_[2]) / static_cast<ValueType>(3);
}

// See https://gamedev.stackexchange.com/questions/23743/whats-the-most-efficient-way-to-find-barycentric-coordinates
template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, 3> Triangle<T, N>::barycoord(const Point<T, N> &p) const
{
    Vector<T, N> v0 = vertices_[1] - vertices_[0];
    Vector<T, N> v1 = vertices_[2] - vertices_[0];
    Vector<T, N> v2 = p - vertices_[0];

    T f00 = dot(v0, v0);
    T f01 = dot(v0, v1);
    T f11 = dot(v1, v1);
    T f20 = dot(v2, v0);
    T f21 = dot(v2, v1);
    T denom = f00 * f11 - f01 * f01;

    T v = (f11 * f20 - f01 * f21) / denom;
    T w = (f00 * f21 - f01 * f20) / denom;
    T u = static_cast<T>(1) - v - w;
    return Point<T, 3>(u, v, w);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> Triangle<T, N>::normal() const
{
    return normalize(cross(vertices_[2] - vertices_[0], vertices_[1] - vertices_[0]));
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool Triangle<T, N>::contains(const Point<T, N> &point) const
{
    const std::array<Point<T, N>, 3> &p = vertices_;
    int32 s1 = static_cast<int32>(sign(cross(p[1] - p[0], point - p[0])));
    int32 s2 = static_cast<int32>(sign(cross(p[2] - p[1], point - p[1])));
    int32 s3 = static_cast<int32>(sign(cross(p[0] - p[2], point - p[2])));
    return s1 == s2 && s2 == s3;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR void Triangle<T, N>::set(index_t index, const Point<T, N> &point)
{
    FMATH_ASSERT(index >= 0 && index < N);
    vertices_[index] = point;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Plane<T> Triangle<T, N>::toPlane() const
{
    return Plane<T>(vertices_[0], vertices_[1], vertices_[2]);
}

template<typename T>
using Triangle2 = Triangle<T, 2>;

template<typename T>
using Triangle3 = Triangle<T, 3>;

using Triangle2f = Triangle2<float>;
using Triangle2lf = Triangle2<double>;

using Triangle3f = Triangle3<float>;
using Triangle3lf = Triangle3<double>;

}

#endif