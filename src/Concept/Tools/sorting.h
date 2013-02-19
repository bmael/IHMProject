/*******************************************************************************
 * File sorting.h
 * Project Moustache
 * Mael BARBIN - JULIEN Bizeul -
 * M1 ALMA - Université de Nantes
 * 2012-2013
 * ******************************************************************************/

#ifndef SORTING_H
#define SORTING_H

#include "Manager/task.h"
#include "Manager/tasklist.h"

/**
 * @brief Sorts a task list according to the priority of its tasks.
 * A priority near 10 is lesser important than a priority near 0 for a taskcomponent.
 * @param list the list to sort.
 * @return res the TaskList corresponding to list sorted.
 */
void sorting(TaskList * list);

#endif // SORTING_H
