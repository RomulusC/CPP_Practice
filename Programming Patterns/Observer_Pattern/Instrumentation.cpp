/*
********************************************
Rommulluss Caraiman------------------------*
10/11/2019---------------------------------*
Project: Observer Pattern------------------*
File:Instrumentation.inl-------------------*
********************************************
*/

#pragma once
#include <string>
#include <chrono>
#include <fstream>
#include <algorithm>
#define PROFILE 1

struct ProfileResult
{
	std::string Name;
	long long Start, End;
	uint32_t ThreadID;
};

struct InstrumentationSession
{
	std::string Name;
};
class Instrumentor
{
	using uint = unsigned int;

public:
	Instrumentor(Instrumentor const&) = delete; // Copy constructor
	void operator=(Instrumentor const&) = delete; // Assignment Operator
	~Instrumentor() {}
private:
	Instrumentor()
		: m_CurrentSession(nullptr)
		, m_OutputStream("")
		, m_ProfileCount((uint)0)
	{}
public:
	static Instrumentor& Instance()
	{
		static Instrumentor* instance = new Instrumentor();
		return *instance;
	}
	void BeginSession(const char* name, const char* filepath)
	{
		m_OutputStream.open(filepath);
		WriteHeader();
		m_CurrentSession = new InstrumentationSession{ name };
	}

	void EndSession()
	{
		WriteFooter();
		m_OutputStream.close();
		delete m_CurrentSession;
		m_CurrentSession = nullptr;
		m_ProfileCount = 0;
	}

	void WriteProfile(const ProfileResult& result)
	{
		if (m_ProfileCount++ > 0)
			m_OutputStream << ",";

		std::string name = result.Name;
		std::replace(name.begin(), name.end(), '"', '\'');

		m_OutputStream << "{";
		m_OutputStream << "\"cat\":\"function\",";
		m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
		m_OutputStream << "\"name\":\"" << name << "\",";
		m_OutputStream << "\"ph\":\"X\",";
		m_OutputStream << "\"pid\":0,";
		m_OutputStream << "\"tid\":" << result.ThreadID << ",";
		m_OutputStream << "\"ts\":" << result.Start;
		m_OutputStream << "}";

		m_OutputStream.flush();
	}

	void WriteHeader()
	{
		m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
		m_OutputStream.flush();
	}

	void WriteFooter()
	{
		m_OutputStream << "]}";
		m_OutputStream.flush();
	}
	InstrumentationSession* m_CurrentSession;
	std::ofstream m_OutputStream;
	uint m_ProfileCount;
};

class InstrumentationTimer
{
public:
	InstrumentationTimer(const char* str_)
		: m_name(str_)
		, m_stopped(false)
		, m_startTimePoint(std::chrono::high_resolution_clock::now())
	{}
	~InstrumentationTimer()
	{
		if (!m_stopped)
			Stop();
	}
	void Stop()
	{
		auto endTimePoint = std::chrono::high_resolution_clock::now();
		long long start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_startTimePoint).time_since_epoch().count();
		long long end  = std::chrono::time_point_cast<std::chrono::milliseconds>(endTimePoint).time_since_epoch().count();
		//T_TRACE("%s took: %.10lfs\n", m_name, (double)(start-end)/(double)1000000000);
		uint32_t threadID = (uint32_t)std::hash<std::thread::id>{}(std::this_thread::get_id());
		Instrumentor::Instance().WriteProfile(ProfileResult{ std::string(m_name), start * 1000, end * 1000, threadID });
	
		m_stopped = true;
	}
private:
	const char* m_name;
	bool m_stopped;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimePoint;
};
#if PROFILE
	#define PROFILE_BEGIN_SESSION(name, filepath) Instrumentor::Instance().BeginSession(name, filepath)
	#define PROFILE_END_SESSION() Instrumentor::Instance().EndSession()
	#define PROFILE_SCOPE(name) InstrumentationTimer timer##__LINE__(name);
	#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCSIG__)
#else
	#define PROFILE_BEGIN_SESSION(name, filepath)
	#define PROFILE_END_SESSION()
	#define PROFILE_SCOPE(name)
	#define PROFILE_FUNCTION()
#endif
	
