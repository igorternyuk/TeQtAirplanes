#include <QApplication>
#include "game.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    Game game;
    game.run();
    return a.exec();
}
