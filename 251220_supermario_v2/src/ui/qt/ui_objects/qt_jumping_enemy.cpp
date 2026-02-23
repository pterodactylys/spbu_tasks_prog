#include "qt_jumping_enemy.hpp"

using biv::QtJumpingEnemy;

QtJumpingEnemy::QtJumpingEnemy(const Coord& top_left, const int width, const int height)
	: JumpingEnemy(top_left, width, height) {}

void QtJumpingEnemy::paint(QPainter* painter) const noexcept {
	painter->fillRect(get_left(), get_top(), get_right() - get_left(), get_bottom() - get_top(), QColor(180, 0, 180));
}
