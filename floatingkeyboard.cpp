#include "floatingkeyboard.h"

#include <QGuiApplication>

FloatingKeyboard::FloatingKeyboard(QWidget *targetWidget, QWidget *parent)
    : QWidget(parent)
    , keyboardLayout(new QGridLayout(this))
    , displayLineEdit(new QLineEdit(this))
    , targetWidgetRef(targetWidget)
{
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);
    setMinimumSize(700, 260);

    displayLineEdit->setReadOnly(true);
    displayLineEdit->setStyleSheet("font-size: 16px; padding: 5px;");
    keyboardLayout->addWidget(displayLineEdit, 0, 0, 1, 9);

    QPushButton *backspaceButton = new QPushButton("<-", this);
    keyboardLayout->addWidget(backspaceButton, 0, 9);
    connect(backspaceButton, &QPushButton::clicked, [this]() {
        QString text = displayLineEdit->text();
        if (!text.isEmpty()) {
            text.chop(1);
            displayLineEdit->setText(text);
        }
    });

    const QString keys[4][10] = {
        {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"},
        {"q", "w", "e", "r", "t", "y", "u", "i", "o", "p"},
        {"a", "s", "d", "f", "g", "h", "j", "k", "l", "Clear"},
        {"Shift", "z", "x", "c", "v", "b", "n", "m", "Space", "Enter"}
    };

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 10; ++col) {
            QPushButton *button = new QPushButton(keys[row][col], this);
            const QString key = keys[row][col];

            keyboardLayout->addWidget(button, row + 1, col);
            connect(button, &QPushButton::clicked, this, [this, key]() {
                handleButtonClicked(key);
            });

            if (key.size() == 1 && key.at(0).isLower()) {
                alphaButtons.append(button);
            }
        }
    }

    if (QScreen *screen = QGuiApplication::primaryScreen()) {
        QRect screenGeometry = screen->availableGeometry();
        int x = screenGeometry.center().x() - width() / 2;
        int y = screenGeometry.center().y() - height() / 2;
        move(x, y);
    }

    adjustButtonSizes();
}

void FloatingKeyboard::showKeyboard(const QString &str)
{
    show();
    raise();
    displayLineEdit->setText(str);
}

void FloatingKeyboard::setTargetWidget(QWidget *targetWidget)
{
    targetWidgetRef = targetWidget;
}

void FloatingKeyboard::handleButtonClicked(const QString &key)
{
    if (key == "Enter") {
        QString currentStr = displayLineEdit->text();

        if (targetWidgetRef) {
            QLineEdit *lineEdit = qobject_cast<QLineEdit *>(targetWidgetRef);
            QTextEdit *textEdit = qobject_cast<QTextEdit *>(targetWidgetRef);

            if (lineEdit) {
                lineEdit->setText(currentStr);
            } else if (textEdit) {
                textEdit->setPlainText(currentStr);
            }
        }

        displayLineEdit->clear();
        hide();
    } else if (key == "Clear") {
        displayLineEdit->clear();
    } else if (key == "Space") {
        displayLineEdit->setText(displayLineEdit->text() + " ");
    } else if (key == "Shift") {
        shiftEnabled = !shiftEnabled;
        updateAlphaKeys();
    } else {
        const QString value = shiftEnabled ? key.toUpper() : key;
        displayLineEdit->setText(displayLineEdit->text() + value);

        if (shiftEnabled) {
            shiftEnabled = false;
            updateAlphaKeys();
        }
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
    adjustButtonSizes();
}

void FloatingKeyboard::adjustButtonSizes()
{
    int buttonWidth = width() / layoutWidth;
    int buttonHeight = (height() - displayLineEdit->height()) / (layoutHeight - 1);

    for (int row = 0; row < keyboardLayout->rowCount(); ++row) {
        for (int col = 0; col < keyboardLayout->columnCount(); ++col) {
            QLayoutItem *item = keyboardLayout->itemAtPosition(row, col);
            if (!item || !item->widget()) {
                continue;
            }

            if (QPushButton *button = qobject_cast<QPushButton *>(item->widget())) {
                button->setFixedSize(buttonWidth, buttonHeight);
            }
        }
    }
}

void FloatingKeyboard::updateAlphaKeys()
{
    for (QPushButton *button : alphaButtons) {
        if (!button) {
            continue;
        }

        const QString currentText = button->text();
        button->setText(shiftEnabled ? currentText.toUpper() : currentText.toLower());
    }
}
