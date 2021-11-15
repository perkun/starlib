#include <iostream>
#include <stdio.h>
#include <gtest/gtest.h>
#include <utility>
#include "Coordinates.h"
#include "Units.h"

using namespace std;
using namespace StarLib;


TEST(ChangeRefFrame, GalacticEquatorialBackAndForth)
{
	Vec3 galactic(1., 2., 3.);

	Vec3 equatorial = galactic_to_equatorial(galactic);
	galactic = equatorial_to_galactic(equatorial);

	EXPECT_DOUBLE_EQ(galactic.x, 1.0);
	EXPECT_DOUBLE_EQ(galactic.y, 2.0);
	EXPECT_DOUBLE_EQ(galactic.z, 3.0);
}


TEST(ChangeRefFrame, EquatorialToGalactic)
{
	SphericalCoords equatorial_sph(0., 0.);
	SphericalCoords galactic_sph = equatorial_to_galactic(equatorial_sph);

	double PRECISION = 1e-5;
	EXPECT_LE(fabs(galactic_sph.longitude - 96.33723581 * UNITS::DEG), PRECISION);
	EXPECT_LE(fabs(galactic_sph.latitude + 60.18845577 * UNITS::DEG), PRECISION);

}


TEST(ChangeRefFrame, GalacticToEquatorial)
{
	SphericalCoords galactic_sph(0.0, 0.0);
	SphericalCoords equatorial_sph = galactic_to_equatorial(galactic_sph);


	double PRECISION = 1e-5;
	EXPECT_LE(fabs(equatorial_sph.longitude -  266.40506655 * UNITS::DEG), PRECISION);
	EXPECT_LE(fabs(equatorial_sph.latitude + 28.93616241 * UNITS::DEG), PRECISION);

}


TEST(ChangeRefFrame, EquatorialToEcliptic)
{
	SphericalCoords equatorial_sph(150 * UNITS::DEG, 20 * UNITS::DEG);
	SphericalCoords ecliptic_sph = equatorial_to_ecliptic(equatorial_sph);
//
	double PRECISION = 1e-5;
	EXPECT_LE(fabs(ecliptic_sph.longitude -  145.12793965 * UNITS::DEG), PRECISION);
	EXPECT_LE(fabs(ecliptic_sph.latitude - 7.29067749 * UNITS::DEG), PRECISION);

}


TEST(ChangeRefFrame, EclipticToEquatorial)
{
	SphericalCoords ecliptic_sph(150 * UNITS::DEG, 20 * UNITS::DEG);
	SphericalCoords equatorial_sph = ecliptic_to_equatiorial(ecliptic_sph);

	double PRECISION = 1e-5;
	EXPECT_LE(fabs(equatorial_sph.longitude -  160.07279506 * UNITS::DEG), PRECISION);
	EXPECT_LE(fabs(equatorial_sph.latitude - 30.04575820 * UNITS::DEG), PRECISION);

}


TEST(CartesianToSpherical, BackAndForth)
{
	Vec3 vec(1., 2., 3);
	SphericalCoords sph = cartesian_to_spherical(vec);
	vec = spherical_to_cartesian(sph);
	EXPECT_DOUBLE_EQ(vec.x, 1.0);
	EXPECT_DOUBLE_EQ(vec.y, 2.0);
	EXPECT_DOUBLE_EQ(vec.z, 3.0);
}



int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

