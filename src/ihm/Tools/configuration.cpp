#include "configuration.h"

Configuration *Configuration::_instance = 0;

Configuration::Configuration(){}
Configuration::~Configuration(){}

void Configuration::setLanguage(int l){
    _language = l;
}

int Configuration::getLanguage(){
    return _language;
}

Configuration * Configuration::getInstance(){
    if(0 == _instance){
        _instance = new Configuration;
    }

    return _instance;
}

