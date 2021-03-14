#ifndef _FMATH_INTERNAL_VECTOR_STORAGE_H_
#define _FMATH_INTERNAL_VECTOR_STORAGE_H_

#include <array>

#include "common.h"
#include "compile_config.h"
#include "functions.h"

namespace fmath
{
namespace internal
{

template<typename T, size_t N>
struct VectorStorage
{
    std::array<T, N> values;

    explicit FMATH_CONSTEXPR VectorStorage()
    {
        values.fill(0);
    }
};

template<typename T>
struct VectorStorage<T, 2>
{
    union
    {
        std::array<T, 2> values;
        struct { T x, y; };
    };

    explicit FMATH_CONSTEXPR VectorStorage(const T &x = 0, const T &y = 0)
        :   x(x),
            y(y)
    {}
};

template<typename T>
struct VectorStorage<T, 3>
{
    union
    {
        std::array<T, 3> values;
        struct { T x, y, z; };
    };

    explicit FMATH_CONSTEXPR VectorStorage(const T &x = 0, const T &y = 0, const T &z = 0)
        :   x(x),
            y(y),
            z(z)
    {}
};

template<typename T>
struct VectorStorage<T, 4>
{
    union
    {
        std::array<T, 4> values;
        struct { T x, y, z, w; };
    };

    explicit FMATH_CONSTEXPR VectorStorage(const T &x = 0, const T &y = 0, const T &z = 0, const T &w = 0)
        :   x(x),
            y(y),
            z(z),
            w(w)
    {}
};

}
}

#endif