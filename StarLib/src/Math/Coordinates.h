#ifndef COORDINATES_H_
#define COORDINATES_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include "starlibmath.h"
#include "Units.h"

namespace StarLib
{

struct EclipticCoordinateSystem
{
    static constexpr double earth_axis_tilt =
        (23. + 26. / 60 + 21.406 / 3600) * UNITS::DEG;
};


struct GalacticCoordinateSystem
{
    /* values from Liu et al. 2011 (equation 10)
     * https://ui.adsabs.harvard.edu/abs/2011A%26A...526A..16L/abstract
     * https://www.aanda.org/articles/aa/pdf/2011/02/aa14961-10.pdf
     */

    struct NorthGalacticPole
    {
        static constexpr double ra =
            (12 + 51. / 60. + 26.27549 / 3600) * UNITS::HOUR;
        static constexpr double dec =
            (27. + 7. / 60.0 + 41.7043 / 3600) * UNITS::DEG;
    };

    // position angle of the Galactic center from the equatorial pole
    static constexpr double position_angle = 122.93191857 * UNITS::DEG;
};

class SphericalCoords
{
	/* ra, lambda, longitude, is an angle between Ox and projected vector R onto
	 * Oxy plane.
	 * dec, beta, latitude is an angle between Oxy plane ane vector R
	 */

public:
	SphericalCoords() : r(0.), alpha(0.), delta(0.) {}
	SphericalCoords(double lon, double lat) : r(1.0), alpha(lon), delta(lat)
	{
		normalize();

	}
	SphericalCoords(double r, double lon, double lat) : r(r), alpha(lon), delta(lat)
	{
		normalize();
	}

	void normalize()
	{
		while (alpha >= 2*M_PI)
			alpha -= 2*M_PI;
		while (alpha < 0.)
			alpha += 2*M_PI;
	}

	union {
		double r, R, distance;
	};

	union {
		double ra, lambda, longitude, alpha;
	};

	union {
		double dec, beta, latitude, delta;
	};

	void print(int precision = 15)
	{
		std::string text = str(precision);
		std::cout << text << std::endl;
	}

protected:
	std::string str(int precision = 15) const
	{
        if (precision > 20)
            precision = 20;
        if (precision < 0)
            precision = 0;

        int total = 7 + precision;

        char fmt[200];
        sprintf(fmt, "%%%d.%dlf  %%%d.%dlf  %%%d.%dlf", total, precision,
                total, precision, total, precision);
		char text[200];
        sprintf(text, fmt, r, alpha, delta);
		return std::string(text);
	}
};


Vec3 galactic_to_equatorial(Vec3 vec);
Vec3 equatorial_to_galactic(Vec3 vec);
SphericalCoords galactic_to_equatorial(SphericalCoords sph);
SphericalCoords equatorial_to_galactic(SphericalCoords sph);

Vec3 equatorial_to_ecliptic(Vec3 vec);
Vec3 ecliptic_to_equatiorial(Vec3 vec);
SphericalCoords equatorial_to_ecliptic(SphericalCoords sph);
SphericalCoords ecliptic_to_equatiorial(SphericalCoords sph);



SphericalCoords cartesian_to_spherical(Vec3 vec);
Vec3 spherical_to_cartesian(SphericalCoords sph);

}

#endif /* COORDINATES_H_ */
