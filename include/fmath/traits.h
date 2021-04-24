#ifndef _FMATH_TRAITS_H_
#define _FMATH_TRAITS_H_

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
struct IsIEC559
{
    static constexpr bool value = std::numeric_limits<T>::is_iec559;
};

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

template<typename T, typename = void>
struct ValueTypeSize
{
    static constexpr size_t value = sizeof(T);
};

template<typename T>
struct ValueTypeSize<T, std::enable_if_t<internal::HasValueType<T>::value>>
{
    static constexpr size_t value = sizeof(typename T::ValueType);
};

template<typename T>
inline constexpr bool is_iec559_v = IsIEC559<T>::value;

template<typename T>
inline constexpr bool is_vector_v = IsVector<T>::value;

template<typename T>
inline constexpr bool is_matrix_v = IsMatrix<T>::value;

template<typename T>
inline constexpr bool is_floating_point_v = IsFloatingPoint<T>::value;

template<typename T>
inline constexpr bool is_integral_v = IsIntegral<T>::value;

template<typename T>
inline constexpr size_t value_type_size_v = ValueTypeSize<T>::value;

}

#endif