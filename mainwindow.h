#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <floatingkeyboard.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QString txt;
    ~MainWindow();

signals:
    void showKboard(QString str);
    void hideKboard();

private slots:
    void on_lineEdit_selectionChanged();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
