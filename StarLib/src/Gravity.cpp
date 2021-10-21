#include "Gravity.h"


namespace Gravity
{

double gravitational_constant(double distance_unit, double time_unit,
                              double mass_unit)
{
    // k2 = 2.9591220828559115E-04 is the gauss  grav. const. [au^3 d^-2 M_s^-1]
    return 2.9591220828559115E-04
		* time_unit * time_unit
		* mass_unit
		/ (distance_unit * distance_unit * distance_unit);
}
} // namespace Gravity
