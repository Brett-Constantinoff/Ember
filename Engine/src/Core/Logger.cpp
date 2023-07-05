#include "Logger.h"

namespace Ember::Core
{
	Logger& logger = Logger::getInstance();


	Logger& Logger::getInstance()
	{
		static Logger logger;
		return logger;
	}

	LogResult Logger::logInfo(std::string& message, const char* file, LogType type)
	{
		return log(message, file, LogLevel::INFO, type);
	}

	LogResult Logger::logWarn(std::string& message, const char* file, LogType type)
	{
		return log(message, file, LogLevel::WARN, type);
	}

	LogResult Logger::logError(std::string& message, const char* file, LogType type)
	{
		return log(message, file, LogLevel::ERROR, type);
	}

	LogResult Logger::log(std::string& message, const char* file, LogLevel level, LogType type)
	{
		std::string startLog{'[' + getLogTime() + ']' + "in " + file};
		std::string endLog{m_resetColor + '\n'};
		switch (level)
		{
			case LogLevel::INFO:
				std::cout << m_infoColor << startLog <<  ":::INFO:::" << message << endLog;
				break;
			case LogLevel::WARN:
				std::cout << m_warnColor << startLog << ":::WARN:::" << message << endLog;
				break;
			case LogLevel::ERROR:
				std::cout << m_errorColor << startLog << ":::ERROR:::" << message << endLog;
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