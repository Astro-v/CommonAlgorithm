#include "Config.hpp"

Config::Config(Type type, std::vector<std::string> variable, unsigned int refresh_rate, std::string script, unsigned int time_before_refresh)
    : m_type(type), m_variable(variable), m_refresh_rate(refresh_rate), m_script(script), m_time_before_refresh(time_before_refresh)
{
}

Config::Config(boost::property_tree::ptree& pt)
{
    if (pt.get<std::string>("type") == "get")
    {
        m_type = GET;
    }
    else if (pt.get<std::string>("type") == "set")
    {
        m_type = SET;
    }
    else
    {
        throw std::runtime_error("Error: type must be GET or SET");
    }

    // read all the variables separated by a comma
    std::string variables = pt.get<std::string>("variable");
    std::string variable;
    for (auto& c : variables)
    {
        if (c != ',')
        {
            variable += c;
        }
        else
        {
            m_variable.push_back(variable);
            variable.clear();
        }
    }
    m_variable.push_back(variable);
    m_refresh_rate = pt.get<unsigned int>("refresh_rate");
    m_script = pt.get<std::string>("script");
    m_time_before_refresh = m_refresh_rate;
}

Config::~Config()
{
}

void Config::treatement()
{
    if (m_time_before_refresh == 0)
    {
        if (m_type == GET)
        {
            // Execute the bash script
            std::string command = m_script;

            for (auto& variable : m_variable)
            {
                command += " " /* + GET VALUE */;
            }
            system(command.c_str());
        }
        else if (m_type == SET)
        {
            std::array<char, 128> buffer;
            std::vector<std::string> result;
            std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(m_script.c_str(), "r"), pclose);
            if (!pipe)
            {
                throw std::runtime_error("popen() failed!");
            }

            // Get the result of the bash script exepted the last line
            while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
            {
                result.push_back(buffer.data());
                result.back().erase(std::remove(result.back().begin(), result.back().end(), '\n'), result.back().end());
            }

            for (auto& line : result)
            {
                if (line.empty())
                    // On ne fait rien
                    continue;
                // std::cout << line << std::endl;
            }

            // Set each variable with the result
            for (auto& variable : m_variable)
            {
                /* SET VALUE */
            }
        }
        m_time_before_refresh = m_refresh_rate;
    }
}

unsigned int min(const std::vector<Config>& configs)
{
    unsigned int min = configs[0].m_time_before_refresh;
    for (auto& config : configs)
    {
        if (config.m_time_before_refresh < min)
            min = config.m_time_before_refresh;
    }
    return min;
}

std::vector<Config>& operator-=(std::vector<Config>& configs, unsigned int time)
{
    for (auto& config : configs)
    {
        if (config.m_time_before_refresh > time)
            config.m_time_before_refresh -= time;
        else
            config.m_time_before_refresh = 0;
    }
    return configs;
}