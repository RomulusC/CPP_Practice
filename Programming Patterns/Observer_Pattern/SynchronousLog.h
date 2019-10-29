#pragma once
#include <iostream>
#include <cstdarg>
#include <mutex>
#include <chrono>
namespace customLog
{
	class SyncOut
	{
	private:
		std::mutex m_mutex;

	public:
		SyncOut() {}

		template<typename ...args>
		void t_trace(args... next)
		{			
			std::lock_guard<std::mutex> lck(m_mutex);
			struct tm timeInfo;
			auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			localtime_s(&timeInfo, &now);
			std::cout << "[" << timeInfo.tm_hour << ":" << timeInfo.tm_min << ":" << timeInfo.tm_sec << "] - ";
			print(next...);			
		}

		template<typename ...args>
		void trace(args... next )
		{			
			std::lock_guard<std::mutex> lck(m_mutex);			
			print(next...);		
		}

		template<typename T, typename ...args>
		void print(T  current, args... next)
		{
			std::cout << current;
			print(next...);
		}

		template<typename T>
		void print(T current)
		{
			std::cout << current;
		}
	};
	SyncOut sync_out;
	
}
//Log Macros
#define C_TRACE(...) customLog::sync_out.trace(__VA_ARGS__) 
#define T_TRACE(...) customLog::sync_out.t_trace(__VA_ARGS__) 

