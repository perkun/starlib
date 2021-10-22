#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <iostream>
#include <memory>
#include <stdio.h>
#include "Integrator.h"
#include "Particle.h"
#include "entt.hpp"
#include "Components.h"

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

	void set_force_strategy(std::shared_ptr<Strategy> strategy);
	void set_step_strategy(std::shared_ptr<Strategy> strategy);
	void set_stop_strategy(std::shared_ptr<StopStrategy> strategy);

	void run();
	double get_integration_time();

	Particle& get_particle(int i);

private:
    std::shared_ptr<Integrator> integrator = nullptr;

    std::shared_ptr<Strategy> force_strategy, step_strategy;
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

} // namespace StarLib

#endif /* SIMULATION_H_ */
