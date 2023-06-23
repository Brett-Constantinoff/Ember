#include "Logger.h"

namespace Ember::Core
{
	Logger& logger = Logger::getInstance();


	Logger& Logger::getInstance()
	{
		static Logger logger;
		return logger;
	}

	LogResult Logger::logInfo(const char* message, LogType type)
	{
		return log(message, LogLevel::INFO, type);
	}

	LogResult Logger::logWarn(const char* message, LogType type)
	{
		return log(message, LogLevel::WARN, type);
	}

	LogResult Logger::logError(const char* message, LogType type)
	{
		return log(message, LogLevel::ERROR, type);
	}

	LogResult Logger::log(const char* message, LogLevel level, LogType type)
	{
		std::string startLog{ m_infoColor + '[' + getLogTime() + ']' + "in " + __FILE__};
		std::string endLog{m_resetColor + '\n'};
		switch (level)
		{
			case LogLevel::INFO:
				std::cout << startLog <<  ":::INFO:::" << message << endLog;
				break;
			case LogLevel::WARN:
				break;
			case LogLevel::ERROR:
				break;
		}
	}

	std::string Logger::getLogTime()
	{
		auto currentTime = std::chrono::system_clock::now();
		std::time_t currentTimeT = std::chrono::system_clock::to_time_t(currentTime);
		std::string currentTimeString = std::ctime(&currentTimeT);
		return currentTimeString;
	}
}