#include "PlanetBuilder.h"

using namespace std;
using namespace StarLib;

PlanetBuilder::PlanetBuilder(const PlanetsConfig &cfg)
    : cfg(cfg),  SwarmBuilder(cfg.planets.size())
{
}


PlanetBuilder::~PlanetBuilder()
{
}


Swarm PlanetBuilder::setup(std::vector<Particle> particles)
{
    map<string, double> masses = {
        {"jupiter", 1. / StarLib::CONSTANTS::SUN_JUPITER_MASS_RATIO},
        {"saturn", 1. / StarLib::CONSTANTS::SUN_SATURN_MASS_RATIO},
        {"uranus", 1. / StarLib::CONSTANTS::SUN_URANUS_MASS_RATIO},
        {"neptune", 1. / StarLib::CONSTANTS::SUN_NEPTUNE_MASS_RATIO},
        {"mercury", 1. / StarLib::CONSTANTS::SUN_MERCURY_MASS_RATIO},
        {"venus", 1. / StarLib::CONSTANTS::SUN_VENUS_MASS_RATIO},
        {"earth", 1. / StarLib::CONSTANTS::SUN_EARTH_MOON_MASS_RATIO},
        {"mars", 1. / StarLib::CONSTANTS::SUN_MARS_MASS_RATIO},
        {"pluto", 1. / StarLib::CONSTANTS::SUN_PLUTO_MASS_RATIO}};

    Swarm swarm;
    for (int i = 0; i < num_particles; i++)
    {
        Particle &p = particles[i];
        PlanetsConfig::Planet cfg_planet = cfg.planets[i];

        auto states = IO::parse_horizons_vectors(cfg_planet.horizon_filename);
		p.add_component<NameComponent>(cfg_planet.name);
		p.add_component<MassComponent>(masses[cfg_planet.name]);
		p.get_component<StateComponent>().state = states.front();

		swarm.push_particle(p);
    }

    return swarm;
}
