#ifndef DRAGON_H
#define DRAGON_H

#include <QGraphicsPixmapItem>

class Dragon : public QGraphicsPixmapItem
{
public:
    Dragon(int _id=1,double _sizeRatio=1 ,QGraphicsItem* parent=nullptr);
    void fireDragon();

private:
    int id;
    double sizeRatio;
};

#endif // DRAGON_H
