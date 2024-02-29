#ifndef I_UNIX_SERVER_HPP
#define I_UNIX_SERVER_HPP

#include <string>

class IUNIXServer
{
   public:
    virtual ~IUNIXServer() = default;
    virtual void start() = 0;
    virtual void stop() = 0;
};

#endif  // I_UNIX_SERVER_HPP