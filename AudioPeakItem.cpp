/**************************************************************************
**   Created by TemetNosce 2020/7/20
**************************************************************************/
#include "AudioPeakItem.h"
#include <QDebug>
AudioPeakItem::AudioPeakItem()
{

}

void AudioPeakItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    qDebug()<<"AudioPeakItem:paint";

    painter->setBrush(Qt::darkBlue);
    painter->drawRect(boundingRect());
}

QRectF AudioPeakItem::boundingRect() const
{
    return mRect;
}

QRectF AudioPeakItem::rect() const
{
    return mRect;
}

void AudioPeakItem::setRect(const QRectF &rect)
{
    mRect = rect;
}

