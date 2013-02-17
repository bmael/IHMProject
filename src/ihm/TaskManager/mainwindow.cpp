#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QStandardItem>
#include <iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ui->tasksView->header()->hide();

    mapping_ = new QMap<QStandardItem *, TaskComponent *>();

    this->newProject(QString::fromStdString("Plopiplop"), 0, QDate::currentDate());

    connect(ui->taskListTools, SIGNAL(sendNewTaskList(QString,int,QDate)), this, SLOT(newTaskList(QString,int,QDate)));
    connect(ui->taskListTools, SIGNAL(sendRemoveTaskList()), this, SLOT(deleteTaskList()));
    connect(ui->tasksView, SIGNAL(clicked(QModelIndex)), this, SLOT(setSelectedItem(QModelIndex)));

    this->fillSubList(new QList<QString>(), this->currentProject_);
}



MainWindow::~MainWindow()
{
    delete ui;
}

/*
  SLOTS
 */

void MainWindow::newProject(QString projectName, int priority, QDate date) {
    model_ = new QStandardItemModel(1,2);
    ui->tasksView->setModel(model_);

    //ui->tasksView->setColumnWidth(0, ui->tasksView->width() - 50);
    ui->tasksView->setColumnWidth(1, 50);

    this->currentProject_ = new TaskList(projectName.toStdString());
    this->currentProject_->setPriority(priority);

    this->currentProjectItem_ = new QStandardItem( (QString::fromStdString(this->currentProject_->getDescription()) + " " + date.toString("d/MM/yyyy")) );
    this->selectedItem_ = currentProjectItem_;

    mapping_->insert(currentProjectItem_, currentProject_);

    currentProjectItem_->setCheckable(true);

    model_->setItem(0, 0, currentProjectItem_);
    model_->setItem(0, 1, new QStandardItem(date.toString()));
}



void MainWindow::newTaskList(QString taskListDesc, int priority, QDate date) {
    qDebug() << "Creating new TaskList : " << taskListDesc << " - " <<  priority << " - " << date;
    // Creating the new TaskList
    TaskList * t = new TaskList(taskListDesc.toStdString());
    t->setPriority(priority);

    // Creating the matching QStandardItem
    QStandardItem * i = new QStandardItem(taskListDesc + " " + date.toString("d/MM/yyyy"));
    i->setCheckable(true);

    // Inserting the couple in the map
    mapping_->insert(i, t);

    // Updating the model and the project TaskList
    QStandardItem * parent = selectedItem_;

    ((TaskList *) mapping_->value(parent))->add(t);
    parent->appendRow(i);
    ui->tasksView->expand(model_->indexFromItem(selectedItem_));

    currentProject_->print();
}



void MainWindow::newTask(QString taskDesc, int priority, QDate date) {
    qDebug() << "Creating new Task : " << taskDesc << " - " << priority << " - " << date;
}



void MainWindow::deleteTaskList()
{
    // Retrieving the selected QStandardItem
    QStandardItem * i = selectedItem_;

    if ( i != currentProjectItem_ ) {
        // Retrieving the TaskList and its parent matching the selected QStandardItem
        TaskList * t = (TaskList *) (mapping_->value(i));
        TaskList * parentTask = (TaskList *) (mapping_->value(i->parent()));

        // Changing the selected item
        ui->tasksView->setCurrentIndex(i->parent()->index());
        this->setSelectedItem(i->parent()->index());

        // Removing the item and the TaskList
        parentTask->remove(t);
        (i->parent())->removeRow(i->row());

        currentProject_->print();
    }
    else {
        qDebug() << "You can't delete the main TaskList";
    }
}



void MainWindow::setSelectedItem(QModelIndex m)
{
    this->selectedItem_ = model_->itemFromIndex(m);

    // Updating the Task state
    // TO DO : Setting a TaskList to DONE also change its subtasks to DONE
    if ( selectedItem_->checkState() == Qt::Checked ) {
        ((TaskList *) mapping_->value(selectedItem_))->setState(DONE);
    }
    else {
        ((TaskList *) mapping_->value(selectedItem_))->setState(TODO);
    }
}



void MainWindow::fillSubList(QList<QString> *list, TaskComponent *t)
{
//    std::deque<TaskComponent*>::const_iterator itb = this->currentProject_->getTasks().begin();
//    const std::deque<TaskComponent*>::const_iterator ite = this->currentProject_->getTasks().end();

//    while ( itb != ite ) {
//        if ( (*itb)->getType() == TASKLIST ) {
//            list->append(QString::fromStdString((*itb)->getDescription()));
//            this->fillSubList(list, ((TaskList *) (*itb)));
//        }
//        ++itb;
//    }
//    emit askFillSubList(list);
}
