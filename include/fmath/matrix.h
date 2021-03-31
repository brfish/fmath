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

    template<typename U, size_t M, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
    Matrix(const Matrix<U, M> &other);

    template<typename U, size_t M, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
    Matrix &operator=(const Matrix<U, M> &other);

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
    template<typename U, size_t M, typename>
Matrix<T, N>::Matrix(const Matrix<U, M> &other)
{
    constexpr size_t REAL = min(N, M);
    for (index_t i = 0; i < REAL; ++i)
        for (index_t j = 0; j < REAL; ++j)
            (*this)[i][j] = static_cast<ValueType>(other[i][j]);
}

template<typename T, size_t N>
    template<typename U, size_t M, typename>
Matrix<T, N> &Matrix<T, N>::operator=(const Matrix<U, M> &other)
{
    constexpr size_t REAL = min(M, N);
    for (index_t i = 0; i < REAL; ++i)
        for (index_t j = 0; j < REAL; ++j)
            (*this)[i][j] = static_cast<ValueType>(other.data[i][j]);
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

template<Axis A, typename T>
FMATH_INLINE FMATH_CONSTEXPR Matrix4<T> rotate(const T &angle)
{
    const T cost = cos(angle); 
    const T sint = sin(angle);
    const T one = static_cast<T>(1);
    const T zero = static_cast<T>(0);

    if constexpr (A == Axis::X)
    {
        return Matrix4<T>(
            one, zero, zero, zero,
            zero, cost, sint, zero,
            zero, -sint, cost, zero,
            zero, zero, zero, one
        );
    }
    else if constexpr (A == Axis::Y)
    {
        return Matrix4<T>(
            cost, zero, -sint, zero,
            zero, one, zero, zero,
            sint, zero, cost, zero,
            zero, zero, zero, one
        );
    }
    else
    {
        return Matrix4<T>(
            cost, sint, zero, zero,
            -sint, cost, zero, zero,
            zero, zero, one, zero,
            zero, zero, zero, one
        );
    }
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Matrix4<T> rotate(const Vector3<T> &axis, const T &angle)
{
    Vector3<T> n = normalize(axis);
    const T cost = cos(angle);
    const T sint = sin(angle);
    const T minus_cost = static_cast<T>(1) - cost;
    const T factor_x = n[0] * minus_cost;
    const T factor_y = n[1] * minus_cost;
    const T factor_z = n[2] * minus_cost;

    Matrix4<T> r;

    r[0][0] = factor_x * n[0] + cost;
    r[0][1] = factor_x * n[1] + sint * n[2];
    r[0][2] = factor_x * n[2] - sint * n[1];

    r[1][0] = factor_y * n[0] - sint * n[2];
    r[1][1] = factor_y * n[1] + cost;
    r[1][2] = factor_y * n[2] + sint * n[0];

    r[2][0] = factor_z * n[0] + sint * n[1];
    r[2][1] = factor_z * n[1] - sint * n[0];
    r[2][2] = factor_z * n[2] + cost;

    r[3][3] = static_cast<T>(1);

    return r;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Matrix4<T> scale(const Vector3<T> &factors)
{
    T one = static_cast<T>(1);
    T zero = static_cast<T>(0);

    return Matrix4<T>(
        factors[0], zero, zero, zero,
        zero, factors[1], zero, zero,
        zero, zero, factors[2], zero,
        zero, zero, zero, one
    );
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Matrix4<T> scale(const T &x, const T &y, const T &z)
{
    return scale(Vector3f(x, y, z));
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Matrix4<T> scale(const T &uniform_factor)
{
    return scale(Vector3f(uniform_factor, uniform_factor, uniform_factor));
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Matrix4<T> scale(const Vector3<T> &axis, const T &factor)
{
    Vector3<T> n = normalize(axis);
    const T factor_x = n[0] * (factor - 1);
    const T factor_y = n[1] * (factor - 1);
    const T factor_z = n[2] * (factor - 1);

    Matrix4<T> result;

    result[0][0] = factor_x * n[0] + 1;
    result[0][1] = factor_y * n[0];
    result[0][2] = factor_z * n[0];

    result[1][0] = factor_x * n[1];
    result[1][1] = factor_y * n[1] + 1;
    result[1][2] = factor_z * n[1];

    result[2][0] = factor_x * n[2];
    result[2][1] = factor_z * n[2];
    result[2][2] = factor_z * n[2] + 1;

    result[3][3] = static_cast<T>(1);

    return result;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Matrix4<T> translate(const Vector3<T> &translation)
{
    const T one = static_cast<T>(1);
    const T zero = static_cast<T>(0);

    return Matrix4<T>(
        one, zero, zero, zero,
        zero, one, zero, zero,
        zero, zero, one, zero,
        translation[0], translation[1], translation[2], one
    );
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Matrix4<T> translate(const T &x, const T &y, const T &z)
{
    return translate(Vector3<T>(x, y, z));
}

template<Axis A, typename T>
FMATH_INLINE FMATH_CONSTEXPR Matrix4<T> shear(const T &factor_s, const T &factor_t)
{
    const T one = static_cast<T>(1);
    const T zero = static_cast<T>(0);

    if constexpr (A == Axis::X)
    {
        return Matrix4<T>(
            one, zero, zero, zero,
            factor_s, one, zero, zero,
            factor_t, zero, one, zero,
            zero, zero, zero, one
        );
    }
    else if constexpr (A == Axis::Y)
    {
        return Matrix4<T>(
            one, factor_s, zero, zero,
            zero, one, zero, zero,
            zero, factor_t, one, zero,
            zero, zero, zero, one
        );
    }
    else
    {
        return Matrix4<T>(
            one, zero, factor_s, zero,
            zero, one, factor_t, zero,
            zero, zero, one, zero,
            zero, zero, zero, one
        );
    }
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Matrix4<T> shear(const Vector3<T> &axis, const T &factor)
{
    Vector3<T> &n = normalize(axis);
    const T factor_x = n[0] * (factor - 1);
    const T factor_y = n[1] * (factor - 1);
    const T factor_z = n[2] * (factor - 1);

    Matrix4<T> r;
    Vector4<T> r0, r1, r2, r3;

    r[0][0] = factor_x * n[0] + 1;
    r[0][1] = factor_y * n[0];
    r[0][2] = factor_z * n[0];

    r[1][0] = factor_x * n[1];
    r[1][1] = factor_y * n[1] + 1;
    r[1][2] = factor_z * n[1];

    r[2][0] = factor_x * n[2];
    r[2][1] = factor_z * n[2];
    r[2][2] = factor_z * n[2] + 1;

    r[3][3] = static_cast<T>(1);

    return r;
}

template<typename T>
Matrix4<T> orthographic(const T &left, const T &right, const T &bottom, const T &top,
    const T &near, const T &far)
{
    const T zero = static_cast<T>(0);
    const T one = static_cast<T>(1);
    const T two = static_cast<T>(2);

    return Matrix4<T>(
        two / (right - left), zero, zero, zero,
        zero, two / (top - bottom), zero, zero,
        zero, zero, two / (near - far), zero,
        (right + left) / (left - right), (top + bottom) / (bottom - top), (near + far) / (far - near), one
    );
}

template<typename T>
Matrix4<T> perspective(const T &left, const T &right, const T &bottom, const T &top,
    const T &near, const T &far)
{
    const T zero = static_cast<T>(0);
    const T one = static_cast<T>(1);
    const T two = static_cast<T>(2);
    const T two_n = two * near;

    return Matrix4<T>(
        two * near / (right - left), zero, zero, zero,
        zero, two_n / (top - bottom), zero, zero,
        (right + left) / (right - left), (top + bottom) / (top - bottom), (far + near) / (near - far), -one,
        zero, zero, two_n * far / (near - far), zero
    );
}

template<typename T>
Matrix4<T> perspective(const T &fovy, const T &aspect, const T &near, const T &far)
{
    const T zero = static_cast<T>(0);
    const T one = static_cast<T>(1);
    const T two = static_cast<T>(2);

    const T tanv = tan(fovy / two);

    return Matrix4<T>(
        one / (aspect * tanv), zero, zero, zero,
        zero, one / tanv, zero, zero,
        zero, zero, (near + far) / (near - far), -one,
        zero, zero, (two * far * near) / (near - far), zero
    );
}

}

#endif