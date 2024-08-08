#pragma once

#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QObject>
#include <QPoint>

class GolfMouse : public QObject
{
    Q_OBJECT
public:
    GolfMouse(QObject *parent = nullptr);
    ~GolfMouse();

    bool eventFilter(QObject *obj, QEvent *event) override;

signals:
    void mouseLeftPress(QPoint pos);
    void mouseLeftRelease(QPoint pos);
    void mouseMove(QPoint pos);

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};
