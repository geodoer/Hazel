/*
 * LayerStack.h 
 * \�γ�
	013. Layers
 */
#pragma once

#include "Hazel/Core/Base.h"
#include "Hazel/Core/Layer.h"

#include <vector>

namespace Hazel {

	/* 
	 *LayerStack��������Layer vector�İ�װ��
	 *vector<Layer>
		0, 1, 2, ...., size-1
		0��ջ��; size-1��ջ��
		������۾���˵��size-1����ǰ�棨���ӽ��۾�����0��ѹ�ں���
		1. ��Ⱦ˳��0, 1, 2, ..., size-1
			����Ⱦ0, ����Ⱦ1, 1����0
		2. �¼�˳��size-1, ..., 2, 1, 0
			�������¼�, �ȵ����size-1, ..., �������0
	 *
	 *ͼ�������֣�Layer��Overlay
		1. Layer��ͨ��
		2. Overlay���ǲ㣬����������Layer֮��
	 */
	class LayerStack
	{
	public:
		LayerStack() = default;
		// ����Layer������ʱ����
		~LayerStack();

		// ��ͨ�㣬��������Layer��Overlay֮ǰ
		void PushLayer(Layer* layer);
		// Overlay�Ǹ��ǲ㣬�Ḳ�������е�Layer֮�ϡ���Ϊ������ϣ�����ǲ��������Ⱦ
		// ���Overlay��������vector��ĩβ
		void PushOverlay(Layer* overlay);

		// Popֻ���Ƴ�Layer,������delete. ��Ϊlayer����Ȩ�������,LayerStack��������
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		// begin -> end, ջ�� -> ջ��
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		// begin <- end, ջ�� <- ջ��
		std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

		// begin -> end, ջ�� -> ջ��
		std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
		std::vector<Layer*>::const_iterator end()	const { return m_Layers.end(); }
		// begin <- end, ջ�� <- ջ��
		std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }
	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0; // ��ͨ��ĸ���(��ͳ��Overlay)
	};

}
