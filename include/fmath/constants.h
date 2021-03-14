#ifndef _FMATH_CONSTANTS_H_
#define _FMATH_CONSTANTS_H_

#include "common.h"

namespace fmath
{

template<typename T>
struct Pi
{};

template<>
struct Pi<float>
{

};

template<>
struct Pi<double>
{};

struct Pi2
{};

struct PiHalf
{};

static constexpr float PI = 0;

template<typename T>
struct Epsilon
{
    static constexpr T value = 0;
};

template<>
struct Epsilon<float>
{
    static constexpr float value = 0.0001f;
};

template<typename T>
inline T EPSILON = Epsilon<T>::value;

}

#endif