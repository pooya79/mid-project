#include "option.h"
#include <QSlider>
#include <QtDebug>
#include <QGraphicsProxyWidget>


Option::Option(double _sizeRatio, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
    , sizeRatio {_sizeRatio}
{
    // draw options
    setPixmap(QPixmap(":/option/resources/base.png").scaled(1000*sizeRatio, 741*sizeRatio));
    setPos(100*sizeRatio, 30*sizeRatio);

    // initializing
    data[0] = 2;
    QFont font("Arial", 30*sizeRatio);
    nRows = new QGraphicsTextItem("2",this);
    nRows->setFont(font);
    nRows->setPos(800*sizeRatio,115*sizeRatio);
    nRows->setDefaultTextColor(Qt::white);
    data[1] = 2;
    nColumns = new QGraphicsTextItem("2",this);
    nColumns->setFont(font);
    nColumns->setPos(800*sizeRatio,170*sizeRatio);
    nColumns->setDefaultTextColor(Qt::white);

}

void Option::setUp()
{
    // drawing dimensions slider
    drawSliders();
    // drawing radio buttons
    drawSolveAlg();
    drawCharacter();
    drawDragon();
}

void Option::drawSliders()
{
    QGraphicsProxyWidget* proxyNSlider = new QGraphicsProxyWidget(this);
    QSlider* nSlider = new QSlider(Qt::Horizontal);
    nSlider->setMaximum(100);
    nSlider->setMinimum(2);
    connect(nSlider, &QSlider::sliderMoved,
            this, &Option::rowChanged);
    nSlider->setGeometry(0,0,245,40);
    nSlider->setStyleSheet(QString("* { background-image : url(:/option/resources/slideBar.png);}"
                                   "*::groove:horizontal { image : url(:/option/resources/rowLine.png);}"
                                   "*::handle:hrizontal { image : url(:/option/resources/handle.png);}")
                                   );
    proxyNSlider->setWidget(nSlider);
    proxyNSlider->setScale(sizeRatio);
    proxyNSlider->setPos(524*sizeRatio,132*sizeRatio);

    QGraphicsProxyWidget* proxyMSlider = new QGraphicsProxyWidget(this);
    QSlider* mSlider = new QSlider(Qt::Horizontal);
    mSlider->setGeometry(0,0,245,40);
    mSlider->setMaximum(100);
    mSlider->setMinimum(2);
    connect(mSlider, &QSlider::sliderMoved,
            this, &Option::columnChanged);
    mSlider->setStyleSheet(QString("* { background-image : url(:/option/resources/slideBar.png);}"
                                   "*::groove:horizontal { image : url(:/option/resources/columnLine.png);}"
                                   "*::handle:hrizontal { image : url(:/option/resources/handle.png);}")
                                   );
    proxyMSlider->setWidget(mSlider);
    proxyMSlider->setScale(sizeRatio);
    proxyMSlider->setPos(524*sizeRatio,183*sizeRatio);
}

void Option::drawSolveAlg()
{
    for (int i {1}; i<=2; i++)
    {
        RadioButton* radioB = new RadioButton(i, this);
        connect(radioB, &RadioButton::pressed,
                this, &Option::algChanged);
        radioB->setScale(sizeRatio);
        radioB->setPos((240+227*i)*sizeRatio, 259*sizeRatio);
        solveAlg.insert(i, radioB);
    }
}

void Option::drawCharacter()
{
    for (int i {1}; i<=4; i++)
    {
        RadioButton* radioB = new RadioButton(i, this);
        connect(radioB, &RadioButton::pressed,
                this, &Option::characterChanged);
        radioB->setScale(sizeRatio);
        radioB->setPos((244+150*i)*sizeRatio, 366*sizeRatio);
        character.insert(i, radioB);
    }
}

void Option::drawDragon()
{
    for (int i {1}; i<=4; i++)
    {
        RadioButton* radioB = new RadioButton(i, this);
        connect(radioB, &RadioButton::pressed,
                this, &Option::dragonChanged);
        radioB->setScale(sizeRatio);
        radioB->setPos((244+150*i)*sizeRatio, 488*sizeRatio);
        dragon.insert(i, radioB);
    }
}

std::array<int, 5> Option::getData() const
{
    return data;
}

void Option::rowChanged(int _n)
{
    nRows->setPlainText(QString::number(_n));
    data[0] = _n;
}

void Option::columnChanged(int _m)
{
    nColumns->setPlainText(QString::number(_m));
    data[1] = _m;
}

void Option::algChanged(int _id)
{
    if (_id == 1)
    {
        solveAlg[2]->setPixmap(QPixmap(":/option/resources/radio.png"));
        solveAlg[2]->setChecked(false);
    }
    else
    {
        solveAlg[1]->setPixmap(QPixmap(":/option/resources/radio.png"));
        solveAlg[1]->setChecked(false);
    }
    data[2]=_id;
}

void Option::characterChanged(int _id)
{
    for (int i{1}; i<=4; i++)
    {
        if (i != _id)
        {
            character[i]->setPixmap(QPixmap(":/option/resources/radio.png"));
            character[i]->setChecked(false);
        }
    }
    data[3]=_id;
}

void Option::dragonChanged(int _id)
{
    for (int i{1}; i<=4; i++)
    {
        if (i != _id)
        {
            dragon[i]->setPixmap(QPixmap(":/option/resources/radio.png"));
            dragon[i]->setChecked(false);
        }
    }
    data[4]=_id;
}
