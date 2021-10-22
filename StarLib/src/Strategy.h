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

protected:
	Simulation* context = nullptr;
};


class ForceStrategy : public Strategy
{
public:
    void execute(std::vector<Vec3> &pos, std::vector<Vec3> &vel,
                         double t, std::vector<Vec3> &g);
	ForceStrategy* push_function(std::function<void(std::vector<Vec3> &pos,
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


class StepStrategy : public Strategy
{
public:
    void execute(std::vector<Vec3> &pos, std::vector<Vec3> &vel,
                         double t);
	StepStrategy* push_function(std::function<void(std::vector<Vec3> &pos,
					   std::vector<Vec3> &vel, double t)>
		fn);


protected:
    std::vector<
        std::function<
						void(std::vector<Vec3> &pos, std::vector<Vec3> &vel,
								double t)
					>
			   > functions;

};


class StopStrategy: public Strategy
{
public:
	StopStrategy() {}
	StopStrategy(Simulation *simulation);
	~StopStrategy() {}

    virtual bool should_stop(std::vector<Vec3> &pos, std::vector<Vec3> &vel,
                             double t);
protected:
};



} // namespace StarLib

#endif /* STRATEGY_H_ */
