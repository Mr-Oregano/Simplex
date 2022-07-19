#pragma once

#include <Log.h>

#ifndef SMPX_CONFIG_DIST
#ifdef _MSC_VER
	#define DEBUG_BREAK() __debugbreak()
#elif __GNUC__
	#define DEBUG_BREAK() __builtin_trap()
#else 
	#define DEBUG_BREAK()
#endif

	#define LOG_INFO(...)		Log::Get()->info(__VA_ARGS__)
	#define LOG_WARN(...)		Log::Get()->warn(__VA_ARGS__)
	#define LOG_ERROR(...)		Log::Get()->error(__VA_ARGS__)
	#define LOG_CRITICAL(...)	Log::Get()->critical(__VA_ARGS__)

	#define ASSERT_WARN(x, ...) do { if (!(x)) { LOG_WARN(__VA_ARGS__); } } while(0)
	#define ASSERT_ERROR(x, ...) do { if (!(x)) { LOG_WARN(__VA_ARGS__); } } while(0)
	#define ASSERT_CRITICAL(x, ...) do { if (!(x)) { LOG_CRITICAL(__VA_ARGS__); DEBUG_BREAK(); } } while(0)

#else
	#define DEBUG_BREAK()

	#define LOG_INFO(...)		
	#define LOG_WARN(...)		
	#define LOG_ERROR(...)	
	#define LOG_CRITICAL(...) 

	#define ASSERT_WARN(x, ...)
	#define ASSERT_ERROR(x, ...)
	#define ASSERT_CRITICAL(x, ...)
#endif
