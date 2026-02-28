#pragma once

#include "basic_enemy.hpp"

namespace biv {
	class FlyingEnemy : public BasicEnemy {
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

			void move_vertically() noexcept override;
	};
}
