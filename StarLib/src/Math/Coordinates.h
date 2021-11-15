#ifndef COORDINATES_H_
#define COORDINATES_H_

#include <iostream>
#include <stdio.h>
#include "starlibmath.h"
#include "Units.h"

namespace StarLib
{

Vec3 galactic_to_equatorial(Vec3 vec);
Vec3 equatorial_to_galactic(Vec3 vec);
Vec3 cartesian_to_spherical(Vec3 vec);

}

#endif /* COORDINATES_H_ */
