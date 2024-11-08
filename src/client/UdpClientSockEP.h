#pragma once

#include "ClientSockEP.h"
#include "ISSClientSockEP.h"
#include <arpa/inet.h>
#include <iostream>

namespace sockep
{

class UdpClientSockEP : public ClientSockEP, public ISSClientSockEP
{
public:
	UdpClientSockEP(std::string serverIpaddr, int port);
	UdpClientSockEP(); // for server side client creation
	~UdpClientSockEP();

	// for both interfaces (Client and Server Side Client)
	int sendMessage(const char *msg, size_t msgLen) override;
	int sendMessage(const std::string &msg) override;
	std::string to_str() const override;

	// for Client interface
	std::string getMessage() override;
	int getMessage(char *msg, const int msgMaxLen) override;

	// for Server Side Client interface
	bool operator==(ISSClientSockEP const *other) override;
	bool operator==(ISSClientSockEP const &other) override;
	void clearSaddr() override;
	struct sockaddr *getSaddr() const override;
	socklen_t getSaddrLen() const override;

	void setSock(int sock) override;
	int getSock() const override;

	void setTtl(int ttl);

private:
	bool connectSocket();
	bool disconnectSocket();
	bool reconnectSocket();
	void handleIncomingMessage() override;
	bool handleError(int error) override;
	struct sockaddr_in saddr_;
	struct sockaddr_in serverSaddr_;
};

} // namespace sockep
