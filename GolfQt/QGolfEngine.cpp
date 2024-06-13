#include "QGolfEngine.hpp"
#include <qDebug>

QGolfEngine::QGolfEngine(int argc, char** argv, std::vector<Physics::Structure> walls)
    : m_engine_timer(QTimer(this)), m_walls(walls), m_hash(SpatialHashMap(400, 400, 20)) {
    auto o = Physics::Object(1, Vec2d(1, 1), Vec2d(0, 0));
    o.give_impulse(Vec2d(2, 0));

    m_objects = std::vector<Physics::Object>{o};

    connect(&m_engine_timer, &QTimer::timeout, this, &QGolfEngine::run_tick);
    
    for (auto& wall : m_walls) {
        auto n_cells = m_hash.add_structure(wall);
        qDebug() << "Number of cells: " << n_cells;
    }
}

QGolfEngine::~QGolfEngine() {
    qDebug() << "QGolf destructor";
}

void QGolfEngine::run_tick() {
    for (auto& o : m_objects) {
        if (std::abs(o.speed.x) > Physics::SIGMA || std::abs(o.speed.y) > Physics::SIGMA) {
            Vec2d friction = (o.speed * (-1.0)).unit();
            o.tick(friction);
            qDebug() << "o speed is: " << o.speed.x << ", " << o.speed.y;
            qDebug() << "o friction is: " << friction.x << ", " << friction.y;
        }
        else {
            o.tick(Vec2d(0, 0));
        }
        //qDebug() << "o position x is: " << o.position.x ;
        //qDebug() << "o speed x is: " << o.speed.x;
    }

    auto possible_collisions = m_hash.broad_collision(m_objects[0]);
    qDebug() << "Possbile collision objects: " << possible_collisions.size();
    for (auto& wall : possible_collisions) {
        wall->set_color(QColor(255, 0, 0, 127));
    }

    emit walls(m_walls);
    emit objects(m_objects);
}

void QGolfEngine::run() {
    qDebug() << "Hello World!";
    qDebug() << "Gravity is: " << Physics::GRAVITY;
    m_engine_timer.start(1000*Physics::TICK_RATE);
}

void QGolfEngine::player_impulse(QPointF cursor_pos) {
    auto& ball = m_objects[0];

    QPointF imp_vector_cm = QPointF(ball.position.x * 100, ball.position.y * 100) - cursor_pos;
    QPointF imp_vector_m = imp_vector_cm / 100;

    ball.give_impulse(Vec2d(imp_vector_m.x(), imp_vector_m.y()));
}

void QGolfEngine::stop() {
    m_engine_timer.stop();
    qDebug() << "STOP!";
    emit finished();
}
