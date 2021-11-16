#include <iostream>
#include <stdio.h>
#include "Simulation.h"
#include "Gravity.h"
#include "Units.h"

#include "ConfigPlanets.h"
#include "PlanetBuilder.h"
#include "RandomPopulationConfig.h"
#include "RandomPopulationBuilder.h"

using namespace std;
using namespace StarLib;




int main(int argc, char *argv[])
{
    const double GRAV_CONSTANT =
        Gravity::gravitational_constant(UNITS::AU, UNITS::DAY, UNITS::MASS_SUN);

	Simulation sim(GRAV_CONSTANT);

	auto force_strategy = sim.create_force_strategy();
	auto step_strategy = sim.create_step_strategy();
	auto stop_strategy = sim.create_stop_strategy();

	force_strategy->set_central_mass(1.0);
    force_strategy->push_member_func(&ForceStrategy::relative_nbody);

	PlanetsConfig config_planets("../../data/planets.yaml");
	PlanetBuilder planet_builder(config_planets);
	Swarm planets = sim.create_swarm(planet_builder);

	RandomPopulationConfig kuiper_belt_config("../../data/kuiper_belt.yaml");
	RandomPopulationBuilder kuiper_belt_builder(kuiper_belt_config, GRAV_CONSTANT);

	Swarm kuiper_belt = sim.create_swarm(kuiper_belt_builder);


    return 0;
}
