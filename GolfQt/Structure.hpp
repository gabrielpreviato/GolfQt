#pragma once
#include <iostream>
#include <cmath>
#include <utility>

#include <QColor>

#include "Physics-Constants.hpp"
#include "Vec2.hpp"
#include "Line2.hpp"

namespace Physics {

	class Structure {
	public:
		Vec2d v1, v2, v3, v4;
		Line2d e1, e2, e3, e4;
		QColor bg_color = QColor(0, 0, 0, 127);

		Structure(Vec2d v1, Vec2d v2, Vec2d v3, Vec2d v4);

		void set_color(QColor new_color) {
			bg_color = new_color;
		}
	};
}
