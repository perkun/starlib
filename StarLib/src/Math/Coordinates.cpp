#include "Coordinates.h"

namespace StarLib
{

static double  G1n (282.859481208*M_PI/180.0);
static double  G2n (62.871748806*M_PI/180.0);
static double  G3n (327.06808143*M_PI/180.0);


Vec3 galactic_to_equatorial(Vec3 vec)
{
	Vec3 result = rotate_z(vec, -G3n);
	result = rotate_x(result, -G2n);
	result = rotate_z(result, -G1n);

	return result;
}

Vec3 equatorial_to_galactic(Vec3 vec)
{
	Vec3 result = rotate_z(vec, G1n);
	result = rotate_x(result, G2n);
	result = rotate_z(result, G3n);

	return result;
}

}
