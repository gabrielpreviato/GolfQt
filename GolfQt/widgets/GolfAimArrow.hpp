#pragma once

#include <QGraphicsItem>
#include <QPen>
#include <qlogging.h>

class GolfAimArrow : public QGraphicsItem {
private:
    QGraphicsLineItem* m_line;
public:
    GolfAimArrow(QGraphicsItem *parent = nullptr) 
        : QGraphicsItem(parent), m_line(new QGraphicsLineItem(this))
    {
        m_line->setPen(QPen(Qt::red, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }

    ~GolfAimArrow()
    {}

    QRectF boundingRect() const override
    {
        return m_line->boundingRect();
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override
    {
        m_line->paint(painter, option, widget);
    }

    void setAngle(qreal angle, const QPointF& initial_pos) {
        // Calculate end points based on the angle and a fixed length
        qreal arrowLength = 50.0; // Adjust as needed
        QPointF endPoint = QPointF(arrowLength * cos(angle), -arrowLength * sin(angle)); // Inverted y-axis for QGraphicsScene
        qDebug() << initial_pos.x();
        m_line->setLine(initial_pos.x(), initial_pos.y(), initial_pos.x() + endPoint.x(), initial_pos.y() + endPoint.y());
    }
};
