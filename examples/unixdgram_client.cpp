#include "sockep/SockEPFactory.h"

#include <iostream>

int main(int argc, char *argv[])
{
	std::unique_ptr<sockep::IClientSockEP> client;
	if (argc > 1)
	{
		client = sockep::SockEPFactory::createUnixDgramClientSockEP(argv[1], "/tmp/unixdgramserver");
	}
	else
	{
		client = sockep::SockEPFactory::createUnixDgramClientSockEP("/tmp/unixdgramclient", "/tmp/unixdgramserver");
	}

	std::cout << "Client valid: " << (client->isValid() ? "true" : "false") << std::endl;

	std::string inp;
	while (true)
	{
		std::cout << "> ";
		std::getline(std::cin, inp);

		client->sendMessage(inp); // inp.c_str(), inp.size());

		if (inp == "quit")
		{
			break;
		}
		if (inp == "read")
		{
			std::cout << client->getMessage() << "\n";
		}
	}
	// client->sendMessage("Hello Socket!");

	// std::string serverMsg = client->getMessage();
	// std::cout << "Got message from server: " << serverMsg << std::endl;

	// client->sendMessage("I found you!");
	// serverMsg = client->getMessage();
	// std::cout << "Got message from server: " << serverMsg << std::endl;

	// client->sendMessage("quit");

	return 0;
}
