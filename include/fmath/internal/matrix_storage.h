#ifndef _FMATH_INTERNAL_MATRIX_STORAGE_H_
#define _FMATH_INTERNAL_MATRIX_STORAGE_H_

#include <array>
#include <initializer_list>

#include "common.h"
#include "vector.h"

namespace fmath
{
namespace internal
{

template<typename T, size_t N>
struct MatrixStorage
{
    static_assert(N != 0);
    std::array<Vector<T, N>, N> values;

    MatrixStorage()
    {
        for (index_t i = 0; i < N; ++i)
            values[i] = Vector<T, N>::zero();
    }

    MatrixStorage(const std::initializer_list<T> &init_list)
    {
        constexpr size_t n = min(init_list.size(), N * N);
        for (index_t i = 0; i < n; ++i)
            values[i / N][i % N] = init_list[i];
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
        :   values { Vector<T, 2>(x0, y0), Vector<T, 2>(x1, y1) }
    {}

    explicit FMATH_CONSTEXPR MatrixStorage(const Vector<T, 2> &v0, const Vector<T, 2> &v1)
        :   values { v0, v1 }
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
        :   values { 
                Vector<T, 3>(x0, y0, z0),
                Vector<T, 3>(x1, y1, z1),
                Vector<T, 3>(x2, y2, z2) 
            }
    {}

    explicit FMATH_CONSTEXPR MatrixStorage(const Vector<T, 3> &v0, const Vector<T, 3> &v1, const Vector<T, 3> &v2)
        :   values { v0, v1, v2 }
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
        :   values { 
                Vector<T, 4>(x0, y0, z0, w0),
                Vector<T, 4>(x1, y1, z1, w1),
                Vector<T, 4>(x2, y2, z2, w2),
                Vector<T, 4>(x3, y3, z3, w3)
            }
    {
    }

    explicit FMATH_CONSTEXPR MatrixStorage(const Vector<T, 4> &v0, const Vector<T, 4> &v1, 
        const Vector<T, 4> &v2, const Vector<T, 4> &v3)
        :   values { v0, v1, v2, v3 }
    {}
};

}
}

#endif