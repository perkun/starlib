#ifndef ORBIT_H_
#define ORBIT_H_

#include <iostream>
#include <stdio.h>

#include "StateVector.h"
#include "OrbitalElements.h"
// #include "Constants.h"

namespace StarLib
{


class Orbit
{
public:
    static const double E_SMALL;

    enum Shape
    {
        ELIPSE,
        PARABOLA,
        HYPERBOLA,
        LINEAR
    };

	// should be a namespace?
    struct Epoch
    {
        static constexpr double J2000 = 2451545.0;
    };


    Orbit() = delete;
    Orbit(const OrbitalElements &elems, double mu, double epoch = Epoch::J2000);
    Orbit(const Vec3 &pos, const Vec3 &vel, double mu,
          double epoch = Epoch::J2000);
	Orbit(const StateVector &state, double mu);
    ~Orbit();

    static Shape determine_shape(double e);

    double n();
    double mean_motion();
    double a();
    double semimajor_axis();
    double period();
    double M(double t);
    double mean_anomaly(double t);
	double p();
	double semilatus();

	void print(double t);


	StateVector state_vector(double t);

    OrbitalElements elements;
    const double mu; // gravitational parameter $\mu$
    Shape shape;

	double epoch;
protected:
    double true_anomaly(double dt);
    void calc_elements(const Vec3 &pos, const Vec3 &vel, double mu);

};


} // namespace StarLib

#endif /* ORBIT_H_ */
