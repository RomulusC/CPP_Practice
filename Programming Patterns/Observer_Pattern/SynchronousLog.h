/*
********************************************
Rommulluss Caraiman------------------------*
19/10/2019---------------------------------*
Project: SynchronousLog.h------------------*
File: main.cpp-----------------------------*
********************************************
*/
//Synchronous logging system with a buffer that's malloc(ed) 

#pragma once
#include <iostream>
#include <mutex>
#include <chrono>
#include <cstdarg>
#include <cassert>
#include <chrono>
#include <vector>

namespace customLog
{
#define MAX_BUFFER_SIZE 512 //Currently, if an input stream is > MAX_BUFFER_SIZE, assert occours. If an input stream is smaller than MAX_BUFFER_SIZE, the buffer prints and flushes, then adds stream. 
	using uint = unsigned int;

	class StringBuffer
	{
	private:

		//going to replace null terminators with \n.
	public:
		StringBuffer(uint bufferSize)
			: m_capacity(bufferSize)
			, m_iterator((uint)0)
			, m_buffer((char*)malloc(sizeof(char)* m_capacity))
		{
			m_buffer[0] = '\0';
		}
		static uint strlength(const char* str_)
		{
			uint i = 0;
			while (str_[i] != '\0')
			{
				i++;
				//maybe do an assert here
			}
			return i;
		}
		void push_back(const char c_)
		{
			assert(m_iterator + 1 <= m_capacity); //check for illegal memory access
			m_buffer[m_iterator++] = c_;
		}
		// str_ must always include a '\0'
		void append(const char* str_)
		{
			assert(m_buffer[m_iterator] != '0');// must always be at end to append
			if (m_iterator != 0)
				m_iterator--;
			uint sizeStr = strlength(str_) + 1;
			assert(this->m_iterator + sizeStr < m_capacity);

			// sanity checks
			//assert(m_buffer[m_iterator] != '\0'); // must make sure: end of m_buffer must ALWAYS be '\0'
			//assert((m_iterator + sizeStr) > capacity()); // must make sure: end of m_buffer must ALWAYS be '\0'				

			for (uint i = 0; i < sizeStr; i++)
			{
				this->push_back(str_[i]);
			}
		}
		void append(const char* str_, const uint& length)
		{
			assert(m_buffer[m_iterator] != '0');// must always be at end to append
			assert(this->m_iterator + 1 < m_capacity);

			if (m_iterator != 0)
				m_iterator--;

			for (uint i = 0; i < length; i++)
			{
				this->push_back(str_[i]);
			}
			this->push_back('\0');

		}
		char& operator[](uint i_)
		{
			return m_buffer[i_];
		}
		/* come back to this
		void operator[](uint i_, char& c_)
		{
			m_buffer[i] = c_;
		}
		*/
		void clear()
		{
			m_buffer[0] = '\0';
			m_iterator = 0;
		}

		uint size()
		{
			return m_iterator;
		}
		uint capacity()
		{
			return m_capacity; // it's going to be MAX_BUFFER_SIZE
		}
		const char* c_str()
		{
			return m_buffer;
			// print until reached m_iterator, as there can be multiple strings.
		}
		void it_remOne()
		{
			if (m_iterator != 0)
				m_iterator--;
		}
	private:
		const uint m_capacity;
		uint m_iterator;
		char* m_buffer;
	};

	class SyncOut
	{

	public:
		//Singleton set up:
		SyncOut(SyncOut const&) = delete;
		void operator=(SyncOut const&) = delete;
		~SyncOut() {}

