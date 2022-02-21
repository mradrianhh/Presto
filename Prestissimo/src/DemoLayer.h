#pragma once

#include "Presto.h"

namespace Presto
{

	class DemoLayer : public Layer
	{
	public:
		DemoLayer();
		virtual ~DemoLayer() = default;

		virtual void OnImGuiRender() override;

	};

}

