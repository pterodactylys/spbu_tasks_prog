/**
	Qt-версия игрового цикла Super Mario.
	Использует QApplication + QTimer вместо while-цикла с sleep.
*/
#include <QApplication>
#include <QTimer>

#include "qt_ui_factory.hpp"
#include "first_level.hpp"
#include "game.hpp"
#include "game_level.hpp"
#include "game_map.hpp"
#include "mario.hpp"
#include "ui_factory.hpp"

#include <QKeyEvent>

namespace {
	// Вспомогательный класс для обработки ввода через Qt
	class GameWidget : public QWidget {
		public:
			bool key_left = false;
			bool key_right = false;
			bool key_jump = false;
			bool key_exit = false;

			GameWidget(QWidget* child, QWidget* parent = nullptr)
				: QWidget(parent) {
				child->setParent(this);
				child->move(0, 0);
				setFixedSize(child->size());
				setFocusPolicy(Qt::StrongFocus);
			}

		protected:
			void keyPressEvent(QKeyEvent* event) override {
				switch (event->key()) {
					case Qt::Key_A: key_right = true; break;
					case Qt::Key_D: key_left = true; break;
					case Qt::Key_Space: key_jump = true; break;
					case Qt::Key_Escape: key_exit = true; break;
				}
			}

			void keyReleaseEvent(QKeyEvent* event) override {
				switch (event->key()) {
					case Qt::Key_A: key_right = false; break;
					case Qt::Key_D: key_left = false; break;
					case Qt::Key_Space: key_jump = false; break;
					case Qt::Key_Escape: key_exit = false; break;
				}
			}
	};
}

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	// 1. Установка параметров игры
	biv::Game game;
	biv::QtUIFactory* ui_factory = new biv::QtUIFactory(&game);
	biv::QtGameMap* qt_game_map = ui_factory->get_qt_game_map();
	biv::GameMap* game_map = ui_factory->get_game_map();
	biv::GameLevel* game_level = new biv::FirstLevel(ui_factory);
	biv::Mario* mario = ui_factory->get_mario();

	GameWidget window(qt_game_map);
	window.setWindowTitle("Super Mario");
	window.show();

	QTimer timer;
	QObject::connect(&timer, &QTimer::timeout, [&]() {
		// 2. Получение пользовательского ввода
		if (window.key_left) {
			mario->move_map_left();
			if (!game.check_static_collisions(mario)) {
				game.move_map_left();
			}
			mario->move_map_right();
		}
		if (window.key_right) {
			mario->move_map_right();
			if (!game.check_static_collisions(mario)) {
				game.move_map_right();
			}
			mario->move_map_left();
		}
		if (window.key_jump) {
			mario->jump();
		}
		if (window.key_exit) {
			game.finish();
		}

		// 3. Обновление внутреннего состояния игры
		game.move_objs_horizontally();
		game.check_horizontally_static_collisions();

		game.move_objs_vertically();
		game.check_mario_collision();
		game.check_vertically_static_collisions();

		if (
			game_map->is_below_map(mario->get_top())
			|| !mario->is_active()
		) {
			game_level->restart();
			mario = ui_factory->get_mario();
		}

		if (game.is_level_end()) {
			if (!game_level->is_final()) {
				game_level = game_level->get_next();
				mario = ui_factory->get_mario();
				game.start_level();
			} else {
				game.finish();
			}
		}

		// 4. Обновление изображения на экране
		qt_game_map->refresh();

		// 5. Проверка того, не окончена ли игра
		if (game.is_finished()) {
			app.quit();
		}
	});
	timer.start(10); // 10мс — как в консольной версии

	// 6. Завершение по выходу из Qt event loop
	return app.exec();
}
