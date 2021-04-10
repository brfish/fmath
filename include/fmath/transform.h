#ifndef _FMATH_TRANSFORM_H_
#define _FMATH_TRANSFORM_H_

#include "line.h"
#include "matrix.h"
#include "normal.h"
#include "point.h"
#include "quaternion.h"
#include "ray.h"
#include "triangle.h"
#include "vector.h"

namespace fmath
{

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

template<typename T, Axis A>
FMATH_INLINE FMATH_CONSTEXPR Matrix4<T> mirror()
{
    return scale<A>(static_cast<T>(-1));
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Matrix4<T> mirror(const Vector3<T> &axis)
{
    return scale(axis, static_cast<T>(-1));
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Matrix4<T> orthographic(const T &left, const T &right, const T &bottom, const T &top,
    const T &near, const T &far)
{
    FMATH_ASSERT(notEqualEpsilon(right - left, static_cast<T>(0)));
    FMATH_ASSERT(notEqualEpsilon(top - bottom, static_cast<T>(0)));
    FMATH_ASSERT(notEqualEpsilon(far - near, static_cast<T>(0)));

    const T zero = static_cast<T>(0);
    const T one = static_cast<T>(1);
    const T two = static_cast<T>(2);

    return Matrix4<T>(
        two / (right - left), zero, zero, zero,
        zero, two / (top - bottom), zero, zero,
        zero, zero, two / (near - far), zero,
        (right + left) / (left - right), (top + bottom) / (bottom - top), (near + far) / (near - far), one
    );
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Matrix4<T> perspective(const T &left, const T &right, const T &bottom, const T &top,
    const T &near, const T &far)
{
    FMATH_ASSERT(notEqualEpsilon(right - left, static_cast<T>(0)));
    FMATH_ASSERT(notEqualEpsilon(top - bottom, static_cast<T>(0)));
    FMATH_ASSERT(notEqualEpsilon(far - near, static_cast<T>(0)));

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
FMATH_INLINE FMATH_CONSTEXPR Matrix4<T> perspective(const T &fovy, const T &aspect, const T &near, const T &far)
{
    FMATH_ASSERT(notEqualEpsilon(fovy, static_cast<T>(0)));
    FMATH_ASSERT(notEqualEpsilon(aspect, static_cast<T>(0)));
    FMATH_ASSERT(notEqualEpsilon(far - near, static_cast<T>(0)));

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

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Matrix4<T> lookAt(const Point3<T> &eye, const Point3<T> &target, const Vector3<T> &up)
{
    Vector3<T> w = normalize(target - eye);
    Vector3<T> u = normalize(cross(w, up));
    Vector3<T> v = cross(u, w);
    
    const Vector3<T> &e = reinterpret_cast<const Vector3<T> &>(eye);

    return Matrix4<T>(
        u[0], v[0], -w[0], static_cast<T>(0),
        u[1], v[1], -w[1], static_cast<T>(0),
        u[2], v[2], -w[2], static_cast<T>(0),
        -dot(u, e), -dot(v, e), dot(w, e), static_cast<T>(1)
    );
}

template<typename T>
class Transform
{
public:
    using ValueType = T;

public:
    FMATH_CONSTEXPR Transform(const Transform &other);

    FMATH_CONSTEXPR Transform();

    FMATH_CONSTEXPR Transform(const Matrix4<ValueType> &mat);

    FMATH_CONSTEXPR Transform &operator=(const Transform &other);

    FMATH_INLINE FMATH_CONSTEXPR const T *data() const;

    FMATH_INLINE FMATH_CONSTEXPR T *data();

    FMATH_INLINE FMATH_CONSTEXPR Matrix3<T> linear() const;

    FMATH_INLINE FMATH_CONSTEXPR Vector3<T> translation() const;

    template<Axis A>
    FMATH_INLINE Transform &preRotate(const ValueType &angle);

    FMATH_INLINE Transform &preRotate(const Vector3<ValueType> &axis, const ValueType &angle);

    FMATH_INLINE Transform &preRotate(const Quat<ValueType> &q);

    FMATH_INLINE Transform &preScale(const Vector3<ValueType> &factors);

    FMATH_INLINE Transform &preScale(const ValueType &uniform_factor);

    FMATH_INLINE Transform &preScale(const Vector3<ValueType> &axis, const ValueType &factor);

    FMATH_INLINE Transform &preTranslate(const Vector3<ValueType> &translation);

    template<Axis A>
    FMATH_INLINE Transform &preShear(const ValueType &factor_s, const ValueType &factor_t);

    template<Axis A>
    FMATH_INLINE Transform &rotate(const ValueType &angle);

    FMATH_INLINE Transform &rotate(const Vector3<ValueType> &axis, const ValueType &angle);

    FMATH_INLINE Transform &rotate(const Quat<ValueType> &q);

    FMATH_INLINE Transform &scale(const Vector3<ValueType> &factors);

    FMATH_INLINE Transform &scale(const ValueType &uniform_factor);
    
    FMATH_INLINE Transform &scale(const Vector3<ValueType> &axis, const ValueType &factor);

    FMATH_INLINE Transform &translate(const Vector3<ValueType> &translation);

    template<Axis A>
    FMATH_INLINE Transform &shear(const ValueType &factor_s, const ValueType &factor_t);

    FMATH_INLINE Transform &shear(const Vector3<ValueType> &axis, const ValueType &factor);

    template<Axis A>
    FMATH_INLINE Transform &mirror();

    FMATH_INLINE Transform &mirror(const Vector3<ValueType> &axis);

    FMATH_INLINE Transform &orthographic(const ValueType &left, const ValueType &right,
        const ValueType &bottom, const ValueType &top, const ValueType &near, const ValueType &far);

    FMATH_INLINE Transform &perspective(const ValueType &left, const ValueType &right,
        const ValueType &bottom, const ValueType &top, const ValueType &near, const ValueType &far);

    FMATH_INLINE Transform &perspective(const ValueType &fovy, const ValueType &aspect,
        const ValueType &near, const ValueType &far);

    FMATH_INLINE Transform &lookAt(const Point3<ValueType> &eye, const Point3<ValueType> &target, const Vector3<ValueType> &up);

    FMATH_INLINE Transform &clear();

    FMATH_INLINE FMATH_CONSTEXPR Vector3<T> apply(const Vector3<ValueType> &v) const;

    FMATH_INLINE FMATH_CONSTEXPR Point3<T> apply(const Point3<ValueType> &p) const;

    FMATH_INLINE FMATH_CONSTEXPR Normal3<T> apply(const Normal3<ValueType> &n) const;

    FMATH_INLINE FMATH_CONSTEXPR Ray3<T> apply(const Ray3<T> &r) const;

    FMATH_INLINE FMATH_CONSTEXPR Line3<T> apply(const Line3<T> &l) const;

    FMATH_INLINE FMATH_CONSTEXPR Box3<T> apply(const Box3<ValueType> &b) const;

    FMATH_INLINE FMATH_CONSTEXPR Triangle3<T> apply(const Triangle3<T> &t) const;

    FMATH_INLINE FMATH_CONSTEXPR Vector3<T> operator()(const Vector3<ValueType> &v) const;

    FMATH_INLINE FMATH_CONSTEXPR Point3<T> operator()(const Point3<ValueType> &p) const;

    FMATH_INLINE FMATH_CONSTEXPR Normal3<T> operator()(const Normal3<ValueType> &n) const;

    FMATH_INLINE FMATH_CONSTEXPR Ray3<T> operator()(const Ray3<ValueType> &r) const;

    FMATH_INLINE FMATH_CONSTEXPR Line3<T> operator()(const Line3<ValueType> &l) const;

    FMATH_INLINE FMATH_CONSTEXPR Box3<T> operator()(const Box3<ValueType> &b) const;

    FMATH_INLINE FMATH_CONSTEXPR Triangle3<T> operator()(const Triangle3<ValueType> &t) const;

    FMATH_INLINE FMATH_CONSTEXPR Transform inverse() const;

    FMATH_INLINE FMATH_CONSTEXPR const Matrix4<T> &toMatrix() const;

private:
    Matrix4<ValueType> mat_;
};

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Transform<T> operator*(const Transform<T> &t1, const Transform<T> &t2)
{
    return Transform<T>(t1.toMatrix() * t2.toMatrix());
}

template<typename T>
FMATH_INLINE std::string toString(const Transform<T> &t, uint32 precision = 6)
{
    return toString(t.toMatrix(), precision);
}

template<typename T>
FMATH_INLINE std::ostream &operator<<(std::ostream &output, const Transform<T> &t)
{
    output << t.toMatrix();
    return output;
}

template<typename T>
FMATH_CONSTEXPR Transform<T>::Transform(const Transform &other)
    :   mat_(other.mat_)
{}

template<typename T>
FMATH_CONSTEXPR Transform<T>::Transform()
    :   mat_(Matrix4<ValueType>::identity())
{}

template<typename T>
FMATH_CONSTEXPR Transform<T>::Transform(const Matrix4<ValueType> &mat)
    :   mat_(mat)
{}

template<typename T>
FMATH_CONSTEXPR Transform<T> &Transform<T>::operator=(const Transform &other)
{
    mat_ = other.mat_;
    return *this;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR const T *Transform<T>::data() const
{
    return mat_.data();
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR T *Transform<T>::data()
{
    return mat_.data();
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Matrix3<T> Transform<T>::linear() const
{
    const Matrix4<T> &m = mat_;

    return Matrix3<T>(
        m[0][0], m[0][1], m[0][2],
        m[1][0], m[1][1], m[1][2],
        m[2][0], m[2][1], m[2][2]    
    );
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Vector3<T> Transform<T>::translation() const
{
    return Vector3<T>(mat_[3][0], mat_[3][1], mat_[3][2]);
}

template<typename T>
    template<Axis A>
FMATH_INLINE Transform<T> &Transform<T>::preRotate(const ValueType &angle)
{
    const ValueType cost = cos(angle);
    const ValueType sint = sin(angle);
    Matrix4<T> &m = mat_;

    if constexpr (A == Axis::X)
    {
        Vector4<T> v1 = m[1] * cost + m[2] * sint;
        Vector4<T> v2 = m[1] * sint + m[2] * cost;
        m[1] = v1;
        m[2] = v2;
    }
    else if constexpr (A == Axis::Y)
    {
        Vector4<T> v0 = m[0] * cost - m[2] * sint;
        Vector4<T> v2 = m[0] * sint + m[2] * cost;
        m[0] = v0;
        m[2] = v2;
    }
    else if constexpr (A == Axis::Z)
    {
        Vector4<T> v0 = m[0] * cost + m[1] * sint;
        Vector4<T> v1 = -m[0] * sint + m[1] * cost;
        m[0] = v0;
        m[1] = v1;
    }
    return *this;
}

template<typename T>
FMATH_INLINE Transform<T> &Transform<T>::preRotate(const Vector3<ValueType> &axis, const ValueType &angle)
{
    Matrix4<ValueType> &m = mat_;
    Vector3<ValueType> n = normalize(axis);
    const ValueType cost = cos(angle);
    const ValueType sint = sin(angle);
    const ValueType minus_cost = static_cast<ValueType>(1) - cost;
    const ValueType factor_x = n[0] * minus_cost;
    const ValueType factor_y = n[1] * minus_cost;
    const ValueType factor_z = n[2] * minus_cost;

    Vector4<T> r0, r1, r2;

    r0[0] = factor_x * n[0] + cost;
    r0[1] = factor_x * n[1] + sint * n[2]; 
    r0[2] = factor_x * n[2] - sint * n[1]; 

    r1[0] = factor_y * n[0] - sint * n[2];
    r1[1] = factor_y * n[1] + cost;
    r1[2] = factor_y * n[2] + sint * n[0]; 

    r2[0] = factor_z * n[0] + sint * n[1];
    r2[1] = factor_z * n[1] - sint * n[0];
    r2[2] = factor_z * n[2] + cost;

    Vector4<T> v0 = m[0] * r0[0] + m[1] * r0[1] + m[2] * r0[2];
    Vector4<T> v1 = m[0] * r1[0] + m[1] * r1[1] + m[2] * r1[2];
    Vector4<T> v2 = m[0] * r2[0] + m[1] * r2[1] + m[2] * r2[2];

    m[0] = v0;
    m[1] = v1;
    m[2] = v2;

    return *this;
}

template<typename T>
FMATH_INLINE Transform<T> &Transform<T>::preRotate(const Quat<ValueType> &q)
{
    mat_ *= q.toMatrix();
    return *this;
}

template<typename T>
FMATH_INLINE Transform<T> &Transform<T>::preScale(const Vector3<ValueType> &factors)
{
    mat_[0] *= factors[0];
    mat_[1] *= factors[1];
    mat_[2] *= factors[2];

    return *this;
}

template<typename T>
FMATH_INLINE Transform<T> &Transform<T>::preScale(const ValueType &uniform_factor)
{
    mat_[0] *= uniform_factor;
    mat_[1] *= uniform_factor;
    mat_[2] *= uniform_factor;

    return *this;
}

template<typename T>
FMATH_INLINE Transform<T> &Transform<T>::preScale(const Vector3<ValueType> &axis, const ValueType &factor)
{
    Matrix4<ValueType> &m = mat_;
    Vector3<ValueType> &n = normalize(axis);
    const ValueType factor_x = n[0] * (factor - static_cast<ValueType>(1));
    const ValueType factor_y = n[1] * (factor - 1);
    const ValueType factor_z = n[2] * (factor - 1);

    Vector3<T> r0, r1, r2;

    r0[0] = factor_x * n[0] + static_cast<ValueType>(1);
    r0[1] = factor_x * n[1];
    r0[2] = factor_x * n[2];

    r1[0] = factor_y * n[0];
    r1[1] = factor_y * n[1] + static_cast<ValueType>(1);
    r1[2] = factor_z * n[2];

    r2[0] = factor_z * n[0];
    r2[1] = factor_z * n[1];
    r2[2] = factor_z * n[2] + static_cast<ValueType>(1);

    Vector4<T> v0 = m[0] * r0[0] + m[1] * r0[1] + m[2] * r0[2];
    Vector4<T> v1 = m[0] * r1[0] + m[1] * r1[1] + m[2] * r1[2];
    Vector4<T> v2 = m[0] * r2[0] + m[1] * r2[1] + m[2] * r2[2];

    m[0] = v0;
    m[1] = v1;
    m[2] = v2;

    return *this;
}

template<typename T>
FMATH_INLINE Transform<T> &Transform<T>::preTranslate(const Vector3<ValueType> &translation)
{
    Matrix4<T> &m = mat_;

    Vector4<ValueType> v = m[0] * translation[0] + m[1] * translation[1] + m[2] * translation[2] + m[3];
    m[3] = v;
    return *this;
}

template<typename T>
    template<Axis A>
FMATH_INLINE Transform<T> &Transform<T>::rotate(const ValueType &angle)
{
    mat_ = fmath::rotate<A>(angle) * mat_;
    return *this;
}

template<typename T>
FMATH_INLINE Transform<T> &Transform<T>::rotate(const Vector3<ValueType> &axis, const ValueType &angle)
{
    mat_ = fmath::rotate(axis, angle) * mat_;
    return *this;
}

template<typename T>
FMATH_INLINE Transform<T> &Transform<T>::rotate(const Quat<ValueType> &q)
{
    mat_ = q.toMatrix() * mat_;
    return *this;
}

template<typename T>
FMATH_INLINE Transform<T> &Transform<T>::scale(const Vector3<ValueType> &factors)
{
    mat_ = fmath::scale(factors) * mat_;
    return *this;
}

template<typename T>
FMATH_INLINE Transform<T> &Transform<T>::scale(const ValueType &uniform_factor)
{
    mat_ = fmath::scale(uniform_factor) * mat_;
    return *this;
}

template<typename T>
Transform<T> &Transform<T>::scale(const Vector3<T> &axis, const ValueType &factor)
{
    mat_ = fmath::scale(axis, factor) * mat_;
    return *this;
}

template<typename T>
FMATH_INLINE Transform<T> &Transform<T>::translate(const Vector3<ValueType> &translation)
{
    mat_[3] += translation;
    return *this;
}

template<typename T>
    template<Axis A>
FMATH_INLINE Transform<T> &Transform<T>::shear(const ValueType &factor_s, const ValueType &factor_t)
{
    mat_ = fmath::shear<A>(factor_s, factor_t) * mat_;
    return *this;
}

template<typename T>
FMATH_INLINE Transform<T> &Transform<T>::shear(const Vector3<ValueType> &axis, const ValueType &factor)
{
    mat_ = fmath::shear(axis, factor) * mat_;
    return *this;
}

template<typename T>
    template<Axis A>
FMATH_INLINE Transform<T> &Transform<T>::mirror()
{
    return scale<A>(static_cast<ValueType>(-1));
}

template<typename T>
FMATH_INLINE Transform<T> &Transform<T>::mirror(const Vector3<ValueType> &axis)
{
    return scale(axis, static_cast<ValueType>(-1));
}

template<typename T>
FMATH_INLINE Transform<T> &Transform<T>::orthographic(const ValueType &left, const ValueType &right,
    const ValueType &bottom, const ValueType &top, const ValueType &near, const ValueType &far)
{
    mat_ = fmath::orthographic(left, right, bottom, top, near, far) * mat_;
    return *this;
}

template<typename T>
FMATH_INLINE Transform<T> &Transform<T>::perspective(const ValueType &left, const ValueType &right,
    const ValueType &bottom, const ValueType &top, const ValueType &near, const ValueType &far)
{
    mat_ = fmath::perspective(left, right, bottom, top, near, far) * mat_;
    return *this;
}

template<typename T>
FMATH_INLINE Transform<T> &Transform<T>::perspective(const ValueType &fovy, const ValueType &aspect,
        const ValueType &near, const ValueType &far)
{
    mat_ = fmath::perspective(fovy, aspect, near, far) * mat_;
    return *this;
}

template<typename T>
FMATH_INLINE Transform<T> &Transform<T>::lookAt(const Point3<ValueType> &eye, const Point3<ValueType> &target, const Vector3<ValueType> &up)
{
    mat_ = fmath::lookAt(eye, target, up) * mat_;
    return *this;
}

template<typename T>
FMATH_INLINE Transform<T> &Transform<T>::clear()
{
    mat_ = Matrix4<ValueType>::identity();
    return *this;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Vector3<T> Transform<T>::apply(const Vector3<ValueType> &vector) const
{
    Vector4<ValueType> result = mat_ * Vector4<ValueType>(vector[0], vector[1], vector[2], static_cast<ValueType>(0));
    return Vector3<ValueType>(result[0], result[1], result[2]);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Point3<T> Transform<T>::apply(const Point3<ValueType> &point) const
{
    Vector4<ValueType> result = mat_ * Vector4<ValueType>(point[0], point[1], point[2], static_cast<ValueType>(1));
    ValueType w = result[3];
    if (w != static_cast<ValueType>(1))
        return Point3<ValueType>(result[0], result[1], result[2]) / w;
    return Point3<ValueType>(result[0], result[1], result[2]);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Normal3<T> Transform<T>::apply(const Normal3<ValueType> &normal) const
{
    Matrix4<ValueType> inv = fmath::inverse(mat_);
    Vector4<ValueType> r = Vector4<ValueType>(normal[0], normal[1], normal[2], static_cast<ValueType>(0)) * inv;
    return Normal3<ValueType>(r[0], r[1], r[2]);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Ray3<T> Transform<T>::apply(const Ray3<ValueType> &r) const
{
    return Ray3<ValueType>(apply(r.origin()), apply(r.direction()));
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Line3<T> Transform<T>::apply(const Line3<ValueType> &l) const
{
    return Line3<ValueType>(apply(l.start()), apply(l.end()));
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Box3<T> Transform<T>::apply(const Box3<ValueType> &b) const
{
    const Point3<ValueType> &pmin = b.min();
    const Point3<ValueType> &pmax = b.max();

    Box3<ValueType> result(apply(pmin));
    result += apply(Point3<ValueType>(pmax[0], pmin[1], pmin[2]));
    result += apply(Point3<ValueType>(pmin[0], pmax[1], pmin[2]));
    result += apply(Point3<ValueType>(pmin[0], pmin[1], pmax[2]));
    result += apply(Point3<ValueType>(pmin[0], pmax[1], pmax[2]));
    result += apply(Point3<ValueType>(pmax[0], pmax[1], pmin[2]));
    result += apply(Point3<ValueType>(pmax[0], pmin[1], pmax[2]));
    result += apply(Point3<ValueType>(pmax[0], pmax[1], pmax[2]));

    return result;
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Triangle3<T> Transform<T>::apply(const Triangle3<ValueType> &t) const
{
    return Triangle3<ValueType>(apply(t[0]), apply(t[1]), apply(t[2]));
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Vector3<T> Transform<T>::operator()(const Vector3<ValueType> &v) const
{
    return apply(v);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Point3<T> Transform<T>::operator()(const Point3<ValueType> &p) const
{
    return apply(p);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Normal3<T> Transform<T>::operator()(const Normal3<ValueType> &n) const
{
    return apply(n);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Ray3<T> Transform<T>::operator()(const Ray3<ValueType> &r) const
{
    return apply(r);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Line3<T> Transform<T>::operator()(const Line3<ValueType> &l) const
{
    return apply(l);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Box3<T> Transform<T>::operator()(const Box3<ValueType> &b) const
{
    return apply(b);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Triangle3<T> Transform<T>::operator()(const Triangle3<ValueType> &t) const
{
    return apply(t);
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR Transform<T> Transform<T>::inverse() const
{
    return Transform<T>(fmath::inverse(mat_));
}

template<typename T>
FMATH_INLINE FMATH_CONSTEXPR const Matrix4<T> &Transform<T>::toMatrix() const
{
    return mat_;
}

using Transform4f = Transform<float>;
using Transform4lf = Transform<double>;

}

#endif