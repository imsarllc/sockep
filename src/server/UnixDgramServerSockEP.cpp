#include "UnixDgramServerSockEP.h"
#include "client/UnixDgramClientSockEP.h" // so server can create new server side clients
#include <iostream>
#include <sys/poll.h>
#include <sys/socket.h>

#include "simpleLogger/SimpleLogger.h"

using namespace sockep;

UnixDgramServerSockEP::UnixDgramServerSockEP(const std::string &bindPath, MessageCallback callback)
    : ServerSockEP(callback), slen_{sizeof(saddr_)}
{
	simpleLogger.debug << "Constructing Unix Datagram Server Socket...\n";

	memset(&saddr_, 0, sizeof(struct sockaddr_un));
	strncpy(saddr_.sun_path, bindPath.c_str(), sizeof(saddr_.sun_path) - 1);
	saddr_.sun_family = AF_UNIX;

	sock_ = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (sock_ == -1)
	{
		simpleLogger.error << "Failed to create socket!\n";
		return;
	}
	unlink(saddr_.sun_path);
	int bind_retval = bind(sock_, (struct sockaddr *)&saddr_, sizeof(saddr_));
	if (bind_retval == -1)
	{
		simpleLogger.error << "Failed to bind socket to: " << saddr_.sun_path << "\n";
		return;
	}


	isValid_ = true;
}

UnixDgramServerSockEP::~UnixDgramServerSockEP()
{
	simpleLogger.debug << "Unix Dgram Server Destructor\n";
	// close the socket
	closeSocket();
	unlink(saddr_.sun_path);
}


void UnixDgramServerSockEP::handlePfdUpdates(const std::vector<struct pollfd> &pfds,
                                             std::vector<struct pollfd> &newPfds,
                                             std::vector<struct pollfd> &removePfds)
{
	for (const struct pollfd &pfd : pfds)
	{
		simpleLogger.debug << "Fd: " << pfd.fd << " | events: " << pfd.events << " | revents : " << pfd.revents << "\n";
		// handle receive socket
		if (pfd.fd == sock_ && pfd.revents & POLLIN)
		{ // new datagram
			std::shared_ptr<ISSClientSockEP> newClient = createNewClient();
			simpleLogger.debug << "Got new client\n";
			newClient->clearSaddr();

			auto len = newClient->getSaddrLen();
			int bytesReceived = recvfrom(sock_, msg_.data(), msg_.size(), 0, newClient->getSaddr(), &len);
			msg_[bytesReceived] = '\0';
			simpleLogger.debug << "Received " << bytesReceived << " bytes from " << newClient->to_str() << "\n";

			std::pair<int, bool> client = addClient(newClient);

			if (client.second) // new client
			{
				notifyConnectionEvent(client.first, ConnectionEvent::CONNECTED, clients_.size());
			}

			if (callback_)
			{
				callback_(client.first, msg_.data(), bytesReceived);
			}
		}
		else if (pfd.fd == pipeFd_[0] && pfd.revents & POLLHUP)
		{ // need to terminate
			serverRunning_ = false;
			simpleLogger.debug << "stopping Unix Dgram server\n";
			break;
		}
		else if (pfd.fd != sock_ && pfd.fd != pipeFd_[0])
		{
			simpleLogger.error << "No idea what happened here\n";
			serverRunning_ = false;
			break;
		}
	}
}

std::shared_ptr<ISSClientSockEP> UnixDgramServerSockEP::createNewClient()
{
	return std::make_shared<UnixDgramClientSockEP>();
}

int UnixDgramServerSockEP::sendMessageToClient(int clientId, const char *msg, size_t msgLen)
{
	if (msgLen > msg_.size())
	{
		simpleLogger.error << "Datagram message too long! Max Datagram length: " << msg_.size() << "\n";
		return -1;
	}

	if (!isValid())
	{
		simpleLogger.error << "Server is not valid\n";
		return -1;
	}

	// Acquire shared_ptr to client while holding lock
	std::shared_ptr<ISSClientSockEP> client;
	{
		std::lock_guard<std::recursive_mutex> lock(clientsMutex_);
		auto clientIt = clients_.find(clientId);
		if (clientIt == clients_.end())
		{
			simpleLogger.error << "Could not find client with id " << clientId << "\n";
			return -1;
		}
		client = clientIt->second;
	}

	simpleLogger.debug << "sending " << msgLen << " bytes to " << client->to_str() << " with sock " << sock_
	                   << "\nAnd saddr len: " << client->getSaddrLen() << "\n";
	int retval = sendto(sock_, msg, msgLen, 0, client->getSaddr(), client->getSaddrLen());
	if (retval == -1)
	{
		simpleLogger.error << "Failed to send message, errno: " << errno << "\n";
	}
	return retval;
}

int UnixDgramServerSockEP::sendMessageToClient(int clientId, const std::string &msg)
{
	return sendMessageToClient(clientId, msg.c_str(), msg.size());
}
