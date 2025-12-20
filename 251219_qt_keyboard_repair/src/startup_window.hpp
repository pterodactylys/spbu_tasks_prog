#pragma once

#include <cstddef>

#include <QGridLayout>
#include <QWidget>
#include <QPushButton>

namespace biv {
    class StartupWindow : public QWidget {
        Q_OBJECT

        signals:
            void start_requested();

        private:
            int window_width;
            int window_height;

            int button_width;
            int button_height;

            void setup_ui(const int width, const int height);

        public:
            StartupWindow(const int width, const int height, QWidget* parent = nullptr);
            void CreateStartButton(const QString& text, const int width, const int height);
    };
}