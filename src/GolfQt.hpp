#pragma once

#include <QMainWindow>

#include "GolfView.hpp"
#include "GolfPlayer.hpp"
#include "GolfEngine.hpp"
#include <QMouseEvent>
#include <QThread>

class GolfQt : public QWidget
{
    Q_OBJECT

public:
    GolfQt(QWidget *parent = nullptr);
    ~GolfQt();

    void load_map(const GolfMap& map);

    GolfView m_gameView;
    GolfPlayer m_player;
    
    GolfEngine* m_engine = nullptr;
    QThread* m_engine_thread = nullptr;

signals:
    void start_engine();
};
