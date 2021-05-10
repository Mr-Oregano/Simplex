
#include <Log.h>
#include <Introduction.h>

namespace Simplex
{
	void Introduce(void)
	{
		Log::Init();

		Log::Info("Welcome to the {0}!", "Simplex Game Engine");
		Log::Warn("This is a warning!");
		Log::Error("This is an error!");
		Log::Critical("This is a fatal error!\n");

		#ifdef SMPX_CONFIG_DEBUG

			Log::Info("Running SMPX_CONFIG_DEBUG...\n");

		#elif defined SMPX_CONFIG_RELEASE

			Log::Info("Running SMPX_CONFIG_RELEASE...\n");

		#elif defined SMPX_CONFIG_DIST

			Log::Info("Running SMPX_CONFIG_DIST...\n");

		#endif

		Log::Info("{0} + {1} = {2}", 5, 23, 5 + 23);
	
		Log::Shutdown();
	}
}