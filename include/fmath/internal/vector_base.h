#ifndef _FMATH_INTERNAL_VECTOR_BASE_H_
#define _FMATH_INTERNAL_VECTOR_BASE_H_

#include "interfaces.h"
#include "vector_storage.h"

namespace fmath
{
namespace internal
{

template<typename T, size_t N>
struct VectorBase : VectorInterface, VectorStorage<T, N>
{
    using VectorStorage<T, N>::VectorStorage;

    explicit VectorBase(const T *data, size_t count);

    template<typename U>
    explicit VectorBase(const VectorBase<U, N - 1> &vec, const T &value);

    template<typename U>
    explicit VectorBase(const T &value, const VectorBase<U, N - 1> &vec);

    FMATH_INLINE FMATH_CONSTEXPR size_t size() const;

    FMATH_INLINE FMATH_CONSTEXPR const T *data() const;

    FMATH_INLINE FMATH_CONSTEXPR T *data();

    FMATH_INLINE FMATH_CONSTEXPR const T &get(index_t index) const;

    FMATH_INLINE FMATH_CONSTEXPR T &get(index_t index);

    FMATH_INLINE void set(index_t index, const T &value);

    FMATH_INLINE FMATH_CONSTEXPR const T &operator[](index_t index) const;

    FMATH_INLINE FMATH_CONSTEXPR T &operator[](index_t index);
};

template<typename T, size_t N>
VectorBase<T, N>::VectorBase(const T *data, size_t count)
{
    memcpy(this->data(), data, sizeof(T) * min(N, count));
}

template<typename T, size_t N>
    template<typename U>
VectorBase<T, N>::VectorBase(const VectorBase<U, N - 1> &vec, const T &value)
{
    static_assert(N >= 1);
    memcpy(this->data(), vec.data(), sizeof(T) * (N - 1));
    this->values[N - 1] = value;
}

template<typename T, size_t N>
    template<typename U>
VectorBase<T, N>::VectorBase(const T &value, const VectorBase<U, N - 1> &vec)
{
    static_assert(N >= 1);
    this->values[0] = value;
    memcpy(this->data() + sizeof(T), vec.data(), sizeof(T) * (N - 1));
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR size_t VectorBase<T, N>::size() const
{
    return N;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR const T *VectorBase<T, N>::data() const
{
    return this->values.data();
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T *VectorBase<T, N>::data()
{
    return this->values.data();
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR const T &VectorBase<T, N>::get(index_t index) const
{
    FMATH_ASSERT(index >= 0 && index < N);
    return this->values[index];
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T &VectorBase<T, N>::get(index_t index)
{
    FMATH_ASSERT(index >= 0 && index < N);
    return this->values[index];
}

template<typename T, size_t N>
FMATH_INLINE void VectorBase<T, N>::set(index_t index, const T &value)
{
    FMATH_ASSERT(index >= 0 && index < N);
    this->values[index] = value;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR const T &VectorBase<T, N>::operator[](index_t index) const
{
    return this->values[index];
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T &VectorBase<T, N>::operator[](index_t index)
{
    return this->values[index];
}

}
}

#endif