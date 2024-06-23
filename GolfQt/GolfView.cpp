#include "GolfView.hpp"

#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <qDebug>
#include <QCursor>
#include <QMouseEvent>

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

    m_gameScene->setSceneRect(0, 0, 1000, 1000);
    setScene(m_gameScene);

    connect(&m_render_timer, &QTimer::timeout, this, &GolfView::render_objects);
    m_render_timer.start(1000*Physics::TICK_RATE);
}

GolfView::~GolfView() {
    m_render_timer.stop();
    delete m_gameScene;
}

void GolfView::receive_objects(std::vector<Physics::Object> objects) {
    m_objects.clear();
    std::copy(objects.begin(), objects.end(), std::back_inserter(m_objects));
}

void GolfView::receive_walls(std::vector<Physics::Structure> walls) {
    m_walls.clear();
    std::copy(walls.begin(), walls.end(), std::back_inserter(m_walls));
}

void GolfView::render_objects() {
    for (auto& golf_ball : m_golf_balls) {
        m_gameScene->removeItem(golf_ball);
        delete golf_ball;
    }
    m_golf_balls.clear();

    for (auto& object : m_objects) {
        QGraphicsEllipseItem* golf_ball = m_gameScene->addEllipse(QRectF(object.position.x*100-3, object.position.y*100-3, 6, 6));
        golf_ball->setAcceptedMouseButtons(Qt::NoButton);
        //qDebug() << "Redered object:" << object.position.x << ", " << object.position.y;
        m_golf_balls.push_back(golf_ball);
        this->centerOn(m_objects[0].position.x * 100, m_objects[0].position.y * 100);
    }

    QPointF cursor_pos = this->mapToScene(this->mapFromGlobal(QCursor::pos()));
    if (m_objects.size() > 0 && m_objects[0].speed.y == 0 && m_objects[0].speed.x == 0) {
        QGraphicsLineItem* aim_line = m_gameScene->addLine(QLineF(m_objects[0].position.x * 100, m_objects[0].position.y * 100, cursor_pos.x(), cursor_pos.y()));
        aim_line->setAcceptedMouseButtons(Qt::NoButton);
        m_golf_balls.push_back(aim_line);

        QGraphicsEllipseItem* golf_ball = m_gameScene->addEllipse(QRectF(cursor_pos.x()-4, cursor_pos.y()-4, 8, 8));
        golf_ball->setAcceptedMouseButtons(Qt::NoButton);
        m_golf_balls.push_back(golf_ball); 
    }

    for (auto& wall : m_walls) {
        QGraphicsPolygonItem* polygon = m_gameScene->addPolygon(
            QPolygonF(
                QList<QPointF>{
                    QPointF(wall.v1.x, wall.v1.y), QPointF(wall.v2.x, wall.v2.y),
                    QPointF(wall.v3.x, wall.v3.y), QPointF(wall.v4.x, wall.v4.y)
                }
            ),
            QPen(), QBrush(wall.bg_color)
        );
        m_golf_balls.push_back(polygon);
    }
}

void GolfView::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton)    // Left button...
    {
        QPointF cursor_pos = this->mapToScene(this->mapFromGlobal(QCursor::pos()));

        //qDebug() << "Released: " << cursor_pos.x();

        emit clicked_impulse(cursor_pos);
    }
}
