#include "prestopch.h"
#include "Application.h"

#include "Presto/Core/Window.h"
#include "Presto/Core/Log.h"

#include "Presto/Components/Controllers/PID.h"
#include "Presto/Components/Sensors/TemperatureSensor.h"
#include "Presto/Components/Actuators/Valve.h"
#include "Presto/Components/ComponentFactory.h"

#include "Presto/Renderer/Renderer.h"

#include <iostream>

#include <GLFW/glfw3.h>


namespace Presto
{

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		PRESTO_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		
		m_Window = std::unique_ptr<Window>(Window::Create(WindowProps()));
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent, this));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		ComponentFactory::Instance()->AddPrototype<Valve>();
		IComponent* valve = ComponentFactory::Instance()->CreateComponent<Valve>("V_01");
		std::cout << valve->GetIdentifier() << std::endl;
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(IEvent& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose, this));

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
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::Run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

			m_ImGuiLayer->Begin();
			{
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}
