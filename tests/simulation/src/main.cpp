#include <iostream>
#include <stdio.h>
#include "Simulation.h"
#include "Strategy.h"

using namespace std;
using namespace StarLib;

class MyStepStrategy : public Strategy
{
public:
    MyStepStrategy()
    {
        push_function(
            [=](vector<Vec3> &pos, vector<Vec3> &vel, double t, vector<Vec3> &g)
            {
                for (int i = 0; i < pos.size(); i++)
                {
                    Particle &particle = context->get_particle(i);
                    cout << "name : "
                         << particle.get_component<NameComponent>().name
                         << "\tmass: "
                         << particle.get_component<MassComponent>().mass
                         << endl;
                }
            });
    }
};

int main(int argc, char *argv[])
{

    Simulation sim;

    sim.set_duration_and_direction(10, TimeArrow::FUTURE);

    Particle sun = sim.create_particle(StateVector(Vec3(0.), Vec3(0.), 0.));
    Particle earth = sim.create_particle(
        StateVector(Vec3(0., 1., 0.), Vec3(0., 0.0001, 0.0), 0.));


    sun.add_component<MassComponent>(1.0);
	sun.add_component<NameComponent>("The Sun");

    earth.add_component<MassComponent>(0.00001);
	earth.add_component<NameComponent>("the Earth");


    // TODO delegate creating strategies to Simulation
    shared_ptr<Strategy> force_strategy = make_shared<Strategy>();
    shared_ptr<Strategy> step_strategy = make_shared<MyStepStrategy>();
    shared_ptr<StopStrategy> stop_strategy = make_shared<StopStrategy>();

    sim.set_force_strategy(force_strategy);
    sim.set_step_strategy(step_strategy);
    sim.set_stop_strategy(stop_strategy);

	/* WARNING!
	 * particles in Integrator pos and vel vectors are not guaranteed to be in
	 * the order of creation
	 */

    force_strategy->push_function(
        [](vector<Vec3> &pos, vector<Vec3> &vel, double t, vector<Vec3> &g)
        {
            for (Vec3 &acc : g)
                acc = Vec3(0.0001, 0.0001, 0.);
        });
//
//     force_strategy->push_function(
//         [](vector<Vec3> &pos, vector<Vec3> &vel, double t, vector<Vec3> &g)
//         {
// 			for (Vec3 &acc: g)
// 				acc += Vec3(1.);
// 		});
//
    step_strategy->push_function(
        [&sim](vector<Vec3> &pos, vector<Vec3> &vel, double t, vector<Vec3> &g)
        { cout << sim.get_integration_time() << endl; });
//
//     step_strategy->push_function(
//         [&sun](vector<Vec3> &pos, vector<Vec3> &vel, double t, vector<Vec3> &g)
//         {
//             for (Vec3 &p : pos)
//                 cout << p << endl;
//         });


    sim.run();

    return 0;
}
