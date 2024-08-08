#pragma once

#include <QObject>

#include "GolfKeyboard.hpp"
#include "GolfMouse.hpp"

class GolfControls : public QObject {
    Q_OBJECT
public:
    GolfControls(QObject* parent = nullptr);
    ~GolfControls();

private:
    GolfKeyboard m_keyboard;
    GolfMouse m_mouse;
};
