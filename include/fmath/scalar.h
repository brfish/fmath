#ifndef _FMATH_SCALAR_H_
#define _FMATH_SCALAR_H_

#include "internal/vector_storage.h"
#include "common.h"

namespace fmath
{

template<typename T, size_t N>
class Scalar : public internal::VectorStorage<T, N>
{
public:
    Scalar(const Scalar &other);

    Scalar &operator=(const Scalar &other);

    

};

}

#endif