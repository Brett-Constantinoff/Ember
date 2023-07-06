#pragma once
#include <chrono>
#include <ctime>
#include <iostream>

namespace Ember::Core
{
	enum class LogType
	{
		Console = 0,
		File = 1
	};

	enum class LogResult
	{
		Success = 0,
		Error = 1
	};

	// not thead safe, if multithreading is used in the future this will
	// need to be updated
	class Logger
	{
	public:
		// singleton
		static Logger& getInstance();

		// public methods
		LogResult logInfo(std::string& message, const char* file,  const LogType type = LogType::Console);
		LogResult logWarn(std::string& message, const char* file, const LogType type = LogType::Console);
		LogResult logError(std::string& message, const char* file, const LogType type = LogType::Console);

	private:
		enum class LogLevel
		{
			Info = 0,
			Warn = 1,
			Error = 2
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

		LogResult log(std::string& message, const char* file, LogLevel level, const LogType type = LogType::Console);
		std::string getLogTime();
	};
}
