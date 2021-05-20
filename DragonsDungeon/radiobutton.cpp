#include "radiobutton.h"

RadioButton::RadioButton(int _id, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
    , id{_id}
{
    setPixmap(QPixmap(":/option/resources/radio.png"));

    setAcceptHoverEvents(true);
}

void RadioButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    if (!checked)
    {
        setPixmap(QPixmap(":/option/resources/radiochecked.png"));
        checked = true;
        emit pressed(id);
    }
}

void RadioButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    if (!checked)
    {
        setPixmap(QPixmap(":/option/resources/radiohover.png"));
    }
}

void RadioButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    if (!checked)
    {
        setPixmap(QPixmap(":/option/resources/radio.png"));
    }
}

int RadioButton::getId() const
{
    return id;
}

bool RadioButton::isChecked() const
{
    return checked;
}

void RadioButton::setId(int _id)
{
    id = _id;
}

void RadioButton::setChecked(bool _c)
{
    checked = _c;
}


