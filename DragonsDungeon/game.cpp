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
    // taking data from option menu
    data = optionMenu->getData();

    // make scene ready
    scene->clear();
    setBackgroundBrush(QBrush(QImage(":/img/resources/startGame.png").scaled(1200*sizeRatio, 800*sizeRatio)));

    // draw board
    board = new Board(data, sizeRatio);
    connect(board, &Board::win,
            this, &Game::win);
    scene->addItem(board);

    // side menu
    QGraphicsPixmapItem* sideBorder = new QGraphicsPixmapItem(QPixmap(":/img/resources/borders2.png").scaled(393, 400));
    sideBorder->setScale(sizeRatio);
    sideBorder->setPos(807*sizeRatio, 0);
    Button* next = new Button("next", sideBorder);
    next->setPos(51, 42);
    connect(next, &Button::clicked,
            this, &Game::startAndNext);
    Button* awakeDragon = new Button("awake", sideBorder);
    awakeDragon->setPos(51,123);
    connect(awakeDragon, &Button::clicked,
            this, &Game::awakeDragon);
    Button* quit = new Button("quit", sideBorder);
    quit->setPos(51,200);
    connect(quit, &Button::clicked,
            this, &Game::close);
    scene->addItem(sideBorder);

    // draw dragon
    dragon = new Dragon(data[4], sizeRatio);
    dragon->setPos(800*sizeRatio, 400*sizeRatio);
    scene->addItem(dragon);

    // make new option menu ready to start
    optionMenu = new Option(sizeRatio);
}

void Game::win()
{
    QGraphicsPixmapItem* victory = new QGraphicsPixmapItem(QPixmap(":/img/resources/victory.png"));
    victory->setScale(sizeRatio);
    victory->setPos(891*sizeRatio, 277*sizeRatio);
    scene->addItem(victory);
}

void Game::awakeDragon()
{
    dragon->fireDragon();
    board->solve();
    QGraphicsPixmapItem* defeat = new QGraphicsPixmapItem(QPixmap(":/img/resources/defeat.png"));
    defeat->setScale(sizeRatio);
    defeat->setPos(891*sizeRatio, 277*sizeRatio);
    scene->addItem(defeat);
}
