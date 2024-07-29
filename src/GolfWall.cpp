#include "GolfWall.hpp"

QRectF GolfWall::rect() const {
    return m_polygon.boundingRect();
}
