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
#include <shared_mutex>

#include "ObserverPattern.h"

class AtomicTime : public Subject
{
private:
	std::shared_mutex m_mutex2;
	long long m_msDelay; //m_mutex2;
	std::chrono::time_point<std::chrono::system_clock> start; //m_mutex2;

	std::shared_mutex m_mutex; 
	bool stop; //m_mutex
	bool init; //m_mutex

public:
	AtomicTime(long long delay)
		:init(false), stop(false), m_msDelay(delay) {}	
	
	std::string ObserGetTimeString()
	{		
		std::stringstream ss;
		std::shared_lock<std::shared_mutex> lock(m_mutex2);
		auto in_time_t = std::chrono::system_clock::to_time_t(start);
		struct tm timeinfo;
		localtime_s(&timeinfo, &in_time_t);
		ss << timeinfo .tm_hour<<":"<<timeinfo.tm_min<< ":" << timeinfo.tm_sec<< " ----------------------- Delay:" << std::to_string(m_msDelay)<<"ms";
		lock.unlock();
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
			if (init == false)
			{
				std::unique_lock<std::shared_mutex> lock3(m_mutex2);
				start = std::chrono::system_clock::now();
				lock3.unlock();
				init = true;
			}
			std::shared_lock<std::shared_mutex> lock1(m_mutex2);
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start);

			if (duration.count() > m_msDelay )
			{
				lock1.unlock();
				std::unique_lock<std::shared_mutex> lock2(m_mutex2);
				m_msDelay += 50;
				if (m_msDelay > 1000)
					m_msDelay = 200;
				start = std::chrono::system_clock::now();
				lock2.unlock();
				UpdateObservers();
			}						
			
			std::shared_lock<std::shared_mutex> lock(m_mutex);
			if (stop == true)
			{
				lock.unlock();
				return;
			}
			lock.unlock();				
		}
	}

	void DeInit()
	{			
		std::unique_lock<std::shared_mutex> lock(m_mutex);
		stop = true;
		return;	
	}

};

class LocalClock : public Observer
{
private:	
	static unsigned int count;
	int thisId;

	virtual void Destruction() override
	{
		auto it = m_SubscribedSubjects.begin();
		while (it != m_SubscribedSubjects.end())
		{
			(*it)->UnsubscribeObserver(this);
			it++;
		}
	}

public:
	LocalClock()
	{
		thisId = ++count;
	}
	~LocalClock()
	{
		Destruction();
		
	}
	virtual void Update(Subject* s) override
	{
		AtomicTime* target = static_cast<AtomicTime*>(s);	
		std::cout <<"Observer ID: "<<thisId<<" ----------- Time: "<< target->ObserGetTimeString() << " -------------------------\n";
	}
	unsigned int GetID()
	{
		return thisId;
	}
	virtual void SubjectDestroyed(Subject* o_) override
	{
		auto it = std::find(m_SubscribedSubjects.begin(), m_SubscribedSubjects.end(), o_);
		if (it != m_SubscribedSubjects.end())
			m_SubscribedSubjects.erase(it);
	}	
};
unsigned int LocalClock::count = 0;
int main()
{
	std::cout << "The Observer Pattern.\n" <<
		"The AtomicTime object (the subject) runs on it's own thread keeping time duration,\nupdates any objects (obserers) that have subscribed to the subject over a period of time.\n" <<

		"Three observers will be subscribed to one subject in this demonstration."<<"\nPress any key to start.\n";
	std::cin.get();


	AtomicTime* subject = new AtomicTime(200);
	LocalClock* observer1 = new LocalClock();
	LocalClock* observer2 = new LocalClock();
	LocalClock* observer3 = new LocalClock();
	

	subject->SubscribeObserver(static_cast<Observer*>(observer1));
	subject->SubscribeObserver(static_cast<Observer*>(observer2));
	//Adding additional same observer to subject subscription to test unintentional additional subscriptions.
	subject->SubscribeObserver(static_cast<Observer*>(observer3));
	subject->SubscribeObserver(static_cast<Observer*>(observer3));
	subject->SubscribeObserver(static_cast<Observer*>(observer3));
	subject->SubscribeObserver(static_cast<Observer*>(observer3));
	subject->SubscribeObserver(static_cast<Observer*>(observer3));
	subject->SubscribeObserver(static_cast<Observer*>(observer3));


	std::thread subjectThread(&AtomicTime::Tick, subject);
	
	std::cin.get();
	subject->UnsubscribeObserver(observer1);
	std::cout << "UNSUBSCRIBED: " << observer1->GetID() << "--------------------------------\n";
	std::cin.get();
	std::cout << "DELETING: " << observer3->GetID() << "--------------------------------\n";
	delete observer3;
	std::cout << "DONE! "<< "--------------------------------\n";
	std::cin.get();
	subject->DeInit(); //check if initiating DeInit() or delete in either order causes crash
	std::cout << "DELETING SUBJECT "<< "--------------------------------\n";
	delete subject;
	std::cin.get();	
	subjectThread.join();	
}