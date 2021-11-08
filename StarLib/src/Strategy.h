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
class Particle;



class Strategy
{
public:
    Strategy(Simulation *simulation, double grav_const);
    ~Strategy() { }

	void set_context(Simulation *simulation);
	Simulation* get_context() { return context; }
	Particle &get_particle(int i);


protected:
	Simulation* context = nullptr;
	const double GRAV_CONSTANT;

};


class ForceStrategy : public Strategy
{
public:
    ForceStrategy(Simulation *simulation, double grav_const)
        : Strategy(simulation, grav_const)
    {
    }

    void execute(std::vector<Vec3> &pos, std::vector<Vec3> &vel, double t,
                 std::vector<Vec3> &g);
    ForceStrategy *push_lambda(
        std::function<void(std::vector<Vec3> &pos, std::vector<Vec3> &vel,
                           double t, std::vector<Vec3> &g)>
            fn)
    {
        functions.push_back(fn);
        return this;
    }

    template <typename Func> ForceStrategy *push_member_func(Func fn)
    {
        auto binded_fn =
            std::bind(fn, this, std::placeholders::_1, std::placeholders::_2,
                      std::placeholders::_3, std::placeholders::_4);

        functions.push_back(binded_fn);
        return this;
    }


protected:
    std::vector<
        std::function<void(std::vector<Vec3> &pos, std::vector<Vec3> &vel,
                           double t, std::vector<Vec3> &g)>>
        functions;

public:
    /** predefined functions, that can be pushed by client */
    void dummy(std::vector<Vec3> &pos, std::vector<Vec3> &vel, double t,
               std::vector<Vec3> &g)
    {
        std::cout << "Dummy force function \n";
    }



};


class StepStrategy : public Strategy
{
public:
    StepStrategy(Simulation *simulation, double grav_const)
        : Strategy(simulation, grav_const)
    {
    }
    void execute(std::vector<Vec3> &pos, std::vector<Vec3> &vel, double t);

	StepStrategy* push_lambda(std::function<void(std::vector<Vec3> &pos,
					   std::vector<Vec3> &vel, double t)>
		fn)
	{
		functions.push_back(fn);
		return this;
	}


	template <typename Func>
	StepStrategy* push_member_func(Func fn)
	{
		auto binded_fn = std::bind(fn, this, std::placeholders::_1,
								   std::placeholders::_2,
								   std::placeholders::_3);

		functions.push_back(binded_fn);
		return this;
	}


protected:
    std::vector<
        	std::function<
				void(std::vector<Vec3> &pos, std::vector<Vec3> &vel, double t)
			>
	> functions;

public:
	/** predefined functions, that can be pushed by client */
	void print_mass(std::vector<Vec3> &pos, std::vector<Vec3> &vel, double t);

};


class StopStrategy: public Strategy
{
public:
    StopStrategy(Simulation *simulation, double grav_const)
        : Strategy(simulation, grav_const)
    {
    }
	~StopStrategy() {}

    virtual bool should_stop(std::vector<Vec3> &pos, std::vector<Vec3> &vel,
                             double t);
	void set_stop_func(
			std::function<bool(std::vector<Vec3> &pos, std::vector<Vec3> &vel, double t)> fn)
	{
		stop_function = fn;
	}

protected:
	std::function<bool(std::vector<Vec3> &pos, std::vector<Vec3> &vel, double t)>
		stop_function = [](std::vector<Vec3> &pos, std::vector<Vec3> &vel, double t)
		{ return false; };

};



} // namespace StarLib

#endif /* STRATEGY_H_ */
