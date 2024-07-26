#pragma once

#include <QObject>
#include <QPointF>

class GolfPlayer : public QObject {
	Q_OBJECT
private:
    int m_strokes;

public:
    GolfPlayer();

public slots:
	void player_impulse(QPointF cursor_pos);

signals:
    void strokes(int stroke);
};
