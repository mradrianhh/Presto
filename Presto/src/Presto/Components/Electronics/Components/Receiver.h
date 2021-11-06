#pragma once

#include "Presto/Components/Electronics/Communication/Channel.h"

namespace Presto
{

	class Receiver
	{
	public:
		Receiver(Channel* channel = nullptr) : m_Channel(channel) {}

		void Receive();

		inline void SetChannel(Channel* channel)
		{
			m_Channel = channel;
		}

		inline ISignal* GetSignal()
		{
			return m_Signal;
		}

	private:
		Channel* m_Channel;
		ISignal* Read();
		ISignal* m_Signal = nullptr;
	};

}