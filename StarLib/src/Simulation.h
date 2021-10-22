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
    Simulation();
    ~Simulation();

    void set_duration_and_direction(double duration, double time_arrow)
    {
        this->duration = duration;
        this->time_arrow = time_arrow;
    }
    Particle create_particle(StateVector sv = StateVector());


    template <typename S>
    std::shared_ptr<ForceStrategy> create_force_strategy();
    template <typename S> std::shared_ptr<StepStrategy> create_step_strategy();
    template <typename S> std::shared_ptr<StopStrategy> create_stop_strategy();

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
    double get_integration_time();

    Particle &get_particle(int i);

private:
    std::shared_ptr<Integrator> integrator = nullptr;

    std::shared_ptr<ForceStrategy> force_strategy;
    std::shared_ptr<StepStrategy> step_strategy;
    std::shared_ptr<StopStrategy> stop_strategy;

    double duration;
    double time_arrow = TimeArrow::FUTURE;

    void prep_integrator();
    void set_integrator_initial_data();
    void run_integrator();
    void collect_integrator_results();

    entt::registry registry;

    std::vector<Particle> particle_order;
};


template <typename S>
std::shared_ptr<ForceStrategy> Simulation::create_force_strategy()
{
	force_strategy = std::make_shared<S>();
	force_strategy->set_context(this);
	return force_strategy;
}


template <typename S>
std::shared_ptr<StepStrategy> Simulation::create_step_strategy()
{
	step_strategy = std::make_shared<S>();
	step_strategy->set_context(this);
	return step_strategy;
}


template <typename S>
std::shared_ptr<StopStrategy> Simulation::create_stop_strategy()
{
	stop_strategy = std::make_shared<S>();
	stop_strategy->set_context(this);
	return stop_strategy;
}

} // namespace StarLib

#endif /* SIMULATION_H_ */
