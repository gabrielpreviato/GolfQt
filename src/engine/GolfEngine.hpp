#pragma once
#include <QDebug>
#include <QObject>
#include <QTimer>
#include <QPoint>
#include <QVector2D>

#include "GolfBall.hpp"
#include "GolfMap.hpp"
#include "Physics.hpp"

#include "FloorHashMap.hpp"
#include "CollisionHashMap.hpp"

class GolfEngine : public QObject {
	Q_OBJECT
public:
	GolfEngine();
	~GolfEngine();
    
    void load_map(const GolfMap& map);

public slots:
	void run_tick();
	void run();
	void player_impulse(QPointF impulse);
	void stop();

signals:
	void objects(std::vector<GolfBall>);
    void is_moving(bool);
	void walls(std::vector<GolfWall>);
	void finished();

private:
	std::vector<GolfBall> m_balls;
	CollisionHashMap m_hash;
    FloorHashMap m_floor_hash;
    GolfMap m_map;
	
    QTimer m_engine_timer;

    double get_floor_friction(const QVector2D& position) const;
};

