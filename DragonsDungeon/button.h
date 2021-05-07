#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QSound>

class Button : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    // constructors
    Button(QString name, QGraphicsItem* parent=nullptr);

    // public methods (events)
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

signals:
    void clicked();

private:
    QString path, hoverPath, clickedPath;
};

#endif // BUTTON_H
