#include "message_widget.hpp"

#include <QLabel>
#include <QLayout>
#include <QLineEdit>

MessageWidget::MessageWidget(QWidget* parent) : QWidget(parent) {
	// TODO: your code here...
	view = new QLineEdit();
	auto smslayout = new QHBoxLayout(this);
	auto sms = new QLabel("Message:");

	smslayout->addWidget(sms);
	smslayout->addWidget(view);
	view->clear();
	setLayout(smslayout);
	view->setReadOnly(true);
}

void MessageWidget::info(QString message) {
	// TODO: your code here...
	view->setText(message);
}

void MessageWidget::error(QString message) {
	// TODO: your code here...
	view->setText(message);
	view->selectAll();

	auto palette = new QPalette();
	palette->setColor(QPalette::Highlight, Qt::red);
	palette->setColor(QPalette::WindowText, Qt::red);
	view->setPalette(*palette);
}

void MessageWidget::clear() {
	// TODO: your code here...
	view->clear();

	auto palette = new QPalette();
	palette->setColor(QPalette::Text, Qt::black);
	view->setPalette(*palette);
}