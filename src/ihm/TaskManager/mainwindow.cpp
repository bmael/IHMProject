#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGroupBox>
#include <QDebug>

#include "../../Concept/Manager/task.h"
#include "../../Concept/Manager/taskcomponent.h"
#include "../../Concept/Manager/tasklist.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
