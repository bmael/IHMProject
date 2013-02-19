/* *****************************************************************************
 * File tasklist.h
 * Project Moustache
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
    std::deque<TaskComponent*> * getTasksReference();
    TaskComponentType getType() const;
    TaskComponent* getComponent(unsigned long int pos);
    bool getIsOrdered() const;

    /** SETTERS **/
    void setIsOrdered(bool ordered);

    /** METHODS **/
    void print(int depth = 0) const;

    void add(TaskComponent *component);             // Add a component to the list
    void insert(TaskComponent *component, int pos); // Insert a component into the list
    void remove(TaskComponent *component);          // Remove a component from the list


private:
    std::deque<TaskComponent*> tasks_;
    bool isOrdered_;
};

#endif // TASKLIST_H
