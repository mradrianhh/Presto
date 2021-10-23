#pragma once
#include "prestopch.h"

#include "Presto/Core/Core.h"
#include "Presto/Events/IEvent.h"

namespace Presto
{

	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "Presto Engine", uint32_t width = 1600, uint32_t height = 900) : Title(title), Width(width), Height(height) {}
	};

	class PRESTO_API IWindow
	{
	public:
		using EventCallbackFn = std::function<void(IEvent&)>;

		virtual ~IWindow() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static IWindow* Create(const WindowProps& props = WindowProps());
	};

}

