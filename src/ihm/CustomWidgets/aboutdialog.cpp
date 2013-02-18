/* ***************************************************
 * File aboutdialog.cpp
 * Project Moustache
 * Mael BARBIN - JULIEN Bizeul
 * M1 ALMA - Université de Nantes
 * 2012-2013
 * ***************************************************/

#include "aboutdialog.h"
#include "ui_aboutdialog.h"

/**
 * @brief Constructs a new AboutDialog widget.
 * @param parent
 */
AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
}

/**
 * @brief Destroys the AboutDialog
 */
AboutDialog::~AboutDialog()
{
    delete ui;
}


