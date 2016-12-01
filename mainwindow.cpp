#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    usrInfo = new userInformation;
}

MainWindow::~MainWindow()
{
    usrInfo->close();
    delete usrInfo;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    usrInfo->show();
}
