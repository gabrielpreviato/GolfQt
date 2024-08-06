#include "GolfView.hpp"
#include "GolfAimArrow.hpp"
#include "Physics-Constants.hpp"

#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <cmath>
#include <numeric>
#include <qDebug>
#include <QCursor>
#include <QMouseEvent>
#include <QDebug>
#include <qalgorithms.h>
#include <qnamespace.h>
#include <qpoint.h>
#include <qwidget.h>

GolfView::GolfView(QWidget* parent)
    : QWidget(parent), m_graphics_view(new QGraphicsView(this)), m_gameScene(new GolfScene(this)), m_render_timer(QTimer(this)),
    m_game_layout(new QVBoxLayout(this)), m_strokes_board(new GolfStrokes(this)), m_golf_bar(new GolfForceBar()), m_aim_arrow(new GolfAimArrow())
{
    int border = 20;


    m_graphics_view->setMinimumSize(1366 - 2*border, 568);
    m_game_layout->addWidget(&m_fps_label);
    m_game_layout->addWidget(m_graphics_view);
    m_game_layout->addWidget(m_strokes_board);
    m_game_layout->addWidget(m_golf_bar);
    //m_graphics_view->move(border, border);
    adjustSize();

    m_graphics_view->setBackgroundBrush(Qt::white);
    m_graphics_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_graphics_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_graphics_view->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    setFocus();
    grabKeyboard();
    grabMouse();
}

GolfView::~GolfView() {
    m_render_timer.stop();
    delete m_gameScene;
}

void GolfView::load_map(const GolfMap& map)
{
    if (m_render_timer.isActive()) {
        m_render_timer.stop();
    }

    m_map = map;
    m_camera = GolfCamera(m_map, m_border);
    
    render_static_map();

    m_gameScene->setSceneRect(0, 0, m_map.m_width + 400, m_map.m_height + 400);
    m_graphics_view->setScene(m_gameScene);

    connect(&m_render_timer, &QTimer::timeout, this, &GolfView::render_objects);
    //m_render_timer.start(1);
    m_render_timer.start(1000*Physics::TICK_RATE);
    m_fps_timer.start();
}

void GolfView::render_static_map() {
    for (auto& floor : m_map.m_floors) {
        auto brush = QBrush();
        brush.setTextureImage(m_map.m_materials[floor.material()].m_texture);
        QGraphicsPathItem* path = m_gameScene->addPath(
            floor.path(),
            QPen(), brush
        );

        m_static_floors.push_back(path);
    }
    qDebug() << m_static_floors.size();

    for (auto& wall : m_map.m_walls) {
        auto brush = QBrush();
        brush.setTextureImage(m_map.m_materials[wall.material()].m_texture);
        QGraphicsPolygonItem* polygon = m_gameScene->addPolygon(
            wall.m_polygon,
            QPen(), brush
        );

        // painter.drawImage(polygon->boundingRect(), *(m_map.m_textures["wood"]));
        m_static_walls.push_back(polygon);
    }

    m_gameScene->addItem(m_aim_arrow);    // auto painter = QPainter();
}

void GolfView::receive_objects(std::vector<GolfBall> objects) {
    m_balls.clear();
    std::copy(objects.begin(), objects.end(), std::back_inserter(m_balls));
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

    if (m_is_aiming) {
        m_aim_arrow->setVisible(true);
    } else {
        m_aim_arrow->setVisible(false);
    }

    for (auto& object : m_balls) {
        QGraphicsEllipseItem* golf_ball = m_gameScene->addEllipse(QRectF(object.position.x()-object.radius, object.position.y()-object.radius, object.radius*2, object.radius*2), QPen(Qt::black), QBrush(Qt::white));
        golf_ball->setAcceptedMouseButtons(Qt::NoButton);
        //qDebug() << "Redered object:" << object.position.x << ", " << object.position.y;
        m_golf_balls.push_back(golf_ball);
        const QRectF& golf_rect = golf_ball->rect();
        if (m_camera.m_mode == CameraMode::CAMERA_MODE_FOLLOW) {
            m_camera.m_position = {golf_rect.x() + golf_rect.width()/2, golf_rect.y() + golf_rect.height()/2};
        }
    }


    if (m_camera.m_mode == CameraMode::CAMERA_MODE_FREE) {
        m_camera.move();
    }
    m_graphics_view->centerOn(m_camera.m_position.x(), m_camera.m_position.y());

    qint64 elapsedMs = m_fps_timer.elapsed(); // Time in milliseconds
    double frameTimeSeconds = elapsedMs / 1000.0; 
    double fps = 1.0 / frameTimeSeconds;
    m_fps_queue.pop_back();
    m_fps_queue.insert(m_fps_queue.begin(), fps);

    double fps_avg = std::accumulate(m_fps_queue.begin(), m_fps_queue.end(), 0.0) / m_fps_queue.size();

    qDebug() << "FPS (avg 5):" << fps_avg;
    m_fps_label.setText(QString("FPS: %1").arg(fps_avg, 0, 'f', 2)); 
    m_fps_timer.start();
}

