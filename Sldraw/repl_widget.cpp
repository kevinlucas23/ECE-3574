#include "repl_widget.hpp"
#include "main_window.hpp"

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QLayout>
#include <QKeyEvent>

REPLWidget::REPLWidget(QWidget* parent) : QWidget(parent) {
	// TODO: your code here
	view = new QLineEdit();

	auto layout = new QHBoxLayout;
	auto script = new QLabel("vtscript>");

	layout->addWidget(script);
	layout->addWidget(view);
	this->setLayout(layout);

	view->setFocus();
	connect(view, &QLineEdit::returnPressed, this, &REPLWidget::changed);
}

void REPLWidget::changed() {
	// TODO: your code here
	auto onscreen = view->text();
	if (!onscreen.isEmpty()) {
		see.add(onscreen);
		emit lineEntered(onscreen);
		view->clear();
	}
}

void REPLWidget::keyPressEvent(QKeyEvent* event) {
	if (event->key() == Qt::Key_Up) {
		if (see.up()) {
			view->setText(see.present());
		}
	}
	else if (event->key() == Qt::Key_Down) {
		if (see.down()) {
			view->setText(see.present());
		}
	}
}