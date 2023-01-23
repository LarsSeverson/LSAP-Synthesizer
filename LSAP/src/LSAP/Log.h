#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"

#include "spdlog/fmt/ostr.h"

namespace LSAP {
	class LSAP_API Log
	{
	public:
		static void initLog();

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return sCoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return sClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> sCoreLogger;
		static std::shared_ptr<spdlog::logger> sClientLogger;
	};
}
// Core side
#define LS_CORE_TRACE(...) ::LSAP::Log::getCoreLogger()->trace(__VA_ARGS__)
#define LS_CORE_INFO(...)  ::LSAP::Log::getCoreLogger()->info(__VA_ARGS__)
#define LS_CORE_WARN(...)  ::LSAP::Log::getCoreLogger()->warn(__VA_ARGS__)
#define LS_CORE_ERROR(...) ::LSAP::Log::getCoreLogger()->error(__VA_ARGS__)
#define LS_CORE_FATAL(...) ::LSAP::Log::getCoreLogger()->fatal(__VA_ARGS__)

// Client side (maybe we use maybe we don't)
#define LS_TRACE(...)      ::LSAP::Log::getClientLogger()->trace(__VA_ARGS__)
#define LS_INFO(...)       ::LSAP::Log::getClientLogger()->info(__VA_ARGS__)
#define LS_WARN(...)       ::LSAP::Log::getClientLogger()->warn(__VA_ARGS__)
#define LS_ERROR(...)      ::LSAP::Log::getClientLogger()->error(__VA_ARGS__)
#define LS_FATAL(...)      ::LSAP::Log::getClientLogger()->fatal(__VA_ARGS__)