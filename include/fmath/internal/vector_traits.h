#ifndef _FMATH_INTERNAL_VECTOR_TRAITS_H_
#define _FMATH_INTERNAL_VECTOR_TRAITS_H_

#include <iomanip>
#include <istream>
#include <ostream>
#include <sstream>
#include <string>

#include "internal/vector_base.h"
#include "functions.h"

namespace fmath::internal
{

template<typename VectorT>
struct VectorTraits_TypeInfo
{};

#pragma region VectorTraits_Compare
template<typename T, size_t N>
struct VectorTraits_Compare
{
    using Base = VectorBase<T, N>;
    static FMATH_INLINE FMATH_CONSTEXPR bool equal(const Base &v1, const Base &v2);
    static FMATH_INLINE FMATH_CONSTEXPR bool equalEpsilon(const Base &v1, const Base &v2, const T &epsilon);
    static FMATH_INLINE FMATH_CONSTEXPR T minComponent(const Base &v);
    static FMATH_INLINE FMATH_CONSTEXPR T maxComponent(const Base &v);
};

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool VectorTraits_Compare<T, N>::equal(const Base &v1, const Base &v2)
{
    if (&v1 == &v2)
        return true;
    
    for (index_t i = 0; i < N; ++i)
    {
        if (v1[i] != v2[i])
            return false;
    }
    return true;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool VectorTraits_Compare<T, N>::equalEpsilon(const Base &v1, const Base &v2, const T &epsilon)
{
    if (&v1 == &v2)
        return true;

    for (index_t i = 0; i < N; ++i)
    {
        if (!fmath::equalEpsilon(v1[i], v2[i], epsilon))
            return false;
    }
    return true;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T VectorTraits_Compare<T, N>::minComponent(const Base &v)
{
    T result = v[0];
    for (index_t i = 1; i < N; ++i)
        result = min(result, v[i]);
    return result;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T VectorTraits_Compare<T, N>::maxComponent(const Base &v)
{
    T result = v[0];
    for (index_t i = 1; i < N; ++i)
        result = max(result, v[i]);
    return result;
}

template<typename T>
struct VectorTraits_Compare<T, 2>
{
    using Base = VectorBase<T, 2>;
    static FMATH_INLINE FMATH_CONSTEXPR bool equal(const Base &v1, const Base &v2);
    static FMATH_INLINE FMATH_CONSTEXPR bool equalEpsilon(const Base &v1, const Base &v2, const T &epsilon);
    static FMATH_INLINE FMATH_CONSTEXPR T minComponent(const Base &v);
    static FMATH_INLINE FMATH_CONSTEXPR T maxComponent(const Base &v);
};

template<typename T>
bool FMATH_INLINE FMATH_CONSTEXPR VectorTraits_Compare<T, 2>::equal(const Base &v1, const Base &v2)
{
    return v1[0] == v2[0] && v1[1] == v2[1];
}

template<typename T>
bool FMATH_INLINE FMATH_CONSTEXPR VectorTraits_Compare<T, 2>::equalEpsilon(const Base &v1, const Base &v2, const T &epsilon)
{
    if (&v1 == &v2)
        return true;

    return fmath::equalEpsilon(v1[0], v2[0], epsilon) && 
        fmath::equalEpsilon(v1[1], v2[1], epsilon);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T VectorTraits_Compare<T, 2>::minComponent(const Base &v)
{
    return min(v[0], v[1]);    
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T VectorTraits_Compare<T, 2>::maxComponent(const Base &v)
{
    return max(v[0], v[1]);
}

template<typename T>
struct VectorTraits_Compare<T, 3>
{
    using Base = VectorBase<T, 3>;
    static FMATH_INLINE FMATH_CONSTEXPR bool equal(const Base &v1, const Base &v2);
    static FMATH_INLINE FMATH_CONSTEXPR bool equalEpsilon(const Base &v1, const Base &v2, const T &epsilon);
    static FMATH_INLINE FMATH_CONSTEXPR T minComponent(const Base &v);
    static FMATH_INLINE FMATH_CONSTEXPR T maxComponent(const Base &v);
};

template<typename T>
bool FMATH_INLINE FMATH_CONSTEXPR VectorTraits_Compare<T, 3>::equal(const Base &v1, const Base &v2)
{
    return v1[0] == v2[0] && v1[1] == v2[1] && v1[2] == v2[2];
}

template<typename T>
bool FMATH_INLINE FMATH_CONSTEXPR VectorTraits_Compare<T, 3>::equalEpsilon(const Base &v1, const Base &v2, const T &epsilon)
{
    if (&v1 == &v2)
        return true;

    return fmath::equalEpsilon(v1[0], v2[0], epsilon) && 
        fmath::equalEpsilon(v1[1], v2[1], epsilon) && 
        fmath::equalEpsilon(v1[2], v2[2], epsilon);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T VectorTraits_Compare<T, 3>::minComponent(const Base &v)
{
    return min(min(v[0], v[1]), v[2]);    
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T VectorTraits_Compare<T, 3>::maxComponent(const Base &v)
{
    return max(max(v[0], v[1]), v[2]);
}

template<typename T>
struct VectorTraits_Compare<T, 4>
{
    using Base = VectorBase<T, 4>;
    static FMATH_INLINE FMATH_CONSTEXPR bool equal(const Base &v1, const Base &v2);
    static FMATH_INLINE FMATH_CONSTEXPR bool equalEpsilon(const Base &v1, const Base &v2, const T &epsilon);
    static FMATH_INLINE FMATH_CONSTEXPR T minComponent(const Base &v);
    static FMATH_INLINE FMATH_CONSTEXPR T maxComponent(const Base &v);
};

template<typename T>
bool FMATH_INLINE FMATH_CONSTEXPR VectorTraits_Compare<T, 4>::equal(const Base &v1, const Base &v2)
{
    return v1[0] == v2[0] && v1[1] == v2[1] && v1[2] == v2[2] && v1[3] == v2[3];
}

template<typename T>
bool FMATH_INLINE FMATH_CONSTEXPR VectorTraits_Compare<T, 4>::equalEpsilon(const Base &v1, const Base &v2, const T &epsilon)
{
    if (&v1 == &v2)
        return true;

    return fmath::equalEpsilon(v1[0], v2[0], epsilon) && 
        fmath::equalEpsilon(v1[1], v2[1], epsilon) && 
        fmath::equalEpsilon(v1[2], v2[2], epsilon) && 
        fmath::equalEpsilon(v1[3], v2[3], epsilon);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T VectorTraits_Compare<T, 4>::minComponent(const Base &v)
{
    return min(min(min(v[0], v[1]), v[2]), v[3]);    
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T VectorTraits_Compare<T, 4>::maxComponent(const Base &v)
{
    return max(max(max(v[0], v[1]), v[2]), v[3]);    
}
#pragma endregion

#pragma region VectorTraits_Add
template<typename T, size_t N, typename VectorT>
struct VectorTraits_Add
{
    using Base = VectorBase<T, N>;
    static FMATH_INLINE FMATH_CONSTEXPR VectorT add(const Base &v1, const Base &v2);
    static FMATH_INLINE FMATH_CONSTEXPR VectorT add(const Base &v, const T &value);
    static FMATH_INLINE FMATH_CONSTEXPR VectorT sub(const Base &v1, const Base &v2);
    static FMATH_INLINE FMATH_CONSTEXPR VectorT sub(const Base &v, const T &value);
};

template<typename T, size_t N, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Add<T, N, VectorT>::add(const Base &v1, const Base &v2)
{
    VectorT result;
    for (index_t i = 0; i < N; ++i)
        result[i] = v1[i] + v2[i];
    return result;
}

template<typename T, size_t N, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Add<T, N, VectorT>::add(const Base &v, const T &value)
{
    VectorT result;
    for (index_t i = 0; i < N; ++i)
        result[i] = v[i] + value;
    return result;
}

template<typename T, size_t N, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Add<T, N, VectorT>::sub(const Base &v1, const Base &v2)
{
    VectorT result;
    for (index_t i = 0; i < N; ++i)
        result[i] = v1[i] - v2[i];
    return result;
}

template<typename T, size_t N, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Add<T, N, VectorT>::sub(const Base &v, const T &value)
{
    VectorT result;
    for (index_t i = 0; i < N; ++i)
        result[i] = v[i] - value;
    return result;
}

template<typename T, typename VectorT>
struct VectorTraits_Add<T, 2, VectorT>
{
    using Base = VectorBase<T, 2>;
    FMATH_INLINE FMATH_CONSTEXPR static VectorT add(const Base &v1, const Base &v2);
    FMATH_INLINE FMATH_CONSTEXPR static VectorT add(const Base &v, const T &value);
    FMATH_INLINE FMATH_CONSTEXPR static VectorT sub(const Base &v1, const Base &v2);
    FMATH_INLINE FMATH_CONSTEXPR static VectorT sub(const Base &v, const T &value);
};

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Add<T, 2, VectorT>::add(const Base &v1, const Base &v2)
{
    return VectorT(v1[0] + v2[0], v1. y + v2[1]);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Add<T, 2, VectorT>::add(const Base &v, const T &value)
{
    return VectorT(v[0] + value, v[1] + value);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Add<T, 2, VectorT>::sub(const Base &v1, const Base &v2)
{
    return VectorT(v1[0] - v2[0], v1[1] - v2[1]);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Add<T, 2, VectorT>::sub(const Base &v, const T &value)
{
    return VectorT(v[0] - value, v[1] - value);
}

template<typename T, typename VectorT>
struct VectorTraits_Add<T, 3, VectorT>
{
    using Base = VectorBase<T, 3>;
    FMATH_INLINE FMATH_CONSTEXPR static VectorT add(const Base &v1, const Base &v2);
    FMATH_INLINE FMATH_CONSTEXPR static VectorT add(const Base &v, const T &value);
    FMATH_INLINE FMATH_CONSTEXPR static VectorT sub(const Base &v1, const Base &v2);
    FMATH_INLINE FMATH_CONSTEXPR static VectorT sub(const Base &v, const T &value);
};

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Add<T, 3, VectorT>::add(const Base &v1, const Base &v2)
{
    return VectorT(v1[0] + v2[0], v1. y + v2[1], v1[2] + v2[2]);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Add<T, 3, VectorT>::add(const Base &v, const T &value)
{
    return VectorT(v[0] + value, v[1] + value, v[2] + value);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Add<T, 3, VectorT>::sub(const Base &v1, const Base &v2)
{
    return VectorT(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Add<T, 3, VectorT>::sub(const Base &v, const T &value)
{
    return VectorT(v[0] - value, v[1] - value, v[2] - value);
}

template<typename T, typename VectorT>
struct VectorTraits_Add<T, 4, VectorT>
{
    using Base = VectorBase<T, 4>;
    FMATH_INLINE FMATH_CONSTEXPR static VectorT add(const Base &v1, const Base &v2);
    FMATH_INLINE FMATH_CONSTEXPR static VectorT add(const Base &v, const T &value);
    FMATH_INLINE FMATH_CONSTEXPR static VectorT sub(const Base &v1, const Base &v2);
    FMATH_INLINE FMATH_CONSTEXPR static VectorT sub(const Base &v, const T &value);
};

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Add<T, 4, VectorT>::add(const Base &v1, const Base &v2)
{
    return VectorT(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2], v1[3] + v2[3]);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Add<T, 4, VectorT>::add(const Base &v, const T &value)
{
    return VectorT(v[0] + value, v[1] + value, v[2] + value, v[3] + value);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Add<T, 4, VectorT>::sub(const Base &v1, const Base &v2)
{
    return VectorT(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2], v1[3] - v2[3]);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Add<T, 4, VectorT>::sub(const Base &v, const T &value)
{
    return VectorT(v[0] - value, v[1] - value, v[2] - value, v[3] - value);
}
#pragma endregion

#pragma region VectorTraits_Dot
template<typename T, size_t N>
struct VectorTraits_Dot
{
    using Base = VectorBase<T, N>;
    FMATH_INLINE FMATH_CONSTEXPR static T dot(const Base &v1, const Base &v2);
};

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T VectorTraits_Dot<T, N>::dot(const Base &v1, const Base &v2)
{
    T result = 0;
    for (index_t i = 0; i < N; ++i)
        result += v1[i] * v2[i];
    return result;
}

template<typename T>
struct VectorTraits_Dot<T, 2>
{
    using Base = VectorBase<T, 2>;
    FMATH_INLINE FMATH_CONSTEXPR static T dot(const Base &v1, const Base &v2);
};

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T VectorTraits_Dot<T, 2>::dot(const Base &v1, const Base &v2)
{
    return v1[0] * v2[0] + v1[1] * v2[1];
}

template<typename T>
struct VectorTraits_Dot<T, 3>
{
    using Base = VectorBase<T, 3>;
    FMATH_INLINE FMATH_CONSTEXPR static T dot(const Base &v1, const Base &v2);
};

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T VectorTraits_Dot<T, 3>::dot(const Base &v1, const Base &v2)
{
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

template<typename T>
struct VectorTraits_Dot<T, 4>
{
    using Base = VectorBase<T, 4>;
    FMATH_INLINE FMATH_CONSTEXPR static T dot(const Base &v1, const Base &v2);
};

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T VectorTraits_Dot<T, 4>::dot(const Base &v1, const Base &v2)
{
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3] * v2[3];
}
#pragma endregion

#pragma region VectorTraits_Scale
template<typename T, size_t N, typename VectorT>
struct VectorTraits_Scale
{
    using Base = VectorBase<T, N>;
    FMATH_INLINE static VectorT mul(const Base &v, const T &value);
    FMATH_INLINE static VectorT div(const Base &v, const T &value);
};

template<typename T, size_t N, typename VectorT>
FMATH_INLINE VectorT VectorTraits_Scale<T, N, VectorT>::mul(const Base &v, const T &value)
{
    VectorT result;
    for (index_t i = 0; i < N; ++i)
        result[i] = v[i] * value;
    return result;
}

template<typename T, size_t N, typename VectorT>
FMATH_INLINE VectorT VectorTraits_Scale<T, N, VectorT>::div(const Base &v, const T &value)
{
    FMATH_ASSERT(value != 0);
    VectorT result;
    for (index_t i = 0; i < N; ++i)
        result[i] = v[i] / value;
    return result;
}

template<typename T, typename VectorT>
struct VectorTraits_Scale<T, 2, VectorT>
{
    using Base = VectorBase<T, 2>;
    FMATH_INLINE FMATH_CONSTEXPR static VectorT mul(const Base &v, const T &value);
    FMATH_INLINE FMATH_CONSTEXPR static VectorT div(const Base &v, const T &value);
};

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Scale<T, 2, VectorT>::mul(const Base &v, const T &value)
{
    return VectorT(v[0] * value, v[1] * value);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Scale<T, 2, VectorT>::div(const Base &v, const T &value)
{
    FMATH_ASSERT(value != 0);
    return VectorT(v[0] / value, v[1] / value);
}

template<typename T, typename VectorT>
struct VectorTraits_Scale<T, 3, VectorT>
{
    using Base = VectorBase<T, 3>;
    FMATH_INLINE FMATH_CONSTEXPR static VectorT mul(const Base &v, const T &value);
    FMATH_INLINE FMATH_CONSTEXPR static VectorT div(const Base &v, const T &value);
};

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Scale<T, 3, VectorT>::mul(const Base &v, const T &value)
{
    return VectorT(v[0] * value, v[1] * value, v[2] * value);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Scale<T, 3, VectorT>::div(const Base &v, const T &value)
{
    FMATH_ASSERT(value != 0);
    return VectorT(v[0] / value, v[1] / value, v[2] / value);
}

template<typename T, typename VectorT>
struct VectorTraits_Scale<T, 4, VectorT>
{
    using Base = VectorBase<T, 4>;
    FMATH_INLINE FMATH_CONSTEXPR static VectorT mul(const Base &v, const T &value);
    FMATH_INLINE FMATH_CONSTEXPR static VectorT div(const Base &v, const T &value);
};

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Scale<T, 4, VectorT>::mul(const Base &v, const T &value)
{
    return VectorT(v[0] * value, v[1] * value, v[2] * value, v[3] * value);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Scale<T, 4, VectorT>::div(const Base &v, const T &value)
{
    FMATH_ASSERT(value != 0);
    return VectorT(v[0] / value, v[1] / value, v[2] / value, v[3] / value);
}
#pragma endregion

#pragma region VectorTraits_Hadamard
template<typename T, size_t N, typename VectorT>
struct VectorTraits_Hadamard
{
    using Base = VectorBase<T, N>;
    FMATH_INLINE FMATH_CONSTEXPR static VectorT hadamardMul(const Base &v1, const Base &v2);
    FMATH_INLINE FMATH_CONSTEXPR static VectorT hadamardDiv(const Base &v1, const Base &v2);
};

template<typename T, size_t N, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Hadamard<T, N, VectorT>::hadamardMul(const Base &v1, const Base &v2)
{
    VectorT result;
    for (index_t i = 0; i < N; ++i)
        result[i] = v1[i] * v2[i];
    return result;
}

template<typename T, size_t N, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Hadamard<T, N, VectorT>::hadamardDiv(const Base &v1, const Base &v2)
{
    VectorT result;
    for (index_t i = 0; i < N; ++i)
    {
        FMATH_ASSERT(v2[i] != 0);
        result[i] = v1[i] / v2[i];
    }   
    return result;
}

template<typename T, typename VectorT>
struct VectorTraits_Hadamard<T, 2, VectorT>
{
    using Base = VectorBase<T, 2>;
    FMATH_INLINE FMATH_CONSTEXPR static VectorT hadamardMul(const Base &v1, const Base &v2);
    FMATH_INLINE FMATH_CONSTEXPR static VectorT hadamardDiv(const Base &v1, const Base &v2);
};

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Hadamard<T, 2, VectorT>::hadamardMul(const Base &v1, const Base &v2)
{
    return VectorT(v1[0] * v2[0], v1[1] * v2[1]);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Hadamard<T, 2, VectorT>::hadamardDiv(const Base &v1, const Base &v2)
{
    FMATH_ASSERT(v2[0] !=0 && v2[1] != 0);
    return VectorT(v1[0] / v2[0], v1[1] / v2[1]);
}

template<typename T, typename VectorT>
struct VectorTraits_Hadamard<T, 3, VectorT>
{
    using Base = VectorBase<T, 3>;
    FMATH_INLINE FMATH_CONSTEXPR static VectorT hadamardMul(const Base &v1, const Base &v2);
    FMATH_INLINE FMATH_CONSTEXPR static VectorT hadamardDiv(const Base &v1, const Base &v2);
};

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Hadamard<T, 3, VectorT>::hadamardMul(const Base &v1, const Base &v2)
{
    return VectorT(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Hadamard<T, 3, VectorT>::hadamardDiv(const Base &v1, const Base &v2)
{
    FMATH_ASSERT(v2[0] !=0 && v2[1] != 0 && v2[2] != 0);
    return VectorT(v1[0] / v2[0], v1[1] / v2[1], v1[2] / v2[2]);
}

template<typename T, typename VectorT>
struct VectorTraits_Hadamard<T, 4, VectorT>
{
    using Base = VectorBase<T, 4>;
    FMATH_INLINE FMATH_CONSTEXPR static VectorT hadamardMul(const Base &v1, const Base &v2);
    FMATH_INLINE FMATH_CONSTEXPR static VectorT hadamardDiv(const Base &v1, const Base &v2);
};

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Hadamard<T, 4, VectorT>::hadamardMul(const Base &v1, const Base &v2)
{
    return VectorT(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2], v1[3] * v2[3]);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Hadamard<T, 4, VectorT>::hadamardDiv(const Base &v1, const Base &v2)
{
    FMATH_ASSERT(v2[0] != 0 && v2[1] != 0 && v2[2] !=0 && v2[3] != 0);
    return VectorT(v1[0] / v2[0], v1[1] / v2[1], v1[2] * v2[2], v1[3] * v2[3]);
}
#pragma endregion

#pragma region VectorTraits_Norm
template<typename T, size_t N>
struct VectorTraits_Norm
{
    using Base = VectorBase<T, N>;
    FMATH_INLINE FMATH_CONSTEXPR static T length2(const Base &v);
};

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T VectorTraits_Norm<T, N>::length2(const Base &v)
{
    T result = 0;
    for (index_t i = 0; i < N; ++i)
        result += v[i] * v[i];
    return result;
}

template<typename T>
struct VectorTraits_Norm<T, 2>
{
    using Base = VectorBase<T, 2>;
    FMATH_INLINE FMATH_CONSTEXPR static T length2(const Base &v);
};

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T VectorTraits_Norm<T, 2>::length2(const Base &v)
{
    return v[0] * v[0] + v[1] * v[1];
}

template<typename T>
struct VectorTraits_Norm<T, 3>
{
    using Base = VectorBase<T, 3>;
    FMATH_INLINE FMATH_CONSTEXPR static T length2(const Base &v);
};

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T VectorTraits_Norm<T, 3>::length2(const Base &v)
{
    return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}

template<typename T>
struct VectorTraits_Norm<T, 4>
{
    using Base = VectorBase<T, 4>;
    FMATH_INLINE FMATH_CONSTEXPR static T length2(const Base &v);
};

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T VectorTraits_Norm<T, 4>::length2(const Base &v)
{
    return v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3];
}
#pragma endregion

#pragma region VectorTraits_Stringify
template<typename T, size_t N>
struct VectorTraits_Stringify
{
    static FMATH_INLINE FMATH_CONSTEXPR std::string toString(const VectorBase<T, N> &base, uint32 precision = 6);
};

template<typename T, size_t  N>
FMATH_INLINE FMATH_CONSTEXPR std::string VectorTraits_Stringify<T, N>::toString(const VectorBase<T, N> &base, uint32 precision)
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision);
    ss << '[';
    for (index_t i = 0; i < N; ++i)
        ss << base[i] << ("," + (i == N - 1));
    ss << ']';
    return ss.str();
}
#pragma endregion

#pragma region VectorTraits_Output
template<typename T, size_t N>
struct VectorTraits_Output
{
    static FMATH_INLINE void write(std::ostream &output, const VectorBase<T, N> &base);
};

template<typename T, size_t N>
FMATH_INLINE void VectorTraits_Output<T, N>::write(std::ostream &output, const VectorBase<T, N> &base)
{
    output << VectorTraits_Stringify<T, N>::toString(base);
}
#pragma endregion

#pragma region VectorTraits_Input
template<typename T, size_t N>
struct VectorTraits_Input
{
    static FMATH_INLINE void read(std::istream &input, VectorBase<T, N> &base);
};

template<typename T, size_t N>
FMATH_INLINE void VectorTraits_Input<T, N>::read(std::istream &input, VectorBase<T, N> &base)
{
    for (index_t i = 0; i < N; ++i)
        input >> base[i];
}
#pragma endregion

}

#endif