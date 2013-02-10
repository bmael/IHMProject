#include "listform.h"
#include "ui_listform.h"

ListForm::ListForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListForm)
{
    ui->setupUi(this);

    ui->timeLimitRelative->hide();
    ui->timeLimitRelativeLabel->hide();

    connect(ui->timeLimitChoiceAbsolute, SIGNAL(clicked()), this, SLOT(showAbsoluteTimeLimit()));
    connect(ui->timeLimitChoiceRelative, SIGNAL(clicked()), this, SLOT(showRelativeTimeLimit()));
    connect(ui->acceptList, SIGNAL(rejected()), this, SIGNAL(hideThis()));
}

ListForm::~ListForm()
{
    delete ui;
}

/*
  SLOTS
 */
void ListForm::showAbsoluteTimeLimit() {
    ui->timeLimitRelative->hide();
    ui->timeLimitRelativeLabel->hide();
    ui->timeLimitAbsolute->show();
}

void ListForm::showRelativeTimeLimit() {
    ui->timeLimitRelative->show();
    ui->timeLimitRelativeLabel->show();
    ui->timeLimitAbsolute->hide();
}
