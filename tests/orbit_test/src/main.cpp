#include <iostream>
#include <stdio.h>
#include <gtest/gtest.h>

#include "Constants.h"
#include "Orbit.h"

using namespace StarLib;
using namespace std;

#define PRECISION (1.0e-12)

TEST(VectorsToElements, Elipse)
{
	double jd = 2459488.500000000;  // julian day of ephemeris;

	Vec3 pos( 4.322971384118571E+01,
			  7.008266498521618E+01,
			 -1.735416319498954E+01);

	Vec3 vel(-2.443025889962331E-03,
			  6.649188624770855E-04,
			  1.879701995545643E-04);
	double mu = 2.9591220828411951E-04;// GAUSS2;
// 	printf("%.16lf\n", mu);

	Orbit orbit(pos, vel, mu, jd);
	OrbitalElements &elems = orbit.elements;

	double hor_q = 7.635856848373376E+01;
	double hor_a = 5.041271107391012E+02;
	double hor_e = 8.485331043359597E-01;
	double hor_i = 1.193122448126597E+01;
	double hor_omega = 3.110755450227138E+02;
	double hor_Omega = 1.442047264654611E+02;
	double hor_M = 3.582843723753385E+02;

	double hor_Tp = 2479191.349350453820;  // julian day of periapsis

// 	printf("%.16lf\n", elems.tp);
// 	printf("tp = %.16lf\n", elems.tp);
// 	printf("M = %.16lf\n",orbit.M(elems.tp)*180./M_PI);

	EXPECT_LE(fabs(elems.q - hor_q), PRECISION);
	EXPECT_LE(fabs(orbit.a() - hor_a), PRECISION);
	EXPECT_LE(fabs(elems.e - hor_e), PRECISION);
	EXPECT_LE(fabs(elems.i * 180./M_PI - hor_i), PRECISION);
	EXPECT_LE(fabs(elems.omega * 180./M_PI - hor_omega), PRECISION);
	EXPECT_LE(fabs(elems.Omega * 180./M_PI - hor_Omega), PRECISION);
	EXPECT_LE(fabs(orbit.M(jd) * 180./M_PI - hor_M), PRECISION);
	EXPECT_LE(fabs(elems.tp - hor_Tp), PRECISION);

};

TEST(VectorsToElements, Hyperbola) {

	double jd = 2459488.500000000;  // julian day of ephemeris;

	Vec3 pos(-3.672238611812362E+00,
			 -3.352030696657659E+00,
			 1.987293247608006E+00);

	Vec3 vel(-4.609943721268436E-03,
			 -8.100875039552124E-03,
			 4.872199390105144E-03);
	double mu = 2.9591220828411951E-04;// GAUSS2;
// 	printf("%.16lf\n", mu);

	Orbit orbit(pos, vel, mu, jd);
	OrbitalElements &elems = orbit.elements;

	double hor_q = 4.741677624240043E-01;
	double hor_a = -3.445695592410417E+03;
	double hor_e = 1.000137611622881E+00;
	double hor_i = 3.142206870982597E+01;
	double hor_omega = 2.600276480319612E+02;
	double hor_Omega = 1.815283942773269E+02;
	double hor_M = 1.858874175439345E-03;

	double hor_Tp = 2459107.029216685332;
// 	printf("tp = %.16lf\n", elems.tp);
// 	printf("M = %.16lf\n",orbit.M(jd)*180./M_PI);

	EXPECT_LE(fabs(elems.q - hor_q), PRECISION);
	EXPECT_LE(fabs(orbit.a() - hor_a), PRECISION*1e3);
	EXPECT_LE(fabs(elems.e - hor_e), PRECISION);
	EXPECT_LE(fabs(elems.i * 180./M_PI - hor_i), PRECISION);
	EXPECT_LE(fabs(elems.omega * 180./M_PI - hor_omega), PRECISION);
	EXPECT_LE(fabs(elems.Omega * 180./M_PI - hor_Omega), PRECISION);
	EXPECT_LE(fabs(orbit.M(jd) * 180./M_PI - hor_M), PRECISION);
	EXPECT_LE(fabs(elems.tp - hor_Tp), PRECISION*1e3);

};


