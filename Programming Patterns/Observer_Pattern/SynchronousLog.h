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

namespace customLog
{
	class SyncOut
	{
		#define MAX_BUFFER_SIZE 1024
		//TODO: try to support new pools when buffer is overflown
	
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

		//bool t_trace if you want timing included in line
		void trace(bool t_trace,const char* str_...)
		{			
			
			if(str_==nullptr || str_[0]=='\0')
				return;
			va_list args;
			va_start(args,str_);
			std::unique_lock<std::mutex> lck(m_mutex);
			//Very crude way of doing this but it will do.
			if(t_trace)
			{
				auto in_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
				struct tm startInfo;
				localtime_s(&startInfo, &in_time_t);
				char x[14] ="[00:00:00] : ";
				char temp[3];
				int i = 0;
				if(startInfo.tm_hour<10)
				{
					temp[0]='0';			
					i++;		
				}				
				sprintf(temp+i,"%d",startInfo.tm_hour);
				x[1] = temp[0];
				x[2] = temp[1];
				i=0;
				if(startInfo.tm_min<10)
				{
					temp[0]='0';			
					i++;		
				}
				sprintf(temp+i,"%d",startInfo.tm_min);
				x[4] = temp[0];
				x[5] = temp[1];
				i=0;
				if(startInfo.tm_sec<10)
				{
					temp[0]='0';			
					i++;		
				}
				sprintf(temp+i,"%d",startInfo.tm_sec);

				x[7] = temp[0];
				x[8] = temp[1];


				addToBuffer(x,"%s");
			}
			unsigned int i = 0;
			while(str_[i]!='\0')
			{
				if(str_[i]=='%')
				{					
					char x[3] = {str_[i],str_[i+1],'\0'};
					addToBuffer(va_arg(args,char*),x);
					i+=1;
				}
				else
					addToBuffer(*(str_+i));

				i++;				
			}
			addToBuffer('\0');
		}
		void printBufferReset()
		{
			printBuffer();
			m_count = 0;			
		}
		void printBuffer()
		{
			if(m_count==0)
				return;

			std::unique_lock<std::mutex> lck(m_mutex);
				
			unsigned short i = 0;
			unsigned short prevStart = 0;
			while(prevStart!=m_count)
			{
				while(*(m_buffer+i)!='\0')
				{
					i++;
				}
				i++;
				printf((char*)(m_buffer+prevStart));
				prevStart = i;
				assert(prevStart<=m_count);
			}
		}
		//Function to allow to easily set up its own thread for testing
		//The printbuffer() would probably be added in a main frame thread
		std::thread autoThread(std::chrono::milliseconds ms_)
		{
			return std::thread(&SyncOut::Tick,this);
		}
		void stopThread()
		{
			m_isThreadStart=false;
		}
		void Tick()
		{
			assert(!m_isThreadStart);
			m_isThreadStart = true;
			using namespace std::chrono_literals;
			while(m_isThreadStart)
			{
				printBufferReset();
				std::this_thread::sleep_for(16ms);
			}
			printBufferReset();
		}
	private:
		SyncOut()
		: 
		m_buffer((char*)malloc(sizeof(char[MAX_BUFFER_SIZE]))),
		m_count(0),
		m_isThreadStart(false)
		{}
		//any other STRING type
		void addToBuffer(const char* t_,const char* format_)
		{
			char temp[64];
			int offset = std::sprintf(temp, format_, t_);
			assert(m_count+offset<=MAX_BUFFER_SIZE);
			
			for(unsigned int i =0; i<offset;i++)
				addToBuffer(*(temp+i));				
		}
		//char only
		void addToBuffer(const char& c_)
		{
			if(m_count+1>MAX_BUFFER_SIZE)
				printBufferReset();

			*(m_buffer+m_count) = c_;
				m_count++;
		}

		std::mutex m_mutex; //locking for synchronised reading and writing
		//m_count will always be on the \0 of the last string
		char* m_buffer; // TODO: maybe have a vector of these, to allow  for overflow. 
		unsigned short int m_count;	//current position of last alive string's '\0'
		bool m_isThreadStart; //deligates when thread stops
	};	
}

//Log Macros
#define printBufferReset SyncOut::instance().printBufferReset
#define printBuffer SyncOut::instance().printBuffer
#define startAutoThread SyncOut::instance().autoThread
#define stopAutoThread SyncOut::instance().stopThread

#define C_TRACE(...) customLog::SyncOut::instance().trace(false,__VA_ARGS__);
#define T_TRACE(...) customLog::SyncOut::instance().trace(true,__VA_ARGS__);