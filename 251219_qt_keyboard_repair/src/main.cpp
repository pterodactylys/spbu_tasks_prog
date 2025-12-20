#include <QApplication>

#include "keyboard_window.hpp"
#include "startup_window.hpp"

int main(int argc, char* argv[]) {
    
    QApplication app(argc, argv);

	biv::StartupWindow startup_window(400, 300);
    startup_window.show();



    biv::KeyBoardWindow keyboard_window;
    keyboard_window.show();
	
    return app.exec();
}
