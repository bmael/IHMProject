#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QString>

class Configuration{
private:
    Configuration();
    ~Configuration();

public:
    void setLanguage(int l);
    int getLanguage();

    void setTaskListPath(QString path);
    QString getTaskListPath();

    static Configuration *getInstance();

private:
    int _language;
    QString _taskListPath;
    static Configuration *_instance;
};


#endif //CONFIGURATION_H
