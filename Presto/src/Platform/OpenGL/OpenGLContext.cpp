#include "prestopch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace Presto
{



	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
	{
		PRESTO_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PRESTO_CORE_ASSERT(status, "Failed to initialize Glad!");

		PRESTO_CORE_INFO("OpenGL Info:");
		PRESTO_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		PRESTO_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		PRESTO_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}