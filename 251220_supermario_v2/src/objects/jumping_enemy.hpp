#pragma once

#include "enemy.hpp"

namespace biv {
    class JumpingEnemy : public Enemy {
        private:
            int time_to_jump = 0;
            int jump_interval = 50;
        public:
            JumpingEnemy(
                const Coord& top_left,
                const int width,
                const int height,
                const int jump_interval = 50
            );

            void move_vertically() noexcept override;
            void process_vertical_static_collision(Rect* obj) noexcept override;
    };
}