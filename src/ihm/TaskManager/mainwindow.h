#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QList>
#include <QDate>

#include "../../Concept/Manager/task.h"
#include "../../Concept/Manager/taskcomponent.h"
#include "../../Concept/Manager/tasklist.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void askFillSubList(QList<QString> *);

public slots:
    void newProject(QString, int, QDate);
    //void openProject(QString);

    void newTaskList(QString, int, QDate);
    void newTask(QString, int, QDate);

    void deleteTaskList();

    void setSelectedItem(QModelIndex);

    void fillSubList(QList<QString> *list, TaskComponent * t);  // Not working yet

private:
    Ui::MainWindow *ui;

    QStandardItemModel * model_;
    QStandardItem * selectedItem_;

    //QList<TaskList *> * openedProjects_;    // Not used yet
    //QList<QStandardItem *> * openedProjectsItem_;   // Not used yet
    //QList<QMap<QStandardItem *, TaskComponent *> > * openedProjectsMapping;   // Not used yet

    TaskList * currentProject_;
    QStandardItem * currentProjectItem_;
    QMap<QStandardItem *, TaskComponent *> * mapping_;
};

#endif // MAINWINDOW_H
