#pragma once

#include <QMainWindow>
#include "ui_GolfQt.h"

#include "GolfView.hpp"
#include "GolfPlayer.hpp"
#include <QMouseEvent>

class GolfQt : public QMainWindow
{
    Q_OBJECT

public:
    GolfQt(const GolfMap& map, QWidget *parent = nullptr);
    ~GolfQt();

    GolfView* m_gameView = nullptr;
    GolfPlayer m_player;

private:
    Ui::GolfQtClass ui;

signals:
    void start_engine();
};
