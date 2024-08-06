#pragma once

#include <QPainterPath>

class GolfFloor {
public:
    GolfFloor();
    GolfFloor(double friction, std::string material);
    GolfFloor(const QPainterPath& path);
    GolfFloor(const GolfFloor& other);
    ~GolfFloor() = default;

    void start_path(const QPointF& start);
    void close_path();
    void add_floor(const QPainterPath& floor);
    void add_floor(const QRect& floor);
    void add_floor(const QPolygonF& floor);
    void add_floor(const QPointF& center, int radius);
    void add_floor(const std::vector<QPointF>& points);
    void add_line(const QPointF& start, const QPointF& end);
    void add_cubic(const QPointF& start, const QPointF& end, const QPointF& c1, const QPointF& c2);
    void add_quad(const QPointF& start, const QPointF& end, const QPointF& c1);

    double friction() const { return m_friction; }
    const QPainterPath& path() const { return m_path; }
    std::string material() const { return m_material; }
    
private:
    QPainterPath m_path;
    std::string m_material;
    double m_friction = 1.0;
};

namespace DefaultObjects {
    inline GolfFloor DefaultFloor = GolfFloor(1.0, "default");
}

