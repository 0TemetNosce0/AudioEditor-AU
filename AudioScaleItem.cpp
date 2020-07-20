/**************************************************************************
**   Created by TemetNosce 2020/7/20
**************************************************************************/
#include "AudioScaleItem.h"

#include <QPainter>
#include <QDebug>
AudioScaleItem::AudioScaleItem() {setFlag(QGraphicsItem::ItemIgnoresTransformations);}

QRectF AudioScaleItem::boundingRect() const { return mRect; }

void AudioScaleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{

    qDebug()<<"AudioScaleItem:paint";
    painter->setBrush(Qt::red);
    painter->drawRect(0, 0, 20, 20);
    painter->setPen(Qt::red);
    painter->drawLine(QPoint(10, 20), QPoint(10, 60));
}
