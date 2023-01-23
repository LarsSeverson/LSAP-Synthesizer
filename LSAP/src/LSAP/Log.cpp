#include "lspch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace LSAP {
	std::shared_ptr<spdlog::logger> Log::sCoreLogger;
	std::shared_ptr<spdlog::logger> Log::sClientLogger;

	void Log::initLog() {
		spdlog::set_pattern("%^[%T] %n: %v%$");

		sCoreLogger = spdlog::stdout_color_mt("LSAP");
		sCoreLogger->set_level(spdlog::level::trace);

		sClientLogger = spdlog::stderr_color_mt("APP");
		sClientLogger->set_level(spdlog::level::trace);
	}
}