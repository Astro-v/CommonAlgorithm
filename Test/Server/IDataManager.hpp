#ifndef I_DATA_MANAGER_HPP
#define I_DATA_MANAGER_HPP

#include <string>

class IDataManager
{
   public:
    virtual ~IDataManager() = default;
    virtual void get_data(const std::string& field_name, std::string& data_get) = 0;
    virtual void set_data(const std::string& field_name, const std::string& data_set) = 0;
};

#endif  // I_DATA_MANAGER_HPP