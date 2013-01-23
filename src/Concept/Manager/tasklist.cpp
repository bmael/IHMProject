/* *****************************************************************************
 * File tasklist.h
 * Project TaskManager
 * Mael BARBIN - JULIEN Bizeul
 * M1 ALMA - Université de Nantes
 * 2012-2013
 ******************************************************************************/

#include "tasklist.h"
#include <algorithm>
#include <iostream>


TaskList::TaskList(std::string description)
{
    this->description_ = description;
}

TaskList::~TaskList()
{
}

int TaskList::getPriority()
{
    return this->priority_;
}

time_t TaskList::getEndDate()
{
    return this->endDate_;
}

TaskState TaskList::getState()
{
    return this->state_;
}

std::string TaskList::getDescription()
{
    return this->description_;
}

void TaskList::setPriority(int p)
{
    this->priority_ = p;
}

void TaskList::setEndDate(time_t d)
{
    this->endDate_ = d;
}

void TaskList::setState(TaskState s){
    this->state_ = s;
}

void TaskList::setDescription(std::string desc)
{
    this->description_ = desc;
}

void TaskList::add(TaskComponent * component)
{
    this->tasks_.push_back(component);
}

void TaskList::remove(TaskComponent * component)
{
    std::list<TaskComponent *>::iterator itr = find(this->tasks_.begin(),
                                                    this->tasks_.end(),
                                                    component);
    if( itr != this->tasks_.end())
    {
        this->tasks_.erase(itr);
    }
}


void TaskList::print()
{
    std::cout << "[" << this->description_ << "]" << std::endl;
    std::for_each(tasks_.begin(), tasks_.end(), std::mem_fun(&TaskComponent::print));
}
