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

    void add_line(const Vec2d& start, const Vec2d& end) {
        //m_path.moveTo(start.x, start.y);
        m_path.lineTo(end.x, end.y);
        //m_path.closeSubpath();
    }

    void add_cubic(const Vec2d& start, const Vec2d& end, const Vec2d& c1, const Vec2d& c2) {
        //m_path.moveTo(start.x, start.y);
        m_path.cubicTo(c1.x, c1.y, c2.x, c2.y, end.x, end.y);
        //m_path.closeSubpath();
    }

    void add_quad(const Vec2d& start, const Vec2d& end, const Vec2d& c1) {
        //m_path.moveTo(start.x, start.y);
        m_path.quadTo(c1.x, c1.y, end.x, end.y);
        //m_path.closeSubpath();
    }
};

namespace GolfEngine {
    static GolfFloor DefaultFloor = GolfFloor(1.0, "default");
}

