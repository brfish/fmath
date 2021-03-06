#ifndef _FMATH_VECTOR_H_
#define _FMATH_VECTOR_H_

#include <ostream>
#include <type_traits>

#include "internal/vector_base.h"
#include "internal/vector_traits.h"
#include "common.h"
#include "constants.h"
#include "math_common_functions.h"

namespace fmath
{

template<typename T, size_t N>
class Vector : public internal::VectorBase<T, N>
{
public:
    using ValueType = T;
    static constexpr size_t DIMENSION = N;

public:
    using internal::VectorBase<T, N>::VectorBase;

    template<typename VectorU>
    FMATH_CONSTEXPR Vector(const VectorU &other);

    template<typename VectorU>
    FMATH_CONSTEXPR Vector &operator=(const VectorU &other);

    FMATH_INLINE FMATH_CONSTEXPR Vector operator+() const;

    FMATH_INLINE FMATH_CONSTEXPR Vector operator-() const;

    FMATH_INLINE Vector &operator+=(const Vector &other);

    FMATH_INLINE Vector &operator+=(const ValueType &value);

    FMATH_INLINE Vector &operator-=(const Vector &other);

    FMATH_INLINE Vector &operator-=(const ValueType &value);

    FMATH_INLINE Vector &operator*=(const ValueType &value);

    FMATH_INLINE Vector &operator/=(const ValueType &value);

    static FMATH_CONSTEXPR Vector zero();
};

namespace internal
{

template<typename T, size_t N>
struct VectorTraits_TypeInfo<Vector<T, N>>
{
    template<typename U, size_t M>
    using VectorType = Vector<U, M>;

    using ValueType = T;

