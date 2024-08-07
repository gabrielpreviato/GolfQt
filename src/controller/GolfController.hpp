#pragma once

#include <QObject>
#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPoint>

class GolfController : public QObject
{
    Q_OBJECT
public:
    GolfController();
    ~GolfController();

    bool eventFilter(QObject* obj, QEvent* event) override;

signals:
    void controller_c_key_press();
    void controller_c_key_release();

    void controller_w_key_press();
    void controller_s_key_press();
    void controller_a_key_press();
    void controller_d_key_press();
    void controller_w_key_release();
    void controller_s_key_release();
    void controller_a_key_release();
    void controller_d_key_release();
    
    void controller_left_mouse_press(QPoint pos);
    void controller_left_mouse_release(QPoint pos);
    void controller_mouse_move(QPoint pos);

private:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
};
