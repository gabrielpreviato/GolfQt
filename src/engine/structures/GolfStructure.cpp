#include <QVector2D>

#include "GolfStructure.hpp"

GolfStructure::GolfStructure(QList<QPointF> points, double restitution)
    : m_restitution(restitution), m_vertices(points), m_polygon(points), Physics::Object(10000)
{
    for (int i = 0; i < points.size(); ++i) {
        m_edges.push_back(QLineF(points[i], points[(i + 1) % points.size()]));
    }

    auto structure_center = m_polygon.boundingRect().center();
    position = QVector2D(structure_center.x(), structure_center.y());
}

GolfStructure::GolfStructure(QList<QPointF> points)
    : GolfStructure(points, 0)
{}

int GolfStructure::detect_collision_edge(const QPointF& collidingPoint) const {
    for (int i = 0; i < m_edges.size(); ++i) {
        QPointF edgeVector = m_vertices[(i + 1) % m_vertices.size()] - m_vertices[i];
        QPointF pointVector = collidingPoint - m_vertices[i];

        // Calculate the cross product
        double cross = edgeVector.x() * pointVector.y() - edgeVector.y() * pointVector.x();

        // Assuming a clockwise definition of edges, a negative cross product
        // indicates the point is on the right (outside) of the edge for a convex shape.
        if (cross < 0) {
            return i; // Return the edge index (1-based for consistency with your get_normal method)
        }
    }

    return -1; // Indicates no external collision detected
}

QPointF GolfStructure::get_normal(int edge) const {
    if (edge < 0 || edge >= m_edges.size()) {
        return QPointF(0, 0);
    }

    QLineF edgeLine = m_edges[edge].normalVector().unitVector();
    return edgeLine.p2() - edgeLine.p1();
}
