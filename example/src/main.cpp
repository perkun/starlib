#include <iostream>
#include <stdio.h>

#include "Simulation.h"
#include "Gravity.h"
#include "Units.h"

using namespace StarLib; // everything in StarLib library is in namespace
                         // "StarLib"

int main()
{
    // create gravitational constant in units of your liking
    const double G =
        Gravity::gravitational_constant(UNITS::AU, UNITS::DAY, UNITS::MASS_SUN);

    // create simulation. Pass Gravitational constant to the constructor
    Simulation sim(G);


    /* Ok, now we need to add some particles to integrate. Particles are created
     * via Simulation, and implement Entity-Component-System. That means that
     * each particle can have any nymber of classes - components - asssiated
     * with them. By default, they have StateComponent, which has state member,
     * which is StateVector (position, velocity and time). When running the
     * simulation, all posiotions and velocities are copied to the vectors of
     * Vec3's: pos and vel (the ones you see in ForceStrategy lambda function).
     * Also, if a particle has MassComponent, the values are copied to the
     * masses vector, available in force function. Any other components are
     * reachable by Particle::get_component method.
     */

    Vec3 position(0.7, 0.6, 0.001);         // in basic units: au
    Vec3 velocity(0.003, 0.0001, 0.000001); // in basic units: au/day
    Particle planet = sim.create_particle(StateVector(position, velocity, 0.0));
    // now, we have a handle for the particle. Let's add mass:
    planet.add_component<MassComponent>(1e-6 * UNITS::MASS_SUN);
    // and name
    planet.add_component<NameComponent>("Planet X");

    Particle comet = sim.create_particle(
        StateVector(Vec3(5.2, 4, 0.1), Vec3(0.001, 0.0002, -0.2), 0.0));
    comet.add_component<MassComponent>(1e-10 * UNITS::MASS_SUN);
    comet.add_component<NameComponent>("comet");


    /* Now, let's create strategies for the integrator. There are:
       - ForceStrategy, that defines the force function,
       - StepStrategy, that defines action performed on each integrator step
       - StopStrategy, defines a function that is performed on each
                    integration step. If it returns true, integration stops.
    */
    auto force_strategy = sim.create_force_strategy();
    auto step_strategy = sim.create_step_strategy();
    auto stop_strategy = sim.create_stop_strategy();

    /* you can push any number of functions to each strategy. Thera are 2 ways
     * of doing this: push_member_func and push_lambda. The former takes a
     * pointer to the member function. E.g. force strategy has defined functions
     * for calculating n-body forces, one for barycentric ref. frame
     * (ForceStrategy::nbody), other for n-body relative to central mass
     * (ForceStrategy::relative_nbody).
     *
     * Let's add relative n-body
     */

    force_strategy->push_member_func(&ForceStrategy::relative_nbody);

    // you can add a lambda as well. You can capture anything you need...
    force_strategy->push_lambda(
        [](std::vector<Vec3> &pos, std::vector<Vec3> &vel, double tm,
           std::vector<Vec3> &g)
        {
            // force function takes positions vector, velocities vector, time of
            // integration and acceleration vector.

            // do stuff...
        });

    // since we want relative n-body, let's set central mass = 1.5 solar mass
    force_strategy->set_central_mass(1.5 * UNITS::MASS_SUN);

    // Let's print velocities at each step
    step_strategy->push_lambda(
        [](std::vector<Vec3> &pos, std::vector<Vec3> &vel, double tm)
        {
            std::cout << "integration time: " << tm << std::endl;
            for (Vec3 velocity : vel)
                std::cout << "velocity: " << velocity.length() << std::endl;
        });

	/* We can integrate the orbits now. Let's define the integration time,
	 * direction and run
	 */
	sim.set_duration_and_direction(100 * UNITS::YEAR, TimeArrow::FUTURE);
	sim.run();

	/* Let's print results, using Components */
	for (int i = 0; i < sim.get_num_particles(); i++)
	{
		Particle p = sim.get_particle(i);
		std::cout << p.get_component<NameComponent>().name << ": " << std::endl;
		StateVector &st = p.get_component<StateComponent>().state;
		std::cout << "Position: " << st.position << std::endl;
		std::cout << "Velocity: " << st.velocity << std::endl;
	}

    return 0;
}
