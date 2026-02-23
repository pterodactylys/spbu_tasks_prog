#include "qt_ship.hpp"

using biv::QtShip;

QtShip::QtShip(const Coord& top_left, const int width, const int height)
	: Ship(top_left, width, height) {}

void QtShip::paint(QPainter* painter) const noexcept {
	painter->fillRect(get_left(), get_top(), get_right() - get_left(), get_bottom() - get_top(), QColor(100, 100, 100));
}
