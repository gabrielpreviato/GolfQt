#include "GolfEngine.hpp"
#include "GolfBall.hpp"
#include "GolfMap.hpp"
#include "Physics-Constants.hpp"
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
    m_hash = CollisionHashMap(map.m_width, map.m_height, 20);
    m_floor_hash = FloorHashMap(map.m_width, map.m_height, 20);
    m_map = map;
    
    auto o = GolfBall(1, QVector2D(map.m_start.x(), map.m_start.y()), QVector2D(0, 0));
    m_balls = std::vector<GolfBall>{o};

    connect(&m_engine_timer, &QTimer::timeout, this, &GolfEngine::run_tick);
    
    for (auto& wall : m_map.m_walls) {
        auto n_cells = m_hash.add_structure(wall);
        qDebug() << "Number of cells: " << n_cells;
    }

    for (auto& floor : m_map.m_floors) {
        m_floor_hash.add_structure(floor);
    }
}

double GolfEngine::get_floor_friction(const QVector2D& position) const {
    auto& floor = m_floor_hash.get_floor(position);
    return floor.friction();    
}

void GolfEngine::run_tick() {
    for (auto& ball : m_balls) {
		GolfBall future_ball{ball};

        if (future_ball.m_is_moving()) {
            double floor_friction = get_floor_friction(future_ball.position);
            QVector2D friction = (future_ball.speed * (-1.0)).normalized() * floor_friction;
            qDebug() << "Friction: " << friction;
            future_ball.tick(friction);
            qDebug() << "Ball speed after tick: " << future_ball.speed;
        }
        else {
            future_ball.tick(QVector2D(0, 0));
        }
        //qDebug() << "o position x is: " << o.position.x ;
        //qDebug() << "o speed x is: " << o.speed.x;
        auto possible_collisions = m_hash.broad_collision(future_ball);
        for (auto& wall : possible_collisions) {
            auto bbox = future_ball.bounding_box();

            if (future_ball.detect_collision(*wall)) {
                auto ball_position = QPointF(future_ball.position.x(), future_ball.position.y());
                int edge = wall->detect_collision_edge(ball_position);
				while (edge == -1) {
                    future_ball.reverse_tick(0.2);
					edge = wall->detect_collision_edge(ball_position);
				}
				
                QPointF collisionNormal = wall->get_normal(edge); // You need to implement get_normal() based on your wall structure

                auto new_speed = future_ball.speed - 2 * QVector2D::dotProduct(future_ball.speed, QVector2D(collisionNormal.x(), collisionNormal.y())) * QVector2D(collisionNormal.x(), collisionNormal.y());
                
                if (new_speed.length() < 0.1) {
                    new_speed = QVector2D(0, 0);
                } else {
                    new_speed = new_speed * (future_ball.speed.length() / new_speed.length());
                }

                qDebug() << "New speed: " << new_speed;
                qDebug() << "New speed * wall->m_restitution: " << new_speed * wall->m_restitution;
                //exit(0);

                future_ball.speed = new_speed * wall->m_restitution;
                future_ball.position = future_ball.position + QVector2D(collisionNormal.x(), collisionNormal.y()); // Adjust the multiplier as needed
            }
        }

        ball.speed = future_ball.speed;
        ball.position = future_ball.position;

        qDebug() << "Ball speed: " << ball.speed;
        qDebug() << "future_ball speed: " << future_ball.speed;

        if ((m_map.m_end.x() - 1 <= future_ball.position.x() && future_ball.position.x() <= m_map.m_end.x() + 1) && 
            (m_map.m_end.y() - 1 <= future_ball.position.y() && future_ball.position.y() <= m_map.m_end.y() + 1) && 
            !future_ball.m_is_moving()) {
            stop();
        }
    }

    emit objects(m_balls);
}

void GolfEngine::run() {
    m_engine_timer.start(1000*Physics::TICK_RATE);
}

void GolfEngine::player_impulse(QPointF impulse) {
    auto& ball = m_balls[0];

    QPointF imp_vector_m = impulse * 5;

    ball.give_impulse(QVector2D(imp_vector_m.x(), imp_vector_m.y()));
}

void GolfEngine::stop() {
    m_engine_timer.stop();
    qDebug() << "STOP!";
    emit finished();
}
