#ifndef _FMATH_TRANSFORM_H_
#define _FMATH_TRANSFORM_H_

#include "euler_angle.h"
#include "matrix.h"
#include "matrix_transform.h"
#include "vector.h"
#include "point.h"
#include "quaternion.h"
#include "normal.h"

namespace fmath
{

template<typename T>
class Transform
{
public:
    using ValueType = T;

public:
    Transform(const Transform &other);

    Transform();

    Transform(const Matrix4<ValueType> &mat);

    Transform &operator=(const Transform &other);

    template<Axis A>
    Transform &preRotate(angle_t angle);

    Transform &preRotate(const Vector3<ValueType> &axis, angle_t angle);

    Transform &preScale(const Vector3<ValueType> &factors);

    Transform &preScale(const ValueType &uniform_factor);

    Transform &preScale(const Vector3<ValueType> &axis, const ValueType &factor);

    Transform &preTranslate(const Vector3<ValueType> &translation);

    template<Axis A>
    Transform &rotate(angle_t angle);

    Transform &rotate(const Vector3<ValueType> &axis, angle_t angle);

    Transform &scale(const Vector3<ValueType> &factors);

    Transform &scale(const ValueType &uniform_factor);
    
    Transform &scale(const Vector3<ValueType> &axis, const ValueType &factor);

    Transform &translate(const Vector3<ValueType> &translation);

    template<Axis A>
    Transform &shear(const ValueType &factor_s, const ValueType &factor_t);

    Transform &mirror(const Vector3<ValueType> &axis);

    template<Axis A>
    Transform &orthographic();

    Transform &orthographic(const Vector3<ValueType> &n);

    Transform &perspective(Vector3<ValueType> a);

    Transform &lookAt(const Point3<ValueType> &eye, const Point3<ValueType> &target, const Vector3<ValueType> &up);

    Transform &clear();

    Vector3<ValueType> apply(const Vector3<ValueType> &v) const;

    Point3<ValueType> apply(const Point3<ValueType> &p) const;

    Normal3<ValueType> apply(const Normal3<ValueType> &n) const;

    Vector3<ValueType> operator()(const Vector3<ValueType> &v) const;

    Point3<ValueType> operator()(const Point3<ValueType> &p) const;

    Normal3<ValueType> operator()(const Normal3<ValueType> &n) const;

    Transform inverse() const;

