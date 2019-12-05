/*
********************************************
Rommulluss Caraiman------------------------*
19/10/2019---------------------------------*
Project: Observer Pattern------------------*
File: ObserverPattern.h--------------------*
********************************************
*/
//The subject and observer classes are virtual classes that sets up functionality for Observer/Subject pattern.
//The Subject contains a reference to the start of a doubly linked list, where the observers are themselves are nodes in the linked list. Updates occur by traversing through the linked list.
//To allow for Observers to be subscribed to multiple subjects, the observers hold a map where the key is a reference of the subject, and the contents of that key is the doubly linked list variables.
//Observers that unsubscribes itself from a subject is constant time, the node connects its neighbors through accessing and altering the references. 

#pragma once
#include <algorithm>
#include <map>
#include <cassert>
#include <shared_mutex>
#include "SynchronousLog.h"

class Subject;

class Observer
{
private:

struct ObserverPointers
{
	Observer* m_previous=nullptr;
	Observer* m_next=nullptr;
};

protected:
	std::shared_mutex m_mutex;
	std::map<Subject*, ObserverPointers> m_ObserverMap;
public:	
	virtual void Update(Subject* _s) = 0;

	Observer()
	{}
	
	Observer* GetNext(Subject* _s)
	{
		std::shared_lock<std::shared_mutex> lck(m_mutex);

		auto it = m_ObserverMap.find(_s);
		if (it != m_ObserverMap.end())
		{
			return it->second.m_next;
		}		
		return nullptr;
	}
	Observer* GetPrevious(Subject* _s)
	{
		std::shared_lock<std::shared_mutex> lck(m_mutex);

		auto it = m_ObserverMap.find(_s);
		if (it != m_ObserverMap.end())
		{
			return it->second.m_previous;
		}
		return nullptr;
	}
	void SetNext(Subject* _s,Observer* _o)
	{
		std::unique_lock<std::shared_mutex> lck(m_mutex);

		auto it = m_ObserverMap.find(_s);
		if(it!=m_ObserverMap.end())
		{
			it->second.m_next = _o;
		}
		else
		{
			m_ObserverMap.emplace(std::pair<Subject*,ObserverPointers>(_s,ObserverPointers()));
			it = m_ObserverMap.find(_s);
			it->second.m_next = _o;
		}

	}
	void SetPrevious(Subject* _s,Observer* _o)
	{
		std::unique_lock<std::shared_mutex> lck(m_mutex);

		auto it = m_ObserverMap.find(_s);
		if (it != m_ObserverMap.end())
		{
			it->second.m_previous = _o;
		}
		m_ObserverMap.emplace(std::pair<Subject*, ObserverPointers>(_s, ObserverPointers()));
		it = m_ObserverMap.find(_s);
		it->second.m_previous = _o;
	}
	void RemoveObserverPointers(Subject* _o)
	{
		auto it = m_ObserverMap.find(_o);
		if (it != m_ObserverMap.end())
			m_ObserverMap.erase(it);
	}
	
	
	~Observer()
	{	
		std::unique_lock<std::shared_mutex> lck(m_mutex);

		auto it = m_ObserverMap.begin();
		
		while(it!=m_ObserverMap.end())
		{
			
			if (it->second.m_next != nullptr && it->second.m_previous != nullptr)
			{
				it->second.m_previous->SetNext(it->first, nullptr);
				it->second.m_next->SetPrevious(it->first, nullptr);
			}

			else if (it->second.m_previous != nullptr)
				it->second.m_previous->SetNext(it->first, nullptr);

			else if (it->second.m_next != nullptr)
				it->second.m_next->SetPrevious(it->first, nullptr);
			it++;
		}
	}
};
class Subject
{
private:
	std::shared_mutex m_mutex;
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
	}
public:
	Subject()
	:m_ObserverLinkedList(nullptr)	{}

	Observer* GetObserverLinkedList()
	{
		std::shared_lock<std::shared_mutex> lck(m_mutex);
		return this->m_ObserverLinkedList;
	}

	void SubscribeObserver(Observer* _o)
	{
		std::unique_lock<std::shared_mutex> lck(m_mutex);
		if(m_ObserverLinkedList==nullptr) //start check
		{
			m_ObserverLinkedList = _o;
			return;
		}

		auto observer = m_ObserverLinkedList;	

		while(observer->GetNext(this)!=nullptr && observer->GetNext(this)!=_o)
			observer = observer->GetNext(this);
		if (observer->GetNext(this) == _o)
		{
			T_TRACE("Tried to subscribe an already subscribed observer.\n");

			return;
		}

		observer->SetNext(this, _o);	
		observer->GetNext(this)->SetPrevious(this,observer);
	}
	void UnsubscribeObserver(Observer* _o)
	{
		std::unique_lock<std::shared_mutex> lck(m_mutex);

		if(m_ObserverLinkedList==nullptr) //No subscribers check
			return;
		if (m_ObserverLinkedList == _o)//Start node check
		{
			if (m_ObserverLinkedList->GetNext(this) != nullptr)
			{
				m_ObserverLinkedList->GetNext(this)->SetPrevious(this, nullptr);
				m_ObserverLinkedList = m_ObserverLinkedList->GetNext(this);
			}
			_o->SetNext(this, nullptr);
			_o->SetPrevious(this, nullptr);
			return;
		}

		//if node is further down the linked list
		auto observer = m_ObserverLinkedList;
		while(observer->GetNext(this) != _o && observer->GetNext(this)!=nullptr)//search for observer node
			observer = observer->GetNext(this);

		if (observer->GetNext(this) != _o)//check if node is NOT found
		{
			T_TRACE("Observer not subscribed\n");
			return;
		}

		observer = observer->GetNext(this);

		if(observer->GetPrevious(this)!=nullptr && observer->GetNext(this)!=nullptr) //node with valid neighbors
		{
			observer->GetPrevious(this)->SetNext(this, observer->GetNext(this));
			observer->GetNext(this)->SetPrevious(this, observer->GetPrevious(this));
		}
		else if(observer->GetPrevious(this)!=nullptr) //if end node
		{
			observer->GetPrevious(this)->SetNext(this,nullptr);
		}	

		observer->RemoveObserverPointers(this);
		
	}
	~Subject()
	{
		std::unique_lock<std::shared_mutex> lck(m_mutex);

		while(m_ObserverLinkedList->GetNext(this)!=nullptr)
		{
			m_ObserverLinkedList = m_ObserverLinkedList->GetNext(this);
			m_ObserverLinkedList->GetPrevious(this)->SetNext(this, nullptr);
			m_ObserverLinkedList->SetPrevious(this,nullptr);
		}
		m_ObserverLinkedList->SetPrevious(this,nullptr);
	}
};