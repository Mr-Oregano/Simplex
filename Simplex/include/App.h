#pragma once

#include <Ref.h>
#include <Window.h>

struct AppProps
{
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

public:
	static Scope<App> CreateApp();

protected:
	Scope<Window> m_Window;
	Scope<ImGuiBackend> m_Gui;
	bool m_Running = false;

};

int main();