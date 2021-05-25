#pragma once

#include <App.h>
#include <Ref.h>
#include <Window.h>

class SandboxApp : public App
{
public:
	SandboxApp();
	~SandboxApp();

private:
	void Run() override;

	void OnEvent(Event &e);

private:
	Scope<Window> m_Window;
	bool m_Running;

};