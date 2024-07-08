#include "GolfQt.hpp"

GolfQt::GolfQt(const GolfMap& map, QWidget *parent)
    : QMainWindow(parent), m_gameView(new GolfView(map, this)), m_player(GolfPlayer())
{
    ui.setupUi(this);
    this->setCentralWidget(m_gameView);

    connect(m_gameView, &GolfView::clicked_impulse, &m_player, &GolfPlayer::player_impulse);
    //QCursor c = QCursor(Qt::CrossCursor);
    //setCursor(c);
}

GolfQt::~GolfQt() {
    delete m_gameView;
}
