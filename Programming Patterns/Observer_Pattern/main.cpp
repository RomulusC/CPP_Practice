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
#include "SynchronousLog.cpp"

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
		ss << startInfo.tm_hour << ":" << startInfo.tm_min << ":" << startInfo.tm_sec << " ----------------------- Delay:" << std::to_string(m_msDelay) << "ms";
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
		std::cout << "Observer ID: " << thisId << " ----------- Time: " << target->ObserGetTimeString() << " -------------------------\n";
	}
	unsigned int GetID()
	{
		return this->thisId;
	}	
	void PrintNeighbours()
	{
		std::unique_lock<std::shared_mutex> lk(m_mutex);

		std::cout << "LocalClock ID: " << this->GetID() << "\n";
		
		auto it = m_ObserverMap.begin();
		if (it == m_ObserverMap.end())
		{
			std::cout << "NO SUBSCRIPTIONS!\n";
		}
		for (auto it : m_ObserverMap)
		{
			std::cout << "Subject object: " << it.first << "\n";
			std::cout << "Previous ID: " << it.second.m_previous<<" ";
			std::cout << "Next ID: " << it.second.m_next<<"\n";
		}
	}
};
void PrintSubscribedObservers(AtomicTime* _s) //concrete type specific
{
	std::cout << "Printing out subscriptions.\n";

	Observer* current = _s->GetObserverLinkedList();
	if (current == nullptr)
	{
		std::cout << "No Subscriptions\n";
		return;
	}
	while (current != nullptr)

	{
		std::cout << "OBSERVER ID: " << static_cast<LocalClock*>(current)->GetID()<<"\n";
		current = current->GetNext(_s);
	}

}


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
	

	using namespace std::chrono_literals;
	auto thread = subject->Start();
	std::this_thread::sleep_for(3s);
	subject->UnsubscribeObserver(observer1);
	std::cout << "UNSUBSCRIBED: " << observer1->GetID() << " =====================================\n";

	std::cout << "DELETING: " << observer3->GetID() << " =====================================\n";
	delete observer3;
	std::cout << "PRESS TO DELETE SUBJECT! " << " =====================================\n";

	std::cout << "DELETING: " << observer4->GetID() << " =====================================\n";
	delete observer4;
	PrintSubscribedObservers(subject);


	std::cout << "PRESS TO DELETE SUBJECT! " << " =====================================\n";
	std::cin.get();
	subject->SubscribeObserver(observer5);
	//Check
	observer1->PrintNeighbours();//no neighbors
	observer2->PrintNeighbours();//subscribed
	//observer3->PrintNeighbours();
	//observer4->PrintNeighbours();
	observer5->PrintNeighbours();//no subscribed
	//subject->DeInit(); //check if initiating DeInit() or delete in either order causes crash
	delete subject;
	std::cout << "DONE! " << " =====================================\n";


	//Check
	observer1->PrintNeighbours();
	observer2->PrintNeighbours();
	//observer3->PrintNeighbours();
	//observer4->PrintNeighbours();
	observer5->PrintNeighbours();
	std::cin.get();
	thread.join();
	


	
	
}