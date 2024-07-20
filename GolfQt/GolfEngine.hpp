#pragma once
#include <QDebug>
#include <QObject>
#include <QTimer>
#include <QPoint>

#include "GolfMap.hpp"
#include "Physics.hpp"
#include "Structure.hpp"
#include "SpatialHashMap.hpp"

class GolfEngine : public QObject {
	Q_OBJECT
public:
	GolfEngine();
	~GolfEngine();
    
    void load_map(const GolfMap& map);

private:
	std::vector<Physics::Object> m_objects;
	SpatialHashMap m_hash;
    SpatialHashMap m_floor_hash;
    GolfMap m_map;
	
    QTimer m_engine_timer;

    double get_floor_friction(const Vec2d& position);

signals:
	void objects(std::vector<Physics::Object>);
    void is_moving(bool);
	void walls(std::vector<Physics::Structure>);
	void finished();

public slots:
	void run_tick();
	void run();
	void player_impulse(QPointF impulse);
	void stop();
};

