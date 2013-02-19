/* *****************************************************************************
 * File taskcomponent.h
 * Project Moustache
 * Mael BARBIN - JULIEN Bizeul
 * M1 ALMA - Université de Nantes
 * 2012-2013
 ******************************************************************************/

#ifndef TASKCOMPONENT_H
#define TASKCOMPONENT_H

#include <ctime>
#include <string>

enum TaskState { TODO, DONE };
enum TaskComponentType {TASK, TASKLIST};

class TaskComponent
{
public:

    /** GETTERS **/
     int getPriority() const;
     std::string getEndDate() const;
     TaskState getState() const;
     std::string getDescription() const;
     virtual TaskComponentType getType() const =0;

     /** SETTERS **/
     void setPriority(int p);
     void setEndDate(std::string d);
     void setState(TaskState s);
     void setDescription(std::string desc);

     /** METHODS **/
    virtual void print(int depth = 0) const =0; // Print a component on the standard output


protected:
    int priority_;
    std::string endDate_;
    TaskState state_;
    std::string description_;

};

#endif // TASKCOMPONENT_H
