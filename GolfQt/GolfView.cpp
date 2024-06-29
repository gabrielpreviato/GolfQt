#include "GolfView.hpp"

#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <qDebug>
#include <QCursor>
#include <QMouseEvent>
#include <qlogging.h>
#include <qpoint.h>

GolfView::GolfView(const GolfMap& map, QWidget* parent)
    : QGraphicsView{ parent }, m_gameScene(new GolfScene(this)), m_render_timer(QTimer(this)),
    m_map(map)
{
    resize(400, 400);
    move(100, 100);

    setBackgroundBrush(Qt::white);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setAlignment(Qt::AlignTop | Qt::AlignLeft);

    render_static_map();

    m_gameScene->setSceneRect(0, 0, m_map.m_width + 400, m_map.m_height + 400);
    setScene(m_gameScene);

    connect(&m_render_timer, &QTimer::timeout, this, &GolfView::render_objects);
    m_render_timer.start(1000*Physics::TICK_RATE);
}

GolfView::~GolfView() {
    m_render_timer.stop();
    delete m_gameScene;
}

void GolfView::render_static_map() {
    for (auto& floor : m_map.m_floors) {
        auto brush = QBrush();
        brush.setTextureImage(m_map.m_materials[floor.m_material].m_texture);
        QGraphicsPathItem* path = m_gameScene->addPath(
            floor.m_path,
            QPen(), brush
        );

        m_static_floors.push_back(path);
    }

    for (auto& wall : m_map.m_walls) {
        auto brush = QBrush();
        brush.setTextureImage(m_map.m_materials[wall.m_material].m_texture);
        QGraphicsPolygonItem* polygon = m_gameScene->addPolygon(
            QPolygonF(
                QList<QPointF>{
                    QPointF(wall.v1.x, wall.v1.y), QPointF(wall.v2.x, wall.v2.y),
                    QPointF(wall.v3.x, wall.v3.y), QPointF(wall.v4.x, wall.v4.y)
                }
            ),
            QPen(), brush
        );

        // auto painter = QPainter();
        // painter.drawImage(polygon->boundingRect(), *(m_map.m_textures["wood"]));
        m_static_walls.push_back(polygon);
    }
}

void GolfView::receive_objects(std::vector<Physics::Object> objects) {
    m_objects.clear();
    std::copy(objects.begin(), objects.end(), std::back_inserter(m_objects));
}

void GolfView::receive_is_moving(bool is_moving) {
    m_is_moving = is_moving;
}

void GolfView::render_objects() {
    for (auto& golf_ball : m_golf_balls) {
        m_gameScene->removeItem(golf_ball);
        delete golf_ball;
    }
    m_golf_balls.clear();

    for (auto& object : m_objects) {
        qDebug() << "Object radius: " << object.radius;
        QGraphicsEllipseItem* golf_ball = m_gameScene->addEllipse(QRectF(object.position.x*100-object.radius, object.position.y*100-object.radius, object.radius*2, object.radius*2));
        golf_ball->setAcceptedMouseButtons(Qt::NoButton);
        //qDebug() << "Redered object:" << object.position.x << ", " << object.position.y;
        m_golf_balls.push_back(golf_ball);
        qDebug() << "Golf ball new pos: " << golf_ball->scenePos();
        const QRectF& golf_rect = golf_ball->rect();
        if (m_camera.m_mode == CameraMode::CAMERA_MODE_FOLLOW) {
            m_camera.m_position = {golf_rect.x() + golf_rect.width()/2, golf_rect.y() + golf_rect.height()/2};
        }
    }

    if (!m_is_moving) {
        QPointF cursor_pos = get_cursor();
        if (m_objects.size() > 0 && m_objects[0].speed.y == 0 && m_objects[0].speed.x == 0) {
            QGraphicsLineItem* aim_line = m_gameScene->addLine(QLineF(m_objects[0].position.x * 100, m_objects[0].position.y * 100, cursor_pos.x(), cursor_pos.y()));
            aim_line->setAcceptedMouseButtons(Qt::NoButton);
            m_golf_balls.push_back(aim_line);

            QGraphicsEllipseItem* golf_ball = m_gameScene->addEllipse(QRectF(cursor_pos.x()-4, cursor_pos.y()-4, 8, 8));
            golf_ball->setAcceptedMouseButtons(Qt::NoButton);
            m_golf_balls.push_back(golf_ball); 
        }
    }

    this->centerOn(m_camera.m_position.x, m_camera.m_position.y);
}

void GolfView::mouseReleaseEvent(QMouseEvent* event) {
    qDebug() << "is_moving: " << m_is_moving;
    if (event->button() == Qt::LeftButton && !m_is_moving)    // Left button...
    {
        QPointF cursor_pos = get_cursor();

        //qDebug() << "Released: " << cursor_pos.x();

        emit clicked_impulse(cursor_pos);
    }
}

void GolfView::keyPressEvent(QKeyEvent* event)
{
    auto key = event->key();
    switch (key) {
    case Qt::Key_C:
        // do your stuff here
        m_camera.switch_mode();
        qDebug() << "C key pressed";
        qDebug() << "is_moving: " << m_is_moving;
        break;
    case Qt::Key_W:
        // do your stuff here
        m_camera.move_up();
        qDebug() << "W key pressed";
        qDebug() << "is_moving: " << m_is_moving;
        break;
    case Qt::Key_S:
        // do your stuff here
        m_camera.move_down();
        qDebug() << "S key pressed";
        qDebug() << "is_moving: " << m_is_moving;
        break;
    case Qt::Key_A:
        // do your stuff here
        m_camera.move_left();
        qDebug() << "A key pressed";
        qDebug() << "is_moving: " << m_is_moving;
        break;
    case Qt::Key_D:
        // do your stuff here
        m_camera.move_right();
        qDebug() << "D key pressed";
        qDebug() << "is_moving: " << m_is_moving;
        break;
    }
}

QPointF GolfView::get_cursor() {
    QPointF cursor_pos = this->mapToScene(this->mapFromGlobal(QCursor::pos()));

    return cursor_pos - QPointF(200, 200);
}

