/*
********************************************
Rommulluss Caraiman------------------------*
19/10/2019---------------------------------*
Project: SynchronousLog.inl----------------*
File: main.cpp-----------------------------*
********************************************
*/
// TODO: Add profiling and observe performance difference between a large and small buffer size. Test Stack vs Heap.
// TODO: Add support for hexadecimal numbers in order to display error codes, thread numbers, ect
#pragma once
#include <iostream>
#include <mutex>
#include <cassert>
#include <chrono>
#include <queue>

namespace customLog
{
	using uint = unsigned int;
#define  STACK_BUFFER_SIZE 1024
	class SyncOut
	{
	private:
		// singleton set up:
		SyncOut()	
			: m_buffOne(std::vector<char*>())
			, m_buffTwo(std::vector<char*>())
			, m_bQueueSpecifier(false)
			, m_isThreadStart(false)
			
		{
			m_buffOne.reserve(50);
			m_buffTwo.reserve(50);			
		}
	public:
		SyncOut(SyncOut const&) = delete;
		void operator=(SyncOut const&) = delete;
		~SyncOut() {}

		static SyncOut& instance()
		{
			static SyncOut* s_instance = new SyncOut();
			return *s_instance;
		}
		// singleton fin set up

		template<typename ...T>
		void AddToBuffer(bool trace_, const char* str_, T ...args_)
		{
			char buffer[STACK_BUFFER_SIZE];

			if (trace_)
			{
				strcpy_s(buffer, 14, "[00:00:00] : ");// 14 chars including '0'
				auto in_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
				struct tm startInfo;
				localtime_s(&startInfo, &in_time_t);
				char temp[3];
				int i = 0;
				if (startInfo.tm_hour < 10)
				{
					temp[0] = '0';
					i++;
					sprintf_s(temp + i, 2, "%d", startInfo.tm_hour);
				}
				else
				{
					sprintf_s(temp + i, 3, "%d", startInfo.tm_hour);
				}
				buffer[1] = temp[0];
				buffer[2] = temp[1];
				i = 0;
				if (startInfo.tm_min < 10)
				{
					temp[0] = '0';
					i++;
					sprintf_s(temp + i, 2, "%d", startInfo.tm_min);
				}
				else
				{
					sprintf_s(temp + i, 3, "%d", startInfo.tm_min);
				}

				buffer[4] = temp[0];
				buffer[5] = temp[1];
				i = 0;
				if (startInfo.tm_sec < 10)
				{
					temp[0] = '0';
					i++;
					sprintf_s(temp + i, 2, "%d", startInfo.tm_sec);
				}
				else
				{
					sprintf_s(temp + i, 3, "%d", startInfo.tm_sec);
				}

				buffer[7] = temp[0];
				buffer[8] = temp[1];	

				sprintf_s(&buffer[13], STACK_BUFFER_SIZE - 13, str_, args_...);
			}
			else
			{
				sprintf_s(buffer, STACK_BUFFER_SIZE, str_, args_...);
			}

			uint length = (uint)strlen(buffer) + 1;
			char* outPut = new char[length];
			strcpy_s(outPut, length, buffer);
			if (!m_bQueueSpecifier) // if first
			{
				std::lock_guard<std::mutex> lck(m_mutexOne);
				m_buffOne.emplace_back(outPut);
			}
			else
			{
				std::lock_guard<std::mutex> lck(m_mutexTwo);
				m_buffTwo.emplace_back(outPut);

			}
		}
		void PrintBufferReset()
		{
			assert(!m_isThreadStart); // Cannot use AutoThread and PrintBufferReset at the same time.
			m_bQueueSpecifier = !m_bQueueSpecifier;
			if (m_bQueueSpecifier == true)  //print first as swapped to second
			{				
				std::lock_guard<std::mutex> lck(m_mutexOne);		
				auto it = m_buffOne.begin();
				while (it != m_buffOne.end())
				{
					printf("%s\n", *it);
					delete[] * it;
					it++;
				}
				m_buffOne.erase(m_buffOne.begin(), m_buffOne.end());
			}
			else // print second as swapped to first
			{
				std::lock_guard<std::mutex> lck(m_mutexTwo);
				auto it = m_buffTwo.begin();
				while (it != m_buffTwo.end())
				{
					printf("%s\n", *it);
					delete[] * it;
					it++;
				}
				m_buffTwo.erase(m_buffTwo.begin(), m_buffTwo.end());
			}			
		}
		std::thread StartThread(std::chrono::milliseconds ms_)
		{
			return std::thread(&SyncOut::Tick, this);
		}
		void StopThread()
		{
			m_isThreadStart = false;
		}
	private:
		void PrintBufferResetLocalThread()
		{
			m_bQueueSpecifier = !m_bQueueSpecifier;
			if (m_bQueueSpecifier == true)  //print first as swapped to second
			{
				std::lock_guard<std::mutex> lck(m_mutexOne);
				auto it = m_buffOne.begin();
				while (it != m_buffOne.end())
				{
					printf("%s\n", *it);
					delete[] * it;
					it++;
				}
				m_buffOne.erase(m_buffOne.begin(), m_buffOne.end());
			}
			else // print second as swapped to first
			{
				std::lock_guard<std::mutex> lck(m_mutexTwo);
				auto it = m_buffTwo.begin();
				while (it != m_buffTwo.end())
				{
					printf("%s\n", *it);
					delete[] * it;
					it++;
				}
				m_buffTwo.erase(m_buffTwo.begin(), m_buffTwo.end());
			}
		}
		void Tick()
		{
			assert(!m_isThreadStart);
			m_isThreadStart = true;
			using namespace std::chrono_literals;
			while (m_isThreadStart)
			{
				PrintBufferResetLocalThread();
				std::this_thread::sleep_for(16ms);
			}
			PrintBufferResetLocalThread();
		}
	private:
		std::vector<char*> m_buffOne, m_buffTwo;
		bool m_bQueueSpecifier;
		std::mutex m_mutexOne, m_mutexTwo;
		bool m_isThreadStart;
	}; // fragmentation prevention vs fewer cycles
}

// Log Macros
#define PrintBufferReset_() customLog::SyncOut::instance().PrintBufferReset()
#define AutoThreadStart_(x) customLog::SyncOut::instance().StartThread(x)
#define AutoThreadStop_() customLog::SyncOut::instance().StopThread()

#define C_TRACE(...) customLog::SyncOut::instance().AddToBuffer(false, __VA_ARGS__)
#define T_TRACE(...) customLog::SyncOut::instance().AddToBuffer(true,  __VA_ARGS__)
// Log Macros End