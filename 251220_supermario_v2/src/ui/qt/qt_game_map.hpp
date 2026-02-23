#pragma once

#include <QWidget>
#include <QPainter>
#include <vector>

#include "game_map.hpp"
#include "qt_ui_obj.hpp"

namespace biv {
	class QtGameMap : public QWidget, public GameMap {
		Q_OBJECT

		private:
			static constexpr int PIXEL_SCALE = 8;

			std::vector<QtUIObject*> objs;

		public:
			QtGameMap(const int height, const int width, QWidget* parent = nullptr);

			void add_obj(QtUIObject* obj);
			void clear() noexcept override;
			void refresh() noexcept override;
			void remove_obj(QtUIObject* obj);
			void remove_objs() override;
			void show() const noexcept override;

		protected:
			void paintEvent(QPaintEvent* event) override;
	};
}
