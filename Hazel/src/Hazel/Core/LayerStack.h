/*
 * LayerStack.h 
 * \课程
	013. Layers
 */
#pragma once

#include "Hazel/Core/Base.h"
#include "Hazel/Core/Layer.h"

#include <vector>

namespace Hazel {

	/* 
	 *LayerStack本质上是Layer vector的包装器
	 *vector<Layer>
		0, 1, 2, ...., size-1
		0是栈底; size-1是栈顶
		相对于眼睛来说，size-1更在前面（更接近眼睛），0被压在后面
		1. 渲染顺序：0, 1, 2, ..., size-1
			先渲染0, 再渲染1, 1覆盖0
		2. 事件顺序：size-1, ..., 2, 1, 0
			例如点击事件, 先点击到size-1, ..., 最后点击到0
	 *
	 *图层有两种：Layer与Overlay
		1. Layer普通层
		2. Overlay覆盖层，覆盖在所有Layer之上
	 */
	class LayerStack
	{
	public:
		LayerStack() = default;
		// 所有Layer在析构时回收
		~LayerStack();

		// 普通层，放在现有Layer后，Overlay之前
		void PushLayer(Layer* layer);
		// Overlay是覆盖层，会覆盖在所有的Layer之上。因为我们总希望覆盖层是最后渲染
		// 因此Overlay将被放在vector的末尾
		void PushOverlay(Layer* overlay);

		// Pop只会移除Layer,但不会delete. 因为layer所有权归调用者,LayerStack不做处理
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		// begin -> end, 栈底 -> 栈顶
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		// begin <- end, 栈底 <- 栈顶
		std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

		// begin -> end, 栈底 -> 栈顶
		std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
		std::vector<Layer*>::const_iterator end()	const { return m_Layers.end(); }
		// begin <- end, 栈底 <- 栈顶
		std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }
	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0; // 普通层的个数(不统计Overlay)
	};

}
