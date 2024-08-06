#include "Physics-Constants.hpp"
#include <GolfBall.hpp>

bool GolfBall::m_is_moving() {
    return std::abs(speed.x()) > Physics::SIGMA || std::abs(speed.y()) > Physics::SIGMA;
}

const QRectF GolfBall::bounding_box() const {
    return QRectF(
        position.toPointF() - QPointF(radius, radius),
        position.toPointF() + QPointF(radius, radius)
    );
}

bool GolfBall::detect_collision(const GolfBall& other) const {
    return bounding_box().intersects(other.bounding_box());
}

bool GolfBall::detect_collision(const QRectF& other) const {
    return bounding_box().intersects(other);
}

bool GolfBall::detect_collision(const GolfStructure& other) const {
    return other.m_polygon.intersects({bounding_box()});
}

