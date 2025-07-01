#include "SockEPFactory.h"

#include "simpleLogger/SimpleLogger.h"

namespace sockep
{
std::unique_ptr<IServerSockEP>
SockEPFactory::createUnixDgramServerSockEP(std::string bindPath,
                                           std::function<void(int, const char *, size_t)> callback)
{
	return nullptr;
}

std::unique_ptr<IClientSockEP> SockEPFactory::createUnixDgramClientSockEP(std::string bindPath, std::string serverPath)
{
	return nullptr;
}

std::unique_ptr<IServerSockEP>
SockEPFactory::createUnixStreamServerSockEP(std::string bindPath,
                                            std::function<void(int, const char *, size_t)> callback)
{
	return nullptr;
}

std::unique_ptr<IClientSockEP> SockEPFactory::createUnixStreamClientSockEP(std::string bindPath, std::string serverPath)
{
	return nullptr;
}

std::unique_ptr<IServerSockEP>
SockEPFactory::createTcpServerSockEP(std::string ipaddr, int port,
                                     std::function<void(int, const char *, size_t)> callback)
{
	return nullptr;
}

std::unique_ptr<IClientSockEP> SockEPFactory::createTcpClientSockEP(std::string serverIpaddr, int port) {}

std::unique_ptr<IServerSockEP>
SockEPFactory::createUdpServerSockEP(std::string ipaddr, int port,
                                     std::function<void(int, const char *, size_t)> callback,
                                     const std::string &multicastAddr = "", const std::string &interfaceAddr = "")
{
	return nullptr;
}

std::unique_ptr<IClientSockEP> SockEPFactory::createUdpClientSockEP(std::string serverIpaddr, int port, int ttl = -1)
{
	return nullptr;
}
} // namespace sockep