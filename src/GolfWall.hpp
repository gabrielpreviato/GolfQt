#pragma once
#include "Structure.hpp"

#include <QRectF>
#include <QList>
#include <QPointF>

class GolfWall : public Physics::Structure {
public:
    std::string m_material;

    GolfWall(QList<QPointF> points, std::string material, double restitution)
        : m_material(material), Structure(points, restitution)
    {}

    QRectF rect() const;

private:
    QRectF m_rect;
};
