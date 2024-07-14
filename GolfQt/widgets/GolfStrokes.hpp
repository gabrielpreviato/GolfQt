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

    GolfStrokes(QWidget* parent = nullptr)
    : QWidget(parent), m_strokes(new QLabel(QString("0"))), m_layout(new QHBoxLayout(this))
    {
        m_strokes->setAlignment(Qt::AlignCenter);
        setMinimumSize(40, 30);

        m_layout->addWidget(m_strokes);
    }

    void set_stroke_count(const int count)
    {
        m_strokes->setText(QString::number(count));
        update();
    }

    void paintEvent(QPaintEvent* event) override
    {
        QWidget::paintEvent(event); // Call base class implementation first

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(QPen(Qt::blue, 5));  // Blue border, 5px width
        QRect borderRect = rect().adjusted(0, 0, -1, -1);
        painter.drawRect(borderRect);

        // Determine label position and size based on borderRect
        m_strokes->setGeometry(borderRect);
    }
};
