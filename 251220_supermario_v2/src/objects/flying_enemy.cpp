#include "flying_enemy.hpp"

#include "map_movable.hpp"

#include <cmath>

using biv::FlyingEnemy;

FlyingEnemy::FlyingEnemy(const Coord& top_left, const int width, const int height, const float fly_amplitude) 
	: RectMapMovableAdapter(top_left, width, height) {
	hspeed = 0.15f;
	vspeed = 0;

}

biv::Rect FlyingEnemy::get_rect() const noexcept {
	return {top_left, width, height};
}

biv::Speed FlyingEnemy::get_speed() const noexcept {
	return {vspeed, hspeed};
}

void FlyingEnemy::process_horizontal_static_collision(Rect* obj) noexcept {
	hspeed = -hspeed;
	move_horizontally();
}

void FlyingEnemy::process_mario_collision(Collisionable* mario) noexcept {
	if (mario->get_speed().v > 0 && mario->get_speed().v != V_ACCELERATION) {
		kill();
	} else {
		mario->kill();
	}
}

void FlyingEnemy::process_vertical_static_collision(Rect* obj) noexcept {
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
	if (vspeed > 0) {
		top_left.y -= vspeed;
		vspeed = 0;
	}
}

void FlyingEnemy::move_vertically() noexcept {
	fly_phase += fly_speed;
	if (fly_phase > 2 * M_PI) {
		fly_phase -= 2 * M_PI;
	}
	top_left.y = base_y + fly_amplitude * std::sin(fly_phase);

	biv::Movable::move_vertically();
}
