/*
********************************************
Rommulluss Caraiman------------------------*
19/10/2019---------------------------------*
Project: SynchronousLog.h------------------*
File: main.cpp-----------------------------*
********************************************
*/
// TODO: Add profiling and observe performance difference between a large and small buffer size. Test Stack vs Heap.
// TODO: Add support for hexadecimal numbers in order to display error codes, thread numbers, ect
#pragma once
#include <iostream>
#include <mutex>
#include <chrono>
#include <cstdarg>
#include <cassert>
#include <chrono>

namespace customLog
{
	using uint = unsigned int;

	class StringBuffer
	{				
	#define MAX_BUFFER_SIZE 1024 //Currently if the stream is full, the current thread process prints buffer and resets. Printing the buffer may take long but the reset just sets the iterator to 0 (should be faster than setting all indexes to '\0')
	public:
		StringBuffer()
			: m_capacity(MAX_BUFFER_SIZE)
			, m_iterator((uint)0)
			//, m_buffer(/*(char*)malloc(sizeof(char)* m_capacity)*/ char[MAX_BUFFER_SIZE]) // now moved to be on the stack
		{
			m_buffer[0] = '\0'; // : m_buffer((char*)malloc(sizeof(char)* m_capacity) gives intellisense error that this line dereferences a nullptr, although it will never be a nulltpr
		}
		~StringBuffer()
		{}
		// strlen does not include null terminator, and neither will strlength
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
		// adds character to the next position, does not increase array size
		void push_back(const char c_)
		{
			assert(m_iterator + 1 <= m_capacity); //check for illegal memory access
			m_buffer[m_iterator++] = c_;
		}
		// str_ end must always be '\0'
		void append(const char* str_)
		{
			assert(m_buffer[m_iterator] != '0'); // must always be at end to append
			if (m_iterator != 0)
				m_iterator--;
			uint sizeStr = strlength(str_) + 1;
			assert(this->m_iterator + sizeStr < m_capacity);						

			for (uint i = 0; i < sizeStr; i++)
			{
				this->push_back(str_[i]);
			}
		}
		// append range from str_ pointer
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
		// buffer character accessor
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
		// sets index 0 to '\0' and resets iterator to 0
		void clear()
		{
			m_buffer[0] = '\0';
			m_iterator = 0;
		}
		// returns size of string in buffer
		uint size()
		{
			return m_iterator;
		}
		// returns total capacity of buffer
		uint capacity()
		{
			return m_capacity; // it's going to be MAX_BUFFER_SIZE
		}
		// returns const char* of begining of buffer
		const char* c_str()
		{
			return m_buffer;
			// print until reached m_iterator, as there can be multiple strings.
		}
		// reduces 1 from m_iterator, use this when you wish to overwrite the previous '\0'
		void it_remOne()
		{
			if (m_iterator != 0)
			{
				m_iterator--;
			}
		}
	private:
		const uint m_capacity; // total buffer capacity
		uint m_iterator; // iterator to end of string buffer, can also indicate total occupied buffer size
		char m_buffer[MAX_BUFFER_SIZE];
	};

	class SyncOut
	{
	private:
		// singleton set up:
		SyncOut()
			:
			m_buffer(StringBuffer())
			, m_isThreadStart(false)
		{}
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

		// synchronous print, function calls will wait for mutex lock to be released,
		// b_ true if the calling scope already contains the mutex
		void printBuffer(bool b_ = false)
		{
			if (!b_)
			{
				std::lock_guard<std::mutex> lck(m_mutex);
			}
			printf(m_buffer.c_str());
		}
		// synchronous print and reset, function calls will wait for mutex lock to be released,
		// b_ true if the calling scope already contains the mutex
		void printBufferReset(bool b_ = false)
		{
			if (!b_)
			{
				std::lock_guard<std::mutex> lck(m_mutex);
			}
			printf(m_buffer.c_str());
			m_buffer.clear();
		}
		// adds string to buffer. b_ = true if time tracing is required
		void addToBuffer(bool b_,const char* str_...)
		{
			std::lock_guard<std::mutex> lck(m_mutex);

			if (str_ == nullptr || str_[0] == '\0')
				return;
			m_buffer.it_remOne();
			// adding time to buffer if trace is enabled
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
				// detect symbols of string format to add numbers
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
		
		// self running thread that prints buffer. Must call stopThread to stop
		std::thread startThread(std::chrono::milliseconds ms_)
		{
			return std::thread(&SyncOut::Tick, this);
		}
		void stopThread()
		{
			m_isThreadStart = false;
		}

	private:
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

// Log Macros
#define printBuffer_() customLog::SyncOut::instance().printBuffer()
#define printBufferReset_() customLog::SyncOut::instance().printBufferReset()
#define autoThreadStart_(x) customLog::SyncOut::instance().startThread(x)
#define autoThreadStop_() customLog::SyncOut::instance().stopThread()

#define C_TRACE(...) customLog::SyncOut::instance().addToBuffer(false,__VA_ARGS__)
#define T_TRACE(...) customLog::SyncOut::instance().addToBuffer(true, __VA_ARGS__)
// Log Macros End