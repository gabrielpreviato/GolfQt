#pragma once

#include <vector>

#include <QVector2D>

#include "SpatialHashMap.hpp"
#include "GolfFloor.hpp"

class FloorHashMap : public SpatialHashMap {
public:
    FloorHashMap(int x_size, int y_size, int cell_size);
    FloorHashMap() = default;

	int add_structure(const GolfFloor& floor);
    const GolfFloor& get_floor(const QVector2D& position) const;

private:
    std::vector<std::vector<std::vector<GolfFloor>>> floor_map;
};
