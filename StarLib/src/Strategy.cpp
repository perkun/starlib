#include "Strategy.h"
#include "Simulation.h"


namespace StarLib
{

Strategy::Strategy(Simulation *simulation)
{
	set_context(simulation);
}

void Strategy::set_context(Simulation *simulation)
{
	context = simulation;
}


Strategy* Strategy::push_function(std::function<void(std::vector<Vec3> &pos,
				   std::vector<Vec3> &vel, double t, std::vector<Vec3> &g)>
	fn)
{
	functions.push_back(fn);
	return this;
}


void Strategy::execute(std::vector<Vec3> &pos, std::vector<Vec3> &vel, double t,
                       std::vector<Vec3> &g)
{
	for (auto fn: functions)
		fn(pos, vel, t, g);
}


StopStrategy::StopStrategy(Simulation *simulation)
{
	set_context(simulation);
}

void StopStrategy::set_context(Simulation *simulation)
{
	context = simulation;
}

bool StopStrategy::should_stop(std::vector<Vec3> &pos, std::vector<Vec3> &vel, double t)
{
	return false;
}

} // namespace StarLib


