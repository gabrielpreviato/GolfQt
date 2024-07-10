#include "GolfQt.hpp"

#include "QGolfEngine.hpp"
#include "GolfMap.hpp"

#include <QtWidgets/QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GolfMap map = GolfMap::load("C:/Users/prg7fe/tools/GolfQt/GolfQt/maps/map1.map");
    GolfQt w{ map };

    QGolfEngine* engine = new QGolfEngine(argc, argv, map);
    QThread* engine_thread = new QThread();

    engine->moveToThread(engine_thread);
    // engine.m_engine_timer.moveToThread(engine_thread);

    w.connect(engine, &QGolfEngine::objects, &w.m_gameView, &GolfView::receive_objects);
    w.connect(&w.m_gameView, &GolfView::clicked_impulse, engine, &QGolfEngine::player_impulse);
    w.connect(engine, &QGolfEngine::is_moving, &w.m_gameView, &GolfView::receive_is_moving);

    QObject::connect(engine_thread, &QThread::started, engine, &QGolfEngine::run);
    a.connect(&a, &QApplication::aboutToQuit, engine, &QGolfEngine::stop);
    a.connect(engine, &QGolfEngine::finished, engine, &QGolfEngine::deleteLater);
    a.connect(engine, &QGolfEngine::finished, engine_thread, &QThread::deleteLater);

    w.show();
    engine_thread->start();

    return a.exec();
}
