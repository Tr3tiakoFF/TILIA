#pragma once


#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

#include <memory>


namespace Tilia {

	class TILIA_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger();
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger();

	private:
	};

}

//Core log macros
#define TL_CORE_TRACE(...)		::Tilia::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TL_CORE_INFO(...)		::Tilia::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TL_CORE_WARN(...)		::Tilia::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TL_CORE_ERROR(...)		::Tilia::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TL_CORE_CRITICAL(...)	::Tilia::Log::GetCoreLogger()->critical(__VA_ARGS__)

//Client log macros
#define TL_TRACE(...)	::Tilia::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TL_INFO(...)		::Tilia::Log::GetClientLogger()->info(__VA_ARGS__)
#define TL_WARN(...)		::Tilia::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TL_ERROR(...)	::Tilia::Log::GetClientLogger()->error(__VA_ARGS__)
#define TL_CRITICAL(...)	::Tilia::Log::GetClientLogger()->critical(__VA_ARGS__)