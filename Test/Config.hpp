#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <memory>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

enum Type
{
    GET,
    SET
};

// Structure of config.ini
class Config
{
   private:
    Type m_type;
    std::vector<std::string> m_variable;
    unsigned int m_refresh_rate;
    std::string m_script;
    unsigned int m_time_before_refresh;

   public:
    Config(Type type, std::vector<std::string> variable, unsigned int refresh_rate, std::string script, unsigned int time_before_refresh);
    Config(boost::property_tree::ptree& pt);
    ~Config();
    void treatement();
    friend unsigned int min(const std::vector<Config>& configs);
    friend std::vector<Config>& operator-=(std::vector<Config>& configs, unsigned int time);
};

#endif  // CONFIG_HPP