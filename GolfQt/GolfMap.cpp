#include <fstream>
#include "GolfMap.hpp"
#include <qDebug>
#include <json.hpp>
#include <qlogging.h>
using json = nlohmann::json;

GolfMap::GolfMap(std::vector<Physics::Structure> walls, std::map<std::string, std::shared_ptr<QImage>> textures, int width, int height)
    : m_walls(walls), m_textures(textures), m_width(width), m_height(height)
{}

GolfMap::GolfMap(const GolfMap& other)
    : m_walls(other.m_walls), m_width(other.m_width), m_height(other.m_height), m_textures(other.m_textures)
{}

GolfMap::~GolfMap()
{}

GolfMap GolfMap::load(std::string path)
{
    std::vector<Physics::Structure> walls;
    std::ifstream file{path};
	if (!file.is_open()) {
		throw std::runtime_error("Could not open file");
	}

    json data = json::parse(file);

    qDebug() << data["walls"].size(); 
    for (auto& wall : data["walls"]) {
        std::vector<Vec2d> points;
        for (auto& point : wall["points"]) {
            qDebug() << point[0].get<double>() << "; " << point[1].get<double>();
            points.push_back(Vec2d{point[0], point[1]});
        }
        walls.push_back(Physics::Structure{
            points
        });
    }

    std::map<std::string, std::shared_ptr<QImage>> textures;
    for (auto& material : data["materials"]) {
        textures[std::string(material["name"])] = std::make_shared<QImage>(QString::fromStdString(std::string(material["image"])));
    }

    return GolfMap{walls, textures, data["width"], data["height"]};
}
