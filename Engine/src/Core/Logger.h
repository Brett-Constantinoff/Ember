#pragma once
#include <chrono>
#include <ctime>
#include <iostream>

namespace Ember::Core
{
	enum class LogType
	{
		CONSOLE = 0,
		FILE = 1
	};

	enum class LogResult
	{
		SUCCESS = 0,
		ERROR = 1
	};

	// not thead safe, if multithreading is used in the future this will
	// need to be updated
	class Logger
	{
	public:
		// singleton
		static Logger& getInstance();

		// public methods
		LogResult logInfo(std::string& message, const char* file,  const LogType type = LogType::CONSOLE);
		LogResult logWarn(std::string& message, const char* file, const LogType type = LogType::CONSOLE);
		LogResult logError(std::string& message, const char* file, const LogType type = LogType::CONSOLE);

	private:
		enum class LogLevel
		{
			INFO = 0,
			WARN = 1,
			ERROR = 2
		};
		const std::string m_resetColor{"\033[0m"};
		const std::string m_infoColor{"\033[32m"};
		const std::string m_warnColor{"\033[33m"};
		const std::string m_errorColor{"\033[31m"};

	private:
		// singleton stuff
		Logger() {};
		~Logger() {};

		Logger(const Logger&) = delete;
		Logger& operator=(const Logger&) = delete;

		LogResult log(std::string& message, const char* file, LogLevel level, const LogType type = LogType::CONSOLE);
		std::string getLogTime();
	};
}
