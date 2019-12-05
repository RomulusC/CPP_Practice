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
#include <sstream> // TODO: Don't rely on sstream, use some fixed char[] buffer instead 
#include <shared_mutex>

#define OBSERVER_PATTERN 1
#if OBSERVER_PATTERN

#include "ObserverPattern.h"
class AtomicTime : public Subject
{
private:
	std::shared_mutex m_mutex;
	
	long long m_msDelay;	
	std::chrono::time_point<std::chrono::system_clock> start; 

	bool stop;
	bool init; 

	void Tick()
	{
		while (stop == false)
		{
				using namespace std::chrono_literals;
			{
				std::unique_lock<std::shared_mutex> lck(m_mutex);
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
					lck.unlock();
					UpdateObservers();
					C_TRACE("---------------------------------------------\n");
				}
			}
			std::this_thread::sleep_for(15ms);
		}
	}


public:
	AtomicTime(long long delay)
		:init(false), stop(false), m_msDelay(delay) {}
	
	std::string ObserGetTimeString()
	{
		std::shared_lock<std::shared_mutex> sLock(m_mutex);
		auto in_time_t = std::chrono::system_clock::to_time_t(start);
		struct tm startInfo;
		localtime_s(&startInfo, &in_time_t);
		std::stringstream ss;
		ss << startInfo.tm_hour << ":" << startInfo.tm_min << ":" << startInfo.tm_sec << " Delay:" << std::to_string(m_msDelay) << "ms";
		return ss.str();
	}
	~AtomicTime()
	{
		Stop();
	}
	std::thread Start()
	{
		return std::thread(&AtomicTime::Tick, this);
	}
	void Stop()
	{
		std::unique_lock<std::shared_mutex> uLock(m_mutex);
		stop = true;
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
		std::unique_lock<std::shared_mutex> lk(m_mutex);
		AtomicTime* target = static_cast<AtomicTime*>(s);
		T_TRACE("Observer ID: %d Time: %s\n" , thisId, target->ObserGetTimeString().c_str());
	}
	unsigned int GetID()
	{
		return this->thisId;
	}	
	void PrintNeighbours()
	{
		std::unique_lock<std::shared_mutex> lk(m_mutex);
		T_TRACE("LocalClock ID: %u " , this->GetID());
		
		auto it = m_ObserverMap.begin();
		if (it == m_ObserverMap.end())
		{
			T_TRACE("NO SUBSCRIPTIONS!\n");
		}
		for (auto it : m_ObserverMap)
		{
			C_TRACE("Subject object: %u\n Previous ID: %u\nNext ID: %u\n" , it.first , it.second.m_previous, it.second.m_next );
		}
	}
};
void PrintSubscribedObservers(AtomicTime* _s) //concrete type specific
{
	T_TRACE("Printing out subscriptions. ----------------------\n");

	Observer* current = _s->GetObserverLinkedList();
	if (current == nullptr)
	{
		T_TRACE("No Subscriptions\n");
		return;
	}
	while (current != nullptr)

	{
		T_TRACE("OBSERVER ID: %d \n" , static_cast<LocalClock*>(current)->GetID());
		current = current->GetNext(_s);
	}

}

unsigned int LocalClock::count = 0;
	
	
int main()
{
	using namespace std::chrono_literals;
	std::thread thread_logging = autoThreadStart_(15ms);
	

	C_TRACE("The Observer Pattern.\n");
	C_TRACE("The AtomicTime object (the subject) runs on it's own thread keeping time duration,\n");
	C_TRACE("updates any objects (observers) that have subscribed to the subject over a period of time.\n");
	C_TRACE("Three observers will be subscribed to one subject in this demonstration.\n");
	C_TRACE("Press any key to start.\n\n");
	std::cin.get();

	AtomicTime* subject = new AtomicTime(200);
	LocalClock* observer1 = new LocalClock();
	LocalClock* observer2 = new LocalClock();
	LocalClock* observer3 = new LocalClock();
	LocalClock* observer4 = new LocalClock();
	LocalClock* observer5 = new LocalClock();

	PrintSubscribedObservers(subject);
	subject->UnsubscribeObserver(observer1);

	subject->SubscribeObserver(observer1);
	PrintSubscribedObservers(subject);

	subject->SubscribeObserver(observer2);
	subject->SubscribeObserver(observer3);
	subject->SubscribeObserver(observer4);
	//Additional same observers to subject subscription to test unintentional additional subscriptions.
	PrintSubscribedObservers(subject);

	subject->SubscribeObserver(observer3); //test: Refuse duplicate subscription

	subject->UnsubscribeObserver(observer3); 
	subject->UnsubscribeObserver(observer5); //test: Refuse to unsubscribed an already unsubscribed observer
	PrintSubscribedObservers(subject);
	
	auto thread = subject->Start();
	std::this_thread::sleep_for(3s);

	subject->UnsubscribeObserver(observer1);
	T_TRACE("UNSUBSCRIBED: %u\n", observer1->GetID());

	delete observer3;
	T_TRACE("DELETED: %u\n", observer3->GetID());

	delete observer4;
	T_TRACE("DELETED: %u\n", observer4->GetID());

	PrintSubscribedObservers(subject);

	T_TRACE("PRESS TO DELETE SUBJECT! \n");

	std::cin.get();
	subject->SubscribeObserver(observer5);
	//Check
	observer1->PrintNeighbours();//unsubscribed, no neighbors
	observer2->PrintNeighbours();//subscribed
	//observer3->PrintNeighbours();//deleted
	//observer4->PrintNeighbours();//deleted
	observer5->PrintNeighbours();//resubscribed
	//subject->DeInit(); //check if initiating DeInit() or delete in either order causes crash
	delete subject;
	T_TRACE("SUBJECT DELETED! \n");
	//Check
	observer1->PrintNeighbours();
	observer2->PrintNeighbours();
	//observer3->PrintNeighbours();//deleted
	//observer4->PrintNeighbours();//deleted
	observer5->PrintNeighbours();
	for(int i =0;i<50;i++) //Use this to check for buffer overflow
	T_TRACE("TEST_SPAM! \n");

	thread.join();
	autoThreadStop_();
	thread_logging.join();
	std::cin.get();	
}
#else

#include "SynchronousLog.h"

int main()
{
	C_TRACE("-------------------------%d-------%d---%d---%d-------\n",22,23,24,25);
	printBufferReset_();
	std::cin.get();

	return 0;
}
#endif