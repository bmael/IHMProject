/*******************************************************************************
 * File parser.cpp
 * Project TaskManager
 * Mael BARBIN - JULIEN Bizeul -
 * M1 ALMA - Université de Nantes
 * 2012-2013
 * ******************************************************************************/

#include "parser.h"

TaskList * parse(const char * file_path){
    TaskList *res;
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(file_path);

    if(result){
        pugi::xml_node title = doc.child("tasklist").child("title");
        res->setDescription((std::string)title.value());

    }

    return res;
}
