#include "WindowsSockEPFactory.h"

#include "simpleLogger/SimpleLogger.h"

namespace sockep
{
std::unique_ptr<IServerSockEP>
SockEPFactory::createWindowsDgramServerSockEP(std::string bindPath,
                                              std::function<void(int, const char *, size_t)> callback)
{
	return nullptr;
}

std::unique_ptr<IClientSockEP> SockEPFactory::createWindowsDgramClientSockIP(std::string bindPath,
                                                                             std::string serverPath)
{
	return nullptr;
}

std::unique_ptr<IServerSockEP>
SockEPFactory::createWindowsStreamServerSockEP(std::string bindPath,
                                               std::function<void(int, const char *, size_t)> callback)
{
	return nullptr;
}

std::unique_ptr<IClientSockEP> SockEPFactory::createWindowsStreamClientSockEP(std::string bindPath,
                                                                              std::string serverPath)
{
	return nullptr;
}

std::unique_ptr<IClientSockEP> SockEPFactory::createUnixDgramClientSockEP(std::string bindPath, std::string serverPath)
{
	return nullptr;
}

std::unique_ptr<IServerSockEP>
SockEPFactory::createUdpServerSockEP(std::string ipaddr, int port,
                                     std::function<void(int, const char *, size_t)> callback)
{
	return nullptr;
}
} // namespace sockep