#ifndef _FMATH_CONSTANTS_H_
#define _FMATH_CONSTANTS_H_

#include <limits>
#include <type_traits>

#include "common.h"

namespace fmath
{
namespace constants
{

template<typename T>
struct Inf
{
    static_assert(std::is_floating_point_v<T>);
    static constexpr T value = std::numeric_limits<T>::infinity();
};

template<typename T>
struct MinValue
{
    static constexpr T value = std::numeric_limits<T>::lowest();
};

template<typename T>
struct MaxValue
{
    static constexpr T value = std::numeric_limits<T>::max();
};

template<typename T>
struct Pi
{};

template<>
struct Pi<double>
{
    static constexpr double value = 3.141592653589793;
};

template<>
struct Pi<float>
{
    static constexpr float value = static_cast<float>(Pi<double>::value);
};

template<typename T>
struct Pi2
{};

template<>
struct Pi2<double>
{
    static constexpr double value = 1.570796326794896;
};

template<>
struct Pi2<float>
{
    static constexpr float value = static_cast<float>(Pi2<double>::value);
};

template<typename T>
struct Pi4
{};

template<>
struct Pi4<double>
{
    static constexpr double value = 0.785398163397448;    
};

template<>
struct Pi4<float>
{
    static constexpr float value = static_cast<float>(Pi4<double>::value);
};

template<typename T>
struct ConstantE
{};

template<>
struct ConstantE<double>
{
    static constexpr double value = 2.718281828459045;
};

template<>
struct ConstantE<float>
{
    static constexpr float value = static_cast<float>(ConstantE<double>::value);
};

template<typename T>
struct Ln2
{};

template<>
struct Ln2<double>
{
    static constexpr double value = 0.6931471805599453;
};

template<>
struct Ln2<float>
{
    static constexpr float value = static_cast<float>(Ln2<double>::value);
};

template<typename T>
struct Ln10
{};

template<>
struct Ln10<double>
{
    static constexpr double value = 2.302585092994046;
};

template<>
struct Ln10<float>
{
    static constexpr float value = static_cast<float>(Ln10<double>::value);
};

template<typename T>
struct Sqrt2
{};

template<>
struct Sqrt2<double>
{
    static constexpr double value = 1.4142135623730951;
};

template<>
struct Sqrt2<float>
{
    static constexpr float value = static_cast<float>(Sqrt2<double>::value);
};

template<typename T>
struct Sqrt3
{};

template<>
struct Sqrt3<double>
{
    static constexpr double value = 1.7320508075688772;
};

template<>
struct Sqrt3<float>
{
    static constexpr float value = static_cast<float>(Sqrt3<double>::value);
};

template<typename T>
struct Epsilon
{
    static constexpr T value = std::numeric_limits<T>::epsilon();
};

template<typename T>
inline constexpr T INF = Inf<T>::value;

template<typename T>
inline constexpr T MIN_VALUE = MinValue<T>::value;

template<typename T>
inline constexpr T MAX_VALUE = MaxValue<T>::value;

inline constexpr double PI = Pi<double>::value;

inline constexpr double PI2 = Pi2<double>::value;

inline constexpr double PI4 = Pi4<double>::value;

inline constexpr double E = ConstantE<double>::value;

inline constexpr double LN2 = Ln2<double>::value;

inline constexpr double LN10 = Ln10<double>::value;

inline constexpr double SQRT2 = Sqrt2<double>::value;

inline constexpr double SQRT3 = Sqrt3<double>::value;

inline constexpr double EPSILON = Epsilon<double>::value;

}
}

#endif