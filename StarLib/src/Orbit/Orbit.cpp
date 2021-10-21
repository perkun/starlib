#include "Orbit.h"
#include <cmath>

namespace StarLib
{

const double Orbit::E_SMALL = 1e-12;

// Orbit::Orbit()
// {
// }
Orbit::Orbit(const OrbitalElements &elems, double mu, double epoch)
    : elements(elems), mu(mu), epoch(epoch)
{
	shape = determine_shape(elements.e);
}

Orbit::Orbit(const StateVector &state, double mu) : mu(mu), epoch(state.time)
{
	calc_elements(state.position, state.velocity, mu);
}

Orbit::Orbit(const Vec3 &pos, const Vec3 &vel, double mu, double epoch)
    : mu(mu), epoch(epoch)
{
    calc_elements(pos, vel, mu);  // sets the shape member
}



Orbit::~Orbit()
{
}

Orbit::Shape Orbit::determine_shape(double e)
{
    // TODO check for orbit degeneracy (via vis viva)

    if (e < 1. - E_SMALL)
        return Shape::ELIPSE;
    else if (e > 1.0 + E_SMALL)
        return Shape::HYPERBOLA;
    else // if (e >= 1. - E_SMALL && e <= 1. + E_SMALL)
        return Shape::PARABOLA;

    return Shape::ELIPSE;
}


double Orbit::n()
{
    return mean_motion();
}


double Orbit::mean_motion()
{
    if (shape == Shape::PARABOLA)
    {
        double p = 2 * elements.q;
        return sqrt(mu / p / p / p);
    }
    else
    {
        double a = abs(semimajor_axis());
        return sqrt(mu / (a * a * a));
    }
}


double Orbit::a()
{
    return semimajor_axis();
}


double Orbit::semimajor_axis()
{
    if (shape == Shape::ELIPSE)
    {
        return elements.q / (1. - elements.e);
    }
    else if (shape == Shape::HYPERBOLA)
    {
        return -elements.q / (elements.e - 1.);
    }
    else
        return 0.0;
}


double Orbit::period()
{
    return 2 * M_PI / mean_motion();
}


double Orbit::M(double t)
{
    return mean_anomaly(t);
}


double Orbit::mean_anomaly(double t)
{
    double M = mean_motion() * (t - elements.tp);
    if (shape == ELIPSE)
    {
        while (M >= 2 * M_PI)
            M -= 2 * M_PI;
        while (M < 0.)
            M += 2 * M_PI;
    }

    return M;
}


double Orbit::p()
{
	return semilatus();
}

double Orbit::semilatus()
{
	return elements.q * (1. + elements.e);
}


void Orbit::calc_elements(const Vec3 &pos, const Vec3 &vel, double mu)
{
    double r = pos.length();
    double v = vel.length();

    // 2. vis viva, angular momentum end laplace vector
    double h = 0.5 * v * v - mu / r; // vis viva
    Vec3 G = cross(pos, vel);  // ang. momentum
    Vec3 laplace = cross(vel, G) / mu - normalize(pos);
    double e = laplace.length();

    double a = mu / 2. / fabs(h);
    shape = determine_shape(e);

    double q;
    if (shape == Shape::ELIPSE)
        q = a * (1. - e);
    else if (shape == Shape::HYPERBOLA)
        q = a * (e - 1.);
    else if (shape == Shape::PARABOLA)
        q = 0.5 * (G.length() * G.length() / mu);


    // TODO use
    // i = 2*arctg(sqrt(G1^2 + G2^2)/G + G3), or
    // i = 2*arctg(G-G3/sqrt(G1^2 + G2^2))
    // depending on the values of G use the correct type for
    // maximum precision
    double s = (sqrt(G.x * G.x + G.y * G.y) / G.length());
    double c = (G.z / G.length());

    double i = acos(c);

    double omega, Omega;
    if (i < E_SMALL || fabs(i - M_PI) < E_SMALL)
        Omega = 0.; // undetermined (orbit in xy plane)
    else
    {
        Omega = 2 * atan2((G.length() * s + G.y), G.x);
    }

    if (e < E_SMALL || s < E_SMALL)
        omega = 0.; // undetermined
    else
    {
        double sin_om = laplace.z / (e * s);
        double cos_om =
            (G.x * laplace.y - G.y * laplace.x) / (G.length() * e * s);

        omega = 2 * atan2(1. - cos_om, sin_om);
    }

    // mean anomaly
    double cos_f = dot(laplace, pos) / (e * r);
    double sin_f =
        dot(G, cross(laplace, pos)) / (G.length() * e * r);
    double D = (1. - cos_f) / sin_f;

    // can' use mean_anomaly() function, because tp is yet unknown
    double M;
    if (shape == Shape::ELIPSE)
    {
        double E = 2 * atan(sqrt((1. - e) / (1. + e)) * D);
        M = E - e * sin(E);
        if (M >= 2 * M_PI)
            M -= 2 * M_PI;
        if (M < 0.)
            M += 2 * M_PI;
    }
    else if (shape == Shape::HYPERBOLA)
    {
        double E = log((1. + e + D * sqrt(e * e - 1.)) /
                       (1 + e - D * sqrt(e * e - 1.)));
        M = e * sinh(E) - E;
    }
    else if (shape == Shape::PARABOLA)
    {
        M = (D * D * D / 3. + 1) * D / 2.;
    }

    // mean motion
    double n;
    if (shape == Shape::PARABOLA)
    {
        double p = 2 * q;
        n = sqrt(mu / p / p / p);
    }
    else
        n = sqrt(mu / a / a / a);

    double time_since_peri = M / n;

    if (shape == Shape::ELIPSE)
    {
        double period = 2 * M_PI / n;
        if (time_since_peri > period / 2.)
            time_since_peri = time_since_peri - period;
        else if (time_since_peri < -period / 2.) // tp is negative and beyond period/2
            time_since_peri = time_since_peri + period;
    }

    elements = OrbitalElements(q, e, i, omega, Omega, epoch - time_since_peri);
}


StateVector Orbit::state_vector(double t)
{
    double f = true_anomaly(t - elements.tp);
    // 	f = 3.229629609971929E+02 * M_PI / 180.;

    double p = semilatus();
    double r = p / (1. + (elements.e * cos(f)));

    //     printf("t = %.16lf, f = %.16lf\n", t, f);

    Vec3 pos(r * cos(f), r * sin(f), 0.);
    Vec3 vel(-sqrt(mu / p) * sin(f), sqrt(mu / p) * (cos(f) + elements.e), 0.);

    // rotations (active!)
    pos = rotate_z(
			rotate_x(
				rotate_z(pos, elements.omega),
			elements.i),
          elements.Omega);
    //
    vel = rotate_z(
			rotate_x(
				rotate_z(vel, elements.omega),
			elements.i),
          elements.Omega);

    return StateVector(pos, vel, t);
}


double Orbit::true_anomaly(double dt)
{
    /***************************************************************************
    **                     Pomysł i algorytm: **
    **     G.Sitarski  (1968), Acta Astronomica,vol.18,no.2,pp 197-205, **
    ****************************************************************************
    **   Programmed by: Piotr A. Dybczyński,     Last modified: 3.03.2012 **
    ***************************************************************************/

    const double &e = elements.e;
    const double &q = elements.q;

    double x, M, M1, E, E1, w, F, v, u, F1, z, n, mi;

    x = (1. - e) / (1. + e);

	mi = mu;

    if (e < (1. - E_SMALL)) /* elipsa */
    {
        n = sqrt(mi * (1. - e) * (1. - e) * (1. - e) / (q * q * q));
        M = n * dt;
        M = fmod(M, 2.0 * M_PI);

        M1 = fabs(M);
        E1 = M_PI;
        do
        {
            E = E1;
            E1 = E + (v = M1 - E + e * sin(E)) / (1. - e * cos(E));
        } while (fabs(v) > fabs(M1 - E1 + e * sin(E1)));

        if (1. != 1. + cos(E1 / 2.))
            w = sqrt(1. / x) * tan(E1 / 2.);
        else
            w = 1.0E+70; /* theta = 180 deg*/
    }

    else if (e > (1. + E_SMALL)) /*hiperbola */
    {
        M = sqrt(mi * (e - 1.) * (e - 1.) * (e - 1.) / (q * q * q)) * dt;

        M1 = fabs(M);
        F1 = 1;
        while ((z = M1 + F1 - e * sinh(F1)) > 0.0)
            F1 += 1.;
        do
        {
            F = F1;
            F1 = F + (v = z) / (e * cosh(F) - 1.);
        } while (fabs(v) > fabs(z = M1 + F1 - e * sinh(F1)));
        w = sqrt(-1. / x) * tanh(F1 / 2.);
    }
    else /* bliskoparabola: e = 1 +/- E_SMALL */
    {
        M = sqrt(mi / (2. * q * q * q)) * dt;

        u = fabs(M) * 1.5;
        v = sqrt(1. + u * u);
        w = pow((v + u), 1. / 3.) - pow((v - u), 1. / 3.);
    }


    double f = (M < 0 ? -2. * atan(w) : 2. * atan(w));

	if (isnan(f))
		return 0.;

	while (f < 0.)
		f += 2. * M_PI;
	while (f >= 2. * M_PI)
		f -= 2. * M_PI;
//
    return f;
}

void Orbit::print(double t)
{
    const double to_deg = 180. / M_PI;
    printf("EC= %.16e QR= %.16e IN= %.16e\n", elements.e, elements.q,
           elements.i * to_deg);
    printf("OM= %.16e W = %.16e Tp=  %.16lf\n", elements.Omega * to_deg,
           elements.omega * to_deg, elements.tp);
    printf("N = %.16e MA= %.16e TA= %.16e\n", mean_motion()*to_deg,
           mean_anomaly(t) * to_deg, true_anomaly(t-elements.tp) * to_deg);
    printf("A = %.16e AD= %.16e PR= %.16e\n", semimajor_axis(), 0., period());
}


} // namespace StarLib


