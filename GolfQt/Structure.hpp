#pragma once
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
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
        Structure(std::vector<Vec2d> points);

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

		int detect_collision_edge(const Vec2d& collidingPoint) {
			std::vector<Vec2d> vertices = { v1, v2, v3, v4 };
			std::vector<Line2d> edges = { e1, e2, e3, e4 };

			for (int i = 0; i < edges.size(); ++i) {
				Vec2d edgeVector = vertices[(i + 1) % vertices.size()] - vertices[i];
				Vec2d pointVector = collidingPoint - vertices[i];

				qDebug() << "pointVector" << pointVector.x << "," << pointVector.y;
				qDebug() << "pointVector" << pointVector.x << "," << pointVector.y;
				qDebug() << "pointVector" << pointVector.x << "," << pointVector.y;
				// Calculate the cross product
				double cross = edgeVector.x * pointVector.y - edgeVector.y * pointVector.x;
				qDebug() << "Edge" << i + 1 << " " << edgeVector.x << "," << edgeVector.y << "Cross Product:" << cross;

				// Assuming a clockwise definition of edges, a negative cross product
				// indicates the point is on the right (outside) of the edge for a convex shape.
				if (cross < 0) {
					return i + 1; // Return the edge index (1-based for consistency with your get_normal method)
				}
			}

			return -1; // Indicates no external collision detected
		}

		Vec2d get_normal(int edge) {
			switch (edge) {
			case 1:
				return e1.normal();
			case 2:
				return e2.normal();
			case 3:
				return e3.normal();
			case 4:
				return e4.normal();
			default:
				return Vec2d(0, 0);
			}
		}
	};
}
