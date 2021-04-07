#ifndef _FMATH_LINE_H_
#define _FMATH_LINE_H_

#include "box.h"
#include "common.h"
#include "constants.h"
#include "point.h"

namespace fmath
{

template<typename T, size_t N>
class Line
{
public:
    using ValueType = T;
    static constexpr size_t DIMENSION = N;

public:
    FMATH_CONSTEXPR Line(const Line &other);

    explicit FMATH_CONSTEXPR Line(const Point<ValueType, N> &start, const Point<ValueType, N> &end);

    explicit FMATH_CONSTEXPR Line(const Point<ValueType, N> &start, const Vector<ValueType, N> &delta);

    FMATH_CONSTEXPR Line &operator=(const Line &other);

    FMATH_INLINE FMATH_CONSTEXPR const Point<T, N> &start() const;

    FMATH_INLINE FMATH_CONSTEXPR Point<T, N> &start();

    FMATH_INLINE FMATH_CONSTEXPR const Point<ValueType, N> &end() const;

    FMATH_INLINE FMATH_CONSTEXPR Point<T, N> &end();

    FMATH_INLINE FMATH_CONSTEXPR Point<T, N> at(const ValueType &t);

    FMATH_INLINE FMATH_CONSTEXPR Point<T, N> middle() const;

    FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> deltaVector() const;

    FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> direction() const;

    FMATH_INLINE FMATH_CONSTEXPR T length2() const;

    FMATH_INLINE FMATH_CONSTEXPR T length() const;

    FMATH_INLINE FMATH_CONSTEXPR Box<T, N> bound() const;

    FMATH_INLINE void setStart(const Point<ValueType, N> &start);

    FMATH_INLINE void setEnd(const Point<ValueType, N> &end);

private:
    Point<ValueType, DIMENSION> start_;
    Point<ValueType, DIMENSION> end_;
};

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool operator==(const Line<T, N> &l1, const Line<T, N> &l2)
{
    return l1.start() == l2.start() && l1.end() == l2.end();
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool operator!=(const Line<T, N> &l1, const Line<T, N> &l2)
{
    return !(l1 == l2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool equal(const Line<T, N> &l1, const Line<T, N> &l2)
{
    return l1 == l2;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool notEqual(const Line<T, N> &l1, const Line<T, N> &l2)
{
    return l1 != l2;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool equalEpsilon(const Line<T, N> &l1, const Line<T, N> &l2, const T &epsilon = constants::Epsilon<T>::value)
{
    return equalEpsilon(l1.start(), l2.start(), epsilon) &&
        equalEpsilon(l1.end(), l2.end(), epsilon);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool notEqualEpsilon(const Line<T, N> &l1, const Line<T, N> &l2, const T &epsilon = constants::Epsilon<T>::value)
{
    return !equalEpsilon(l1, l2, epsilon);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T length2(const Line<T, N> &l)
{
    return distance2(l.start(), l.end());
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T length(const Line<T, N> &l)
{
    return distance(l.start(), l.end());
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T distance2(const Line<T, N> &l, const Point<T, N> &p)
{
    Vector<T, N> hypotenuse = l.start() - p;
    Vector<T, N> direction = l.direction();

    return length2(hypotenuse - (hypotenuse * direction) * direction);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T distance2(const Point<T, N> &p, const Line<T, N> &l)
{
    return distance2(l, p);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T distance(const Line<T, N> &l, const Point<T, N> &p)
{
    Vector<T, N> hypotenuse = l.start() - p;
    Vector<T, N> direction = l.direction();

    return length(hypotenuse - (hypotenuse * direction) * direction);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T distance(const Point<T, N> &p, const Line<T, N> &l)
{
    return distance(l, p);
}

template<typename T, size_t N>
FMATH_INLINE std::string toString(const Line<T, N> &l, uint32 precision = 6)
{
    std::stringstream ss;
    ss << '(' << toString(l.start(), precision) << ',' << toString(l.end(), precision) << ')';
    return ss.str();
}

template<typename T, size_t N>
FMATH_INLINE std::ostream &operator<<(std::ostream &output, const Line<T, N> &l)
{
    output << '(' << l.start() << ',' << l.end() << ')';
    return output;
}

template<typename T, size_t N>
FMATH_CONSTEXPR Line<T, N>::Line(const Line &other)
    :   start_(other.start_),
        end_(other.end_)
{}

template<typename T, size_t N>
FMATH_CONSTEXPR Line<T, N>::Line(const Point<ValueType, N> &start, const Point<ValueType, N> &end)
    :   start_(start),
        end_(end)
{}

template<typename T, size_t N>
FMATH_CONSTEXPR Line<T, N>::Line(const Point<ValueType, N> &start, const Vector<ValueType, N> &delta)
    :   start_(start),
        end_(start + delta)
{}

template<typename T, size_t N>
FMATH_CONSTEXPR Line<T, N> &Line<T, N>::operator=(const Line &other)
{
    start_ = other.start_;
    end_ = other.end_;
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR const Point<T, N> &Line<T, N>::start() const
{
    return start_;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> &Line<T, N>::start()
{
    return start_;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR const Point<T, N> &Line<T, N>::end() const
{
    return end_;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> &Line<T, N>::end()
{
    return end_;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> Line<T, N>::at(const ValueType &t)
{
    return start_ + (end_ - start_) * t;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> Line<T, N>::middle() const
{
    return at(static_cast<ValueType>(0.5));
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> Line<T, N>::deltaVector() const
{
    return end_ - start_;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> Line<T, N>::direction() const
{
    return normalize(deltaVector());
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T Line<T, N>::length2() const
{
    return distance2(start_, end_);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T Line<T, N>::length() const
{
    return distance(start_, end_);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Box<T, N> Line<T, N>::bound() const
{
    return Box<T, N>(start_, end_);
}

template<typename T, size_t N>
FMATH_INLINE void Line<T, N>::setStart(const Point<ValueType, N> &start)
{
    start_ = start;
}

template<typename T, size_t N>
FMATH_INLINE void Line<T, N>::setEnd(const Point<ValueType, N> &end)
{
    end_ = end;
}

template<typename T>
using Line2 = Line<T, 2>;

template<typename T>
using Line3 = Line<T, 3>;

using Line2f = Line2<float>;
using Line2lf = Line2<double>;

using Line3f = Line3<float>;
using Line3lf = Line3<double>;

}

#endif