#pragma once

#ifndef SMPX_CONFIG_DIST
	#ifdef _MSC_VER
		#define DEBUG_BREAK() __debugbreak()
	#elif __GNUC__
		#define DEBUG_BREAK() __builtin_trap()
	#else 
		#define DEBUG_BREAK()
#endif
#else
	#define DEBUG_BREAK()
#endif

#ifdef _MSC_VER
	#define SMPX_FORCE_INLINE __forceinline
#elif __GNUC__
	#define SMPX_FORCE_INLINE __attribute__((always_inline))
#else
	#define SMPX_FORCE_INLINE
#endif