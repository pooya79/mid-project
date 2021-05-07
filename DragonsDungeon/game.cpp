#include "game.h"
#include "button.h"
#include <QMouseEvent>
#include <memory>
#include <QtDebug>

Game::Game(QWidget* parent)
    : QGraphicsView(parent)
{
    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1200, 800);
    setBackgroundBrush(QBrush(QImage(":/img/resources/backGround.png")));

    // set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1200,800);
    setScene(scene);
}

Game::~Game()
{
    delete scene;
}

void Game::displayStartMenu()
{
    // define border
    QGraphicsPixmapItem* border {new QGraphicsPixmapItem()};
    border->setPixmap(QPixmap(":/img/resources/borders.png").scaled(QSize(351,220)));
    border->setPos(424.5,290);
    scene->addItem(border);

    // place buttons in border
    Button* start {new Button(QString("start"), border)};
    start->setPos(28, 33);
    connect(start, &Button::clicked,
            this, &Game::startAndNext);

    Button* quit {new Button(QString("quit"), border)};
    quit->setPos(28, 122);
    connect(quit, &Button::clicked,
            this, &Game::close);
}

void Game::displayOptionMenu()
{
    qDebug() << "we are in option menu";
}

void Game::startAndNext()
{
    displayOptionMenu();
}
