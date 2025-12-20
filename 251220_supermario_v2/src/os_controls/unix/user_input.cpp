#include "user_input.hpp"

#include <unistd.h>
#include <sys/select.h>
#include <cctype>

using biv::os::UserInput;

UserInput biv::os::get_user_input() {
    fd_set set;
    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);
    struct timeval tv{0, 0};
    int rv = select(STDIN_FILENO + 1, &set, nullptr, nullptr, &tv);
    if (rv > 0 && FD_ISSET(STDIN_FILENO, &set)) {
        char ch = 0;
        if (read(STDIN_FILENO, &ch, 1) <= 0) return UserInput::NO_INPUT;
        char c = static_cast<char>(std::toupper((unsigned char)ch));
        // Сопоставление повторяет логику windows-реализации
        if (c == 'A') return UserInput::MAP_RIGHT;
        if (c == 'D') return UserInput::MAP_LEFT;
        if (ch == ' ') return UserInput::MARIO_JUMP;
        if (ch == 27) return UserInput::EXIT; // ESC
    }
    return UserInput::NO_INPUT;
}