#pragma once

#ifdef PRESTO_PLATFORM_WINDOWS

extern Presto::Application* Presto::CreateApplication();

int main(int argc, char** argv)
{
	Presto::Log::Init();
	PRESTO_CORE_WARN("Presto!!");
	Presto::Application* app = Presto::CreateApplication();
	app->Run();
	delete app;
}

#endif