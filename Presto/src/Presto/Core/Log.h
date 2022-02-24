#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Presto
{

	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define PRESTO_CORE_TRACE(...)    ::Presto::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PRESTO_CORE_INFO(...)     ::Presto::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PRESTO_CORE_WARN(...)     ::Presto::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PRESTO_CORE_ERROR(...)    ::Presto::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PRESTO_CORE_FATAL(...)    ::Presto::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define PRESTO_TRACE(...)	      ::Presto::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PRESTO_INFO(...)	      ::Presto::Log::GetClientLogger()->info(__VA_ARGS__)
#define PRESTO_WARN(...)	      ::Presto::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PRESTO_ERROR(...)	      ::Presto::Log::GetClientLogger()->error(__VA_ARGS__)
#define PRESTO_FATAL(...)	      ::Presto::Log::GetClientLogger()->fatal(__VA_ARGS__)

