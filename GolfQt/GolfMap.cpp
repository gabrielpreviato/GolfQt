#include <fstream>
#include "GolfMap.hpp"
#include <qDebug>
#include <json.hpp>
using json = nlohmann::json;

GolfMap::GolfMap(std::vector<Physics::Structure> walls)
    : m_walls(walls)
{}

GolfMap::~GolfMap()
{
}

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

    return GolfMap{walls};
}
