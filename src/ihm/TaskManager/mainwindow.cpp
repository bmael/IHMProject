#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QStandardItem>
#include <QTranslator>
#include <QFileDialog>
#include <iostream>
#include "../Tools/configuration.h"
#include "../Tools/loadconfiguration.h"
#include "../CustomWidgets/aboutdialog.h"
#include "../CustomWidgets/preferencies.h"
#include "../CustomWidgets/projectwidget.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::MainWindow(LangType language, QWidget *parent) :
       QMainWindow(parent),
       ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
    this->changeLanguage(language);
}

MainWindow::~MainWindow()
{
    saveConfig("conf/session.conf");
    delete ui;
}

void MainWindow::init()
{
    translator = new QTranslator(0);

    //ui->tasksView->header()->hide();

    mapping_ = new QMap<QList<QStandardItem *> * , TaskComponent *>();
    model_ = new QStandardItemModel(1,2);
    this->currentProject_ = new TaskList();
    this->currentProjectItem_ = new QList<QStandardItem *>();

//    this->newProject(QString::fromStdString("Plopiplop"), 0, QDate::currentDate());

    connect(ui->taskListTools, SIGNAL(sendNewTaskList(QString,int,QDate)), this, SLOT(newTaskList(QString,int,QDate)));
    connect(ui->taskListTools, SIGNAL(sendRemoveTaskList()), this, SLOT(deleteTaskList()));
    connect(model_, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(modifyTaskList(QModelIndex,QModelIndex)));
    connect(ui->tasksView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(prepareTaskDescriptionModification(QModelIndex)));
    connect(ui->tasksView, SIGNAL(clicked(QModelIndex)), this, SLOT(setSelectedItem(QModelIndex)));


    // Graphic components
    connect(ui->action_propos_de_Moustache, SIGNAL(triggered()), this, SLOT(aboutPopup()));
    connect(ui->actionPreferences, SIGNAL(triggered()), this, SLOT(preferenciesPopup()));
    connect(ui->actionOuvrir, SIGNAL(triggered()), this, SLOT(openProject()));
    connect(ui->actionNouveau, SIGNAL(triggered()), this, SLOT(configureNewProject()));


    //retranslation
    connect(this, SIGNAL(retranslate()), ui->taskListTools, SLOT(retranslate()));
    connect(this, SIGNAL(retranslate()), ui->taskTools, SLOT(retranslate()));


    this->fillSubList(new QList<QString>(), this->currentProject_);
}

/*
  SLOTS
 */

void MainWindow::configureNewProject()
{
    ProjectWidget pw;
    connect(&pw, SIGNAL(transmitConfiguration(QString, int, QDate)), this, SLOT(newProject(QString,int,QDate)));
    pw.exec();

}

void MainWindow::newProject(QString projectName, int priority, QDate date) {

    ui->tasksView->setModel(model_);

    //ui->tasksView->setColumnWidth(0, ui->tasksView->width() - 50);
    ui->tasksView->setColumnWidth(1, 50);

    this->currentProject_->setDescription(projectName.toStdString());
    this->currentProject_->setPriority(priority);
    this->currentProject_->setEndDate(date.toString("d/MM/yyyy").toStdString());
    this->currentProject_->setIsOrdered(false);

    currentProjectItem_->append(new QStandardItem( (QString::fromStdString(this->currentProject_->getDescription())) ));
    currentProjectItem_->append(new QStandardItem());
    currentProjectItem_->at(1)->setData(QVariant(date), 2);

    this->selectedItem_ = currentProjectItem_;

    mapping_->insert(currentProjectItem_, currentProject_);

    currentProjectItem_->at(0)->setCheckable(true);

    model_->setItem(0, 0, currentProjectItem_->at(0));
    model_->setItem(0, 1, currentProjectItem_->at(1));
}

void MainWindow::openProject()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Ouvrir un projet"), QString(), QString("*.mst"));

    // TODO display the result of parsing for file_path
}



