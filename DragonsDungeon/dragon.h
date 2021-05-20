#ifndef DRAGON_H
#define DRAGON_H

#include <QGraphicsPixmapItem>
#include <QMediaPlayer>

class Dragon : public QGraphicsPixmapItem
{
public:
    Dragon(int _id=1,double _sizeRatio=1 ,QGraphicsItem* parent=nullptr);
    ~Dragon();
    void fireDragon();

private:
    int id;
    double sizeRatio;
    QMediaPlayer* fireSound;
};

#endif // DRAGON_H
