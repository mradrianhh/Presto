#include "prestopch.h"
#include "Transmitter.h"

#include <iostream>

namespace Presto
{
	void Transmitter::Transmit()
	{
		std::cout << "Transmitting" << std::endl;
		while (true)
		{
			Send(m_Signal);
		}
	}

	void Transmitter::Send(ISignal* signal)
	{
		m_Channel->Send(signal);
	}

}