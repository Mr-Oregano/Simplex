
#include <Log.h>

void Log::Init()
{
	spdlog::set_pattern("[%T] %n: %^%v%$");

	logger = spdlog::stdout_color_mt("SIMPLEX");
	logger->set_level(spdlog::level::trace);

	auto color_sink = static_cast<spdlog::sinks::stdout_color_sink_mt *>(logger->sinks()[0].get());
	color_sink->set_color(spdlog::level::info, 0x3); // CYAN
}

void Log::Shutdown()
{
}


