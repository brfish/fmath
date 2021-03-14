#ifndef _FMATH_POINT_H_
#define _FMATH_POINT_H_

#include "internal/vector_storage.h"
#include "common.h"
#include "vector.h"

namespace fmath
{

template<typename T, size_t N>
class Point : public internal::VectorStorage<T, N>
{
public:
    using ValueType = T;
    static constexpr size_t SIZE = N;
public:
    using internal::VectorStorage<T, N>::VectorStorage;

    Point(const Point &other);

    Point(const ValueType *data, size_t count);

    Point &operator=(const Point &other);

    FMATH_INLINE FMATH_CONSTEXPR bool equals(const Point &other) const;

    FMATH_INLINE FMATH_CONSTEXPR size_t size() const;

    FMATH_INLINE FMATH_CONSTEXPR const ValueType *data() const;

    FMATH_INLINE FMATH_CONSTEXPR ValueType *data();

    FMATH_INLINE FMATH_CONSTEXPR const ValueType &get(index_t index) const;

    FMATH_INLINE FMATH_CONSTEXPR ValueType &get(index_t index);

    FMATH_INLINE void set(index_t index, const ValueType &value);

    FMATH_INLINE FMATH_CONSTEXPR const ValueType &operator[](index_t index) const;

    FMATH_INLINE FMATH_CONSTEXPR ValueType &operator[](index_t index);

    FMATH_INLINE FMATH_CONSTEXPR Point operator+() const;

    FMATH_INLINE FMATH_CONSTEXPR Point operator-() const;

    Point &operator+=(const Vector<T, N> &vec);

    Point &operator+=(const ValueType &value);

    Point &operator-=(const Vector<T, N> &vec);

    Point &operator-=(const ValueType &value);

    Point &operator*=(const ValueType &value);

    Point &operator/=(const ValueType &value);

    static Point zero();
};

template<typename T, size_t N>
struct PointTraits
{
    using ValueType = T;
    static constexpr size_t SIZE = N;

    static FMATH_CONSTEXPR bool equal(const Point<T, N> &p1, const Point<T, N> &p2);
    static FMATH_CONSTEXPR bool equalEpsilon(const Point<T, N> &p1, const Point<T, N> &p2, const T &epsilon = Epsilon<T>::value);

    static FMATH_CONSTEXPR Point<T, N> add(const Point<T, N> &p, const Vector<T, N> &v);
    static FMATH_CONSTEXPR Point<T, N> add(const Point<T, N> &p, const T &value);
    static FMATH_CONSTEXPR Vector<T, N> sub(const Point<T, N> &p1, const Point<T, N> &p2);
    static FMATH_CONSTEXPR Vector<T, N> sub(const Point<T, N> &p, const Vector<T, N> &v);
    static FMATH_CONSTEXPR Point<T, N> sub(const Point<T, N> &p, const T &value);
    static FMATH_CONSTEXPR Point<T, N> mul(const Point<T, N> &p, const T &value);
    static FMATH_CONSTEXPR Point<T, N> div(const Point<T, N> &p, const T &value);

    static FMATH_CONSTEXPR Point<T, N> hadamardMul(const Point<T, N> &p1, const Point<T, N> &p2);
    static FMATH_CONSTEXPR Point<T, N> hadamardDiv(const Point<T, N> &p1, const Point<T, N> &p2);

    static FMATH_CONSTEXPR T distance(const Point<T, N> &p1, const Point<T, N> &p2);
};

template<typename T, size_t N>
Point<T, N> operator+(const Point<T, N> &p1, const Vector<T, N> &p2);

template<typename T, size_t N>
Point<T, N> operator-(const Point<T, N> &p1, const Vector<T, N> &p2);

template<typename T, size_t N>
Point<T, N> operator-(const Point<T, N> &p1, const Point<T, N> &p2);



}

#endif