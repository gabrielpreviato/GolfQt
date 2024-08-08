#include "GolfMap.hpp"
#include "GolfWall.hpp"
#include <fstream>
#include <json.hpp>
#include <qDebug>
#include <qlogging.h>
#include "assets_manager/AssetsManager.hpp"
using json = nlohmann::json;

GolfMap::GolfMap(
    std::vector<GolfWall> walls,
    std::vector<GolfFloor> floors,
    QPointF start,
    QPointF end,
    int width,
    int height)
    : m_walls(walls)
    , m_floors(floors)
    , m_width(width)
    , m_height(height)
    , m_start(start)
    , m_end(end)
{}

GolfMap::GolfMap(const GolfMap &other)
    : m_walls(other.m_walls)
    , m_floors(other.m_floors)
    , m_width(other.m_width)
    , m_height(other.m_height)
    , m_start(other.m_start)
    , m_end(other.m_end)
{}

GolfMap::~GolfMap() {}

GolfMap &GolfMap::operator=(const GolfMap &map)
{
    m_walls = map.m_walls;
    m_floors = map.m_floors;
    m_width = map.m_width;
    m_height = map.m_height;
    m_start = map.m_start;
    m_end = map.m_end;

    //qDebug() << "Called assignment" ;

    return *this;
}

GolfMap GolfMap::load(std::string path)
{
    std::ifstream file{path};
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    json data = json::parse(file);

    qDebug() << data["walls"].size();
    std::vector<GolfWall> walls;
    for (auto &wall : data["walls"]) {
        QList<QPointF> points;
        for (auto &point : wall["points"]) {
            qDebug() << point[0].get<double>() << "; " << point[1].get<double>() << ";"
                     << std::string(wall["material"]);
            points.push_back(QPointF{point[0], point[1]});
        }

        auto material = G_ASSETS_MANAGER.getMaterial(std::string(wall["material"])).toStrongRef();
        walls.push_back(GolfWall{points, std::string(wall["material"]), material.data()->restitution()});
    }

    std::vector<GolfFloor> floors;
    for (auto &floor : data["floors"]) {
        std::vector<QPointF> points;
        auto material = G_ASSETS_MANAGER.getMaterial(std::string(floor["material"])).toStrongRef();
        auto golf_floor = GolfFloor{material.data()->friction(), std::string(floor["material"])};

        golf_floor.start_path({floor["points"][0]["begin"][0], floor["points"][0]["begin"][1]});
        for (auto &point : floor["points"]) {
            auto path_type = std::string(point["type"]);
            if (path_type == "line") {
                golf_floor.add_line(
                    {point["begin"][0], point["begin"][1]}, {point["end"][0], point["end"][1]});
            } else if (path_type == "quad") {
                golf_floor.add_quad(
                    {point["begin"][0], point["begin"][1]},
                    {point["end"][0], point["end"][1]},
                    {point["control"][0][0], point["control"][0][1]});
            } else if (path_type == "cubic") {
                golf_floor.add_cubic(
                    {point["begin"][0], point["begin"][1]},
                    {point["end"][0], point["end"][1]},
                    {point["control"][0][0], point["control"][0][1]},
                    {point["control"][0][0], point["control"][0][1]});
            }
            // qDebug() << point[0].get<double>() << "; " << point[1].get<double>() << ";" << std::string(floor["material"]);
        }
        golf_floor.close_path();

        floors.push_back(golf_floor);
    }
    qDebug() << floors.size();

    auto hole_floor = GolfFloor{14, "black"};
    hole_floor.add_floor(QPointF{data["finish_position"][0], data["finish_position"][1]}, 10);
    floors.push_back(hole_floor);

    return GolfMap{
        walls,
        floors,
        QPointF{data["starting_position"][0], data["starting_position"][1]},
        QPointF{data["finish_position"][0], data["finish_position"][1]},
        data["width"],
        data["height"]};
}
