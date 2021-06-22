#pragma once

#include <Log.h>

#ifndef SMPX_CONFIG_DIST
	#define LOG_INFO(...)		Log::Info(__VA_ARGS__)
	#define LOG_WARN(...)		Log::Warn(__VA_ARGS__)
	#define LOG_ERROR(...)		Log::Error(__VA_ARGS__)
	#define LOG_CRITICAL(...)	Log::Critical(__VA_ARGS__)

	#define ASSERT_WARN(x, ...) do { if (!(x)) { LOG_WARN(__VA_ARGS__); } } while(0)
	#define ASSERT_ERROR(x, ...) do { if (!(x)) { LOG_WARN(__VA_ARGS__); } } while(0)
	#define ASSERT_CRITICAL(x, ...) do { if (!(x)) { LOG_CRITICAL(__VA_ARGS__); std::cin.get(); exit(-1); } } while(0)
#else
	#define LOG_INFO(...)		
	#define LOG_WARN(...)		
	#define LOG_ERROR(...)	
	#define LOG_CRITICAL(...) 

	#define ASSERT_WARN(x, ...)
	#define ASSERT_ERROR(x, ...)
	#define ASSERT_CRITICAL(x, ...)
#endif
