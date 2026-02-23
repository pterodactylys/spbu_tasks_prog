#pragma once

#include "qt_ui_obj_rect_adapter.hpp"
#include "full_box.hpp"

namespace biv {
	class QtFullBox : public FullBox, public QtUIObjectRectAdapter {
		public:
			QtFullBox(
				const Coord& top_left,
				const int width, const int height,
				UIFactory* ui_factory
			);

			void paint(QPainter* painter) const noexcept override;
	};
}
