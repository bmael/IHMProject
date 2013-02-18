#include "preferencies.h"
#include "ui_preferencies.h"

Preferencies::Preferencies(LangType lang, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preferencies)
{
    ui->setupUi(this);
    switch(lang){
        case EN:
            ui->englishRadioButton->setChecked(true);
            break;
        case FR:
            ui->frenchRadioButton->setChecked(true);
            break;
    }
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


