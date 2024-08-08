#include "GolfQt.hpp"
#include <qthread.h>

GolfQt::GolfQt(QWidget *parent)
    : m_gameView(GolfGameView(this))
    , m_player(GolfPlayer())
    , m_engine(new GolfEngine())
    , m_engine_thread(new QThread())
    , m_controls(GolfControls(this))
    , QWidget(parent)
{
    adjustSize();

    connect(&m_gameView, &GolfGameView::clicked_impulse, &m_player, &GolfPlayer::player_impulse);
    connect(&m_player, &GolfPlayer::strokes, &m_gameView, &GolfGameView::update_strokes);

    m_engine->moveToThread(m_engine_thread);
    //    m_engine->m_engine_timer.moveToThread(m_engine_thread);

    connect(m_engine, &GolfEngine::objects, &m_gameView, &GolfGameView::receive_objects);
    connect(&m_gameView, &GolfGameView::clicked_impulse, m_engine, &GolfEngine::player_impulse);
    connect(m_engine, &GolfEngine::is_moving, &m_gameView, &GolfGameView::receive_is_moving);

    connect(m_engine_thread, &QThread::started, m_engine, &GolfEngine::run);
    //connect(this, &QWidget::destroyed, m_engine, &GolfEngine::stop);
    connect(this, &QWidget::destroyed, m_engine_thread, &QThread::quit);
    //connect(m_engine, &GolfEngine::finished, m_engine_thread, &QThread::deleteLater);
    connect(m_engine_thread, &QThread::finished, m_engine, &GolfEngine::deleteLater);
    connect(m_engine_thread, &QThread::finished, m_engine_thread, &QThread::deleteLater);

    m_engine_thread->start();
}

GolfQt::~GolfQt() {}

void GolfQt::load_map(const GolfMap &map)
{
    m_engine->load_map(map);
    m_gameView.load_map(map);
}
