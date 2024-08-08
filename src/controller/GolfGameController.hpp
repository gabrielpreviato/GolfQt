#pragma once

#include <QObject>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "GolfEngine.hpp"
#include "GolfGameView.hpp"
#include "GolfMap.hpp"

class GolfGameController : public QObject
{
    Q_OBJECT
public:
    GolfGameController(QWeakPointer<GolfEngine> engine, QObject *parent = nullptr);
    ~GolfGameController();

    void load_map(const GolfMapReference &map);

private:
    QWeakPointer<GolfEngine> m_engine;
    QSharedPointer<const GolfMap> m_current_map;
    QScopedPointer<GolfGameView> m_current_game_view;
};
