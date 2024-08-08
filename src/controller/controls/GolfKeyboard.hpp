#pragma once

#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QObject>
#include <QPoint>

class GolfKeyboard : public QObject
{
    Q_OBJECT
public:
    GolfKeyboard(QObject *parent = nullptr);
    ~GolfKeyboard();

    bool eventFilter(QObject *obj, QEvent *event) override;

signals:
    void keyboard_C_KeyPress();
    void keyboard_C_KeyRelease();

    void keyboard_W_KeyPress();
    void keyboard_S_KeyPress();
    void keyboard_A_KeyPress();
    void keyboard_D_KeyPress();
    void keyboard_W_KeyRelease();
    void keyboard_S_KeyRelease();
    void keyboard_A_KeyRelease();
    void keyboard_D_KeyRelease();

private:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};
