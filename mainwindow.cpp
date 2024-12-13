#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_selectionChanged()
{
    FloatingKeyboard* kBoard = new FloatingKeyboard(ui->lineEdit,this);
    kBoard->showKeyboard(ui->lineEdit->text());
}
