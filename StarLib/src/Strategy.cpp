#include "Strategy.h"
#include "Simulation.h"


namespace StarLib
{


Strategy::Strategy(Simulation *simulation, double grav_const)
    : GRAV_CONSTANT(grav_const)
{
    set_context(simulation);
}

void Strategy::set_context(Simulation *simulation) { context = simulation; }


Particle &Strategy::get_particle(int i) { return context->get_particle(i); }


void ForceStrategy::execute(std::vector<Vec3> &pos, std::vector<Vec3> &vel,
                            double t, std::vector<Vec3> &g)
{
    for (Vec3 &acc : g)
        acc = Vec3(0.);

    for (auto fn : functions)
        fn(pos, vel, t, g);
}




void StepStrategy::execute(std::vector<Vec3> &pos, std::vector<Vec3> &vel,
                           double t)
{
    for (auto fn : functions)
        fn(pos, vel, t);
}


void StepStrategy::print_mass(std::vector<Vec3> &pos, std::vector<Vec3> &vel,
                              double t)
{
    int num_bodies = pos.size();
    for (int i = 0; i < num_bodies; i++)
    {
        double mass = get_particle(i).get_component<MassComponent>().mass;
        std::cout << "body " << i << ", mass: " << mass << std::endl;
    }
}


bool StopStrategy::should_stop(std::vector<Vec3> &pos, std::vector<Vec3> &vel,
                               double t)
{
    return stop_function(pos, vel, t);
}

} // namespace StarLib
