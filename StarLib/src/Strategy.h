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

class Simulation;

class Strategy
{
public:
	Strategy() {}
    Strategy(Simulation *simulation);
    ~Strategy() { }

	void set_context(Simulation *simulation);
	Simulation* get_context() { return context; }

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

	Simulation* context = nullptr;
};



class StopStrategy
{
public:
	StopStrategy() {}
	StopStrategy(Simulation *simulation);
	~StopStrategy() {}

	void set_context(Simulation *simulation);
	Simulation* get_context() { return context; }

    virtual bool should_stop(std::vector<Vec3> &pos, std::vector<Vec3> &vel,
                             double t);

protected:
	Simulation* context = nullptr;
};



} // namespace StarLib

#endif /* STRATEGY_H_ */
