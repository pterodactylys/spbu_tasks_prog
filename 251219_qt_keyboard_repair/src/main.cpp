#include <QApplication>

#include "keyboard_window.hpp"
#include "startup_window.hpp"

int main(int argc, char* argv[]) {
    
    QApplication app(argc, argv);

	biv::StartupWindow startup_window(400, 300);
    biv::KeyBoardWindow keyboard_window;
    startup_window.show();
    QObject::connect(&startup_window, &biv::StartupWindow::start_requested, [&]() {
        startup_window.close();
        keyboard_window.show();
            });

    return app.exec();
}
