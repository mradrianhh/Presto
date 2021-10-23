#pragma once

#include "Presto/Core/Core.h"
#include "Presto/Core/IWindow.h"

namespace Presto
{

	class PRESTO_API Application
	{

	public:
		Application();
		virtual ~Application();
		void Run();

	private:
		std::unique_ptr<IWindow> m_Window;
		bool m_Running = true;
	};

	Application* CreateApplication();

}