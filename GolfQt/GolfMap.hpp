#pragma once

#include <QObject>
#include "Structure.hpp"

class GolfMap : public QObject
{
    Q_OBJECT

public:
    GolfMap(std::vector<Physics::Structure> walls);
    ~GolfMap();
    
    static GolfMap load(std::string path);
private:
    std::vector<Physics::Structure> m_walls;

signals:
};
