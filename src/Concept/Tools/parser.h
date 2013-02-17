/* *****************************************************************************
 * File parser.h
 * Project TaskManager
 * Mael BARBIN - JULIEN Bizeul
 * M1 ALMA - Université de Nantes
 * 2012-2013
 *
 *  Provides some methods to parse xml file for the TaskManager program
 ******************************************************************************/

#ifndef PARSER_H
#define PARSER_H

#include "../lib/pugixml_sources/pugixml.hpp"
#include "Manager/task.h"
#include "Manager/tasklist.h"

/**
 * @brief Parses an xml and creates the TaskList according to this xml file.
 * @param file_path the path for the xml file to parse
 * @return res the tasklist result of the parsing
 */
TaskList * parse(const char * file_path);

/**
 * @brief Parses a tasklist recursively.
 * @param tasklistnode the xlm node to parse
 * @param list the tasklist where is stored the result of the parsing.
 * @return  a TaskList resulting of the parsing.
 */
TaskList * parseTaskList(pugi::xml_node tasklistnode, TaskList *list);

/**
 * @brief Parses a task.
 * @param tasknode an xml node corresponding to a task.
 * @return the task resulting of the parsing of the xml node.
 */
Task * parseTask(pugi::xml_node tasknode);

/**
 * @brief Save a taskList into the xml file given in parameter. Creates the
 * xml file if does not exist.
 * @param list
 * @param file_path
 */
void save(TaskList * list, const char * file_path);

void addTaskList(TaskList * list, pugi::xml_node node);
void addTask(Task * task, pugi::xml_node node);

#endif // PARSER_H
