#ifndef STATEVECTOR_H_
#define STATEVECTOR_H_

#include "starlibmath.h"

namespace StarLib
{

struct StateVector
{
    StateVector()
    {
    }

    StateVector(const Vec3 &p, const Vec3 &v, double t) : position(p), velocity(v), time(t)
    {
    }
    ~StateVector()
    {
    }

    Vec3 position{0.};
    Vec3 velocity{0.};
    double time = 0.;
};
}

#endif /* STATEVECTOR_H_ */
