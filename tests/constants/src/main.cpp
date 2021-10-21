#include <iostream>
#include <stdio.h>
#include "Gravity.h"
#include "Units.h"


using namespace std;
using namespace StarLib;

int main(int argc, char *argv[])
{

    double G =
        Gravity::gravitational_constant(UNITS::AU, UNITS::DAY, UNITS::MASS_SUN);
	printf("Grav. const. in AU^3, d^-2, M_sun^-1: %.16e\n", G);

	G = Gravity::gravitational_constant(UNITS::PARSEC, UNITS::MYEAR, UNITS::MASS_SUN);
	printf("Grav. const. in pc^3, Myrs^-2, M_sun^-1: %.16e\n", G);

    return 0;
}
