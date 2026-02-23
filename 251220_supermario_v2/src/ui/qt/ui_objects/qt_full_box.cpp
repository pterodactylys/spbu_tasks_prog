#include "qt_full_box.hpp"

using biv::QtFullBox;

QtFullBox::QtFullBox(
	const Coord& top_left,
	const int width, const int height,
	UIFactory* ui_factory
) : FullBox(top_left, width, height, ui_factory) {}

void QtFullBox::paint(QPainter* painter) const noexcept {
	if (is_active_) {
		painter->fillRect(get_left(), get_top(), get_right() - get_left(), get_bottom() - get_top(), QColor(255, 165, 0));
	} else {
		painter->fillRect(get_left(), get_top(), get_right() - get_left(), get_bottom() - get_top(), QColor(139, 90, 43));
	}
}
