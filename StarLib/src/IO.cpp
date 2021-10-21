#include "IO.h"
#include "Constants.h"


namespace StarLib
{
namespace IO
{

std::deque<Orbit> parse_horizons_elements(std::string filename)
{
	std::deque<Orbit> orbits;

	FILE *file = fopen(filename.c_str(), "r");

	if (file == NULL)
	{
		std::cout << "Error reading file: " << filename << std::endl;
		return orbits;
	}

	// read untill $$SOE
	char line[1000];
	bool data_started = false;
	double mu = 0;

	while (fgets(line, 999, file))
	{
		if (strncmp(line, "$$SOE", 5) == 0)
		{
			data_started = true;
			continue;
		}

		if (strncmp(line, "$$EOE", 5) == 0)
			break;


		// find mu:
		// Keplerian GM    : 2.9591220828411951E-04 au^3/d^2
		if (strncmp(line, "Keplerian GM", 12) == 0)
			sscanf(line, "Keplerian GM    : %lf", &mu);


		if (!data_started)
			continue;

        double jd;
		OrbitalElements elems;

		//read jd
        sscanf(line, "%lf %*s", &jd);

        fgets(line, 999, file);
        sscanf(line, " EC= %lf QR= %lf IN= %lf", &elems.e, &elems.q, &elems.i);

        fgets(line, 999, file);
        sscanf(line, " OM= %lf W = %lf Tp= %lf", &elems.Omega, &elems.omega,
												 &elems.tp);

        fgets(line, 999, file); // N = ...
        fgets(line, 999, file); // A = ...

		// degrees -> radians
		elems.i = elems.i * UNITS::DEG;
		elems.Omega = elems.Omega * UNITS::DEG;
		elems.omega = elems.omega * UNITS::DEG;

		orbits.emplace_back(elems, mu, jd);
	}



	fclose(file);
	return orbits;
}


std::deque<StateVector> parse_horizons_vectors(std::string filename)
{
	std::deque<StateVector> states;

	FILE *file = fopen(filename.c_str(), "r");

	if (file == NULL)
	{
		std::cout << "Error reading file: " << filename << std::endl;
		return states;
	}

	// read untill $$SOE
	char line[1000];
	bool data_started = false;
	double mu = 0;

	while (fgets(line, 999, file))
	{
		if (strncmp(line, "$$SOE", 5) == 0)
		{
			data_started = true;
			continue;
		}

		if (strncmp(line, "$$EOE", 5) == 0)
			break;


		// find mu:
		// Keplerian GM    : 2.9591220828411951E-04 au^3/d^2
		if (strncmp(line, "Keplerian GM", 12) == 0)
			sscanf(line, "Keplerian GM    : %lf", &mu);


		if (!data_started)
			continue;

        double jd;
		Vec3 pos, vel;
		//read jd
        sscanf(line, "%lf %*s", &jd);

        fgets(line, 999, file);
        sscanf(line, " X =%lf Y =%lf Z =%lf", &pos.x, &pos.y, &pos.z);

        fgets(line, 999, file);
        sscanf(line, " VX=%lf VY=%lf VZ=%lf", &vel.x, &vel.y, &vel.z);

        fgets(line, 999, file); // LT= ...

		states.emplace_back(pos, vel, jd);

// 2459488.500000000 = A.D. 2021-Oct-01 00:00:00.0000 TDB
//  X = 4.322971384118571E+01 Y = 7.008266498521618E+01 Z =-1.735416319498954E+01
//  VX=-2.443025889962331E-03 VY= 6.649188624770855E-04 VZ= 1.879701995545643E-04
//  LT= 4.860212802107484E-01 RG= 8.415197603395406E+01 RR=-7.400193400340951E-04
	}

	return states;
}


} // namespace IO
} // namespace StarLib




