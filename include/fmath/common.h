#ifndef _FMATH_COMMON_H_
#define _FMATH_COMMON_H_

#include <cassert>
#include <cstdarg>
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

namespace internal
{

static void assertFormatPrint(const char *filename, index_t line, 
    const char *expression, const char *format, ...)
{
    printf("Source: %s:%d\n", filename, line);
    printf("Expected: %s\n", expression);
    printf("Message: ");
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    putchar('\n');
}

}

#ifndef NDEBUG
#   define FMATH_ASSERT(Expr) \
        do { if (!(Expr)) { internal::assertFormatPrint(__FILE__, __LINE__, #Expr, "Assertion failed"); std::abort(); }} while (false)

#   define FMATH_FASSERT(Expr, Fmt, ...) \
        do { if (!(Expr)) { internal::assertFormatPrint(__FILE__, __LINE__, #Expr, (Fmt), ##__VA_ARGS__); std::abort(); }} while (false)
#else
#   define FMATH_ASSERT(Expr)
#   define FMATH_FASSERT(Expr, Fmt, ...)
#endif

enum class Axis
{
    X, Y, Z
};

enum class Component : uint8
{
    X = 0x00, Y = 0x01, Z = 0x02, W = 0x03,
    R = 0x10, G = 0x11, B = 0x12, A = 0x13,
    S = 0x20, T = 0x21, P = 0x22, Q = 0x23
};

template<typename T>
FMATH_ALWAYS_INLINE std::string toString(const T &value, uint32 precision = 6)
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