#include "taskcomponent.h"

int TaskComponent::getPriority() const
{
    return this->priority_;
}

time_t TaskComponent::getEndDate() const
{
    return this->endDate_;
}

TaskState TaskComponent::getState() const
{
    return this->state_;
}

std::string TaskComponent::getDescription() const
{
    return this->description_;
}

void TaskComponent::setPriority(int p)
{
    this->priority_ = p;
}

void TaskComponent::setEndDate(time_t d)
{
    this->endDate_ = d;
}

void TaskComponent::setState(TaskState s)
{
    this->state_ = s;
}

void TaskComponent::setDescription(std::string desc)
{
    this->description_ = desc;
}
