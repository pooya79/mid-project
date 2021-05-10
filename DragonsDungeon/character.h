#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsObject>
#include <QPair>

class Character : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Character(int _id,int _size,std::vector<std::vector<int>>& _mazeData,QPair<int,int>* _pos=nullptr, QGraphicsItem* parent=nullptr);
    ~Character();
    void keyPressEvent(QKeyEvent* event);
    void dead();

signals:
    void win();

private:
    int id;
    QPair<int,int>* pos;
    std::vector<std::vector<int>>& mazeData;
    int size;
};

#endif // CHARACTER_H
