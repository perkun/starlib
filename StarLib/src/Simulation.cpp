#include "Simulation.h"

using namespace std;

namespace StarLib
{

Simulation::Simulation(double grav_const) : GRAV_CONSTANT(grav_const)
{
	create_force_strategy();
	create_step_strategy();
	create_stop_strategy();
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


Swarm Simulation::create_swarm(SwarmBuilder &builder)
{
	vector<Particle> particles;
	for (int i = 0; i < builder.get_num_particles(); i++)
	{
		particles.push_back(create_particle());
	}
	return builder.setup(particles);
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
    for (int i = 0; i < get_num_particles(); i++)
    {
        StateVector &state =
            get_particle(i).get_component<StateComponent>().state;
		state.position = integrator->pos[i];
		state.velocity = integrator->vel[i];
		state.time = integrator->get_integration_time();
	}
}


Particle& Simulation::get_particle(int i)
{
	return particle_order[i];
}

int Simulation::get_num_particles()
{
	return particle_order.size();
}

};
