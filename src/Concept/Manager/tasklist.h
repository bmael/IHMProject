/* *****************************************************************************
 * File tasklist.h
 * Project TaskManager
 * Mael BARBIN - JULIEN Bizeul
 * M1 ALMA - Université de Nantes
 * 2012-2013
 ******************************************************************************/

#ifndef TASKLIST_H
#define TASKLIST_H

#include "taskcomponent.h"
#include <list>

class TaskList : public TaskComponent
{
public:
    TaskList();
    TaskList(std::string description);
    virtual ~TaskList();

    /** GETTERS **/
    int getPriority();
    time_t getEndDate();
    TaskState getState();
    std::string getDescription();
    std::list<TaskComponent*> getTasks();

    /** SETTERS **/
    void setPriority(int p);
    void setEndDate(time_t d);
    void setState(TaskState s);
    void setDescription(std::string desc);
    void setTasks(std::list<TaskComponent*> li);

    /** METHODS **/
    void print();

    void add(TaskComponent *component);
    void remove(TaskComponent *component);



private:
    std::list<TaskComponent*> tasks_;
};

#endif // TASKLIST_H
