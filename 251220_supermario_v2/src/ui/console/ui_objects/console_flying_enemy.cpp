#include "console_flying_enemy.hpp"

using biv::ConsoleFlyingEnemy;

ConsoleFlyingEnemy::ConsoleFlyingEnemy(
	const Coord& top_left,
	const int width, const int height,
	const float fly_amplitude
) : FlyingEnemy(top_left, width, height, fly_amplitude) {}

char ConsoleFlyingEnemy::get_brush() const noexcept {
	return 'f';
}
