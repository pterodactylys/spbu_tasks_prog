#include "qt_enemy.hpp"

using biv::QtEnemy;

QtEnemy::QtEnemy(const Coord& top_left, const int width, const int height)
	: Enemy(top_left, width, height) {}

void QtEnemy::paint(QPainter* painter) const noexcept {
	painter->fillRect(get_left(), get_top(), get_right() - get_left(), get_bottom() - get_top(), QColor(0, 180, 0));
}
