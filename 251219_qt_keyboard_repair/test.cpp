#include <cstddef>
#include <unordered_map>
#include <iostream>

#include <QGridLayout>
#include <QWidget>


QString KeyBoard::get_key_text(const int code) const {
	return buttons.at(code)->text();
}

int main() {
    QString key_text = KeyBoard::get_key_text(65); // Example key code
    std::cout << key_text.toStdString() << std::endl;
    return 0;
}