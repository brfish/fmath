#ifndef _FMATH_INTERNAL_VECTOR_BASE_H_
#define _FMATH_INTERNAL_VECTOR_BASE_H_

#include "internal/vector_storage.h"

namespace fmath
{
namespace internal
{

template<typename T, size_t N>
struct VectorBase : VectorStorage<T, N>
{
    using ValueType = T;
    static constexpr size_t SIZE = N;

    using VectorStorage<T, N>::VectorStorage;

    explicit VectorBase(const ValueType *data, size_t count);

    FMATH_INLINE FMATH_CONSTEXPR size_t size() const;

    FMATH_INLINE FMATH_CONSTEXPR const ValueType *data() const;

    FMATH_INLINE FMATH_CONSTEXPR ValueType *data();

    FMATH_INLINE FMATH_CONSTEXPR const ValueType &get(index_t index) const;

    FMATH_INLINE ValueType &get(index_t index);

    FMATH_INLINE void set(index_t index, const ValueType &value);

    FMATH_INLINE FMATH_CONSTEXPR const ValueType &operator[](index_t index) const;

    FMATH_INLINE ValueType &operator[](index_t index);
};

template<typename T, size_t N>
VectorBase<T, N>::VectorBase(const ValueType *data, size_t count)
{
    memcpy(this->data(), data, sizeof(ValueType) * min(SIZE, count));
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR size_t VectorBase<T, N>::size() const
{
    return SIZE;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR const typename VectorBase<T, N>::ValueType *VectorBase<T, N>::data() const
{
    return this->values.data();
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR typename VectorBase<T, N>::ValueType *VectorBase<T, N>::data()
{
    return this->values.data();
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR const typename VectorBase<T, N>::ValueType &VectorBase<T, N>::get(index_t index) const
{
    return this->values[index];
}

template<typename T, size_t N>
FMATH_INLINE typename VectorBase<T, N>::ValueType &VectorBase<T, N>::get(index_t index)
{
    return this->values[index];
}

template<typename T, size_t N>
FMATH_INLINE void VectorBase<T, N>::set(index_t index, const ValueType &value)
{
    this->values[index] = value;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR const typename VectorBase<T, N>::ValueType &VectorBase<T, N>::operator[](index_t index) const
{
    return this->values[index];
}

template<typename T, size_t N>
FMATH_INLINE typename VectorBase<T, N>::ValueType &VectorBase<T, N>::operator[](index_t index)
{
    return this->values[index];
}

}
}

#endif