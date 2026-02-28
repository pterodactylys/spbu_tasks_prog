#pragma once

#include "basic_enemy.hpp"

namespace biv {
	class JumpingEnemy : public BasicEnemy {
        private:
            int time_to_jump = 0;
            int jump_interval = 50;
		public:
			JumpingEnemy(const Coord& top_left, const int width, const int height);
			void move_vertically() noexcept override;
	};
}
