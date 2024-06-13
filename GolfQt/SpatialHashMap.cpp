#include "SpatialHashMap.hpp"
#include <unordered_set>
#include <qDebug>

SpatialHashMap::SpatialHashMap(unsigned int x_size, unsigned int y_size, unsigned int cell_size)
: x_size(x_size), y_size(y_size), cell_size(cell_size) {
    n_cols = (x_size + cell_size - 1) / cell_size;
    n_rows = (y_size + cell_size - 1) / cell_size;

    for (auto i = 0; i < n_rows; i++) {
        auto map_row = std::vector<std::vector<Physics::Structure*>>(n_cols);
        map.push_back(map_row);
    }
}

int SpatialHashMap::coord_to_cell(double coord, bool is_max) {
    double mod = std::fmod(coord, cell_size);
    unsigned int cell = coord / cell_size;

    if (!is_max && mod <= 0.2*cell_size && cell > 0) {
        return cell - 1;
    }
    else if (is_max && mod >= 0.8 * cell_size && cell < n_cols) {
        return cell + 1;
    }
    else {
        return cell;
    }
}

std::tuple<double, double, double, double> SpatialHashMap::structure_bbox(Physics::Structure& structure) {
    double min_x = std::min({ structure.v1.x, structure.v2.x , structure.v3.x, structure.v4.x });
    double min_y = std::min({ structure.v1.y, structure.v2.y , structure.v3.y, structure.v4.y });
    double max_x = std::max({ structure.v1.x, structure.v2.x , structure.v3.x, structure.v4.x });
    double max_y = std::max({ structure.v1.y, structure.v2.y , structure.v3.y, structure.v4.y });

    return { min_x, min_y, max_x, max_y };
}

int SpatialHashMap::add_structure(Physics::Structure& structure) {
    auto [min_x, min_y, max_x, max_y] = structure_bbox(structure);

    unsigned int n_mappings = 0;
    for (auto i = coord_to_cell(min_y); i < coord_to_cell(max_y, true); i++) {
        for (auto j = coord_to_cell(min_x); j < coord_to_cell(max_x, true); j++) {
            map[i][j].push_back(&structure);
            n_mappings++;
        }
    }

    return n_mappings;
}

std::vector<Physics::Structure*> SpatialHashMap::broad_collision(Physics::Structure& object) {
    auto [min_x, min_y, max_x, max_y] = structure_bbox(object);

    qDebug() << min_x << "; " << min_y << "; " << max_x << "; " << max_y;

    auto possible_obj_collision = std::unordered_set<Physics::Structure*>{};
    for (auto i = coord_to_cell(min_y); i <= coord_to_cell(max_y, true); i++) {
        for (auto j = coord_to_cell(min_x); j <= coord_to_cell(max_x, true); j++) {
            possible_obj_collision.insert(map[i][j].begin(), map[i][j].end());
        }
    }

    return std::vector<Physics::Structure*>(possible_obj_collision.begin(), possible_obj_collision.end());
}

std::vector<Physics::Structure*> SpatialHashMap::broad_collision(Physics::Object& object) {
    Physics::Structure ball_structure = object.bounding_box();

    return broad_collision(ball_structure);
}