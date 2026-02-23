#pragma once

#include "qt_ui_obj_rect_adapter.hpp"
#include "mario.hpp"

namespace biv {
	class QtMario : public Mario, public QtUIObjectRectAdapter {
		public:
			QtMario(const Coord& top_left, const int width, const int height);

			void paint(QPainter* painter) const noexcept override;
	};
}
