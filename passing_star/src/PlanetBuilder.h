#ifndef PLANETBUILDER_H_
#define PLANETBUILDER_H_

#include <iostream>
#include <stdio.h>
#include <map>
#include "SwarmBuilder.h"
#include "ConfigPlanets.h"
#include "Constants.h"
#include "Components.h"
#include "IO.h"

class PlanetBuilder : public StarLib::SwarmBuilder
{
public:
    PlanetBuilder(const PlanetsConfig &cfg);
    ~PlanetBuilder();

private:
	const PlanetsConfig cfg;
    virtual StarLib::Swarm setup(std::vector<StarLib::Particle>) override;
};

#endif /* PLANETBUILDER_H_ */
