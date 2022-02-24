#pragma once

#include "Application.h"

#ifdef PRESTO_PLATFORM_WINDOWS

extern Presto::Application* Presto::CreateApplication();

int main(int argc, char** argv)
{
	Presto::Log::Init();
	Presto::Application* app = Presto::CreateApplication();
	app->Run();
	delete app;
}

#endif