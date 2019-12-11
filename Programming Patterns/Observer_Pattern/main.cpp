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
#include <shared_mutex>

#include "Instrumentation.cpp"
#include "SynchronousLog.cpp"

#define OBSERVER_PATTERN 0
#if OBSERVER_PATTERN

#include "ObserverPattern.cpp"
class AtomicTime : public Subject
{
private:
	
	long long m_msDelay;	

	bool stop;
	bool init; 

	std::thread m_thread;

	void Tick()
	{
		while (stop == false)
		{
			{
				PROFILE_FUNCTION();

				m_msDelay += 50;
				if (m_msDelay > 1000)
					m_msDelay = 200;
				std::this_thread::sleep_for((std::chrono::milliseconds)m_msDelay);
				UpdateObservers();
				C_TRACE("---------------------------------------------");				
			}
		}
	}

public:
	long long GetDelay()
	{
		return m_msDelay;
	}
	AtomicTime(long long delay)
		:init(false), stop(false), m_msDelay(delay) {}	

	~AtomicTime()
	{
		if(!stop)
			Stop();
	}
	void Start()
	{
		m_thread = std::thread(&AtomicTime::Tick, this);
	}
	void Stop()
	{
		PROFILE_FUNCTION();

		stop = true;
		m_thread.join();
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
		PROFILE_FUNCTION();

		std::unique_lock<std::shared_mutex> lk(m_mutex);
		AtomicTime* target = static_cast<AtomicTime*>(s);

		auto in_time_t = std::chrono::system_clock::to_time_t(std::chrono::time_point<std::chrono::system_clock>(std::chrono::system_clock::now()));
		struct tm startInfo;
		localtime_s(&startInfo, &in_time_t);
		T_TRACE("Observer ID: %d Time: [%d:%d:%d] Delay: %dms" , thisId, startInfo.tm_hour, startInfo.tm_min, startInfo.tm_sec, target->GetDelay());
	}
	unsigned int GetID()
	{
		return this->thisId;
	}	
	void PrintNeighbours()
	{
		PROFILE_FUNCTION();

		std::unique_lock<std::shared_mutex> lk(m_mutex);
		T_TRACE("LocalClock ID: %u " , this->GetID());
		
		auto it = m_ObserverMap.begin();
		if (it == m_ObserverMap.end())
		{
			T_TRACE("NO SUBSCRIPTIONS!");
		}
		for (auto it : m_ObserverMap)
		{
			C_TRACE("Subject object: 0x%x\nPrevious ID: 0x%x\nNext ID: 0x%x" , it.first , it.second.m_previous, it.second.m_next );
		}
	}
};
void PrintSubscribedObservers(AtomicTime* _s) //concrete type specific
{
	PROFILE_FUNCTION();

	T_TRACE("Printing out subscriptions. ----------------------");

	Observer* current = _s->GetObserverLinkedList();
	if (current == nullptr)
	{
		T_TRACE("No Subscriptions");
		return;
	}
	while (current != nullptr)

	{
		T_TRACE("OBSERVER ID: %d" , static_cast<LocalClock*>(current)->GetID());
		current = current->GetNext(_s);
	}
}

unsigned int LocalClock::count = 0;	
	
int main()
{
	PROFILE_BEGIN_SESSION("main_scope","profiling.json");
	
	using namespace std::chrono_literals;
	LogThreadStart_(15ms);
	{
		C_TRACE("The Observer Pattern.\n");
		C_TRACE("The AtomicTime object (the subject) runs on it's own thread keeping time duration,");
		C_TRACE("updates any objects (observers) that have subscribed to the subject over a period of time.");
		C_TRACE("Three observers will be subscribed to one subject in this demonstration.");
		C_TRACE("Press any key to start.\n");
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

		subject->Start();
		std::this_thread::sleep_for(3s);

		subject->UnsubscribeObserver(observer1);
		T_TRACE("UNSUBSCRIBED: %u", observer1->GetID());

		delete observer3;
		T_TRACE("DELETED: %u", 3);

		delete observer4;
		T_TRACE("DELETED: %u", 4);

		PrintSubscribedObservers(subject);

		T_TRACE("PRESS TO DELETE SUBJECT!");

		std::cin.get();
		subject->SubscribeObserver(observer5);
		//Check
		observer1->PrintNeighbours();//unsubscribed, no neighbors
		observer2->PrintNeighbours();//subscribed

		observer5->PrintNeighbours();//resubscribed
		delete subject;
		T_TRACE("SUBJECT DELETED!");
		//Check
		observer1->PrintNeighbours();
		observer2->PrintNeighbours();
		observer5->PrintNeighbours();

		LogThreadStop_(); // this can go at end of scope
		customLog::SyncOut::Instance().PrintBufferReset();
		{
			PROFILE_SCOPE("TEST_SPAM!_1");
			for (int i = 0; i < 50; i++)
				T_TRACE("TEST_SPAM!");
			customLog::SyncOut::Instance().PrintBufferReset();
		}
		{
			PROFILE_SCOPE("TEST_SPAM!_2");
			for (int i = 0; i < 50; i++)
			{
				T_TRACE("TEST_SPAM!");
				PrintBufferReset_();
			}
		}
		{
			PROFILE_SCOPE("PRINTF_SPAM!");
			for (int i = 0; i < 50; i++)
			{
				printf("TEST_SPAM!");
			}
		}


		LogThreadStart_(15ms);
	}	
	LogThreadStop_(); // this can go at end of scope
	PROFILE_END_SESSION();
	std::cin.get();
}
#else

// testing
int main()
{
	//TODO:
	// Fix writing to .json too fast, buffer it first
	// Actually have a const char* double buffer rather than a double buffer container of strings

	PROFILE_BEGIN_SESSION("main_scope", "profiling.json");

	{
		PROFILE_SCOPE("TEST_SPAM!_1");
		for (int i = 0; i < 50; i++)
			T_TRACE("TEST_SPAM!");
		customLog::SyncOut::Instance().PrintBufferReset();
	}
	{
		PROFILE_SCOPE("TEST_SPAM!_2");
		for (int i = 0; i < 50; i++)
		{
			T_TRACE("TEST_SPAM!");
			PrintBufferReset_();
		}
	}
	{
		PROFILE_SCOPE("PRINTF_SPAM!");
		for (int i = 0; i < 50; i++)
		{
			printf("TEST_SPAM!\n");
		}
		
	}
	{
		PROFILE_SCOPE("std::cout_SPAM!");
		for (int i = 0; i < 50; i++)
		{
			std::cout << "TEST_SPAM!\n";
		}
	}

	PROFILE_END_SESSION();

	std::cin.get();
}
#endif