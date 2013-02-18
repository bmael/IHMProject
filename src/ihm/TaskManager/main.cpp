#include <QApplication>
#include <QTranslator>
#include <QTextCodec>
#include <../ihm/TaskManager/mainwindow.h>
#include "../Tools/loadconfiguration.h"
#include "../Tools/configuration.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    #if QT_VERSION < 0x050000
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    #endif

    readConfig("conf/session.conf");

    MainWindow w((LangType)Configuration::getInstance()->getLanguage());
    w.show();


    return a.exec();
}
