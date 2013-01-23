/* *****************************************************************************
 * File tasklist.h
 * Project TaskManager
 * Mael BARBIN - JULIEN Bizeul
 * M1 ALMA - Université de Nantes
 * 2012-2013
 ******************************************************************************/

#include "tasklist.h"
#include <algorithm>


TaskList::TaskList()
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

void TaskList::add(TaskComponent * component)
{
    this->tasks.push_back(component);
}

void TaskList::remove(TaskComponent * component)
{
    std::list<TaskComponent *>::iterator itr = find(this->tasks.begin(),
                                                    this->tasks.end(),
                                                    component);
    if( itr != this->tasks.end())
    {
        this->tasks.erase(itr);
    }
}
