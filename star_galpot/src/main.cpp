#include <iostream>
#include <stdio.h>
#include "Simulation.h"
#include "Strategy.h"
#include "RosetteBuilder.h"
#include "Gravity.h"
#include "Units.h"
#include "GalacticPotential.h"

using namespace std;
using namespace StarLib;

int main(int argc, char *argv[])
{
    double GRAV_CONSTANT = //4.498310022e-3;
        Gravity::gravitational_constant(UNITS::PARSEC, UNITS::MYEAR, UNITS::MASS_SUN);
	printf("G = %.16e\n", GRAV_CONSTANT);

    Simulation sim(GRAV_CONSTANT);

	Particle sun = sim.create_particle();
	Particle star = sim.create_particle();

    auto force_strategy = sim.create_force_strategy();
	auto stop_strategy = sim.create_stop_strategy();

	GalacticPotential_IWTS_Ia *gal_pot = new GalacticPotential_IWTS_Ia(GRAV_CONSTANT);

	StateVector &sun_state = sun.get_component<StateComponent>().state;
	sun_state.position = Vec3(-gal_pot->sun_galactic_distance, 0., gal_pot->sun_pos_z);
	sun_state.velocity = gal_pot->get_sun_velocity();
	sun.add_component<MassComponent>(1.0);

	StateVector &star_state = star.get_component<StateComponent>().state;
	star_state.position = Vec3(-44.8490007837, +60.9378075571, -1.0510946256) + sun_state.position;
	star_state.velocity = Vec3(-16.0744115985, +21.7529716101, -0.3661435984) + sun_state.velocity;
	star.add_component<MassComponent>(1.08);

	sim.set_duration_and_direction(5.795485, TimeArrow::PAST);

	force_strategy->push_member_func(&ForceStrategy::nbody);
	force_strategy->push_lambda(
		[&gal_pot](vector<Vec3> &pos, vector<Vec3> &vel, double t, vector<Vec3> &g)
		{
			g[0] += gal_pot->get_acceleration(pos[0]);
			g[1] += gal_pot->get_acceleration(pos[1]);
		});

	double prev_distance = 1e32;
	stop_strategy->set_stop_func(
		[&prev_distance](vector<Vec3> &pos, vector<Vec3> &vel, double t)
		{
			double distance = (pos[1] - pos[0]).length();
			if (distance > prev_distance)
				return true;
			prev_distance = distance;
			return false;
		});


	sim.run();
	prev_distance = 1e32;
	sim.set_duration_and_direction(1.0, TimeArrow::FUTURE);
	sim.run_constant_step(0.000001);


	sun_state.position.print();
	sun_state.velocity.print();
	star_state.position.print();
	star_state.velocity.print();

	cout << (star_state.position - sun_state.position).length() << endl;
	cout << prev_distance << endl;


	// P0230     -44.8490007837     +60.9378075571      -1.0510946256   -16.0744115985    +21.7529716101    -0.3661435984    1.0800
	// d_min=0.023962, t_min=-2.795485, v_rel=26.492249
	return 0;
}

