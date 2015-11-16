#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "common.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    process_line();
}

MainWindow::~MainWindow()
{
    delete ui;
}
