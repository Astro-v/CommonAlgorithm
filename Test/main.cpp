#include <iostream>
#include <vector>
#include "Config.hpp"

void initializeConfig(std::vector<Config>& configs);

int main()
{
    try
    {
        std::vector<Config> configs;
        initializeConfig(configs);

        bool runing = true;
        while (runing)
        {
            for (auto& config : configs)
            {
                config.treatement();
            }
            std::this_thread::sleep_for(std::chrono::seconds(min(configs)));
            std::cout << "here" << std::endl;
            configs -= min(configs);
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

void initializeConfig(std::vector<Config>& configs)
{
    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini("../config.ini", pt);

    // fullfill the configs vector
    for (auto& section : pt)
    {
        configs.emplace_back(section.second);
    }
}