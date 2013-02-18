#include "preferencies.h"
#include "ui_preferencies.h"

Preferencies::Preferencies(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preferencies)
{
    ui->setupUi(this);
}

Preferencies::~Preferencies()
{
    delete ui;
}

void Preferencies::on_buttonBox_accepted()
{
    if(ui->frenchRadioButton->isChecked()) emit languageChanged(FR);
    else emit languageChanged(EN);
}


