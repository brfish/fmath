#ifndef _FMATH_INTERNAL_COLOR_STORAGE_H_
#define _FMATH_INTERNAL_COLOR_STORAGE_H_

#include <array>

#include "../common.h"
#include "../math_common_functions.h"
#include "../vector.h"

namespace fmath
{

namespace internal
{

template<typename T, size_t N>
struct ColorStorage
{};

template<>
struct ColorStorage<float, 3>
{
    union
    {
        Vector3<float> values;
        struct { float r, g, b; };
    };

    explicit FMATH_CONSTEXPR ColorStorage(const float &r = 0.0F, const float &g = 0.0F, const float &b = 0.0F)
        :   values { clamp(r, 0.0F, 1.0F), clamp(g, 0.0F, 1.0F), clamp(b, 0.0F, 1.0F) }
    {}

    FMATH_CONSTEXPR ColorStorage(const Vector3<float> &vec)
        :   ColorStorage(vec[0], vec[1], vec[2])
    {}

    explicit FMATH_CONSTEXPR ColorStorage(const float *data)
        :   ColorStorage(data[0], data[1], data[2])
    {}
};

template<>
struct ColorStorage<float, 4>
{
    union
    {
        Vector4<float> values;
        struct { float r, g, b, a; };
    };

    explicit FMATH_CONSTEXPR ColorStorage(const float &r = 0.0F, const float &g = 0.0F, const float &b = 0.0F, const float &a = 1.0F)
        :   values { clamp(r, 0.0F, 1.0F), clamp(g, 0.0F, 1.0F), clamp(b, 0.0F, 1.0F), clamp(a, 0.0F, 1.0F) }
    {}

    FMATH_CONSTEXPR ColorStorage(const Vector4<float> &vec)
        :   ColorStorage(vec[0], vec[1], vec[2], vec[3])
    {}

    explicit FMATH_CONSTEXPR ColorStorage(const float *data)
        :   ColorStorage(data[0], data[1], data[2], data[3])
    {}
};

template<>
struct ColorStorage<uint8, 3>
{
    union
    {
        Vector3<uint8> values;
        struct { uint8 r, g, b; };
    };

    explicit FMATH_CONSTEXPR ColorStorage(const uint8 &r = 0, const uint8 &g = 0, const uint8 &b = 0)
        :   values { clamp(r, 0, 255), clamp(g, 0, 255), clamp(b, 0, 255) }
    {}

    FMATH_CONSTEXPR ColorStorage(const Vector3<uint8> &vec)
        :   ColorStorage(vec[0], vec[1], vec[2])
    {}

    explicit FMATH_CONSTEXPR ColorStorage(const uint8 *data)
        :   ColorStorage(data[0], data[1], data[2])
    {}
};

template<>
struct ColorStorage<uint8, 4>
{
    union
    {
        Vector4<uint8> values;
        struct { uint8 r, g, b, a; };
    };

    explicit FMATH_CONSTEXPR ColorStorage(const uint8 &r = 0, const uint8 &g = 0, const uint8 &b = 0, const uint8 &a = 255)
        :   values { clamp(r, 0, 255), clamp(g, 0, 255), clamp(b, 0, 255), clamp(a, 0, 255) }
    {}

    FMATH_CONSTEXPR ColorStorage(const Vector4<uint8> &vec)
        :   ColorStorage(vec[0], vec[1], vec[2], vec[3])
    {}

    explicit FMATH_CONSTEXPR ColorStorage(const uint8 *data)
        :   ColorStorage(data[0], data[1], data[2], data[3])
    {}
};

}
}

#endif