#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "option.h"

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
    void displayOptionMenu();

    // public attributes
    QGraphicsScene* scene;

public slots:
    void startAndNext();
    void startGame();

private:
    double sizeRatio;
    Option* optionMenu;
    std::array<int,5> data;
};

#endif // GAME_H
