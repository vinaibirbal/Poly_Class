#include "PriorityTask.h"
#include <iostream>
#include <cmath>
#include <unistd.h>
using namespace std;

bool TaskQueue::enqueue(const Task &t) 
{
	if(tp == nullptr || t.daysTillDue < 0) 
	{
	return false;
	}

    Node *prev;
    Node *next;
    Node *New = new Node;
    New->task.type = t.type;
    New->task.daysTillDue = t.daysTillDue;
    New->_dueDate = _currentDay + t.daysTillDue;

    if(t.description == nullptr) 
	{    
        New->task.description = nullptr;
    } 
	else 
	{
        int length = 0;                 
        char* c = t.description;  
        while(*c != 0) 
		{ 
            length++;
            c++;
        }

        char* description = new char[length];
        if(description == nullptr) 
		{
            delete New;
            return false;
        }

        New->task.description = description;
        char* d = desecription;
        c = t.description;
        while(*c != '\0') 
		{
            *d++ = *c++;
        }
	}

    New->task.taskID = t.taskID; 
    New->next = nullptr;

    if(_tHead == nullptr) 
	{
        _tHead = tp;
        return true;
    }
    prev = nullptr;
    next = _tHead;
    while(next != nullptr) 
	{
        if(next->_dueDate > tp->_dueDate)
			{
            if(prev == nullptr) 
			{
                New->next = _tHead;
                New->_dueDate = _currentDay + tp->task.daysTillDue;
                _tHead = tp;
                return true;
            } 
			else
				{
                prev->next = tp;
                tp->next = next;
                return true;
            }
        }
        prev = next;
        next = next->next;
    }
    prev->next = New;

    return true;
}

Task *TaskQueue::dequeue() 
{
    Node *New = _tHead;
    if(tp != nullptr) 
	{
        _tHead = New->next;
        _currentDay = New->_dueDate;
        New->task.daysTillDue = 0;
        return &New->task;
    }
    return nullptr;
}

const Task *TaskQueue::peek() const 
{
    return &_tHead->task;
}

const Task *TaskQueue::next(const Task::TaskType &t) const 
{
    Node* New = _tHead;
    while(New != nullptr) 
	{
        if(New->task.type == t) 
		{
            New->task.daysTillDue = tp->_dueDate - _currentDay;
            return &tp->task;
        }
        New = New->next;
    }
    return nullptr;

}

bool TaskQueue::remove(const taskID& t) 
{
  
    return false;
}

bool TaskQueue::isEmpty() const {
    if(_tHead == nullptr) {
        return true;
    }
    return false;
}


////////////////////////////////////////////
TaskQueue::TaskQueue() {
    _currentDay = 0;
    _tHead = nullptr;
}

TaskQueue::~TaskQueue()
{
    while(!isEmpty())
		{
        remove(_tHead->task.taskID);
    }
}

