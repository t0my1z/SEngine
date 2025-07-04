/* simple Logger class */

#pragma once
#include "Core.h"
#include <spdlog/spdlog.h>

namespace SE 
{
    class SENGINE_API Log
    {
    public:

        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; } 
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

//Core Log Macros
#define SE_CORE_TRACE(...)   ::SE::Log::GetCoreLogger()->trace(__VA_ARGS__)  
#define SE_CORE_INFO(...)    ::SE::Log::GetCoreLogger()->info(__VA_ARGS__) 
#define SE_CORE_WARN(...)    ::SE::Log::GetCoreLogger()->warn(__VA_ARGS__) 
#define SE_CORE_ERROR(...)   ::SE::Log::GetCoreLogger()->error(__VA_ARGS__)  
#define SE_CORE_FATAL(...)   ::SE::Log::GetCoreLogger()->fatal(__VA_ARGS__)       

//Cient Log Macros 
#define SE_TRACE(...)		 ::SE::Log::GetClientLogger()->trace(__VA_ARGS__)  
#define SE_INFO(...)		 ::SE::Log::GetClientLogger()->info(__VA_ARGS__) 
#define SE_WARN(...)		 ::SE::Log::GetClientLogger()->warn(__VA_ARGS__)  
#define SE_ERROR(...)		 ::SE::Log::GetClientLogger()->error(__VA_ARGS__)   
#define SE_FATAL(...)		 ::SE::Log::GetClientLogger()->fatal(__VA_ARGS__)    