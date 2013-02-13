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
}

Task::Task(std::string desc)
{
    this->description_ = desc;
    this->priority_ = 0;
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
    std::cout << " [" << this->priority_ << "] " << this->description_ << std::endl;
}

