#pragma once
#include "Vec2.hpp"

template <class T> class Line2 {
public:
	Vec2<T> p1, p2;

	Line2(Vec2<T> p1, Vec2<T> p2) : p1(p1), p2(p2) {}
    Line2() : p1(Vec2<T>()), p2(Vec2<T>()) {}

	Vec2<T> normal() {
		// (-dy, dx)
		return Vec2<T>(-p2.y + p1.y, p2.x - p1.x).unit();
	}
};

using Line2d = Line2<double>;
