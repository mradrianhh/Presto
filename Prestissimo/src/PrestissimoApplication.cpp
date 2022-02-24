#include <Presto.h>
#include <Presto/Core/EntryPoint.h>

namespace Presto
{

	class PrestissimoApplication : public Application
	{
	public:
		PrestissimoApplication()
		{
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
