

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <string>
#include <vector>


enum Type
{
    GET,
    SET
};

// Structure of config.ini
struct Config
{
    Type type;
    std::string variable;
    unsigned int refresh_rate;
    std::string script;
    unsigned int time_before_refresh;
};  

// define min function for the std::vector<Config> returning the minimal value of time_before_refresh
unsigned int min(std::vector<Config>& configs)
{
    unsigned int min = configs[0].time_before_refresh;
    for (auto& config : configs)
    {
        if (config.time_before_refresh < min)
            min = config.time_before_refresh;
    }
    return min;
}

// operator -= for std::vector<Config>
std::vector<Config>& operator-=(std::vector<Config>& configs, unsigned int time)
{
    for (auto& config : configs)
    {
        if (config.time_before_refresh > time)
            config.time_before_refresh -= time;
        else
            config.time_before_refresh = 0;
    }
    return configs;
}

int main()
{
    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini("config.ini", pt);
    
    std::vector<Config> configs;
    // fullfill the configs vector
    for (auto& section : pt)
    {
        Config config;
        if (section.second.get<std::string>("type") == "GET")
        {
            config.type = GET;
        }
        else if (section.second.get<std::string>("type") == "SET")
        {
            config.type = SET;
        }
        else
        {
            std::cout << "Error: type must be GET or SET" << std::endl;
            return 1;
        }
        config.variable = section.second.get<std::string>("variable");
        config.refresh_rate = section.second.get<unsigned int>("refresh_rate");
        config.script = section.second.get<std::string>("script");
        config.time_before_refresh = config.refresh_rate;
        configs.push_back(config);
    }

    bool runing = true;
    while (runing)
    {
        for (auto& config : configs)
        {
            if (config.time_before_refresh == 0)
            {            
                if (config.type == GET)
                {
                    std::string value;
                    // Get the value
                    // value = ...

                    // Execute the bash script
                    std::string command = config.script + " " + config.variable + " " + value;
                    system(command.c_str());
                }
                else if (config.type == SET)
                {
                    // set the value of the variable
                    // if the value is different from the previous one, execute the script
                    // else do nothing
                }
            }
        }
        sleep(min(configs));
        configs -= min(configs);
    }
    

    return 0;
}