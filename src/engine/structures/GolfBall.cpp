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
