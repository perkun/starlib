#ifndef INTEGRATOR_H_
#define INTEGRATOR_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <memory>
#include "starlibmath.h"
#include "Strategy.h"


namespace StarLib
{


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

    double integrate(double time_delta, double sequence_size, int precision);
    void set_conditions(const std::vector<Vec3> &pos,
                        const std::vector<Vec3> &vel,
                        const std::vector<double> &m);

    std::vector<Vec3> positions;
    std::vector<Vec3> velocities;
    std::vector<double> masses;

    int num_bodies = 0;
    int iteration = 0;

    const EQ_CLASS nclass; // class of the problem for ra15

    double get_integration_time()
    {
        return tm;
    }

protected:
    std::shared_ptr<Strategy> force_strategy, step_strategy;
    std::shared_ptr<StopStrategy> stop_strategy;
    double tm;
};
}

#endif /* INTEGRATOR_H_ */
