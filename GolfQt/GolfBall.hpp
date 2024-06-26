#pragma once
#include "Physics.hpp"

class GolfBall : public Physics::Object {
public:
    GolfBall(double mass, Vec2d position, Vec2d velocity) : Physics::Object(mass, position, velocity) {
        radius = 6;
    }
    GolfBall(double mass) : Physics::Object(mass) {}
    GolfBall(const GolfBall& other) : Physics::Object(other) {}
    GolfBall(GolfBall&& other) noexcept : Physics::Object(std::move(other)) {}
    GolfBall(const Physics::Object& other) : Physics::Object(other) {
        radius = 6;
    }
    ~GolfBall() {}
};