    const Matrix4<ValueType> &toMatrix() const;

private:
    Matrix4<ValueType> mat_;
};

template<typename T>
Transform<T>::Transform(const Transform &other)
    :   mat_(other.mat_)
{}

template<typename T>
Transform<T>::Transform()
    :   mat_(Matrix4<ValueType>::identity())
{}

template<typename T>
Transform<T>::Transform(const Matrix4<ValueType> &mat)
    :   mat_(mat)
{}

template<typename T>
Transform<T> &Transform<T>::operator=(const Transform &other)
{
    mat_ = other.mat_;
    return *this;
}

template<typename T>
    template<Axis A>
Transform<T> &Transform<T>::preRotate(angle_t angle)
{
#ifdef FMATH_USE_DEGREE
    angle = toRadian(angle);
#endif
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
Transform<T> &Transform<T>::preRotate(const Vector3<ValueType> &axis, angle_t angle)
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
Transform<T> &Transform<T>::preScale(const Vector3<ValueType> &factors)
{
    mat_[0] *= factors[0];
    mat_[1] *= factors[1];
    mat_[2] *= factors[2];

    return *this;
}

template<typename T>
Transform<T> &Transform<T>::preScale(const ValueType &uniform_factor)
{
    mat_[0] *= uniform_factor;
    mat_[1] *= uniform_factor;
    mat_[2] *= uniform_factor;

    return *this;
}

template<typename T>
Transform<T> &Transform<T>::preScale(const Vector3<ValueType> &axis, const ValueType &factor)
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
Transform<T> &Transform<T>::preTranslate(const Vector3<ValueType> &translation)
{
    Matrix4<T> &m = mat_;

    Vector4<ValueType> v = m[0] * translation[0] + m[1] * translation[1] + m[2] * translation[2] + m[3];
    m[3] = v;
    return *this;
}

template<typename T>
    template<Axis A>
Transform<T> &Transform<T>::rotate(angle_t angle)
{
    const ValueType cost = cos(angle);
    const ValueType sint = sin(angle);
    const ValueType one = static_cast<ValueType>(1);
    const ValueType zero = static_cast<ValueType>(0);

    if constexpr (A == Axis::X)
    {
        Matrix4<T> r(
            one, zero, zero, zero,
            zero, cost, -sint, zero,
            zero, sint, cost, zero,
            zero, zero, zero, one
        );
        mat_ = r * mat_;
    }
    else if constexpr (A == Axis::Y)
    {
        Matrix4<T> r(
            cost, zero, sint, zero,
            zero, one, zero, zero,
            -sint, zero, cost, zero,
            zero, zero, zero, one
        );
        mat_ = r * mat_;
    }
    else if constexpr (A == Axis::Z)
    {
        Matrix4<T> r(
            cost, -sint, zero, zero,
            sint, cost, zero, zero,
            zero, zero, one, zero,
            zero, zero, zero, one
        );
        mat_ = r * mat_;
    }

    return *this;
}

template<typename T>
Transform<T> &Transform<T>::rotate(const Vector3<ValueType> &axis, angle_t angle)
{
    Matrix4<T> &m = mat_;
    Vector3<ValueType> n = normalize(axis);
    const ValueType cost = cos(angle);
    const ValueType sint = sin(angle);
    const ValueType minus_cost = static_cast<ValueType>(1) - cost;
    const ValueType factor_x = n[0] * minus_cost;
    const ValueType factor_y = n[1] * minus_cost;
    const ValueType factor_z = n[2] * minus_cost;

    Vector4<T> r0, r1, r2, r3;

    r0[0] = factor_x * n[0] + cost;
    r0[1] = factor_y * n[0] - sint * n[2];
    r0[2] = factor_z * n[0] + sint * n[1];

    r1[0] = factor_x * n[1] + sint * n[2];
    r1[1] = factor_y * n[1] + cost;
    r1[2] = factor_z * n[1] - sint * n[0];

    r2[0] = factor_x * n[2] - sint * n[1];
    r2[1] = factor_y * n[2] + sint * n[0];
    r2[2] = factor_z * n[2] + cost;

    r3[3] = static_cast<ValueType>(1);

    Vector4<T> v0 = r0 * m[0][0] + r1 * m[0][1] + r2 * m[0][2];
    Vector4<T> v1 = r0 * m[1][0] + r1 * m[1][1] + r2 * m[1][2];
    Vector4<T> v2 = r0 * m[2][0] + r1 * m[2][1] + r2 * m[2][2];
    Vector4<T> v3 = r0 * m[3][0] + r1 * m[3][1] + r2 * m[3][2] + r3;

    m[0] = v0;
    m[1] = v1;
    m[2] = v2;
    m[3] = v3;

    return *this;
}

template<typename T>
Transform<T> &Transform<T>::scale(const Vector3<ValueType> &factors)
{
    const ValueType one = static_cast<ValueType>(1);
    const ValueType zero = static_cast<ValueType>(0);

    Matrix4<T> s(
        factors[0], zero, zero, zero,
        zero, factors[1], zero, zero,
        zero, zero, factors[2], zero,
        zero, zero, zero, one
    );

    mat_ = s * mat_;

    return *this;
}

template<typename T>
Transform<T> &Transform<T>::scale(const ValueType &uniform_factor)
{
    return scale(Vector3<ValueType>(uniform_factor, uniform_factor, uniform_factor));
}

template<typename T>
Transform<T> &Transform<T>::scale(const Vector3<T> &axis, const ValueType &factor)
{
    Matrix4<T> &m = mat_;
    Vector3<T> &n = normalize(axis);
    const ValueType factor_x = n[0] * (factor - 1);
    const ValueType factor_y = n[1] * (factor - 1);
    const ValueType factor_z = n[2] * (factor - 1);

    Vector4<T> r0, r1, r2, r3;

    r0[0] = factor_x * n[0] + 1;
    r0[1] = factor_y * n[0];
    r0[2] = factor_z * n[0];

    r1[0] = factor_x * n[1];
    r1[1] = factor_y * n[1] + 1;
    r1[2] = factor_z * n[1];

    r2[0] = factor_x * n[2];
    r2[1] = factor_z * n[2];
    r2[2] = factor_z * n[2] + 1;

    r3[3] = static_cast<ValueType>(1);

    Vector4<T> v0 = r0 * m[0][0] + r1 * m[0][1] + r2 * m[0][2];
    Vector4<T> v1 = r0 * m[1][0] + r1 * m[1][1] + r2 * m[1][2];
    Vector4<T> v2 = r0 * m[2][0] + r1 * m[2][1] + r2 * m[2][2];
    Vector4<T> v3 = r0 * m[3][0] + r1 * m[3][1] + r2 * m[3][2] + r3;

    m[0] = v0;
    m[1] = v1;
    m[2] = v2;
    m[3] = v3;

    return *this;
}

template<typename T>
Transform<T> &Transform<T>::translate(const Vector3<ValueType> &translation)
{
    mat_[3] += translation;

    return *this;
}

template<typename T>
    template<Axis A>
Transform<T> &Transform<T>::shear(const ValueType &factor_s, const ValueType &factor_t)
{
    const ValueType one = static_cast<ValueType>(1);
    const ValueType zero = static_cast<ValueType>(0);

    if constexpr (A == Axis::X)
    {
        Matrix4<T> h(
            one, zero, zero, zero,
            factor_s, one, zero, zero,
            factor_t, zero, one, zero,
            zero, zero, zero, one
        );
        mat_ = h * mat_;
    }
    else if constexpr (A == Axis::Y)
    {
        Matrix4<T> h(
            one, factor_s, zero, zero,
            zero, one, zero, zero,
            zero, factor_t, one, zero,
            zero, zero, zero, one
        );
        mat_ = h * mat_;
    }
    else if constexpr (A == Axis::Z)
    {
        Matrix4<T> h(
            one, zero, factor_s, zero,
            zero, one, factor_t, zero,
            zero, zero, one, zero,
            zero, zero, zero, one
        );
        mat_ = h * mat_;
    }

    return *this;
}

template<typename T>
Transform<T> &Transform<T>::mirror(const Vector3<ValueType> &axis)
{
    return scale(axis, static_cast<ValueType>(-1));
}

template<typename T>
    template<Axis A>
Transform<T> &Transform<T>::orthographic()
{
    size_t index = static_cast<size_t>(A);
    mat_[0][index] = 0;
    mat_[1][index] = 0;
    mat_[2][index] = 0;
    mat_[3][index] = 0;
    return *this;
}

template<typename T>
Transform<T> &Transform<T>::orthographic(const Vector3<ValueType> &axis)
{
    return scale(axis, static_cast<ValueType>(0));
}

template<typename T>
Transform<T> &Transform<T>::lookAt(const Point3<ValueType> &eye, const Point3<ValueType> &target, const Vector3<ValueType> &up)
{
    Vector3<ValueType> w = normalize(target - eye);
    Vector3<ValueType> u = normalize(cross(up, w));
    Vector3<ValueType> v = cross(w, u);
    
    Matrix4<ValueType> l(
        u[0], v[0], w[0], static_cast<ValueType>(0),
        u[1], v[1], w[1], static_cast<ValueType>(0),
        u[2], v[2], w[2], static_cast<ValueType>(0),
        -dot(u, eye), -dot(v, eye), -dot(w, eye), static_cast<ValueType>(1)
    );

    return *this;
}

template<typename T>
Transform<T> &Transform<T>::clear()
{
    mat_ = Matrix4<ValueType>::identity();
}

template<typename T>
Vector3<T> Transform<T>::apply(const Vector3<ValueType> &vector) const
{
    Vector4<ValueType> result = mat_ * Vector4<ValueType>(vector[0], vector[1], vector[2], static_cast<ValueType>(0));
    return Vector3<ValueType>(result[0], result[1], result[2]);
}

template<typename T>
Point3<T> Transform<T>::apply(const Point3<ValueType> &point) const
{
    Vector4<ValueType> result = mat_ * Vector4<ValueType>(point[0], point[1], point[2], static_cast<ValueType>(1));
    ValueType w = result[3];
    if (w != static_cast<ValueType>(1))
        return Point3<T>(result[0], result[1], result[2]) / w;
    return Point3<T>(result[0], result[1], result[2]);
}

template<typename T>
Normal3<T> Transform<T>::apply(const Normal3<ValueType> &normal) const
{
    Matrix4<T> inv = fmath::inverse(mat_);
    Vector4<T> r = Vector4<T>(normal[0], normal[1], normal[2], 0) * inv;
    return Normal3<T>(r[0], r[1], r[2]);
}

template<typename T>
Vector3<T> Transform<T>::operator()(const Vector3<ValueType> &v) const
{
    return apply(v);
}

template<typename T>
Point3<T> Transform<T>::operator()(const Point3<ValueType> &p) const
{
    return apply(p);
}

template<typename T>
Normal3<T> Transform<T>::operator()(const Normal3<ValueType> &n) const
{
    return apply(n);
}

template<typename T>
Transform<T> Transform<T>::inverse() const
{
    return Transform<T>(fmath::inverse(mat_));
}

template<typename T>
const Matrix4<T> &Transform<T>::toMatrix() const
{
    return mat_;
}

using Transform4f = Transform<float>;
using Transform4lf = Transform<double>;

}

#endif