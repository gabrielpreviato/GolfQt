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
		Physics::Object future_o = o;

        if (std::abs(future_o.speed.x) > Physics::SIGMA || std::abs(future_o.speed.y) > Physics::SIGMA) {
            Vec2d friction = (future_o.speed * (-1.0)).unit();
            future_o.tick(friction);
            qDebug() << "future_o speed is: " << future_o.speed.x << ", " << future_o.speed.y;
            qDebug() << "future_o friction is: " << friction.x << ", " << friction.y;
        }
        else {
            future_o.tick(Vec2d(0, 0));
        }
        //qDebug() << "o position x is: " << o.position.x ;
        //qDebug() << "o speed x is: " << o.speed.x;
        auto possible_collisions = m_hash.broad_collision(future_o);
        qDebug() << "Possbile collision objects: " << possible_collisions.size();
        for (auto& wall : possible_collisions) {
            wall->set_color(QColor(255, 0, 0, 127));
        }

		if (possible_collisions.size() > 0) {
			o.speed = Vec2d(0, 0);
		}
		else {
			o.speed = future_o.speed;
			o.position = future_o.position;
		}

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
