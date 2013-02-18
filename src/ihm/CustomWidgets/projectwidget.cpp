#include "projectwidget.h"
#include "ui_projectwidget.h"

ProjectWidget::ProjectWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectWidget)
{
    ui->setupUi(this);

    ui->dateEdit->setMinimumDate(QDate::currentDate());
}

ProjectWidget::~ProjectWidget()
{
    delete ui;
}

void ProjectWidget::on_buttonBox_accepted()
{
    emit transmitConfiguration(ui->namelineEdit->text(), 0, ui->dateEdit->date());
}
