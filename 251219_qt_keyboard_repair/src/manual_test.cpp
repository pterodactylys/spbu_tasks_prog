#include <QApplication>
#include <iostream>
#include "keyboard.hpp"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    biv::KeyBoard kb(800, nullptr);
    QString button_text;
    int key_code;
    button_text = kb.get_key_text(65); // Example key code for 'A'
    std::cout << "Key code 65 corresponds to button text: " << button_text.toStdString() << std::endl;
}