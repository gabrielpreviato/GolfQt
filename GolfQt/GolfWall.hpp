#pragma once
#include "Structure.hpp"

class GolfWall : public Physics::Structure {
public:
    std::string m_material;

    GolfWall(Vec2d v1, Vec2d v2, Vec2d v3, Vec2d v4, std::string material, double restitution)
        : m_material(material), Structure(v1, v2, v3, v4, restitution)
    {}

    GolfWall(std::vector<Vec2d> points, std::string material, double restitution)
        : m_material(material), Structure(points, restitution)
    {}
};
