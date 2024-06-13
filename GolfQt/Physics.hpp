#pragma once
#include <iostream>
#include <cmath>
#include <utility>

#include "Physics-Constants.hpp"
#include "Vec2.hpp"

namespace Physics {

	class Object
	{
	public:
		const int radius = 3;
		double mass;
		Vec2d position;
		Vec2d speed;

		Object(double mass) : mass(mass) {};
		Object(double mass, const Vec2d& p, const Vec2d& s) : mass(mass), position(p), speed(s) {};
		Object(double mass, Vec2d&& p, Vec2d&& s) : mass(mass), position(std::move(p)), speed(std::move(s)) {};


		Object(const Object& o) : mass(o.mass), position(o.position), speed(o.speed) {};
		Object(Object&& o) noexcept : mass(o.mass), position(o.position), speed(o.speed) {};

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

	private:

	};
};