#pragma once

#include "Application.h"

#ifdef PRESTO_PLATFORM_WINDOWS

extern Presto::Application* Presto::CreateApplication();

int main(int argc, char** argv)
{
	Presto::Log::Init();

	PRESTO_PROFILE_BEGIN_SESSION("Startup", "PrestoProfile-Startup.json");
	Presto::Application* app = Presto::CreateApplication();
	PRESTO_PROFILE_END_SESSION();

	PRESTO_PROFILE_BEGIN_SESSION("Runtime", "PrestoProfile-Runtime.json");
	app->Run();
	PRESTO_PROFILE_END_SESSION();

	PRESTO_PROFILE_BEGIN_SESSION("Shutdown", "PrestoProfile-Shutdown.json");
	delete app;
	PRESTO_PROFILE_END_SESSION();
}

#endif