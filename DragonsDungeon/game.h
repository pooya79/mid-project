#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    // constructors
    Game(QWidget* parent=nullptr);

    // destructors
    ~Game();

    // public methods
    void displayStartMenu();
    void displayOptionMenu();

    // public attributes
    QGraphicsScene* scene;

public slots:
    void startAndNext();
};

#endif // GAME_H
