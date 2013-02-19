#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QStandardItem>
#include <QTranslator>
#include <QFileDialog>

#include <QPrintDialog>
#include <QPrinter>
#include <QPainter>
#include <QPrintPreviewDialog>

#include <QMessageBox>
#include <QPushButton>

#include <QPropertyAnimation>

#include <iostream>
#include "../Tools/configuration.h"
#include "../Tools/loadconfiguration.h"
#include "../CustomWidgets/aboutdialog.h"
#include "../CustomWidgets/preferencies.h"
#include "../CustomWidgets/projectwidget.h"

#include "../Concept/Tools/parser.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::MainWindow(QString file_path,LangType language, QWidget *parent) :
       QMainWindow(parent),
       ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
    this->changeLanguage(language);
    qDebug() << "have to load : " << file_path;
    this->openProject(file_path);
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::init()
{
    addFormHidden_ = true;

    translator = new QTranslator(0);

    //ui->tasksView->header()->hide();

    mapping_ = new QMap<QList<QStandardItem *> * , TaskComponent *>();
    model_ = new QStandardItemModel(1,2);
    this->currentProject_ = new TaskList();
    this->currentProjectItem_ = new QList<QStandardItem *>();
    this->currentProjectNotSaved_ = false;

//    this->newProject(QString::fromStdString("Plopiplop"), 0, QDate::currentDate());

//    connect(ui->taskListTools, SIGNAL(sendNewTaskList(QString,int,QDate)), this, SLOT(newTaskList(QString,int,QDate)));
//    connect(ui->taskListTools, SIGNAL(sendRemoveTaskList()), this, SLOT(deleteTaskList()));
    connect(model_, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(modifyTaskList(QModelIndex,QModelIndex)));
    connect(ui->tasksView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(prepareTaskDescriptionModification(QModelIndex)));
    connect(ui->tasksView, SIGNAL(clicked(QModelIndex)), this, SLOT(setSelectedItem(QModelIndex)));


    // Graphic components
    connect(ui->action_propos_de_Moustache, SIGNAL(triggered()), this, SLOT(aboutPopup()));
    connect(ui->actionPreferences, SIGNAL(triggered()), this, SLOT(preferenciesPopup()));
    connect(ui->actionOuvrir, SIGNAL(triggered()), this, SLOT(openProject()));
    connect(ui->actionNouveau, SIGNAL(triggered()), this, SLOT(configureNewProject()));
    connect(ui->actionEnregistrer_sous, SIGNAL(triggered()), this, SLOT(saveProjectAs()));
    connect(ui->actionEnregistrer, SIGNAL(triggered()), this, SLOT(saveProject()));
    connect(ui->actionImprimer, SIGNAL(triggered()), this, SLOT(print()));
    connect(ui->actionQuitter, SIGNAL(triggered()), this, SLOT(closeApplication()));

    connect(ui->addTaskListWidget, SIGNAL(sendNewTaskList(QString,int,QDate)), this, SLOT(newTaskList(QString,int,QDate)));
    connect(ui->addTaskListWidget, SIGNAL(rejected()), this, SLOT(hideAddTaskWidget()));

    ui->addTaskListWidget->setMaximumWidth(0);


    //retranslation
//    connect(this, SIGNAL(retranslate()), ui->taskListTools, SLOT(retranslate()));
//    connect(this, SIGNAL(retranslate()), ui->taskTools, SLOT(retranslate()));


    /** Toolbar **/
    QLayout * mainLayout = new QVBoxLayout();

    QPushButton * newProject = new QPushButton(this);
    newProject->setToolTip(tr("Créer un nouveau projet"));
    newProject->setIcon(QIcon(":/icons/new"));
    connect(newProject, SIGNAL(clicked()), this, SLOT(configureNewProject()));

    QPushButton * openProject = new QPushButton(this);
    openProject->setToolTip(tr("Ouvrir un projet"));
    openProject->setIcon(QIcon(":/icons/open"));
    connect(openProject, SIGNAL(clicked()), this, SLOT(openProject()));

    QPushButton * save = new QPushButton(this);
    save->setToolTip(tr("Enregistrer"));
    save->setIcon(QIcon(":/icons/save"));
    connect(save, SIGNAL(clicked()), this, SLOT(saveProject()));

    QPushButton * saveas = new QPushButton(this);
    saveas->setToolTip(tr("Enregistrer sous"));
    saveas->setIcon(QIcon(":/icons/saveas"));
    connect(saveas, SIGNAL(clicked()), this, SLOT(saveProjectAs()));

    QPushButton * add = new QPushButton(this);
    add->setToolTip(tr("Ajouter une tâche"));
    add->setIcon(QIcon(":/icons/add"));
    connect(add, SIGNAL(clicked()), this, SLOT(showAddTaskWidget()));

    QPushButton * remove = new QPushButton(this);
    remove->setToolTip(tr("Supprimer la tâche sélectionnée"));
    remove->setIcon(QIcon(":/icons/remove"));
    connect(remove, SIGNAL(clicked()), this, SLOT(deleteTaskList()));

    QPushButton * print = new QPushButton(this);
    print->setToolTip(tr("Imprimer le projet"));
    print->setIcon(QIcon(":/icons/printer"));
    connect(print, SIGNAL(clicked()), this, SLOT(print()));

    ui->toolBar->setLayout(mainLayout);

    ui->toolBar->addWidget(newProject);
    ui->toolBar->addWidget(openProject);
    ui->toolBar->addSeparator();

    ui->toolBar->addWidget(save);
    ui->toolBar->addWidget(saveas);
    ui->toolBar->addSeparator();

    ui->toolBar->addWidget(add);
    ui->toolBar->addWidget(remove);
    ui->toolBar->addSeparator();

    ui->toolBar->addWidget(print);

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

    delete currentProject_;
    delete currentProjectItem_;
    delete model_;
    delete mapping_;

    currentProject_ = new TaskList();
    currentProjectItem_ = new QList<QStandardItem *>();
    mapping_ = new QMap<QList<QStandardItem *> *, TaskComponent *>();
    model_ = new QStandardItemModel(1, 2);

    currentProjectNotSaved_ = true;
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

    ui->actionEnregistrer->setEnabled(true);
    ui->actionEnregistrer_sous->setEnabled(true);

}