void GolfView::update_strokes(int strokes) {
    m_strokes_board->set_stroke_count(strokes);
}

void GolfView::mousePressEvent(QMouseEvent* event) {
    qDebug() << event->button() << " " << Qt::LeftButton;
    if (event->button() == Qt::LeftButton && !m_is_moving)    // Left button...
    {
        initialMousePos = event->pos();
        m_golf_bar->setForce(0);
        m_is_aiming = true;
    }
}

void GolfView::mouseMoveEvent(QMouseEvent* event) {
    if (!m_is_moving)    // Left button...
    {
        currentMousePos = event->pos();
        int forceValue = calculateForceFromMouseMovement();
        m_golf_bar->setForce(forceValue);
        qDebug() << forceValue;

        QPointF ballPos = QPointF(m_balls[0].position.x(), m_balls[0].position.y()) + QPointF(200.0, 200.0);

        qreal angle = atan2(ballPos.y() - currentMousePos.y(), currentMousePos.x() - ballPos.x());
        m_aim_arrow->setAngle(angle, ballPos);
    }
}

int GolfView::calculateForceFromMouseMovement() {
    int delta_x = std::abs(currentMousePos.x() - initialMousePos.x());
    int delta_y = std::abs(currentMousePos.y() - initialMousePos.y());
    int distance = std::sqrt(delta_x * delta_x + delta_y * delta_y);

    qDebug() << "Distance: " << distance;

    // Adjust the following parameters to fine-tune the force calculation:
    int maxForce = 100;
    int sensitivity = 5; // Higher value means more sensitive movement

    int forceValue = std::max(0, std::min(maxForce, distance / sensitivity));
    return forceValue;
}

void GolfView::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton && !m_is_moving)    // Left button...
    {
        QPointF cursor_pos = get_cursor();
        QPointF ballPos = m_golf_balls[0]->pos();

        qDebug() << "Released: " << cursor_pos.x();

        auto angle = m_aim_arrow->angle();
        QPointF direction = QPointF(std::cos(angle), std::sin(angle));
        double size = std::sqrt(direction.x() * direction.x() + direction.y() * direction.y());

        emit clicked_impulse(direction / size * m_golf_bar->m_force);
        m_is_aiming = false;
        m_golf_bar->setForce(0);
    }
}

void GolfView::keyPressEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat()) {
        event->ignore();
        return;
    }

    auto key = event->key();
    switch (key) {
    case Qt::Key_C:
        // do your stuff here
        m_camera.switch_mode();
        break;
    case Qt::Key_W:
        // do your stuff here
        m_camera.move_up();
        break;
    case Qt::Key_S:
        // do your stuff here
        m_camera.move_down();
        break;
    case Qt::Key_A:
        // do your stuff here
        m_camera.move_left();
        break;
    case Qt::Key_D:
        // do your stuff here
        m_camera.move_right();
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }
}

void GolfView::keyReleaseEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat()) {
        event->ignore();
        return;
    }

    auto key = event->key();
    switch (key) {
    case Qt::Key_W:
        // do your stuff here
        m_camera.stop_up();
        break;
    case Qt::Key_S:
        // do your stuff here
        m_camera.stop_down();
        break;
    case Qt::Key_A:
        // do your stuff here
        m_camera.stop_left();
        break;
    case Qt::Key_D:
        // do your stuff here
        m_camera.stop_right();
        break;
    default:
        QWidget::keyReleaseEvent(event);
        break;
    }
}

QPointF GolfView::get_cursor() {
    QPointF cursor_pos = m_graphics_view->mapToScene(this->mapFromGlobal(QCursor::pos()));

    return cursor_pos;// - QPointF(m_border, m_border);
}

