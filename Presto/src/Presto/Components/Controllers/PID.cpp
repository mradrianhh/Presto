#include "prestopch.h"
#include "PID.h"

namespace Presto
{
	void PID::Process()
	{
		// Process all signals.
	}
	void PID::ConfigureIOLayout(int numInput, int numOutput)
	{
		while (m_Inputs.size() != numInput) 
		{
			AddInput();
		}

		while (m_Outputs.size() != numOutput)
		{
			AddOutput();
		}
	}

	void PID::ConnectSensor(Sensor* sensor, int IN_PIN)
	{
		m_Inputs[IN_PIN]->SetSensor(sensor);
		m_PIN_MAP[sensor->GetIdentifier()] = std::make_pair(ChannelType::INPUT, IN_PIN);
		sensor->Activate();
	}

	void PID::ConnectSensor(Sensor* sensor)
	{
		for (auto pair : m_Inputs)
		{
			if (pair.second->GetSensor() == nullptr)
			{
				pair.second->SetSensor(sensor);
				m_PIN_MAP[sensor->GetIdentifier()] = std::make_pair(ChannelType::INPUT, pair.first);
				sensor->Activate();
			}
		}
	}

	void PID::ConnectActuator(Actuator* actuator, int OUT_PIN)
	{
		m_Outputs[OUT_PIN]->SetActuator(actuator);
		m_PIN_MAP[actuator->GetIdentifier()] = std::make_pair(ChannelType::OUTPUT, OUT_PIN);
		actuator->Activate();
	}

	void PID::ConnectActuator(Actuator* actuator)
	{
		for (auto pair : m_Outputs)
			if (pair.second->GetActuator() == nullptr)
			{
				pair.second->SetActuator(actuator);
				m_PIN_MAP[actuator->GetIdentifier()] = std::make_pair(ChannelType::OUTPUT, pair.first);
				actuator->Activate();
			}
	}

	void PID::AddInput(IComponent* component)
	{
		static int I_PIN_ID = 1;
		m_Inputs[I_PIN_ID] = new Input(new Channel(ChannelType::INPUT), (Sensor*)component);
		I_PIN_ID++;
	}

	void PID::AddOutput(IComponent* component)
	{
		static int O_PIN_ID = 1;
		m_Outputs[O_PIN_ID] = new Output(new Channel(ChannelType::OUTPUT), (Actuator*)component);
		O_PIN_ID++;
	}

}