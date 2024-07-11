#include "GolfQt.hpp"
#include <memory>
#include <qthread.h>

GolfQt::GolfQt(QWidget *parent)
    : QMainWindow(parent), m_gameView(GolfView(this)), m_player(GolfPlayer()),
    m_engine(new GolfEngine()), m_engine_thread(new QThread())
{
    ui.setupUi(this);
    this->setCentralWidget(&m_gameView);

    connect(&m_gameView, &GolfView::clicked_impulse, &m_player, &GolfPlayer::player_impulse);
    
    m_engine->moveToThread(m_engine_thread);
//    m_engine->m_engine_timer.moveToThread(m_engine_thread);

    connect(m_engine, &GolfEngine::objects, &m_gameView, &GolfView::receive_objects);
    connect(&m_gameView, &GolfView::clicked_impulse, m_engine, &GolfEngine::player_impulse);
    connect(m_engine, &GolfEngine::is_moving, &m_gameView, &GolfView::receive_is_moving);

    connect(m_engine_thread, &QThread::started, m_engine, &GolfEngine::run);
    //connect(this, &QWidget::destroyed, m_engine, &GolfEngine::stop);
    connect(this, &QWidget::destroyed, m_engine_thread, &QThread::quit);
    //connect(m_engine, &GolfEngine::finished, m_engine_thread, &QThread::deleteLater);
    connect(m_engine_thread, &QThread::finished, m_engine, &GolfEngine::deleteLater);
    connect(m_engine_thread, &QThread::finished, m_engine_thread, &QThread::deleteLater);

    m_engine_thread->start();
}

GolfQt::~GolfQt() 
{}

void GolfQt::load_map(const GolfMap& map)
{
    m_engine->load_map(map); 
    m_gameView.load_map(map);
}
