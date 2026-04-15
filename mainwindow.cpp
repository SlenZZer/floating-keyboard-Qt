#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLineEdit>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , keyboard(nullptr)
{
    ui->setupUi(this);

    keyboard = new FloatingKeyboard(ui->lineEdit, this);
    ui->lineEdit->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->lineEdit &&
        (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::FocusIn)) {
        keyboard->setTargetWidget(ui->lineEdit);
        keyboard->showKeyboard(ui->lineEdit->text());
        return false;
    }

    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::on_pushButton_clicked()
{
    statusBar()->showMessage(QString("Saved: %1").arg(ui->lineEdit->text()), 2500);
}
