#pragma once
#include <iostream>
#include <algorithm>
#include <cmath>
#include <utility>

#include <QColor>

#include "Physics-Constants.hpp"
#include "Vec2.hpp"
#include "Line2.hpp"
#include <qDebug>

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

		bool projections_overlap(const Structure& other) {
			auto min_x = std::min({ v1.x, v2.x, v3.x, v4.x });
			auto min_y = std::min({ v1.y, v2.y, v3.y, v4.y });
			auto max_x = std::max({ v1.x, v2.x, v3.x, v4.x });
			auto max_y = std::max({ v1.y, v2.y, v3.y, v4.y });

			auto other_min_x = std::min({ other.v1.x, other.v2.x, other.v3.x, other.v4.x });
			auto other_min_y = std::min({ other.v1.y, other.v2.y, other.v3.y, other.v4.y });
			auto other_max_x = std::max({ other.v1.x, other.v2.x, other.v3.x, other.v4.x });
			auto other_max_y = std::max({ other.v1.y, other.v2.y, other.v3.y, other.v4.y });

			bool x_overlap = (min_x <= other_max_x && max_x >= other_min_x);
			bool y_overlap = (min_y <= other_max_y && max_y >= other_min_y);

			qDebug() << "X overlap: " << x_overlap << "; Y overlap: " << y_overlap;

			return x_overlap && y_overlap;
		}
	};
}
