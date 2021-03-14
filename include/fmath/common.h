#ifndef _FMATH_COMMON_H_
#define _FMATH_COMMON_H_

#include <cstdint>
#include <cstdlib>

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

}

#endif