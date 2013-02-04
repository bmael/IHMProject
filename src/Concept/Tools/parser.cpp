/*******************************************************************************
 * File parser.cpp
 * Project TaskManager
 * Mael BARBIN - JULIEN Bizeul -
 * M1 ALMA - Université de Nantes
 * 2012-2013
 * ******************************************************************************/

#include "parser.h"

#include <iostream>
#include <cstring>

TaskList * parse(const char * file_path){
    TaskList *res = new TaskList();
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(file_path);

    if(result){

        pugi::xml_node mainTaskList = doc.child("tasklist");
        res->setDescription(mainTaskList.child("title").text().as_string());
        parseTaskList(mainTaskList, res);

//        for(pugi::xml_node child = mainTaskList.first_child();
//            child;
//            child = child.next_sibling())
//        {
//            if(std::strcmp(child.name(), "title") == 0 ) res->setDescription((std::string)child.text().as_string());

//            if(std::strcmp(child.name(), "tasklist") == 0){
//                // call method for taskList
//            }

//            if(std::strcmp(child.name(), "task") == 0){
//                res->add(parseTask(child));
//            }


//        }



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

//    // There are only task to add to the current tasklist
//    if(endOfBranch(tasklistnode)){
//        std::cout << "this is the end of a branch" << std::endl;
//        for(pugi::xml_node child = tasklistnode.first_child();
//            child;
//            child = child.next_sibling())
//        {
//            list->add(parseTask(child));
//        }
//        return list;
//    }else{
//        for(pugi::xml_node child = tasklistnode.first_child();
//                    child;
//            child = child.next_sibling("task"))
//        {
//            list->add(parseTask(child));
//        }
//        for(pugi::xml_node child = tasklistnode.first_child();
//                    child;
//            child = child.next_sibling("tasklist"))
//        {
////            TaskList * tmp = new TaskList();
//            list->setDescription(child.child("title").text().as_string());
//            list->add(parseTaskList(child, list));
//        }

//    }
    for(pugi::xml_node child = tasklistnode.first_child();
        child;
        child = child.next_sibling())
    {
        if(std::strcmp(child.name(), "tasklist") == 0) {
            TaskList * toAdd = new TaskList();
            list->add(parseTaskList(child,toAdd));

        }
        if(std::strcmp(child.name(), "title") == 0) list->setDescription(child.text().as_string());
        if(std::strcmp(child.name(), "task") == 0) list->add(parseTask(child));
    }
    return list;

}

bool endOfBranch(pugi::xml_node branchnode){
   return branchnode.children().end() == branchnode.children().begin();
}

