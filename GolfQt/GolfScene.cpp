#include "GolfScene.hpp"

GolfScene::GolfScene(QObject* parent) : QGraphicsScene{ parent } {
    setBackgroundBrush(Qt::white);
}

QGraphicsLineItem* GolfScene::addLine(const QLineF& line) {
    auto new_line = line.translated({200, 200});

    return QGraphicsScene::addLine(new_line);
}

QGraphicsPolygonItem* GolfScene::addPolygon(const QPolygonF& polygon, const QPen& pen, const QBrush& brush) {
    auto new_polygon = polygon.translated({200, 200});

    return QGraphicsScene::addPolygon(new_polygon, pen, brush);
}

QGraphicsEllipseItem* GolfScene::addEllipse(const QRectF& ellipse, const QPen& pen, const QBrush& brush) {
    auto new_ellipse = ellipse.translated({200, 200});

    return QGraphicsScene::addEllipse(new_ellipse, pen, brush);
}
