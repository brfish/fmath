#ifndef _FMATH_INTERNAL_COLOR_BASE_H_
#define _FMATH_INTERNAL_COLOR_BASE_H_

#include "color_storage.h"
#include "interfaces.h"

namespace fmath
{
namespace internal
{

template<typename T, size_t N>
struct ColorBase : ColorStorage<T, N>, VectorInterface
{
    using ColorStorage<T, N>::ColorStorage;

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
FMATH_INLINE FMATH_CONSTEXPR size_t ColorBase<T, N>::size() const
{
    return N;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR const T *ColorBase<T, N>::data() const
{
    return this->values.data();
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T *ColorBase<T, N>::data()
{
    return this->values.data();
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR const T &ColorBase<T, N>::get(index_t index) const
{
    FMATH_ASSERT(index >= 0 && index < size());
    return this->values[index];
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T &ColorBase<T, N>::get(index_t index)
{
    FMATH_ASSERT(index >= 0 && index < size());
    return this->values[index];
}

template<typename T, size_t N>
FMATH_INLINE void ColorBase<T, N>::set(index_t index, const T &value)
{
    FMATH_ASSERT(index >= 0 && index < size());
    this->values[index] = value;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR const T &ColorBase<T, N>::operator[](index_t index) const
{
    return this->values[index];
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T &ColorBase<T, N>::operator[](index_t index)
{
    return this->values[index];
}

}
}

#endif