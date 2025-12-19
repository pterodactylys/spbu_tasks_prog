#include "keyboard_window.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QKeyEvent>

using biv::KeyBoardWindow;

KeyBoardWindow::KeyBoardWindow(QWidget* parent) : QWidget(parent) {
	const int keyboard_width = 1160;
	resize(keyboard_width, 710);
    setWindowTitle("Грустная Клавиатура");

	setFocusPolicy(Qt::StrongFocus);
    setFocus();
	
	QPixmap pixmap("img/grustnii-smail.png");
	QLabel* image = new QLabel(this);
	image->setFixedSize(200, 200);
	image->setPixmap(pixmap);
	image->setScaledContents(true);
	
	QHBoxLayout* smail_layout = new QHBoxLayout();
	smail_layout->addWidget(image);

    display = new QLineEdit();
	display->setMinimumHeight(80);
	display->setFont(QFont("Roboto", 40));
    display->setReadOnly(true);
	display->setText("Помоги мне заработать лучше...");

    display->setFocusPolicy(Qt::NoFocus);

    keyboard = new KeyBoard(keyboard_width);
    keyboard->setFocusPolicy(Qt::NoFocus);

    QVBoxLayout* main_layout = new QVBoxLayout(this);
	main_layout->addLayout(smail_layout);
    main_layout->addWidget(display);
    main_layout->addWidget(keyboard);

	connect(keyboard, &KeyBoard::key_pressed, this, [this](int key) {
		if (keyboard -> is_key_allowed(key)) {
			display -> setText(display -> text() + keyboard -> get_key_text(key));
			keyboard -> animate_button(key);
			return;
		}

		if (key == Qt::Key_Backspace) {
			QString current_text = display -> text();
			current_text.chop(1);
			display -> setText(current_text);
			keyboard -> animate_button(key);
			return;
		}
		if (key == Qt::Key_Space) {
			display -> setText(display -> text() + " ");
			keyboard -> animate_button(key);
			return;
		}
	});
}

void KeyBoardWindow::keyPressEvent(QKeyEvent* event) {
    const int key = event->key();
	
	if (key == Qt::Key_Backspace) {
        QString txt = display->text();
        if (!txt.isEmpty()) txt.chop(1);
        display->setText(txt);
        keyboard->animate_button(Qt::Key_Backspace);
        return;
    }

    if (key == Qt::Key_Space) {
        display->setText(display->text() + ' ');
        keyboard->animate_button(Qt::Key_Space);
        return;
    }

    if (key == Qt::Key_Tab) {
        display->setText(display->text() + '\t');
        keyboard->animate_button(Qt::Key_Tab);
        return;
    }

    if (key == Qt::Key_Return || key == Qt::Key_Enter) {
        display->setText(display->text() + ' ');
        keyboard->animate_button(Qt::Key_Return);
        return;
    }

    if (keyboard->is_key_allowed(key)) {
        display->setText(display->text() + keyboard->get_key_text(key));
        keyboard->animate_button(key);
        return;
    }

    const QString txt = event->text();
    if (!txt.isEmpty()) {
        display->setText(display->text() + txt);
    }
}