void MainWindow::openProject(QString file_path)
{
    if ( currentProjectNotSaved_ ) {
        QMessageBox askSave;

        askSave.setIcon(QMessageBox::Question);
        askSave.setText("Le projet à été modifié");
        askSave.setInformativeText("Voulez-vous enregister les changements?");
        askSave.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        askSave.setDefaultButton(QMessageBox::Save);

        int ret = askSave.exec();

        switch (ret) {
            case QMessageBox::Save:
            saveProject();
            break;
        case QMessageBox::Discard:
            // Don't Save was clicked
            break;
        case QMessageBox::Cancel:
            // Cancel was clicked
            return;
            break;
        default:
            break;
        }
    }

    QString file;
    if(file_path.isNull())
       file = QFileDialog::getOpenFileName(this, tr("Ouvrir un projet"), QString(), QString("*.mst"));
    else{
        file = file_path;
    }

    if ( file.isNull() ) {
        return;
    }

    delete currentProject_;
    delete currentProjectItem_;
    delete model_;
    delete mapping_;

    currentProject_ = parse(file.toStdString().c_str());
    currentProjectPath_ = file;
    currentProject_->print();
    currentProjectItem_ = new QList<QStandardItem *>();
    mapping_ = new QMap<QList<QStandardItem *> *, TaskComponent *>();

    currentProjectItem_->append(new QStandardItem( (QString::fromStdString(this->currentProject_->getDescription())) ));
    currentProjectItem_->append(new QStandardItem());
    currentProjectItem_->at(1)->setData(QVariant(QDate::fromString(QString::fromStdString(currentProject_->getEndDate()), "d/MM/yyyy")), 2);

    this->selectedItem_ = currentProjectItem_;

    mapping_->insert(currentProjectItem_, currentProject_);

    currentProjectItem_->at(0)->setCheckable(true);
    if ( currentProject_->getState() == DONE ) {
        currentProjectItem_->at(0)->setCheckState(Qt::Checked);
    }
    loadCurrentProjectItem(currentProject_, currentProjectItem_, mapping_);

    model_ = new QStandardItemModel(1, 2);
    model_->setItem(0, 0, currentProjectItem_->at(0));
    model_->setItem(0, 1, currentProjectItem_->at(1));

    ui->tasksView->setModel(model_);
    ui->tasksView->expandAll();

    connect(model_, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(modifyTaskList(QModelIndex,QModelIndex)));

    ui->actionEnregistrer->setEnabled(true);
    ui->actionEnregistrer_sous->setEnabled(true);
}

void MainWindow::saveProjectAs()
{
    QString s = QFileDialog::getSaveFileName(this,tr("Sauvegarder sous..."),QDir::currentPath(), "TaskList (*.mst);;Template (*.tpt)");
    if( !s.isNull()){
        save(this->currentProject_, s.toStdString());
        this->currentProjectPath_ = s;
        Configuration::getInstance()->setTaskListPath(this->currentProjectPath_);
        currentProjectNotSaved_ = false;
    }
}

void MainWindow::saveProject()
{
    if(this->currentProjectPath_.isNull()) saveProjectAs();
    else{
        save(this->currentProject_, this->currentProjectPath_.toStdString());
        currentProjectNotSaved_ = false;
    }
}

