#pragma once

#include <App.h>

class SandboxApp : public App
{
public:
	SandboxApp();
	~SandboxApp();

private:
	void Start() override;
	void Update() override;

private:
	bool m_Running;
};