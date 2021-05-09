#include "game.h"
#include "button.h"
#include <QMouseEvent>
#include <QtDebug>


Game::Game(double _sizeRatio, QWidget* parent)
    : QGraphicsView(parent)
    , sizeRatio {_sizeRatio}
    , data {}
{
    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1200*sizeRatio, 800*sizeRatio);
    setBackgroundBrush(QBrush(QImage(":/img/resources/backGround.png").scaled(1200*sizeRatio, 800*sizeRatio)));

    // set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1200*sizeRatio,800*sizeRatio);
    setScene(scene);

    // making ready option menu
    optionMenu = new Option(sizeRatio);
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
    border->setScale(sizeRatio);
    border->setPos(424*sizeRatio,290*sizeRatio);
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


void Game::startAndNext()
{
    optionMenu->setUp();
    Button* begin {new Button(QString("begin"), optionMenu)};
    begin->setScale(sizeRatio);
    connect(begin, &Button::clicked,
            this, &Game::startGame);
    begin->setPos(354*sizeRatio, 610*sizeRatio);
    scene->clear();
    scene->addItem(optionMenu);
}

void Game::startGame()
{
    data = optionMenu->getData();
    for (auto i : data)
        qDebug() << i;
    qDebug() << "next";
}
