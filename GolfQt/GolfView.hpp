#pragma once

#include <QGraphicsView>
#include <QTimer>
#include <QLabel>
#include <QPolygonF>
#include <QList>
#include <QVBoxLayout>
#include <qboxlayout.h>
#include <qelapsedtimer.h>
#include <qgraphicsview.h>
#include <qpoint.h>
#include <qwidget.h>
#include "widgets/GolfAimArrow.hpp"
#include "widgets/GolfStrokes.hpp"
#include "widgets/GolfForceBar.hpp"

#include "GolfCamera.hpp"
#include "GolfMap.hpp"
#include "GolfScene.hpp"

#include "Physics.hpp"

class GolfView : public QWidget {
    Q_OBJECT

public:
    GolfView(QWidget* parent = nullptr);
    ~GolfView();
    GolfScene* m_gameScene = nullptr;
    QGraphicsView* m_graphics_view = nullptr;
    QVBoxLayout* m_game_layout = nullptr;
    GolfStrokes* m_strokes_board = nullptr;
    GolfForceBar* m_golf_bar;

    void load_map(const GolfMap& map);

private:
    QTimer m_render_timer;
    std::vector<double> m_fps_queue{{60.0, 60.0, 60.0, 60.0, 60.0}};
    double m_border = 200;

    std::vector<QGraphicsItem*> m_golf_balls{};
    std::vector<QGraphicsItem*> m_static_walls{};
    std::vector<QGraphicsItem*> m_static_floors{};
    std::vector<Physics::Object> m_objects{};
    GolfMap m_map;
    GolfCamera m_camera;

    QElapsedTimer m_fps_timer;
    QLabel m_fps_label;

    QPoint initialMousePos;
    QPoint currentMousePos;

    bool m_is_moving = false;
    GolfAimArrow* m_aim_arrow;

    void render_static_map();
    void render_objects();
    QPointF get_cursor();
    int calculateForceFromMouseMovement();

protected:
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

public slots:
    void receive_objects(std::vector<Physics::Object>);
    void receive_is_moving(bool is_moving);
    void update_strokes(int strokes);

signals:
    void clicked_impulse(QPointF impulse);
};
