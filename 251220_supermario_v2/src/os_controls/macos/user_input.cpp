#include "user_input.hpp"

#include <ApplicationServices/ApplicationServices.h>

using biv::os::UserInput;

namespace {
    constexpr CGKeyCode KEY_A = 0;
    constexpr CGKeyCode KEY_D = 2;
    constexpr CGKeyCode KEY_SPACE = 49;
    constexpr CGKeyCode KEY_ESC = 53;
}

UserInput biv::os::get_user_input() {
    if (CGEventSourceKeyState(kCGEventSourceStateCombinedSessionState, KEY_A)) {
        return UserInput::MAP_RIGHT;
    }
    if (CGEventSourceKeyState(kCGEventSourceStateCombinedSessionState, KEY_D)) {
        return UserInput::MAP_LEFT;
    }
    if (CGEventSourceKeyState(kCGEventSourceStateCombinedSessionState, KEY_SPACE)) {
        return UserInput::MARIO_JUMP;
    }
    if (CGEventSourceKeyState(kCGEventSourceStateCombinedSessionState, KEY_ESC)) {
        return UserInput::EXIT;
    }
    return UserInput::NO_INPUT;
}