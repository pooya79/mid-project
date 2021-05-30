#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsObject>
#include <QPair>
#include <memory>
#include "maze.h"

class Character : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Character(int _id, int _size,std::vector<std::vector<int>>& _mazeData,QPair<int,int>* _pos=nullptr
            ,std::shared_ptr<Maze::Node> root=nullptr,std::shared_ptr<Maze::Node> goal=nullptr ,QGraphicsItem* parent=nullptr);
    ~Character();
    void keyPressEvent(QKeyEvent* event);
    void dead();

    // auto solve
    void characterGo(int moveAlg);
    // Move Algs and their heleper functions
    bool DFSGo(std::shared_ptr<Maze::Node> n);
    void BFSGo();
    void DSGoWithBabyDragon();
    void characterMove(std::shared_ptr<Maze::Node> n);
    void characterReachedGoal();
    void babyDragonMove(std::shared_ptr<Maze::Node> n);
    void characterStop();
    void changeSpeed(int v);
    std::shared_ptr<Maze::Node> checkFootSteps(std::shared_ptr<Maze::Node> n);
    void followBabyFootSteps(std::shared_ptr<Maze::Node> n);
    void merge(std::list<std::shared_ptr<Maze::Node>>& l1, std::list<std::shared_ptr<Maze::Node>>& l2);

signals:
    void win();

private:
    int id;
    QPair<int,int>* pos;
    std::vector<std::vector<int>>& mazeData;
    int size;
    std::shared_ptr<Maze::Node> root;
    std::shared_ptr<Maze::Node> goal;
    QGraphicsPixmapItem* babyDragon;
    int speed;
    bool m;
};

#endif // CHARACTER_H
