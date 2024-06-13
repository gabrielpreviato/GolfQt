#pragma once

#include <QMainWindow>
#include "ui_GolfQt.h"

#include "Structure.hpp"

#include "GolfView.hpp"
#include <QMouseEvent>

class GolfQt : public QMainWindow
{
    Q_OBJECT

public:
    GolfQt(std::vector<Physics::Structure> walls, QWidget *parent = nullptr);
    ~GolfQt();

    GolfView* m_gameView = nullptr;

private:
    Ui::GolfQtClass ui;

signals:
    void start_engine();
};
