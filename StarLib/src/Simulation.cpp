#include "Simulation.h"

using namespace std;

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

    integrator->set_state(
        conv.get_collection_of<Vec3>(conv.get_position, body_store),
        conv.get_collection_of<Vec3>(conv.get_velocitiy, body_store),
        conv.get_collection_of<double>(conv.get_mass, body_store));
}

void Simulation::run_integrator()
{
	integrator->integrate(time_arrow * duration, sequence_size, precision);
}

void Simulation::collect_integrator_results()
{
	vector<Body> bodies;
	bodies.reserve(integrator->positions.size());

	for (int i = 0; i < integrator->positions.size(); i++)
	{

		bodies.emplace_back(
				Body{"tmp",
					integrator->masses[i],
					StateVector(
						integrator->positions[i],
						integrator->velocities[i],
						integrator->get_integration_time())}
				);
	}

	integrated_body_store.clear();
	integrated_body_store.add_group("tmp", bodies);
	BodyStoreConverter::copy_metadata(body_store, integrated_body_store);

}

};
