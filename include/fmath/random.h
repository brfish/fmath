#ifndef _FMATH_RANDOM_H_
#define _FMATH_RANDOM_H_

#include <ctime>
#include <random>

#include "common.h"
#include "normal.h"
#include "point.h"
#include "traits.h"
#include "vector.h"

namespace fmath
{
namespace internal
{

static std::mt19937 global_random_engine { static_cast<std::mt19937::result_type>(time(NULL)) };
static std::mt19937_64 global_random_engine64 { static_cast<std::mt19937_64::result_type>(time(NULL)) };

template<typename T, typename R, typename = void>
struct RandomTraits
{};

template<typename T, typename R>
struct RandomTraits<T, R, std::enable_if_t<std::is_integral_v<T>>>
{
    static FMATH_INLINE T uniform(const T &minv, const T &maxv, R &engine)
    {
        using DistributionType = std::uniform_int_distribution<
            std::conditional_t<(sizeof(T) > 1), T,
                std::conditional_t<std::is_signed_v<T>, int32, uint32>
        >>;
        using ParamType = typename DistributionType::param_type;

        static DistributionType d { };
        return d(engine, ParamType(minv, maxv));
    }
};

template<typename T, typename R>
struct RandomTraits<T, R, std::enable_if_t<std::is_floating_point_v<T>>>
{
    static FMATH_INLINE T uniform(const T &minv, const T &maxv, R &engine)
    {
        using DistributionType = std::uniform_real_distribution<T>;
        using ParamType = typename DistributionType::param_type;

        static DistributionType d { };

        std::pair<const T &, const T &> range = minmax(minv, maxv);
        return d(engine, ParamType(range.first, range.second));
    }
};

template<typename T, typename R>
struct RandomTraits<T, R, std::enable_if_t<is_vector_v<T>>>
{
    static FMATH_INLINE T uniform(const T &minv, const T &maxv, R &engine)
    {
        T result { };
        for (index_t i = 0; i < T::DIMENSION; ++i)
        {
            std::pair<const T &, const T &> range = minmax(minv[i], maxv[i]);
            result[i] = RandomTraits<typename T::ValueType, R>::uniform(range.first, range.second, engine);
        }
        return result;
    }
};

}

template<typename T, typename R>
static FMATH_INLINE T random(const T &minv, const T &maxv, R &engine)
{
    return internal::RandomTraits<T, R>::uniform(minv, maxv, engine);
}

template<typename T>
static FMATH_INLINE T random(const T &minv, const T &maxv)
{
    using EngineType = std::conditional_t<is_integral_v<T> && ValueTypeSize<T>::value >= 4, std::mt19937_64, std::mt19937>;
    static thread_local EngineType engine;
    return random(minv, maxv, engine);
}

}

#endif