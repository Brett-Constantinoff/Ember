#include "Logger.h"

namespace Ember::Core
{
	Logger& Logger::getInstance()
	{
		static Logger logger;
		return logger;
	}

	LogResult Logger::logInfo(std::string& message, const char* file, LogType type)
	{
		return log(message, file, LogLevel::Info, type);
	}

	LogResult Logger::logWarn(std::string& message, const char* file, LogType type)
	{
		return log(message, file, LogLevel::Warn, type);
	}

	LogResult Logger::logError(std::string& message, const char* file, LogType type)
	{
		return log(message, file, LogLevel::Error, type);
	}

	LogResult Logger::log(std::string& message, const char* file, LogLevel level, LogType type)
	{
		std::string startLog{'[' + getLogTime() + ']' + "in " + file};
		std::string endLog{m_resetColor + '\n'};
		switch (level)
		{
			case LogLevel::Info:
				std::cout << m_infoColor << startLog <<  ":::INFO:::" << message << endLog;
				break;
			case LogLevel::Warn:
				std::cout << m_warnColor << startLog << ":::WARN:::" << message << endLog;
				break;
			case LogLevel::Error:
				std::cout << m_errorColor << startLog << ":::ERROR:::" << message << endLog;
				// throw an empty error so we exit gracefully,
				// all errors that occur cannot be handled and
				// the app will have to quit
				throw std::runtime_error{""};
		}
		return LogResult::Success;
	}

	std::string Logger::getLogTime()
	{
		auto currentTime = std::chrono::system_clock::now();
		std::time_t currentTimeT = std::chrono::system_clock::to_time_t(currentTime);
		std::string currentTimeString = std::ctime(&currentTimeT);
		return currentTimeString;
	}
}