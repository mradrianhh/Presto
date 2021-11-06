#pragma once

#include "Presto/Components/IComponent.h"

#include <string>

namespace Presto
{

	enum class ControllerType
	{
		PID,
		ECU
	};

#define CONTROLLER_CLASS_TYPE(type) static ControllerType GetStaticControllerType() { return type; }\
								virtual ControllerType GetControllerType() const override { return GetStaticControllerType(); }\

	class Controller : public IComponent
	{
	public:
		Controller(std::string identifier) : IComponent(identifier) {}
		virtual ~Controller() = default;

		// OnUpdate(): Process all signals
		virtual void Process() = 0;

		virtual ControllerType GetControllerType() const = 0;

		COMPONENT_CLASS_TYPE(ComponentType::CONTROLLER)
	};

}