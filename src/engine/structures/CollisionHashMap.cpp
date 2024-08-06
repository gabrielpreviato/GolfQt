#include "CollisionHashMap.hpp"
#include "GolfStructure.hpp"

#include <unordered_set>

CollisionHashMap::CollisionHashMap(int x_size, int y_size, int cell_size) : SpatialHashMap(x_size, y_size, cell_size) {
    collision_map = std::vector<std::vector<std::vector<const GolfStructure*>>>(n_rows, std::vector<std::vector<const GolfStructure*>>(n_cols));
}

int CollisionHashMap::add_structure(const GolfStructure& structure) {
    double min_x, min_y, max_x, max_y;
    structure.bounding_box().getCoords(&min_x, &min_y, &max_x, &max_y);

    unsigned int n_mappings = 0;
    for (auto i = coord_to_cell(min_y); i <= coord_to_cell(max_y, true); i++) {
        for (auto j = coord_to_cell(min_x); j <= coord_to_cell(max_x, true); j++) {
            collision_map[i][j].push_back(&structure);
            n_mappings++;
        }
    }

    return n_mappings;
}

const std::vector<const GolfStructure*> CollisionHashMap::broad_collision(const QRectF& object) const {
    double min_x, min_y, max_x, max_y;
    object.getCoords(&min_x, &min_y, &max_x, &max_y);

    auto possible_obj_collision = std::unordered_set<const GolfStructure*>{};
    for (auto i = coord_to_cell(min_y); i <= coord_to_cell(max_y, true); i++) {
        for (auto j = coord_to_cell(min_x); j <= coord_to_cell(max_x, true); j++) {
            possible_obj_collision.insert(collision_map[i][j].begin(), collision_map[i][j].end());
        }
    }

    return std::vector<const GolfStructure*>(possible_obj_collision.begin(), possible_obj_collision.end());
}

const std::vector<const GolfStructure*> CollisionHashMap::broad_collision(const Physics::Object& object) const {
    QRectF ball_structure = object.bounding_box();

    return broad_collision(ball_structure);
}

