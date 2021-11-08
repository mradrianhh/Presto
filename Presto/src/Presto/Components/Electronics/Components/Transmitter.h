#pragma once

#include "Presto/Components/IComponent.h"
#include "Presto/Components/Electronics/Communication/Channel.h"
#include "Presto/Components/Electronics/Communication/Signals/ISignal.h"

#include <string>

namespace Presto
{

	class Transmitter
	{
	public:
		Transmitter(ISignal* signal = nullptr, Channel* channel = nullptr) : m_Channel(channel), m_Signal(signal){}

		void Transmit();

		inline void SetChannel(Channel* channel)
		{
			m_Channel = channel;
		}

		inline void SetSignal(ISignal* signal)
		{
			m_Signal = signal;
		}

	private:
		Channel* m_Channel;
		ISignal* m_Signal;

		void Send(ISignal* signal);
	};

}