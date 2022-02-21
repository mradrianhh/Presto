#include <Presto.h>
#include <Presto/Core/EntryPoint.h>
#include "DemoLayer.h"

namespace Presto
{

	class PrestissimoApplication : public Application
	{
	public:
		PrestissimoApplication()
		{
			PushLayer(new DemoLayer());
		}

		~PrestissimoApplication()
		{

		}
	};

	Application* CreateApplication()
	{
		return new PrestissimoApplication();
	}

}
