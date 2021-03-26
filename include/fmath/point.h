#ifndef _FMATH_POINT_H_
#define _FMATH_POINT_H_

#include <type_traits>

#include "internal/vector_base.h"
#include "internal/vector_traits.h"
#include "common.h"
#include "vector.h"

namespace fmath
{

template<typename T, size_t N>
class Point : public internal::VectorBase<T, N>
{
public:
    using ValueType = T;
    static constexpr size_t SIZE = N;

public:
    using internal::VectorBase<T, N>::VectorBase;

    template<typename U, size_t M, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
    Point(const Point<U, M> &other);

    template<typename U, size_t M, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
    Point &operator=(const Point<U, M> &other);

    FMATH_INLINE FMATH_CONSTEXPR Point operator+() const;

    FMATH_INLINE FMATH_CONSTEXPR Point operator-() const;

    FMATH_INLINE Point &operator+=(const Vector<T, N> &vec);

    FMATH_INLINE Point &operator+=(const ValueType &value);

    FMATH_INLINE Point &operator-=(const Vector<T, N> &vec);

    FMATH_INLINE Point &operator-=(const ValueType &value);

    FMATH_INLINE Point &operator*=(const ValueType &value);

    FMATH_INLINE Point &operator/=(const ValueType &value);

    static FMATH_CONSTEXPR Point zero();
};

namespace internal
{

template<typename T, size_t N>
struct VectorTraits_TypeInfo<Point<T, N>>
{
    template<typename U, size_t M>
    using VectorType = Point<U, M>;

