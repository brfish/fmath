#ifndef _FMATH_COMMON_H_
#define _FMATH_COMMON_H_

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <string>
#include <type_traits>

#include "compile_config.h"

namespace fmath
{

using int8      =   int8_t;
using uint8     =   uint8_t;
using int16     =   int16_t;
using uint16    =   uint16_t;
using int32     =   int32_t;
using uint32    =   uint32_t;
using int64     =   int64_t;
using uint64    =   uint64_t;

using uchar     =   unsigned char;
using byte8     =   unsigned char;

using size_t    =   ::size_t;
using ssize_t   =   ::ssize_t;
using index_t   =   size_t;
using offset_t  =   ptrdiff_t;
using diff_t    =   ptrdiff_t;

using angle_t   =   double;

#define FMATH_ASSERT(Expr) assert(Expr)

enum class Axis
{
    X, Y, Z
};

enum class Component
{
    X = 0, Y = 1, Z = 2, W = 3,
    R = 0, G = 1, B = 2, A = 3,
};

template<typename T>
std::string toString(const T &value, uint32 precision = 6)
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision);

    if constexpr (std::is_integral_v<T> && sizeof(T) <= 2)
    {
        using PromotedType = std::conditional_t<std::is_signed_v<T>, int32, uint32>;
        ss << static_cast<PromotedType>(value);
    }
    else
        ss << value;
    return ss.str();
}

}

#endif