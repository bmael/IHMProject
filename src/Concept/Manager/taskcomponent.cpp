/* *****************************************************************************
 * File taskcomponent.cpp
 * Project Moustache
 * Mael BARBIN - JULIEN Bizeul
 * M1 ALMA - Université de Nantes
 * 2012-2013
 ******************************************************************************/
#include "taskcomponent.h"

/**
 * @brief Getter for priority attribute
 * @return priority
 */
int TaskComponent::getPriority() const
{
    return this->priority_;
}

/**
 * @brief Getter for endDate attribute
 * @return endDate
 */
std::string TaskComponent::getEndDate() const
{
    return this->endDate_;
}

/**
 * @brief Getter for state attribute
 * @return state
 */
TaskState TaskComponent::getState() const
{
    return this->state_;
}

/**
 * @brief Getter for description attribute
 * @return description
 */
std::string TaskComponent::getDescription() const
{
    return this->description_;
}

/**
 * @brief Setter for priority attribute
 */
void TaskComponent::setPriority(int p)
{
    this->priority_ = p;
}

/**
 * @brief Setter for endDate attribute
 */
void TaskComponent::setEndDate(std::string d)
{
    this->endDate_ = d;
}

/**
 * @brief Setter for state attribute
 */
void TaskComponent::setState(TaskState s)
{
    this->state_ = s;
}

/**
 * @brief Setter for description attribute
 */
void TaskComponent::setDescription(std::string desc)
{
    this->description_ = desc;
}
