#include "GolfQt.hpp"

GolfQt::GolfQt(std::vector<Physics::Structure> walls, QWidget *parent)
    : QMainWindow(parent), m_gameView(new GolfView(walls, this))
{
    ui.setupUi(this);
    this->setCentralWidget(m_gameView);

    //QCursor c = QCursor(Qt::CrossCursor);
    //setCursor(c);
}

GolfQt::~GolfQt() {
    delete m_gameView;
}
