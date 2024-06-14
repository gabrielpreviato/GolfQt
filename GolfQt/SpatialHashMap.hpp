#pragma once
#include <vector>
#include <array>
#include <tuple>
#include <algorithm>
#include <cmath>
#include "Structure.hpp"
#include "Physics.hpp"

class SpatialHashMap {
private:
	int x_size, y_size;
	int cell_size;

	int n_rows, n_cols;
	std::vector<std::vector<std::vector<Physics::Structure*>>> map;

public:
	SpatialHashMap(int x_size, int y_size, int cell_size);
	int coord_to_cell(double coord, bool is_max=false);
	std::tuple<double, double, double, double> structure_bbox(Physics::Structure& structure);
	int add_structure(Physics::Structure& structure);

	std::vector<Physics::Structure*> broad_collision(Physics::Structure& object);
	std::vector<Physics::Structure*> broad_collision(Physics::Object& object);
};