void MainWindow::print()
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setFullPage(true);

    QPrintDialog dialog(&printer, this);
    dialog.setWindowIcon(QIcon(":icons/printer"));
    dialog.setWindowTitle(tr("Impression du projet"));

    if(dialog.exec() != QDialog::Accepted) return;

    QPainter painter;
    painter.begin(&printer);

    painter.scale(20, 20);

    ui->tasksView->render(&painter);

}

void MainWindow::loadCurrentProjectItem(TaskList * currentList, QList<QStandardItem *> * currentItem, QMap<QList<QStandardItem *> *, TaskComponent *> * mapping)
{
    std::deque<TaskComponent*>::const_iterator itb = currentList->getTasksReference()->begin();
    const std::deque<TaskComponent*>::const_iterator ite = currentList->getTasksReference()->end();

    while(itb != ite ){
        if((*itb)->getType() == TASK) {
            QList<QStandardItem *> * l = new QList<QStandardItem *>();
            QStandardItem * i = new QStandardItem(QString::fromStdString((*itb)->getDescription()));
            QStandardItem * d = new QStandardItem();

            l->append(i);
            l->append(d);
            l->at(1)->setData(QVariant(QDate::fromString(QString::fromStdString((*itb)->getEndDate()), "dd/MM/yyyy")), 2);
            l->at(0)->setCheckable(true);

            if ( (*itb)->getState() == DONE ) {
                l->at(0)->setCheckState(Qt::Checked);
            }

            mapping->insert(l, (*itb));

            currentItem->at(0)->appendRow(*l);
        }
        else {
            QList<QStandardItem *> * l = new QList<QStandardItem *>();
            QStandardItem * i = new QStandardItem(QString::fromStdString((*itb)->getDescription()));
            QStandardItem * d = new QStandardItem();

            l->append(i);
            l->append(d);
            l->at(1)->setData(QVariant(QDate::fromString(QString::fromStdString((*itb)->getEndDate()), "dd/MM/yyyy")), 2);
            l->at(0)->setCheckable(true);

            if ( (*itb)->getState() == DONE ) {
                l->at(0)->setCheckState(Qt::Checked);
            }

            mapping->insert(l, (*itb));
            (currentItem->at(0))->appendRow(*l);

            loadCurrentProjectItem(((TaskList *) (*itb)), l, mapping);
        }
        ++itb;
    }
}





void MainWindow::newTaskList(QString taskListDesc, int priority, QDate date) {
    currentProjectNotSaved_ = true;

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
    currentProjectNotSaved_ = true;

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
    currentProjectNotSaved_ = true;

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
    currentProjectNotSaved_ = true;

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
    currentProjectNotSaved_ = true;

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
    currentProjectNotSaved_ = true;

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





void MainWindow::showAddTaskWidget()
{
    if(!addFormHidden_) return;

    QPropertyAnimation * animation = new QPropertyAnimation(ui->addTaskListWidget, "maximumWidth");

    animation->setDuration(1000);

    animation->setStartValue(ui->addTaskListWidget->maximumWidth());
    animation->setEndValue(250);
    ui->showHidepushButton->setIcon(QIcon(":/icons/hide"));

    animation->setEasingCurve(QEasingCurve::OutBack);
    addFormHidden_ = false;

    animation->start(QPropertyAnimation::DeleteWhenStopped);


}

void MainWindow::hideAddTaskWidget()
{
    if(addFormHidden_) return;

    QPropertyAnimation * animation = new QPropertyAnimation(ui->addTaskListWidget, "maximumWidth");

    animation->setDuration(1000);

    animation->setStartValue(ui->addTaskListWidget->maximumWidth());
    animation->setEndValue(0);
    ui->showHidepushButton->setIcon(QIcon(":/icons/show"));

    animation->setEasingCurve(QEasingCurve::InBack);
    addFormHidden_ = true;

    animation->start(QPropertyAnimation::DeleteWhenStopped);

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

void MainWindow::closeApplication()
{
    qDebug() << "closing the applicaiton";

    if ( currentProjectNotSaved_ ) {
        QMessageBox askSave;

        askSave.setIcon(QMessageBox::Question);
        askSave.setText("Le projet à été modifié");
        askSave.setInformativeText("Voulez-vous enregister les changements?");
        askSave.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        askSave.setDefaultButton(QMessageBox::Save);

        int ret = askSave.exec();

        switch (ret) {
            case QMessageBox::Save:
            saveProject();
            break;
        case QMessageBox::Discard:
            // Don't Save was clicked
            break;
        case QMessageBox::Cancel:
            // Cancel was clicked
            return;
            break;
        default:
            break;
        }
    }
    Configuration::getInstance()->setTaskListPath(this->currentProjectPath_);
    saveConfig("conf/session.conf");
    this->close();
}



void MainWindow::on_showHidepushButton_clicked()
{
    if(addFormHidden_) {
        showAddTaskWidget();
    }else{
        hideAddTaskWidget();
    }
}
