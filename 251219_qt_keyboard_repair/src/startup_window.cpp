#include "startup_window.hpp"

using biv::StartupWindow;

StartupWindow::StartupWindow(const int width, const int height, QWidget* parent) 
    : window_width(width), window_height(height), QWidget(parent) {
    
    setFixedSize(window_width, window_height);
}