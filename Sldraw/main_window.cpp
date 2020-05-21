#include "main_window.hpp"

#include <iostream>

#include <QLayout>

#include "message_widget.hpp"
#include "canvas_widget.hpp"
#include "repl_widget.hpp"
#include "interpreter_semantic_error.hpp"

MainWindow::MainWindow(QWidget* parent) : MainWindow("", parent) {
	// TODO: your code here...
}

MainWindow::MainWindow(std::string filename, QWidget* parent) : QWidget(parent) {
	// TODO: your code here...
	auto messageView = new MessageWidget;
	auto canvasView = new  CanvasWidget;
	auto replView = new REPLWidget;
	auto layout = new QVBoxLayout;

	QObject::connect(&interp, &QtInterpreter::info, messageView, &MessageWidget::info);
	QObject::connect(&interp, &QtInterpreter::error, messageView, &MessageWidget::error);
	QObject::connect(&interp, &QtInterpreter::clearing, messageView, &MessageWidget::clear);
	QObject::connect(&interp, &QtInterpreter::drawGraphic, canvasView, &CanvasWidget::addGraphic);
	QObject::connect(&interp, &QtInterpreter::cleari, canvasView, &CanvasWidget::clearing);
	QObject::connect(replView, &REPLWidget::lineEntered, &interp, &QtInterpreter::parseAndEvaluate);

	layout->addWidget(messageView);
	layout->addWidget(canvasView);
	layout->addWidget(replView);
	setLayout(layout);

	interp.preload(filename);
}