#include "game.h"


Game::Game(double _sizeRatio, QWidget* parent)
    : QGraphicsView(parent)
    , sizeRatio {_sizeRatio}
    , data {}
    , board {nullptr}
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

    // initialize background music
    playList = new QMediaPlaylist();
    playList->addMedia(QUrl("qrc:/sound/resources/sleepsound.wav"));
    playList->setPlaybackMode(QMediaPlaylist::Loop);
    music = new QMediaPlayer();
    music->setPlaylist(playList);

    // victory sound
    victorySound = new QMediaPlayer();
    victorySound->setMedia(QUrl("qrc:/sound/resources/victorysound.wav"));
}

Game::~Game()
{
    delete scene;
    delete music;
    delete playList;
    delete victorySound;
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
    // when going from game menu to option menu
    if (board)
        board->characterStop();
    victorySound->stop();
    music->stop();

    // draw option menu
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
    music->play();

    // draw board
    board = new Board(data, sizeRatio);
    connect(board, &Board::win,
            this, &Game::win);
    scene->addItem(board);

    // side menu
    QGraphicsPixmapItem* sideBorder = new QGraphicsPixmapItem(QPixmap(":/img/resources/borders2.png").scaled(393, 500));
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
    characterGoButton = new Button("charactergo", sideBorder);
    characterGoButton->setPos(51,281);
    connect(characterGoButton, &Button::clicked,
            this, &Game::characterGo);
    proxySpeedSlider = new QGraphicsProxyWidget(sideBorder);
    QSlider* speedSlider = new QSlider(Qt::Horizontal);
    speedSlider->setMaximum(100);
    speedSlider->setMinimum(1);
    speedSlider->setGeometry(0, 0, 245, 40);
    connect(speedSlider, &QSlider::sliderMoved,
            this, &Game::changeSpeed);
    speedSlider->setStyleSheet(QString("* { background-image : url(:/option/resources/slideBar.png);}"
                                   "*::groove:horizontal { image : url(:/option/resources/rowLine.png);}"
                                   "*::handle:hrizontal { image : url(:/option/resources/handle.png);}"));
    proxySpeedSlider->setWidget(speedSlider);
    proxySpeedSlider->setPos(68, 304);
    proxySpeedSlider->setVisible(false);
    scene->addItem(sideBorder);

    // draw dragon
    dragon = new Dragon(data[4], sizeRatio);
    dragon->setPos(800*sizeRatio, 450*sizeRatio);
    scene->addItem(dragon);

    // make new option menu ready to start
    optionMenu = new Option(sizeRatio);
}

void Game::win()
{
    board->characterStop();
    music->stop();
    victorySound->play();
    QGraphicsPixmapItem* victory = new QGraphicsPixmapItem(QPixmap(":/img/resources/victory.png"));
    victory->setScale(sizeRatio);
    victory->setPos(891*sizeRatio, 377*sizeRatio);
    scene->addItem(victory);
}

void Game::awakeDragon()
{
    board->characterStop();
    music->stop();
    dragon->fireDragon();
    board->solve();
    QGraphicsPixmapItem* defeat = new QGraphicsPixmapItem(QPixmap(":/img/resources/defeat.png"));
    defeat->setScale(sizeRatio);
    defeat->setPos(891*sizeRatio, 377*sizeRatio);
    scene->addItem(defeat);
}

void Game::characterGo()
{
    characterGoButton->setVisible(false);
    proxySpeedSlider->setVisible(true);
    board->characterGo();
}

void Game::changeSpeed(int v)
{
    board->changeSpeed(v);
}

void Game::characterGoClicked()
{
    moveToThread(&thread);
    connect(&thread, SIGNAL(started()), this, SLOT(characterGo()));
    thread.start();
}
