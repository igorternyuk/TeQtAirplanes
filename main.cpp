#include <QApplication>
#include "game.hpp"
#include <memory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    std::unique_ptr<Game> upGame{std::make_unique<Game>()};
    upGame->run();
    return a.exec();
}
