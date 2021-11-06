#pragma once

#include "Presto/Components/Electronics/Communication/Signals/ISignal.h"

namespace Presto
{
	enum class ChannelType
	{
		INPUT,
		OUTPUT
	};

	class Channel
	{
	public:
		Channel(ChannelType channelType) : m_ChannelType(channelType), m_Signal(nullptr) {}

		void Send(ISignal* signal);
		ISignal* Read();

		inline ChannelType GetChannelType() {
			return m_ChannelType;
		}

	private:
		ISignal* m_Signal;

		ChannelType m_ChannelType;
	};

}