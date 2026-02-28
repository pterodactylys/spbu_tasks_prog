#include "jumping_enemy.hpp"

using biv::JumpingEnemy;

JumpingEnemy::JumpingEnemy(const Coord& top_left, const int width, const int height) 
	: BasicEnemy(top_left, width, height) {}

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
