#ifndef CONSTANTS_H_
#define CONSTANTS_H_
/* astronomical and physical constants definitions
 * should be in SI
 * Values from https://ssd.jpl.nasa.gov/?constants
 * Values from https://ssd.jpl.nasa.gov/doc/Park.2021.AJ.DE440.pdf
 * */

namespace StarLib
{

namespace CONSTANTS
{

static const double AU = 149597870700;
static const double GRAV_CONST = 6.67430e-11;
static const double ECL_OBLIQ_ARCSEC = 84381.412;
static const double LIGHT_TIME_AU = 499.004783836;
static const double GAUSS = 0.01720209895;           // [rad/day]
static const double GAUSS2 = 2.9591220828559115E-04; // GAUSS squared


static const double SUN_GM_KM3S2 = 132712440041.279419; // km^3/s^2

static const double SUN_MERCURY_MASS_RATIO = SUN_GM_KM3S2 / 22031.868551;
static const double SUN_VENUS_MASS_RATIO = SUN_GM_KM3S2 / 324858.592000;

static const double SUN_EARTH_MASS_RATIO = SUN_GM_KM3S2 / 398600.435507;
static const double SUN_MOON_MASS_RATIO = SUN_GM_KM3S2 / 4902.800118;
static const double SUN_EARTH_MOON_MASS_RATIO =
    SUN_GM_KM3S2 / (398600.435507 + 4902.800118);

static const double SUN_MARS_MASS_RATIO = SUN_GM_KM3S2 / 42828.375816;
static const double SUN_JUPITER_MASS_RATIO = SUN_GM_KM3S2 / 126712764.1000;
static const double SUN_SATURN_MASS_RATIO = SUN_GM_KM3S2 / 37940584.841800;
static const double SUN_URANUS_MASS_RATIO = SUN_GM_KM3S2 / 5794556.400;
static const double SUN_NEPTUNE_MASS_RATIO = SUN_GM_KM3S2 / 6836527.100580;
static const double SUN_PLUTO_MASS_RATIO = SUN_GM_KM3S2 / 975.500000;
static const double SUN_CERES_MASS_RATIO = SUN_GM_KM3S2 / 62.62890;
static const double SUN_VESTA_MASS_RATIO = SUN_GM_KM3S2 / 17.288245;

// physics
static const double SPEED_OF_LIGHT = 299792458;  // m/s

} // namespace CONSTANTS
} // namespace StarLib


#endif
