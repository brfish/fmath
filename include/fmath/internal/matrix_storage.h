#ifndef _FMATH_INTERNAL_MATRIX_STORAGE_H_
#define _FMATH_INTERNAL_MATRIX_STORAGE_H_

#include <array>

#include "common.h"
#include "vector.h"

namespace fmath
{
namespace internal
{

template<typename T, size_t N>
struct MatrixStorage
{
    std::array<Vector<T, N>, N> values;

    FMATH_CONSTEXPR MatrixStorage()
    {
        for (index_t i = 0; i < N; ++i)
            values[i] = Vector<T, N>::zero();
    }
};

template<typename T>
struct MatrixStorage<T, 2>
{
    union
    {
        std::array<Vector<T, 2>, 2> values;
        struct { Vector<T, 2> v0, v1; };
    };

    explicit FMATH_CONSTEXPR MatrixStorage(const T &x0 = 0, const T &y0 = 0, const T &x1 = 0, const T &y1 = 0)
        :   v0(x0, y0),
            v1(x1, y1);
    {}

    explicit FMATH_CONSTEXPR MatrixStorage(const Vector<T, 2> &v0, const Vector<T, 2> &v1)
        :   v0(v0),
            v1(v1)
    {}
};

template<typename T>
struct MatrixStorage<T, 3>
{
    union
    {
        std::array<Vector<T, 3>, 3> values;
        struct { Vector<T, 3> v0, v1, v2; };
    };

    explicit FMATH_CONSTEXPR MatrixStorage(const T &x0 = 0, const T &y0 = 0, const T &z0 = 0,
        const T &x1 = 0, const T &y1 = 0, const T &z1 = 0,
        const T &x2 = 0, const T &y2 = 0, const T &z2 = 0)
        :   v0(x0, y0, z0),
            v1(x1, y1, z1),
            v2(x2, y2, z2)
    {}

    explicit FMATH_CONSTEXPR MatrixStorage(const Vector<T, 3> &v0, const Vector<T, 3> &v1, const Vector<T, 3> &v2)
        :   v0(v0),
            v1(v1),
            v2(v2)
    {}
};

template<typename T>
struct MatrixStorage<T, 4>
{
    union
    {
        std::array<Vector<T, 4>, 4> values;
        struct { Vector<T, 4> v0, v1, v2, v3; };
    };

    explicit FMATH_CONSTEXPR MatrixStorage(const T &x0 = 0, const T &y0 = 0, const T &z0 = 0, const T &w0 = 0,
        const T &x1 = 0, const T &y1 = 0, const T &z1 = 0, const T &w1 = 0,
        const T &x2 = 0, const T &y2 = 0, const T &z2 = 0, const T &w2 = 0,
        const T &x3 = 0, const T &y3 = 0, const T &z3 = 0, const T &w3 = 0)
        :   v0(x0, y0, z0, w0),
            v1(x1, y1, z1, w1),
            v2(x2, y2, z2, w2),
            v3(x3, y3, z3, w3)
    {
    }

    explicit FMATH_CONSTEXPR MatrixStorage(const Vector<T, 4> &v0, const Vector<T, 4> &v1, 
        const Vector<T, 4> &v2, const Vector<T, 4> &v3)
        :   v0(v0),
            v1(v1),
            v2(v2),
            v3(v3)
    {}
};

}
}

#endif