void MainWindow::newTaskList(QString taskListDesc, int priority, QDate date) {
    qDebug() << "Creating new TaskList : " << taskListDesc << " - " <<  priority << " - " << date;
    // Creating the new TaskList
    TaskList * t = new TaskList(taskListDesc.toStdString());
    t->setPriority(priority);
    t->setEndDate(date.toString("d/MM/yyyy").toStdString());
    t->setIsOrdered(false);

    // Creating the matching QStandardItems
    QStandardItem * i = new QStandardItem(taskListDesc);
    QStandardItem * d = new QStandardItem();
    i->setCheckable(true);
    d->setData(QVariant(date), 2);

    QList<QStandardItem *> * l = new QList<QStandardItem *>();
    l->append(i);
    l->append(d);

    // Inserting the couple in the map
    mapping_->insert(l, t);

    // Updating the model and the project TaskList
    QStandardItem * parent = selectedItem_->at(0);

    ((TaskList *) mapping_->value(selectedItem_))->add(t);
    parent->appendRow(*l);
    ui->tasksView->expand(model_->indexFromItem(parent));

    displayTaskList(parent, ((TaskList *) mapping_->value(findQListFromItem(parent)))->getIsOrdered());

    currentProject_->print();
}



void MainWindow::newTask(QString taskDesc, int priority, QDate date) {
    qDebug() << "Creating new Task : " << taskDesc << " - " << priority << " - " << date;

    // Creating the new Task
    TaskComponent * t = new Task(taskDesc.toStdString());
    t->setPriority(priority);
    t->setEndDate(date.toString("d/MM/yyyy").toStdString());

    // Creating the matching QStandardItems
    QStandardItem * i = new QStandardItem(taskDesc);
    QStandardItem * d = new QStandardItem();
    i->setCheckable(true);
    d->setData(QVariant(date), 2);

    QList<QStandardItem *> * l = new QList<QStandardItem *>();
    l->append(i);
    l->append(d);

    // Inserting the couple in the map
    mapping_->insert(l, t);

    // Updating the model and the project TaskList
    QStandardItem * parent = selectedItem_->at(0);
    TaskComponent * parentTask = mapping_->value(selectedItem_);

    if ( parentTask->getType() == TASKLIST ) {
        qDebug() << QString::fromStdString(parentTask->getDescription()) << "is already a TaskList";
        ((TaskList *) parentTask)->add(t);
    }
    else {
        qDebug() << QString::fromStdString(parentTask->getDescription()) << "is not yet a TaskList ; " << findQListFromItem(parent->parent())->at(0)->data(0);
        // Creating a new TaskList to replace the previous Task
        std::string savedDesc = parentTask->getDescription();
        int savedPriority = parentTask->getPriority();
        std::string savedDate = parentTask->getEndDate();

        TaskComponent * newTaskList = new TaskList(savedDesc);
        newTaskList->setPriority(savedPriority);
        newTaskList->setEndDate(savedDate);

        // Adding the new Task to the created TaskList
        ((TaskList *) newTaskList)->add(t);

        // Replacing the old Task
        TaskList * deckList = (TaskList *) mapping_->value(findQListFromItem(parent->parent()));

        std::deque<TaskComponent *> * deck = deckList->getTasksReference();

        std::deque<TaskComponent *>::iterator itr = std::find(deck->begin(), deck->end(), parentTask);

        if( itr != deck->end())
        {
            deck->erase(itr);
            qDebug() << QString::fromStdString(newTaskList->getDescription());
            deck->insert(itr, newTaskList);
        }
        else {
            qDebug() << "NOT FOUND IN DECK!!!";
        }

        //delete parentTask;

        mapping_->remove(selectedItem_);
        mapping_->insert(selectedItem_, newTaskList);

        this->selectedItem_ = findQListFromItem(parent);
    }

    parent->appendRow(*l);
    ui->tasksView->expand(model_->indexFromItem(parent));

    displayTaskList(parent, ((TaskList *) mapping_->value(findQListFromItem(parent)))->getIsOrdered());

    currentProject_->print();
}



