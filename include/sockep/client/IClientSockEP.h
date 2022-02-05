#pragma once

#include <unistd.h>
#include <string>
#include <sys/socket.h>

namespace sockep
{
    
class IClientSockEP
{
public:
    ~IClientSockEP() {};

    virtual bool isValid() = 0;
    //virtual void sendMessage(char* msg, size_t msgLen) = 0;
    virtual void sendMessage(const char* msg, size_t msgLen) = 0;
    virtual void sendMessage(const std::string &msg) = 0;
    virtual std::string getMessage() = 0;
    virtual void getMessage(char* msg, const int msgMaxLen) = 0;
    virtual std::string to_str() const = 0;
    // probably need to start a thread here to get messages. 

    // virtual bool operator== (IClientSockEP const *other) = 0; 
    // virtual void clearSaddr() = 0;
    // virtual struct sockaddr * getSaddr() = 0;
    // virtual socklen_t getSaddrLen() = 0;

};

}