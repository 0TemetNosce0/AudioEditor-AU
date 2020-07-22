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
             QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsScenePositionChanges);
}

QRectF AudioScaleItem::boundingRect() const { return mRect; }

void AudioScaleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{

    qDebug() << "AudioScaleItem:paint";
    painter->setBrush(Qt::darkGreen);
    painter->drawRect(0, 0, mRect.width(), mRect.width());
    painter->setPen(Qt::darkGreen);
    painter->drawLine(QPointF(mRect.width() / 2, mRect.width()), QPoint(mRect.width() / 2, mRect.height()));
}

QPainterPath AudioScaleItem::shape() const
{
    QPainterPath path;
        path.addRect(0, 0, mRect.width(), mRect.width());
//    path.addRect(mRect);
    return path;
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
        //        // value is the new position.

        QPointF newPos = value.toPointF();
        //        //        QRectF rect = scene()->sceneRect();
        //        //        if (!rect.contains(newPos)) {
        //        //            // Keep the item inside the scene rect.
        //        //            newPos.setX(0/*qMin(rect.right(), qMax(newPos.x(), rect.left()))*/);
        //        //            newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
        //        //            return newPos;
        //        //        }
        newPos.setY(20);
        return QGraphicsItem::itemChange(change, newPos);
    }
    return QGraphicsItem::itemChange(change, value);
}
void AudioScaleItem::setRect(const QRectF &rect) { mRect = rect; }
