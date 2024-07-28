#include "GolfEngine.hpp"
#include "GolfBall.hpp"
#include "GolfMap.hpp"
#include <qDebug>
#include <qlogging.h>
#include <qpoint.h>

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
    auto& floor = m_floor_hash.get_floor(position);
    return floor.m_friction;    
}

void GolfEngine::run_tick() {
    for (auto& o : m_objects) {
		GolfBall future_o{o};

        if (std::abs(future_o.speed.x) > Physics::SIGMA || std::abs(future_o.speed.y) > Physics::SIGMA) {
            Vec2d friction = (future_o.speed * (-1.0)).unit() * get_floor_friction(future_o.position * 100);
            future_o.tick(friction);
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
        for (auto& wall : possible_collisions) {
            auto bbox = future_o.bounding_box();

            if (bbox.projections_overlap(*wall)) {
                int edge = wall->detect_collision_edge(future_o.position * 100);
				while (edge == -1) {
                    future_o.reverse_tick(0.5);
					edge = wall->detect_collision_edge(future_o.position * 100);
				}
				
                Vec2d collisionNormal = wall->get_normal(edge); // You need to implement get_normal() based on your wall structure

                auto new_speed = future_o.speed.reflect(collisionNormal);
                new_speed = new_speed * (future_o.speed.length() / new_speed.length());

                future_o.speed = new_speed * wall->m_restitution;
                future_o.position -= collisionNormal * 0.01; // Adjust the multiplier as needed
            }
        }

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
    m_engine_timer.start(1000*Physics::TICK_RATE);
}

void GolfEngine::player_impulse(QPointF impulse) {
    auto& ball = m_objects[0];

    QPointF imp_vector_m = impulse / 100;

    ball.give_impulse(Vec2d(imp_vector_m.x(), imp_vector_m.y()));
}

void GolfEngine::stop() {
    m_engine_timer.stop();
    qDebug() << "STOP!";
    emit finished();
}