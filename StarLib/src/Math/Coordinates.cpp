#include "Coordinates.h"

namespace StarLib
{

Vec3 galactic_to_equatorial(Vec3 vec)
{
	double ngp_ra = 192.85 * UNITS::DEG;
	double ngp_dec = 27.13 * UNITS::DEG;
	double ncp_long = 122.93 * UNITS::DEG;

	// vec to longitude, latitude
	double gal_long = atan2(vec.y, vec.x);
	double ga_lat = asin(vec.z / vec.length());

	double dec = asin( sin(ngp_dec)  );


	return Vec3();
}

}
