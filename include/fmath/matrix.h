#ifndef _FMATH_MATRIX_H_
#define _FMATH_MATRIX_H_

#include <array>

#include "internal/matrix_base.h"
#include "internal/matrix_traits.h"
#include "common.h"
#include "constants.h"
#include "normal.h"
#include "point.h"
#include "vector.h"

namespace fmath
{

template<typename T, size_t N>
class Matrix : public internal::MatrixBase<T, N>
{
public:
    using ValueType = T;
    using VectorType = Vector<T, N>;
    static constexpr size_t DIMENSION = N;

public:
    using internal::MatrixBase<T, N>::MatrixBase;

    template<typename MatrixU>
    FMATH_CONSTEXPR Matrix(const MatrixU &other);

    template<typename MatrixU>
    FMATH_CONSTEXPR Matrix &operator=(const MatrixU &other);

    FMATH_INLINE FMATH_CONSTEXPR Matrix operator+() const;

    FMATH_INLINE FMATH_CONSTEXPR Matrix operator-() const;

    FMATH_INLINE Matrix &operator+=(const Matrix &other);

    FMATH_INLINE Matrix &operator+=(const ValueType &value);

    FMATH_INLINE Matrix &operator-=(const Matrix &other);

    FMATH_INLINE Matrix &operator-=(const ValueType &value);

    FMATH_INLINE Matrix &operator*=(const ValueType &value);

    FMATH_INLINE Matrix &operator*=(const Matrix &other);

    FMATH_INLINE Matrix &operator/=(const ValueType &value);

    static FMATH_CONSTEXPR Matrix zero();

