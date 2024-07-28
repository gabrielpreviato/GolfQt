#include "Physics.hpp"
#include "Physics-Constants.hpp"
#include <qobject.h>
namespace Physics {

    double Object::kinetic_energy() {
        return mass * QVector2D::dotProduct(speed, speed) / 2;
    }

    double Object::gravitational_energy() {
        return mass * GRAVITY * position.y();
    }

    double Object::energy() {
        return kinetic_energy() + gravitational_energy();
    }

    QVector2D Object::momemtum() {
        return speed * mass;
    }

    void Object::give_impulse(QVector2D&& impulse) {
        speed = speed + impulse / mass;
    }

    void Object::zero_normalize(const double sigma) {
        std::abs(speed.x()) <= sigma ? speed.setX(0.0) : void();
        std::abs(speed.y()) <= sigma ? speed.setY(0.0) : void();
    }

    void Object::tick(const QVector2D& force) {
        position += speed * TICK_RATE;
        speed += force * TICK_RATE;

        zero_normalize(SIGMA);
    }

    void Object::reverse_tick(double rate) {
        position -= speed * TICK_RATE * rate;
    }
}

