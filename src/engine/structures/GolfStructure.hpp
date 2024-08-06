#pragma once
#include <algorithm>

#include <QColor>

#include <QList>
#include <QPolygonF>
#include <QPointF>
#include <QLineF>
#include <qDebug>

#include "Physics.hpp"

class GolfStructure : public Physics::Object {
public:
    QPolygonF m_polygon;
    QList<QPointF> m_vertices;
    QList<QLineF> m_edges;
    double m_restitution = 0;

    GolfStructure(QList<QPointF> points);
    GolfStructure(QList<QPointF> points, double restitution);
    GolfStructure(const GolfStructure& other) : m_polygon(other.m_polygon), m_vertices(other.m_vertices), m_edges(other.m_edges), m_restitution(other.m_restitution), Physics::Object(other) {}
    
    virtual const QRectF bounding_box() const = 0;
    virtual bool detect_collision(const Object& other) const = 0;

    int detect_collision_edge(const QPointF& collidingPoint) const;
    QPointF get_normal(int edge) const;

    GolfStructure& operator=(const GolfStructure& structure) {
        Physics::Object::operator=(structure);
        m_polygon = structure.m_polygon;
        m_vertices = structure.m_vertices;
        m_edges = structure.m_edges;
        m_restitution = structure.m_restitution;

        return *this;
    }
};
