#pragma once

#include <QGraphicsItem>
#include <QPen>
#include <QWidget>

class GolfAimArrow : public QGraphicsItem {
private:
    QGraphicsLineItem* m_line;
public:
    GolfAimArrow(QGraphicsItem *parent = nullptr);
    ~GolfAimArrow();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setAngle(qreal angle, const QPointF& initial_pos);
};
