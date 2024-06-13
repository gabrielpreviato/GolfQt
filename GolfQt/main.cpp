#include "GolfQt.hpp"

#include "QGolfEngine.hpp"

#include <QtWidgets/QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
    auto s = Physics::Structure({ 0, 300 }, { 200, 300 }, { 200, 350 }, { 0, 350 });
    auto walls = std::vector<Physics::Structure>{ s };

    QApplication a(argc, argv);
    GolfQt w{ walls };

    QGolfEngine* engine = new QGolfEngine(argc, argv, walls);
    QThread* engine_thread = new QThread();

    engine->moveToThread(engine_thread);
    // engine.m_engine_timer.moveToThread(engine_thread);

    w.connect(engine, &QGolfEngine::objects, w.m_gameView, &GolfView::receive_objects);
    w.connect(engine, &QGolfEngine::walls, w.m_gameView, &GolfView::receive_walls);
    w.connect(w.m_gameView, &GolfView::clicked_impulse, engine, &QGolfEngine::player_impulse);

    QObject::connect(engine_thread, &QThread::started, engine, &QGolfEngine::run);
    a.connect(&a, &QApplication::aboutToQuit, engine, &QGolfEngine::stop);
    a.connect(engine, &QGolfEngine::finished, engine, &QGolfEngine::deleteLater);
    a.connect(engine, &QGolfEngine::finished, engine_thread, &QThread::deleteLater);

    w.show();
    engine_thread->start();

    return a.exec();
}
