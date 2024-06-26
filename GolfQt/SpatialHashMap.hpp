#pragma once
#include <vector>
#include <array>
#include <tuple>
#include <QRectF>
#include <algorithm>
#include <cmath>
#include "GolfFloor.hpp"
#include "Structure.hpp"
#include "Physics.hpp"

class SpatialHashMap {
private:
	int x_size, y_size;
	int cell_size;

	int n_rows, n_cols;
	std::vector<std::vector<std::vector<Physics::Structure*>>> map;
    std::vector<std::vector<std::vector<GolfFloor>>> floor_map;

public:
	SpatialHashMap(int x_size, int y_size, int cell_size);
	int coord_to_cell(double coord, bool is_max=false);
	std::tuple<double, double, double, double> structure_bbox(Physics::Structure& structure);
	int add_structure(Physics::Structure& structure);
	int add_structure(const GolfFloor& floor);

	std::vector<Physics::Structure*> broad_collision(Physics::Structure& object);
	std::vector<Physics::Structure*> broad_collision(Physics::Object& object);
    GolfFloor& get_floor(const Vec2d& position);
        
};
