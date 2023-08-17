#pragma once

#include <Ref.h>
#include <Window.h>

#define MAKE_APP_VERSION(major, minor) ((major << (sizeof(int) / 2)) | (minor & 0xffff))

struct AppProps
{
	const char *name = "Untitled";
	int version = MAKE_APP_VERSION(1, 0);
	WindowProps windowProps;
};

class App
{
friend int main();

public:
	App(const AppProps &props = {});
	virtual ~App();

protected:
	virtual void OnStart() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnStop() = 0;
	virtual void OnImGui() {}

private:
	void Run();

protected:
	Scope<Window> m_Window;
	Scope<ImGuiBackend> m_Gui;
	bool m_Running = false;

};

int main();