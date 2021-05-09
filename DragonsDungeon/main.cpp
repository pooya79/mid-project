#include <QApplication>
#include <QScreen>
#include "game.h"

Game* game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSize screenSize {a.screens()[0]->size()};
    double screenSizeRatio {1};
    if (screenSize.width() < 1200 || screenSize.height() < 800)
        screenSizeRatio = 0.75;
    game = new Game(screenSizeRatio);
    game->show();
    game->displayStartMenu();
    return a.exec();
}
