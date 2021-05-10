#include "dragon.h"

Dragon::Dragon(int _id, double _sizeRatio, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
    , id {_id}
    , sizeRatio {_sizeRatio}
{
    if (id == 1)
    {
        setPixmap(QPixmap(":/dragons/resources/firesleep.png").scaled(400*sizeRatio,400*sizeRatio));
    }
    else if (id == 2)
    {
        setPixmap(QPixmap(":/dragons/resources/icesleep.png").scaled(400*sizeRatio, 400*sizeRatio));
    }
    else if (id == 3)
    {
        setPixmap(QPixmap(":/dragons/resources/goldsleep.png").scaled(400*sizeRatio, 400*sizeRatio));
    }
    else if (id == 4)
    {
        setPixmap(QPixmap(":/dragons/resources/stormsleep.png").scaled(400*sizeRatio, 400*sizeRatio));
    }
}

void Dragon::fireDragon()
{
    if (id == 1)
    {
        setPixmap(QPixmap(":/dragons/resources/firefire.png").scaled(400*sizeRatio,400*sizeRatio));
    }
    else if (id == 2)
    {
        setPixmap(QPixmap(":/dragons/resources/icefire.png").scaled(400*sizeRatio, 400*sizeRatio));
    }
    else if (id == 3)
    {
        setPixmap(QPixmap(":/dragons/resources/goldfire.png").scaled(400*sizeRatio, 400*sizeRatio));
    }
    else if (id == 4)
    {
        setPixmap(QPixmap(":/dragons/resources/stormfire.png").scaled(400*sizeRatio, 400*sizeRatio));
    }
}
