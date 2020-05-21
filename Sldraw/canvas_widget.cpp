#include "canvas_widget.hpp"

#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLayout>

CanvasWidget::CanvasWidget(QWidget* parent) : QWidget(parent) {
	// TODO: your code here...
	scene = new QGraphicsScene(this);
	auto view = new QGraphicsView(scene);
	auto layout = new QVBoxLayout;

	layout->addWidget(view);
	setLayout(layout);
}

void CanvasWidget::addGraphic(QGraphicsItem* item) {
	// TODO: your code here...
	scene->addItem(item);
}

void CanvasWidget::clearing() {
	scene->clear();
}