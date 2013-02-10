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
     int getPriority();
     time_t getEndDate();
     TaskState getState();
     std::string getDescription();

    /** SETTERS **/
     void setPriority(int p);
     void setEndDate(time_t d);
     void setState(TaskState s);
     void setDescription(std::string desc);

     /** METHODS **/
     void print();

private:

};

#endif // TASK_H
