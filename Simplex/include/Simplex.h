#pragma once

#include <Log.h>

#ifndef SMPX_CONFIG_DIST
	#define LOG_INFO(x)		Log::Info(x)
	#define LOG_WARN(x)		Log::Warn(x)
	#define LOG_ERROR(x)	Log::Error(x)
	#define LOG_CRITICAL(x) Log::Critical(x)

	#define ASSERT_CRITICAL(x, m) do { if (!x) { LOG_CRITICAL(m); exit(-1); } } while(0)
#else
	#define LOG_INFO(x)		
	#define LOG_WARN(x)		
	#define LOG_ERROR(x)	
	#define LOG_CRITICAL(x) 

	#define ASSERT_CRITICAL(x, m)
#endif

#ifndef SMPX_SYSTEM_WINDOWS
	#error "Simplex only supports Windows currently"
#endif