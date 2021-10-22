#ifndef INTEGRATOR_H_
#define INTEGRATOR_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <memory>
#include "starlibmath.h"


namespace StarLib
{

class ForceStrategy;
class StepStrategy;
class StopStrategy;

enum EQ_CLASS
{
    /**
    y'=f(y,t) is nclass=1, y''=f(y,t) is nclass=-2, y''=f(y',y,t) is nclass=2.
    */

    FIRST_DERIVATIVE = 1,
    SECOND_DERIVATIVE = -2,
    SECOND_DERIVATIVE_DEPENDENT = 2
};


class Integrator
{
public:
    Integrator() = delete;
    Integrator(EQ_CLASS nclass) : nclass(nclass) { }
    ~Integrator() { }


	double sequence_size = 0.001;
	int precision = 14;

    double integrate(double time_delta);

    std::vector<Vec3> pos;
    std::vector<Vec3> vel;

//     int num_bodies = 0;
    int iteration = 0;

    const EQ_CLASS nclass; // class of the problem for ra15

    double get_integration_time()
    {
        return tm;
    }

    std::shared_ptr<ForceStrategy> force_strategy;
	std::shared_ptr<StepStrategy> step_strategy;
    std::shared_ptr<StopStrategy> stop_strategy;

protected:
    double tm;
};
}

#endif /* INTEGRATOR_H_ */
