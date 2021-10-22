#include "Strategy.h"
#include "Simulation.h"


namespace StarLib
{


Strategy::Strategy(Simulation *simulation) { set_context(simulation); }

void Strategy::set_context(Simulation *simulation) { context = simulation; }


ForceStrategy *ForceStrategy::push_function(
    std::function<void(std::vector<Vec3> &pos, std::vector<Vec3> &vel, double t,
                       std::vector<Vec3> &g)>
        fn)
{
    functions.push_back(fn);
    return this;
}


void ForceStrategy::execute(std::vector<Vec3> &pos, std::vector<Vec3> &vel,
                            double t, std::vector<Vec3> &g)
{
    for (auto fn : functions)
        fn(pos, vel, t, g);
}


StepStrategy *StepStrategy::push_function(
    std::function<void(std::vector<Vec3> &pos, std::vector<Vec3> &vel,
                       double t)>
        fn)
{
    functions.push_back(fn);
    return this;
}


void StepStrategy::execute(std::vector<Vec3> &pos, std::vector<Vec3> &vel,
                           double t)
{
    for (auto fn : functions)
        fn(pos, vel, t);
}


StopStrategy::StopStrategy(Simulation *simulation) { set_context(simulation); }


bool StopStrategy::should_stop(std::vector<Vec3> &pos, std::vector<Vec3> &vel,
                               double t)
{
    return false;
}

} // namespace StarLib
