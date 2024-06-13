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
	unsigned int x_size, y_size;
	unsigned int cell_size;

	unsigned int n_rows, n_cols;
	std::vector<std::vector<std::vector<Physics::Structure*>>> map;

public:
	SpatialHashMap(unsigned int x_size, unsigned int y_size, unsigned int cell_size);
	int coord_to_cell(double coord, bool is_max=false);
	std::tuple<double, double, double, double> structure_bbox(Physics::Structure& structure);
	int add_structure(Physics::Structure& structure);

	std::vector<Physics::Structure*> broad_collision(Physics::Structure& object);
	std::vector<Physics::Structure*> broad_collision(Physics::Object& object);
};
