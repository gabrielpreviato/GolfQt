#pragma once

#include "Vec2.hpp"
#include <QPainterPath>

class GolfFloor {
public:
    QPainterPath m_path;
    std::string m_material;
    double m_friction = 1.0;

public:
    GolfFloor() : m_path(QPainterPath())
    {
        m_path.setFillRule(Qt::WindingFill);
    }
    GolfFloor(double friction, std::string material) : m_path(QPainterPath()), m_friction(friction), m_material(material)
    {
        m_path.setFillRule(Qt::WindingFill);
    }
    GolfFloor(const QPainterPath& path) : m_path(path) {
        m_path.setFillRule(Qt::WindingFill);
    }
    GolfFloor(const GolfFloor& other) : m_path(other.m_path), m_friction(other.m_friction), m_material(other.m_material) {}
    ~GolfFloor() {}

    void add_floor(const QPainterPath& floor) {
        m_path.addPath(floor);
    }

    void add_floor(const QRect& floor) {
        m_path.addRect(floor);
    }

    void add_floor(const QPolygonF& floor) {
        m_path.addPolygon(floor);
    }

    void add_floor(const QPointF& center, int radius) {
        m_path.addEllipse(center, radius, radius);
    }

    void add_floor(const std::vector<Vec2d>& points) {
        m_path.moveTo(points[0].x, points[0].y);
        for (size_t i = 1; i < points.size(); i++) {
            m_path.lineTo(points[i].x, points[i].y);
        }
        m_path.closeSubpath();
    }
};
