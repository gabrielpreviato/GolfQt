#include "GolfQt.hpp"

#include "GolfMap.hpp"

#include <QtWidgets/QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GolfMap map = GolfMap::load("assets/assets/map1.map");
    GolfQt w;

    w.load_map(map);
    w.show();
    return a.exec();
}
