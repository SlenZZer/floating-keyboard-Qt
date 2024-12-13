#include "floatingkeyboard.h"


FloatingKeyboard::FloatingKeyboard(void *textObject, QWidget *parent) :
    QWidget(parent), keyboardLayout(new QGridLayout(this)), signalMapper(new QSignalMapper(this)),
    displayLineEdit(new QLineEdit(this)),textObjRef(textObject)
{
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);

    displayLineEdit->setReadOnly(true);
    displayLineEdit->setStyleSheet("font-size: 16px; padding: 5px;");
    keyboardLayout->addWidget(displayLineEdit, 0, 0, 1, 9);

    QPushButton *backspaceButton = new QPushButton("<-", this);
    keyboardLayout->addWidget(backspaceButton, 0, 9);
    connect(backspaceButton, &QPushButton::clicked, [this]() {
        QString text = displayLineEdit->text();
        if (!text.isEmpty()) {

            displayLineEdit->setText("");
        }
    });

    QString keys[4][10] = {
        {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"},
        {"q", "w", "e", "r", "t", "y", "u", "i", "o", "p"},
        {"a", "s", "d", "f", "g", "h", "j", "k", "l", "Clear"},
        {"z", "x", "c", "v", "b", "n", "m", ".", "Space", "Enter"}
    };

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 10; ++col) {
            QPushButton *button = new QPushButton(keys[row][col], this);

            keyboardLayout->addWidget(button, row + 1, col);
            connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
            signalMapper->setMapping(button, keys[row][col]);
        }
    }

    connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(handleButtonClicked(QString)));

    // Center the keyboard on the screen
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;

    move(x, y);
}

void FloatingKeyboard::showKeyboard(QString str)
{
    show();
    raise();
    displayLineEdit->setText(str);
}

void FloatingKeyboard::handleButtonClicked(const QString &key)
{
    if (key == "Enter") {
        QString curerentStr = displayLineEdit->text();

        if (textObjRef) {
            QLineEdit *lineEdit = qobject_cast<QLineEdit *>(reinterpret_cast<QObject *>(textObjRef));
            QTextEdit *textEdit = qobject_cast<QTextEdit *>(reinterpret_cast<QObject *>(textObjRef));

            if (lineEdit) {
                lineEdit->setText(curerentStr);
            } else if (textEdit) {
                textEdit->setPlainText(curerentStr);
            }
        }

        displayLineEdit->clear();
        hide();
    }  else if (key == "Clear") {
        QString text = displayLineEdit->text();
        if (!text.isEmpty()) {
            text.chop(1);
            displayLineEdit->setText(text);
        }
    }else if (key == "Space") {
        displayLineEdit->setText(displayLineEdit->text() + " ");
    } else {
        displayLineEdit->setText(displayLineEdit->text() + key);
    }
    qDebug() << "Key pressed:" << key;
}

void FloatingKeyboard::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragStartPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void FloatingKeyboard::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPos() - dragStartPosition);
        event->accept();
    }
}

void FloatingKeyboard::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    //adjustButtonSizes();
}

void FloatingKeyboard::adjustButtonSizes()
{
    int buttonWidth = width() / layoutWidth;
        int buttonHeight = (height() - displayLineEdit->height()) / (layoutHeight - 1);

        for (int row = 0; row < keyboardLayout->rowCount(); ++row) {
            for (int col = 0; col < keyboardLayout->columnCount(); ++col) {
                QLayoutItem *item = keyboardLayout->itemAtPosition(row, col);
                if (QPushButton *button = qobject_cast<QPushButton *>(item->widget())) {
                    button->setFixedSize(buttonWidth, buttonHeight);
                }
            }
        }
}
