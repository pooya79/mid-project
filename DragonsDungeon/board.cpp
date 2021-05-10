#include "board.h"
#include "maze.h"
#include <iostream>
#include <QtDebug>

Board::Board(std::array<int, 5> _data, double _sizeRatio, QGraphicsItem *parent)
    : QGraphicsRectItem(parent)
    , sizeRatio {_sizeRatio}
    , data {_data}
{
    setUp();
}

void Board::setUp()
{
    // draw maze
    if (data[0] > data[1])
    {
        blockSize = sizeRatio*800/(data[0]+2);
    }
    else
    {
        blockSize = sizeRatio*800/(data[1]+2);
    }
    int x = 400*sizeRatio - (data[1]+2)*blockSize/2;
    int y = 400*sizeRatio - (data[0]+2)*blockSize/2;
    Maze maze {(size_t)data[0], (size_t)data[1]};
    mazeData = maze.solve((size_t)data[2]);
    drawMaze(blockSize, x, y);

    // draw character
    charPos = new QPair<int,int>(1,0);
    character = new Character(data[3], blockSize, mazeData, charPos, this);
    character->setPos(x+blockSize*0,y+blockSize*1);
    connect(character, &Character::win,
            [this]{emit win(); character->clearFocus();});
    // make character focusable
    character->setFlag(QGraphicsItem::ItemIsFocusable);
    character->setFocus();
}

void Board::solve()
{
    character->clearFocus();
    character->dead();
    QPixmap solvePave;
    if (data[4] == 1)
    {
        solvePave.load(":/blocks/resources/firepave.png");
    }
    else if (data[4] == 2)
    {
        solvePave.load(":/blocks/resources/icepave.png");
    }
    else if (data[4] == 3)
    {
        solvePave.load(":/blocks/resources/goldpave.png");
    }
    else if (data[4] == 4)
    {
        solvePave.load(":/blocks/resources/stormpave.png");
    }
    for (size_t i{}, n{mazeData.size()}; i<n; i++)
    {
        for (size_t j{}, m{mazeData[i].size()}; j<m; j++)
        {
            if (mazeData[i][j] == 1 || mazeData[i][j] == 5)
                mazeBlocks[i][j]->setPixmap(solvePave.scaled(blockSize,blockSize));
        }
    }
}

void Board::drawMaze(int blockSize, int x, int y)
{
    QPixmap pave {":blocks/resources/pave.png"};
    QPixmap wall {":blocks/resources/wall.png"};
    QPixmap solidWall {":blocks/resources/solidwall.png"};
    QPixmap entrance {":blocks/resources/entrance.png"};
    for (size_t i{}, n{mazeData.size()}; i<n ;i++)
    {
        mazeBlocks.resize(n);
        for (size_t j{}, m{mazeData[i].size()}; j<m; j++)
        {
            QGraphicsPixmapItem* block = new QGraphicsPixmapItem(this);
            int blockId = mazeData[i][j];
            if (blockId == 2 || blockId == 1 || blockId == 5)
            {
                block->setPixmap(pave.scaled(blockSize,blockSize));
            }
            else if (blockId == 3 || blockId == 0)
            {
                block->setPixmap(wall.scaled(blockSize,blockSize));
            }
            else if (blockId == 4)
            {
                block->setPixmap(solidWall.scaled(blockSize,blockSize));
            }
            else if (blockId == 6)
            {
                block->setPixmap(entrance.scaled(blockSize,blockSize));
                goalPos.first = i;
                goalPos.second = j;
            }
            block->setPos(x+blockSize*j,y+blockSize*i);
            mazeBlocks[i].push_back(block);
        }
    }
}

