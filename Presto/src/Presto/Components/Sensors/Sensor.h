#pragma once

#include "Presto/Components/IComponent.h"
#include "Presto/Components/Electronics/Components/Transmitter.h"
#include "Presto/Components/Electronics/Communication/Channel.h"

#include <string>

namespace Presto
{

	class Sensor : public IComponent
	{
	public:
		Sensor(std::string identifier) : IComponent(identifier) {}

		virtual ~Sensor() = default;

		// Start two threads in paralell
		// Thread 1: Read sensor-reading, update m_Signal
		// Thread 2: Transmit m_Signal.
		virtual void Activate() = 0;

		inline void ConfigureTransmitter(Channel* channel)
		{
			m_Transmitter.SetChannel(channel);
		};

	protected:
		Transmitter m_Transmitter;
	};

}