#include "GolfQt.hpp"

GolfQt::GolfQt(const GolfMap& map, QWidget *parent)
    : QMainWindow(parent), m_gameView(GolfView(map, this)), m_player(GolfPlayer())
{
    ui.setupUi(this);
    this->setCentralWidget(&m_gameView);

    connect(&m_gameView, &GolfView::clicked_impulse, &m_player, &GolfPlayer::player_impulse);
}

GolfQt::~GolfQt() 
{}
