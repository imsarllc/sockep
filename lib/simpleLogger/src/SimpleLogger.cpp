#include "SimpleLogger.h"

#ifndef SIMPLE_LOGGER_LEVEL
#define SIMPLE_LOGGER_LEVEL warning
#endif

#ifndef SIMPLE_LOGGER_OSTREAM
#define SIMPLE_LOGGER_OSTREAM std::cout
#endif

SimpleLogger &SimpleLogger::get()
{
	static std::unique_ptr<SimpleLogger> s_simpleLogger;
	if (!s_simpleLogger)
	{
		s_simpleLogger =
		    std::unique_ptr<SimpleLogger>(new SimpleLogger(&SIMPLE_LOGGER_OSTREAM, Level::SIMPLE_LOGGER_LEVEL));
	}
	return *s_simpleLogger;
}
