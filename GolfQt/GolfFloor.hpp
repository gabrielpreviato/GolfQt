#pragma once

#include <QPainterPath>

class GolfFloor {
private:
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
};
