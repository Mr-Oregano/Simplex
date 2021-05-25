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
	void Start() override;
	void Update() override;
	void Shutdown() override;

private:
	Scope<Window> m_Window;
	bool m_Running;

};