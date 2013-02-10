#include "tasklistwidget.h"
#include "ui_tasklistwidget.h"

TaskListWidget::TaskListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskListWidget)
{
    ui->setupUi(this);

    ui->taskListForm->hide();

    connect(ui->newTaskList, SIGNAL(clicked()), this, SLOT(showNewTaskListForm()));
    connect(ui->modifyTaskList, SIGNAL(clicked()), this, SLOT(showModifyTaskListForm()));
    connect(ui->taskListForm, SIGNAL(hideThis()), this, SLOT(hideListForm()));
}

TaskListWidget::~TaskListWidget()
{
    delete ui;
}

/*
  SLOTS
 */

void TaskListWidget::showNewTaskListForm() {
    ui->taskListForm->show();
}

void TaskListWidget::showModifyTaskListForm() {
    ui->taskListForm->show();
}

void TaskListWidget::hideListForm() {
    ui->taskListForm->hide();
}
