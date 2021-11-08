#pragma once

#include "Presto/Components/IComponent.h"

#include <string>

namespace Presto
{

	class Controller : public IComponent
	{
	public:
		Controller(std::string identifier) : IComponent(identifier) {}
		virtual ~Controller() = default;

		// OnUpdate(): Process all signals
		virtual void Process() = 0;

	};

}