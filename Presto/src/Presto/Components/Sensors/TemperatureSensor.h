#pragma once

#include "Presto/Components/Sensors/Sensor.h"
#include "Presto/Components/Electronics/Communication/Signals/TTSignal.h"

#include <string>

namespace Presto
{

	class TemperatureSensor : public Sensor
	{
	public:
		TemperatureSensor(std::string identifier) : Sensor(identifier), m_Reading(0)
		{
			m_Signal = new TTSignal(m_Reading);
			m_Transmitter.SetSignal(m_Signal);
		}

		void Activate();

		SENSOR_CLASS_TYPE(SensorType::TEMPERATURE_SENSOR)
	private:
		TTSignal* m_Signal;
		float* m_Reading;
	};

}