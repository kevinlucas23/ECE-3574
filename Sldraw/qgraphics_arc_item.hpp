#ifndef QGRAPHIC_ARC_ITEM_HPP
#define QGRAPHIC_ARC_ITEM_HPP

#include <QGraphicsEllipseItem>

class QGraphicsArcItem : public QGraphicsEllipseItem {
public:

	QGraphicsArcItem(qreal x, qreal y, qreal width, qreal height, qreal angle1, qreal angle2, QGraphicsItem* parent = nullptr);

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:
};

#endif