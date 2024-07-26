#include "GolfStrokes.hpp"

GolfStrokes::GolfStrokes(QWidget* parent)
: QWidget(parent), m_strokes(new QLabel(QString("0"))), m_layout(new QHBoxLayout(this))
{
    m_strokes->setAlignment(Qt::AlignCenter);
    setMinimumSize(40, 30);

    m_layout->addWidget(m_strokes);
}

void GolfStrokes::set_stroke_count(const int count)
{
    m_strokes->setText(QString::number(count));
    update();
}

void GolfStrokes::paintEvent(QPaintEvent* event)
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
