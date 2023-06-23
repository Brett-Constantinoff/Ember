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

	class Logger
	{
	public:
		// singleton
		static Logger& getInstance();

		// public methods
		LogResult logInfo(const char* message, const LogType type = LogType::CONSOLE);
		LogResult logWarn(const char* message, const LogType type = LogType::CONSOLE);
		LogResult logError(const char* message, const LogType type = LogType::CONSOLE);

	private:
		enum class LogLevel
		{
			INFO = 0,
			WARN = 1,
			ERROR = 2
		};
		const std::string m_resetColor{"\033[0m"};
		const std::string m_infoColor{"\033[32m"};

	private:
		// singleton stuff
		Logger() {};
		~Logger() {};

		Logger(const Logger&) = delete;
		Logger& operator=(const Logger&) = delete;

		LogResult log(const char* message, LogLevel level, const LogType type = LogType::CONSOLE);
		std::string getLogTime();
	};
}
