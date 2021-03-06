#include "dragon.h"

Dragon::Dragon(int _id, double _sizeRatio, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
    , id {_id}
    , sizeRatio {_sizeRatio}
{
    fireSound = new QMediaPlayer();
    if (id == 1)
    {
        setPixmap(QPixmap(":/dragons/resources/firesleep.png").scaled(400*sizeRatio,400*sizeRatio));
        fireSound->setMedia(QUrl("qrc:/sound/resources/firegoldsound.wav"));
    }
    else if (id == 2)
    {
        setPixmap(QPixmap(":/dragons/resources/icesleep.png").scaled(400*sizeRatio, 400*sizeRatio));
        fireSound->setMedia(QUrl("qrc:/sound/resources/icesound.wav"));
    }
    else if (id == 3)
    {
        setPixmap(QPixmap(":/dragons/resources/goldsleep.png").scaled(400*sizeRatio, 400*sizeRatio));
        fireSound->setMedia(QUrl("qrc:/sound/resources/firegoldsound.wav"));
    }
    else if (id == 4)
    {
        setPixmap(QPixmap(":/dragons/resources/stormsleep.png").scaled(400*sizeRatio, 400*sizeRatio));
        fireSound->setMedia(QUrl("qrc:/sound/resources/stormsound.wav"));
    }
}

Dragon::~Dragon()
{
    delete fireSound;
}

void Dragon::fireDragon()
{
    fireSound->play();
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
