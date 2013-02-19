#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QList>
#include <QDate>
#include <QTranslator>

#include "../../Concept/Manager/task.h"
#include "../../Concept/Manager/taskcomponent.h"
#include "../../Concept/Manager/tasklist.h"

#include "../CustomWidgets/preferencies.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    MainWindow(LangType language, QWidget *parent = 0);
    ~MainWindow();

private:
    void init();    // Initializes the interface
    void loadCurrentProjectItem(TaskList * currentList, QList<QStandardItem *> * currentItem, QMap<QList<QStandardItem *> *, TaskComponent *> * mapping);

signals:
    void askFillSubList(QList<QString> *);
    void retranslate();

public slots:
    void configureNewProject();
    void newProject(QString, int, QDate);
    void openProject();

    void prepareTaskDescriptionModification(QModelIndex);
    void modifyTaskList(QModelIndex,QModelIndex);
    void modifyTask(QModelIndex,QModelIndex);

    void newTaskList(QString, int, QDate);
    void newTask(QString, int, QDate);

    void deleteTaskList();
    void deleteTask();

    void setSelectedItem(QModelIndex);

    QList<QStandardItem *> *findQListFromItem(QStandardItem *);
    void displayTaskList(QStandardItem *, bool);

    void fillSubList(QList<QString> *list, TaskComponent * t);  // Not working yet

private slots:
    void aboutPopup();          // Display the about popup
    void preferenciesPopup();   // Display the preferencies popup
    void changeLanguage(LangType lang); // Change the language of the application
    void changeEvent(QEvent *);

private:
    Ui::MainWindow *ui;
    QTranslator * translator;

    QStandardItemModel * model_;
    QList<QStandardItem *> * selectedItem_;

    //QList<TaskList *> * openedProjects_;    // Not used yet
    //QList<QStandardItem *> * openedProjectsItem_;   // Not used yet
    //QList<QMap<QStandardItem *, TaskComponent *> > * openedProjectsMapping;   // Not used yet

    TaskList * currentProject_;
    QList<QStandardItem *> * currentProjectItem_;
    bool currentProjectNotSaved_;
    QMap<QList<QStandardItem *> *, TaskComponent *> * mapping_;
};

#endif // MAINWINDOW_H
