#include "GolfQt.hpp"

#include "QGolfEngine.hpp"
#include "GolfMap.hpp"

#include <QtWidgets/QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
    auto s = Physics::Structure({ 0, 300 }, { 200, 300 }, { 200, 350 }, { 0, 350 });

    auto wall1 = Physics::Structure({ 0, 0 }, { 400, 0 }, { 400, 10 }, { 0, 10 });
    auto wall2 = Physics::Structure({ 0, 0 }, { 10, 0 }, { 10, 400 }, { 0, 400 });
    auto wall3 = Physics::Structure({ 0, 390 }, { 400, 390 }, { 400, 400 }, { 0, 400 });
    auto wall4 = Physics::Structure({ 390, 0 }, { 400, 0 }, { 400, 400 }, { 390, 400 });
    auto walls = std::vector<Physics::Structure>{ s, wall1, wall2, wall3, wall4 };

    QApplication a(argc, argv);

    GolfMap map = GolfMap::load("C:/Users/gabri/GolfQt/GolfQt/maps/map1.map");
    GolfQt w{ map };

    QGolfEngine* engine = new QGolfEngine(argc, argv, map);
    QThread* engine_thread = new QThread();

    engine->moveToThread(engine_thread);
    // engine.m_engine_timer.moveToThread(engine_thread);

    w.connect(engine, &QGolfEngine::objects, w.m_gameView, &GolfView::receive_objects);
    w.connect(w.m_gameView, &GolfView::clicked_impulse, engine, &QGolfEngine::player_impulse);

    QObject::connect(engine_thread, &QThread::started, engine, &QGolfEngine::run);
    a.connect(&a, &QApplication::aboutToQuit, engine, &QGolfEngine::stop);
    a.connect(engine, &QGolfEngine::finished, engine, &QGolfEngine::deleteLater);
    a.connect(engine, &QGolfEngine::finished, engine_thread, &QThread::deleteLater);

    w.show();
    engine_thread->start();

    return a.exec();
}
