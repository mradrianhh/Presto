#pragma once

#include "Presto/Components/IComponent.h"

namespace Presto
{

	enum class ContainerType
	{
		TANK
	};


#define CONTAINER_CLASS_TYPE(type) static ContainerType GetStaticContainerType() { return type; }\
								virtual ContainerType GetContainerType() const override { return GetStaticContainerType(); }\
								virtual const char* GetName() const override {return }

	class Container : public IComponent
	{
	public:
		virtual ~Container() = default;

		virtual ContainerType GetContainerType() const = 0;
		virtual const char* GetName() const = 0;

		COMPONENT_CLASS_TYPE(ComponentType::CONTAINER)
	};

}