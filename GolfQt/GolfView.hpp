#pragma once

#include <QGraphicsView>
#include <QTimer>
#include <QPolygonF>
#include <QList>

#include "GolfCamera.hpp"
#include "GolfMap.hpp"
#include "GolfScene.hpp"

#include "Physics.hpp"

class GolfView : public QGraphicsView {
    Q_OBJECT

public:
    GolfView(QWidget* parent = nullptr);
    ~GolfView();
    GolfScene* m_gameScene = nullptr;

    void load_map(const GolfMap& map);

private:
    QTimer m_render_timer;
    double m_border = 200;

    std::vector<QGraphicsItem*> m_golf_balls{};
    std::vector<QGraphicsItem*> m_static_walls{};
    std::vector<QGraphicsItem*> m_static_floors{};
    std::vector<Physics::Object> m_objects{};
    GolfMap m_map;
    GolfCamera m_camera;

    bool m_is_moving = false;

    void render_static_map();
    void render_objects();
    QPointF get_cursor();

protected:
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

public slots:
    void receive_objects(std::vector<Physics::Object>);
    void receive_is_moving(bool is_moving);

signals:
    void clicked_impulse(QPointF cursor_pos);
};
