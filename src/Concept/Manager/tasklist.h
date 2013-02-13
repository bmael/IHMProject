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
#include <deque>

class TaskList : public TaskComponent
{
public:
    TaskList(const TaskList &tl);
    TaskList();
    TaskList(std::string description);
    virtual ~TaskList();

    /** GETTERS **/
    std::deque<TaskComponent*> getTasks() const;
    TaskComponentType getType() const;
    TaskComponent* getComponent(unsigned long int pos);
    bool getIsOrdered() const;

    /** SETTERS **/
    void setIsOrdered(bool ordered);

    /** METHODS **/
    void print(int depth = 0) const;

    void add(TaskComponent *component);
    void insert(TaskComponent *component, int pos);
    void remove(TaskComponent *component);


private:
    std::deque<TaskComponent*> tasks_;
    bool isOrdered_;
};

#endif // TASKLIST_H
