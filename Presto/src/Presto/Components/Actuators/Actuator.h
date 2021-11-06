#pragma once

#include "Presto/Components/IComponent.h"
#include "Presto/Components/Electronics/Components/Receiver.h"
#include "Presto/Components/Electronics/Components/Transmitter.h"

#include <string>

namespace Presto
{

	enum class ActuatorType
	{
		VALVE
	};

#define ACTUATOR_CLASS_TYPE(type) static ActuatorType GetStaticActuatorType() { return type; }\
								virtual ActuatorType GetActuatorType() const override { return GetStaticActuatorType(); }\

	class Actuator : public IComponent
	{
	public:
		Actuator(std::string identifier) : IComponent(identifier) {}

		virtual ~Actuator() = default;

		virtual ActuatorType GetActuatorType() const = 0;

		virtual void Activate() = 0;

		inline void ConfigureTransmitter(Channel* channel)
		{
			m_Transmitter.SetChannel(channel);
		}

		COMPONENT_CLASS_TYPE(ComponentType::ACTUATOR)
	protected:
		Transmitter m_Transmitter;
		Receiver m_Receiver;
	};

}