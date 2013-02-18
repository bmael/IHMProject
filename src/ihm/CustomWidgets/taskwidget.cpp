#include "taskwidget.h"
#include "ui_taskwidget.h"

TaskWidget::TaskWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskWidget)
{
    ui->setupUi(this);

    ui->taskForm->hide();

    connect(ui->newTask, SIGNAL(clicked()), this, SLOT(showNewTaskForm()));
    connect(ui->modifyTask, SIGNAL(clicked()), this, SLOT(showModifyTaskForm()));
    connect(ui->taskForm, SIGNAL(hideThis()), this, SLOT(hideTaskForm()));

    //retranslation
    connect(this, SIGNAL(askRetranslate()), ui->taskForm, SLOT(retranslate()));

}

TaskWidget::~TaskWidget()
{
    delete ui;
}

/*
  SLOTS
 */

void TaskWidget::showNewTaskForm() {
    ui->taskForm->show();
}

void TaskWidget::showModifyTaskForm() {
    ui->taskForm->show();
}

void TaskWidget::hideTaskForm() {
    ui->taskForm->hide();
}

void TaskWidget::retranslate()
{
    ui->retranslateUi(this);
    emit askRetranslate();
}


