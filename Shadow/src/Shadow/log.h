#pragma once

#include "Shadow/config.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

SHADOW_BEGIN_NAMESPACE

class Log
{
public:
    Log() = default;
    ~Log() = default;

    static SHADOW_API void Init();
    inline static SHADOW_API std::shared_ptr<spdlog::logger>& GetLogger() { return m_Logger; }

private:
    static std::shared_ptr<spdlog::logger> m_Logger;
};

SHADOW_END_NAMESPACE

//Application log macros
#ifndef SHADOW_FINAL
    #define SHADOW_LOG_TRACE(...)      ::Shadow::Log::GetLogger()->trace(__VA_ARGS__)
    #define SHADOW_LOG_INFO(...)       ::Shadow::Log::GetLogger()->info(__VA_ARGS__)
    #define SHADOW_LOG_WARN(...)       ::Shadow::Log::GetLogger()->warn(__VA_ARGS__)
#else
    #define SHADOW_LOG_TRACE(...)
    #define SHADOW_LOG_INFO(...)
    #define SHADOW_LOG_WARN(...)
#endif

#define SHADOW_LOG_ERROR(...)      ::Shadow::Log::GetLogger()->error(__VA_ARGS__)
#define SHADOW_LOG_FATAL(...)      ::Shadow::Log::GetLogger()->fatal(__VA_ARGS__)

#ifndef SHADOW_FINAL
    #define SHADOW_ASSERT(x, ...) { if(!(x)) { SHADOW_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); SHADOW_DEBUG_BREAK(); } }
#endif