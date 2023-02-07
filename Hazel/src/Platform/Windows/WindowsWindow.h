/*
 * WindowsWindow.h Windows平台的窗口类
 * \课程
	011. Window抽象和GLFW
	012. 窗口事件
 */
#pragma once

#include "Hazel/Core/Window.h"
#include "Hazel/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Hazel {

	//Windows平台的窗口类
	class WindowsWindow : public Window
	{ 
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		//更新GLFW，而缓冲区会轮询输入事件，一帧运行一次
		void OnUpdate() override;

		unsigned int GetWidth() const override { return m_Data.Width; }
		unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		//设置Event触发的回调函数
		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		Scope<GraphicsContext> m_Context;

		//Window相关属性
		// 在GLFW中无法查询到这些信息，因此需要提供一个缓存，方便外部查询
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;	//事件触发的回调函数
		};
		WindowData m_Data;
	};

}
