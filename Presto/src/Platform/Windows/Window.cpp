#include "prestopch.h"
#include "Window.h"

namespace Presto
{
	
	static bool s_GLFWInitialized = false;

	Window::Window(const WindowProps& props)
	{
		Init(props);
	}

	Window::~Window()
	{
		Shutdown();
	}

	IWindow* IWindow::Create(const WindowProps& props)
	{
		return new Window(props);
	}

	void Window::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		if (!s_GLFWInitialized)
		{
			glfwInit();
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void Window::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void Window::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool Window::IsVSync() const
	{
		return m_Data.VSync;
	}

}
