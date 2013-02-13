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

TaskList::TaskList(const TaskList &tl) : TaskComponent(tl),tasks_(tl.getTasks())
{
}

TaskList::TaskList()
{
    this->priority_ = 0;
}

TaskList::TaskList(std::string description)
{
    this->description_ = description;
    this->priority_ = 0;
}

TaskList::~TaskList(){}

std::deque<TaskComponent*> TaskList::getTasks() const
{
    return this->tasks_;
}

TaskComponentType TaskList::getType() const
{
    return TASKLIST;
}

TaskComponent *TaskList::getComponent(unsigned long pos)
{
    return this->tasks_.at(pos);
}

void TaskList::add(TaskComponent * component)
{
    this->tasks_.push_back(component);
}

void TaskList::insert(TaskComponent *component, int pos)
{
    this->tasks_.insert(this->tasks_.begin() + pos, component);
}

void TaskList::remove(TaskComponent * component)
{
    std::deque<TaskComponent *>::iterator itr = find(this->tasks_.begin(),
                                                    this->tasks_.end(),
                                                    component);
    if( itr != this->tasks_.end())
    {
        this->tasks_.erase(itr);
    }
}


void TaskList::print(int depth) const
{
    std::deque<TaskComponent*>::const_iterator itb = this->tasks_.begin();
    const std::deque<TaskComponent*>::const_iterator ite = this->tasks_.end();

    int tmp = 0;
    while(tmp != depth){
        std::cout << "\t";
        tmp++;
    }
    std::cout << "|-";
    std::cout << " ["<< this->getPriority() << "][" << this->getDescription()<< "]" << std::endl;

    while(itb != ite ){
        if((*itb)->getType() == TASK) (*itb)->print(depth);
        else {
            depth ++;
            (*itb)->print(depth);
        }
        ++itb;
    }
}



