#include "prestopch.h"
#include "Application.h"
#include "Presto/Core/Window.h"
#include "Presto/Components/Controllers/PID.h"
#include "Presto/Components/Sensors/TemperatureSensor.h"
#include "Presto/Components/Actuators/Valve.h"

#include <iostream>


namespace Presto
{

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create(WindowProps()));
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent, this));
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(IEvent& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose, this));

		std::cout << e.ToString() << std::endl;

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::Run()
	{
		while (m_Running)
		{
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}
