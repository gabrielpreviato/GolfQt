#include "GolfWall.hpp"


GolfWall& GolfWall::operator=(const GolfWall& wall) {
    GolfStructure::operator=(wall);
    m_material = wall.m_material;

    return *this;
}

const QRectF GolfWall::bounding_box() const {
    return m_polygon.boundingRect();
}

