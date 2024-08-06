#pragma once
#include <tuple>

#include <QRectF>
#include "GolfStructure.hpp"

class SpatialHashMap {
public:
	SpatialHashMap(int x_size, int y_size, int cell_size);
    SpatialHashMap() = default;

	int coord_to_cell(double coord, bool is_max=false) const;
	std::tuple<double, double, double, double> structure_bbox(GolfStructure& structure);
	
    int add_structure(GolfStructure& structure);

protected:
	int x_size, y_size;
	int cell_size;

	int n_rows, n_cols;
};