    static constexpr size_t DIMENSION = N;
};

template<typename T, size_t N>
struct VectorTraits : 
    VectorTraits_Add<T, N, Vector<T, N>>,
    VectorTraits_Assign<T, N, Vector<T, N>>,
    VectorTraits_Clamp<T, N, Vector<T, N>>,
    VectorTraits_Compare<T, N>,
    VectorTraits_ComponentWise<T, N, Vector<T, N>>,
    VectorTraits_Constants<T, N, Vector<T, N>>,
    VectorTraits_Dot<T, N>,
    VectorTraits_Hadamard<T, N, Vector<T, N>>,
    VectorTraits_Input<T, N>,
    VectorTraits_Norm<T, N>,
    VectorTraits_Output<T, N>,
    VectorTraits_Scale<T, N, Vector<T, N>>,
    VectorTraits_Stringify<T, N>
{};

}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool operator==(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return internal::VectorTraits<T, N>::equal(v1, v2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool operator!=(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return !internal::VectorTraits<T, N>::equal(v1, v2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool operator<(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return internal::VectorTraits<T, N>::less(v1, v2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool operator>(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return internal::VectorTraits<T, N>::greater(v1, v2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool operator<=(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return internal::VectorTraits<T, N>::lessOrEqual(v1, v2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool operator>=(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return internal::VectorTraits<T, N>::greaterOrEqual(v1, v2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool equal(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return internal::VectorTraits<T, N>::equal(v1, v2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool notEqual(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return !equal(v1, v2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool equalEpsilon(const Vector<T, N> &v1, const Vector<T, N> &v2, const T epsilon = constants::Epsilon<T>::value)
{
    return internal::VectorTraits<T, N>::equalEpsilon(v1, v2, epsilon);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool notEqualEpsilon(const Vector<T, N> &v1, const Vector<T, N> &v2, const T &epsilon = constants::Epsilon<T>::value)
{
    return !equalEpsilon(v1, v2, epsilon);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool less(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return v1 < v2;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool greater(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return v1 > v2;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool lessOrEqual(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return v1 <= v2;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR bool greaterOrEqual(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return v1 >= v2;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T minComponent(const Vector<T, N> &v)
{
    return internal::VectorTraits<T, N>::minComponent(v);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T maxComponent(const Vector<T, N> &v)
{
    return internal::VectorTraits<T, N>::maxComponent(v);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> operator+(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return internal::VectorTraits<T, N>::add(v1, v2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> operator+(const Vector<T, N> &vec, const T &value)
{
    return internal::VectorTraits<T, N>::add(vec, value);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> operator-(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return internal::VectorTraits<T, N>::sub(v1, v2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> operator-(const Vector<T, N> &vec, const T &value)
{
    return internal::VectorTraits<T, N>::sub(vec, value);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T operator*(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return internal::VectorTraits<T, N>::dot(v1, v2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> operator*(const Vector<T, N> &vec, const T &value)
{
    return internal::VectorTraits<T, N>::mul(vec, value);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> operator*(T value, const Vector<T, N> &vec)
{
    return internal::VectorTraits<T, N>::mul(vec, value);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> operator/(const Vector<T, N> &vec, const T &value)
{
    return internal::VectorTraits<T, N>::div(vec, value);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> add(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return v1 + v2;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> add(const Vector<T, N> &vec, const T &value)
{
    return vec + value;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> sub(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return v1 - v2;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> sub(const Vector<T, N> &vec, const T &value)
{
    return vec - value;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> mul(const Vector<T, N> &vec, const T &value)
{
    return vec * value;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> div(const Vector<T, N> &vec, const T &value)
{
    return vec / value;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T dot(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return internal::VectorTraits<T, N>::dot(v1, v2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T absDot(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return abs(dot(v1, v2));
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> hadamardMul(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return internal::VectorTraits<T, N>::hadamardMul(v1, v2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> hadamardDiv(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return internal::VectorTraits<T, N>::hadamardDiv(v1, v2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T length2(const Vector<T, N> &vec)
{
    return internal::VectorTraits<T, N>::length2(vec);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T length(const Vector<T, N> &vec)
{
    static_assert(std::is_floating_point_v<T>);
    return sqrt(length2(vec));
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> normalize(const Vector<T, N> &vec)
{
    static_assert(std::is_floating_point_v<T>);
    return internal::VectorTraits<T, N>::div(vec, length(vec));
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T cross(const Vector<T, 2> &v1, const Vector<T, 2> &v2)
{
    return v1.x * v2.y - v1.y * v2.x;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, 3> cross(const Vector<T, 3> &v1, const Vector<T, 3> &v2)
{
    return Vector<T, 3>(v1[1] * v2[2] - v1[2] * v2[1],
        v1[2] * v2[0] - v1[0] * v2[2],
        v1[0] * v2[1] - v1[1] * v2[0]
    );
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR float angle(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return acos(dot(normalize(v1), normalize(v2)));
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> reflect(const Vector<T, N> &incident, const Vector<T, N> &normal)
{
    return incident - static_cast<T>(2) * (normal * incident) * normal;
}

// See https://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf
template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> refract(const Vector<T, N> &incident, const Vector<T, N> &normal, const T &n)
{
    T cosi = -(incident * normal);
    T sint2 = n * n * (static_cast<T>(1) - cosi * cosi);

    if (sint2 <= static_cast<T>(1))
        return Vector<T, N>::zero();

    T cost = sqrt(static_cast<T>(1) - sint2);
    return n * incident + (n * cosi - cost) * normal;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> refract(const Vector<T, N> &incident, const Vector<T, N> &normal, 
    const T &n1, const T &n2)
{
    return refract(incident, normal, n1 / n2);
}

// See https://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf
template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR T refractance(const Vector<T, N> &incident, const Vector<T, N> &normal,
    const T &n1, const T &n2)
{
    T n = n1 / n2;
    T cosi = -(incident * normal);
    T sint2 = n * n * (static_cast<T>(1) - cosi * cosi);

    if (sint2 > static_cast<T>(1))
        return static_cast<T>(1);

    T cost = sqrt(static_cast<T>(1) - sint2);

    T perpendicular = (n1 * cosi - n2 * cost) / (n1 * cosi + n2 * cost);
    T parallel = (n2 * cosi - n1 * cost) / (n2 * cosi + n1 * cost);

    return (perpendicular * perpendicular + parallel * parallel) / static_cast<T>(2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> halfway(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return normalize(v1 + v2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> opposite(const Vector<T, N> &v)
{
    return -v;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR std::string toString(const Vector<T, N> &vec, uint32 precision = 6)
{
    return internal::VectorTraits<T, N>::toString(vec, precision);
}

template<typename T, size_t N>
FMATH_INLINE std::ostream &operator<<(std::ostream &output, const Vector<T, N> &vec)
{
    internal::VectorTraits<T, N>::write(output, vec);
    return output;
}

template<typename T, size_t N>
FMATH_INLINE std::istream &operator>>(std::istream &input, Vector<T, N> &vec)
{
    internal::VectorTraits<T, N>::read(input, vec);
    return input;
}

template<typename T, size_t N>
    template<typename VectorU>
FMATH_CONSTEXPR Vector<T, N>::Vector(const VectorU &other)
    :   Vector()
{
    internal::VectorTraits<T, N>::template assign(*this, other);
}

template<typename T, size_t N>
    template<typename VectorU>
FMATH_CONSTEXPR Vector<T, N> &Vector<T, N>::operator=(const VectorU &other)
{
    internal::VectorTraits<T, N>::template assign(*this, other);
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> Vector<T, N>::operator+() const
{
    return Vector(*this);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> Vector<T, N>::operator-() const
{
    return zero() - (*this);
}

template<typename T, size_t N>
FMATH_INLINE Vector<T, N> &Vector<T, N>::operator+=(const Vector &other)
{
    *this = internal::VectorTraits<T, N>::add(*this, other);
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE Vector<T, N> &Vector<T, N>::operator+=(const ValueType &value)
{
    *this = internal::VectorTraits<T, N>::add(*this, value);
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE Vector<T, N> &Vector<T, N>::operator-=(const Vector &other)
{
    *this = internal::VectorTraits<T, N>::sub(*this, other);
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE Vector<T, N> &Vector<T, N>::operator*=(const ValueType &value)
{
    *this = internal::VectorTraits<T, N>::mul(*this, value);
    return *this;
}

template<typename T, size_t N>
FMATH_INLINE Vector<T, N> &Vector<T, N>::operator/=(const ValueType &value)
{
    *this = internal::VectorTraits<T, N>::div(*this, value);
    return *this;
}

template<typename T, size_t N>
FMATH_CONSTEXPR Vector<T, N> Vector<T, N>::zero()
{
    return Vector();
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> clamp(const Vector<T, N> &vec, const Vector<T, N> &minv, const Vector<T, N> &maxv)
{
    return internal::VectorTraits<T, N>::clamp(vec, minv, maxv);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> clamp(const Vector<T, N> &vec, const T &minv, const T &maxv)
{
    return internal::VectorTraits<T, N>::clamp(vec, minv, maxv);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> lerp(const Vector<T, N> &v1, const Vector<T, N> &v2, const T &t)
{
    return v1 + (v2 - v1) * t;
};

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> componentWiseMin(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return internal::VectorTraits<T, N>::componentWiseMin(v1, v2);
}

template<typename T, size_t N>
FMATH_INLINE FMATH_CONSTEXPR Vector<T, N> componentWiseMax(const Vector<T, N> &v1, const Vector<T, N> &v2)
{
    return internal::VectorTraits<T, N>::componentWiseMax(v1, v2);
}

namespace constants
{

template<typename T, size_t N>
struct MinValue<Vector<T, N>>
{
    static constexpr Vector<T, N> value = internal::VectorTraits<T, N>::MIN_VALUE;
};

template<typename T, size_t N>
struct MaxValue<Vector<T, N>>
{
    static constexpr Vector<T, N> value = internal::VectorTraits<T, N>::MAX_VALUE;
};

}

template<typename T>
using Vector2 = Vector<T, 2>;

template<typename T>
using Vector3 = Vector<T, 3>;

template<typename T>
using Vector4 = Vector<T, 4>;

using Vector2u  = Vector2<uint32>;
using Vector2i  = Vector2<int32>;
using Vector2f  = Vector2<float>;
using Vector2lf = Vector2<double>;

using Vector3u  = Vector3<uint32>;
using Vector3i  = Vector3<int32>;
using Vector3f  = Vector3<float>;
using Vector3lf = Vector3<double>;

using Vector4u  = Vector4<uint32>;
using Vector4i  = Vector4<int32>;
using Vector4f  = Vector4<float>;
using Vector4lf = Vector4<double>;

template<typename T>
inline constexpr Vector2<T> AXIS2D_X = internal::VectorTraits<T, 2>::UNIT_X;

template<typename T>
inline constexpr Vector2<T> AXIS2D_Y = internal::VectorTraits<T, 2>::UNIT_Y;

template<typename T>
inline constexpr Vector3<T> AXIS3D_X = internal::VectorTraits<T, 3>::UNIT_X;

template<typename T>
inline constexpr Vector3<T> AXIS3D_Y = internal::VectorTraits<T, 3>::UNIT_Y;

template<typename T>
inline constexpr Vector3<T> AXIS3D_Z = internal::VectorTraits<T, 3>::UNIT_Z;


}

#endif