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
AudioScaleItem::AudioScaleItem()
{
    setAcceptHoverEvents(true);
    setFlags(QGraphicsItem::ItemIgnoresTransformations | QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemSendsScenePositionChanges);

}

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

    qDebug() << "AudioScaleItem:mouseMoveEvent" << event->pos();

    QGraphicsItem::mouseMoveEvent(event);
}

void AudioScaleItem::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug() << "AudioScaleItem:dragMoveEvent" << event->pos();
    return QGraphicsItem::dragMoveEvent(event);
}

void AudioScaleItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug() << "AudioScaleItem:hoverLeaveEvent" << event->pos();
    return QGraphicsItem::hoverLeaveEvent(event);
}
QVariant AudioScaleItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
        // value is the new position.
        QPointF newPos = value.toPointF();
            qDebug()<<"=====================itemChange"<<newPos;
    }

    return QGraphicsItem::itemChange(change, value);
}
