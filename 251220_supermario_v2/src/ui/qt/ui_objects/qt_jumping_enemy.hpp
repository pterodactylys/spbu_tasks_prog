#pragma once

#include "qt_ui_obj_rect_adapter.hpp"
#include "jumping_enemy.hpp"

namespace biv {
	class QtJumpingEnemy : public JumpingEnemy, public QtUIObjectRectAdapter {
		public:
			QtJumpingEnemy(const Coord& top_left, const int width, const int height);

			void paint(QPainter* painter) const noexcept override;
	};
}