void MainWindow::prepareTaskDescriptionModification(QModelIndex index)
{
    model_->blockSignals(true);

    QStandardItem * i = model_->itemFromIndex(index);
    QList<QStandardItem *> * l = findQListFromItem(i);

    if ( i == l->at(0) ) {
        TaskComponent * t = mapping_->value(l);

        QString desc = QString::fromStdString(t->getDescription());
        i->setText(desc);
    }

    model_->blockSignals(false);
}



void MainWindow::modifyTaskList(QModelIndex topLeft, QModelIndex bottomRight)
{
    QStandardItem * i = model_->itemFromIndex(topLeft);
    QList<QStandardItem *> * l = findQListFromItem(i);
    TaskList * t = (TaskList *) mapping_->value(l);

    // Updating the Task state
    // TO DO : Setting a TaskList to DONE also change its subtasks to DONE
    if ( l->at(0)->checkState() == Qt::Checked ) {
        t->setState(DONE);
    }
    else {
        t->setState(TODO);
    }

    // Updating value for the task Description
    if ( i == l->at(0) ) {
        qDebug() << "description test : " << l->at(0)->data(0).toString();
        t->setDescription(l->at(0)->data(0).toString().toStdString());
    }

    // Updating the project for the task end date
    if ( i == l->at(1) ) {
        qDebug() << "end date test : " << l->at(1)->data(0).toDate().toString("d/MM/yyyy");
        t->setEndDate(l->at(1)->data(0).toDate().toString("d/MM/yyyy").toStdString());
    }

    if ( l != currentProjectItem_ ) {
        QStandardItem * parent = i->parent();
        displayTaskList(parent, ((TaskList *) mapping_->value(findQListFromItem(parent)))->getIsOrdered());
    }

    currentProject_->print();
}



void MainWindow::modifyTask(QModelIndex topLeft, QModelIndex bottomRight)
{
    QStandardItem * i = model_->itemFromIndex(topLeft);
    QList<QStandardItem *> * l = findQListFromItem(i);
    TaskComponent * t = mapping_->value(l);

    // Updating the Task state
    // TO DO : Setting a TaskList to DONE also change its subtasks to DONE
    if ( l->at(0)->checkState() == Qt::Checked ) {
        t->setState(DONE);
    }
    else {
        t->setState(TODO);
    }

    // Updating value for the task Description
    if ( i == l->at(0) ) {
        qDebug() << "description test : " << l->at(0)->data(0).toString();
        t->setDescription(l->at(0)->data(0).toString().toStdString());
    }

    // Updating the project for the task end date
    if ( i == l->at(1) ) {
        qDebug() << "end date test : " << l->at(1)->data(0).toDate().toString("d/MM/yyyy");
        t->setEndDate(l->at(1)->data(0).toDate().toString("d/MM/yyyy").toStdString());
    }

    // Refreshing the display
    if ( l != currentProjectItem_ ) {
        QStandardItem * parent = i->parent();
        displayTaskList(parent, ((TaskList *) mapping_->value(findQListFromItem(parent)))->getIsOrdered());
    }

    currentProject_->print();
}



void MainWindow::deleteTaskList()
{
    // Retrieving the selected QStandardItem
    QList<QStandardItem *> * l = selectedItem_;

    if ( l != currentProjectItem_ ) {
        // Retrieving the TaskList and its parent matching the selected QStandardItem
        TaskList * t = (TaskList *) (mapping_->value(l));
        TaskList * parentTask = (TaskList *) (mapping_->value(findQListFromItem((l->at(0))->parent())));

        // Changing the selected item
        ui->tasksView->setCurrentIndex((l->at(0))->parent()->index());
        this->setSelectedItem((l->at(0))->parent()->index());

        qDebug() << "New CurrentItem after deletion :";
        qDebug() << (l->at(0))->parent()->data(0);
        qDebug() << this->selectedItem_->at(0)->data(0);

        // Removing the item and the TaskList
        parentTask->remove(t);

        int row = l->at(0)->row();
        ((l->at(0))->parent())->removeRow(row);

        mapping_->remove(l);

        currentProject_->print();
    }
    else {
        qDebug() << "You can't delete the main TaskList";
    }
}



