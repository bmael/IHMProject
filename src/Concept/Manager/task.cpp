/* *****************************************************************************
 * File task.cpp
 * Project TaskManager
 * Mael BARBIN - JULIEN Bizeul
 * M1 ALMA - Université de Nantes
 * 2012-2013
 ******************************************************************************/

#include "task.h"
#include <iostream>

Task::Task()
{
    this->priority_ = 0;
    this->state_ = TODO;
}

Task::Task(std::string desc)
{
    this->description_ = desc;
    this->priority_ = 0;
    this->state_ = TODO;
}

Task::~Task()
{}

TaskComponentType Task::getType() const
{
    return TASK;
}

void Task::print(int depth) const
{

    int tmp = 0;
    while(tmp != depth){
         std::cout << "\t";
         tmp++;
     }
    std::cout << "\t|-";
    std::cout << " Type : task [" << this->priority_ << "] (" << this->endDate_ << ")" << this->description_ << " : ";
    this->state_ ? std::cout << "DONE" << std::endl : std::cout << "TODO" << std::endl;
}

