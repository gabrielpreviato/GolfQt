#pragma once
#include <QGraphicsScene>
#include <QPoint>
#include <QGraphicsSceneMouseEvent>
#include <qDebug>

class GolfScene : public QGraphicsScene {
    Q_OBJECT

public:
    GolfScene(QObject* parent = nullptr);
};

