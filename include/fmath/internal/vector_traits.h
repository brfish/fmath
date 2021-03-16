#ifndef _FMATH_INTERNAL_VECTOR_TRAITS_H_
#define _FMATH_INTERNAL_VECTOR_TRAITS_H_

#include "internal/vector_base.h"
#include "functions.h"

namespace fmath::internal
{

#pragma region VectorTraits_Compare
template<typename T, size_t N>
struct VectorTraits_Compare
{
    using Base = VectorBase<T, N>;
    static FMATH_INLINE FMATH_CONSTEXPR bool equal(const Base &v1, const Base &v2);
    static FMATH_INLINE FMATH_CONSTEXPR bool equalEpsilon(const Base &v1, const Base &v2, const T &epsilon);
};

template<typename T, size_t N>
bool FMATH_INLINE FMATH_CONSTEXPR VectorTraits_Compare<T, N>::equal(const Base &v1, const Base &v2)
{
    for (index_t i = 0; i < N; ++i)
    {
        if (v1[i] != v2[i])
            return false;
    }
    return true;
}

template<typename T, size_t N>
bool FMATH_INLINE FMATH_CONSTEXPR VectorTraits_Compare<T, N>::equalEpsilon(const Base &v1, const Base &v2, const T &epsilon)
{
    for (index_t i = 0; i < N; ++i)
    {
        if (!equalEpsilon(v1[i], v2[i], epsilon))
            return false;
    }
    return true;
}

template<typename T>
struct VectorTraits_Compare<T, 2>
{
    using Base = VectorBase<T, 2>;
    static FMATH_INLINE FMATH_CONSTEXPR bool equal(const Base &v1, const Base &v2);
    static FMATH_INLINE FMATH_CONSTEXPR bool equalEpsilon(const Base &v1, const Base &v2, const T &epsilon);
};

template<typename T>
bool FMATH_INLINE FMATH_CONSTEXPR VectorTraits_Compare<T, 2>::equal(const Base &v1, const Base &v2)
{
    return v1.x == v2.x && v1.y == v2.y;
}

template<typename T>
bool FMATH_INLINE FMATH_CONSTEXPR VectorTraits_Compare<T, 2>::equalEpsilon(const Base &v1, const Base &v2, const T &epsilon)
{
    return equalEpsilon(v1.x, v2.x) && equalEpsilon(v1.y, v2.y);
}

template<typename T>
struct VectorTraits_Compare<T, 3>
{
    using Base = VectorBase<T, 3>;
    static FMATH_INLINE FMATH_CONSTEXPR bool equal(const Base &v1, const Base &v2);
    static FMATH_INLINE FMATH_CONSTEXPR bool equalEpsilon(const Base &v1, const Base &v2, const T &epsilon);
};

template<typename T>
bool FMATH_INLINE FMATH_CONSTEXPR VectorTraits_Compare<T, 3>::equal(const Base &v1, const Base &v2)
{
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

template<typename T>
bool FMATH_INLINE FMATH_CONSTEXPR VectorTraits_Compare<T, 3>::equalEpsilon(const Base &v1, const Base &v2, const T &epsilon)
{
    return equalEpsilon(v1.x, v2.x) && equalEpsilon(v1.y, v2.y) && equalEpsilon(v1.z, v2.z);
}

template<typename T>
struct VectorTraits_Compare<T, 4>
{
    using Base = VectorBase<T, 4>;
    static FMATH_INLINE FMATH_CONSTEXPR bool equal(const Base &v1, const Base &v2);
    static FMATH_INLINE FMATH_CONSTEXPR bool equalEpsilon(const Base &v1, const Base &v2, const T &epsilon);
};

template<typename T>
bool FMATH_INLINE FMATH_CONSTEXPR VectorTraits_Compare<T, 4>::equal(const Base &v1, const Base &v2)
{
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w;
}

template<typename T>
bool FMATH_INLINE FMATH_CONSTEXPR VectorTraits_Compare<T, 4>::equalEpsilon(const Base &v1, const Base &v2, const T &epsilon)
{
    return equalEpsilon(v1.x, v2.x) && equalEpsilon(v1.y, v2.y) && 
        equalEpsilon(v1.z, v2.z) && equalEpsilon(v1.w, v2.w);
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
    return VectorT(v1.x + v2.x, v1. y + v2.y);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Add<T, 2, VectorT>::add(const Base &v, const T &value)
{
    return VectorT(v.x + value, v.y + value);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Add<T, 2, VectorT>::sub(const Base &v1, const Base &v2)
{
    return VectorT(v1.x - v2.x, v1.y - v2.y);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Add<T, 2, VectorT>::sub(const Base &v, const T &value)
{
    return VectorT(v.x - value, v.y - value);
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
    return VectorT(v1.x + v2.x, v1. y + v2.y, v1.z + v2.z);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Add<T, 3, VectorT>::add(const Base &v, const T &value)
{
    return VectorT(v.x + value, v.y + value, v.z + value);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Add<T, 3, VectorT>::sub(const Base &v1, const Base &v2)
{
    return VectorT(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Add<T, 3, VectorT>::sub(const Base &v, const T &value)
{
    return VectorT(v.x - value, v.y - value, v.z - value);
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
    return VectorT(v1.x + v2.x, v1. y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Add<T, 4, VectorT>::add(const Base &v, const T &value)
{
    return VectorT(v.x + value, v.y + value, v.z + value, v.w + value);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Add<T, 4, VectorT>::sub(const Base &v1, const Base &v2)
{
    return VectorT(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Add<T, 4, VectorT>::sub(const Base &v, const T &value)
{
    return VectorT(v.x - value, v.y - value, v.z - value, v.w - value);
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
    return v1.x * v2.x + v1.y * v2.y;
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
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
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
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}
#pragma endregion

#pragma region VectorTraits_Scale
template<typename T, size_t N, typename VectorT>
struct VectorTraits_Scale
{
    using Base = VectorBase<T, N>;
    FMATH_INLINE FMATH_CONSTEXPR static VectorT mul(const Base &v, const T &value);
    FMATH_INLINE FMATH_CONSTEXPR static VectorT div(const Base &v, const T &value);
};

template<typename T, size_t N, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Scale<T, N, VectorT>::mul(const Base &v, const T &value)
{
    VectorT result;
    for (index_t i = 0; i < N; ++i)
        result[i] = v[i] * value;
    return result;
}

template<typename T, size_t N, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Scale<T, N, VectorT>::div(const Base &v, const T &value)
{
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
    return VectorT(v.x * value, v.y * value);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Scale<T, 2, VectorT>::div(const Base &v, const T &value)
{
    return VectorT(v.x / value, v.y / value);
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
    return VectorT(v.x * value, v.y * value, v.z * value);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Scale<T, 3, VectorT>::div(const Base &v, const T &value)
{
    return VectorT(v.x / value, v.y / value, v.z / value);
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
    return VectorT(v.x * value, v.y * value, v.z * value, v.w * value);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Scale<T, 4, VectorT>::div(const Base &v, const T &value)
{
    return VectorT(v.x / value, v.y / value, v.z / value, v.w / value);
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
        result[i] = v1[i] / v2[i];
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
    return VectorT(v1.x * v2.x, v1.y * v2.y);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Hadamard<T, 2, VectorT>::hadamardDiv(const Base &v1, const Base &v2)
{
    return VectorT(v1.x / v2.x, v1.y / v2.y);
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
    return VectorT(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Hadamard<T, 3, VectorT>::hadamardDiv(const Base &v1, const Base &v2)
{
    return VectorT(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
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
    return VectorT(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT VectorTraits_Hadamard<T, 4, VectorT>::hadamardDiv(const Base &v1, const Base &v2)
{
    return VectorT(v1.x / v2.x, v1.y / v2.y, v1.z * v2.z, v1.w * v2.w);
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
    return v.x * v.x + v.y * v.y;
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
    return v.x * v.x + v.y * v.y + v.z * v.z;
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
    return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
}
#pragma endregion

#pragma region VectorTraits_Print
template<typename T, size_t N>
struct VectorTraits_Print
{
    FMATH_INLINE static void print(std::ostream &output, const VectorBase<T, N> &base);
};

template<typename T, size_t N>
FMATH_INLINE void VectorTraits_Print<T, N>::print(std::ostream &output, const VectorBase<T, N> &base)
{
    output << '[';
    for (index_t i = 0; i < N; ++i)
        output << base[i] << ("," + (i == N - 1));
    output << ']';
}

#pragma endregion

}

#endif