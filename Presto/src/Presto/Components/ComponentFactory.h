#pragma once

#include "Presto/Core/Core.h"
#include "Presto/Components/IComponent.h"

#include <map>
#include <string>

namespace Presto
{

	class PRESTO_API ComponentFactory
	{
	public:
		template<typename T>
		void AddPrototype() 
		{
			if (!m_Prototype[T::GetStaticType()])
				m_Prototype[T::GetStaticType()] = [](std::string identifier) { return new T(identifier); };
		}

		template<typename T>
		IComponent* CreateComponent(std::string identifier)
		{
			if (m_Prototype[T::GetStaticType()])
				return m_Prototype[T::GetStaticType()](identifier);
		}

		inline static ComponentFactory* Instance()
		{
			static ComponentFactory* s_Instance;
			if (!s_Instance)
				s_Instance = new ComponentFactory();

			return s_Instance;
		}
	private:
		std::map<ComponentType, std::function<IComponent*(std::string)>> m_Prototype;
	};

}

