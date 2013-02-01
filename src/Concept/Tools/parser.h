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

#include "../../lib/pugixml_sources/pugixml.hpp"
#include "../Manager/task.h"
#include "../Manager/tasklist.h"

/**
 * @brief Parses an xml and creates the TaskList according to this xml file.
 * @param file_path the path for the xml file to parse
 * @return res the tasklist result of the parsing
 */
TaskList * parse(const char * file_path);

#endif // PARSER_H
