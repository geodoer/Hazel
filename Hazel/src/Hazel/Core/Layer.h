/*
 * Layer.h �����ͼ����
 * \�γ�
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

		//��Layer��Push��LayerStackʱ����
		virtual void OnAttach() {}
		//��Layer��LayerStack Pop��ȥʱ����
		virtual void OnDetach() {}
		//��Layer����ʱ���ã�һ֡һ��
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		//�¼�����ʱ����
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName; //ͼ�������������
	};

}
