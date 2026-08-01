#include "precomp.h"
#include "log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

SHADOW_BEGIN_NAMESPACE

std::shared_ptr<spdlog::logger> Log::m_Logger;

void Log::Init()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");

	m_Logger = spdlog::stdout_color_mt("SHADOW");
	m_Logger->set_level(spdlog::level::trace);
}

SHADOW_END_NAMESPACE