#ifndef _RANDOMPOPULATIONCONFIG_
#define _RANDOMPOPULATIONCONFIG_

#include <stdio.h>
#include <yaml-cpp/yaml.h>

class RandomPopulationConfig
{
public:
	RandomPopulationConfig(std::string filename)
	{
		YAML::Node cfg_file = YAML::LoadFile(filename);

		q_min = cfg_file["q_min"].as<double>();
		q_max = cfg_file["q_max"].as<double>();

		e_min = cfg_file["e_min"].as<double>();
		e_max = cfg_file["e_max"].as<double>();

		i_min = cfg_file["i_min"].as<double>();
		i_max = cfg_file["i_max"].as<double>();

		omega_min = cfg_file["omega_min"].as<double>();
		omega_max = cfg_file["omega_max"].as<double>();

		Omega_min = cfg_file["Omega_min"].as<double>();
		Omega_max = cfg_file["Omega_max"].as<double>();

		seed = cfg_file["seed"].as<int>();
		num_objects = cfg_file["num_objects"].as<int>();
		tp_range = cfg_file["tp_range"].as<double>();

		mean_mass = cfg_file["mean_mass"].as<double>();
		mass_range = cfg_file["mass_range"].as<double>();

		jd = cfg_file["jd"].as<double>();
	}

	double q_min, q_max,
		   e_min, e_max,
		   i_min, i_max,
		   omega_min, omega_max,
		   Omega_min, Omega_max,
		   tp_range,
		   mean_mass, mass_range,
		   jd;
	int num_objects;
	int seed;

private:

};

#endif
