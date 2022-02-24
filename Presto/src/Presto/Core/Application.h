#pragma once

#include "Presto/Core/Core.h"
#include "Presto/Core/Window.h"
#include "Presto/Events/IEvent.h"
#include "Presto/Events/ApplicationEvent.h"
#include "Presto/Core/LayerStack.h"
#include "Presto/ImGui/ImGuiLayer.h"

#include "Presto/Renderer/Shader.h"
#include "Presto/Renderer/Buffer.h"

#include <memory>

namespace Presto
{

	class Application
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

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	// Defined in CLIENT(prestissimo).
	Application* CreateApplication();

}