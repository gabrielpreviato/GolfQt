#include "GolfEngine.hpp"
#include "GolfBall.hpp"
#include "GolfMap.hpp"
#include <qDebug>
#include <qlogging.h>

GolfEngine::GolfEngine()
    : m_engine_timer(QTimer(this))
{}

GolfEngine::~GolfEngine() {
    qDebug() << "QGolf destructor";
}

void GolfEngine::load_map(const GolfMap& map)
{
    m_hash = SpatialHashMap(map.m_width, map.m_height, 20);
    m_floor_hash = SpatialHashMap(map.m_width, map.m_height, 20);
    m_map = map;
    
    auto o = GolfBall(1, map.m_start / 100, Vec2d(0, 0));
    m_objects = std::vector<Physics::Object>{o};

    connect(&m_engine_timer, &QTimer::timeout, this, &GolfEngine::run_tick);
    
    for (auto& wall : m_map.m_walls) {
        auto n_cells = m_hash.add_structure(wall);
        qDebug() << "Number of cells: " << n_cells;
    }

    for (auto& floor : m_map.m_floors) {
        m_floor_hash.add_structure(floor);
    }
}

double GolfEngine::get_floor_friction(const Vec2d& position) {
    qDebug() << "Getting floor friction";
    auto& floor = m_floor_hash.get_floor(position);
    return floor.m_friction;    
}

void GolfEngine::run_tick() {
    for (auto& o : m_objects) {
		GolfBall future_o{o};
        qDebug() << "future_o radius is: " << future_o.radius;

        if (std::abs(future_o.speed.x) > Physics::SIGMA || std::abs(future_o.speed.y) > Physics::SIGMA) {
            Vec2d friction = (future_o.speed * (-1.0)).unit() * get_floor_friction(future_o.position * 100);
            qDebug() << "friction is: " << friction.x << ", " << friction.y;
            future_o.tick(friction);
            qDebug() << "future_o speed is: " << future_o.speed.x << ", " << future_o.speed.y;
            qDebug() << "future_o friction is: " << friction.x << ", " << friction.y;
            future_o.m_is_moving = true;
            emit is_moving(true);
        }
        else {
            future_o.tick(Vec2d(0, 0));
            future_o.m_is_moving = false;
            emit is_moving(false);
        }
        //qDebug() << "o position x is: " << o.position.x ;
        //qDebug() << "o speed x is: " << o.speed.x;
        auto possible_collisions = m_hash.broad_collision(future_o);
        qDebug() << "Possbile collision objects: " << possible_collisions.size();
        for (auto& wall : possible_collisions) {
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
				
                Vec2d collisionNormal = wall->get_normal(edge); // You need to implement get_normal() based on your wall structure

                auto new_speed = future_o.speed.reflect(collisionNormal);
                new_speed = new_speed * (future_o.speed.length() / new_speed.length());

                future_o.speed = new_speed * wall->m_restitution;
                future_o.position -= collisionNormal * 0.01; // Adjust the multiplier as needed
            }
        }

        qDebug() << "o radius is: " << o.radius;
        o.speed = future_o.speed;
        o.position = future_o.position;

        if ((m_map.m_end.x/100 - 0.1 <= future_o.position.x && future_o.position.x <= m_map.m_end.x/100 + 0.1) && 
            (m_map.m_end.y/100 - 0.1 <= future_o.position.y && future_o.position.y <= m_map.m_end.y/100 + 0.1) && 
            !future_o.m_is_moving) {
            stop();
        }
    }

    emit objects(m_objects);
}

void GolfEngine::run() {
    qDebug() << "Hello World!";
    qDebug() << "Gravity is: " << Physics::GRAVITY;
    m_engine_timer.start(1000*Physics::TICK_RATE);
}

void GolfEngine::player_impulse(QPointF cursor_pos) {
    auto& ball = m_objects[0];

    QPointF imp_vector_cm = QPointF(ball.position.x * 100, ball.position.y * 100) - cursor_pos;
    QPointF imp_vector_m = imp_vector_cm / 100;

    ball.give_impulse(Vec2d(imp_vector_m.x(), imp_vector_m.y()));
}

void GolfEngine::stop() {
    m_engine_timer.stop();
    qDebug() << "STOP!";
    emit finished();
}
