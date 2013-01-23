/* *****************************************************************************
 * File taskcomponent.h
 * Project TaskManager
 * Mael BARBIN - JULIEN Bizeul
 * M1 ALMA - Université de Nantes
 * 2012-2013
 ******************************************************************************/

#ifndef TASKCOMPONENT_H
#define TASKCOMPONENT_H

#include <ctime>
#include <string>

enum TaskState { TODO, DONE };

class TaskComponent
{
public:
    virtual int getPriority() =0;
    virtual time_t getEndDate() =0;
    virtual TaskState getState() =0;
    virtual std::string getDescription() =0;

    virtual void setPriority(int p) =0;
    virtual void setEndDate(time_t d) =0;
    virtual void setState(TaskState s) =0;
    virtual void setDescription(std::string desc) =0;

protected:
    int priority_;
    time_t endDate_;
    TaskState state_;
    std::string description_;

};

#endif // TASKCOMPONENT_H
