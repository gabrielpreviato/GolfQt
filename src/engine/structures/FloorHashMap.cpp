#include "FloorHashMap.hpp"

#include <ranges>

FloorHashMap::FloorHashMap(int x_size, int y_size, int cell_size)
    : SpatialHashMap(x_size, y_size, cell_size)
{
    floor_map = std::vector<std::vector<std::vector<GolfFloor>>>(n_rows, std::vector<std::vector<GolfFloor>>(n_cols));
}

int FloorHashMap::add_structure(const GolfFloor& floor) {
    auto rect = floor.m_path.boundingRect();
    double min_x, min_y, max_x, max_y;
    rect.getCoords(&min_x, &min_y, &max_x, &max_y);

    unsigned int n_mappings = 0;
    for (auto i = coord_to_cell(min_y); i <= coord_to_cell(max_y, true); i++) {
        for (auto j = coord_to_cell(min_x); j <= coord_to_cell(max_x, true); j++) {
            floor_map[i][j].push_back(floor);
            n_mappings++;
        }
    }

    return n_mappings;
}

const GolfFloor& FloorHashMap::get_floor(const QVector2D& position) const {
    int i = coord_to_cell(position.y());
    int j = coord_to_cell(position.x());

    GolfFloor* last_floor = nullptr;
    for (auto& floor : floor_map[i][j] | std::views::reverse) {
        if (floor.m_path.contains(QPointF(position.x(), position.y()))) {
            return floor;
        }
    }

    return DefaultObjects::DefaultFloor;
}

