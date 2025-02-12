#pragma once

#include "Hazel/Core/PlatformDetection.h"

#include <memory>

#ifdef HZ_DEBUG
	#if defined(HZ_PLATFORM_WINDOWS)
		#define HZ_DEBUGBREAK() __debugbreak()
	#elif defined(HZ_PLATFORM_LINUX)
		#include <signal.h>
		#define HZ_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define HZ_ENABLE_ASSERTS
#else
	#define HZ_DEBUGBREAK()
#endif

#define HZ_EXPAND_MACRO(x) x
#define HZ_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

//将成员函数转成std::function
#define HZ_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
//#define HZ_BIND_EVENT_FN(fn) std::bind(&x, this, std::placeholders::_1)

namespace Hazel {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}

#include "Hazel/Core/Log.h"
#include "Hazel/Core/Assert.h"
