/*
********************************************
Rommulluss Caraiman------------------------*
19/10/2019---------------------------------*
Project: Observer Pattern------------------*
File: main.cpp-----------------------------*
********************************************
*/

#include <iostream>
#include <chrono>
#include <thread>
#include <sstream> 
#include <mutex>
#include <future>

#include "ObserverPattern.h"

class AtomicTime : public Subject
{
private:
	std::mutex m_mutex;
	
	long long m_msDelay;	
	std::chrono::time_point<std::chrono::system_clock> start; 

	bool stop;
	bool init; 

public:
	AtomicTime(long long delay)
		:init(false), stop(false), m_msDelay(delay) {}
	
	std::string ObserGetTimeString()
	{
		std::unique_lock<std::mutex> sLock(m_mutex);
		auto in_time_t = std::chrono::system_clock::to_time_t(start);
		struct tm timeinfo;
		localtime_s(&timeinfo, &in_time_t);
		std::stringstream ss;
		ss << timeinfo.tm_hour << ":" << timeinfo.tm_min << ":" << timeinfo.tm_sec << " ----------------------- Delay:" << std::to_string(m_msDelay) << "ms";
		sLock.unlock();
		return ss.str();
	}
	~AtomicTime()
	{
		DeInit();
	}

	void Tick()
	{
		while (true)
		{
			using namespace std::chrono_literals;
			std::unique_lock<std::mutex> uLock(m_mutex);
			if (init == false)
			{
				start = std::chrono::system_clock::now();
				init = true;
			}
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start);

			if (duration.count() > m_msDelay)
			{
				m_msDelay += 50;
				if (m_msDelay > 1000)
					m_msDelay = 200;
				start = std::chrono::system_clock::now();
				uLock.unlock();
				UpdateObservers();
				uLock.lock();
			}
			if (stop == true)
			{
				uLock.unlock();

				return;
			}
			uLock.unlock();

		}
	}

	void DeInit()
	{
		std::unique_lock<std::mutex> uLock(m_mutex);
		stop = true;
		uLock.unlock();
		return;
	}

};

class LocalClock : public Observer
{
private:
	static unsigned int count;
	int thisId;
	
public:
	LocalClock()
	{
		thisId = ++count;
	}

	~LocalClock() {}

	virtual void Update(Subject* s) override
	{
		std::unique_lock<std::mutex> lk(m_mutex);
		AtomicTime* target = static_cast<AtomicTime*>(s);
		//--------------------------------------------------------

		std::cout << "Observer ID: " << thisId << " ----------- Time: " << target->ObserGetTimeString() << " -------------------------\n";
	}
	unsigned int GetID()
	{
		return thisId;
	}	
};

unsigned int LocalClock::count = 0;
int main()
{
	std::cout << "The Observer Pattern.\n" <<
		"The AtomicTime object (the subject) runs on it's own thread keeping time duration,\n"<<
		"updates any objects (observers) that have subscribed to the subject over a period of time.\n" <<
		"Three observers will be subscribed to one subject in this demonstration." << 
		"\nPress any key to start.\n";

	AtomicTime* subject = new AtomicTime(200);
	LocalClock* observer1 = new LocalClock();
	LocalClock* observer2 = new LocalClock();
	LocalClock* observer3 = new LocalClock();
	LocalClock* observer4 = new LocalClock();


	subject->SubscribeObserver(static_cast<Observer*>(observer1));
	subject->SubscribeObserver(static_cast<Observer*>(observer2));
	//Adding additional same observer to subject subscription to test unintentional additional subscriptions.
	subject->SubscribeObserver(static_cast<Observer*>(observer3));
	subject->SubscribeObserver(static_cast<Observer*>(observer3));
	subject->SubscribeObserver(static_cast<Observer*>(observer3));
	subject->SubscribeObserver(static_cast<Observer*>(observer3));
	subject->SubscribeObserver(static_cast<Observer*>(observer3));
	subject->SubscribeObserver(static_cast<Observer*>(observer3));
	subject->SubscribeObserver(static_cast<Observer*>(observer4));



	using namespace std::chrono_literals;
	std::cin.get();
	//std::thread subjectThread(&AtomicTime::Tick, subject);
	auto thread = std::async(std::launch::async, &AtomicTime::Tick, subject);
	std::this_thread::sleep_for(3s);
	subject->UnsubscribeObserver(observer1);
	std::cout << "UNSUBSCRIBED: " << observer1->GetID() << " =====================================\n";
	std::this_thread::sleep_for(3s);
	std::cout << "DELETING: " << observer3->GetID() << " =====================================\n";
	//subject->UnsubscribeObserver(observer3);
	delete observer3;
	std::cout << "PRESS TO DELETE SUBJECT! " << " =====================================\n";
	std::cin.get();
	//subject->DeInit(); //check if initiating DeInit() or delete in either order causes crash
	delete subject;
	std::cout << "DONE! " << " =====================================\n";
	std::cin.get();
	
}