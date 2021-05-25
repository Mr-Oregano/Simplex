#pragma once

#include <Ref.h>

class App
{
friend int main();

public:
	App();
	virtual ~App();

protected:
	virtual void Run() = 0;

private:
	void InitServices();
	void ShutdownServices();

public:
	static Scope<App> CreateApp();
};

int main();