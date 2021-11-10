#ifndef UNITS_H_
#define UNITS_H_

#include <math.h>

namespace StarLib
{

namespace UNITS
{
	/*
	 * Basic units are:
	 * 	radian,
	 * 	day,
	 * 	au,
	 * 	solar mass
	 *
	 * 	...
	 *
	 * 	Everything else is expresed in basic units.
	 * 	If you want to use non-basic unit for something, multiply the value by
	 * 	the unit.
	 * 	E.g.: let's define an angle in basic units (radians) with the value of
	 * 	M_PI/4. If you want to use degrees as units, the same angle would be
	 * 	(45 * UNITS::DEG).
	 */


					    // BASIC UNITS
	static const double RAD = 1.0,
						DAY = 1.0,
						AU = 1.0,
						MASS_SUN = 1.0,

						// DERIVED UNITS
						// angles
				 		DEG = M_PI / 180.,  // 1 deg in radians
						ARCMIN = DEG / 60.,
						ARCSEC = ARCMIN / 60.,

						// time
						YEAR =  365.24219,  		// solar year
						MYEAR = YEAR * 1.0e6,
						GYEAR = YEAR * 1.0e9,
						CALENDAR_YEAR = 365.2425,   // calendar year
						JULIAN_YEAR = 365.25,
						SEC = 1. / (DAY * 24. * 3600.),


						// distance
						PARSEC = 206264.8062470963632222,
						METER = 1./149597870700.,
						KM = 1./149597870.700,

						// velocity
						PARSEC_MYRS = PARSEC / (1.0e6 * YEAR),
						KM_S = KM / SEC;




} // namespace UNITS

} // namespace StarLib


#endif
