# floating-keyboard-Qt

## Overview
This project provides a customizable floating keyboard widget using Qt. The keyboard can be dynamically resized, repositioned, and interacts seamlessly with either `QLineEdit` or `QTextEdit` objects for text input.

## Features
- Resizable keyboard with proportional button dimensions.
- Draggable interface for easy repositioning.
- Dynamically updates text in linked `QLineEdit` or `QTextEdit` objects.
- Configurable layout with support for special keys like Enter, Space, and Clear.
- Middle-of-the-screen positioning on launch.

## Minimum Requirements
- **Operating System**: Windows, macOS, or Linux.
- **Qt Version**: 5.14 or later.
- **Compiler**: Compatible C++ compiler (e.g., MSVC, GCC, or Clang).

## How to Use
1. **Clone or Download**: Get the source code.
   ```bash
   git clone <repository_url>
   ```
2. **Build the Project**:
   - Open the project in Qt Creator.
   - Configure the build settings to match your environment.
   - Build and run the project.
3. **Integrate the Floating Keyboard**:
   - Include `FloatingKeyboard.h` and `FloatingKeyboard.cpp` in your project.
   - Create an instance of `FloatingKeyboard`:
     ```cpp
     QString textBuffer;
     QLineEdit *lineEdit = new QLineEdit;
     FloatingKeyboard *keyboard = new FloatingKeyboard(textBuffer, lineEdit);
     ```
   - Show the keyboard when needed:
     ```cpp
     keyboard->showKeyboard();
     ```
4. **Link Text Objects**:
   - Pass a pointer to either `QLineEdit` or `QTextEdit` for automatic text updates on pressing Enter.

## Customization
- Modify the `keys` array in `FloatingKeyboard.cpp` to change the keyboard layout.
- Adjust `layoutWidth` and `layoutHeight` constants for different grid dimensions.
- Update styles for buttons and text using Qt Stylesheets.

## Troubleshooting
- Ensure your Qt version meets the minimum requirement.
- Verify `QLineEdit` or `QTextEdit` references are valid when passed to the constructor.

## License
This project is open-source. Modify and use it as needed in your applications.


