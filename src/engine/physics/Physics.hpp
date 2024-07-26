#pragma once
#include <iostream>
#include <cmath>
#include <utility>

#include "Physics-Constants.hpp"
#include "Vec2.hpp"
#include "Structure.hpp"

namespace Physics {

	class Object
	{
	public:
		double radius = 3;
		double mass;
		Vec2d position;
		Vec2d speed;

		Object(double mass) : mass(mass) {};
		Object(double mass, const Vec2d& p, const Vec2d& s) : mass(mass), position(p), speed(s) {};
		Object(double mass, Vec2d&& p, Vec2d&& s) : mass(mass), position(std::move(p)), speed(std::move(s)) {};


		Object(const Object& o) : radius(o.radius), mass(o.mass), position(o.position), speed(o.speed) {};
		Object(Object&& o) noexcept : radius(o.radius), mass(o.mass), position(o.position), speed(o.speed) {};

		double kinetic_energy() {
			return mass * speed.squared();
		}

		double gravitational_energy() {
			return mass * GRAVITY * position.y;
		}

		double energy() {
			return kinetic_energy() + gravitational_energy();
		}

		Vec2d momemtum() {
			return speed * mass;
		}

		void give_impulse(Vec2d&& impulse) {
			speed = speed + impulse / mass;
		}

		void tick(const Vec2d& force) {
			//qDebug() << "Speed before: " << speed.x << "; Position before: " << position.x ;

			position += speed * TICK_RATE;
			speed += force * TICK_RATE;

			//qDebug() << "Speed: " << speed.x << "; Position: " << position.x ;
			speed.zero_normalize(SIGMA);
		}

		void reverse_tick(double rate) {
			//qDebug() << "Speed before: " << speed.x << "; Position before: " << position.x ;

			position -= speed * TICK_RATE * rate;
			//speed -= force * TICK_RATE * rate;

			//qDebug() << "Speed: " << speed.x << "; Position: " << position.x ;
			//speed.zero_normalize(SIGMA);
		}

		Structure bounding_box() {
			return Structure(
				position * 100 - Vec2d(radius, radius),
				position * 100 - Vec2d(0, radius) + Vec2d(radius, 0),
				position * 100 - Vec2d(radius, 0) + Vec2d(0, radius),
				position * 100 + Vec2d(radius, radius)
			);
		}

	private:

	};
};
