#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>


class RadioButton : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    RadioButton(int _id=-1, QGraphicsItem* parent=nullptr);

    // public methods (events)
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

    int getId() const;
    bool isChecked() const;
    void setId(int _id);
    void setChecked(bool _c);

signals:
    void pressed(int _id);

private:
    int id;
    bool checked;
};

#endif // RADIOBUTTON_H
