#include "prestopch.h"
#include "Valve.h"

namespace Presto
{

	void Valve::Activate()
	{
		m_Receiver.Receive();
		m_Transmitter.Transmit();
	}

}