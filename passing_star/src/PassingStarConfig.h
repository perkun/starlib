#ifndef _PASSINGSTARCONFIG_
#define _PASSINGSTARCONFIG_

#include <iostream>
#include <yaml-cpp/yaml.h>
#include <string>
#include <vector>
#include "Units.h"
#include "StateVector.h"
#include "starlibmath.h"

class PassingStarConfig
{
public:
    PassingStarConfig(std::string filename)
    {
        read_config_file(filename);

		min_position = StarLib::Vec3(min_distance, 0., 0.);

        direction =
            StarLib::rotate_x(StarLib::Vec3(0., 1., 0.), -approach_angle);

        init_state.position = min_position + (-init_star_distance * direction);
        init_state.velocity = speed * direction;
        passage_duration = (init_star_distance + final_star_distance) / speed;
    }

    void read_config_file(std::string filename)
    {
        YAML::Node cfg_file = YAML::LoadFile(filename);

        approach_angle =
            cfg_file["approach_angle"].as<double>() * StarLib::UNITS::DEG;

        init_star_distance = cfg_file["init_star_distance"].as<double>();
        final_star_distance = cfg_file["final_star_distance"].as<double>();
		speed = cfg_file["speed"].as<double>();
		min_distance = cfg_file["min_distance"].as<double>();
    }

    double approach_angle, init_star_distance, final_star_distance, speed;
	double min_distance;
    StarLib::Vec3 direction;
	StarLib::Vec3 min_position;
    StarLib::StateVector init_state;
    double passage_duration;


private:
};

#endif
