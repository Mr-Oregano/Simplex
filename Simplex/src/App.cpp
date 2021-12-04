
// Precompiled
#include <sxpch.h>
//

#include <App.h>

#include <Log.h>
#include <Simplex.h>

App::App()
{
	InitServices();
	LOG_INFO("Initialized services.");
}

App::~App()
{
	LOG_INFO("Shutting down services...");
	ShutdownServices();
}

void App::InitServices()
{
#ifndef SMPX_CONFIG_DIST
	Log::Init("SIMPLEX");
#endif
}

void App::ShutdownServices()
{
#ifndef SMPX_CONFIG_DIST
	Log::Shutdown();
#endif
}

int main() 
{
	Scope<App> app = App::CreateApp();

	app->Run();

	return 0;
}