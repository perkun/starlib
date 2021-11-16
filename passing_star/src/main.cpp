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

int main(int argc, char *argv[]) {
  const double GRAV_CONSTANT =
      Gravity::gravitational_constant(UNITS::AU, UNITS::DAY, UNITS::MASS_SUN);

  Simulation sim(GRAV_CONSTANT);

  auto force_strategy = sim.create_force_strategy();
  auto step_strategy = sim.create_step_strategy();
  auto stop_strategy = sim.create_stop_strategy();

  force_strategy->set_central_mass(1.0);
  force_strategy->push_member_func(&ForceStrategy::relative_nbody);

  PlanetBuilder planet_builder(PlanetsConfig("../../data/planets.yaml"));
  Swarm planets = sim.create_swarm(planet_builder);

//   RandomPopulationBuilder kuiper_belt_builder(
//       RandomPopulationConfig("../../data/kuiper_belt.yaml"), GRAV_CONSTANT);
//   Swarm kuiper_belt = sim.create_swarm(kuiper_belt_builder);


  sim.set_duration_and_direction(300. * UNITS::YEAR, TimeArrow::FUTURE);
  sim.run();

  for (Particle &planet: planets)
  {
	if (planet.get_component<NameComponent>().name == "jupiter")
	{
		StateVector &state = planet.get_component<StateComponent>().state;
		state.position.print();
		state.velocity.print();
	}

  }

  return 0;
}
