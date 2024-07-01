#pragma once
#include <QDebug>
#include <QObject>
#include <QTimer>
#include <QPoint>

#include "GolfMap.hpp"
#include "Physics.hpp"
#include "Structure.hpp"
#include "SpatialHashMap.hpp"

class QGolfEngine : public QObject {
	Q_OBJECT
public:
	QGolfEngine(int argc, char**argv, const GolfMap& map);
	~QGolfEngine();
	QTimer m_engine_timer;

private:
	std::vector<Physics::Object> m_objects;
	std::vector<GolfWall> m_walls;
	SpatialHashMap m_hash;
    SpatialHashMap m_floor_hash;
    GolfMap m_map;

    double get_floor_friction(const Vec2d& position);

signals:
	void objects(std::vector<Physics::Object>);
    void is_moving(bool);
	void walls(std::vector<Physics::Structure>);
	void finished();

public slots:
	void run_tick();
	void run();
	void player_impulse(QPointF cursor_pos);
	void stop();
};

