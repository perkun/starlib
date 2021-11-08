#include <iostream>
#include <stdio.h>
#include <gtest/gtest.h>
#include "Simulation.h"
#include "Strategy.h"
#include "RosetteBuilder.h"
#include "Gravity.h"
#include "Units.h"

using namespace std;
using namespace StarLib;

#define PRECISION (1.0e-15)


TEST(Rosettes, SevenBodiesCentralMass)
{

    double GRAV_CONSTANT =
        Gravity::gravitational_constant(UNITS::AU, UNITS::DAY, UNITS::MASS_SUN);

    double sun_mass = 1.0;

    Simulation sim(GRAV_CONSTANT);
    sim.set_duration_and_direction(1e5, TimeArrow::FUTURE);

    RosetteBuilder rosette_builder(7, sun_mass, 1e-4, 1.0, 0.2819,
                                   GRAV_CONSTANT);
    Swarm bodies = sim.create_swarm(rosette_builder);

    auto force_strategy = sim.create_force_strategy();
	force_strategy->set_central_mass(sun_mass);
	force_strategy->push_member_func(&ForceStrategy::relative_nbody);

    sim.run();

	StateVector &state = sim.get_particle(0).get_component<StateComponent>().state;

    EXPECT_LE(fabs(state.position.x - -1.5423242612087613),
              PRECISION);
    EXPECT_LE(fabs(state.position.y - -0.7538104850866012),
              PRECISION);
    EXPECT_LE(fabs(state.position.z - 0.0), PRECISION);
    EXPECT_LE(fabs(state.velocity.x - 0.0066723209717247),
              PRECISION);
    EXPECT_LE(fabs(state.velocity.y - -0.0093683095846389),
              PRECISION);
    EXPECT_LE(fabs(state.velocity.z - 0.0), PRECISION);


}




int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
