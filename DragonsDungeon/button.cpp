#include "button.h"
#include <QBrush>


Button::Button(QString name, QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent)
    , c {false}
{
    // intitialize
    path = QString(":/buttons/resources/") + name + QString("button.png");
    hoverPath = QString(":/buttons/resources/") + name + QString("hoverbutton.png");
    clickedPath = QString(":/buttons/resources/") + name + QString("clickedbutton.png");

    // polices
    setAcceptHoverEvents(true);

    // set pixmap
    setPixmap(QPixmap(path));
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event);
    setPixmap(clickedPath);
    if (!c)
    {
        c = true;
        emit clicked();
    }
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    Q_UNUSED(event);
    setPixmap(hoverPath);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    Q_UNUSED(event);
    setPixmap(path);
}
