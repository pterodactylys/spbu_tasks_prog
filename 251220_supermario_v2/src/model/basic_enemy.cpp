#include "basic_enemy.hpp"

using biv::BasicEnemy;

BasicEnemy::BasicEnemy(
	const Coord& top_left, const int width, const int height,
	const float hspeed
) : RectMapMovableAdapter(top_left, width, height) {
	this->vspeed = 0;
	this->hspeed = hspeed;
}

biv::Rect BasicEnemy::get_rect() const noexcept {
	return {top_left, width, height};
}

biv::Speed BasicEnemy::get_speed() const noexcept {
	return {vspeed, hspeed};
}

void BasicEnemy::process_horizontal_static_collision(Rect* obj) noexcept {
	hspeed = -hspeed;
	move_horizontally();
}

void BasicEnemy::process_mario_collision(Collisionable* mario) noexcept {
	if (mario->get_speed().v > 0 && mario->get_speed().v != V_ACCELERATION) {
		kill();
	} else {
		mario->kill();
	}
}

void BasicEnemy::process_vertical_static_collision(Rect* obj) noexcept {
	// Проверка: не свалился ли враг с корабля. 
	// Т.е., если он на краю, то он должен разверуться 
	// и побежать в обратную сторону.
	top_left.x += hspeed;
	if (!has_collision(obj)) {
		process_horizontal_static_collision(obj);
	} else {
		top_left.x -= hspeed;
	}
	
	// Особенность модели вертикального передвижения в игре.
	if (vspeed != 0) {
		top_left.y -= vspeed;
		vspeed = 0;
	}
}
