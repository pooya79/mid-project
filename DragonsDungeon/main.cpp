#include <QApplication>
#include <QScreen>
#include <QIcon>
#include "game.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/img/resources/icon.jpg"));
    QSize screenSize {a.screens()[0]->size()};
    double screenSizeRatio {1};
    if (screenSize.width() < 1200 || screenSize.height() < 800)
        screenSizeRatio = 0.75;

    Game* game;
    game = new Game(screenSizeRatio);
    game->show();
    game->displayStartMenu();
    return a.exec();
}
