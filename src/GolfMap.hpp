#pragma once

#include <QObject>
#include <QImage>
#include <QPointF>

#include <vector>
#include "GolfFloor.hpp"
#include "GolfWall.hpp"
#include "Material.hpp"

class GolfMap : public QObject
{
    Q_OBJECT

public:
    std::vector<GolfWall> m_walls;
    std::vector<GolfFloor> m_floors;
    std::map<std::string, Material> m_materials;
    QPointF m_start;
    QPointF m_end;
    int m_width, m_height;

    GolfMap() = default;
    GolfMap(std::vector<GolfWall> walls, std::vector<GolfFloor> floors, std::map<std::string, Material> materials, QPointF m_start, QPointF m_end, int width, int height);
    GolfMap(const GolfMap& other);
    ~GolfMap();
    
    GolfMap& operator=(const GolfMap& map);
    static GolfMap load(std::string path);
signals:
};
