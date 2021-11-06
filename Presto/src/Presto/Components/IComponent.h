#pragma once

#include <string>

namespace Presto
{

	enum class ComponentType
	{
		ACTUATOR,
		SENSOR,
		CONTAINER,
		CONTROLLER,
		TRANSMITTER,
		RECEIVER
	};

#define COMPONENT_CLASS_TYPE(type) static ComponentType GetStaticComponentType() {return type; }\
								virtual ComponentType GetComponentType() const override { return GetStaticComponentType(); }\
								virtual const char* GetName() const override { return #type; }

	class IComponent
	{
	public:
		IComponent(std::string identifier) : m_Identifier(identifier) {};
		virtual ~IComponent() = default;

		virtual ComponentType GetComponentType() const = 0;
		virtual const char* GetName() const = 0;

		inline std::string GetIdentifier()
		{
			return m_Identifier;
		}
	private:
		std::string m_Identifier;
	};

}