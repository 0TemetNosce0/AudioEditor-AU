/**************************************************************************
**   Created by TemetNosce 2020/7/20
**************************************************************************/
#include "AudioPeakItem.h"
#include <QDebug>
#include <QStyleOptionGraphicsItem>
AudioPeakItem::AudioPeakItem()
{
    //    setFlags(QGraphicsItem::ItemIgnoresTransformations);
}
void AudioPeakItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    qDebug() << "AudioPeakItem:paint" << this->pos() << boundingRect();
    QRectF exposedRect = item->exposedRect;
    painter->setBrush(Qt::darkBlue);
    painter->drawRect(boundingRect());

    painter->setPen(Qt::darkYellow);
    // 当前放缩倍数;
    qreal scaleFactor = painter->matrix().m11();
    double scaleFactor1 = 1.0 / painter->matrix().m11();
    // view放大或者缩小，我们在paint方法中进行反操作;
    // 比如view放大了一倍，我们就缩小一倍;view缩小一半，我们就放大一倍;
    painter->scale(scaleFactor1, 1);
    qreal startX = exposedRect.x() * scaleFactor;
    for (int i = startX; i < data.size() /* boundingRect().width()*/; i++) {
        qreal min = data.at(i).min / 256.0 + 0.5;
        qreal max = data.at(i).max / 256.0 + 0.5;
        painter->drawLine(QPointF(i, min * boundingRect().height()), QPointF(i, max * boundingRect().height()));
    }
}

QRectF AudioPeakItem::boundingRect() const { return mRect; }

void AudioPeakItem::setRect(const QRectF &rect) { mRect = rect; }
