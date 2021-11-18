#include <iostream>
#include <stdio.h>
#include "Simulation.h"
#include "Gravity.h"
#include "Units.h"

#include "ConfigPlanets.h"
#include "PassingStarConfig.h"
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

    PlanetBuilder planet_builder(PlanetsConfig("../../data/planets.yaml"));
    Swarm planets = sim.create_swarm(planet_builder);

    RandomPopulationBuilder kuiper_belt_builder(
        RandomPopulationConfig("../../data/kuiper_belt.yaml"), GRAV_CONSTANT);
    Swarm kuiper_belt = sim.create_swarm(kuiper_belt_builder);


    PassingStarConfig star_cfg("../../data/passing_star.yaml");

    double sim_duration = star_cfg.passage_duration;
    cout << "sim duration: " << sim_duration << " days" << endl;
    cout << "sim duration: " << sim_duration / UNITS::YEAR << " yrs" << endl;


    Particle passing_star = sim.create_particle(star_cfg.init_state);
    passing_star.add_component<MassComponent>(1.0);

    step_strategy->push_lambda(
        [&passing_star, &star_cfg](vector<Vec3> &pos, vector<Vec3> &vel,
                                   double tm)
        {
            int id = passing_star.order;
            pos[id] = star_cfg.init_state.position +
                      (star_cfg.speed * tm * star_cfg.direction);
        });


    sim.set_duration_and_direction(100. * UNITS::YEAR, TimeArrow::FUTURE);
    sim.run();

    for (Particle &planet : planets)
    {
        if (planet.get_component<NameComponent>().name == "jupiter")
        {
            StateVector &state = planet.get_component<StateComponent>().state;
            double mu =
                GRAV_CONSTANT * (force_strategy->get_central_mass() +
                                 planet.get_component<MassComponent>().mass);
            Orbit orbit(state, mu);
			orbit.print(sim_duration);
            //             state.position.print();
            //             state.velocity.print();
        }
    }

    return 0;
}
