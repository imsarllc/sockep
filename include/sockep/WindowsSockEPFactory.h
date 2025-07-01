#pragma once

#include "sockep/client/IClientSockEP.h"
#include "sockep/server/IServerSockEP.h"

#include <functional>
#include <memory>

namespace sockep
{
class SockEPFactory
{
private:
	SockEPFactory() {};
	~SockEPFactory() {};

public:
	static std::unique_ptr<IServerSockEP>
	createWindowsDgramServerSockEP(std::string bindPath, std::function<void(int, const char *, size_t)> callback);
	static std::unique_ptr<IClientSockEP> createWindowsDgramClientSockIP(std::string bindPath, std::string serverPath);
	static std::unique_ptr<IServerSockEP>
	createWindowsStreamServerSockEP(std::string bindPath, std::function<void(int, const char *, size_t)> callback);
	static std::unique_ptr<IClientSockEP> createWindowsStreamClientSockEP(std::string bindPath, std::string serverPath);

	static std::unique_ptr<IClientSockEP> createUnixDgramClientSockEP(std::string bindPath, std::string serverPath);
	static std::unique_ptr<IServerSockEP>
	createUdpServerSockEP(std::string ipaddr, int port, std::function<void(int, const char *, size_t)> callback);
};
} // namespace sockep
