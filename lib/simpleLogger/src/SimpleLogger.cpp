#include "SimpleLogger.h"

#ifndef SIMPLE_LOGGER_LEVEL
#define SIMPLE_LOGGER_LEVEL warning
#endif

#ifndef SIMPLE_LOGGER_OSTREAM
#define SIMPLE_LOGGER_OSTREAM std::cout
#endif

std::shared_ptr<SimpleLogger> SimpleLogger::instancePtr()
{
	static std::shared_ptr<SimpleLogger> instance =
	    std::shared_ptr<SimpleLogger>(new SimpleLogger(&SIMPLE_LOGGER_OSTREAM, Level::SIMPLE_LOGGER_LEVEL));
	return instance;
}
