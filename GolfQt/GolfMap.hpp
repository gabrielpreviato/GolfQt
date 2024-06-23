#pragma once

#include <QObject>
#include "Structure.hpp"

class GolfMap : public QObject
{
    Q_OBJECT

public:
    std::vector<Physics::Structure> m_walls;
    int m_width, m_height;

    GolfMap(std::vector<Physics::Structure> walls, int width, int height);
    GolfMap(const GolfMap& other);
    ~GolfMap();
    
    static GolfMap load(std::string path);
signals:
};
