#include "character.h"
#include <QKeyEvent>


Character::Character(int _id, int _size, std::vector<std::vector<int>>& _mazeData, QPair<int, int> *_pos, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
    , id {_id}
    , pos {_pos}
    , mazeData {_mazeData}
    , size {_size}
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
    if (id==1)
    {
        setPixmap(QPixmap(":/characters/resources/deaddwarf.png").scaled(size,size));
    }
    else if (id==2 || id==3)
    {
        setPixmap(QPixmap(":/characters/resources/deadelfangel.png").scaled(size,size));
    }
    else if (id==4)
    {
        setPixmap(QPixmap(":/characters/resources/deadcentaur.png").scaled(size,size));
    }
}
