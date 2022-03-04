#pragma once

#include "Presto/Core/Layer.h"

#include "Presto/Events/ApplicationEvent.h"
#include "Presto/Events/KeyEvent.h"
#include "Presto/Events/MouseEvent.h"

namespace Presto {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		void OnEvent(IEvent& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

		void SetDarkThemeColors();
	private:
		bool m_BlockEvents = true;
	};

}
