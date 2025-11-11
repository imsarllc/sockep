#pragma once

#include <functional>
#include <string>
#include <vector>

#include "sockep/DataTypes.h"

// #define SOCKEP_SERVER_TRANSMIT_MSG_MAX_LEN 1000

namespace sockep
{

class IServerSockEP
{
public:
	using MessageCallback = std::function<void(int clientId, const char *data, size_t dataLength)>;

	virtual ~IServerSockEP() = default;

	virtual bool isValid() = 0;
	virtual void setBufferSize(unsigned int size) = 0;

	virtual void startServer() = 0;
	virtual void stopServer() = 0;
	virtual bool serverRunning() = 0;
	virtual void setCallback(std::function<void(int, const char *, size_t)> callback) = 0;
	// virtual int sendMessageToClient(int clientId, const std::array<char, SOCKEP_SERVER_TRANSMIT_MSG_MAX_LEN>, size_t
	// msgLen) = 0;
	virtual int sendMessageToClient(int clientId, const char *msg, size_t msgLen) = 0;
	virtual int sendMessageToClient(int clientId, const std::string &msg) = 0;
	virtual void sendMessageToAll(const char *msg, size_t msgLen) = 0;
	virtual void sendMessageToAll(const std::string &msg) = 0;
	virtual std::vector<int> getClientIds() = 0;
	virtual std::string getClientAddress(int clientId) = 0;
	virtual std::string to_str() = 0;

	using ConnectionCallback = std::function<void(int clientId, ConnectionEvent event, unsigned int count)>;
	virtual void registerConnectionEventHandler(const std::string &id, ConnectionCallback cb) = 0;
	virtual void unregisterConnectionEventHandler(const std::string &id) = 0;
};
} // namespace sockep
