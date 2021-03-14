#ifndef _FMATH_QUATERNION_H_
#define _FMATH_QUATERNION_H_

#include "vector.h"

namespace fmath
{

class Quaternion
{
public:

public:
    union
    {
        struct { float x, y, z, w; };
        struct { Vector<float, 3> vec; float w; };
    };
};

}

#endif