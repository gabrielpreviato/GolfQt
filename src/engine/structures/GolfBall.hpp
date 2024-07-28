#pragma once
#include "Physics.hpp"

class GolfBall : public Physics::Object {
public:
    GolfBall(double mass, QVector2D position, QVector2D velocity) : Physics::Object(mass, position, velocity) {}
    GolfBall(double mass) : Physics::Object(mass) {}
    GolfBall(const GolfBall& other) : Physics::Object(other) {}
    GolfBall(GolfBall&& other) noexcept : Physics::Object(std::move(other)) {}
    GolfBall(const Physics::Object& other) : Physics::Object(other) {}
    ~GolfBall() {}

    bool m_is_moving();
    QRectF bounding_box();
    
    double radius = 6;
};

