#include "enemy.hpp"

using biv::Enemy;

Enemy::Enemy(const Coord& top_left, const int width, const int height) 
	: BasicEnemy(top_left, width, height) {}
