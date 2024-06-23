#include "GolfQt.hpp"

GolfQt::GolfQt(const GolfMap& map, QWidget *parent)
    : QMainWindow(parent), m_gameView(new GolfView(map, this))
{
    ui.setupUi(this);
    this->setCentralWidget(m_gameView);

    //QCursor c = QCursor(Qt::CrossCursor);
    //setCursor(c);
}

GolfQt::~GolfQt() {
    delete m_gameView;
}
