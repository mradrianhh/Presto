#pragma once

#include "Presto/Components/Controllers/Controller.h"
#include "Presto/Components/Electronics/Communication/Channel.h"
#include "Presto/Components/IComponent.h"
#include "Presto/Components/Sensors/Sensor.h"
#include "Presto/Components/Actuators/Actuator.h"

#include <map>
#include <string>
#include <functional>

/*
	Implement regulation-loops using builder-pattern.
*/

namespace Presto
{

	struct Input
	{
	public:
		Input(Channel* channel, Sensor* sensor)
		{
			SetChannel(channel);
			SetSensor(sensor);
		}

		inline void SetChannel(Channel* channel) 
		{
			m_Channel = channel;
		}

		inline Channel* GetChannel()
		{
			return m_Channel;
		}

		inline void SetSensor(Sensor* sensor)
		{
			if (sensor != nullptr)
			{
				sensor->ConfigureTransmitter(m_Channel);
				m_Sensor = sensor;
			}
			else
				m_Sensor = sensor;
		}

		inline Sensor* GetSensor()
		{
			return m_Sensor;
		}

	private:
		Channel* m_Channel;
		Sensor* m_Sensor;
	};

	struct Output
	{
	public:
		Output(Channel* channel, Actuator* actuator)
		{
			SetChannel(channel);
			SetActuator(actuator);
		}
		
		inline void SetChannel(Channel* channel)
		{
			m_Channel = channel;
		}

		inline Channel* GetChannel()
		{
			return m_Channel;
		}

		inline void SetActuator(Actuator* actuator)
		{
			if (actuator != nullptr)
			{
				actuator->ConfigureTransmitter(m_Channel);
				m_Actuator = actuator;
			}
			else
				m_Actuator = actuator;
		}

		inline Actuator* GetActuator()
		{
			return m_Actuator;
		}

	private:
		Channel* m_Channel;
		Actuator* m_Actuator;
	};

	class PID : public Controller
	{
	public:
		PID(std::string identifier) : Controller(identifier) {}

		void ConfigureIOLayout(int numInput, int numOutput);

		void ConnectSensor(Sensor* sensor, int IN_PIN);
		void ConnectSensor(Sensor* sensor);

		void ConnectActuator(Actuator* actuator, int OUT_PIN);
		void ConnectActuator(Actuator* actuator);

		void Regulate();

		inline void SetSetRegulation(std::function<void()> SetRegulation)
		{
			m_SetRegulation = SetRegulation;
		}

		COMPONENT_CLASS_TYPE(ComponentType::PID)

	private:
		std::map<int, Input*> m_Inputs;
		std::map<int, Output*> m_Outputs;
		std::map<std::string, std::pair<ChannelType, int>> m_PIN_MAP;

		std::function<void()> m_SetRegulation;

		void AddInput(IComponent* component = nullptr);
		void AddOutput(IComponent* component = nullptr);
	};

}