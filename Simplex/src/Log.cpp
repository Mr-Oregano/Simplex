
// Precompiled
#include <sxpch.h>
//

#include <Log.h>

void Log::Init(const std::string &name)
{
	spdlog::set_pattern("[%T] %n: %^%v%$");

	logger = spdlog::stdout_color_mt(name);
	logger->set_level(spdlog::level::trace);

	auto color_sink = static_cast<spdlog::sinks::stdout_color_sink_mt *>(logger->sinks()[0].get());

#ifdef SMPX_SYSTEM_WINDOWS
	color_sink->set_color(spdlog::level::info, 0x03); // CYAN
#else
	color_sink->set_color(spdlog::level::info, "\033[34m");
#endif

}

void Log::Shutdown()
{
	// No resources to release yet
}
