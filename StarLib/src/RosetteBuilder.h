#ifndef ROSETTEBUILDER_H_
#define ROSETTEBUILDER_H_

#include <iostream>
#include <stdio.h>
#include <math.h>
#include "SwarmBuilder.h"
#include "Orbit.h"
#include "Components.h"

namespace StarLib {
class RosetteBuilder : public SwarmBuilder
{
public:
    RosetteBuilder(int num_particles, double central_mass, double mass,
                   double q, double e, double grav_const);
    ~RosetteBuilder();

    virtual Swarm setup(std::vector<Particle>) override;

private:
    static double polygon_constant(int n);
    double central_mass, mass, q, e;
    double GRAV_CONSTANT;
};
}

#endif /* ROSETTEBUILDER_H_ */
