#include "QGolfEngine.hpp"
#include "GolfMap.hpp"
#include <qDebug>

QGolfEngine::QGolfEngine(int argc, char** argv, const GolfMap& map)
    : m_engine_timer(QTimer(this)), m_hash(SpatialHashMap(map.m_width, map.m_height, 20)), m_walls(map.m_walls),
    m_floor_hash(SpatialHashMap(map.m_width, map.m_height, 20))
{
    auto o = Physics::Object(1, Vec2d(1, 1), Vec2d(0, 0));
    o.give_impulse(Vec2d(2, 0));

    m_objects = std::vector<Physics::Object>{o};

    connect(&m_engine_timer, &QTimer::timeout, this, &QGolfEngine::run_tick);
    
    for (auto& wall : m_walls) {
        auto n_cells = m_hash.add_structure(wall);
        qDebug() << "Number of cells: " << n_cells;
    }

    for (auto& floor : map.m_floors) {
        m_floor_hash.add_structure(floor);
    }
}

QGolfEngine::~QGolfEngine() {
    qDebug() << "QGolf destructor";
}

double QGolfEngine::get_floor_friction(const Vec2d& position) {
    qDebug() << "Getting floor friction";
    auto& floor = m_floor_hash.get_floor(position);
    return floor.m_friction;    
}

void QGolfEngine::run_tick() {
    for (auto& o : m_objects) {
		Physics::Object future_o = o;

        if (std::abs(future_o.speed.x) > Physics::SIGMA || std::abs(future_o.speed.y) > Physics::SIGMA) {
            Vec2d friction = (future_o.speed * (-1.0)).unit() * get_floor_friction(future_o.position * 100);
            qDebug() << "friction is: " << friction.x << ", " << friction.y;
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
            auto bbox = future_o.bounding_box();

            if (bbox.projections_overlap(*wall)) {
                int edge = wall->detect_collision_edge(future_o.position * 100);
				while (edge == -1) {
                    future_o.reverse_tick(0.5);
					edge = wall->detect_collision_edge(future_o.position * 100);
				}
                qDebug() << "Collision! " << edge;

				qDebug() << "Wall: " << wall->v1.x << ", " << wall->v1.y << "; " << wall->v2.x << ", " << wall->v2.y << "; " << wall->v3.x << ", " << wall->v3.y << "; " << wall->v4.x << ", " << wall->v4.y;
				qDebug() << "Ball: " << bbox.v1.x << ", " << bbox.v1.y << "; " << bbox.v2.x << ", " << bbox.v2.y << "; " << bbox.v3.x << ", " << bbox.v3.y << "; " << bbox.v4.x << ", " << bbox.v4.y;
                wall->set_color(QColor(255, 255, 0, 127));
				
                Vec2d collisionNormal = wall->get_normal(edge); // You need to implement get_normal() based on your wall structure

                future_o.speed = future_o.speed.reflect(collisionNormal);
                future_o.position -= collisionNormal * 0.01; // Adjust the multiplier as needed
            }
        }

        o.speed = future_o.speed;
        o.position = future_o.position;
    }

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
