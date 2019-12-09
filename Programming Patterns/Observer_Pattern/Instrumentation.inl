/*
********************************************
Rommulluss Caraiman------------------------*
19/10/2019---------------------------------*
Project: Observer Pattern------------------*
File:Instrumentation.inl-------------------*
********************************************
*/

#pragma once
#include <chrono>
#include <string>
#include <iostream>
#include "SynchronousLog.inl"

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
		long long start = std::chrono::time_point_cast<std::chrono::milliseconds>(endTimePoint).time_since_epoch().count();
		long long end  = std::chrono::time_point_cast<std::chrono::milliseconds>(m_startTimePoint).time_since_epoch().count();
		T_TRACE("%s took: %.3fs\n", m_name.c_str(), (float)(start-end)/1000);
	
		m_stopped = true;
	}
private:
	std::string m_name;
	bool m_stopped;
	std::chrono::steady_clock::time_point m_startTimePoint;
};