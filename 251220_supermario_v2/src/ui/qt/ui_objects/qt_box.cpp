#include "qt_box.hpp"

using biv::QtBox;

QtBox::QtBox(const Coord& top_left, const int width, const int height)
	: Box(top_left, width, height) {}

void QtBox::paint(QPainter* painter) const noexcept {
	painter->fillRect(get_left(), get_top(), get_right() - get_left(), get_bottom() - get_top(), QColor(139, 90, 43));
}
