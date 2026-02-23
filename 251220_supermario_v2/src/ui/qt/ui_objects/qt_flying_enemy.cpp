#include "qt_flying_enemy.hpp"

using biv::QtFlyingEnemy;

QtFlyingEnemy::QtFlyingEnemy(
	const Coord& top_left,
	const int width, const int height,
	const float fly_amplitude
) : FlyingEnemy(top_left, width, height, fly_amplitude) {}

void QtFlyingEnemy::paint(QPainter* painter) const noexcept {
	painter->fillRect(get_left(), get_top(), get_right() - get_left(), get_bottom() - get_top(), QColor(255, 80, 80));
}
