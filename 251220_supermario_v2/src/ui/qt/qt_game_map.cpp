#include "qt_game_map.hpp"

#include <algorithm>
#include <QPaintEvent>

using biv::QtGameMap;

QtGameMap::QtGameMap(const int height, const int width, QWidget* parent)
	: QWidget(parent), GameMap(height, width) {

	setFixedSize(GameMap::width * PIXEL_SCALE, GameMap::height * PIXEL_SCALE);
}

void QtGameMap::add_obj(QtUIObject* obj) {
	objs.push_back(obj);
}

void QtGameMap::clear() noexcept {
}

void QtGameMap::refresh() noexcept {
	update();
}

void QtGameMap::remove_obj(QtUIObject* obj) {
	objs.erase(std::remove(objs.begin(), objs.end(), obj), objs.end());
}

void QtGameMap::remove_objs() {
	objs.clear();
}

void QtGameMap::show() const noexcept {
}

void QtGameMap::paintEvent(QPaintEvent* event) {
	QPainter painter(this);

	painter.fillRect(
		0, 0,
		GameMap::width * PIXEL_SCALE, (GameMap::height - 3) * PIXEL_SCALE,
		QColor(135, 206, 235)
	);

	painter.fillRect(
		0, (GameMap::height - 3) * PIXEL_SCALE,
		GameMap::width * PIXEL_SCALE, 3 * PIXEL_SCALE,
		QColor(0, 100, 200)
	);

	painter.scale(PIXEL_SCALE, PIXEL_SCALE);

	for (const QtUIObject* obj : objs) {
		obj->paint(&painter);
	}
}
