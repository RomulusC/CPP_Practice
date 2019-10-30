/*
********************************************
Rommulluss Caraiman------------------------*
19/10/2019---------------------------------*
Project: SynchronousLog.h------------------*
File: main.cpp-----------------------------*
********************************************
*/
//The SyncOut class is a singleton that synchronizes the std::cout function, with the choice to add a log like time printing with T_TRACE and regular cout with C_TRACE

#pragma once
#include <iostream>
#include <mutex>
#include <chrono>
namespace customLog
{
	class SyncOut
	{
	private:
		std::mutex m_mutex;
		SyncOut() {}
	public:
//Singleton functions:
		SyncOut(SyncOut const&) = delete;
		void operator=(SyncOut const&) = delete;
		~SyncOut() {}

		static SyncOut& instance()
		{
			static SyncOut* s_Instance = new SyncOut();
			return *s_Instance;
		}
//Trace Functions:
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
}
//Log Macros
#define C_TRACE(...) customLog::SyncOut::instance().trace(__VA_ARGS__);
#define T_TRACE(...) customLog::SyncOut::instance().t_trace(__VA_ARGS__);
