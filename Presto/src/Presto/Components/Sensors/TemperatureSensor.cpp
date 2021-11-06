#include "prestopch.h"
#include "TemperatureSensor.h"

namespace Presto
{

	void TemperatureSensor::Activate()
	{
		m_Transmitter.Transmit();
	}

}