    using ValueType = T;
    static constexpr size_t SIZE = N;
};

template<typename T, size_t N>
struct PointTraits :
    VectorTraits_Add<T, N, Point<T, N>>,
    VectorTraits_Compare<T, N>,
    VectorTraits_Input<T, N>,
    VectorTraits_Norm<T, N>,
    VectorTraits_Output<T, N>,
    VectorTraits_Scale<T, N, Point<T, N>>,
    VectorTraits_Stringify<T, N>
{};

};

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool operator==(const Point<T, N> &p1, const Point<T, N> &p2)
{
    return internal::PointTraits<T, N>::equal(p1, p2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool operator!=(const Point<T, N> &p1, const Point<T, N> &p2)
{
    return !internal::PointTraits<T, N>::equal(p1, p2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool equal(const Point<T, N> &p1, const Point<T, N> &p2)
{
    return internal::PointTraits<T, N>::equal(p1, p2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool notEqual(const Point<T, N> &p1, const Point<T, N> &p2)
{
    return !equal(p1, p2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool equalEpsilon(const Point<T, N> &p1, const Point<T, N> &p2, const T epsilon = number::Epsilon<T>::value)
{
    return internal::PointTraits<T, N>::equalEpsilon(p1, p2, epsilon);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool notEqualEpsilon(const Point<T, N> &p1, const Point<T, N> &p2, const T epsilon = number::Epsilon<T>::value)
{
    return !equalEpsilon(p1, p2, epsilon);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T minComponent(const Point<T, N> &p)
{
    return internal::PointTraits<T, N>::minComponent(p);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T maxComponent(const Point<T, N> &p)
{
    return internal::PointTraits<T, N>::maxComponent(p);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> operator+(const Point<T, N> &p, const Vector<T, N> &v)
{
    return internal::PointTraits<T, N>::add(p, v);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> operator+(const Point<T, N> &p, const T &value)
{
    return internal::PointTraits<T, N>::add(p, value);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> operator-(const Point<T, N> &p, const Vector<T, N> &v)
{
    return internal::PointTraits<T, N>::sub(p, v);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> operator-(const Point<T, N> &p, const T &value)
{
    return internal::PointTraits<T, N>::sub(p, value);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> operator-(const Point<T, N> &p1, const Point<T, N> &p2)
{
    return internal::VectorTraits_Add<T, N, Vector<T, N>>::sub(p1, p2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> operator*(const Point<T, N> &p, const T &value)
{
    return internal::PointTraits<T, N>::mul(p, value);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> operator*(const T &value, const Point<T, N> &p)
{
    return internal::PointTraits<T, N>::mul(p, value);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> operator/(const Point<T, N> &p, const T &value)
{
    return internal::PointTraits<T, N>::div(p, value);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> add(const Point<T, N> &p, const Vector<T, N> &v)
{
    return p + v;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> add(const Point<T, N> &p, const T &value)
{
    return p + value;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> sub(const Point<T, N> &p1, const Point<T, N> &p2)
{
    return p1 - p2;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> sub(const Point<T, N> &p, const T &value)
{
    return p - value;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> mul(const Point<T, N> &p, const T &value)
{
    return p * value;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> div(const Point<T, N> &p, const T &value)
{
    return p / value;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T distance2(const Point<T, N> &p1, const Point<T, N> &p2)
{
    return internal::PointTraits<T, N>::length2(p1 - p2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T distance(const Point<T, N> &p1, const Point<T, N> &p2)
{
    return sqrt(distance2(p1, p2));
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> opposite(const Point<T, N> &p)
{
    return -p;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR std::string toString(const Point<T, N> &vec, uint32 precision = 6)
{
    return internal::PointTraits<T, N>::toString(vec, precision);
}

template<typename T, size_t N>
std::ostream &operator<<(std::ostream &output, const Point<T, N> &p)
{
    internal::PointTraits<T, N>::write(output, p);
    return output;
}

template<typename T, size_t N>
std::istream &operator>>(std::istream &input, Point<T, N> &p)
{
    internal::PointTraits<T, N>::read(input, p);
    return input;
}

template<typename T, size_t N>
    template<typename U, size_t M, typename>
Point<T, N>::Point(const Point<U, M> &other)
{
    constexpr size_t REAL = min(SIZE, M);
    for (index_t i = 0; i < REAL; ++i)
        this->values[i] = static_cast<ValueType>(other[i]);
}

template<typename T, size_t N>
    template<typename U, size_t M, typename>
Point<T, N> &Point<T, N>::operator=(const Point<U, M> &other)
{
    constexpr size_t REAL = min(SIZE, M);
    for (index_t i = 0; i < REAL; ++i)
        this->values[i] = static_cast<ValueType>(other[i]);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> Point<T, N>::operator+() const
{
    return Point(*this);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Point<T, N> Point<T, N>::operator-() const
{
    return zero() - (*this);
}

template<typename T, size_t N>
FMATH_INLINE Point<T, N> &Point<T, N>::operator+=(const Vector<T, N> &vec)
{
    *this = (*this) + vec;
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE Point<T, N> &Point<T, N>::operator+=(const ValueType &value)
{
    *this = (*this) + value;
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE Point<T, N> &Point<T, N>::operator-=(const Vector<T, N> &vec)
{
    *this = (*this) - vec;
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE Point<T, N> &Point<T, N>::operator-=(const ValueType &value)
{
    *this = (*this) - value;
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE Point<T, N> &Point<T, N>::operator*=(const ValueType &value)
{
    *this = (*this) * value;
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE Point<T, N> &Point<T, N>::operator/=(const ValueType &value)
{
    *this = (*this) / value;
    return *this;
}

template<typename T, size_t N>
FMATH_CONSTEXPR Point<T, N> Point<T, N>::zero()
{
    return Point();
}

template<typename T>
using Point2 = Point<T, 2>;

template<typename T>
using Point3 = Point<T, 3>;

template<typename T>
using Point4 = Point<T, 4>;

using Point2u  = Point2<uint32>;
using Point2i  = Point2<int32>;
using Point2f  = Point2<float>;
using Point2lf = Point2<double>;

using Point3u  = Point3<uint32>;
using Point3i  = Point3<int32>;
using Point3f  = Point3<float>;
using Point3lf = Point3<double>;

using Point4u  = Point4<uint32>;
using Point4i  = Point4<int32>;
using Point4f  = Point4<float>;
using Point4lf = Point4<double>;

}

#endif