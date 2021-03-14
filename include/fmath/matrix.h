#ifndef _FMATH_MATRIX_H_
#define _FMATH_MATRIX_H_

#include <array>

#include "internal/matrix_storage.h"
#include "common.h"
#include "compile_config.h"
#include "vector.h"


namespace fmath
{

template<typename T, size_t N>
class Matrix : public internal::MatrixStorage<T, N>
{
public:
    Matrix(const Matrix &other);

    Matrix &operator=(const Matrix &other);

    size_t size() const;
};

}

#endif