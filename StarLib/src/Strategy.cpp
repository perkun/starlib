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


void ForceStrategy::relative_nbody(std::vector<Vec3> &pos, std::vector<Vec3> &vel, double t,
		   std::vector<Vec3> &g)
{
    // calculate distances first:
    int num_bodies = context->get_num_particles();
    Vec3 distances[num_bodies][num_bodies];
    Vec3 uks[num_bodies];
    for (int i = 0; i < num_bodies; i++)
    {
        for (int k = i + 1; k < num_bodies; k++)
        {

            Vec3 dif = pos[k] - pos[i];
            double len = dif.length();
            dif /= len * len * len;

            distances[i][k] = dif;
            distances[k][i] = -1. * dif;
        }

        double len = pos[i].length();
        uks[i] = pos[i] / (len * len * len);
    }

    for (int i = 0; i < num_bodies; i++)
    {
        Vec3 acc(0.);
        for (int k = 0; k < num_bodies; k++)
        {
            if (i == k)
                continue;

            double mass_k =
                context->get_particle(k).get_component<MassComponent>().mass;
            if (mass_k == 0.0)
                continue;

            acc += (distances[i][k] - uks[k]) * mass_k;
        }
        // central mass acceleration
        double mass =
            context->get_particle(i).get_component<MassComponent>().mass;
        acc -= uks[i] * (central_mass + mass);

        g[i] = acc * GRAV_CONSTANT;
    }

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
