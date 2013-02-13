/*******************************************************************************
 * File parser.cpp
 * Project TaskManager
 * Mael BARBIN - JULIEN Bizeul -
 * M1 ALMA - Université de Nantes
 * 2012-2013
 * ******************************************************************************/

#include "parser.h"
#include "sorting.h"

#include <iostream>
#include <cstring>

TaskList * parse(const char * file_path){
    TaskList *res = new TaskList();

    std::cout << "parser : priority of mainList : " << res->getPriority() << std::endl;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(file_path);

    if(result){
        // if the xml file is open correctly, initializes the main taskList for the recursion.
        pugi::xml_node mainTaskList = doc.child("tasklist");
        res->setDescription(mainTaskList.child("title").text().as_string());
        parseTaskList(mainTaskList, res);

    }
    return res;
}

Task * parseTask(pugi::xml_node tasknode){
    Task * t = new Task();

    if(std::strcmp(tasknode.name(), "task") == 0){
        t->setDescription(tasknode.child("desc").text().as_string());
        t->setPriority(tasknode.child("priority").text().as_int());
    }

    return t;
}

TaskList * parseTaskList(pugi::xml_node tasklistnode, TaskList * list){

    for(pugi::xml_node child = tasklistnode.first_child();
        child;
        child = child.next_sibling())
    {
        if(std::strcmp(child.name(), "tasklist") == 0) {
            TaskList * toAdd = new TaskList();

            toAdd = parseTaskList(child,toAdd);

            if(toAdd->getPriority()!=0 ){

                bool find = false;
                unsigned int pos = 0;

                while(pos < list->getTasks().size() && !find){
                    if(toAdd->getPriority() < list->getComponent(pos)->getPriority()) find = true;
                    else{
                        ++pos;
                    }
                }

                list->insert(toAdd, pos);
            }
            else{
                list->add(toAdd);
            }

        }

        if(std::strcmp(child.name(), "title") == 0) list->setDescription(child.text().as_string());
        if(std::strcmp(child.name(), "priority") == 0) list->setPriority(child.text().as_int());

        if(std::strcmp(child.name(), "task") == 0) {

            Task * t = new Task();
            t = parseTask(child);

            if(t->getPriority()!=0 ){

                bool find = false;
                unsigned int pos = 0;

                while(pos < list->getTasks().size() && !find && t->getPriority()!=0 ){
                    if(t->getPriority() < list->getComponent(pos)->getPriority()) find = true;
                    else{
                        ++pos;
                    }
                }

                list->insert(t,pos);
            }
            else{
                list->add(t);
            }

        }
    }

    return list;

}

