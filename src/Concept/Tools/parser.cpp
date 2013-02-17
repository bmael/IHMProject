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
#include <sstream>

TaskList * parse(const char * file_path){
    TaskList *res = new TaskList();

    std::cout << "parser : priority of mainList : " << res->getPriority() << std::endl;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(file_path);

    if(result){
        // if the xml file is open correctly, initializes the main taskList for the recursion.
        pugi::xml_node mainTaskList = doc.child("tasklist");
        res->setDescription(mainTaskList.child("title").text().as_string());
        res->setPriority(mainTaskList.child("priority").text().as_int());
        res->setEndDate(mainTaskList.child("date").text().as_string());
        res->setState((TaskState)mainTaskList.child("state").text().as_int());
        parseTaskList(mainTaskList, res);

    }
    return res;
}

Task * parseTask(pugi::xml_node tasknode){
    Task * t = new Task();

    if(std::strcmp(tasknode.name(), "task") == 0){
        t->setDescription(tasknode.child("desc").text().as_string());
        t->setPriority(tasknode.child("priority").text().as_int());
        t->setEndDate(tasknode.child("date").text().as_string());
        t->setState((TaskState)tasknode.child("state").text().as_int());

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
        if(std::strcmp(child.name(), "date") == 0) list->setEndDate(child.text().as_string());
        if(std::strcmp(child.name(), "state") == 0) list->setState((TaskState)child.text().as_int());


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

void save(TaskList * list, const char * file_path){
    pugi::xml_document doc;

    pugi::xml_node mainTaskList = doc.append_child(pugi::node_element);
    mainTaskList.set_name("tasklist");


    // Initializes the main node
    pugi::xml_node title = mainTaskList.append_child("title");
    title.append_child(pugi::node_pcdata).set_value(list->getDescription().c_str());

    pugi::xml_node priority = mainTaskList.append_child("priority");
    unsigned int priorityvalue = list->getPriority();
    std::stringstream priorityss;
    priorityss << priorityvalue;
    priority.append_child(pugi::node_pcdata).set_value(priorityss.str().c_str());

    pugi::xml_node date = mainTaskList.append_child("date");
    date.append_child(pugi::node_pcdata).set_value(list->getEndDate().c_str());

    pugi::xml_node state = mainTaskList.append_child("state");
    state.append_child(pugi::node_pcdata).set_value(list->getState() ? "1" : "0");

    // Add all others lists and tasks
    int i;
    TaskComponent * c;
    for(i=0; i<list->getTasks().size(); i++){
        c = list->getComponent(i);
        if(c->getType() == TASK) addTask((Task *)c, mainTaskList);
        else addTaskList((TaskList *)c, mainTaskList);
    }

    doc.save_file(file_path);
}

void addTaskList(TaskList * list, pugi::xml_node node){

    pugi::xml_node child = node.append_child("tasklist");

    pugi::xml_node title = child.append_child("title");
    title.append_child(pugi::node_pcdata).set_value(list->getDescription().c_str());

    pugi::xml_node priority = child.append_child("priority");
    unsigned int priorityvalue = list->getPriority();
    std::stringstream priorityss;
    priorityss << priorityvalue;
    priority.append_child(pugi::node_pcdata).set_value(priorityss.str().c_str());

    pugi::xml_node date = child.append_child("date");
    date.append_child(pugi::node_pcdata).set_value(list->getEndDate().c_str());

    pugi::xml_node state = child.append_child("state");
    state.append_child(pugi::node_pcdata).set_value(list->getState() ? "1" : "0");

    int i;
    TaskComponent * c;
    for(i=0; i<list->getTasks().size(); i++){
        c = list->getComponent(i);
        if(c->getType() == TASK) addTask((Task *)c, child);
        else addTaskList((TaskList *)c, child);
    }
}

void addTask(Task * task, pugi::xml_node node){
    pugi::xml_node child = node.append_child("task");

    pugi::xml_node title = child.append_child("desc");
    title.append_child(pugi::node_pcdata).set_value(task->getDescription().c_str());

    pugi::xml_node priority = child.append_child("priority");
    unsigned int priorityvalue = task->getPriority();
    std::stringstream priorityss;
    priorityss << priorityvalue;
    priority.append_child(pugi::node_pcdata).set_value(priorityss.str().c_str());

    pugi::xml_node date = child.append_child("date");
    date.append_child(pugi::node_pcdata).set_value(task->getEndDate().c_str());

    pugi::xml_node state = child.append_child("state");
    state.append_child(pugi::node_pcdata).set_value(task->getState() ? "1" : "0");

}

