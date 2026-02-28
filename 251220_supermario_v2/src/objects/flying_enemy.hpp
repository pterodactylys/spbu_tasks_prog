#pragma once

#include "collisionable.hpp"
#include "movable.hpp"
#include "rect.hpp"
#include "rect_map_movable_adapter.hpp"
#include "speed.hpp"

namespace biv {
	class FlyingEnemy : public RectMapMovableAdapter, public Movable, public Collisionable {
		private:
			float base_y;
			float fly_amplitude;
			float fly_phase;
			const float fly_speed = 0.02f;
		public:
			FlyingEnemy(
				const Coord& top_left,
				const int width,
				const int height,
				const float fly_amplitude = 5.0f
			);

			Rect get_rect() const noexcept override;
			Speed get_speed() const noexcept override;

			void process_horizontal_static_collision(Rect*) noexcept override;
			void process_mario_collision(Collisionable*) noexcept override;
			void process_vertical_static_collision(Rect*) noexcept override;
			void move_vertically() noexcept override;
	};
}
