#ifndef _FMATH_INTERNAL_COLOR_STORAGE_H_
#define _FMATH_INTERNAL_COLOR_STORAGE_H_

#include <array>

#include "common.h"
#include "functions.h"

namespace fmath
{

enum class ColorFormat
{
    BIT,
    GREY,
    GREY16,
    RGB,
    RGB_I,
    RGBA,
    RGBA_I
};

namespace internal
{

template<typename T, size_t N>
struct ColorStorageBase
{};

template<ColorFormat Format>
struct ColorStorage
{};

template<>
struct ColorStorage<ColorFormat::BIT> : ColorStorageBase<bool, 1>
{
    union
    {
        std::array<bool, 1> values;
        bool v;
    };

    explicit FMATH_CONSTEXPR ColorStorage(const bool &v)
        :   values { v }
    {}
};

template<>
struct ColorStorage<ColorFormat::GREY> : ColorStorageBase<uint8, 1>
{
    union
    {
        std::array<uint8, 1> values;
        uint8 v;
    };

    explicit FMATH_CONSTEXPR ColorStorage(const uint8 &v)
        :   values { v }
    {}
};

template<>
struct ColorStorage<ColorFormat::GREY16> : ColorStorageBase<uint16, 1>
{
    union
    {
        std::array<uint16, 1> values;
        uint16 v;
    };

    explicit FMATH_CONSTEXPR ColorStorage(const uint16 &v)
        :   values { v }
    {}
};

template<>
struct ColorStorage<ColorFormat::RGB> : ColorStorageBase<float, 3>
{
    union
    {
        std::array<float, 3> values;
        struct { float r, g, b; };
    };

    explicit FMATH_CONSTEXPR ColorStorage(const float &r, const float &g, const float &b)
        :   values { clamp(r, 0.0F, 1.0F), clamp(g, 0.0F, 1.0F), clamp(b, 0.0F, 1.0F) }
    {}
};

template<>
struct ColorStorage<ColorFormat::RGB_I> : ColorStorageBase<uint8, 3>
{
    union
    {
        std::array<uint8, 3> values;
        struct { uint8 r, g, b; };
    };

    explicit FMATH_CONSTEXPR ColorStorage(const uint8 &r, const uint8 &g, const uint8 &b)
        :   values { r, g, b }
    {}
};

template<>
struct ColorStorage<ColorFormat::RGBA> : ColorStorageBase<float, 4>
{
    union
    {
        std::array<float, 4> values;
        struct { float r, g, b, a; };
    };

    explicit FMATH_CONSTEXPR ColorStorage(const float &r, const float &g, const float &b, const float &a)
        :   values { clamp(r, 0.0F, 1.0F), clamp(g, 0.0F, 1.0F), clamp(b, 0.0F, 1.0F), clamp(a, 0.0F, 1.0F) }
    {}
};

template<>
struct ColorStorage<ColorFormat::RGBA_I> : ColorStorageBase<uint8, 4>
{
    union
    {
        std::array<uint8, 4> values;
        struct { uint8 r, g, b, a; };
    };

    explicit FMATH_CONSTEXPR ColorStorage(const uint8 &r, const uint8 &g, const uint8 &b, const uint8 &a)
        :   values { r, g, b, a }
    {}
};

}
}

#endif