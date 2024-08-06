#pragma once
#include "GolfStructure.hpp"

#include <QRectF>
#include <QList>
#include <QPointF>

class GolfWall : public GolfStructure {
public:
    GolfWall(QList<QPointF> points, std::string material, double restitution)
        : m_material(material), GolfStructure(points, restitution)
    {}
    GolfWall(const GolfWall& other) : m_material(other.m_material), GolfStructure(other) {}
    GolfWall& operator=(const GolfWall& wall);
    
    QRectF rect() const;
    const QRectF bounding_box() const override;
    bool detect_collision(const Physics::Object& other) const override {
        return detect_collision(other);
    }

    std::string material() const {
        return m_material;
    }

private:
    QRectF m_rect;
    std::string m_material;
};
