#pragma once
#include <QGraphicsScene>
#include <QPoint>
#include <QGraphicsSceneMouseEvent>
#include <QPainterPath>
#include <qDebug>

class GolfScene : public QGraphicsScene {
    Q_OBJECT

public:
    GolfScene(QObject* parent = nullptr);

    QGraphicsLineItem* addLine(const QLineF& line);
    QGraphicsPolygonItem* addPolygon(const QPolygonF& polygon, const QPen& pen = QPen(), const QBrush& brush = QBrush());
    QGraphicsEllipseItem* addEllipse(const QRectF& ellipse, const QPen& pen = QPen(), const QBrush& brush = QBrush());
    QGraphicsPathItem* addPath(const QPainterPath& path, const QPen& pen = QPen(), const QBrush& brush = QBrush());
};

