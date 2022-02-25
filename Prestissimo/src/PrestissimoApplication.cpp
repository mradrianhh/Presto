#include <Presto.h>
#include <Presto/Core/EntryPoint.h>

#include "imgui/imgui.h"

namespace Presto
{

	class ExampleLayer : public Layer
	{
	public:
		ExampleLayer()
			: Layer("Example")
		{
		}

		void OnUpdate() override
		{
			if (Input::IsKeyPressed(PRESTO_KEY_TAB))
				PRESTO_TRACE("Tab key is pressed (poll)!");
		}

		virtual void OnImGuiRender() override
		{
			ImGui::Begin("Test");
			ImGui::Text("Hello World");
			ImGui::End();
		}

		void OnEvent(IEvent& event) override
		{
			if (event.GetEventType() == EventType::KeyPressed)
			{
				KeyPressedEvent& e = (KeyPressedEvent&)event;
				if (e.GetKeyCode() == PRESTO_KEY_TAB)
					PRESTO_TRACE("Tab key is pressed (event)!");
				PRESTO_TRACE("{0}", (char)e.GetKeyCode());
			}
		}

	};

	class PrestissimoApplication : public Application
	{
	public:
		PrestissimoApplication()
		{
			PushLayer(new ExampleLayer());
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
