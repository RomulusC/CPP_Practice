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
		std::cout << "Observer Deleted!\n";

	}	
};
class Subject
{
protected:
	std::vector<Observer*> m_observerList;

	void UpdateObservers()
	{
		auto it = m_observerList.begin();
		while (it != m_observerList.end())
		{
			(*it)->Update(this);
			it++;
		}
		std::cout << "---------------------------------------------\n";
	}
public:
	void SubscribeObserver(Observer* _o)
	{
		if (std::find(m_observerList.begin(), m_observerList.end(), _o) == m_observerList.end())
		{
			m_observerList.emplace_back(_o);
			_o->SubscriptionComplete(this);
		}
	}
	void UnsubscribeObserver(Observer* _o)
	{
		auto it = std::find(m_observerList.begin(), m_observerList.end(), _o);
		if (it != m_observerList.end())
		{
			m_observerList.erase(it);
		}
	}	
	~Subject()
	{
		for (auto it : m_observerList)
			it->SubjectDestroyed(this);
		std::cout << "Subject Deleted!\n";			
	}
};