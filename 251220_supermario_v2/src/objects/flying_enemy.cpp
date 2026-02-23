#include "flying_enemy.hpp"

#include <cmath>

using biv::FlyingEnemy;

FlyingEnemy::FlyingEnemy(
	const Coord& top_left,
	const int width,
	const int height,
	const float fly_amplitude
) : Enemy(top_left, width, height),
	base_y(top_left.y),
	fly_amplitude(fly_amplitude) {

	hspeed = 0.15f;
	vspeed = 0;
}

void FlyingEnemy::move_vertically() noexcept {
	fly_phase += FLY_SPEED;
	if (fly_phase > 2 * M_PI) {
		fly_phase -= 2 * M_PI;
	}
	top_left.y = base_y + fly_amplitude * std::sin(fly_phase);
}

void FlyingEnemy::process_vertical_static_collision(Rect* obj) noexcept {
}
