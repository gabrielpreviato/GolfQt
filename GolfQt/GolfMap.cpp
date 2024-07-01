#include <fstream>
#include "GolfMap.hpp"
#include "GolfWall.hpp"
#include "Material.hpp"
#include <qDebug>
#include <json.hpp>
#include <qlogging.h>
using json = nlohmann::json;

GolfMap::GolfMap(std::vector<GolfWall> walls, std::vector<GolfFloor> floors, std::map<std::string, Material> materials, Vec2d start, int width, int height)
    : m_walls(walls), m_floors(floors), m_materials(materials), m_width(width), m_height(height), m_start(start)
{}

GolfMap::GolfMap(const GolfMap& other)
    : m_walls(other.m_walls), m_floors(other.m_floors), m_width(other.m_width), m_height(other.m_height), m_materials(other.m_materials), m_start(other.m_start)
{}

GolfMap::~GolfMap()
{}

GolfMap GolfMap::load(std::string path)
{
    std::ifstream file{path};
	if (!file.is_open()) {
		throw std::runtime_error("Could not open file");
	}

    json data = json::parse(file);

    std::map<std::string, Material> materials;
    for (auto& material : data["materials"]) {
        materials[std::string(material["name"])] = {std::string(material["name"]), material["friction"], material["restitution"], QImage{QString::fromStdString(std::string(material["image"]))}};
        qDebug() << "Loaded texture: " << std::string(material["image"]);
    }

    qDebug() << data["walls"].size(); 
    std::vector<GolfWall> walls;
    for (auto& wall : data["walls"]) {
        std::vector<Vec2d> points;
        for (auto& point : wall["points"]) {
            qDebug() << point[0].get<double>() << "; " << point[1].get<double>() << ";" << std::string(wall["material"]);
            points.push_back(Vec2d{point[0], point[1]});
        }
        walls.push_back(GolfWall{
            points, std::string(wall["material"])
        });
    }

    std::vector<GolfFloor> floors;
    for (auto& floor : data["floors"]) {
        std::vector<Vec2d> points;
        for (auto& point : floor["points"]) {
            qDebug() << point[0].get<double>() << "; " << point[1].get<double>() << ";" << std::string(floor["material"]);
            points.push_back(Vec2d{point[0], point[1]});
        }
        auto golf_floor = GolfFloor{materials[std::string(floor["material"])].m_friction, std::string(floor["material"])};
        golf_floor.add_floor(points);
        floors.push_back(golf_floor);
    }

    return GolfMap{walls, floors, materials, Vec2d{data["starting_position"][0], data["starting_position"][1]}, data["width"], data["height"]};
}
