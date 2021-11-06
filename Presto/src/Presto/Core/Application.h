#pragma once

#include "Presto/Core/Core.h"
#include "Presto/Core/Window.h"
#include "Presto/Events/IEvent.h"
#include "Presto/Events/ApplicationEvent.h"
#include "Presto/Core/LayerStack.h"

namespace Presto
{

	class PRESTO_API Application
	{

	public:
		Application();
		virtual ~Application();
		void Run();

		void OnEvent(IEvent& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
	};

	Application* CreateApplication();

}