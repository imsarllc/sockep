#pragma once

// #include "sockep/ISockEP.h"
#include "sockep/TcpOptions.h"
#include "sockep/client/IClientSockEP.h"
#include "sockep/server/IServerSockEP.h"

#include <functional>
#include <memory>

namespace sockep
{
class SockEPFactory
{
private:
	SockEPFactory(){};
	~SockEPFactory(){};

public:
	// Unix Datagram
	static std::unique_ptr<IServerSockEP> createUnixDgramServerSockEP(const std::string &bindPath,
	                                                                  IServerSockEP::MessageCallback callback);
	static std::unique_ptr<IClientSockEP> createUnixDgramClientSockEP(const std::string &bindPath,
	                                                                  const std::string &serverPath);

	// Unix Stream
	static std::unique_ptr<IServerSockEP> createUnixStreamServerSockEP(const std::string &bindPath,
	                                                                   IServerSockEP::MessageCallback callback);
	static std::unique_ptr<IClientSockEP> createUnixStreamClientSockEP(const std::string &bindPath,
	                                                                   const std::string &serverPath);

	// TCP
	static std::unique_ptr<IServerSockEP> createTcpServerSockEP(const std::string &ipaddr, int port,
	                                                            IServerSockEP::MessageCallback callback);
	static std::unique_ptr<IServerSockEP> createTcpServerSockEP(const std::string &ipaddr, int port,
	                                                            IServerSockEP::MessageCallback callback,
	                                                            const TcpOptions &options);

	static std::unique_ptr<IClientSockEP> createTcpClientSockEP(const std::string &serverIpaddr, int port);
	static std::unique_ptr<IClientSockEP> createTcpClientSockEP(const std::string &serverIpaddr, int port,
	                                                            const TcpOptions &options);

	// UDP
	static std::unique_ptr<IServerSockEP> createUdpServerSockEP(const std::string &ipaddr, int port,
	                                                            IServerSockEP::MessageCallback callback,
	                                                            const std::string &multicastAddr = "",
	                                                            const std::string &interfaceAddr = "");
	static std::unique_ptr<IClientSockEP> createUdpClientSockEP(const std::string &serverIpaddr, int port,
	                                                            int ttl = -1);
};
} // namespace sockep
