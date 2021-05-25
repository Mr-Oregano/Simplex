
// Precompiled
#include <sxpch.h>
//

#include <App.h>

#include <Log.h>

App::App()
{
	InitServices();
}

App::~App()
{
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

	app->Start();
	app->Update();
	app->Shutdown();

	return 0;
}