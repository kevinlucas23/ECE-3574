#include "qt_interpreter.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <fstream>

#include <QBrush>
#include <QDebug>
#include <QLineEdit>
#include <iostream>
#include <QPainter>

#include "qgraphics_arc_item.hpp"

#include "message_widget.hpp"
#include "interpreter_semantic_error.hpp"
#include "repl_widget.hpp"

QtInterpreter::QtInterpreter(QObject* parent) : QObject(parent) {
	// TODO: your code here...
}

void QtInterpreter::parseAndEvaluate(QString entry) {
	// TODO: your code here...
	std::string text = entry.toStdString();
	std::istringstream iss(text);
	emit clearing();
	if (!text.empty()) {
		parse(iss);
		try {
			Expression result = eval();
			ontheGo();
			draw();
		}
		catch (InterpreterSemanticError & e) {
			emit cleari();
			QString rs = QString::fromStdString(e.what());
			std::cout << e.what() << std::endl;
			emit error(rs);
		}
	}
}

void QtInterpreter::preload(std::string filename)
{
	std::ifstream ifs(filename);
	if (!filename.empty()) {
		emit clearing();
		parse(ifs);
		try {
			Expression result = eval();
			ontheGo();
			draw();
		}
		catch (InterpreterSemanticError & e) {
			emit cleari();
			QString rs = QString::fromStdString(e.what());
			std::cout << e.what() << std::endl;
			emit error(rs);
		}
	}
}

void QtInterpreter::notready() {
	auto result = QString();
	if (ast.head.type == BooleanType) {
		if (ast.head.value.bool_value)
			emit info("(True)");
		else
			emit info("(False)");
	}

	if (ast.head.type == NumberType) {
		auto num = QString::number(ast.head.value.num_value);
		result.append("(" + num + ")");
		emit info(result);
	}

	if (ast.head.type == PointType) {
		result.append("(" + QString::number(ast.head.value.point_value.x) + "," + QString::number(ast.head.value.point_value.y) + ")");
		emit info(result);
	}

	if (ast.head.type == LineType) {
		result.append("((" + QString::number(ast.head.value.line_value.first.x) + "," + QString::number(ast.head.value.line_value.first.y) + "),(" + QString::number(ast.head.value.line_value.second.x) + "," + QString::number(ast.head.value.line_value.second.y) + "))");
		emit info(result);
	}

	if (ast.head.type == ArcType) {
		result.append("((" + QString::number(ast.head.value.arc_value.center.x) + "," + QString::number(ast.head.value.arc_value.center.y) + "),(" + QString::number(ast.head.value.arc_value.start.x) + "," + QString::number(ast.head.value.arc_value.start.y) + ") " + QString::number(ast.head.value.arc_value.span) + ")");
		emit info(result);
	}
}

void QtInterpreter::draw()
{
	if (!graphics.empty()) {
		emit info("(None)");
		for (auto a : graphics) {
			if (a.type == PointType) {
				const qreal r = 2;
				double x = a.value.point_value.x;
				double y = a.value.point_value.y;

				auto point = new QGraphicsEllipseItem(x - r, y - r, 2 * r, 2 * r);
				point->setBrush(QBrush(Qt::black, Qt::SolidPattern));
				emit drawGraphic(point);
			}

			if (a.type == LineType) {
				double x1 = a.value.line_value.first.x;
				double y1 = a.value.line_value.first.y;
				double x2 = a.value.line_value.second.x;
				double y2 = a.value.line_value.second.y;

				auto line = new QGraphicsLineItem(x1, y1, x2, y2);
				auto bick = new QPen;
				bick->setWidth(2);
				bick->setBrush(QBrush(Qt::black, Qt::SolidPattern));
				line->setPen(*bick);
				emit drawGraphic(line);
			}

			if (a.type == ArcType) {
				double x1 = a.value.arc_value.center.x;
				double y1 = a.value.arc_value.center.y;
				double x2 = a.value.arc_value.start.x;
				double y2 = a.value.arc_value.start.y;
				double angle = a.value.arc_value.span;

				qreal radius = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
				qreal x = x1 - radius;
				qreal y = y1 - radius;
				qreal height_width = radius * 2;
				double pi = atan2(0, -1);
				double startangle = (16 * (atan2(y1 - y2, x2 - x1) * (180 / pi)));
				double spanangle = (16 * (angle * (180 / pi)));
				auto arc = new QGraphicsArcItem(x, y, height_width, height_width, startangle, spanangle);
				emit drawGraphic(arc);
			}
		}
	}

	notready();
}