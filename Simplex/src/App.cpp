
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
	Scope<App> app = App::GetApp();

	app->Start();
	app->Update();

	return 0;
}