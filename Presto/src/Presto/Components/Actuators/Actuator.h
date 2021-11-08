#pragma once

#include "Presto/Components/IComponent.h"
#include "Presto/Components/Electronics/Components/Receiver.h"
#include "Presto/Components/Electronics/Components/Transmitter.h"

#include <string>

namespace Presto
{

	class Actuator : public IComponent
	{
	public:
		Actuator(std::string identifier) : IComponent(identifier) {}

		virtual ~Actuator() = default;

		virtual void Activate() = 0;

		inline void ConfigureTransmitter(Channel* channel)
		{
			m_Transmitter.SetChannel(channel);
		}

	protected:
		Transmitter m_Transmitter;
		Receiver m_Receiver;
	};

}