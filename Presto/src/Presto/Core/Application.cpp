#include "prestopch.h"
#include "Application.h"

namespace Presto
{

	Application::Application()
	{
		m_Window = std::unique_ptr<IWindow>(IWindow::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}

}
