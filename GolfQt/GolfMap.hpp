#pragma once

#include <QObject>
#include <QImage>
#include "Structure.hpp"

class GolfMap : public QObject
{
    Q_OBJECT

public:
    std::vector<Physics::Structure> m_walls;
    std::map<std::string, std::shared_ptr<QImage>> m_textures;
    int m_width, m_height;

    GolfMap(std::vector<Physics::Structure> walls, std::map<std::string, std::shared_ptr<QImage>> textures, int width, int height);
    GolfMap(const GolfMap& other);
    ~GolfMap();
    
    static GolfMap load(std::string path);
signals:
};
