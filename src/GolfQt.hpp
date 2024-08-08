#pragma once

#include <QMainWindow>

#include "GolfControls.hpp"
#include "GolfEngine.hpp"
#include "GolfGameView.hpp"
#include "GolfPlayer.hpp"
#include "assets_manager/AssetsManager.hpp"
#include <QMouseEvent>
#include <QThread>

class GolfQt : public QWidget
{
    Q_OBJECT

public:
    GolfQt(QWidget *parent = nullptr);
    ~GolfQt();

    void load_map(const GolfMap &map);

    GolfGameView m_gameView;
    GolfPlayer m_player;

    GolfControls m_controls;

    GolfEngine *m_engine = nullptr;
    QThread *m_engine_thread = nullptr;

signals:
    void start_engine();

private:
    AssetsManager m_assets_manager;
};
