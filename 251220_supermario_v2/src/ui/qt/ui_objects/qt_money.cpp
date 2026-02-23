#include "qt_money.hpp"

using biv::QtMoney;

QtMoney::QtMoney(const Coord& top_left, const int width, const int height)
	: Money(top_left, width, height) {}

void QtMoney::paint(QPainter* painter) const noexcept {
	painter->fillRect(get_left(), get_top(), get_right() - get_left(), get_bottom() - get_top(), QColor(255, 215, 0));
}