void MainWindow::deleteTask()
{
    // Retrieving the selected QStandardItem
    QList<QStandardItem *> * l = selectedItem_;

    if ( l != currentProjectItem_ ) {
        // Retrieving the TaskList and its parent matching the selected QStandardItem
        TaskList * t = (TaskList *) (mapping_->value(l));
        TaskList * parentTask = (TaskList *) (mapping_->value(findQListFromItem((l->at(0))->parent())));

        // Changing the selected item
        ui->tasksView->setCurrentIndex((l->at(0))->parent()->index());
        this->setSelectedItem((l->at(0))->parent()->index());

        qDebug() << "New CurrentItem after deletion :";
        qDebug() << (l->at(0))->parent()->data(0);
        qDebug() << this->selectedItem_->at(0)->data(0);

        // Removing the item and the TaskList
        parentTask->remove(t);

        int row = l->at(0)->row();
        ((l->at(0))->parent())->removeRow(row);

        mapping_->remove(l);

        currentProject_->print();
    }
    else {
        qDebug() << "You can't delete the main TaskList";
        ui->statusBar->showMessage("Vous ne pouvez supprimer la liste du projet");
    }
}



void MainWindow::setSelectedItem(QModelIndex m)
{
    this->selectedItem_ = findQListFromItem(model_->itemFromIndex(m));
    qDebug() << "setSelectedItem : " << selectedItem_->at(0)->data(0);
}



QList<QStandardItem *> * MainWindow::findQListFromItem(QStandardItem * i)
{
    QList<QList<QStandardItem *> *> l = mapping_->keys();

    QListIterator<QList<QStandardItem *> *> iter(l);

    QList<QStandardItem *> * result = iter.next();
    QStandardItem * compare = result->at(0);

    while ( (iter.hasNext()) && (i != compare) ) {
        result = iter.next();
        compare = result->at(0);
    }

    return result;
}



void MainWindow::displayTaskList(QStandardItem * item, bool ordered)
{
    // Blocking the signals to avoid a call to modifyTaskList
    model_->blockSignals(true);

    QList<QStandardItem *> * l = findQListFromItem(item);
    TaskComponent * t = mapping_->value(l);

    if ( ordered ) {
        qDebug() << "ordered display for " << item->data(0);
        for ( int i = 0 ; i < item->rowCount() ; ++i ) {
            QString desc = QString::fromStdString(mapping_->value(findQListFromItem(item->child(i, 0)))->getDescription());
            qDebug() << "row " << i << " : " << QString::number(i+1) + ". " + desc;
            item->child(i, 0)->setText(QString(QString::number(i+1) + ". " + desc));
        }
    }
    else {
        for ( int i = 0 ; i < item->rowCount() ; ++i ) {
            QString desc = QString::fromStdString(mapping_->value(findQListFromItem(item->child(i, 0)))->getDescription());
            item->child(i, 0)->setText(desc);
        }
    }

    model_->blockSignals(false);
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


void MainWindow::aboutPopup()
{
    AboutDialog dial;
    dial.exec();
}

void MainWindow::preferenciesPopup()
{
    Preferencies * pref = new Preferencies((LangType)Configuration::getInstance()->getLanguage(),this);
    connect(pref, SIGNAL(languageChanged(LangType)), this, SLOT(changeLanguage(LangType)));
    pref->exec();
}

void MainWindow::changeLanguage(LangType lang)
{
    switch(lang){
        case FR:
            qDebug() << "French language selected";
            Configuration::getInstance()->setLanguage(FR);
            translator->load("ihm_fr.qm");
            break;
        case EN:
            qDebug() << "English language selected";
            Configuration::getInstance()->setLanguage(EN);
            translator->load("ihm_en.qm");
            break;
    }


    qApp->installTranslator(translator);

}

void MainWindow::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
        emit retranslate();
    }

    QMainWindow::changeEvent(event);
}


