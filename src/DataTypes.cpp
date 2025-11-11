#include "DataTypes.h"

namespace sockep
{

std::string stringifyConnectionEvent(ConnectionEvent event)
{
	switch (event)
	{
	case ConnectionEvent::CONNECTED:
		return "connected";
	case ConnectionEvent::DISCONNECTED:
		return "disconnected";
	default:
		return "unknown_event";
	};
}


} // namespace sockep