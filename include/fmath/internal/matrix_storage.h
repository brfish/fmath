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
};

template<typename T>
struct MatrixStorage<T, 2>
{
    std::array<Vector<T, 2>, 2> values;

    MatrixStorage(const T &x0, const T &y0, const T &x1, const T &y1);
    MatrixStorage(const Vector<T, 2> &v0, const Vector<T, 2> &v1);
};

template<typename T>
struct MatrixStorage<T, 3>
{
    std::array<Vector<T, 3>, 3> values;

    MatrixStorage(const T &x0, const T &y0, const T &z0,
        const T &x1, const T &y1, const T &z1,
        const T &x2, const T &y2, const T &z2);
    MatrixStorage(const Vector<T, 3> &v0, const Vector<T, 3> &v1, const Vector<T, 3> &v2);
};

template<typename T>
struct MatrixStorage<T, 4>
{
    std::array<Vector<T, 4>, 4> values;

    MatrixStorage(const T &x0, const T &y0, const T &z0, const T &w0,
        const T &x1, const T &y1, const T &z1, const T &w1,
        const T &x2, const T &y2, const T &z2, const T &w2,
        const T &x3, const T &y3, const T &z3, const T &w3);
    MatrixStorage(const Vector<T, 4> &v0, const Vector<T, 4> &v1, const Vector<T, 4> &v2, const Vector<T, 4> &v3);
};

}
}

#endif