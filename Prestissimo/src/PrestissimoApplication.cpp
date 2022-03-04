#include <Presto.h>
#include "Presto/Core/EntryPoint.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

	class PrestissimoApplication : public Presto::Application
	{
	public:
		PrestissimoApplication()
		{
			PushLayer(new Sandbox2D());
		}

		~PrestissimoApplication()
		{

		}
	};

	Presto::Application* Presto::CreateApplication()
	{
		return new PrestissimoApplication();
	}
