#pragma once

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <qboxlayout.h>

class GolfStrokes : public QWidget {
    Q_OBJECT
public:
    QLabel* m_strokes;
    QHBoxLayout* m_layout;

    GolfStrokes(QWidget* parent = nullptr);

    void set_stroke_count(const int count);
    void paintEvent(QPaintEvent* event) override;
};
