#ifndef _FMATH_INTERNAL_COLOR_STORAGE_H_
#define _FMATH_INTERNAL_COLOR_STORAGE_H_

#include <array>

#include "common.h"

namespace fmath
{
namespace internal
{

template<typename T, size_t N>
struct ColorStorage
{
    std::array<T, N> values;
};

template<typename T>
struct ColorStorage<T, 3>
{
    union
    {
        std::array<T, 3> values;
        struct { T r, g, b; };
    };
};

template<typename T>
struct ColorStorage<T, 4>
{
    union
    {
        std::array<T, 4> values;
        struct { T r, g, b, a; };
    };
};

}
}

#endif