#pragma once

#include <QMainWindow>
#include "ui_GolfQt.h"

#include "GolfView.hpp"
#include "GolfPlayer.hpp"
#include "GolfEngine.hpp"
#include <QMouseEvent>
#include <QThread>

class GolfQt : public QMainWindow
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

private:
    Ui::GolfQtClass ui;

signals:
    void start_engine();
};
