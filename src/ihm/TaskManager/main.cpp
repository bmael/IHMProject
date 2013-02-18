#include <QApplication>
#include <QTranslator>
#include <../ihm/TaskManager/mainwindow.h>
#include "../Tools/loadconfiguration.h"
#include "../Tools/configuration.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    readConfig("conf/session.conf");

    MainWindow w((LangType)Configuration::getInstance()->getLanguage());
    w.show();
    

    return a.exec();
}
