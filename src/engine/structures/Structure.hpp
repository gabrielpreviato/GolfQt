#pragma once
#include <algorithm>

#include <QColor>

#include <QList>
#include <QPolygonF>
#include <QPointF>
#include <QLineF>
#include <qDebug>

namespace Physics {

	class Structure {
	public:
        QPolygonF m_polygon;
        QList<QPointF> m_vertices;
        QList<QLineF> m_edges;
        double m_restitution = 0;

        Structure(QList<QPointF> points);
        Structure(QList<QPointF> points, double restitution);

		int detect_collision_edge(const QPointF& collidingPoint) const;
		QPointF get_normal(int edge) const;
	};
}
