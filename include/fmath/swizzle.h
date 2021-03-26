#ifndef _FMATH_INTERNAL_SWIZZLE_H_
#define _FMATH_INTERNAL_SWIZZLE_H_

#include <type_traits>

#include "internal/vector_traits.h"
#include "common.h"

namespace fmath
{

template<index_t C0, index_t C1, typename VectorT>
auto swizzle(const VectorT &v)
{
    using Traits = internal::VectorTraits_TypeInfo<Vector3f>;
    using ResultType = typename Traits::template VectorType<Traits::ValueType, 2>;

    static_assert(C0 >= 0 && C0 < Traits::SIZE);
    static_assert(C1 >= 0 && C1 < Traits::SIZE);

    return ResultType(v[C0], v[C1]);
}

template<index_t C0, index_t C1, index_t C2, typename VectorT>
auto swizzle(const VectorT &v)
{
    using Traits = internal::VectorTraits_TypeInfo<VectorT>;
    using ResultType = typename Traits::template VectorType<typename Traits::ValueType, 3>;

    static_assert(C0 >= 0 && C0 < Traits::SIZE);
    static_assert(C1 >= 0 && C1 < Traits::SIZE);
    static_assert(C2 >= 0 && C2 < Traits::SIZE);

    return ResultType(v[C0], v[C1], v[C2]);
}

template<index_t C0, index_t C1, index_t C2, index_t C3, typename VectorT>
auto swizzle(const VectorT &v)
{
    using Traits = internal::VectorTraits_TypeInfo<VectorT>;
    using ResultType = typename Traits::template VectorType<typename Traits::ValueType, 4>;

    static_assert(C0 >= 0 && C0 < Traits::SIZE);
    static_assert(C1 >= 0 && C1 < Traits::SIZE);
    static_assert(C2 >= 0 && C2 < Traits::SIZE);
    static_assert(C3 >= 0 && C3 < Traits::SIZE);

    return ResultType(v[C0], v[C1], v[C2], v[C3]);
}

template<Component C0, Component C1, typename VectorT>
auto swizzle(const VectorT &v)
{
    return swizzle<static_cast<index_t>(C0), static_cast<index_t>(C1)>(v);
}

template<Component C0, Component C1, Component C2, typename VectorT>
auto swizzle(const VectorT &v)
{
    return swizzle<static_cast<index_t>(C0), static_cast<index_t>(C1), static_cast<index_t>(C2)>(v);
}

template<Component C0, Component C1, Component C2, Component C3, typename VectorT>
auto swizzle(const VectorT &v)
{
    return swizzle<static_cast<index_t>(C0), static_cast<index_t>(C1), 
        static_cast<index_t>(C2), static_cast<index_t>(C3)>(v);
}

}

#endif