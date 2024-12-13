#ifndef FLOATINGKEYBOARD_H
#define FLOATINGKEYBOARD_H

#include <QObject>
#include <QGridLayout>
#include <QSignalMapper>
#include <QPushButton>
#include <QDebug>
#include <QWidget>
#include <QMouseEvent>
#include <QLineEdit>
#include <QApplication>
#include <QDesktopWidget>
#include <QTextEdit>


//! Developed By: Ansul Yadav
//! Custom minimalist on-screen draggable keyboard using the Qt Widget class.
//! Includes only the required keys; not all keys are included.
//! features:
//! 1. Draggable.
//! 2. Easy to include using minimalistic APIs.
//! 3. Resizable. (work to be done)
class FloatingKeyboard : public QWidget
{
    Q_OBJECT
public:
    explicit FloatingKeyboard(void *textObject, QWidget *parent = nullptr);

    // function to Show keyBoard with some initial string to edit
    void showKeyboard(QString str);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void adjustButtonSizes();
private slots:
    void handleButtonClicked(const QString &key);

private:
    QGridLayout *keyboardLayout;
    QSignalMapper *signalMapper; // to map signals from all the Buttons to their respective strings
    QPoint dragStartPosition;
    QLineEdit *displayLineEdit;  // LineEdit to show real time input of keyBoard
    void *textObjRef;
    const int layoutWidth = 10; // Fixed grid width
    const int layoutHeight = 5; // Fixed grid height
};

#endif // FLOATINGKEYBOARD_H
