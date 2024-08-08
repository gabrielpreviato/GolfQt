#include "GolfControls.hpp"

GolfControls::GolfControls(QObject *parent)
    : QObject(parent)
    , m_keyboard(GolfKeyboard(this))
    , m_mouse(GolfMouse(this))
{
    installEventFilter(&m_keyboard);
    installEventFilter(&m_mouse);
}

GolfControls::~GolfControls() {}

