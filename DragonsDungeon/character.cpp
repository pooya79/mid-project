#include "character.h"
#include <QKeyEvent>
#include <QTimer>
#include <QEventLoop>
#include <list>
#include <QDebug>

Character::Character(int _id, int _size, std::vector<std::vector<int>>& _mazeData, QPair<int, int> *_pos
                     , std::shared_ptr<Maze::Node> _root,std::shared_ptr<Maze::Node> _goal , QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
    , id {_id}
    , pos {_pos}
    , mazeData {_mazeData}
    , size {_size}
    , root {_root}
    , goal {_goal}
    , speed {1}
    , m {true}
{
    if (id==1)
    {
        setPixmap(QPixmap(":/characters/resources/dwarf.png").scaled(size,size));
    }
    else if (id==2)
    {
        setPixmap(QPixmap(":/characters/resources/highelf.png").scaled(size,size));
    }
    else if (id==3)
    {
        setPixmap(QPixmap(":/characters/resources/angel.png").scaled(size,size));
    }
    else if (id==4)
    {
        setPixmap(QPixmap(":/characters/resources/paladincentaur.png").scaled(size,size));
    }
}

Character::~Character()
{
    delete pos;
}

void Character::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up && mazeData[pos->first - 1][pos->second] != 3 && mazeData[pos->first - 1][pos->second] != 4)
    {
        pos->first--;
        setPos(x(), y()-size);
    }
    else if (event->key() == Qt::Key_Down && mazeData[pos->first + 1][pos->second] != 3 && mazeData[pos->first + 1][pos->second] != 4)
    {
        pos->first++;
        setPos(x(), y()+size);
    }
    else if (event->key() == Qt::Key_Right && mazeData[pos->first][pos->second + 1] != 3 && mazeData[pos->first][pos->second + 1] != 4)
    {
        pos->second++;
        setPos(x()+size, y());
        if (mazeData[pos->first][pos->second] == 6)
        {
            emit win();
        }
    }
    else if (event->key() == Qt::Key_Left && mazeData[pos->first][pos->second - 1] != 3 && mazeData[pos->first][pos->second - 1] != 4 && (pos->first != 1 || pos->second != 0))
    {
        pos->second--;
        setPos(x()-size, y());
    }

}

void Character::dead()
{
    setVisible(false);
    QGraphicsPixmapItem* deadBody = new QGraphicsPixmapItem(this->parentItem());
    deadBody->setPos(x(), y());
    if (id==1)
    {
        deadBody->setPixmap(QPixmap(":/characters/resources/deaddwarf.png").scaled(size,size));
    }
    else if (id==2 || id==3)
    {
        deadBody->setPixmap(QPixmap(":/characters/resources/deadelfangel.png").scaled(size,size));
    }
    else if (id==4)
    {
        deadBody->setPixmap(QPixmap(":/characters/resources/deadcentaur.png").scaled(size,size));
    }
}

void Character::characterGo(int moveAlg)
{
    if (!m)
        return;
    characterMove(root);
    if (moveAlg == 1)
    {
        DFSGo(root);
    }
    else if (moveAlg == 2)
    {
        BFSGo();
    }
    else if (moveAlg == 3)
    {
        DSGoWithBabyDragon();
    }
}

bool Character::DFSGo(std::shared_ptr<Maze::Node> n)
{
    if (!m)
        return true;
    bool isWinhere;
    if (n->getIsWin())
    {
        characterReachedGoal();
        return true;
    }
    else {
        for (const auto& child : n->neighbors)
        {
            characterMove(child);
            isWinhere = DFSGo(child);
            if (isWinhere)
                break;
        }
    }
    if (!isWinhere)
    {
        characterMove(n->parent);
        return false;
    }
    return true;
}

void Character::BFSGo()
{
    std::list<std::shared_ptr<Maze::Node>> tempQueue {root->neighbors};
    while (m)
    {
        std::list<std::shared_ptr<Maze::Node>> queue {std::move(tempQueue)};
        for (auto itr{queue.begin()}; itr!=queue.end(); itr++){
            characterMove((*itr));
            if ((*itr)->getIsWin())
            {
                characterReachedGoal();
                break;
            }
            merge(tempQueue, (*itr)->neighbors);
        }
    }
}

