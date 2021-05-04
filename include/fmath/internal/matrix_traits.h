#ifndef _FMATH_INTERNAL_MATRIX_TRAITS_H_
#define _FMATH_INTERNAL_MATRIX_TRAITS_H_

#include <cstring>
#include <istream>
#include <ostream>
#include <sstream>
#include <string>

#include "matrix_base.h"
#include "../common.h"
#include "../functions.h"

namespace fmath
{
namespace internal
{

#pragma region MatrixTraits_Assign
template<typename T, size_t N, typename MatrixT>
struct MatrixTraits_Assign
{};

template<typename T, typename MatrixT>
struct MatrixTraits_Assign<T, 2, MatrixT>
{
    template<typename MatrixU>
    static FMATH_INLINE FMATH_CONSTEXPR void assign(MatrixT &dst, const MatrixU &src);
};

template<typename T, typename MatrixT>
    template<typename MatrixU>
FMATH_INLINE FMATH_CONSTEXPR void MatrixTraits_Assign<T, 2, MatrixT>::assign(MatrixT &dst, const MatrixU &src)
{
    dst[0] = src[0];
    dst[1] = src[1];
}

template<typename T, typename MatrixT>
struct MatrixTraits_Assign<T, 3, MatrixT>
{
    template<typename MatrixU>
    static FMATH_INLINE FMATH_CONSTEXPR void assign(MatrixT &dst, const MatrixU &src);
};

template<typename T, typename MatrixT>
    template<typename MatrixU>
FMATH_INLINE FMATH_CONSTEXPR void MatrixTraits_Assign<T, 3, MatrixT>::assign(MatrixT &dst, const MatrixU &src)
{
    using VectorType = typename MatrixU::VectorType;

    dst[0] = src[0];
    dst[1] = src[1];

    if constexpr (MatrixU::DIMENSION >= 3)
        dst[2] = src[2];
    else
        dst[2] = VectorType();
}

template<typename T, typename MatrixT>
struct MatrixTraits_Assign<T, 4, MatrixT>
{
    template<typename MatrixU>
    static FMATH_INLINE FMATH_CONSTEXPR void assign(MatrixT &dst, const MatrixU &src);
};

template<typename T, typename MatrixT>
    template<typename MatrixU>
FMATH_INLINE FMATH_CONSTEXPR void MatrixTraits_Assign<T, 4, MatrixT>::assign(MatrixT &dst, const MatrixU &src)
{
    using VectorType = typename MatrixU::VectorType;

    dst[0] = src[0];
    dst[1] = src[1];

    if constexpr (MatrixU::DIMENSION >= 3)
        dst[2] = src[2];
    else
        dst[2] = VectorType();
    
    if constexpr (MatrixU::DIMENSION >= 4)
        dst[3] = src[3];
    else
        dst[3] = VectorType();
}
#pragma endregion

#pragma region MatrixTraits_Compare
template<typename T, size_t N>
struct MatrixTraits_Compare
{};

template<typename T>
struct MatrixTraits_Compare<T, 2>
{
    using Base = MatrixBase<T, 2>;
    static FMATH_INLINE FMATH_CONSTEXPR bool equal(const Base &m1, const Base &m2);
    static FMATH_INLINE FMATH_CONSTEXPR bool equalEpsilon(const Base &m1, const Base &m2, const T &epsilon);
};

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool MatrixTraits_Compare<T, 2>::equal(const Base &m1, const Base &m2)
{
    return fmath::equal(m1[0], m2[0]) && fmath::equal(m1[1], m2[1]);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool MatrixTraits_Compare<T, 2>::equalEpsilon(const Base &m1, const Base &m2, const T &epsilon)
{
    return fmath::equalEpsilon(m1[0], m2[0], epsilon) &&
        fmath::equalEpsilon(m1[1], m2[1], epsilon);
}

template<typename T>
struct MatrixTraits_Compare<T, 3>
{
    using Base = MatrixBase<T, 3>;
    static FMATH_INLINE FMATH_CONSTEXPR bool equal(const Base &m1, const Base &m2);
    static FMATH_INLINE FMATH_CONSTEXPR bool equalEpsilon(const Base &m1, const Base &m2, const T &epsilon);
};

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool MatrixTraits_Compare<T, 3>::equal(const Base &m1, const Base &m2)
{
    return fmath::equal(m1[0], m2[0]) && fmath::equal(m1[1], m2[1]) && fmath::equal(m1[2], m2[2]);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool MatrixTraits_Compare<T, 3>::equalEpsilon(const Base &m1, const Base &m2, const T &epsilon)
{
    return fmath::equalEpsilon(m1[0], m2[0], epsilon) &&
        fmath::equalEpsilon(m1[1], m2[1], epsilon) &&
        fmath::equalEpsilon(m1[2], m2[2], epsilon);
}

template<typename T>
struct MatrixTraits_Compare<T, 4>
{
    using Base = MatrixBase<T, 4>;
    static FMATH_INLINE FMATH_CONSTEXPR bool equal(const Base &m1, const Base &m2);
    static FMATH_INLINE FMATH_CONSTEXPR bool equalEpsilon(const Base &m1, const Base &m2, const T &epsilon);
};

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool MatrixTraits_Compare<T, 4>::equal(const Base &m1, const Base &m2)
{
    return fmath::equal(m1[0], m2[0]) && fmath::equal(m1[1], m2[1]) &&
        fmath::equal(m1[2], m2[2]) && fmath::equal(m1[3], m2[3]);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR bool MatrixTraits_Compare<T, 4>::equalEpsilon(const Base &m1, const Base &m2, const T &epsilon)
{
    return fmath::equalEpsilon(m1[0], m2[0], epsilon) &&
        fmath::equalEpsilon(m1[1], m2[1], epsilon) &&
        fmath::equalEpsilon(m1[2], m2[2], epsilon) &&
        fmath::equalEpsilon(m1[3], m2[3], epsilon)
}
#pragma endregion

#pragma region MatrixTraits_Add
template<typename T, size_t N, typename MatrixT>
struct MatrixTraits_Add
{};

template<typename T, typename MatrixT>
struct MatrixTraits_Add<T, 2, MatrixT>
{
    using Base = MatrixBase<T, 2>;
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT add(const Base &m1, const Base &m2);
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT add(const Base &m, const T &value);
    static FMATH_INLINE FMATH_CONSTEXPR void addBy(Base &m, const Base &other);
    static FMATH_INLINE FMATH_CONSTEXPR void addBy(Base &m, const T &value);
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT sub(const Base &m1, const Base &m2);
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT sub(const Base &m, const T &value);
    static FMATH_INLINE FMATH_CONSTEXPR void subBy(Base &m, const Base &other);
    static FMATH_INLINE FMATH_CONSTEXPR void subBy(Base &m, const T &value);
};

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Add<T, 2, MatrixT>::add(const Base &m1, const Base &m2)
{
    return MatrixT(m1[0] + m2[0], m1[1] + m2[1]);
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Add<T, 2, MatrixT>::add(const Base &m, const T &value)
{
    return MatrixT(m[0] + value, m[1] + value);
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR void MatrixTraits_Add<T, 2, MatrixT>::addBy(Base &m, const Base &other)
{
    m[0] += other[0];
    m[1] += other[1];
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR void MatrixTraits_Add<T, 2, MatrixT>::addBy(Base &m, const T &value)
{
    m[0] += value;
    m[1] += value;
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Add<T, 2, MatrixT>::sub(const Base &m1, const Base &m2)
{
    return MatrixT(m1[0] - m2[0], m1[1] - m2[1]);
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Add<T, 2, MatrixT>::sub(const Base &m, const T &value)
{
    return MatrixT(m[0] - value, m[1] - value);
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR void MatrixTraits_Add<T, 2, MatrixT>::subBy(Base &m, const Base &other)
{
    m[0] -= other[0];
    m[1] -= other[1];
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR void MatrixTraits_Add<T, 2, MatrixT>::subBy(Base &m, const T &value)
{
    m[0] -= value;
    m[1] -= value;
}

template<typename T, typename MatrixT>
struct MatrixTraits_Add<T, 3, MatrixT>
{
    using Base = MatrixBase<T, 3>;
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT add(const Base &m1, const Base &m2);
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT add(const Base &m, const T &value);
    static FMATH_INLINE FMATH_CONSTEXPR void addBy(Base &m, const Base &other);
    static FMATH_INLINE FMATH_CONSTEXPR void addBy(Base &m, const T &value);
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT sub(const Base &m1, const Base &m2);
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT sub(const Base &m, const T &value);
    static FMATH_INLINE FMATH_CONSTEXPR void subBy(Base &m, const Base &other);
    static FMATH_INLINE FMATH_CONSTEXPR void subBy(Base &m, const T &value);
};

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Add<T, 3, MatrixT>::add(const Base &m1, const Base &m2)
{
    return MatrixT(m1[0] + m2[0], m1[1] + m2[1], m1[2] + m2[2]);
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Add<T, 3, MatrixT>::add(const Base &m, const T &value)
{
    return MatrixT(m[0] + value, m[1] + value, m[2] + value);
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR void MatrixTraits_Add<T, 3, MatrixT>::addBy(Base &m, const Base &other)
{
    m[0] += other[0];
    m[1] += other[1];
    m[2] += other[2];
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR void MatrixTraits_Add<T, 3, MatrixT>::addBy(Base &m, const T &value)
{
    m[0] += value;
    m[1] += value;
    m[2] += value;
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Add<T, 3, MatrixT>::sub(const Base &m1, const Base &m2)
{
    return MatrixT(m1[0] - m2[0], m1[1] - m2[1], m1[2] - m2[2]);
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Add<T, 3, MatrixT>::sub(const Base &m, const T &value)
{
    return MatrixT(m[0] - value, m[1] - value, m[2] - value);
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR void MatrixTraits_Add<T, 3, MatrixT>::subBy(Base &m, const Base &other)
{
    m[0] -= other[0];
    m[1] -= other[1];
    m[2] -= other[2];
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR void MatrixTraits_Add<T, 3, MatrixT>::subBy(Base &m, const T &value)
{
    m[0] -= value;
    m[1] -= value;
    m[2] -= value;
}

template<typename T, typename MatrixT>
struct MatrixTraits_Add<T, 4, MatrixT>
{
    using Base = MatrixBase<T, 4>;
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT add(const Base &m1, const Base &m2);
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT add(const Base &m, const T &value);
    static FMATH_INLINE FMATH_CONSTEXPR void addBy(Base &m, const Base &other);
    static FMATH_INLINE FMATH_CONSTEXPR void addBy(Base &m, const T &value);
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT sub(const Base &m1, const Base &m2);
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT sub(const Base &m, const T &value);
    static FMATH_INLINE FMATH_CONSTEXPR void subBy(Base &m, const Base &other);
    static FMATH_INLINE FMATH_CONSTEXPR void subBy(Base &m, const T &value);
};

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Add<T, 4, MatrixT>::add(const Base &m1, const Base &m2)
{
    return MatrixT(m1[0] + m2[0], m1[1] + m2[1], m1[2] + m2[2], m1[3] + m2[3]);
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Add<T, 4, MatrixT>::add(const Base &m, const T &value)
{
    return MatrixT(m[0] + value, m[1] + value, m[2] + value, m[3] + value);
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR void MatrixTraits_Add<T, 4, MatrixT>::addBy(Base &m, const Base &other)
{
    m[0] += other[0];
    m[1] += other[1];
    m[2] += other[2];
    m[3] += other[3];
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR void MatrixTraits_Add<T, 4, MatrixT>::addBy(Base &m, const T &value)
{
    m[0] += value;
    m[1] += value;
    m[2] += value;
    m[3] += value;
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Add<T, 4, MatrixT>::sub(const Base &m1, const Base &m2)
{
    return MatrixT(m1[0] - m2[0], m1[1] - m2[1], m1[2] - m2[2], m1[3] - m2[3]);
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Add<T, 4, MatrixT>::sub(const Base &m, const T &value)
{
    return MatrixT(m[0] - value, m[1] - value, m[2] - value, m[3] - value);
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR void MatrixTraits_Add<T, 4, MatrixT>::subBy(Base &m, const Base &other)
{
    m[0] -= other[0];
    m[1] -= other[1];
    m[2] -= other[2];
    m[3] -= other[3];
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR void MatrixTraits_Add<T, 4, MatrixT>::subBy(Base &m, const T &value)
{
    m[0] -= value;
    m[1] -= value;
    m[2] -= value;
    m[3] -= value;
}
#pragma endregion

#pragma region MatrixTraits_Scale
template<typename T, size_t N, typename MatrixT>
struct MatrixTraits_Scale
{};

template<typename T, typename MatrixT>
struct MatrixTraits_Scale<T, 2, MatrixT>
{
    using Base = MatrixBase<T, 2>;
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT scalarMul(const Base &m, const T &value);
    static FMATH_INLINE FMATH_CONSTEXPR void scalarMulBy(Base &m, const T &value);
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT scalarDiv(const Base &m, const T &value);
    static FMATH_INLINE FMATH_CONSTEXPR void scalarDivBy(Base &m, const T &value);
};

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Scale<T, 2, MatrixT>::scalarMul(const Base &m, const T &value)
{
    return MatrixT(m[0] * value, m[1] * value);
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR void MatrixTraits_Scale<T, 2, MatrixT>::scalarMulBy(Base &m, const T &value)
{
    m[0] *= value;
    m[1] *= value;
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Scale<T, 2, MatrixT>::scalarDiv(const Base &m, const T &value)
{
    return MatrixT(m[0] / value, m[1] / value);
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR void MatrixTraits_Scale<T, 2, MatrixT>::scalarDivBy(Base &m, const T &value)
{
    m[0] /= value;
    m[1] /= value;
}

template<typename T, typename MatrixT>
struct MatrixTraits_Scale<T, 3, MatrixT>
{
    using Base = MatrixBase<T, 3>;
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT scalarMul(const Base &m, const T &value);
    static FMATH_INLINE FMATH_CONSTEXPR void scalarMulBy(Base &m, const T &value);
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT scalarDiv(const Base &m, const T &value);
    static FMATH_INLINE FMATH_CONSTEXPR void scalarDivBy(Base &m, const T &value);
};

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Scale<T, 3, MatrixT>::scalarMul(const Base &m, const T &value)
{
    return MatrixT(m[0] * value, m[1] * value, m[2] * value);
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR void MatrixTraits_Scale<T, 3, MatrixT>::scalarMulBy(Base &m, const T &value)
{
    m[0] *= value;
    m[1] *= value;
    m[2] *= value;
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Scale<T, 3, MatrixT>::scalarDiv(const Base &m, const T &value)
{
    return MatrixT(m[0] / value, m[1] / value, m[2] * value);
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR void MatrixTraits_Scale<T, 3, MatrixT>::scalarDivBy(Base &m, const T &value)
{
    m[0] /= value;
    m[1] /= value;
    m[2] /= value;
}

template<typename T, typename MatrixT>
struct MatrixTraits_Scale<T, 4, MatrixT>
{
    using Base = MatrixBase<T, 4>;
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT scalarMul(const Base &m, const T &value);
    static FMATH_INLINE FMATH_CONSTEXPR void scalarMulBy(Base &m, const T &value);
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT scalarDiv(const Base &m, const T &value);
    static FMATH_INLINE FMATH_CONSTEXPR void scalarDivBy(Base &m, const T &value);
};

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Scale<T, 4, MatrixT>::scalarMul(const Base &m, const T &value)
{
    return MatrixT(m[0] * value, m[1] * value, m[2] * value, m[3] * value);
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR void MatrixTraits_Scale<T, 4, MatrixT>::scalarMulBy(Base &m, const T &value)
{
    m[0] *= value;
    m[1] *= value;
    m[2] *= value;
    m[3] *= value;
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Scale<T, 4, MatrixT>::scalarDiv(const Base &m, const T &value)
{
    return MatrixT(m[0] / value, m[1] / value, m[2] / value, m[3] / value);
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR void MatrixTraits_Scale<T, 4, MatrixT>::scalarDivBy(Base &m, const T &value)
{
    m[0] /= value;
    m[1] /= value;
    m[2] /= value;
    m[3] /= value;
}
#pragma endregion

#pragma region MatrixTraits_Transpose
template<typename T, size_t N, typename MatrixT>
struct MatrixTraits_Transpose
{};

template<typename T, typename MatrixT>
struct MatrixTraits_Transpose<T, 2, MatrixT>
{
    using Base = MatrixBase<T, 2>;
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT transpose(const Base &m);
};

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Transpose<T, 2, MatrixT>::transpose(const Base &m)
{
    return MatrixT(m[0][0], m[1][0], m[0][1], m[1][1]);
}

template<typename T, typename MatrixT>
struct MatrixTraits_Transpose<T, 3, MatrixT>
{
    using Base = MatrixBase<T, 3>;
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT transpose(const Base &m);
};

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Transpose<T, 3, MatrixT>::transpose(const Base &m)
{
    return MatrixT(m[0][0], m[1][0], m[2][0],
        m[0][1], m[1][1], m[2][1],
        m[0][2], m[1][2], m[2][2]
    );
}

template<typename T, typename MatrixT>
struct MatrixTraits_Transpose<T, 4, MatrixT>
{
    using Base = MatrixBase<T, 4>;
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT transpose(const Base &m);
};

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Transpose<T, 4, MatrixT>::transpose(const Base &m)
{
    return MatrixT(m[0][0], m[1][0], m[2][0], m[3][0],
        m[0][1], m[1][1], m[2][1], m[3][1],
        m[0][2], m[1][2], m[2][2], m[3][2],
        m[0][3], m[1][3], m[2][3], m[3][3]
    );
}
#pragma endregion

template<typename T, size_t N, typename MatrixT>
struct MatrixTraits_Basic :
    MatrixTraits_Add<T, N, MatrixT>,
    MatrixTraits_Scale<T, N, MatrixT>,
    MatrixTraits_Transpose<T, N, MatrixT>
{};

#pragma region MatrixTraits_Mul
template<typename T, size_t N, typename MatrixT>
struct MatrixTraits_Mul
{};

template<typename T, typename MatrixT>
struct MatrixTraits_Mul<T, 2, MatrixT>
{
    using Base = MatrixBase<T, 2>;
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT mul(const Base &m1, const Base &m2);
};

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Mul<T, 2, MatrixT>::mul(const Base &m1, const Base &m2)
{
    return MatrixT(m2[0][0] * m1[0][0] + m2[0][1] * m1[1][0], m2[0][0] * m1[0][1] + m2[0][1] * m1[1][1],
        m2[1][0] * m1[0][0] + m2[1][1] * m1[1][0], m2[1][0] * m1[0][1] + m2[1][1] * m1[1][1]
    );
}

template<typename T, typename MatrixT>
struct MatrixTraits_Mul<T, 3, MatrixT>
{
    using Base = MatrixBase<T, 3>;
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT mul(const Base &m1, const Base &m2);
};

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Mul<T, 3, MatrixT>::mul(const Base &m1, const Base &m2)
{
    return MatrixT(m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2],
        m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2],
        m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2],
        m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2],
        m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2],
        m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2],
        m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2],
        m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2],
        m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1] + m1[2][2] * m2[2][2]
    );
}

template<typename T, typename MatrixT>
struct MatrixTraits_Mul<T, 4, MatrixT>
{
    using Base = MatrixBase<T, 4>;
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT mul(const Base &m1, const Base &m2);
};

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Mul<T, 4, MatrixT>::mul(const Base &m1, const Base &m2)
{
    return MatrixT(m1[0] * m2[0][0] + m1[1] * m2[0][1] + m1[2] * m2[0][2] + m1[3] * m2[0][3],
	    m1[0] * m2[1][0] + m1[1] * m2[1][1] + m1[2] * m2[1][2] + m1[3] * m2[1][3],
	    m1[0] * m2[2][0] + m1[1] * m2[2][1] + m1[2] * m2[2][2] + m1[3] * m2[2][3],
	    m1[0] * m2[3][0] + m1[1] * m2[3][1] + m1[2] * m2[3][2] + m1[3] * m2[3][3]
    );
}
#pragma endregion

#pragma region MatrixTraits_VectorMul
template<typename T, size_t N, typename VectorT>
struct MatrixTraits_VectorMul
{};

template<typename T, typename VectorT>
struct MatrixTraits_VectorMul<T, 2, VectorT>
{
    using VecBase = VectorBase<T, 2>;
    using MatBase = MatrixBase<T, 2>;
    static FMATH_INLINE FMATH_CONSTEXPR VectorT vectorMul(const VecBase &v, const MatBase &m);
    static FMATH_INLINE FMATH_CONSTEXPR VectorT vectorMul(const MatBase &m, const VecBase &v);
};

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT MatrixTraits_VectorMul<T, 2, VectorT>::vectorMul(const VecBase &v, const MatBase &m)
{
    return VectorT(v[0] * m[0][0] + v[1] * m[0][1],
        v[0] * m[1][0] + v[1] * m[1][1]);
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT MatrixTraits_VectorMul<T, 2, VectorT>::vectorMul(const MatBase &m, const VecBase &v)
{
    return VectorT(m[0][0] * v[0] + m[1][0] * v[1],
        m[0][1] * v[0] + m[1][1] * v[1]
    );
}

template<typename T, typename VectorT>
struct MatrixTraits_VectorMul<T, 3, VectorT>
{
    using VecBase = VectorBase<T, 3>;
    using MatBase = MatrixBase<T, 3>;
    static FMATH_INLINE FMATH_CONSTEXPR VectorT vectorMul(const VecBase &v, const MatBase &m);
    static FMATH_INLINE FMATH_CONSTEXPR VectorT vectorMul(const MatBase &m, const VecBase &v);
};

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT MatrixTraits_VectorMul<T, 3, VectorT>::vectorMul(const VecBase &v, const MatBase &m)
{
    return VectorT(v[0] * m[0][0] + v[1] * m[0][1] + v[2] * m[0][2],
        v[0] * m[1][0] + v[1] * m[1][1] + v[2] * m[1][2],
        v[0] * m[2][0] + v[1] * m[2][1] + v[2] * m[2][2]
    );
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT MatrixTraits_VectorMul<T, 3, VectorT>::vectorMul(const MatBase &m, const VecBase &v)
{
    return VectorT(m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2],
        m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2],
        m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2]
    );
}

template<typename T, typename VectorT>
struct MatrixTraits_VectorMul<T, 4, VectorT>
{
    using VecBase = VectorBase<T, 4>;
    using MatBase = MatrixBase<T, 4>;
    static FMATH_INLINE FMATH_CONSTEXPR VectorT vectorMul(const VecBase &v, const MatBase &m);
    static FMATH_INLINE FMATH_CONSTEXPR VectorT vectorMul(const MatBase &m, const VecBase &v);
};

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT MatrixTraits_VectorMul<T, 4, VectorT>::vectorMul(const VecBase &v, const MatBase &m)
{
    return VectorT(v[0] * m[0][0] + v[1] * m[0][1] + v[2] * m[0][2] + v[3] * m[0][3],
        v[0] * m[1][0] + v[1] * m[1][1] + v[2] * m[1][2] + v[3] * m[1][3],
        v[0] * m[2][0] + v[1] * m[2][1] + v[2] * m[2][2] + v[3] * m[2][3],
        v[0] * m[3][0] + v[1] * m[3][1] + v[2] * m[3][2] + v[3] * m[3][3]
    );
}

template<typename T, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR VectorT MatrixTraits_VectorMul<T, 4, VectorT>::vectorMul(const MatBase &m, const VecBase &v)
{
    return VectorT(m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2] + m[3][0] * v[3],
        m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2] + m[3][1] * v[3],
        m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2] + m[3][2] * v[3],
        m[0][3] * v[0] + m[1][3] * v[1] + m[2][3] * v[2] + m[3][3] * v[3]
    );
}
#pragma endregion

#pragma region MatrixTraits_Hadamard
template<typename T, size_t N, typename MatrixT>
struct MatrixTraits_Hadamard
{};

template<typename T, typename MatrixT>
struct MatrixTraits_Hadamard<T, 2, MatrixT>
{
    using Base = MatrixBase<T, 2>;
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT hadamardMul(const Base &m1, const Base &m2);
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT hadamardDiv(const Base &m1, const Base &m2);
};

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Hadamard<T, 2, MatrixT>::hadamardMul(const Base &m1, const Base &m2)
{
    return MatrixT(fmath::hadamardMul(m1[0], m2[0]), fmath::hadamardMul(m1[1], m2[1]));
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Hadamard<T, 2, MatrixT>::hadamardDiv(const Base &m1, const Base &m2)
{
    return MatrixT(fmath::hadamardDiv(m1[0], m2[0]), fmath::hadamardDiv(m1[1], m2[1]));
}

template<typename T, typename MatrixT>
struct MatrixTraits_Hadamard<T, 3, MatrixT>
{
    using Base = MatrixBase<T, 3>;
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT hadamardMul(const Base &m1, const Base &m2);
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT hadamardDiv(const Base &m1, const Base &m2);
};

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Hadamard<T, 3, MatrixT>::hadamardMul(const Base &m1, const Base &m2)
{
    return MatrixT(fmath::hadamardMul(m1[0], m2[0]), 
        fmath::hadamardMul(m1[1], m2[1]),
        fmath::hadamardMul(m1[2], m2[2])
    );
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Hadamard<T, 3, MatrixT>::hadamardDiv(const Base &m1, const Base &m2)
{
    return MatrixT(fmath::hadamardDiv(m1[0], m2[0]), 
        fmath::hadamardDiv(m1[1], m2[1]),
        fmath::hadamardDiv(m1[2], m2[2])
    );
}

template<typename T, typename MatrixT>
struct MatrixTraits_Hadamard<T, 4, MatrixT>
{
    using Base = MatrixBase<T, 4>;
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT hadamardMul(const Base &m1, const Base &m2);
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT hadamardDiv(const Base &m1, const Base &m2);
};

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Hadamard<T, 4, MatrixT>::hadamardMul(const Base &m1, const Base &m2)
{
    return MatrixT(fmath::hadamardMul(m1[0], m2[0]), 
        fmath::hadamardMul(m1[1], m2[1]),
        fmath::hadamardMul(m1[2], m2[2]),
        fmath::hadamardMul(m1[3], m2[3])
    );
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Hadamard<T, 4, MatrixT>::hadamardDiv(const Base &m1, const Base &m2)
{
    return MatrixT(fmath::hadamardDiv(m1[0], m2[0]), 
        fmath::hadamardDiv(m1[1], m2[1]),
        fmath::hadamardDiv(m1[2], m2[2]),
        fmath::hadamardDiv(m1[3], m2[3])
    );
}
#pragma endregion

#pragma region MatrixTraits_Square
template<typename T, size_t N, typename MatrixT>
struct MatrixTraits_Square
{};

template<typename T, typename MatrixT>
struct MatrixTraits_Square<T, 2, MatrixT>
{
    using Base = MatrixBase<T, 2>;
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT inverse(const Base &m);
    static FMATH_INLINE FMATH_CONSTEXPR T determinant(const Base &m);
};

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Square<T, 2, MatrixT>::inverse(const Base &m)
{
    static_assert(std::is_floating_point_v<T>, "T must be a floating point type");

    T det = determinant(m);
    FMATH_FASSERT(det != static_cast<T>(0), "The matrix is not invertible");

    det = static_cast<T>(1) / det;
    return MatrixT(m[1][1], -m[0][1], -m[1][0], m[0][0]) * det;
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR T MatrixTraits_Square<T, 2, MatrixT>::determinant(const Base &m)
{
    return m[0][0] * m[1][1] - m[0][1] * m[1][0]; 
}

template<typename T, typename MatrixT>
struct MatrixTraits_Square<T, 3, MatrixT>
{
    using Base = MatrixBase<T, 3>;
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT inverse(const Base &m);
    static FMATH_INLINE FMATH_CONSTEXPR T determinant(const Base &m);
};

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Square<T, 3, MatrixT>::inverse(const Base &m)
{
    static_assert(std::is_floating_point_v<T>, "T must be a floating point type");

    MatrixT result;
    result[0][0] = m[1][1] * m[2][2] - m[1][2] * m[2][1];
    result[0][1] = m[0][2] * m[2][1] - m[0][1] * m[2][2];
    result[0][2] = m[0][1] * m[1][2] - m[0][2] * m[1][1];
    result[1][0] = m[1][2] * m[2][0] - m[1][0] * m[2][2];
    result[1][1] = m[0][0] * m[2][2] - m[0][2] * m[2][0];
    result[1][2] = m[0][2] * m[1][0] - m[0][0] * m[1][2];
    result[2][0] = m[1][0] * m[2][1] - m[1][1] * m[2][0];
    result[2][1] = m[0][1] * m[2][0] - m[0][0] * m[2][1];
    result[2][2] = m[0][0] * m[1][1] - m[0][1] * m[1][0];

    T det = determinant(m);
    FMATH_FASSERT(det != static_cast<T>(0), "The matrix is not invertible");

    det = static_cast<T>(1) / det;

    result *= det;
    return result;
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR T MatrixTraits_Square<T, 3, MatrixT>::determinant(const Base &m)
{
    return m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) - 
        m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2]) + 
        m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]
    );
}

template<typename T, typename MatrixT>
struct MatrixTraits_Square<T, 4, MatrixT>
{
    using Base = MatrixBase<T, 4>;
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT inverse(const Base &m);
    static FMATH_INLINE FMATH_CONSTEXPR T determinant(const Base &m);
};

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Square<T, 4, MatrixT>::inverse(const Base &m)
{
    static_assert(std::is_floating_point_v<T>, "T must be a floating point type");

    MatrixT result;
    result[0][0] = m[1][1] * m[2][2] * m[3][3] -
        m[1][1] * m[2][3] * m[3][2] -
        m[2][1] * m[1][2] * m[3][3] +
        m[2][1] * m[1][3] * m[3][2] +
        m[3][1] * m[1][2] * m[2][3] -
        m[3][1] * m[1][3] * m[2][2];

    result[1][0] = -m[1][0] * m[2][2] * m[3][3] + 
        m[1][0] * m[2][3] * m[3][2] +
        m[2][0] * m[1][2] * m[3][3] -
        m[2][0] * m[1][3] * m[3][2] -
        m[3][0] * m[1][2] * m[2][3] +
        m[3][0] * m[1][3] * m[2][2];

    result[2][0] = m[1][0] * m[2][1] * m[3][3] - 
        m[1][0] * m[2][3] * m[3][1] -
        m[2][0] * m[1][1] * m[3][3] +
        m[2][0] * m[1][3] * m[3][1] +
        m[3][0] * m[1][1] * m[2][3] -
        m[3][0] * m[1][3] * m[2][1];

    result[3][0] = -m[1][0] * m[2][1] * m[3][2] + 
        m[1][0] * m[2][2] * m[3][1] +
        m[2][0] * m[1][1] * m[3][2] -
        m[2][0] * m[1][2] * m[3][1] -
        m[3][0] * m[1][1] * m[2][2] +
        m[3][0] * m[1][2] * m[2][1];

    result[0][1] = -m[0][1] * m[2][2] * m[3][3] + 
        m[0][1] * m[2][3] * m[3][2] +
        m[2][1] * m[0][2] * m[3][3] -
        m[2][1] * m[0][3] * m[3][2] -
        m[3][1] * m[0][2] * m[2][3] +
        m[3][1] * m[0][3] * m[2][2];

    result[1][1] = m[0][0] * m[2][2] * m[3][3] -
        m[0][0] * m[2][3] * m[3][2] -
        m[2][0] * m[0][2] * m[3][3] +
        m[2][0] * m[0][3] * m[3][2] +
        m[3][0] * m[0][2] * m[2][3] -
        m[3][0] * m[0][3] * m[2][2];

    result[2][1] = -m[0][0] * m[2][1] * m[3][3] + 
        m[0][0] * m[2][3] * m[3][1] +
        m[2][0] * m[0][1] * m[3][3] -
        m[2][0] * m[0][3] * m[3][1] -
        m[3][0] * m[0][1] * m[2][3] +
        m[3][0] * m[0][3] * m[2][1];

    result[3][1] = m[0][0] * m[2][1] * m[3][2] - 
        m[0][0] * m[2][2] * m[3][1] -
        m[2][0] * m[0][1] * m[3][2] +
        m[2][0] * m[0][2] * m[3][1] +
        m[3][0] * m[0][1] * m[2][2] -
        m[3][0] * m[0][2] * m[2][1];

    result[0][2] = m[0][1] * m[1][2] * m[3][3] - 
        m[0][1] * m[1][3] * m[3][2] -
        m[1][1] * m[0][2] * m[3][3] +
        m[1][1] * m[0][3] * m[3][2] +
        m[3][1] * m[0][2] * m[1][3] -
        m[3][1] * m[0][3] * m[1][2];

    result[1][2] = -m[0][0] * m[1][2] * m[3][3] + 
        m[0][0] * m[1][3] * m[3][2] +
        m[1][0] * m[0][2] * m[3][3] -
        m[1][0] * m[0][3] * m[3][2] -
        m[3][0] * m[0][2] * m[1][3] +
        m[3][0] * m[0][3] * m[1][2];

    result[2][2] = m[0][0] * m[1][1] * m[3][3] -
        m[0][0] * m[1][3] * m[3][1] -
        m[1][0] * m[0][1] * m[3][3] +
        m[1][0] * m[0][3] * m[3][1] +
        m[3][0] * m[0][1] * m[1][3] -
        m[3][0] * m[0][3] * m[1][1];

    result[3][2] = -m[0][0] * m[1][1] * m[3][2] + 
        m[0][0] * m[1][2] * m[3][1] +
        m[1][0] * m[0][1] * m[3][2] -
        m[1][0] * m[0][2] * m[3][1] -
        m[3][0] * m[0][1] * m[1][2] +
        m[3][0] * m[0][2] * m[1][1];

    result[0][3] = -m[0][1] * m[1][2] * m[2][3] + 
        m[0][1] * m[1][3] * m[2][2] +
        m[1][1] * m[0][2] * m[2][3] -
        m[1][1] * m[0][3] * m[2][2] -
        m[2][1] * m[0][2] * m[1][3] +
        m[2][1] * m[0][3] * m[1][2];

    result[1][3] = m[0][0] * m[1][2] * m[2][3] - 
        m[0][0] * m[1][3] * m[2][2] -
        m[1][0] * m[0][2] * m[2][3] +
        m[1][0] * m[0][3] * m[2][2] +
        m[2][0] * m[0][2] * m[1][3] -
        m[2][0] * m[0][3] * m[1][2];

    result[2][3] = -m[0][0] * m[1][1] * m[2][3] + 
        m[0][0] * m[1][3] * m[2][1] +
        m[1][0] * m[0][1] * m[2][3] -
        m[1][0] * m[0][3] * m[2][1] -
        m[2][0] * m[0][1] * m[1][3] +
        m[2][0] * m[0][3] * m[1][1];

    result[3][3] = m[0][0] * m[1][1] * m[2][2] - 
        m[0][0] * m[1][2] * m[2][1] -
        m[1][0] * m[0][1] * m[2][2] +
        m[1][0] * m[0][2] * m[2][1] +
        m[2][0] * m[0][1] * m[1][2] -
        m[2][0] * m[0][2] * m[1][1];

    T det = m[0][0] * result[0][0] + m[0][1] * result[1][0] + m[0][2] * result[2][0] + m[0][3] * result[3][0];
    FMATH_FASSERT(det != static_cast<T>(0), "The matrix is not invertible");

    det = static_cast<T>(1) / det;
    result *= det;
    return result;
}

template<typename T, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR T MatrixTraits_Square<T, 4, MatrixT>::determinant(const Base &m)
{
    T f0 = m[1][1] * m[2][2] * m[3][3] -
        m[1][1] * m[2][3] * m[3][2] -
        m[2][1] * m[1][2] * m[3][3] +
        m[2][1] * m[1][3] * m[3][2] +
        m[3][1] * m[1][2] * m[2][3] -
        m[3][1] * m[1][3] * m[2][2];

    T f1 = -m[1][0] * m[2][2] * m[3][3] + 
        m[1][0] * m[2][3] * m[3][2] +
        m[2][0] * m[1][2] * m[3][3] -
        m[2][0] * m[1][3] * m[3][2] -
        m[3][0] * m[1][2] * m[2][3] +
        m[3][0] * m[1][3] * m[2][2];

    T f2 = m[1][0] * m[2][1] * m[3][3] - 
        m[1][0] * m[2][3] * m[3][1] -
        m[2][0] * m[1][1] * m[3][3] +
        m[2][0] * m[1][3] * m[3][1] +
        m[3][0] * m[1][1] * m[2][3] -
        m[3][0] * m[1][3] * m[2][1];

    T f3 = -m[1][0] * m[2][1] * m[3][2] + 
        m[1][0] * m[2][2] * m[3][1] +
        m[2][0] * m[1][1] * m[3][2] -
        m[2][0] * m[1][2] * m[3][1] -
        m[3][0] * m[1][1] * m[2][2] +
        m[3][0] * m[1][2] * m[2][1];
    
    return f0 * m[0][0] + f1 * m[0][1] + f2 * m[0][2] + f3 * m[0][3];
}

#pragma endregion

#pragma region MatrixTraits_Stringify
template<typename T, size_t N>
struct MatrixTraits_Stringify
{
    using Base = MatrixBase<T, N>;
    static FMATH_INLINE FMATH_CONSTEXPR std::string toString(const Base &mat, uint32 precision = 6);
};

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR std::string MatrixTraits_Stringify<T, N>::toString(const Base &mat, uint32 precision)
{
    std::stringstream ss;
    ss << '[';
    for (index_t i = 0; i < N; ++i)
        ss << fmath::toString(mat[i], precision);
    ss << ']';
    return ss.str();
}
#pragma endregion

#pragma region MatrixTraits_Output
template<typename T, size_t N>
struct MatrixTraits_Output
{
    using Base = MatrixBase<T, N>;
    static FMATH_INLINE void write(std::ostream &output, const Base &mat);
};

template<typename T, size_t N>
FMATH_INLINE void MatrixTraits_Output<T, N>::write(std::ostream &output, const Base &mat)
{
    output << '[';
    for (index_t i = 0; i < N; ++i)
    {
        const char *space = " ";
        space += (i == N - 1);
        output << mat[i] << space;
    }
    output << ']';
}
#pragma endregion

#pragma region MatrixTraits_Input
template<typename T, size_t N>
struct MatrixTraits_Input
{
    using Base = MatrixBase<T, N>;
    static FMATH_INLINE void read(std::ostream &input, Base &mat);
};

template<typename T, size_t N>
FMATH_INLINE void MatrixTraits_Input<T, N>::read(std::ostream &input, Base &mat)
{
    for (index_t i = 0; i < N; ++i)
        for (index_t j = 0; j < N; ++j)
            input >> mat[i][j];
}
#pragma endregion

}
}

#endif