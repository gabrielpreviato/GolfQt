#include "GolfController.hpp"

GolfController::GolfController()
{}

GolfController::~GolfController()
{}

bool GolfController::eventFilter(QObject* obj, QEvent* event)
{
    bool handled = false;
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent* key_event = static_cast<QKeyEvent *>(event);
        keyPressEvent(key_event); 
        return true;
    } 
    else if (event->type() == QEvent::KeyRelease) 
    {
        QKeyEvent* key_event = static_cast<QKeyEvent *>(event);
        keyReleaseEvent(key_event);
        return true;
    }
    else if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* mouse_event = static_cast<QMouseEvent *>(event);
        mousePressEvent(mouse_event);
        return true;
    }
    else if (event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent* mouse_event = static_cast<QMouseEvent *>(event);
        mouseReleaseEvent(mouse_event);
        return true;
    }
    else if (event->type() == QEvent::MouseMove)
    {
        QMouseEvent* mouse_event = static_cast<QMouseEvent *>(event);
        mouseMoveEvent(mouse_event);
        return true;
    }
    
    return QObject::eventFilter(obj, event);
}   

void GolfController::keyPressEvent(QKeyEvent* event) {
    if (event->isAutoRepeat()) {
        event->ignore();
        return;
    }

    auto key = event->key();
    switch (key) {
    case Qt::Key_C:
        emit controller_c_key_press();
        break;
    case Qt::Key_W:
        emit controller_w_key_press();
        break;
    case Qt::Key_S:
        emit controller_s_key_press();
        break;
    case Qt::Key_A:
        emit controller_a_key_press();
        break;
    case Qt::Key_D:
        emit controller_d_key_press();
        break;
    default:
        break;
    }
}

void GolfController::keyReleaseEvent(QKeyEvent* event) {
    if (event->isAutoRepeat()) {
        event->ignore();
        return;
    }

    auto key = event->key();
    switch (key) {
    case Qt::Key_W:
        emit controller_w_key_release();
        break;
    case Qt::Key_S:
        emit controller_s_key_release();
        break;
    case Qt::Key_A:
        emit controller_a_key_release();
        break;
    case Qt::Key_D:
        emit controller_d_key_release();
        break;
    default:
        break;
    }
}

void GolfController::mousePressEvent(QMouseEvent* event) {
    auto button = event->button();
    switch (button) {
    case Qt::LeftButton:
        emit controller_left_mouse_press(event->pos());
        break;
    default:
        break;
    }
}

void GolfController::mouseReleaseEvent(QMouseEvent* event) {
    auto button = event->button();
    switch (button) {
    case Qt::LeftButton:
        emit controller_left_mouse_release(event->pos());
        break;
    default:
        break;
    }
}

void GolfController::mouseMoveEvent(QMouseEvent* event) {
    emit controller_mouse_move(event->pos());
}

