#include "SpatialHashMap.hpp"

#include <cmath>
#include <algorithm>

SpatialHashMap::SpatialHashMap(int x_size, int y_size, int cell_size)
: x_size(x_size), y_size(y_size), cell_size(cell_size) {
    n_cols = (x_size + cell_size - 1) / cell_size;
    n_rows = (y_size + cell_size - 1) / cell_size;
}

int SpatialHashMap::coord_to_cell(double coord, bool is_max) const {
    double mod = std::fmod(coord, cell_size);
    int cell = coord / cell_size;

    if (!is_max && mod <= 0.2*cell_size && cell > 0) {
        return std::max(cell - 1, 0);
    }
    else if (is_max && mod >= 0.8 * cell_size && cell < n_cols) {
        return std::min(cell + 1, n_rows-1);
    }
    else {
        return std::min(cell, n_rows - 1);
    }
}