TEST(ElementsToVectors, Elipse)
{

    double jd = 2459488.500000000;      // julian day of ephemeris;
    double mu = 2.9591220828411951E-04; // GAUSS2;

    Vec3 pos(4.322971384118571E+01,
			  7.008266498521618E+01,
             -1.735416319498954E+01);

    Vec3 vel(-2.443025889962331E-03,
			  6.649188624770855E-04,
              1.879701995545643E-04);


    const double to_rad = M_PI / 180.;
    Orbit orbit(OrbitalElements(7.635856848373376E+01,
								8.485331043359597E-01,
                                1.193122448126597E+01 * to_rad,
                                3.110755450227138E+02 * to_rad,
                                1.442047264654611E+02 * to_rad,
                                2479191.349350453820),
                mu, jd);
// 	orbit.print(jd);

    StateVector sv = orbit.state_vector(jd);
// 	sv.position.print();

    EXPECT_LE(sv.position.length() - pos.length(), PRECISION);
    EXPECT_LE(sv.velocity.length() - vel.length(), PRECISION);

    EXPECT_LE((sv.position - pos).length(), PRECISION);
    EXPECT_LE((sv.velocity - vel).length(), PRECISION);
}


TEST(ElementsToVectors, Hyperbola)
{
    double jd = 2459488.500000000;      // julian day of ephemeris;
    double mu = 2.9591220828411951E-04; // GAUSS2;


	Vec3 pos(-3.672238611812362E+00,
			 -3.352030696657659E+00,
			 1.987293247608006E+00);

	Vec3 vel(-4.609943721268436E-03,
			 -8.100875039552124E-03,
			 4.872199390105144E-03);

    const double to_rad = M_PI / 180.;
    Orbit orbit(OrbitalElements(4.741677624240043E-01,
								1.000137611622881E+00,
                                3.142206870982597E+01 * to_rad,
                                2.600276480319612E+02 * to_rad,
                                1.815283942773269E+02 * to_rad,
                                2459107.029216685332),
                mu, jd);


    StateVector sv = orbit.state_vector(jd);

    EXPECT_LE(sv.position.length() - pos.length(), PRECISION*10);
    EXPECT_LE(sv.velocity.length() - vel.length(), PRECISION*10);

    EXPECT_LE((sv.position - pos).length(), PRECISION*10);
    EXPECT_LE((sv.velocity - vel).length(), PRECISION*10);

}

TEST(ElementsToVectors, Circular)
{
    double mu = 2.9591220828411951E-04; // GAUSS2;
	Orbit orbit(OrbitalElements(1., 0.0, 0.0, 0., 0.0, 0.0), mu, 0.0);
	StateVector sv = orbit.state_vector(0.0);

	Vec3 pos(1., 0, 0);
	Vec3 vel(0.0, 0.0172020989500000, 0.0);

    EXPECT_LE(sv.position.length() - pos.length(), PRECISION);
    EXPECT_LE(sv.velocity.length() - vel.length(), PRECISION);

    EXPECT_LE((sv.position - pos).length(), PRECISION);
    EXPECT_LE((sv.velocity - vel).length(), PRECISION);


	Orbit orbit2(OrbitalElements(1., 0.0, 0.0, 120. * M_PI/180., 0.0, 0.0), mu, 0.0);
	sv = orbit2.state_vector(0.0);

	pos = Vec3(-0.4999999999999998, 0.8660254037844387, 0.0);
	vel = Vec3(-0.0148974546891136, -0.0086010494750000, 0.0);

    EXPECT_LE(sv.position.length() - pos.length(), PRECISION);
    EXPECT_LE(sv.velocity.length() - vel.length(), PRECISION);

    EXPECT_LE((sv.position - pos).length(), PRECISION);
    EXPECT_LE((sv.velocity - vel).length(), PRECISION);

}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
