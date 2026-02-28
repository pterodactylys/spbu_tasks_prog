#pragma once

#include "enemy.hpp"

namespace biv {
	class FlyingEnemy : public Enemy {
		private:
			float base_y;
			float fly_amplitude;
			float fly_phase = 0;
			const float fly_speed = 0.02f;

		public:
			FlyingEnemy(
				const Coord& top_left,
				const int width,
				const int height,
				const float fly_amplitude = 5.0f
			);

			void move_vertically() noexcept override;
			void process_vertical_static_collision(Rect* obj) noexcept override;
	};
}
