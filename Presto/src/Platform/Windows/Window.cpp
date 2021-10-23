#include "prestopch.h"
#include "Window.h"

namespace Presto
{

	Window::Window(const WindowProps& props)
	{

	}

	Window::~Window()
	{

	}

	void Window::Init(const WindowProps& props)
	{

	}

	void Window::Shutdown()
	{

	}

	void Window::OnUpdate()
	{

	}

	void Window::SetVSync(bool enabled)
	{
		m_Data.VSync = enabled;
	}

	bool Window::IsVSync() const
	{
		return m_Data.VSync;
	}

}
