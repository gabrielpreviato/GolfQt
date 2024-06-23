#pragma once

#include <QGraphicsView>
#include <QTimer>
#include <QPolygonF>
#include <QList>

#include "GolfMap.hpp"
#include "GolfScene.hpp"

#include "Physics.hpp"
#include "Structure.hpp"

#include <algorithm> // for copy() and assign()  
#include <iterator>

class GolfView : public QGraphicsView {
    Q_OBJECT

public:
    GolfView(const GolfMap& map, QWidget* parent = nullptr);
    ~GolfView();
    GolfScene* m_gameScene = nullptr;

private:
    QTimer m_render_timer;

    std::vector<QGraphicsItem*> m_golf_balls{};
    std::vector<Physics::Object> m_objects{};
    GolfMap m_map;

    void render_objects();

protected:
    void mouseReleaseEvent(QMouseEvent* event) override;

public slots:
    void receive_objects(std::vector<Physics::Object>);
    void receive_walls(std::vector<Physics::Structure>);

signals:
    void clicked_impulse(QPointF cursor_pos);
};
