#include "startup_window.hpp"

using biv::StartupWindow;

StartupWindow::StartupWindow(const int width, const int height, QWidget* parent) 
    : window_width(width), window_height(height), QWidget(parent) {
    
    setFixedSize(window_width, window_height);
    CreateStartButton("Виртуальная клавиатура", 200, 50);
}

void StartupWindow::CreateStartButton(const QString& text, const int width, const int height) {
    button_width = width;
    button_height = height;
    const QString button_text = QString("Запустить: ") + text;

    QPushButton* start_button = new QPushButton(button_text, this);
    start_button->setFixedSize(button_width, button_height);
    start_button->move((window_width - button_width) / 2, (window_height - button_height) / 2);

    connect(start_button, &QPushButton::clicked, this, &StartupWindow::start_requested);
}