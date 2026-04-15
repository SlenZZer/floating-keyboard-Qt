#ifndef FLOATINGKEYBOARD_H
#define FLOATINGKEYBOARD_H

#include <QObject>
#include <QGridLayout>
#include <QPushButton>
#include <QDebug>
#include <QWidget>
#include <QMouseEvent>
#include <QLineEdit>
#include <QApplication>
#include <QTextEdit>
#include <QScreen>
#include <QPointer>
#include <QVector>


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
    explicit FloatingKeyboard(QWidget *targetWidget, QWidget *parent = nullptr);

    // function to Show keyBoard with some initial string to edit
    void showKeyboard(const QString &str);
    void setTargetWidget(QWidget *targetWidget);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void adjustButtonSizes();
private slots:
    void handleButtonClicked(const QString &key);

private:
    QGridLayout *keyboardLayout;
    QPoint dragStartPosition;
    QLineEdit *displayLineEdit;  // LineEdit to show real time input of keyBoard
    QPointer<QWidget> targetWidgetRef;
    QVector<QPushButton *> alphaButtons;
    bool shiftEnabled = false;
    const int layoutWidth = 10; // Fixed grid width
    const int layoutHeight = 5; // Fixed grid height
    void updateAlphaKeys();
};

#endif // FLOATINGKEYBOARD_H
