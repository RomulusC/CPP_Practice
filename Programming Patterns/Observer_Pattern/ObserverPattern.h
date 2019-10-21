/*
********************************************
Rommulluss Caraiman------------------------*
19/10/2019---------------------------------*
Project: Observer Pattern------------------*
File: ObserverPattern.h--------------------*
********************************************
*/

#pragma once
#include <iostream>
#include <algorithm>
#include <map>
#include <cassert>
#include <mutex>

class Subject;

class Observer
{
private:

struct SubscriptionType
{
	Observer* m_previous;
	Observer* m_next;
};

protected:
	std::mutex m_mutex;
	std::map<Subject*,SubscriptionType> m_ObserverMap;
public:	
	Observer()
	{}
		
	Observer* GetNext(Subject* _s)
	{
		std::unique_lock<std::mutex> lck(m_mutex);

		auto it = m_ObserverMap.find(_s);
		if (it != m_ObserverMap.end())
		{
			return it->second.m_next;
			lck.unlock();
		}
		
		lck.unlock();
		return nullptr;
	}
	Observer* GetPrevious(Subject* _s)
	{
		std::unique_lock<std::mutex> lck(m_mutex);

		auto it = m_ObserverMap.find(_s);
		if (it != m_ObserverMap.end())
		{
			lck.unlock();
			return it->second.m_previous;
		}
		lck.unlock();
		return nullptr;
	}
	bool SetNext(Subject* _s,Observer* _o)
	{
		std::unique_lock<std::mutex> lck(m_mutex);

		auto it = m_ObserverMap.find(_s);
		if(it!=m_ObserverMap.end())
		{
			it->second.m_next = _o;
			lck.unlock();
			return true;
		}		
		lck.unlock();
		return false;
	}
	bool SetPrevious(Subject* _s,Observer* _o)
	{
		std::unique_lock<std::mutex> lck(m_mutex);

		auto it = m_ObserverMap.find(_s);
		if(it!=m_ObserverMap.end())
		{
			it->second.m_previous = _o;
			lck.unlock();
			return true;
		}		
		lck.unlock();
		return false;
	}
	
	virtual void Update(Subject* _s) = 0;
	
	~Observer()
	{	
		std::unique_lock<std::mutex> lck(m_mutex);

		auto it = m_ObserverMap.begin();
		
		while(it!=m_ObserverMap.end())
		{
			Observer* current = this;
			if(current->GetPrevious(it->first)!=nullptr && current->GetNext(it->first)!=nullptr)
			{
				current->GetPrevious(it->first)->SetNext(it->first,current->GetNext(it->first));
				current->GetNext(it->first)->SetPrevious(it->first,current->GetPrevious(it->first));
			}
			else if(current->GetPrevious(it->first)!=nullptr)
			{
				current->GetPrevious(it->first)->SetNext(it->first, nullptr);
			}
			else if(current->GetNext(it->first)!=nullptr)
			{
				current->SetNext(it->first, nullptr);
			}
		//remove from final testing
		this->SetNext(it->first,nullptr);
		this->SetPrevious(it->first,nullptr);
		//
		it++;
		}
		lck.unlock();
		std::cout << "OBSERVER DESTRUCTOR: Deleted!\n";
	}
};
class Subject
{
private:

protected:
	Observer* m_ObserverLinkedList;
	void UpdateObservers()
	{
		auto observer = m_ObserverLinkedList;
		while(observer!=nullptr)
		{
			observer->Update(this);
			observer = observer->GetNext(this);
		}
		std::cout << "---------------------------------------------\n";
	}
public:
	Subject()
	:m_ObserverLinkedList(nullptr)	{}

	void SubscribeObserver(Observer* _o)
	{
		if(m_ObserverLinkedList==nullptr) //start check
		{
			m_ObserverLinkedList = _o;
			return;
		}

		auto observer = m_ObserverLinkedList;	

		while(observer->GetNext(this)!=nullptr)
			observer = observer->GetNext(this);

		observer->SetNext(this, _o);	
		observer->GetNext(this)->SetPrevious(this,observer);
	}
	void UnsubscribeObserver(Observer* _o)
	{
		if(m_ObserverLinkedList==nullptr) //start check
			return;
		
		auto observer = m_ObserverLinkedList;
		while(observer!= _o||observer->GetNext(this)!=nullptr)//search for observer node
			observer = observer->GetNext(this);

		if(observer!=_o)//check if node is found
			return;		

		if(observer->GetPrevious(this)!=nullptr&& observer->GetNext(this)!=nullptr)
		{
			observer->GetPrevious(this)->SetNext(this, observer->GetNext(this));
			observer->GetNext(this)->SetPrevious(this, observer->GetPrevious(this));
		}
		else if(observer->GetPrevious(this)!=nullptr) //if end node
		{
			observer->GetPrevious(this)->SetNext(this,nullptr);
		}
		else if(observer->GetNext(this)!=nullptr) //if start node
		{
			m_ObserverLinkedList = nullptr;
		}
		

		observer->SetNext(this, nullptr);
		observer->SetPrevious(this,nullptr);
		
		
	}
	~Subject()
	{
		//assert(m_ObserverLinkedList->GetPrevious(this)!=nullptr);//before
		while(m_ObserverLinkedList->GetNext(this)!=nullptr)
		{
			m_ObserverLinkedList = m_ObserverLinkedList->GetNext(this);
			m_ObserverLinkedList->GetPrevious(this)->SetNext(this, nullptr);
			m_ObserverLinkedList->SetPrevious(this,nullptr);
		}
		m_ObserverLinkedList->SetPrevious(this,nullptr);
		//assert(m_ObserverLinkedList->GetNext(this)!=nullptr);//after

		std::cout << "SUBJECT DESTRUCTOR: Deleted!\n";
	}
};