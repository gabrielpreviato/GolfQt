#include "GolfFloor.hpp"

GolfFloor::GolfFloor() : m_path(QPainterPath())
{
    m_path.setFillRule(Qt::WindingFill);
}
GolfFloor::GolfFloor(double friction, std::string material) : m_path(QPainterPath()), m_friction(friction), m_material(material)
{
    m_path.setFillRule(Qt::WindingFill);
}
GolfFloor::GolfFloor(const QPainterPath& path) : m_path(path) {
    m_path.setFillRule(Qt::WindingFill);
}
GolfFloor::GolfFloor(const GolfFloor& other) : m_path(other.m_path), m_friction(other.m_friction), m_material(other.m_material) {}

void GolfFloor::start_path(const QPointF& start)
{
    m_path.moveTo(start);
}

void GolfFloor::close_path()
{
    m_path.closeSubpath();
}

void GolfFloor::add_floor(const QPainterPath& floor) {
    m_path.addPath(floor);
}

void GolfFloor::add_floor(const QRect& floor) {
    m_path.addRect(floor);
}

void GolfFloor::add_floor(const QPolygonF& floor) {
    m_path.addPolygon(floor);
}

void GolfFloor::add_floor(const QPointF& center, int radius) {
    m_path.addEllipse(center, radius, radius);
}

void GolfFloor::add_floor(const std::vector<QPointF>& points) {
    m_path.moveTo(points[0].x(), points[0].y());
    for (size_t i = 1; i < points.size(); i++) {
        m_path.lineTo(points[i].x(), points[i].y());
    }
    m_path.closeSubpath();
}

void GolfFloor::add_line(const QPointF& start, const QPointF& end) {
    //m_path.moveTo(start.x, start.y);
    m_path.lineTo(end.x(), end.y());
    //m_path.closeSubpath();
}

void GolfFloor::add_cubic(const QPointF& start, const QPointF& end, const QPointF& c1, const QPointF& c2) {
    //m_path.moveTo(start.x, start.y);
    m_path.cubicTo(c1.x(), c1.y(), c2.x(), c2.y(), end.x(), end.y());
    //m_path.closeSubpath();
}

void GolfFloor::add_quad(const QPointF& start, const QPointF& end, const QPointF& c1) {
    //m_path.moveTo(start.x, start.y);
    m_path.quadTo(c1.x(), c1.y(), end.x(), end.y());
    //m_path.closeSubpath();
}
