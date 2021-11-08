#ifndef SWARM_H_
#define SWARM_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include "Particle.h"


namespace StarLib {
class Swarm
{
public:
    Swarm();
    ~Swarm();

    void push_particle(Particle p) { particles.push_back(p); }

    std::vector<Particle>::iterator begin() { return particles.begin(); }
    std::vector<Particle>::iterator end() { return particles.end(); }

private:
    std::vector<Particle> particles;
};
}

#endif /* SWARM_H_ */
