#pragma once

#include <string>

namespace Presto
{

	enum class ComponentType
	{
		VALVE,
		PID,
		TEMPERATURE_SENSOR
	};

#define COMPONENT_CLASS_TYPE(type) static ComponentType GetStaticType() {return type; }\
								virtual ComponentType GetComponentType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

	class IComponent
	{
	public:
		IComponent(std::string identifier) : m_Identifier(identifier) {};
		virtual ~IComponent() = default;

		virtual ComponentType GetComponentType() const = 0;
		virtual const char* GetName() const { return m_Name.c_str(); }

		inline std::string GetIdentifier()
		{
			return m_Identifier;
		}
	private:
		std::string m_Name;
		std::string m_Identifier;
	};

}