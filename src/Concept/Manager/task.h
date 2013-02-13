/* *****************************************************************************
 * File task.h
 * Project TaskManager
 * Mael BARBIN - JULIEN Bizeul
 * M1 ALMA - Université de Nantes
 * 2012-2013
 ******************************************************************************/

#ifndef TASK_H
#define TASK_H

#include "taskcomponent.h"


class Task : public TaskComponent
{
public:
    Task();
    Task(std::string desc);
    virtual ~Task();


    /** GETTERS **/
    TaskComponentType getType() const;

     /** METHODS **/
     void print(int depth = 0) const;


};

#endif // TASK_H
