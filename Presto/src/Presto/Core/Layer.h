#pragma once

#include "Presto/Core/Core.h"
#include "Presto/Core/Timestep.h"
#include "Presto/Events/IEvent.h"

namespace Presto
{

	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep timestep) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(IEvent& event) {}

		inline const std::string& GetName() const
		{
			return m_DebugName;
		}
	protected:
		std::string m_DebugName;
	};

}