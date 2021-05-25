#pragma once

#include <Ref.h>

class App
{

friend int main();

public:
	App();
	virtual ~App();

protected:
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Shutdown() = 0;

private:
	void InitServices();
	void ShutdownServices();

public:
	static Scope<App> CreateApp();
};

int main();