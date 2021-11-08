#ifndef SWARMBUILDER_H_
#define SWARMBUILDER_H_

#include <iostream>
#include <stdio.h>
#include <memory>
#include <vector>
#include "Particle.h"
#include "Swarm.h"

namespace StarLib {
class SwarmBuilder
{
public:
    SwarmBuilder(int num_particles);
    ~SwarmBuilder();

    int get_num_particles() { return num_particles; }
    virtual Swarm setup(std::vector<Particle>) = 0;

protected:
    int num_particles = 0;
};
}

#endif /* SWARMBUILDER_H_ */
