#include "Coordinates.h"

namespace StarLib
{


static double eps = (23. + 26. / 60 + 21.406 / 3600) * UNITS::DEG;


Vec3 galactic_to_equatorial(Vec3 vec)
{
    Vec3 result =
        rotate_z(vec, M_PI - GalacticCoordinateSystem::position_angle);
    result = rotate_y(
        result, M_PI_2 - GalacticCoordinateSystem::NorthGalacticPole::dec);
    result = rotate_z(result, GalacticCoordinateSystem::NorthGalacticPole::ra);
    //
    return result;
}

Vec3 equatorial_to_galactic(Vec3 vec)
{

    Vec3 result =
        rotate_z(vec, -(GalacticCoordinateSystem::NorthGalacticPole::ra));
    result = rotate_y(
        result, -(M_PI_2 - GalacticCoordinateSystem::NorthGalacticPole::dec));
    result =
        rotate_z(result, -(M_PI - GalacticCoordinateSystem::position_angle));

    return result;
}


SphericalCoords galactic_to_equatorial(SphericalCoords sph)
{
	Vec3 vec = spherical_to_cartesian(sph);
	vec = galactic_to_equatorial(vec);
	return cartesian_to_spherical(vec);

}

SphericalCoords equatorial_to_galactic(SphericalCoords sph)
{
	Vec3 vec = spherical_to_cartesian(sph);
	vec = equatorial_to_galactic(vec);
	return cartesian_to_spherical(vec);
}

Vec3 equatorial_to_ecliptic(Vec3 vec)
{
	return rotate_x(vec, -eps);
}


Vec3 ecliptic_to_equatiorial(Vec3 vec)
{
	return rotate_x(vec, eps);
}


SphericalCoords equatorial_to_ecliptic(SphericalCoords sph)
{
	Vec3 vec = spherical_to_cartesian(sph);
	vec = equatorial_to_ecliptic(vec);
	return cartesian_to_spherical(vec);
}


SphericalCoords ecliptic_to_equatiorial(SphericalCoords sph)
{
	Vec3 vec = spherical_to_cartesian(sph);
	vec = ecliptic_to_equatiorial(vec);
	return cartesian_to_spherical(vec);
}


SphericalCoords cartesian_to_spherical(Vec3 vec)
{
	double len = vec.length();
	return SphericalCoords(len, atan2(vec.y, vec.x), asin(vec.z/len));
}

Vec3 spherical_to_cartesian(SphericalCoords sph)
{
	double r_cos_d = sph.r * cos(sph.delta);
	return Vec3(r_cos_d * cos(sph.alpha),
				r_cos_d * sin(sph.alpha),
				sph.r * sin(sph.delta));
}


} // namespace StarLib
