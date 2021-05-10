#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsRectItem>
#include <QHash>
#include <QString>
#include <QPair>
#include <array>
#include <vector>
#include "character.h"

class Board : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Board(std::array<int, 5> _data, double _sizeRatio, QGraphicsItem* parent=nullptr);
    void setUp();
    void solve();
    void drawMaze(int blockSize, int x, int y);

signals:
    void win();

private:
    double sizeRatio;
    int blockSize;
    std::array<int, 5> data;
    std::vector<std::vector<int>> mazeData;
    std::vector<std::vector<QGraphicsPixmapItem*>> mazeBlocks;
    Character* character;
    QPair<int,int>* charPos;
    QPair<int,int> goalPos;
    QHash<int,QString> dragonPave;
};

#endif // BOARD_H
