#include "Strategy.h"


namespace StarLib
{


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

} // namespace StarLib


