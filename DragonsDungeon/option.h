#ifndef OPTION_H
#define OPTION_H

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QPair>
#include <QHash>
#include <array>
#include "radiobutton.h"

class Option : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Option(double _sizeRatio=1, QGraphicsItem* parent=nullptr);
    void setUp();
    void drawSliders();
    void drawSolveAlg();
    void drawCharacter();
    void drawDragon();
    std::array<int, 5> getData() const;

public slots:
    void rowChanged(int _n);
    void columnChanged(int _m);
    void algChanged(int _id);
    void characterChanged(int _id);
    void dragonChanged(int _id);

private:
    double sizeRatio;
    QGraphicsTextItem* nRows;
    QGraphicsTextItem* nColumns;
    QHash<int, RadioButton*> solveAlg;
    QHash<int, RadioButton*> character;
    QHash<int, RadioButton*> dragon;
    std::array<int,5> data;
};

#endif // OPTION_H
