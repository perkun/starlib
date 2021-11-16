#include "RandomPopulationBuilder.h"

using namespace std;
using namespace StarLib;


double random_d(double min, double max)
{
    return (double)rand() / RAND_MAX * (max - min) + min;
}


RandomPopulationBuilder::RandomPopulationBuilder(
    const RandomPopulationConfig &cfg, double G)
    : cfg(cfg), GRAV_CONSTANT(G), SwarmBuilder(cfg.num_objects)
{
}


RandomPopulationBuilder::~RandomPopulationBuilder()
{
}


Swarm RandomPopulationBuilder::setup(std::vector<Particle> particles)
{
	Swarm swarm;
	set_random_generator_seed(cfg.seed);

	for (int i = 0; i < particles.size(); i++)
	{
		Particle &p = particles[i];
		double mass = calc_random_mass();
		p.add_component<MassComponent>(mass);
		p.add_component<NameComponent>(make_name(i));

		Orbit orbit(make_random_elements(), GRAV_CONSTANT * (1. + mass), cfg.jd);
		p.get_component<StateComponent>().state = orbit.state_vector(cfg.jd);

		swarm.push_particle(p);
	}


	return swarm;
}






void RandomPopulationBuilder::set_random_generator_seed(unsigned int seed)
{
	srand(seed);
}


double RandomPopulationBuilder::calc_random_mass()
{
    return random_d(cfg.mean_mass - cfg.mass_range / 2.,
                    cfg.mean_mass + cfg.mass_range / 2.);
}


std::string RandomPopulationBuilder::make_name(int i)
{
	char name[100];
	sprintf(name, "KB_%02d", i);
	return string(name);
}


StarLib::OrbitalElements RandomPopulationBuilder::make_random_elements()
{
    double tp_min = cfg.jd - cfg.tp_range / 2;
    double tp_max = cfg.jd + cfg.tp_range / 2;

    return OrbitalElements(
        random_d(cfg.q_min, cfg.q_max),
        random_d(cfg.e_min, cfg.e_max),
        random_d(cfg.i_min, cfg.i_max),
        random_d(cfg.omega_min, cfg.omega_max),
        random_d(cfg.Omega_min, cfg.Omega_max),
        random_d(tp_min, tp_max));

}
