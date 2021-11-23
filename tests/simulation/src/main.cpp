#include <iostream>
#include <stdio.h>
#include "Simulation.h"
#include "Strategy.h"

using namespace std;
using namespace StarLib;


void func1(vector<Vec3> &pos, vector<Vec3> &vel, double t, vector<Vec3> &g)
{
	for (Vec3 &acc : g)
		acc = Vec3(0.0001, 0.0001, 0.);
}


// class MyStepStrategy : public StepStrategy
// {
// public:
//     MyStepStrategy()
//     {
//         push_function(
//             [=](vector<Vec3> &pos, vector<Vec3> &vel, double t)
//             {
//                 for (int i = 0; i < pos.size(); i++)
//                 {
//                     Particle &particle = context->get_particle(i);
//                     cout << "name : "
//                          << particle.get_component<NameComponent>().name
//                          << "\tmass: "
//                          << particle.get_component<MassComponent>().mass
//                          << endl;
//                 }
//             });
//     }
// };



int main(int argc, char *argv[])
{
    Simulation sim(1.0);

    sim.set_duration_and_direction(10, TimeArrow::FUTURE);

    Particle sun = sim.create_particle(StateVector(Vec3(0.), Vec3(0.), 0.));
    Particle earth = sim.create_particle(
        StateVector(Vec3(0., 1., 0.), Vec3(0., 0.0001, 0.0), 0.));


    sun.add_component<MassComponent>(1.0);
    sun.add_component<NameComponent>("The Sun");

    earth.add_component<MassComponent>(0.00001);
    earth.add_component<NameComponent>("the Earth");


    shared_ptr<ForceStrategy> force_strategy = sim.create_force_strategy();
    shared_ptr<StepStrategy> step_strategy = sim.create_step_strategy();
//     shared_ptr<StepStrategy> step_strategy = sim.create_step_strategy<MyStepStrategy>();
    shared_ptr<StopStrategy> stop_strategy = sim.create_stop_strategy();


//     force_strategy->push_lambda(
//         [](vector<Vec3> &pos, vector<Vec3> &vel, double t, vector<Vec3> &g)
//         {
//             for (Vec3 &acc : g)
//                 acc = Vec3(0.0001, 0.0001, 0.);
//         });

	force_strategy->push_lambda(func1);

//     step_strategy->push_lambda(
//         [&sim](vector<Vec3> &pos, vector<Vec3> &vel, double t)
//         {
// 			cout << sim.get_integration_time() << endl;
// 			cout << sim.get_particle(1).get_component<NameComponent>().name << endl;
// 		});

	step_strategy->push_member_func(&StepStrategy::print_mass);

	stop_strategy->set_stop_func(
		[](vector<Vec3> &pos, vector<Vec3> &vel, double t)
		{
			if (t >= 5)
				return true;
			return false;
		});


    sim.run();



    return 0;
}
