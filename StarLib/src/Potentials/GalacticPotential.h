#ifndef GALACTIC_POTENTIAL_H_
#define GALACTIC_POTENTIAL_H_

#include "Potential.h"
#include "GalPotMcMillan/GalPot.h"

namespace StarLib {


class GalacticPotential : public Potential
{
public:
	virtual ~GalacticPotential() {}

	virtual Vec3 get_sun_velocity();
	string description;
	string description_short;

    double sun_galactic_distance;
    double sun_mean_orbital_speed;
	double sun_pos_z;
private:

};


class GalacticPotential_IWTS_Ia : public GalacticPotential
{
public:
    GalacticPotential_IWTS_Ia() = default;
    GalacticPotential_IWTS_Ia(double gauss2);
    double M_b, M_d, M_h, a_h, b_b, a_d, b_d;
    double gauss2;

    virtual Vec3 get_acceleration(const Vec3 &pos) override;

	void print_parameters();

protected:
    virtual Vec3 acc_bulge(const Vec3 &pos, double galactic_distance);
    virtual Vec3 acc_disk(const Vec3 &pos, double cylindrical_distance);
    virtual Vec3 acc_halo(const Vec3 &pos, double galactic_distance);
};


class GalacticPotential_IWTS_Ib : public GalacticPotential_IWTS_Ia
{
public:
    GalacticPotential_IWTS_Ib(double gauss2);
};


class GalacticPotential_IWTS_IIIa : public GalacticPotential_IWTS_Ia
{
public:
	GalacticPotential_IWTS_IIIa() = default;
	GalacticPotential_IWTS_IIIa(double gauss2);

    virtual Vec3 acc_halo(const Vec3 &pos, double galactic_distance) override;

};


class GalacticPotential_IWTS_IIIb : public GalacticPotential_IWTS_IIIa
{
public:
	GalacticPotential_IWTS_IIIb(double gauss2);
};


class GalacticPotential_McMillan : public GalacticPotential
{
public:
    GalacticPotential_McMillan();
    ~GalacticPotential_McMillan()
    {
        delete Phi;
    }

    virtual Vec3 get_acceleration(const Vec3 &pos) override;

private:
	McMillan::GalaxyPotential *Phi;
};

}

#endif
