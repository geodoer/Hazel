/*
 * Layer.h 抽象的图层类
 * \课程
	013. Layers 
 */
#pragma once

#include "Hazel/Core/Base.h"
#include "Hazel/Core/Timestep.h"
#include "Hazel/Events/Event.h"

namespace Hazel {

	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		//当Layer被Push到LayerStack时调用
		virtual void OnAttach() {}
		//当Layer从LayerStack Pop出去时调用
		virtual void OnDetach() {}
		//当Layer更新时调用，一帧一次
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		//事件触发时调用
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName; //图层名，方便调试
	};

}
