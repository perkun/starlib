#include "RosetteBuilder.h"


namespace StarLib
{
RosetteBuilder::RosetteBuilder(int num_particles, double central_mass,
                               double mass, double q, double e,
                               double grav_const)
    : central_mass(central_mass), mass(mass), q(q), e(e),
      GRAV_CONSTANT(grav_const), SwarmBuilder(num_particles)
{
}


RosetteBuilder::~RosetteBuilder() {}


Swarm RosetteBuilder::setup(std::vector<Particle> particles)
{
	Swarm swarm;
    double k = polygon_constant(num_particles);
    double mu = GRAV_CONSTANT * (central_mass + k * num_particles * mass);

    for (int i = 0; i < num_particles; i++)
    {
        double omega = i * (2 * M_PI / num_particles);
        Orbit orbit(OrbitalElements(q, e, 0.0, omega, 0.0, 0.0), mu, 0.0);

        particles[i].add_component<MassComponent>(mass);
        particles[i].get_component<StateComponent>().state =
            orbit.state_vector(0.0);

		swarm.push_particle(particles[i]);
    }

    return swarm;
}


double RosetteBuilder::polygon_constant(int n)
{
    double k = 0;
    if (n % 2 == 0) // even
    {
        k = 0.5;
        for (int i = 1; i <= (n - 2) / 2; i++)
            k += 1. / cos(M_PI / n * i);
    }
    else // odd
    {
        for (int i = 1; i <= (n - 1) / 2; i++)
            k += 1. / cos(M_PI / 2. / n * (2 * i - 1));
    }
    k = 1. / 2. / n * k;
    return k;
}


} // namespace StarLib
