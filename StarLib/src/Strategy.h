#ifndef STRATEGY_H_
#define STRATEGY_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include <memory>
#include <functional>
#include "Potential.h"
#include "starlibmath.h"

namespace StarLib
{

class Strategy
{
public:
    Strategy() { }
    ~Strategy() { }

    void execute(std::vector<Vec3> &pos, std::vector<Vec3> &vel,
                         double t, std::vector<Vec3> &g);
	Strategy* push_function(std::function<void(std::vector<Vec3> &pos,
					   std::vector<Vec3> &vel, double t, std::vector<Vec3> &g)>
		fn);

protected:
    std::vector<
        std::function<
						void(std::vector<Vec3> &pos, std::vector<Vec3> &vel,
								double t, std::vector<Vec3> &g)
					>
			   > functions;
};



class StopStrategy
{
public:
	StopStrategy() {}
	~StopStrategy() {}
    virtual bool should_stop(std::vector<Vec3> &pos, std::vector<Vec3> &vel,
                             double t) = 0;
};

} // namespace StarLib

#endif /* STRATEGY_H_ */
