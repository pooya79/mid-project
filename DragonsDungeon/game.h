#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSlider>
#include <QGraphicsProxyWidget>
#include <QThread>
#include "option.h"
#include "button.h"
#include "board.h"
#include "dragon.h"

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    // constructors
    Game(double _sizeRatio=1, QWidget* parent=nullptr);

    // destructors
    ~Game();

    // public methods
    void displayStartMenu();

    // public attributes
    QGraphicsScene* scene;

public slots:
    void startAndNext();
    void startGame();
    void win();
    void awakeDragon();
    void characterGoClicked();
    void characterGo();
    void changeSpeed(int v);

private:
    double sizeRatio;
    Option* optionMenu;
    std::array<int,5> data;
    Board* board;
    Dragon* dragon;
    QMediaPlaylist* playList;
    QMediaPlayer* music;
    QMediaPlayer* victorySound;
    Button* characterGoButton;
    QGraphicsProxyWidget* proxySpeedSlider;
    QThread thread;
};

#endif // GAME_H
