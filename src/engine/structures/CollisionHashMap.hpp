#pragma once

#include "SpatialHashMap.hpp"

#include <QRectF>

#include "Physics.hpp"

class CollisionHashMap : public SpatialHashMap {
public:
    CollisionHashMap(int x_size, int y_size, int cell_size);
    CollisionHashMap() = default;

    int add_structure(const QRectF& structure);
	const std::vector<QRectF*> broad_collision(const QRectF& object) const;
	const std::vector<QRectF*> broad_collision(const Physics::Object& object) const;        

private:
    std::vector<std::vector<std::vector<QRectF>>> collision_map;
};
