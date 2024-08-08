#include "GolfMouse.hpp"
#include <qobject.h>

GolfMouse::GolfMouse(QObject *parent)
    : QObject(parent)
{}

GolfMouse::~GolfMouse() {}

bool GolfMouse::eventFilter(QObject *obj, QEvent *event)
{
    bool handled = false;
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouse_event = static_cast<QMouseEvent *>(event);
        mousePressEvent(mouse_event);
        return true;
    } else if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouse_event = static_cast<QMouseEvent *>(event);
        mouseReleaseEvent(mouse_event);
        return true;
    } else if (event->type() == QEvent::MouseMove) {
        QMouseEvent *mouse_event = static_cast<QMouseEvent *>(event);
        mouseMoveEvent(mouse_event);
        return true;
    }

    return QObject::eventFilter(obj, event);
}

void GolfMouse::mousePressEvent(QMouseEvent *event)
{
    auto button = event->button();
    switch (button) {
    case Qt::LeftButton:
        emit mouseLeftPress(event->pos());
        break;
    default:
        break;
    }
}

void GolfMouse::mouseReleaseEvent(QMouseEvent *event)
{
    auto button = event->button();
    switch (button) {
    case Qt::LeftButton:
        emit mouseLeftRelease(event->pos());
        break;
    default:
        break;
    }
}

void GolfMouse::mouseMoveEvent(QMouseEvent *event)
{
    emit mouseMove(event->pos());
}
