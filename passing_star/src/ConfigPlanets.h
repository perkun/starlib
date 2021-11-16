#ifndef _CONFIG_PLANETS_
#define _CONFIG_PLANETS_

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

class PlanetsConfig
{
public:
    PlanetsConfig(std::string filename) { read_config_file(filename); }

    void read_config_file(std::string filename)
    {
        YAML::Node cfg_file = YAML::LoadFile(filename);
        std::string folder = cfg_file["folder"].as<std::string>();

        for (auto planet : cfg_file["planets"])
        {
            planets.push_back({planet["name"].as<std::string>(),
                               folder + planet["file"].as<std::string>()});
        }
    }

    struct Planet
    {
        std::string name, horizon_filename;
    };

    std::vector<Planet> planets;
};


#endif
