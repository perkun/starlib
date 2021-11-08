#include <iostream>
#include <stdio.h>
#include "Simulation.h"
#include "Strategy.h"
#include "RosetteBuilder.h"
#include "Gravity.h"
#include "Units.h"

using namespace std;
using namespace StarLib;

class RelativeForceStrategy : public ForceStrategy
{
public:
    RelativeForceStrategy(Simulation *sim, double grav_constant)
        : ForceStrategy(sim, grav_constant)
    {
    }
    ~RelativeForceStrategy() {}

    double central_mass;

    void relative_nbody(std::vector<Vec3> &pos, std::vector<Vec3> &vel,
                        double t, std::vector<Vec3> &g);

private:
};

void RelativeForceStrategy::relative_nbody(std::vector<Vec3> &pos, std::vector<Vec3> &vel, double t,
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

int main(int argc, char *argv[])
{
    double GRAV_CONSTANT =
        Gravity::gravitational_constant(UNITS::AU, UNITS::DAY, UNITS::MASS_SUN);

    double sun_mass = 1.0;

    Simulation sim(GRAV_CONSTANT);
    sim.set_duration_and_direction(1e5, TimeArrow::FUTURE);

    RosetteBuilder rosette_builder(7, sun_mass, 1e-4, 1.0, 0.2819,
                                   GRAV_CONSTANT);
    Swarm bodies = sim.create_swarm(rosette_builder);

    //     shared_ptr<RelativeForceStrategy> force_strategy =
    //         sim.create_force_strategy<RelativeForceStrategy>();
    auto force_strategy = sim.create_force_strategy();
    force_strategy->push_lambda(
        [&sim, &sun_mass, &GRAV_CONSTANT](vector<Vec3> &pos, vector<Vec3> &vel, double t,
                          vector<Vec3> &g)
        {
            // calculate distances first:
            int num_bodies = sim.get_num_particles();
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

                    double mass_k = sim.get_particle(k)
                                        .get_component<MassComponent>()
                                        .mass;
                    if (mass_k == 0.0)
                        continue;

                    acc += (distances[i][k] - uks[k]) * mass_k;
                }
                // central mass acceleration
                double mass = sim.get_particle(i)
                                  .get_component<MassComponent>()
                                  .mass;
                acc -= uks[i] * (sun_mass + mass);

                g[i] = acc * GRAV_CONSTANT;
            }
        });

    sim.run();

    for (int i = 0; i < sim.get_num_particles(); i++)
    {
        StateVector &state =
            sim.get_particle(i).get_component<StateComponent>().state;
		cout << i << "\t" << state.position << endl;
    }

    return 0;
}
