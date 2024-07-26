#include "GolfQt.hpp"
#include <memory>
#include <qthread.h>

GolfQt::GolfQt(QWidget *parent)
    : m_gameView(GolfView(this)), m_player(GolfPlayer()),
    m_engine(new GolfEngine()), m_engine_thread(new QThread())
{
    // ui.setupUi(this);
    //this->setCentralWidget(&m_gameView);
    //setMaximumWidth(1366);
    //setMaximumHeight(768);
    //setMinimumWidth(1366);
    //setMinimumHeight(768);
    //resize(1366, 768);
    //setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    adjustSize();

    connect(&m_gameView, &GolfView::clicked_impulse, &m_player, &GolfPlayer::player_impulse);
    connect(&m_player, &GolfPlayer::strokes, &m_gameView, &GolfView::update_strokes);
    
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
