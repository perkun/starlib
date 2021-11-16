#ifndef RANDOMPOPULATIONBUILDER_H_
#define RANDOMPOPULATIONBUILDER_H_

#include <iostream>
#include <stdio.h>
#include "OrbitalElements.h"
#include "Components.h"
#include "Orbit.h"

#include "RandomPopulationConfig.h"
#include "SwarmBuilder.h"

class RandomPopulationBuilder : public StarLib::SwarmBuilder
{
public:
    RandomPopulationBuilder(const RandomPopulationConfig &cfg, double G);
    ~RandomPopulationBuilder();

private:
    const RandomPopulationConfig cfg;
    virtual StarLib::Swarm setup(std::vector<StarLib::Particle>) override;
	const double GRAV_CONSTANT;

	void set_random_generator_seed(unsigned int seed);
	double calc_random_mass();
	std::string make_name(int i);
	StarLib::OrbitalElements make_random_elements();



};

#endif /* KUIPERBELTBUILDER_H_ */
