#include "SockEPFactory.h"

#include "server/IServerSockEP.h"
#include "client/IClientSockEP.h"
// #include "SockEP.h"

#include "server/UnixDgramServerSockEP.h"
#include "client/UnixDgramClientSockEP.h"

using namespace sockep;

// IServerSockEP *SockEPFactory::createServerSockEP()
// {
//     IServerSockEP *val;
//     return val;
// }
IServerSockEP *SockEPFactory::createUnixDgramServerSockEP(std::string bindPath, void (*callback)(int, std::string))
{
    return new UnixDgramServerSockEP(bindPath, callback);
}

IClientSockEP *SockEPFactory::createUnixDgramClientSockEP(std::string bindPath, std::string serverPath)
{
    return new UnixDgramClientSockEP(bindPath, serverPath);
}

// IServerSockEP *SockEPFactory::createUnixStreamServerSockEP(std::string bindPath)
// {
//     return new UnixStreamServerSockEP(bindPath);
// }

// IClientSockEP *SockEPFactory::createUnixStreamClientSockEP(std::string serverPath)
// {
//     return new UnixStreamClientSockEP(serverPath);
// }

// ISockEP *SockEPFactory::createUnixStreamSockEP()
// {
//     return new UnixStreamSockEP();
// }
// ISockEP *SockEPFactory::createTCPSockEP()
// {
//     ISockEP *val;
//     return val;
// }
// ISockEP *SockEPFactory::createUDPSockEP()
// {
//     ISockEP *val;
//     return val;
// }

