#pragma once

#include <Defines.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>

#include <memory>
#include <string>
#include <utility>

#ifndef SMPX_CONFIG_DIST

#define LOG_INFO(...)		Log::info(__VA_ARGS__)
#define LOG_WARN(...)		Log::warn(__VA_ARGS__)
#define LOG_ERROR(...)		Log::error(__VA_ARGS__)
#define LOG_CRITICAL(...)	Log::critical(__VA_ARGS__)

#define ASSERT_WARN(x, ...) do { if (!(x)) { LOG_WARN(__VA_ARGS__); } } while(0)
#define ASSERT_ERROR(x, ...) do { if (!(x)) { LOG_WARN(__VA_ARGS__); } } while(0)
#define ASSERT_CRITICAL(x, ...) do { if (!(x)) { LOG_CRITICAL(__VA_ARGS__); DEBUG_BREAK(); } } while(0)

#else

#define LOG_INFO(...)		
#define LOG_WARN(...)		
#define LOG_ERROR(...)	
#define LOG_CRITICAL(...) 

#define ASSERT_WARN(x, ...)
#define ASSERT_ERROR(x, ...)
#define ASSERT_CRITICAL(x, ...)
#endif

class Log
{
private:
    inline static std::shared_ptr<spdlog::logger> logger = nullptr;

public:
    static void Init(const std::string &name);
    static void Shutdown();

	template<typename... Args>
	SMPX_FORCE_INLINE static void info(spdlog::format_string_t<Args...> fmt, Args &&... args)
	{
		logger->info(fmt, std::forward<Args>(args)...);
	}

	template<typename T>
	SMPX_FORCE_INLINE static void info(const T &msg)
	{
		logger->info(msg);
	}

	template<typename... Args>
	SMPX_FORCE_INLINE static void warn(spdlog::format_string_t<Args...> fmt, Args &&... args)
	{
		logger->warn(fmt, std::forward<Args>(args)...);
	}

	template<typename T>
	SMPX_FORCE_INLINE static void warn(const T &msg)
	{
		logger->warn(msg);
	}

	template<typename... Args>
	SMPX_FORCE_INLINE static void error(spdlog::format_string_t<Args...> fmt, Args &&... args)
	{
		logger->error(fmt, std::forward<Args>(args)...);
	}

	template<typename T>
	SMPX_FORCE_INLINE static void error(const T &msg)
	{
		logger->error(msg);
	}

	template<typename... Args>
	SMPX_FORCE_INLINE static void critical(spdlog::format_string_t<Args...> fmt, Args &&... args)
	{
		logger->critical(fmt, std::forward<Args>(args)...);
	}

	template<typename T>
	SMPX_FORCE_INLINE static void critical(const T &msg)
	{
		logger->critical(msg);
	}
};