		static SyncOut& instance()
		{
			static SyncOut* s_instance = new SyncOut();
			return *s_instance;
		}
		void printBuffer(bool b_ = false)
		{
			if (!b_)
			{
				std::lock_guard<std::mutex> lck(m_mutex);
			}
			printf(m_buffer.c_str());
		}
		void printBufferReset(bool b_ = false)
		{
			if (!b_)
			{
				std::lock_guard<std::mutex> lck(m_mutex);
			}
			printf(m_buffer.c_str());
			m_buffer.clear();
		}
		void addToBuffer(bool b_,const char* str_...)
		{
			std::lock_guard<std::mutex> lck(m_mutex);

			if (str_ == nullptr || str_[0] == '\0')
				return;
			m_buffer.it_remOne();

			if(b_)
			{
				auto in_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
				struct tm startInfo;
				localtime_s(&startInfo, &in_time_t);
				char x[14] = "[00:00:00] : ";
				char temp[3];
				int i = 0;
				if (startInfo.tm_hour < 10)
				{
					temp[0] = '0';
					i++;
					sprintf_s(temp + i, 2, "%d", startInfo.tm_hour);
				}
				else
					sprintf_s(temp + i, 3, "%d", startInfo.tm_hour);
				x[1] = temp[0];
				x[2] = temp[1];
				i = 0;
				if (startInfo.tm_min < 10)
				{
					temp[0] = '0';
					i++;
					sprintf_s(temp + i, 2, "%d", startInfo.tm_min);
				}
				else
					sprintf_s(temp + i, 3, "%d", startInfo.tm_min);

				x[4] = temp[0];
				x[5] = temp[1];
				i = 0;
				if (startInfo.tm_sec < 10)
				{
					temp[0] = '0';
					i++;
					sprintf_s(temp + i, 2, "%d", startInfo.tm_sec);
				}
				else
					sprintf_s(temp + i, 3, "%d", startInfo.tm_sec);

				x[7] = temp[0];
				x[8] = temp[1];

				uint j = 0;
				while (x[j] != '\0')
				{
					if (m_buffer.capacity() == m_buffer.size() + 1)
					{
						m_buffer.push_back('\0');
						printBufferReset(true);
					}
					m_buffer.push_back(x[j]);
					j++;
				}
			}

			va_list args;
			va_start(args, str_);
			uint i = 0;
			while (str_[i] != '\0')
			{
				if (m_buffer.capacity() == m_buffer.size() + 1)
				{
					m_buffer.push_back('\0');
					printBufferReset(true);
				}

				if (str_[i] == '%')
				{
					char temp[64] = { 0 };
					char format[3] = { str_[i], str_[i + 1], '\0' };
					i++;
					uint offset = sprintf_s(temp, 64, format, va_arg(args, char*));
					uint j = 0;
					while (temp[j] != '\0')
					{
						if (m_buffer.capacity() == m_buffer.size() + 1)
						{
							m_buffer.push_back('\0');
							printBufferReset(true);
						}
						m_buffer.push_back(temp[j]);
						j++;
					}
				}
				else
				{
					m_buffer.push_back(str_[i]);
				}
				i++;
			}
			m_buffer.push_back('\0');
		}
		

		std::thread startThread(std::chrono::milliseconds ms_)
		{
			return std::thread(&SyncOut::Tick, this);
		}
		void stopThread()
		{
			m_isThreadStart = false;
		}


		//Trace Functions:		
	private:
		SyncOut()
			:
			m_buffer(StringBuffer((uint)MAX_BUFFER_SIZE))
			, m_isThreadStart(false)
		{}

		void Tick()
		{
			assert(!m_isThreadStart);
			m_isThreadStart = true;
			using namespace std::chrono_literals;
			while (m_isThreadStart)
			{
				printBufferReset();
				std::this_thread::sleep_for(16ms);
			}
			printBufferReset();
		}

		StringBuffer m_buffer;// stores multiple string objects, kind of like a split pool of char's
		bool m_isThreadStart; //delegates when thread stops
		std::mutex m_mutex; //locking for synchronized reading and writing
	};
}

//Log Macros
#define printBuffer_() customLog::SyncOut::instance().printBuffer()
#define printBufferReset_() customLog::SyncOut::instance().printBufferReset()
#define autoThreadStart_(x) customLog::SyncOut::instance().startThread(x)
#define autoThreadStop_() customLog::SyncOut::instance().stopThread()

#define C_TRACE(...) customLog::SyncOut::instance().addToBuffer(false,__VA_ARGS__)
#define T_TRACE(...) customLog::SyncOut::instance().addToBuffer(true, __VA_ARGS__)