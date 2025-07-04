#pragma once

#include <memory>

//When we build the dll from TEngine, the macro will export, and when we use it in another project, it'll import
//Irrelevant, since we now build as a static library, instead of a dynamic one.
#ifdef SE_PLATFORM_WINDOWS 
	#if SE_DYNAMIC_LINK
		#ifdef SE_BUILD_DLL
			#define SENGINE_API __declspec(dllexport) 
		#else
			#define SENGINE_API __declspec(dllimport) 
		#endif
#else
	#define SENGINE_API 
#endif
#else
	#error SEngine only supports windows
#endif 

#ifdef SE_DEBUG
#define SE_ENABLE_ASSERTS
#endif

#ifdef SE_ENABLE_ASSERTS
#define SE_ASSERT(x, ...) { if(!(x)) { SE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }  
#define SE_CORE_ASSERT(x, ...) { if(!(x)) { SE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }  
#else
#define SE_ASSERT(x, ...) 
#define SE_CORE_ASSERT(x, ...) 
#endif

#define BIT(x) (1 << x) 

#define SE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace SE
{
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