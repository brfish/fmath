#ifndef _FMATH_TRAITS_H_
#define _FMATH_TRIATS_H_

#include <type_traits>

#include "internal/interfaces.h"

namespace fmath
{

namespace internal
{

template<typename T, typename = void>
struct HasValueType : std::false_type
{};

template<typename T>
struct HasValueType<T, std::void_t<typename T::ValueType>> : std::true_type
{};

}

template<typename T>
struct IsVector : std::conditional_t<
    std::is_base_of_v<internal::VectorInterface, T>, 
        std::true_type, 
        std::false_type>
{};

template<typename T>
struct IsMatrix : std::conditional_t<
    std::is_base_of_v<internal::MatrixInterface, T>, 
        std::true_type, 
        std::false_type>
{};

template<typename T, typename = void>
struct IsFloatingPoint : std::is_floating_point<T>
{};

template<typename T>
struct IsFloatingPoint<T, std::enable_if_t<internal::HasValueType<T>::value>> :
    std::is_floating_point<typename T::ValueType>
{};

template<typename T, typename = void>
struct IsIntegral : std::is_integral<T>
{};

template<typename T>
struct IsIntegral<T, std::enable_if_t<internal::HasValueType<T>::value>> :
    std::is_integral<typename T::ValueType>
{};

template<typename T>
inline constexpr bool is_vector_v = IsVector<T>::value;

template<typename T>
inline constexpr bool is_matrix_v = IsMatrix<T>::value;

template<typename T>
inline constexpr bool is_floating_point_v = IsFloatingPoint<T>::value;

template<typename T>
inline constexpr bool is_integral_v = IsIntegral<T>::value;

}

#endif