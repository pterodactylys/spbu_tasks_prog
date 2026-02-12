#include "jumping_enemy.hpp"

using biv::JumpingEnemy;

JumpingEnemy::JumpingEnemy(
    const Coord& top_left,
    const int width,
    const int height,
    const int jump_interval
) : Enemy(top_left, width, height),
    time_to_jump(jump_interval),
    jump_interval(jump_interval) {

    hspeed = 0;
    }

void JumpingEnemy::move_vertically() noexcept {
    if (!vspeed) {
        if (time_to_jump <= 0) {
            vspeed = JUMP_SPEED;
            time_to_jump = jump_interval;
        }
        else {
            time_to_jump--;
        }
    }

    biv::Movable::move_vertically();
}

void JumpingEnemy::process_vertical_static_collision(Rect* obj) noexcept {
    top_left.x += hspeed;
    if (!has_collision(obj)) {
        process_horizontal_static_collision(obj);
    }
    else {
        top_left.x -= hspeed;
    }

    if (vspeed != 0) {
        top_left.y -= vspeed;
        vspeed = 0;
    }
}