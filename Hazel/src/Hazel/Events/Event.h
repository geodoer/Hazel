/*
 * Event.h 事件系统的主文件 
 * \课程
	009. 实现事件系统
 */
#pragma once

#include "Hazel/Debug/Instrumentor.h"
#include "Hazel/Core/Base.h"

#include <functional>

namespace Hazel {

	// Events in Hazel are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

	//在Hazel，Events是阻塞事件，它没有被缓冲，没有被延迟
	//事件一旦发生（比如鼠标点击），整个应用就会停止，然后处理这个事件
	//这与非阻塞的不同：将事件推送到某个队列或某个缓冲区中，应用不阻塞，事件依次执行

	//事件类型
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	//事件分类
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication    = BIT(0),
		EventCategoryInput          = BIT(1),	//输入类事件（包含键盘、鼠标、鼠标按钮等）
		EventCategoryKeyboard       = BIT(2),	//键盘类事件
		EventCategoryMouse          = BIT(3),	//鼠标类事件
		EventCategoryMouseButton    = BIT(4)	//鼠标按钮
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	//事件基类
	class Event
	{
	public:
		virtual ~Event() = default;

		//事件是否被处理
		// 在处理的过程中，如果不想事件被继续传递，可以置为True，后面的事件就不会处理了
		bool Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};

	//事件调度器
	// 基于事件类型调度事件的方法
	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}
		
		// F will be deduced by the compiler
		//  F是一个用于处理事件的匿名方法，函数签名为bool(Event的子类)
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			//事件类型 与 T的类型 匹配
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				//调用F对事件进行处理
				//如果返回true，则表示处理完成
				m_Event.Handled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	//添加一个<<方法，日志系统会调用此函数进行输出
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}

