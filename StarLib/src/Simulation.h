#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <iostream>
#include <memory>
#include <stdio.h>
#include "Bodies.h"
#include "BodyStoreConverter.h"
#include "Integrator.h"

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

	void run();
	double get_integration_time();
	BodyStore get_results();

    double duration;

    // data for integration
	BodyStore body_store;
private:
    std::shared_ptr<Integrator> integrator;
	double sequence_size = 0.001;
	int precision = 14;
	double time_arrow = TimeArrow::FUTURE;

	void prep_integrator();
	void set_integrator_initial_data();
	void run_integrator();
	void collect_integrator_results();

	BodyStore integrated_body_store;

};

} // namespace StarLib

#endif /* SIMULATION_H_ */
