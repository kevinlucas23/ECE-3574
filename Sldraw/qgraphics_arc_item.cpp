#include "qgraphics_arc_item.hpp"

#include <cmath>

#include <QDebug>
#include <QPainter>

QGraphicsArcItem::QGraphicsArcItem(qreal x, qreal y, qreal width, qreal height, qreal angle1, qreal angle2, QGraphicsItem* parent) {
	// TODO: your code here ...
	setRect(x, y, width, height);
	setStartAngle((int)angle1);
	setSpanAngle((int)angle2);
}

void QGraphicsArcItem::paint(QPainter* painter,
	const QStyleOptionGraphicsItem* option,
	QWidget* widget) {
	// TODO: your code here ...
	auto bick = new QPen;
	bick->setWidth(2);
	painter->setPen(*bick);
	painter->setBrush(QBrush(Qt::black, Qt::SolidPattern));
	painter->drawArc(rect(), startAngle(), spanAngle());
}