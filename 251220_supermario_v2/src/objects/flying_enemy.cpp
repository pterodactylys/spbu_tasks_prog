#include "flying_enemy.hpp"

#include <cmath>

using biv::FlyingEnemy;

FlyingEnemy::FlyingEnemy(const Coord& top_left, const int width, const int height, const float fly_amplitude) 
	: BasicEnemy(top_left, width, height, 0.15f),
	  base_y(top_left.y), fly_amplitude(fly_amplitude), fly_phase(0) {}

void FlyingEnemy::move_vertically() noexcept {
	fly_phase += fly_speed;
	if (fly_phase > 2 * M_PI) {
		fly_phase -= 2 * M_PI;
	}
	top_left.y = base_y + fly_amplitude * std::sin(fly_phase);

	biv::Movable::move_vertically();
}
