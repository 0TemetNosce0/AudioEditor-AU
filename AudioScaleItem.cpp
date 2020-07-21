/**************************************************************************
**   Created by TemetNosce 2020/7/20
**************************************************************************/
#include "AudioScaleItem.h"

#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QPainter>
AudioScaleItem::AudioScaleItem() { setFlags(QGraphicsItem::ItemIgnoresTransformations| QGraphicsItem::ItemIsMovable); }

QRectF AudioScaleItem::boundingRect() const { return mRect; }

void AudioScaleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{

    qDebug() << "AudioScaleItem:paint";
    painter->setBrush(Qt::darkGreen);
    painter->drawRect(0, 0, 20, 20);
    painter->setPen(Qt::darkGreen);
    painter->drawLine(QPoint(10, 20), QPoint(10, 60));
}

void AudioScaleItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    qDebug()<<"AudioScaleItem:mouseMoveEvent"<<event->pos();

    emit updateValue();
    return ;
    QGraphicsItem::mouseMoveEvent(event);
}
