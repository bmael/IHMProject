#ifndef CONFIGURATION_H
#define CONFIGURATION_H

class Configuration{
private:
    Configuration(){}
    ~Configuration(){}

public:
    void setLanguage(int l){_language = l;}

    static Configuration *getInstance(){
        if(NULL == _instance){
            _instance = new Configuration;
        }

        return _instance;
    }

private:
    int _language;
    static Configuration *_instance;
};

Configuration *Configuration::_instance = NULL;

#endif //CONFIGURATION_H
