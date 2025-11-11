#pragma once

#include <string>

namespace sockep
{

enum ConnectionEvent
{
	CONNECTED,
	DISCONNECTED
};

std::string stringifyConnectionEvent(ConnectionEvent event);

} // namespace sockep