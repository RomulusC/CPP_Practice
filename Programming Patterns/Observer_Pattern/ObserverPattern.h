/*
********************************************
Rommulluss Caraiman------------------------*
19/10/2019---------------------------------*
Project: Observer Pattern------------------*
File: ObserverPattern.h--------------------*
********************************************
*/

#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
class Sync_out
{
	std::mutex m_mutex;
public:
	void operator<<(std::string sss)
	{
		std::scoped_lock lck(m_mutex);
		std::cout << sss;
		
	}
};
Sync_out sync_out;
class Subject;
class Observer
{
private:
protected:
	std::vector<Subject*> m_SubscribedSubjects;
	virtual void Destruction() = 0; //THIS IS REQUIRED TO UNSUBSCRIBE ON DELETION. CANNOT BE DONE IN LOCAL DESTRUCTOR BECAUSE CLASS SUBJECT MUST BE FULLY DEFINED
public:
	virtual void Update(Subject* s) = 0;
	void SubscriptionComplete(Subject* _s)
	{
		m_SubscribedSubjects.emplace_back(_s);
	}
	virtual void SubjectDestroyed(Subject* _o) = 0;//THIS IS REQUIRED TO NOTIFY SUBJECT OBJECT DELETION. CANNOT BE DONE IN LOCAL DESTRUCTOR BECAUSE CLASS SUBJECT MUST BE FULLY DEFINED
	~Observer()
	{
		std::stringstream ss;
		ss << "OBSERVER DESTRUCTOR: Deleted!\n";
		sync_out << ss.str();

	}
};
class Subject
{
private:
	std::mutex mm_mutex;

protected:
	std::vector<Observer*> m_observerList;
	void UpdateObservers()
	{
		std::scoped_lock<std::mutex> lck(mm_mutex);
		auto it = m_observerList.begin();
		while (it != m_observerList.end())
		{
			(*it)->Update(this);
			it++;
		}
		std::stringstream ss;
		ss << "---------------------------------------------\n";
		sync_out << ss.str();
	}
public:
	void SubscribeObserver(Observer* _o)
	{
		std::scoped_lock<std::mutex> lck(mm_mutex);

		if (std::find(m_observerList.begin(), m_observerList.end(), _o) == m_observerList.end())
		{
			m_observerList.emplace_back(_o);
			_o->SubscriptionComplete(this);
		}
	}
	void UnsubscribeObserver(Observer* _o)
	{
		std::scoped_lock<std::mutex> lck(mm_mutex);

		auto it = std::find(m_observerList.begin(), m_observerList.end(), _o);
		if (it != m_observerList.end())
		{
			m_observerList.erase(it);
		}
	}
	~Subject()
	{
		std::scoped_lock<std::mutex> lck(mm_mutex);
		std::stringstream ss;
		for (auto it : m_observerList)
			it->SubjectDestroyed(this);
		ss << "SUBJECT DESTRUCTOR: Deleted!\n";
		sync_out << ss.str();
	}
};