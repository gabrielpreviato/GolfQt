#pragma once

#include <QObject>
#include <QImage>
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
    int m_width, m_height;

    GolfMap(std::vector<GolfWall> walls, std::vector<GolfFloor> floors, std::map<std::string, Material> materials, int width, int height);
    GolfMap(const GolfMap& other);
    ~GolfMap();
    
    static GolfMap load(std::string path);
signals:
};
