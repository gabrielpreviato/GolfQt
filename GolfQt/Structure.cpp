#include "Structure.hpp"

Physics::Structure::Structure(Vec2d v1, Vec2d v2, Vec2d v3, Vec2d v4)
    : v1(v1), v2(v2), v3(v3), v4(v4), 
    e1(Line2d(v1, v2)), e2(Line2d(v2, v3)), e3(Line2d(v3, v4)), e4(Line2d(v4, v1))
{
    m_edges = {e1, e2, e3, e4};
}

Physics::Structure::Structure(std::vector<Vec2d> points)
{
    if (points.size() != 4) {
        throw std::invalid_argument("Structure must have 4 points");
    }
    v1 = points[0];
    v2 = points[1];
    v3 = points[2];
    v4 = points[3];
    e1 = Line2d(v1, v2);
    e2 = Line2d(v2, v3);
    e3 = Line2d(v3, v4);
    e4 = Line2d(v4, v1);

    m_edges = {e1, e2, e3, e4};
}
