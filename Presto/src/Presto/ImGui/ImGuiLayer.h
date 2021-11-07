#pragma once

#include "Presto/Core/Layer.h"
#include "Presto/Events/IEvent.h"


namespace Presto
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(IEvent& event);
	private:

	};

}
