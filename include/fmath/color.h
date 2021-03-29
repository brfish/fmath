#ifndef _FMATH_COLOR_H_
#define _FMATH_COLOR_H_

#include "internal/color_base.h"
#include "internal/vector_traits.h"
#include "common.h"

namespace fmath
{

template<typename T, size_t N>
class Color : public internal::ColorBase<T, N>
{
public:
    using ValueType = T;
    static constexpr size_t SIZE = N;

public:
    using internal::ColorBase<T, N>::ColorBase;

    FMATH_INLINE Color &operator+=(const Color &other);

    FMATH_INLINE Color &operator-=(const Color &other);

    FMATH_INLINE Color &operator*=(const Color &other);

    FMATH_INLINE Color &operator*=(const ValueType &value);

    FMATH_INLINE Color &operator/=(const Color &other);

    FMATH_INLINE Color &operator/=(const ValueType &value);
};

namespace internal
{

template<typename T>
struct ColorRangeTraits
{};

template<>
struct ColorRangeTraits<float>
{
    static constexpr float RANGE_MIN = 0.0F;
    static constexpr float RANGE_MAX = 1.0F;
};

template<>
struct ColorRangeTraits<uint8>
{
    static constexpr uint8 RANGE_MIN = 0;
    static constexpr uint8 RANGE_MAX = 255;
};

template<typename T, size_t N>
struct VectorTraits_TypeInfo<Color<T, N>>
{
    template<typename U, size_t M>
    using VectorType = Color<U, M>;

    using ValueType = T;

    static constexpr size_t SIZE = N;
};

};

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool operator==(const Color<T, N> &c1, const Color<T, N> &c2)
{
    return c1.values == c2.values;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool operator!=(const Color<T, N> &c1, const Color<T, N> &c2)
{
    return c1.values != c2.values;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool equal(const Color<T, N> &c1, const Color<T, N> &c2)
{
    return c1 == c2;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool notEqual(const Color<T, N> &c1, const Color<T, N> &c2)
{
    return c1 != c2;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool equalEpsilon(const Color<T, N> &c1, const Color<T, N> &c2, const T &epsilon = constants::Epsilon<T>::value)
{
    return equalEpsilon(c1.values, c2.values, epsilon);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool notEqualEpsilon(const Color<T, N> &c1, const Color<T, N> &c2, const T &epsilon = constants::Epsilon<T>::value)
{
    return !equalEpsilon(c1, c2, epsilon);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Color<T, N> operator+(const Color<T, N> &c1, const Color<T, N> &c2)
{
    return Color<T, N>(clamp(c1.values + c2.values, internal::ColorRangeTraits<T>::RANGE_MIN, 
        internal::ColorRangeTraits<T>::RANGE_MAX));
};

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Color<T, N> operator-(const Color<T, N> &c1, const Color<T, N> &c2)
{
    return Color<T, N>(clamp(c1.values - c2.values, internal::ColorRangeTraits<T>::RANGE_MIN, 
        internal::ColorRangeTraits<T>::RANGE_MAX));
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Color<T, N> operator*(const Color<T, N> &c1, const Color<T, N> &c2)
{
    return Color<T, N>(hadamardMul(c1.values, c2.values) / internal::ColorRangeTraits<T>::RANGE_MAX);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Color<T, N> operator*(const Color<T, N> &c, const T &value)
{
    return Color<T, N>(c.values * value);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Color<T, N> operator*(const T &value, const Color<T, N> &c)
{
    return Color<T, N>(c.values * value);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Color<T, N> operator/(const Color<T, N> &c1, const Color<T, N> &c2)
{
    return Color<T, N>(hadamardDiv(c1.values, c2.values) * internal::ColorRangeTraits<T>::RANGE_MAX);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Color<T, N> operator/(const Color<T, N> &c, const T &value)
{
    return Color<T, N>(clamp(c.values / value, internal::ColorRangeTraits<T>::RANGE_MIN,
        internal::ColorRangeTraits<T>::RANGE_MAX));
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR std::ostream &operator<<(std::ostream &output, const Color<T, N> &c)
{
    output << c.values;
    return output;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR std::istream &operator>>(std::istream &input, Color<T, N> &c)
{
    input >> c.values;
    return input;
}

template<typename T, size_t N>
FMATH_INLINE Color<T, N> &Color<T, N>::operator+=(const Color &other)
{
    *this = (*this) + other;
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE Color<T, N> &Color<T, N>::operator-=(const Color &other)
{
    *this = (*this) - other;
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE Color<T, N> &Color<T, N>::operator*=(const Color &other)
{
    *this = (*this) * other;
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE Color<T, N> &Color<T, N>::operator*=(const ValueType &value)
{
    *this = (*this) * value;
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE Color<T, N> &Color<T, N>::operator/=(const Color &other)
{
    *this = (*this) / other;
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE Color<T, N> &Color<T, N>::operator/=(const ValueType &value)
{
    *this = (*this) / value;
    return *this;
}

using Rgb = Color<float, 3>;
using Rgbi = Color<uint8, 3>;

using Rgba = Color<float, 4>;
using Rgbai = Color<uint8, 4>;

}

#endif