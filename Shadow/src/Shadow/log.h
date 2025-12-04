#pragma once

#include "config.h"
#include "spdlog/spdlog.h"

namespace Shadow
{
	class SHADOW_API Log
	{
	public:
		Log() = default;
		~Log() = default;

		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return m_EngineLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetAppLogger() { return m_AppLogger; }

	private:
		static std::shared_ptr<spdlog::logger> m_EngineLogger;
		static std::shared_ptr<spdlog::logger> m_AppLogger;
	};
}

//Engine log macros
#define SHADOW_ENGINE_TRACE(...)   ::Shadow::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define SHADOW_ENGINE_INFO(...)    ::Shadow::Log::GetEngineLogger()->info(__VA_ARGS__)
#define SHADOW_ENGINE_WARN(...)    ::Shadow::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define SHADOW_ENGINE_ERROR(...)   ::Shadow::Log::GetEngineLogger()->error(__VA_ARGS__)
#define SHADOW_ENGINE_FATAL(...)   ::Shadow::Log::GetEngineLogger()->fatal(__VA_ARGS__)

//Application log macros
#define SHADOW_APP_TRACE(...)      ::Shadow::Log::GetAppLogger()->trace(__VA_ARGS__)
#define SHADOW_APP_INFO(...)       ::Shadow::Log::GetAppLogger()->info(__VA_ARGS__)
#define SHADOW_APP_WARN(...)       ::Shadow::Log::GetAppLogger()->warn(__VA_ARGS__)
#define SHADOW_APP_ERROR(...)      ::Shadow::Log::GetAppLogger()->error(__VA_ARGS__)
#define SHADOW_APP_FATAL(...)      ::Shadow::Log::GetAppLogger()->fatal(__VA_ARGS__)