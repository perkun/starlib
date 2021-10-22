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


Particle Simulation::create_particle(StateVector sv)
{
	Particle particle(registry.create(), &registry);

	// add default components
	particle.add_component<StateComponent>(sv);

	particle_order.push_back(particle);

	return particle;
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

void Simulation::prep_integrator()
{
	integrator = make_shared<Integrator>(EQ_CLASS::SECOND_DERIVATIVE);
	integrator->sequence_size = 0.001;
	integrator->precision = 14;

	integrator->force_strategy = force_strategy;
	integrator->step_strategy = step_strategy;
	integrator->stop_strategy = stop_strategy;

	set_integrator_initial_data();
}

Particle& Simulation::get_particle(int i)
{
	return particle_order[i];
}


void Simulation::set_integrator_initial_data()
{
    for (Particle &particle : particle_order)
    {
		StateComponent &sc = particle.get_component<StateComponent>();
        integrator->pos.push_back(sc.state.position);
        integrator->vel.push_back(sc.state.velocity);
    }
}

void Simulation::run_integrator()
{
	integrator->integrate(time_arrow * duration);
}

void Simulation::collect_integrator_results()
{

}

};




