#ifndef _FMATH_SWIZZLE_H_
#define _FMATH_SWIZZLE_H_

#include <type_traits>

#include "internal/vector_traits.h"
#include "common.h"

namespace fmath
{

namespace internal
{

template<index_t C0, index_t C1>
FMATH_ALWAYS_INLINE FMATH_CONSTEXPR bool indicesUnique()
{
    return C0 != C1;
}

template<index_t C0, index_t C1, index_t C2>
FMATH_ALWAYS_INLINE FMATH_CONSTEXPR bool indicesUnique()
{
    constexpr bool c[3] { false };
    c[C0] = true;
    c[C1] = true;
    c[C2] = true;
    return c[0] && c[1] && c[2];
}

template<index_t C0, index_t C1, index_t C2, index_t C3>
FMATH_ALWAYS_INLINE FMATH_CONSTEXPR bool indicesUnique()
{
    constexpr bool c[4] { false };
    c[C0] = true;
    c[C1] = true;
    c[C2] = true;
    c[C3] = true;
    return c[0] && c[1] && c[2] && c[3];
}

}

template<index_t C0, index_t C1, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR auto swizzle(const VectorT &v)
{
    using Traits = internal::VectorTraits_TypeInfo<VectorT>;
    using ResultType = typename Traits::template VectorType<typename Traits::ValueType, 2>;

    static_assert(C0 >= 0 && C0 < Traits::DIMENSION, "The vector doesn't have the component \"C0\"");
    static_assert(C1 >= 0 && C1 < Traits::DIMENSION, "The vector doesn't have the component \"C1\"");

    return ResultType(v[C0], v[C1]);
}

template<index_t C0, index_t C1, index_t C2, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR auto swizzle(const VectorT &v)
{
    using Traits = internal::VectorTraits_TypeInfo<VectorT>;
    using ResultType = typename Traits::template VectorType<typename Traits::ValueType, 3>;

    static_assert(C0 >= 0 && C0 < Traits::DIMENSION, "The vector doesn't have the component \"C0\"");
    static_assert(C1 >= 0 && C1 < Traits::DIMENSION, "The vector doesn't have the component \"C1\"");
    static_assert(C2 >= 0 && C2 < Traits::DIMENSION, "The vector doesn't have the component \"C2\"");

    return ResultType(v[C0], v[C1], v[C2]);
}

template<index_t C0, index_t C1, index_t C2, index_t C3, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR auto swizzle(const VectorT &v)
{
    using Traits = internal::VectorTraits_TypeInfo<VectorT>;
    using ResultType = typename Traits::template VectorType<typename Traits::ValueType, 4>;

    static_assert(C0 >= 0 && C0 < Traits::DIMENSION, "The vector doesn't have the component \"C0\"");
    static_assert(C1 >= 0 && C1 < Traits::DIMENSION, "The vector doesn't have the component \"C1\"");
    static_assert(C2 >= 0 && C2 < Traits::DIMENSION, "The vector doesn't have the component \"C2\"");
    static_assert(C3 >= 0 && C3 < Traits::DIMENSION, "The vector doesn't have the component \"C3\"");

    return ResultType(v[C0], v[C1], v[C2], v[C3]);
}

template<Component C0, Component C1, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR auto swizzle(const VectorT &v)
{
    constexpr uint8 i0 = static_cast<uint8>(C0);
    constexpr uint8 i1 = static_cast<uint8>(C1);

    static_assert((i0 & 0xF0) == (i1 & 0xF0), "It is not a valid swizzle mask");

    constexpr index_t c0 = i0 & 0x0F;
    constexpr index_t c1 = i1 & 0x0F;

    return swizzle<c0, c1>(v);
}

template<Component C0, Component C1, Component C2, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR auto swizzle(const VectorT &v)
{
    constexpr uint8 i0 = static_cast<uint8>(C0);
    constexpr uint8 i1 = static_cast<uint8>(C1);
    constexpr uint8 i2 = static_cast<uint8>(C2);

    static_assert((i0 & 0xF0) == (i1 & 0xF0) && (i1 & 0xF0) == (i2 & 0xF0), 
        "It is not a valid swizzle mask");

    constexpr index_t c0 = i0 & 0x0F;
    constexpr index_t c1 = i1 & 0x0F;
    constexpr index_t c2 = i2 & 0x0F;

    return swizzle<c0, c1, c2>(v);
}

template<Component C0, Component C1, Component C2, Component C3, typename VectorT>
FMATH_INLINE FMATH_CONSTEXPR auto swizzle(const VectorT &v)
{
    constexpr uint8 i0 = static_cast<uint8>(C0);
    constexpr uint8 i1 = static_cast<uint8>(C1);
    constexpr uint8 i2 = static_cast<uint8>(C2);
    constexpr uint8 i3 = static_cast<uint8>(C3);

    static_assert((i0 & 0xF0) == (i1 & 0xF0) && (i1 & 0xF0) == (i2 & 0xF0) && (i2 & 0xF0) == (i3 & 0xF0),
        "It is not a valid swizzle mask");

    constexpr index_t c0 = i0 & 0x0F;
    constexpr index_t c1 = i1 & 0x0F;
    constexpr index_t c2 = i2 & 0x0F;
    constexpr index_t c3 = i3 & 0x0F;
    
    return swizzle<c0, c1, c2, c3>(v);
}

template<index_t C0, index_t C1, typename VectorT, typename VectorU>
FMATH_INLINE void swizzleSet(VectorT &v, const VectorU &new_v)
{
    static_assert(VectorU::DIMENSION == 2, "The dimension of \"VectorU\" must be 2");
    static_assert(internal::indicesUnique<C0, C1>(), "The component indices must be different from each other");

    v[C0] = new_v[0];
    v[C1] = new_v[1];
}

template<index_t C0, index_t C1, index_t C2, typename VectorT, typename VectorU>
FMATH_INLINE void swizzleSet(VectorT &v, const VectorU &new_v)
{
    static_assert(VectorU::DIMENSION == 3, "The dimension of \"VectorU\" must be 3");
    static_assert(internal::indicesUnique<C0, C1, C2>(), "The component indices must be different from each other");

    v[C0] = new_v[0];
    v[C1] = new_v[1];
    v[C2] = new_v[2];
}

template<index_t C0, index_t C1, index_t C2, index_t C3, typename VectorT, typename VectorU>
FMATH_INLINE void swizzleSet(VectorT &v, const VectorU &new_v)
{
    static_assert(VectorU::DIMENSION == 4, "The dimension of \"VectorU\" must be 4");
    static_assert(internal::indicesUnique<C0, C1, C2, C3>(), "The component indices must be different from each other");

    v[C0] = new_v[0];
    v[C1] = new_v[1];
    v[C2] = new_v[2];
    v[C3] = new_v[3];
}

template<Component C0, Component C1, typename VectorT, typename VectorU>
FMATH_INLINE void swizzleSet(VectorT &v, const VectorU &new_v)
{
    constexpr uint8 i0 = static_cast<uint8>(C0);
    constexpr uint8 i1 = static_cast<uint8>(C1);

    static_assert((i0 & 0xF0) == (i1 & 0xF0), "It is not a valid swizzle mask");

    constexpr index_t c0 = i0 & 0x0F;
    constexpr index_t c1 = i1 & 0x0F;

    return swizzleSet<c0, c1>(v, new_v);
}

template<Component C0, Component C1, Component C2, typename VectorT, typename VectorU>
FMATH_INLINE void swizzleSet(VectorT &v, const VectorU &new_v)
{
    constexpr uint8 i0 = static_cast<uint8>(C0);
    constexpr uint8 i1 = static_cast<uint8>(C1);
    constexpr uint8 i2 = static_cast<uint8>(C2);

    static_assert((i0 & 0xF0) == (i1 & 0xF0) && (i1 & 0xF0) == (i2 & 0xF0), 
        "It is not a valid swizzle mask");

    constexpr index_t c0 = i0 & 0x0F;
    constexpr index_t c1 = i1 & 0x0F;
    constexpr index_t c2 = i2 & 0x0F;

    return swizzleSet<c0, c1, c2>(v, new_v);
}

template<Component C0, Component C1, Component C2, Component C3, typename VectorT, typename VectorU>
FMATH_INLINE void swizzleSet(VectorT &v, const VectorU &new_v)
{
    constexpr uint8 i0 = static_cast<uint8>(C0);
    constexpr uint8 i1 = static_cast<uint8>(C1);
    constexpr uint8 i2 = static_cast<uint8>(C2);
    constexpr uint8 i3 = static_cast<uint8>(C3);

    static_assert((i0 & 0xF0) == (i1 & 0xF0) && (i1 & 0xF0) == (i2 & 0xF0) && (i2 & 0xF0) == (i3 & 0xF0),
        "It is not a valid swizzle mask");

    constexpr index_t c0 = i0 & 0x0F;
    constexpr index_t c1 = i1 & 0x0F;
    constexpr index_t c2 = i2 & 0x0F;
    constexpr index_t c3 = i3 & 0x0F;
    
    return swizzleSet<c0, c1, c2, c3>(v, new_v);
}

}
#endif