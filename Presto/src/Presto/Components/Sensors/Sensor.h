#pragma once

#include "Presto/Components/IComponent.h"
#include "Presto/Components/Electronics/Components/Transmitter.h"
#include "Presto/Components/Electronics/Communication/Channel.h"

#include <string>

namespace Presto
{

	enum class SensorType
	{
		TEMPERATURE_SENSOR,
		PRESSURE_SENSOR
	};

#define SENSOR_CLASS_TYPE(type) static SensorType GetStaticSensorType() { return type; }\
								virtual SensorType GetSensorType() const override { return GetStaticSensorType(); }\

	class Sensor : public IComponent
	{
	public:
		Sensor(std::string identifier) : IComponent(identifier) {}

		virtual ~Sensor() = default;

		virtual SensorType GetSensorType() const = 0;

		// Start two threads in paralell
		// Thread 1: Read sensor-reading, update m_Signal
		// Thread 2: Transmit m_Signal.
		virtual void Activate() = 0;

		inline void ConfigureTransmitter(Channel* channel)
		{
			m_Transmitter.SetChannel(channel);
		};

		COMPONENT_CLASS_TYPE(ComponentType::SENSOR)
	protected:
		Transmitter m_Transmitter;
	};

}