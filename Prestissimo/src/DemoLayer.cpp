#include "DemoLayer.h"
#include "imgui/imgui.h"

namespace Presto
{

	DemoLayer::DemoLayer() {}

	void DemoLayer::OnImGuiRender()
	{
		ImGui::ShowDemoWindow();
	}

}