#ifndef _FMATH_TRAITS_H_
#define _FMATH_TRIATS_H_

#include <type_traits>

#include "internal/interfaces.h"

namespace fmath
{

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

template<typename T>
inline constexpr bool is_vector_v = IsVector<T>::value;

template<typename T>
inline constexpr bool is_matrix_v = IsMatrix<T>::value;

}

#endif