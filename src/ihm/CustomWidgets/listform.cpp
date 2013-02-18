#include "listform.h"
#include "ui_listform.h"
#include <QDebug>

ListForm::ListForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListForm)
{
    ui->setupUi(this);

    ui->timeLimitAbsolute->setDate(QDate::currentDate());
    ui->timeLimitAbsolute->setMinimumDate(QDate::currentDate());

    ui->timeLimitRelative->hide();
    ui->timeLimitRelativeLabel->hide();

    connect(ui->timeLimitChoiceAbsolute, SIGNAL(clicked()), this, SLOT(showAbsoluteTimeLimit()));
    connect(ui->timeLimitChoiceRelative, SIGNAL(clicked()), this, SLOT(showRelativeTimeLimit()));

    // Connecting the button box (Ok, Cancel)
    connect(ui->acceptList, SIGNAL(rejected()), this, SIGNAL(hideThis()));
    connect(ui->acceptList, SIGNAL(accepted()), this, SLOT(prepareNewTaskList()));
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

void ListForm::fillSubList(QList<QString> *list) {
    for ( int i = 0 ; i < list->size() ; ++i ) {
        ui->subList->addItem(list->at(i));
    }
}

void ListForm::prepareNewTaskList() {
    if ( ui->timeLimitChoiceAbsolute->isChecked()) {
        emit sendNewTaskList(ui->listName->text(),
                             ui->priority->value(),
                             ui->timeLimitAbsolute->date()
                             );
    }
    else {
        emit sendNewTaskList(ui->listName->text(),
                             ui->priority->value(),
                             QDate::currentDate().addDays(ui->timeLimitRelative->value())
                             );
    }

    emit hideThis();
}

void ListForm::retranslate()
{
    ui->retranslateUi(this);
}


