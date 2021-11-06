#pragma once

#include "Presto/Components/Actuators/Actuator.h"

namespace Presto
{
	class Valve : public Actuator
	{
	public:
		Valve(std::string identifier, float FlowRate) : Actuator(identifier), m_Position(0), m_FlowRate(FlowRate)
		{ }

		virtual ~Valve() = default;

		void Activate();

		inline float GetPosition()
		{
			return m_Position;
		}
		inline void SetPosition(float Position)
		{
			m_Position = Position;
		}

		inline float GetFlowRate()
		{
			return m_FlowRate;
		}
		inline void SetFlowRate(float FlowRate)
		{
			m_FlowRate = FlowRate;
		}

		ACTUATOR_CLASS_TYPE(ActuatorType::VALVE)
	private:
		float m_Position;
		float m_FlowRate;
	};
}