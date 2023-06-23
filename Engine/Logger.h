#pragma once
#include <string_view>

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
		LogResult logInfo(std::string_view& message, const LogType type = LogType::CONSOLE);
		LogResult logWarn(std::string_view& message, const LogType type = LogType::CONSOLE);
		LogResult logError(std::string_view& message, const LogType type = LogType::CONSOLE);

	private:
		// singleton stuff
		Logger();
		~Logger();

		Logger(const Logger&) = delete;
		Logger& operator=(const Logger&) = delete;

		// normal private stuff
		enum class LogLevel
		{
			INFO = 0,
			WARN = 1,
			ERROR = 2
		};

		LogResult log(std::string_view& message, LogLevel level, const LogType type = LogType::CONSOLE);
	};
}
