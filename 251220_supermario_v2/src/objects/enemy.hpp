#pragma once

#include "basic_enemy.hpp"

namespace biv {
	class Enemy : public BasicEnemy {
		public:
			Enemy(const Coord& top_left, const int width, const int height);
	};
}
