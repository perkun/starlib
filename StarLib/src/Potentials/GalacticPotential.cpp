#include "GalacticPotential.h"

#define KMS_TO_PCMY (1.0227)

namespace StarLib {


Vec3 GalacticPotential::get_sun_velocity()
{
	return Vec3(
			11.1 * KMS_TO_PCMY,
			(sun_mean_orbital_speed + 12.24) * KMS_TO_PCMY,
			7.25 * KMS_TO_PCMY);
}


GalacticPotential_IWTS_Ia::GalacticPotential_IWTS_Ia(double gauss2)
{
		this->gauss2 = gauss2;

        M_b = 9509250000.0;  // M_sun
        M_d = 66402000000.0;
        M_h = 23668500000.0;
        b_b = 230; 			 // pc
        b_d = 292;
        a_d = 4220;
        a_h = 2562;

        sun_galactic_distance = 8400.0;
		sun_pos_z = 17;
		// z value (distance above galactic disk) = 17.0 from
		// Joshi(2017)
        sun_mean_orbital_speed = 242.0;

		description = "IWTS Model Ia, parameters from Irrgang et.al 2013";
		description_short = "IWTS_Ia";

}

Vec3 GalacticPotential_IWTS_Ia::get_acceleration(const Vec3 &pos)
{
    double galactic_distance = pos.length();
    double cylindrical_distance = sqrt(pos.x * pos.x + pos.y * pos.y);

    return acc_bulge(pos, galactic_distance) +
           acc_disk(pos, cylindrical_distance) +
           acc_halo(pos, galactic_distance);
}


Vec3 GalacticPotential_IWTS_Ia::acc_bulge(const Vec3 &pos, double galactic_distance)
{
    double den = galactic_distance * galactic_distance + b_b * b_b;
    return pos * (-gauss2 * M_b / sqrt(den * den * den));
}

Vec3 GalacticPotential_IWTS_Ia::acc_disk(const Vec3 &pos, double cylindrical_distance)
{
    double x = a_d + sqrt(b_d * b_d + pos.z * pos.z);
    double y = x * x;
    double den = cylindrical_distance * cylindrical_distance + y;
    double f = -gauss2 * M_d / sqrt(den * den * den);

    return Vec3(pos.x * f, pos.y * f,
                pos.z * x * f / sqrt(b_d * b_d + pos.z * pos.z));
}


Vec3 GalacticPotential_IWTS_Ia::acc_halo(const Vec3 &pos, double galactic_distance)
{
    return pos * (-gauss2 * M_h /
                  (a_h * (galactic_distance + a_h) * galactic_distance));
}




GalacticPotential_IWTS_Ib::GalacticPotential_IWTS_Ib(double gauss2)

{
		this->gauss2 = gauss2;

		double mass = 2.325e7;
        M_b = 386 * mass;
        M_d = 3092 * mass;
        M_h = 452 * mass;
        b_b = 249;
        b_d = 305;
        a_d = 3670;
        a_h = 1520;

        sun_galactic_distance = 8300.0; // pc
		sun_pos_z = 17;
        sun_mean_orbital_speed = 239;  // km/s

		description = "IWTS Model Ib, parameters from Bajkova & Bobylev 2017";
		description_short = "IWTS_Ib";
}


GalacticPotential_IWTS_IIIa::GalacticPotential_IWTS_IIIa(double gauss2)
{
		this->gauss2 = gauss2;

		double mass = 2.325e7;
        M_b = 439 * mass;
        M_d = 3096 * mass;
        M_h = 142200 * mass;
        b_b = 236;
        b_d = 289;
        a_d = 3262;
        a_h = 45020;

        sun_galactic_distance = 8330.0; // pc
		sun_pos_z = 17;
        sun_mean_orbital_speed = 239.7;  // km/s

		description = "IWTS Model IIIa, parameters from Irrgang et.al 2013";
		description_short = "IWTS_IIIa";
}


Vec3 GalacticPotential_IWTS_IIIa::acc_halo(const Vec3 &pos, double galactic_distance)
{
    double x = -log(1 + galactic_distance / a_h) /
               (galactic_distance * galactic_distance * galactic_distance);

    x += 1. / (a_h * (1 + galactic_distance / a_h) *
               (galactic_distance * galactic_distance));

    x *= gauss2 * M_h;

    return pos * x;
}


void GalacticPotential_IWTS_Ia::print_parameters()
{
	printf("M_b = %22.15lf\n", M_b);
	printf("M_d = %22.15lf\n", M_d);
	printf("M_h = %22.15lf\n", M_h);

	printf("b_b = %22.15lf\n", b_b);

	printf("a_d = %22.15lf\n", a_d);

	printf("b_d = %22.15lf\n", b_d);

	printf("a_h = %22.15lf\n", a_h);

	printf("R_sun = %22.15lf\n", sun_galactic_distance);
	printf("V_sun = %22.15lf\n", sun_mean_orbital_speed);
}


GalacticPotential_IWTS_IIIb::GalacticPotential_IWTS_IIIb(double gauss2)
{
		this->gauss2 = gauss2;

		double mass = 2.325e7;
        M_b = 443 * mass;
        M_d = 2798 * mass;
        M_h = 12474 * mass;
        b_b = 267;
        b_d = 308;
        a_d = 4400;
        a_h = 7700;

        sun_galactic_distance = 8300.0; // pc
		sun_pos_z = 17;
        sun_mean_orbital_speed = 243.9;  // km/s

		description = "IWTS Model IIIb, parameters from Bajkova & Bobylev 2017";
		description_short = "IWTS_IIIb";
}


GalacticPotential_McMillan::GalacticPotential_McMillan()
{
	sun_galactic_distance = 8210;
	sun_pos_z = 17; // 14?
	sun_mean_orbital_speed = 233.1;

#ifndef MCM_POT_PATH
	#define MCM_POT_PATH "pot"
#endif

    ifstream file;
	file.open(MCM_POT_PATH"/PJM16_best.Tpot");
// 	file.open("pot/PJM17_best.Tpot");
	Phi = new McMillan::GalaxyPotential(file);
	file.close();

	description = "McMillan (2017), PJM16_best.Tpot";
	description_short = "McMillan_PJM16_best";
}


Vec3 GalacticPotential_McMillan::get_acceleration(const Vec3 &pos)
{
    // input pos in parsecs

    Vec3 acceleration;
    double dPdR, dPdz, P;

    //     double galactic_distance = pos.length();
    double galactic_distance = sqrt(pos.x * pos.x + pos.y * pos.y);

    P = (*Phi)(galactic_distance / 1000., pos.z / 1000., dPdR, dPdz);

	// cos(phi) = pos.x/R, sin(phi) = pos.y/R
    acceleration.x = -dPdR * pos.x/galactic_distance * 1000.;
    acceleration.y = -dPdR * pos.y/galactic_distance * 1000.;
    acceleration.z = -dPdz * 1000.;

    return acceleration;
}


} // namespace StarLib
