#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

SHADOW_BEGIN_NAMESPACE

class SHADOW_API Log
{
public:
	Log() = default;
	~Log() = default;

	static void Init();
	inline static std::shared_ptr<spdlog::logger>& GetLogger() { return m_Logger; }

private:
	static std::shared_ptr<spdlog::logger> m_Logger;
};

SHADOW_END_NAMESPACE

//Application log macros
#define SHADOW_TRACE(...)      ::Shadow::Log::GetLogger()->trace(__VA_ARGS__)
#define SHADOW_INFO(...)       ::Shadow::Log::GetLogger()->info(__VA_ARGS__)
#define SHADOW_WARN(...)       ::Shadow::Log::GetLogger()->warn(__VA_ARGS__)
#define SHADOW_ERROR(...)      ::Shadow::Log::GetLogger()->error(__VA_ARGS__)
#define SHADOW_FATAL(...)      ::Shadow::Log::GetLogger()->fatal(__VA_ARGS__)