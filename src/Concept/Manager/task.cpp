/* *****************************************************************************
 * File task.cpp
 * Project TaskManager
 * Mael BARBIN - JULIEN Bizeul
 * M1 ALMA - Université de Nantes
 * 2012-2013
 ******************************************************************************/

#include "task.h"
#include <iostream>

Task::Task(){}

Task::Task(std::string desc)
{
    this->description_ = desc;
}

Task::~Task()
{
}

int Task::getPriority()
{
    return this->priority_;
}

time_t Task::getEndDate()
{
    return this->endDate_;
}

TaskState Task::getState()
{
    return this->state_;
}

std::string Task::getDescription()
{
    return this->description_;
}

void Task::setPriority(int p)
{
    this->priority_ = p;
}

void Task::setEndDate(time_t d)
{
    this->endDate_ = d;
}

void Task::setState(TaskState s)
{
    this->state_ = s;
}

void Task::setDescription(std::string desc)
{
    this->description_ = desc;
}

void Task::print()
{
    std::cout << "- " << this->description_ << std::endl;
}




