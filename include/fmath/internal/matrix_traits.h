#ifndef _FMATH_INTERNAL_MATRIX_TRAITS_H_
#define _FMATH_INTERNAL_MATRIX_TRAITS_H_

#include <cstring>
#include <istream>
#include <ostream>

#include "internal/matrix_base.h"
#include "common.h"
#include "functions.h"

namespace fmath
{
namespace internal
{
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
        output << mat[i] << (" " + (i == N - 1));
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

#pragma region MatrixTraits_Compare
template<typename T, size_t N>
struct MatrixTraits_Compare
{
    using Base = MatrixBase<T, N>;
    static FMATH_INLINE bool equal(const Base &m1, const Base &m2);
    static FMATH_INLINE bool equalEpsilon(const Base &m1, const Base &m2, const T &epsilon);
};

template<typename T, size_t N>
FMATH_INLINE bool MatrixTraits_Compare<T, N>::equal(const Base &m1, const Base &m2)
{
    if (&m1 == &m2)
        return true;
    return memcmp(m1.data(), m2.data(), sizeof(Base)) == 0;
}

template<typename T, size_t N>
FMATH_INLINE bool MatrixTraits_Compare<T, N>::equalEpsilon(const Base &m1, const Base &m2, const T &epsilon)
{
    if (&m1 == &m2)
        return true;
    for (index_t i = 0; i < N; ++i)
    {
        for (index_t j = 0; j < N; ++j)
        {
            if (!fmath::equalEpsilon(m1[i][j], m2[i][j], epsilon))
                return false;
        }
    }
    return true;
}
#pragma endregion

#pragma region MatrixTraits_Add
template<typename T, size_t N, typename MatrixT>
struct MatrixTraits_Add
{
    using Base = MatrixBase<T, N>;
    static FMATH_INLINE MatrixT add(const Base &m1, const Base &m2);
    static FMATH_INLINE MatrixT add(const Base &m, const T &value);
    static FMATH_INLINE FMATH_CONSTEXPR void addBy(Base &m, const Base &other);
    static FMATH_INLINE FMATH_CONSTEXPR void addBy(Base &m, const T &value);
    static FMATH_INLINE MatrixT sub(const Base &m1, const Base &m2);
    static FMATH_INLINE MatrixT sub(const Base &m, const T &value);
    static FMATH_INLINE FMATH_CONSTEXPR void subBy(Base &m, const Base &other);
    static FMATH_INLINE FMATH_CONSTEXPR void subBy(Base &m, const T &value);
};

template<typename T, size_t N, typename MatrixT>
FMATH_INLINE MatrixT MatrixTraits_Add<T, N, MatrixT>::add(const Base &m1, const Base &m2)
{
    MatrixT result;
    for (index_t i = 0; i < N; ++i)
        result[i] = m1[i] + m2[i];
    return result;
}

template<typename T, size_t N, typename MatrixT>
FMATH_INLINE MatrixT MatrixTraits_Add<T, N, MatrixT>::add(const Base &m, const T &value)
{
    MatrixT result;
    for (index_t i = 0; i < N; ++i)
        result[i] = m[i] + value;
    return m;
}

template<typename T, size_t N, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR void MatrixTraits_Add<T, N, MatrixT>::addBy(Base &m, const Base &other)
{
    for (index_t i = 0; i < N; ++i)
        m[i] += other[i];
}

template<typename T, size_t N, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR void MatrixTraits_Add<T, N, MatrixT>::addBy(Base &m, const T &value)
{
    for (index_t i = 0; i < N; ++i)
        m[i] += value;
}

template<typename T, size_t N, typename MatrixT>
FMATH_INLINE MatrixT MatrixTraits_Add<T, N, MatrixT>::sub(const Base &m1, const Base &m2)
{
    MatrixT result;
    for (index_t i = 0; i < N; ++i)
        result[i] = m1[i] - m2[i];
    return result;
}

template<typename T, size_t N, typename MatrixT>
FMATH_INLINE MatrixT MatrixTraits_Add<T, N, MatrixT>::sub(const Base &m, const T &value)
{
    MatrixT result;
    for (index_t i = 0; i < N; ++i)
        result[i] = m[i] - value;
    return result;
}
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
{
    using Base = MatrixBase<T, N>;
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT scalarMul(const Base &m, const T &value);
    static FMATH_INLINE FMATH_CONSTEXPR void scalarMulBy(Base &m, const T &value);
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT scalarDiv(const Base &m, const T &value);
    static FMATH_INLINE FMATH_CONSTEXPR void scalarDivBy(Base &m, const T &value);
};

template<typename T, size_t N, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Scale<T, N, MatrixT>::scalarMul(const Base &m, const T &value)
{
    MatrixT mat;
    for (index_t i = 0; i < N; ++i)
        mat[i] = m[i] * value;
    return mat;
}

template<typename T, size_t N, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR void MatrixTraits_Scale<T, N, MatrixT>::scalarMulBy(Base &m, const T &value)
{
    for (index_t i = 0; i < N; ++i)
        m[i] *= value;
}

template<typename T, size_t N, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Scale<T, N, MatrixT>::scalarDiv(const Base &m, const T &value)
{
    MatrixT mat;
    for (index_t i = 0; i < N; ++i)
        mat[i] = m[i] / value;
    return mat;
}

template<typename T, size_t N, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR void MatrixTraits_Scale<T, N, MatrixT>::scalarDivBy(Base &m, const T &value)
{
    for (index_t i = 0; i < N; ++i)
        m[i] /= value;
}

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
{
    using Base = MatrixBase<T, N>;
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT transpose(const Base &m);
};

template<typename T, size_t N, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Transpose<T, N, MatrixT>::transpose(const Base &m)
{
    MatrixT result;
    for (index_t i = 0; i < N; ++i)
        for (index_t j = 0; j < N; +j)
            result[i][j] = m[j][i];
    return result;
}

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
{
    using Base = MatrixBase<T, N>;
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT mul(const Base &m1, const Base &m2);
};

template<typename T, size_t N, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Mul<T, N, MatrixT>::mul(const Base &m1, const Base &m2)
{
    MatrixT result;
    for (index_t k = 0; k < N; ++k)
        for (index_t i = 0; i < N; ++i)
            for (index_t j = 0; j < N; ++j)
                result[k] += m1[i] * m2[k][j];
    return result;
}

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
{
    using VecBase = VectorBase<T, N>;
    using MatBase = MatrixBase<T, N>;
    static FMATH_INLINE FMATH_CONSTEXPR VectorT vectorMul(const VecBase &v, const MatBase &m);
    static FMATH_INLINE FMATH_CONSTEXPR VectorT vectorMul(const MatBase &m, const VecBase &v);
};

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
{
    using Base = MatrixBase<T, N>;
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT hadamardMul(const Base &m1, const Base &m2);
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT hadamardDiv(const Base &m1, const Base &m2);
};

template<typename T, size_t N, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Hadamard<T, N, MatrixT>::hadamardMul(const Base &m1, const Base &m2)
{
    MatrixT result;
    for (index_t i = 0; i < N; ++i)
        for (index_t j = 0; j < N; ++j)
            result[i][j] = m1[i][j] * m2[i][j];
    return result;
}

template<typename T, size_t N, typename MatrixT>
FMATH_INLINE FMATH_CONSTEXPR MatrixT MatrixTraits_Hadamard<T, N, MatrixT>::hadamardDiv(const Base &m1, const Base &m2)
{
    MatrixT result;
    for (index_t i = 0; i < N; ++i)
        for (index_t j = 0; j < N; ++j)
            result[i][j] = m1[i][j] / m2[i][j];
    return result;
}

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
{
    using Base = MatrixBase<T, N>;
    static FMATH_INLINE FMATH_CONSTEXPR MatrixT inverse(const Base &m);
    static FMATH_INLINE FMATH_CONSTEXPR T determinant(const Base &m);
};

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
    T det = determinant(m);
    FMATH_ASSERT(det != 0);

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
    FMATH_ASSERT(det != 0);

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
    FMATH_ASSERT(det != 0);

    det = 1.0 / det;
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

}
}

#endif