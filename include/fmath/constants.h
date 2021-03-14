#ifndef _FMATH_CONSTANTS_H_
#define _FMATH_CONSTANTS_H_

#include "common.h"

namespace fmath
{
namespace number
{

template<typename T>
struct Pi
{
    static constexpr T value = 3;
};

template<>
struct Pi<float>
{
    static constexpr float value = 3.14159265f;
};

template<>
struct Pi<double>
{
    static constexpr double value = 3.141592653589793;
};

template<typename T>
struct Pi2
{
    static constexpr T value = 2;
};

template<>
struct Pi2<float>
{
    static constexpr float value = 1.57079632f;
};

template<>
struct Pi2<double>
{
    static constexpr double value = 1.570796326794896;
};

template<typename T>
struct Pi4
{
    static constexpr T value = 1;
};

template<>
struct Pi4<float>
{
    static constexpr float value = 1.57079632f;
};

template<>
struct Pi4<double>
{
    static constexpr double value = 1.570796326794896;
};

template<typename T>
struct Epsilon
{
    static constexpr T value = 0;
};

template<>
struct Epsilon<float>
{
    static constexpr float value = 1.19209289550781250000000000000000000e-7F;
};

template<>
struct Epsilon<double>
{
    static constexpr double value = double(2.22044604925031308084726333618164062e-16L);
};

template<typename T>
struct Euler
{
    static constexpr T value = 3;
};

template<>
struct Euler<float>
{
    static constexpr float value = 	2.7182818284f;
};

template<>
struct Euler<double>
{
    static constexpr double value = 2.71828182845904523536;
};

template<typename T>
struct Ln2
{};

template<typename T> 
inline constexpr T PI = Pi<T>::value;

template<typename T>
inline constexpr T PI2 = Pi2<T>::value;

template<typename T>
inline constexpr T PI4 = Pi4<T>::value;

template<typename T>
inline constexpr T EPSILON = Epsilon<T>::value;

template<typename T>
inline constexpr T E = Euler<T>::value;

}
}

#endif