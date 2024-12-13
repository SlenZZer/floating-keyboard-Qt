# floating-keyboard-Qt

## Overview
This project provides a custom, minimalist floating keyboard widget using Qt. Designed by Ansul Yadav, it includes essential features for easy integration into applications. This draggable, resizable keyboard allows seamless interaction with `QLineEdit` or `QTextEdit` objects for text input.

## Features
- Draggable interface for easy repositioning.
- Real-time text display for live feedback.
- Configurable initial string for editing.
- Resizable keyboard layout (in-progress).
- Minimalistic design with required keys only.

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
     QTextEdit *textEdit = new QTextEdit;
     FloatingKeyboard *keyboard = new FloatingKeyboard(textEdit);
     ```
   - Show the keyboard with an initial string:
     ```cpp
     keyboard->showKeyboard("Initial text");
     ```

## Customization
- Modify the `keys` array in `FloatingKeyboard.cpp` to change the keyboard layout.
- Adjust `layoutWidth` and `layoutHeight` constants for different grid dimensions.
- Update styles for buttons and text using Qt Stylesheets.

## Troubleshooting
- Ensure your Qt version meets the minimum requirement.
- Verify `QLineEdit` or `QTextEdit` references are valid when passed to the constructor.

## License
This project is open-source. Modify and use it as needed in your applications.

