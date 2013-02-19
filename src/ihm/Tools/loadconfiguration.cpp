#include "loadconfiguration.h"
#include "configuration.h"
#include <iostream>
#include <sstream>

void readConfig(const char * file_path){
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(file_path);

    std::cout << file_path << std::endl;

    if(result){

        // if the xml file is open correctly
        pugi::xml_node session = doc.child("session");

        //Last tasksList
        pugi::xml_node tasklistpath = doc.child("tasklist");
        Configuration::getInstance()->setTaskListPath(QString::fromStdString(tasklistpath.text().as_string()));

        // Preferences
        pugi::xml_node preferences = session.child("preferences");
        Configuration::getInstance()->setLanguage(preferences.child("language").text().as_int());

    }
}

void saveConfig(const char *file_path){
    pugi::xml_document doc;

    pugi::xml_node session = doc.append_child(pugi::node_element);
    session.set_name("session");

    // Task list
    pugi::xml_node tasklist = session.append_child("tasklist");
    tasklist.append_child(pugi::node_pcdata).set_value(Configuration::getInstance()->getTaskListPath().toStdString().c_str());

    // Preferences
    pugi::xml_node preferences = session.append_child("preferences");
    pugi::xml_node language = preferences.append_child("language");
    unsigned int langvalue = Configuration::getInstance()->getLanguage();
    std::stringstream langss;
    langss << langvalue;
    language.append_child(pugi::node_pcdata).set_value(langss.str().c_str());

    doc.save_file(file_path);
}


