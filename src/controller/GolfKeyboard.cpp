#include "GolfKeyboard.hpp"

GolfKeyboard::GolfKeyboard() {}

GolfKeyboard::~GolfKeyboard() {}

bool GolfKeyboard::eventFilter(QObject *obj, QEvent *event)
{
    bool handled = false;
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *key_event = static_cast<QKeyEvent *>(event);
        keyPressEvent(key_event);
        return true;
    } else if (event->type() == QEvent::KeyRelease) {
        QKeyEvent *key_event = static_cast<QKeyEvent *>(event);
        keyReleaseEvent(key_event);
        return true;
    }
    
    return QObject::eventFilter(obj, event);
}

void GolfKeyboard::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()) {
        event->ignore();
        return;
    }

    auto key = event->key();
    switch (key) {
    case Qt::Key_C:
        emit keyboard_C_KeyPress();
        break;
    case Qt::Key_W:
        emit keyboard_W_KeyPress();
        break;
    case Qt::Key_S:
        emit keyboard_S_KeyPress();
        break;
    case Qt::Key_A:
        emit keyboard_A_KeyPress();
        break;
    case Qt::Key_D:
        emit keyboard_D_KeyPress();
        break;
    default:
        break;
    }
}

void GolfKeyboard::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()) {
        event->ignore();
        return;
    }

    auto key = event->key();
    switch (key) {
    case Qt::Key_W:
        emit keyboard_W_KeyRelease();
        break;
    case Qt::Key_S:
        emit keyboard_S_KeyRelease();
        break;
    case Qt::Key_A:
        emit keyboard_A_KeyRelease();
        break;
    case Qt::Key_D:
        emit keyboard_D_KeyRelease();
        break;
    default:
        break;
    }
}

