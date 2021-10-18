#include <Presto.h>

class Application : public Presto::Application
{
public:
	Application()
	{

	}

	~Application()
	{

	}
};

Presto::Application* Presto::CreateApplication()
{
	return new Application();
}