#pragma once

#ifndef DEFAULT_MAX_LEN
#define DEFAULT_MAX_LEN 5000
#endif

#include "client/ISSClientSockEP.h"
#include "server/IServerSockEP.h"

#include <atomic>
#include <cstring>
#include <map>
#include <memory>
#include <mutex>
#include <thread>

#include <sys/poll.h>

namespace sockep
{

enum class ServerSockEPType
{
	unixDgram,
	unixStream,
	tcp,
	udp,
};

class ServerSockEP : public IServerSockEP
{
public:
	ServerSockEP(MessageCallback callback);
	virtual ~ServerSockEP();

	bool isValid() override { return isValid_; };
	virtual void setBufferSize(unsigned int size) override;


	virtual void startServer() override;
	virtual void stopServer() override;
	bool serverRunning() override;

	void setCallback(std::function<void(int, const char *, size_t)> callback) override;

	virtual int sendMessageToClient(int clientId, const char *msg, size_t msgLen) = 0;
	virtual int sendMessageToClient(int clientId, const std::string &msg) = 0;
	virtual void sendMessageToAll(const char *msg, size_t msgLen) override;
	virtual void sendMessageToAll(const std::string &msg) override;
	virtual std::vector<int> getClientIds() override;
	virtual std::string getClientAddress(int clientId) override;
	virtual std::string to_str() override
	{
		std::string s = "howdy";
		return s;
	};

	virtual void registerConnectionEventHandler(const std::string &id, ConnectionCallback cb) override;
	virtual void unregisterConnectionEventHandler(const std::string &id) override;
	virtual std::string getConnectionEventName(ConnectionEvent event) const override;

protected:
	// Create (or find) a client matching the provided client (by address)
	// Returns a pair of {int clientId, bool isNewClient}
	virtual std::pair<int, bool> addClient(std::unique_ptr<ISSClientSockEP> newClient);

	void runServer();
	virtual void handlePfdUpdates(const std::vector<struct pollfd> &pfds, std::vector<struct pollfd> &newPfds,
	                              std::vector<struct pollfd> &removePfds) = 0;
	virtual void closeSocket();
	void notifyConnectionEvent(int clientId, ConnectionEvent status);

	// allow concrete class to create the proper type of client
	virtual std::unique_ptr<ISSClientSockEP> createNewClient() = 0;

	ServerSockEPType sockType_;
	std::atomic<bool> serverRunning_{false};
	int sock_ = -1;
	bool isValid_ = false;
	std::vector<char> msg_;

	// this should probably hold a unique pointer
	std::map<int, std::unique_ptr<ISSClientSockEP>> clients_;
	std::recursive_mutex clientsMutex_;
	std::thread serverThread_;
	MessageCallback callback_;
	std::map<std::string, ConnectionCallback> connectionCallbacks_;
	int pipeFd_[2];
};
} // namespace sockep
