/*******************************************************************************
 * File sorting.cpp
 * Project Moustache
 * Mael BARBIN - JULIEN Bizeul -
 * M1 ALMA - Université de Nantes
 * 2012-2013
 * ******************************************************************************/

#include "sorting.h"
#include <algorithm>
#include <iostream>
struct Lesser{
    inline bool operator() (TaskComponent * cmp1, TaskComponent * cmp2){

        std::cout << "[Lesser] : called with : " << cmp1->getPriority()
                                        << " < " << cmp2->getPriority() << std::endl;

        bool res = cmp1->getPriority() < cmp2->getPriority();

        res ? std::cout << "[lesser] : res = true" << std::endl :
              std::cout << "[lesser] : res = false" << std::endl ;

        return res;
    }
};

void sorting(TaskList * list){

    //separation of Task and TaskList : we have to sort all task in a taskList
    std::deque<TaskComponent *>::iterator itr;

    for(itr = list->getTasks().begin(); itr != list->getTasks().end(); ++itr)
    {
        if ((*itr)->getType() == TASKLIST){
            std::cout << "List detected : " << std::endl;
            (*itr)->print();
        }
    }

    //list->getTasks().sort(Lesser());
}
