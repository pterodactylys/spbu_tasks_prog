#include "os_control_settings.hpp"

#include <unistd.h>
#include <termios.h>
#include <cstdio>

static struct termios g_orig_term;
static bool g_term_saved = false;

void biv::os::init_settings() {
    if (!g_term_saved) {
        if (tcgetattr(STDIN_FILENO, &g_orig_term) == 0) g_term_saved = true;
    }
    struct termios t = g_orig_term;
    t.c_lflag &= ~(ICANON | ECHO);
    t.c_cc[VMIN] = 0;
    t.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);

    // Скрыть курсор
    std::printf("\x1b[?25l");
    std::fflush(stdout);
}

void biv::os::set_cursor_start_position() {
    // Переместить курсор в верхний левый угол
    std::printf("\x1b[H");
    std::fflush(stdout);
}