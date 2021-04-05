#ifndef _FMATH_BOUND_H_
#define _FMATH_BOUND_H_

#include <initializer_list>

#include "common.h"
#include "constants.h"
#include "point.h"
#include "vector.h"

namespace fmath
{

template<typename T, size_t N>
class Box
{
public:
    using ValueType = T;
    static constexpr size_t DIMENSION = N;

public:
    FMATH_CONSTEXPR Box(const Box &other);

    explicit FMATH_CONSTEXPR Box(const Point<T, N> &p0 = constants::MIN_VALUE<Point<T, N>>, 
        const Point<T, N> &p1 = constants::MAX_VALUE<Point<T, N>>);

    FMATH_CONSTEXPR Box &operator=(const Box &other);

    FMATH_INLINE FMATH_CONSTEXPR const Point<T, N> &min() const;

    FMATH_INLINE FMATH_CONSTEXPR Point<T, N> &min();

    FMATH_INLINE FMATH_CONSTEXPR const Point<T, N> &max() const;

    FMATH_INLINE FMATH_CONSTEXPR Point<T, N> &max();

    FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> diagonal() const;

    FMATH_INLINE FMATH_CONSTEXPR bool contains(const Point<ValueType, N> &point);

    FMATH_INLINE FMATH_CONSTEXPR bool contains(const Box<ValueType, N> &box);

    FMATH_INLINE FMATH_CONSTEXPR bool overlaps(const Box<ValueType, N> &box);

    FMATH_INLINE FMATH_CONSTEXPR bool isEmpty() const;

    FMATH_INLINE Box &add(const Box &other);

    FMATH_INLINE Box &add(const Point<ValueType, N> &point);

    FMATH_INLINE Box &operator+=(const Box &other);

    FMATH_INLINE Box &operator+=(const Point<ValueType, N> &point);

    static FMATH_CONSTEXPR Box make(const std::initializer_list<Point<ValueType, N>> &points);

    static FMATH_CONSTEXPR Box makeEmpty();

private:
    Point<ValueType, DIMENSION> min_;
    Point<ValueType, DIMENSION> max_;
};

template<typename T, size_t N>
bool operator==(const Box<T, N> &b1, const Box<T, N> &b2)
{
    return b1.min() == b2.min() && b1.max() == b2.max();
}

template<typename T, size_t N>
bool operator!=(const Box<T, N> &b1, const Box<T, N> &b2)
{
    return !(b1 == b2);
}

template<typename T, size_t N>
bool equal(const Box<T, N> &b1, const Box<T, N> &b2)
{
    return b1 == b2;
}

template<typename T, size_t N>
bool notEqual(const Box<T, N> &b1, const Box<T, N> &b2)
{
    return b1 != b2;
}

template<typename T, size_t N>
bool equalEpsilon(const Box<T, N> &b1, const Box<T, N> &b2, const T epsilon = constants::Epsilon<T>::value)
{
    return equalEpsilon(b1.min(), b2.min(), epsilon) &&
        equalEpsilon(b1.max(), b2.max(), epsilon);
}

template<typename T, size_t N>
bool notEqualEpsilon(const Box<T, N> &b1, const Box<T, N> &b2, const T epsilon = constants::Epsilon<T>::value)
{
    return !(equalEpsilon(b1, b2, epsilon));
}

template<typename T, size_t N>
Box<T, N> operator+(const Box<T, N> &b1, const Box<T, N> &b2)
{
    Box<T, N> result(b1);
    result += b2;
    return result;
}

template<typename T, size_t N>
Box<T, N> operator+(const Box<T, N> &box, const Point<T, N> &point)
{
    Box<T, N> result(box);
    result += point;
    return result;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR std::string toString(const Box<T, N> &box, uint32 precision = 6)
{
    std::stringstream ss;
    ss << '(' << box.min() << ',' << box.max() << ')';
    return ss.str();
}

template<typename T, size_t N>
std::ostream &operator<<(std::ostream &output, const Box<T, N> &box)
{
    output << '(' << box.min() << ',' << box.max() << ')';
    return output;
}

template<typename T, size_t N>
FMATH_CONSTEXPR Box<T, N>::Box(const Box &other)
    :   min_(other.min_),
        max_(other.max_)
{}

template<typename T, size_t N>
FMATH_CONSTEXPR Box<T, N>::Box(const Point<T, N> &p0, const Point<T, N> &p1)
    :   min_(componentWiseMin(p0, p1)),
        max_(componentWiseMax(p0, p1))
{}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Box<T, N> &Box<T, N>::operator=(const Box &other)
{
    min_ = other.min_;
    max_ = other.max_;
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR const Point<T, N> &Box<T, N>::min() const
{
    return min_;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> &Box<T, N>::min()
{
    return min_;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR const Point<T, N> &Box<T, N>::max() const
{
    return max_;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> &Box<T, N>::max()
{
    return max_;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> Box<T, N>::diagonal() const
{
    return max_ - min_;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool Box<T, N>::contains(const Point<ValueType, N> &point)
{
    return point >= min_ && point <= max_;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool Box<T, N>::contains(const Box<ValueType, N> &box)
{
    return box.min_ >= min_ && box.max_ <= max_;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool Box<T, N>::overlaps(const Box<ValueType, N> &box)
{
    return min_ <= box.max_ && max_ >= box.min_;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool Box<T, N>::isEmpty() const
{
    return min_ > max_;
}

template<typename T, size_t N>
FMATH_INLINE Box<T, N> &Box<T, N>::add(const Box &other)
{
    min_ = componentWiseMin(min_, other.min_);
    max_ = componentWiseMax(max_, other,max_);
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE Box<T, N> &Box<T, N>::add(const Point<ValueType, N> &point)
{
    min_ = componentWiseMin(min_, point);
    max_ = componentWiseMax(max_, point);
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE Box<T, N> &Box<T, N>::operator+=(const Box &other)
{
    return add(other);
}

template<typename T, size_t N>
FMATH_INLINE Box<T, N> &Box<T, N>::operator+=(const Point<ValueType, N> &point)
{
    return add(point);
}

template<typename T, size_t N>
FMATH_CONSTEXPR Box<T, N> Box<T, N>::make(const std::initializer_list<Point<ValueType, N>> &points)
{
    Box<T, N> result;
    for (const auto &p : points)
    {
        result.min_ = componentWiseMin(result.min_, p);
        result.max_ = componentWiseMax(result.max_, p);
    }
    return result;
}

template<typename T, size_t N>
FMATH_CONSTEXPR Box<T, N> Box<T, N>::makeEmpty()
{
    Box<T, N> result;
    result.min_ = constants::MAX_VALUE<Point<T, N>>;
    result.max_ = constants::MIN_VALUE<Point<T, N>>;
    return result;
}

template<typename T>
using Box2 = Box<T, 2>;

template<typename T>
using Box3 = Box<T, 3>;

using Box2f = Box2<float>;
using Box2lf = Box2<double>;

using Box3f = Box3<float>;
using Box3lf = Box3<double>;

}

#endif