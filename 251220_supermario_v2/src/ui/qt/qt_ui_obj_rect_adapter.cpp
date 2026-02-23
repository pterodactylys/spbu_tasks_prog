#include "qt_ui_obj_rect_adapter.hpp"

using biv::QtUIObjectRectAdapter;

QtUIObjectRectAdapter::QtUIObjectRectAdapter(
	const Coord& top_left, const int width, const int height
) {
	this->top_left = top_left;
	this->width = width;
	this->height = height;
}
