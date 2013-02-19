#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QDate>
#include <QMainWindow>
#include <QTranslator>
#include <QStandardItemModel>

#include "../../Concept/Manager/task.h"
#include "../CustomWidgets/preferencies.h"
#include "../../Concept/Manager/tasklist.h"
#include "../../Concept/Manager/taskcomponent.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    MainWindow(QString file_path, LangType language, QWidget *parent = 0);
    ~MainWindow();

private:
    void init();    // Initializes the interface
    void loadCurrentProjectItem(TaskList * currentList,
                                QList<QStandardItem *> * currentItem,
                                QMap<QList<QStandardItem *> *,
                                TaskComponent *> * mapping);

signals:
    void askFillSubList(QList<QString> *);
    void retranslate(); // Send when the user changes the application language

public slots:
    void configureNewProject();                 // Configure the new Project
    void newProject(QString, int, QDate);       // Creates a new Project
    void openProject(QString file_path = 0);    // Open an existing project

    void saveProjectAs();  // Save current project as...
    void saveProject();    // Save current project

    void print();   // Print the current project

    void prepareTaskDescriptionModification(QModelIndex);
    void modifyTaskList(QModelIndex,QModelIndex);
    void modifyTask(QModelIndex,QModelIndex);

    void newTaskList(QString, int, QDate);  // Creates a new TaskList
    void newTask(QString, int, QDate);      // Creates a new Task

    void deleteTaskList();                  // Delete the selected TaskList
    void deleteTask();                      // Delete the selected Task

    void setSelectedItem(QModelIndex);      // Selects an object on our model

    QList<QStandardItem *> *findQListFromItem(QStandardItem *);
    void displayTaskList(QStandardItem *, bool);    // Displays a TaskList on our gui

    void fillSubList(QList<QString> *list, TaskComponent * t);  // Not working yet

private slots:
    void aboutPopup();          // Display the about popup
    void preferenciesPopup();   // Display the preferencies popup
    void changeLanguage(LangType lang); // Change the language of the application
    void changeEvent(QEvent *); // Detects when the language change
    void closeApplication();    // Close the application

private:
    Ui::MainWindow *ui;
    QTranslator * translator;

    QStandardItemModel * model_;
    QList<QStandardItem *> * selectedItem_;

    //QList<TaskList *> * openedProjects_;    // Not used yet
    //QList<QStandardItem *> * openedProjectsItem_;   // Not used yet
    //QList<QMap<QStandardItem *, TaskComponent *> > * openedProjectsMapping;   // Not used yet

    TaskList * currentProject_;
    QString currentProjectPath_;
    QList<QStandardItem *> * currentProjectItem_;
    bool currentProjectNotSaved_;
    QMap<QList<QStandardItem *> *, TaskComponent *> * mapping_;
};

#endif // MAINWINDOW_H
