#ifndef CONFIGURATION_H
#define CONFIGURATION_H

class Configuration{
private:
    Configuration();
    ~Configuration();

public:
    void setLanguage(int l);
    int getLanguage();

    static Configuration *getInstance();

private:
    int _language;
    static Configuration *_instance;
};


#endif //CONFIGURATION_H
