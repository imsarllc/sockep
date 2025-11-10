#pragma once

#ifndef DEFAULT_MAX_LEN
#define DEFAULT_MAX_LEN 5000
#endif

#include "client/IClientSockEP.h"
#include <atomic>
#include <sys/poll.h>
#include <thread>
#include <vector>

namespace sockep
{

enum class ClientSockEPType
{
	unixDgram,
	unixStream,
	tcp,
	udp,
};

class ClientSockEP : public IClientSockEP
{
public:
	ClientSockEP();
	virtual ~ClientSockEP();

	bool isValid() override { return isValid_; };
	virtual void setBufferSize(unsigned int size) override;

	virtual int sendMessage(const char *msg, size_t msgLen) override = 0;
	virtual int sendMessage(const std::string &msg) override = 0;
	virtual std::string getMessage() override = 0;
	virtual int getMessage(char *msg, const int msgMaxLen) override = 0;
	virtual std::string to_str() const override = 0;

	virtual int startRecvThread(MessageCallback callback) override;
	virtual int stopRecvThread() override;
	virtual bool recvThreadRunning() override;

protected:
	// This is for the concrete implementations to handle in an implementation-specific way
	virtual void handleIncomingMessage() = 0;
	virtual bool handleError(int error) { return false; };

	void runThread();
	std::thread recvThread_;
	std::atomic<bool> threadRunning_{false};
	MessageCallback callback_;
	int pipeFd_[2];

	ClientSockEPType sockType_;
	bool isValid_{false};
	int sock_ = -1;
	std::vector<char> msg_;
};

} // namespace sockep
