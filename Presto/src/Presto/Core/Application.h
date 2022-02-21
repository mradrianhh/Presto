#pragma once

#include "Presto/Core/Core.h"
#include "Presto/Core/Window.h"
#include "Presto/Events/IEvent.h"
#include "Presto/Events/ApplicationEvent.h"
#include "Presto/Core/LayerStack.h"
#include "Presto/ImGui/ImGuiLayer.h"

#include <memory>

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

		inline Window& GetWindow() { return *m_Window; }

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;

		static Application* s_Instance;
	};

	// Defined in CLIENT(prestissimo).
	Application* CreateApplication();

}