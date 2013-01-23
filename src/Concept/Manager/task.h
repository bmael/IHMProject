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

     int getPriority();
     time_t getEndDate();
     TaskState getState();

     void setPriority(int p);
     void setEndDate(time_t d);
     void setState(TaskState s);

private:

};

#endif // TASK_H
