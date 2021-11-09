#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <iostream>
#include <memory>
#include <stdio.h>
#include "Integrator.h"
#include "Particle.h"
#include "entt.hpp"
#include "Components.h"
#include "Strategy.h"
#include "Swarm.h"
#include "SwarmBuilder.h"


namespace StarLib
{

struct TimeArrow
{
	static constexpr double FUTURE = 1.0,
					 		PAST = -1.0;
};


class Simulation
{
public:
    Simulation(double grav_const);
    ~Simulation();

    void set_duration_and_direction(double duration, double time_arrow)
    {
        this->duration = duration;
        this->time_arrow = time_arrow;
    }
    Particle create_particle(StateVector sv = StateVector());
	Swarm create_swarm(SwarmBuilder &builder);


    template <typename S>
    std::shared_ptr<S> create_force_strategy();
    template <typename S> std::shared_ptr<S> create_step_strategy();
    template <typename S> std::shared_ptr<S> create_stop_strategy();

    std::shared_ptr<ForceStrategy> create_force_strategy()
    {
        return create_force_strategy<ForceStrategy>();
    }

    std::shared_ptr<StepStrategy> create_step_strategy()
    {
        return create_step_strategy<StepStrategy>();
    }

    std::shared_ptr<StopStrategy> create_stop_strategy()
    {
        return create_stop_strategy<StopStrategy>();
    }


    void run();
    void run_constant_step(double sequence_size);
    double get_integration_time();
    Particle &get_particle(int i);
	int get_num_particles();

private:
    std::shared_ptr<Integrator> integrator = nullptr;

    std::shared_ptr<ForceStrategy> force_strategy;
    std::shared_ptr<StepStrategy> step_strategy;
    std::shared_ptr<StopStrategy> stop_strategy;

    double duration;
    double time_arrow = TimeArrow::FUTURE;

    void prep_integrator(double sequence_size = 0.001, int precision = 14);
    void set_integrator_initial_data();
    void run_integrator();
    void collect_integrator_results();

    entt::registry registry;

    std::vector<Particle> particle_order;

	const double GRAV_CONSTANT;
};


template <typename S>
std::shared_ptr<S> Simulation::create_force_strategy()
{
	std::shared_ptr<S> strategy = std::make_shared<S>(this, GRAV_CONSTANT);
	force_strategy = std::static_pointer_cast<ForceStrategy>(strategy);
	return strategy;
}


template <typename S>
std::shared_ptr<S> Simulation::create_step_strategy()
{
	std::shared_ptr<S> strategy = std::make_shared<S>(this, GRAV_CONSTANT);
	step_strategy = std::static_pointer_cast<StepStrategy>(strategy);
	return strategy;
}


template <typename S>
std::shared_ptr<S> Simulation::create_stop_strategy()
{
	std::shared_ptr<S> strategy = std::make_shared<S>(this, GRAV_CONSTANT);
	stop_strategy = std::static_pointer_cast<StopStrategy>(strategy);
	return strategy;
}

} // namespace StarLib

#endif /* SIMULATION_H_ */