void Character::DSGoWithBabyDragon()
{
    babyDragon = new QGraphicsPixmapItem(QPixmap(":/dragons/resources/babydragon.png").scaled(size, size), parentItem());
    babyDragon->setPos(goal->pos.second*size, goal->pos.first*size);
    int turn {};
    std::shared_ptr<Maze::Node> intersectionNode;
    std::list<std::shared_ptr<Maze::Node>> tempQueue1 {root->neighbors};
    std::list<std::shared_ptr<Maze::Node>> tempQueue2 {goal->neighbors};
    while (m)
    {
        std::list<std::shared_ptr<Maze::Node>> queue1 {std::move(tempQueue1)};
        std::list<std::shared_ptr<Maze::Node>> queue2 {std::move(tempQueue2)};
        for (auto itr1{queue1.begin()}, itr2{queue2.begin()}; itr1!=queue1.end() || itr2!=queue2.end(); turn++){
            if (turn%2 && itr1!=queue1.end())
            {
                characterMove(*itr1);
                intersectionNode = checkFootSteps(*itr1);
                if (intersectionNode)
                {
                    babyDragon->setVisible(false);
                    followBabyFootSteps(intersectionNode);
                    return;
                }
                merge(tempQueue1, (*itr1)->neighbors);
                itr1++;
            }
            else if (!(turn%2) && itr2!=queue2.end())
            {
                babyDragonMove(*itr2);
                intersectionNode = checkFootSteps(*itr2);
                if (intersectionNode)
                {
                    intersectionNode->parent = *itr2;
                    babyDragon->setVisible(false);
                    followBabyFootSteps(intersectionNode);
                    return;
                }
                merge(tempQueue2, (*itr2)->neighbors);
                itr2++;
            }
        }
    }
}

void Character::characterMove(std::shared_ptr<Maze::Node> n)
{
    QEventLoop loop;
    QTimer::singleShot(2000/speed, &loop, SLOT(quit()) );
    loop.exec();
    if (!m)
        return;
    QGraphicsPixmapItem* footsteps = new QGraphicsPixmapItem(QPixmap(":/footsteps/resources/footsteps.png").scaled(size,size), parentItem());
    footsteps->setPos(x(), y());
    setPos(n->pos.second*size, n->pos.first*size);
    pos->first = n->pos.first;
    pos->second = n->pos.second;
}

void Character::characterReachedGoal()
{
    QEventLoop loop;
    QTimer::singleShot(2000/speed, &loop, SLOT(quit()) );
    loop.exec();
    QGraphicsPixmapItem* footsteps = new QGraphicsPixmapItem(QPixmap(":/footsteps/resources/footsteps.png").scaled(size,size), parentItem());
    footsteps->setPos(x(), y());
    pos->second++;
    setPos(x()+size, y());
    emit win();
}

void Character::babyDragonMove(std::shared_ptr<Maze::Node> n)
{
    QEventLoop loop;
    QTimer::singleShot(2000/speed, &loop, SLOT(quit()) );
    loop.exec();
    QGraphicsPixmapItem* footsteps = new QGraphicsPixmapItem(QPixmap(":/footsteps/resources/dragonfootsteps.png").scaled(size,size), parentItem());
    footsteps->setPos(babyDragon->x(), babyDragon->y());
    babyDragon->setPos(n->pos.second*size, n->pos.first*size);
}

void Character::characterStop()
{
    m = false;
}

void Character::changeSpeed(int v)
{
    speed = v;
}

std::shared_ptr<Maze::Node> Character::checkFootSteps(std::shared_ptr<Maze::Node> n)
{
    for (auto neighbor : n->neighbors)
    {
        if (neighbor->parent != n)
            return neighbor;
    }
    return nullptr;
}

void Character::followBabyFootSteps(std::shared_ptr<Maze::Node> n)
{
    characterMove(n);
    if (n == goal)
    {
        characterReachedGoal();
        return;
    }
    if (n->parent)
        followBabyFootSteps(n->parent);
}

void Character::merge(std::list<std::shared_ptr<Maze::Node> > &l1, std::list<std::shared_ptr<Maze::Node> > &l2)
{
    for (std::shared_ptr<Maze::Node>& neighbor : l2)
    {
        l1.push_back(neighbor);
    }
}
