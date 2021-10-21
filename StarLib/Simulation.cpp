#include "Simulation.h"


namespace StarLib
{

Simulation::Simulation()
{
}


Simulation::~Simulation()
{
}




void Simulation::run()
{
	// convert data
	prep_integrator();
	run_integrator();
	collect_integrator_results();
}

double Simulation::get_integration_time()
{
	return integrator->get_integration_time();
}

BodyStore Simulation::get_results()
{
	return integrated_body_store;
}




void Simulation::prep_integrator()
{
	set_integrator_initial_data();
}


void Simulation::set_integrator_initial_data()
{
	// convert BodyStore to integrator pos & vel vectors

	BodyStoreConverter conv;
	conv.get<double>(body_store, convget_mass);

// 	integrator->set_conditions(
// 		BodyStoreConverter::get<Vec3, BodyStoreConverter::get_position>(body_store),
// 		BodyStoreConverter::get<Vec3, BodyStoreConverter::get_velocitiy>(body_store),
// 		BodyStoreConverter::get<Vec3, BodyStoreConverter::get_mass>(body_store),
// 		BodyStoreConverter::get

}

void Simulation::run_integrator()
{
	integrator->integrate(time_arrow * duration, sequence_size, precision);
}

void Simulation::collect_integrator_results()
{
	for (int i = 0; i < integrator->positions.size(); i++)
	{

	}
}

};
