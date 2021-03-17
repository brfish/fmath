#ifndef _FMATH_INTERNAL_MATRIX_BASE_H_
#define _FMATH_INTERNAL_MATRIX_BASE_H_

#include "internal/matrix_storage.h"
#include "common.h"
#include "compile_config.h"
#include "functions.h"

namespace fmath
{
namespace internal
{

template<typename T, size_t N>
struct MatrixBase : internal::MatrixStorage<T, N>
{
    using internal::MatrixStorage<T, N>::MatrixStorage;

    explicit MatrixBase(const T *data, size_t count);

    FMATH_INLINE FMATH_CONSTEXPR size_t dimension() const;

    FMATH_INLINE FMATH_CONSTEXPR const T *data() const;

    FMATH_INLINE FMATH_CONSTEXPR T *data();

    FMATH_INLINE FMATH_CONSTEXPR const T &get(index_t i, index_t j) const;

    FMATH_INLINE T &get(index_t i, index_t j);

    FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> col(index_t index) const;

    FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> row(index_t index) const;
    
    FMATH_INLINE void set(index_t i, index_t j, const T &value);

    FMATH_INLINE void setCol(index_t index, const Vector<T, N> &v);

    FMATH_INLINE void setRow(index_t index, const Vector<T, N> &v);

    FMATH_INLINE FMATH_CONSTEXPR const Vector<T, N> &operator[](index_t index) const;

    FMATH_INLINE Vector<T, N> &operator[](index_t index);

    FMATH_INLINE void fill(const T &value);
};

template<typename T, size_t N>
MatrixBase<T, N>::MatrixBase(const T *data, size_t count)
{
    memcpy(this->data(), data, sizeof(T) * min(N * N, count));
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR size_t MatrixBase<T, N>::dimension() const
{
    return N;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR const T *MatrixBase<T, N>::data() const
{
    return &this->values[0][0];
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T *MatrixBase<T, N>::data()
{
    return &this->values[0][0];
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR const T &MatrixBase<T, N>::get(index_t i, index_t j) const
{
    return this->values[i][j];
}

template<typename T, size_t N>
FMATH_INLINE T &MatrixBase<T, N>::get(index_t i, index_t j)
{
    return this->values[i][j];
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> MatrixBase<T, N>::col(index_t index) const
{
    return this->values[index];
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> MatrixBase<T, N>::row(index_t index) const
{
    Vector<T, N> v;
    for (index_t i = 0; i < N; ++i)
        v[i] = this->values[i][index];
    return v;
}

template<typename T, size_t N>
FMATH_INLINE void MatrixBase<T, N>::set(index_t i, index_t j, const T &value)
{
    this->values[i][j] = value;
}

template<typename T, size_t N>
FMATH_INLINE void MatrixBase<T, N>::setCol(index_t index, const Vector<T, N> &v)
{
    this->values[index] = v;
}

template<typename T, size_t N>
FMATH_INLINE void MatrixBase<T, N>::setRow(index_t index, const Vector<T, N> &v)
{
    for (index_t i = 0; i < N; ++i)
        this->values[i][index] = v[i];
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR const Vector<T, N> &MatrixBase<T, N>::operator[](index_t index) const
{
    return this->values[index];
}

template<typename T, size_t N>
FMATH_INLINE Vector<T, N> &MatrixBase<T, N>::operator[](index_t index)
{
    return this->values[index];
}


template<typename T, size_t N>
FMATH_INLINE void MatrixBase<T, N>::fill(const T &value)
{
    for (index_t i = 0; i < N; ++i)
        for (index_t j = 0; j < N; ++j)
            this->values[i][j] = value;
}

}
}

#endif