    static FMATH_CONSTEXPR Matrix identity();
};

namespace internal
{

template<typename T, size_t N>
struct MatrixTraits :
    MatrixTraits_Assign<T, N, Matrix<T, N>>,
    MatrixTraits_Basic<T, N, Matrix<T, N>>,
    MatrixTraits_Compare<T, N>,
    MatrixTraits_Hadamard<T, N, Matrix<T, N>>,
    MatrixTraits_Input<T, N>,
    MatrixTraits_Mul<T, N, Matrix<T, N>>,
    MatrixTraits_Output<T, N>,
    MatrixTraits_Square<T, N, Matrix<T, N>>,
    MatrixTraits_Stringify<T, N>,
    MatrixTraits_VectorMul<T, N, Vector<T, N>>
{};

}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool operator==(const Matrix<T, N> &m1, const Matrix<T, N> &m2)
{
    return internal::MatrixTraits<T, N>::equal(m1, m2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool operator!=(const Matrix<T, N> &m1, const Matrix<T, N> &m2)
{
    return !internal::MatrixTraits<T, N>::equal(m1, m2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool equal(const Matrix<T, N> &m1, const Matrix<T, N> &m2)
{
    return internal::MatrixTraits<T, N>::equal(m1, m2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool notEqual(const Matrix<T, N> &m1, const Matrix<T, N> &m2)
{
    return !equal(m1, m2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool equalEpsilon(const Matrix<T, N> &m1, const Matrix<T, N> &m2, const T &epsilon = constants::Epsilon<T>::value)
{
    return internal::MatrixTraits<T, N>::equalEpsilon(m1, m2, epsilon);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool notEqualEpsilon(const Matrix<T, N> &m1, const Matrix<T, N> &m2, const T &epsilon = constants::Epsilon<T>::value)
{
    return !equalEpsilon(m1, m2, epsilon);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Matrix<T, N> operator+(const Matrix<T, N> &m1, const Matrix<T, N> &m2)
{
    return internal::MatrixTraits<T, N>::add(m1, m2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Matrix<T, N> operator+(const Matrix<T, N> &mat, const T &value)
{
    return internal::MatrixTraits<T, N>::add(mat, value);
};

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Matrix<T, N> operator-(const Matrix<T, N> &m1, const Matrix<T, N> &m2)
{
    return internal::MatrixTraits<T, N>::sub(m1, m2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Matrix<T, N> operator-(const Matrix<T, N> &mat, const T &value)
{
    return internal::MatrixTraits<T, N>::sub(mat, value);
};

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Matrix<T, N> operator*(const Matrix<T, N> &m1, const Matrix<T, N> &m2)
{
    return internal::MatrixTraits<T, N>::mul(m1, m2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Matrix<T, N> operator*(const Matrix<T, N> &mat, const T &value)
{
    return internal::MatrixTraits<T, N>::scalarMul(mat, value);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Matrix<T, N> operator*(const T &value, const Matrix<T, N> &mat)
{
    return internal::MatrixTraits<T, N>::mul(mat, value);
}

template<typename T, size_t N>
typename Matrix<T, N>::VectorType operator*(const Matrix<T, N> &mat, const Vector<T, N> &vec)
{
    return internal::MatrixTraits<T, N>::vectorMul(mat, vec);
}

template<typename T, size_t N>
typename Matrix<T, N>::VectorType operator*(const Vector<T, N> &vec, const Matrix<T, N> &mat)
{
    return internal::MatrixTraits<T, N>::vectorMul(vec, mat);
}

template<typename T, size_t N>
Normal<T, N> operator*(const Normal<T, N> &normal, const Matrix<T, N> &mat)
{
    Matrix<T, N> inv = internal::MatrixTraits<T, N>::inverse(mat);
    return normal * inv;
}

template<typename T, size_t N>
Point<T, N> operator*(const Matrix<T, N> &mat, const Point<T, N> &point)
{
    return internal::MatrixTraits_VectorMul<T, N, Point<T, N>>::vectorMul(mat, point);
}

template<typename T, size_t N>
Point<T, N> operator*(const Point<T, N> &point, const Matrix<T, N> &mat)
{
    return internal::MatrixTraits_VectorMul<T, N, Point<T, N>>::vectorMul(point, mat);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Matrix<T, N> operator/(const Matrix<T, N> &mat, T value)
{
    return internal::MatrixTraits<T, N>::scalarDiv(mat, value);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Matrix<T, N> add(const Matrix<T, N> &m1, const Matrix<T, N> &m2)
{
    return internal::MatrixTraits<T, N>::add(m1, m2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Matrix<T, N> add(const Matrix<T, N> &mat, const T &value)
{
    return internal::MatrixTraits<T, N>::add(mat, value);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Matrix<T, N> sub(const Matrix<T, N> &m1, const Matrix<T, N> &m2)
{
    return internal::MatrixTraits<T, N>::sub(m1, m2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Matrix<T, N> sub(const Matrix<T, N> &mat, const T &value)
{
    return internal::MatrixTraits<T, N>::sub(mat, value);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Matrix<T, N> mul(const Matrix<T, N> &m1, const Matrix<T, N> &m2)
{
    return internal::MatrixTraits<T, N>::mul(m1, m2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Matrix<T, N> mul(const Matrix<T, N> &mat, const T &value)
{
    return internal::MatrixTraits<T, N>::mul(mat, value);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Matrix<T, N> div(const Matrix<T, N> &mat, const T &value)
{
    return internal::MatrixTraits<T, N>::div(mat, value);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Matrix<T, N> hadamardMul(const Matrix<T, N> &m1, const Matrix<T, N> &m2)
{
    return internal::MatrixTraits<T, N>::hadamardMul(m1, m2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Matrix<T, N> hadamardDiv(const Matrix<T, N> &m1, const Matrix<T, N> &m2)
{
    return internal::MatrixTraits<T, N>::hadamardDiv(m1, m2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T determinant(const Matrix<T, N> &mat)
{
    return internal::MatrixTraits<T, N>::determinant(mat);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Matrix<T, N> inverse(const Matrix<T, N> &mat)
{
    return internal::MatrixTraits<T, N>::inverse(mat);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Matrix<T, N> transpose(const Matrix<T, N> &mat)
{
    return internal::MatrixTraits<T, N>::transpose(mat);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR std::string toString(const Matrix<T, N> &mat, uint32 precision = 6)
{
    return internal::MatrixTraits<T, N>::toString(mat, precision);
}

template<typename T, size_t N>
FMATH_INLINE std::ostream &operator<<(std::ostream &output, const Matrix<T, N> &mat)
{
    internal::MatrixTraits<T, N>::write(output, mat);
    return output;
}

template<typename T, size_t N>
FMATH_INLINE std::istream &operator>>(std::istream &input, Matrix<T, N> &mat)
{
    internal::MatrixTraits<T, N>::read(input, mat);
    return input;
}

template<typename T, size_t N>
    template<typename MatrixU>
FMATH_CONSTEXPR Matrix<T, N>::Matrix(const MatrixU &other)
{
    internal::MatrixTraits<T, N>::assign(*this, other);
}

template<typename T, size_t N>
    template<typename MatrixU>
FMATH_CONSTEXPR Matrix<T, N> &Matrix<T, N>::operator=(const MatrixU &other)
{
    internal::MatrixTraits<T, N>::assign(*this, other);
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Matrix<T, N> Matrix<T, N>::operator+() const
{
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Matrix<T, N> Matrix<T, N>::operator-() const
{
    return zero() - (*this);
}

template<typename T, size_t N>
FMATH_INLINE Matrix<T, N> &Matrix<T, N>::operator+=(const Matrix<T, N> &mat)
{
    internal::MatrixTraits<T, N>::addBy(*this, mat);
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE Matrix<T, N> &Matrix<T, N>::operator+=(const ValueType &value)
{
    internal::MatrixTraits<T, N>::addBy(*this, value);
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE Matrix<T, N> &Matrix<T, N>::operator-=(const Matrix<T, N> &mat)
{
    internal::MatrixTraits<T, N>::subBy(*this, mat);
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE Matrix<T, N> &Matrix<T, N>::operator-=(const ValueType &value)
{
    internal::MatrixTraits<T, N>::subBy(*this, value);
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE Matrix<T, N> &Matrix<T, N>::operator*=(const Matrix<T, N> &mat)
{
    *this = (*this) * mat;
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE Matrix<T, N> &Matrix<T, N>::operator*=(const ValueType &value)
{
    internal::MatrixTraits<T, N>::scalarMulBy(*this, value);
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE Matrix<T, N> &Matrix<T, N>::operator/=(const ValueType &value)
{
    internal::MatrixTraits<T, N>::scalarDivBy(*this, value);
    return *this;
}

template<typename T, size_t N>
FMATH_CONSTEXPR Matrix<T, N> Matrix<T, N>::zero()
{
    return Matrix<T, N>();
}

template<typename T, size_t N>
FMATH_CONSTEXPR Matrix<T, N> Matrix<T, N>::identity()
{
    Matrix result;
    for (index_t i = 0; i < DIMENSION; ++i)
        result[i][i] = 1;
    return result;
}

template<typename T>
using Matrix2 = Matrix<T, 2>;

template<typename T>
using Matrix3 = Matrix<T, 3>;

template<typename T>
using Matrix4 = Matrix<T, 4>;

using Matrix2u = Matrix2<uint32>;
using Matrix2i = Matrix2<int32>;
using Matrix2f = Matrix2<float>;
using Matrix2lf = Matrix2<double>;

using Matrix3u = Matrix3<uint32>;
using Matrix3i = Matrix3<int32>;
using Matrix3f = Matrix3<float>;
using Matrix3lf = Matrix3<double>;

using Matrix4u = Matrix4<uint32>;
using Matrix4i = Matrix4<int32>;
using Matrix4f = Matrix4<float>;
using Matrix4lf = Matrix4<double>;

}

#endif