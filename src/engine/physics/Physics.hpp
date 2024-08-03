#pragma once
#include <utility>

#include <QRectF>
#include <QVector2D>

namespace Physics {
	class Object
	{
	public:
		Object(double mass) : mass(mass) {};
		Object(double mass, const QVector2D& p, const QVector2D& s) : mass(mass), position(p), speed(s) {};
		Object(double mass, QVector2D&& p, QVector2D&& s) : mass(mass), position(std::move(p)), speed(std::move(s)) {};

		Object(const Object& o) : mass(o.mass), position(o.position), speed(o.speed) {};
		Object(Object&& o) noexcept : mass(o.mass), position(o.position), speed(o.speed) {};

		double kinetic_energy();
		double gravitational_energy();
		double energy();
		QVector2D momemtum();
		void give_impulse(QVector2D&& impulse);
        void zero_normalize(const double sigma);
		void tick(const QVector2D& force);
		void reverse_tick(double rate);
		virtual const QRectF bounding_box() const;
        virtual bool detect_collision(const Object& other) const;
		
		double mass;
		QVector2D position;
		QVector2D speed;
	};
};
