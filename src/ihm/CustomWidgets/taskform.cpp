#include "taskform.h"
#include "ui_taskform.h"

TaskForm::TaskForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskForm)
{
    ui->setupUi(this);

    ui->timeLimitRelative->hide();
    ui->timeLimitRelativeLabel->hide();

    connect(ui->timeLimitChoiceAbsolute, SIGNAL(clicked()), this, SLOT(showAbsoluteTimeLimit()));
    connect(ui->timeLimitChoiceRelative, SIGNAL(clicked()), this, SLOT(showRelativeTimeLimit()));
    connect(ui->acceptTask, SIGNAL(rejected()), this, SIGNAL(hideThis()));
}

TaskForm::~TaskForm()
{
    delete ui;
}

/*
  SLOTS
 */
void TaskForm::showAbsoluteTimeLimit() {
    ui->timeLimitRelative->hide();
    ui->timeLimitRelativeLabel->hide();
    ui->timeLimitAbsolute->show();
}

void TaskForm::showRelativeTimeLimit() {
    ui->timeLimitRelative->show();
    ui->timeLimitRelativeLabel->show();
    ui->timeLimitAbsolute->hide();
}
