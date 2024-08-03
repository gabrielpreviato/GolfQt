#pragma once
#include "Physics.hpp"
#include "Structure.hpp"

class GolfBall : public Physics::Object {
public:
    GolfBall(double mass, QVector2D position, QVector2D velocity) : Physics::Object(mass, position, velocity) {}
    GolfBall(double mass) : Physics::Object(mass) {}
    GolfBall(const GolfBall& other) : Physics::Object(other) {}
    GolfBall(GolfBall&& other) noexcept : Physics::Object(std::move(other)) {}
    GolfBall(const Physics::Object& other) : Physics::Object(other) {}
    ~GolfBall() {}

    bool m_is_moving();
    const QRectF bounding_box() const override;
    bool detect_collision(const Object& other) const override {
        return detect_collision(other);
    }
    bool detect_collision(const GolfBall& other) const;
    bool detect_collision(const QRectF& other) const;
    bool detect_collision(const Physics::Structure& other) const;
    
    double radius = 6;
};

