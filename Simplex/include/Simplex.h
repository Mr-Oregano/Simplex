#pragma once

#include <Log.h>

#ifndef SMPX_CONFIG_DIST
	#define LOG_INFO(x, ...)		Log::Info(x, __VA_ARGS__)
	#define LOG_WARN(x, ...)		Log::Warn(x, __VA_ARGS__)
	#define LOG_ERROR(x, ...)		Log::Error(x, __VA_ARGS__)
	#define LOG_CRITICAL(x, ...)	Log::Critical(x, __VA_ARGS__)

	#define ASSERT_WARN(x, m, ...) do { if (!(x)) { LOG_WARN(m, __VA_ARGS__); } } while(0)
	#define ASSERT_ERROR(x, m, ...) do { if (!(x)) { LOG_WARN(m, __VA_ARGS__); } } while(0)
	#define ASSERT_CRITICAL(x, m, ...) do { if (!(x)) { LOG_CRITICAL(m, __VA_ARGS__); exit(-1); } } while(0)
#else
	#define LOG_INFO(x, ...)		
	#define LOG_WARN(x, ...)		
	#define LOG_ERROR(x, ...)	
	#define LOG_CRITICAL(x, ...) 

	#define ASSERT_WARN(x, m, ...)
	#define ASSERT_ERROR(x, m, ...)
	#define ASSERT_CRITICAL(x, m, ...)
#endif

#ifndef SMPX_SYSTEM_WINDOWS
	#error "Simplex only supports Windows currently"
#endif