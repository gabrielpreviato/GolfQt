#pragma once
#include <tuple>

#include <QRectF>
#include "Structure.hpp"

class SpatialHashMap {
public:
	SpatialHashMap(int x_size, int y_size, int cell_size);
    SpatialHashMap() = default;

	int coord_to_cell(double coord, bool is_max=false) const;
	std::tuple<double, double, double, double> structure_bbox(Physics::Structure& structure);
	
    int add_structure(Physics::Structure& structure);

protected:
	int x_size, y_size;
	int cell_size;

	int n_rows, n_cols;
};
