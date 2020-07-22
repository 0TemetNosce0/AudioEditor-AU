/**************************************************************************
**   Created by TemetNosce 2020/7/20
**************************************************************************/
#include "AudioRulerItem.h"

#include <QDebug>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
AudioRulerItem::AudioRulerItem()
{
    setFlags(/*QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges
                |*/
             //             QGraphicsItem::ItemSendsScenePositionChanges |
             QGraphicsItem::
                 ItemUsesExtendedStyleOption /*|ItemClipsToShape*/ /*|QGraphicsItem::ItemIgnoresTransformations*/);

    setAcceptHoverEvents(true);
}

QRectF AudioRulerItem::boundingRect() const { return mRect; }

void AudioRulerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *)
{
    QRectF exposedRect = item->exposedRect;
    qDebug() << "AudioRulerItem1:" << painter->matrix().m11() << painter->matrix().dx() << exposedRect;

    /*整个底色*/
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkCyan);
    painter->drawRect(this->boundingRect() /*exposedRect*/);
    painter->restore();
    //    return ;
    painter->save();

    // 当前放缩倍数;
    qreal scaleFactor = painter->matrix().m11();
    // 1s对应的宽度
    qreal val1 = mRect.width() * scaleFactor / duration;
    qreal test = type * val1 * typeF;
    if (preScale > scaleFactor) {
        switch (type) {
        case 1:
            if (test < 40) {
                type = 2;

                test = type * val1 * typeF;
            }
            break;
        case 2:
            if (test < 40) {
                type = 5;
                test = type * val1 * typeF;
            }
            break;
        case 5:
            if (test < 40) {
                type = 1;
                typeF = typeF * 10;
                test = type * val1 * typeF;
            }
            break;
        }
    } else if (preScale < scaleFactor) {

        switch (type) {
        case 1:
            if (test > 80) {
                type = 5;
                typeF = typeF / 10;
                test = type * val1 * typeF;
            }
            break;
        case 2:
            if (test > 80) {
                type = 1;
                test = type * val1 * typeF;
            }
            break;
        case 5:
            if (test > 80) {
                type = 2;
                test = type * val1 * typeF;
            }
            break;
        }
    }

    preScale = scaleFactor;

    // Tahoma
    double scaleFactor1 = 1.0 / painter->matrix().m11();
    // view放大或者缩小，我们在paint方法中进行反操作;
    // 比如view放大了一倍，我们就缩小一倍;view缩小一半，我们就放大一倍;
    painter->scale(scaleFactor1, 1 /*scaleFactor1*/);
    QPen myPen = painter->pen();
    // 重新设置画笔线宽;
    //    myPen.setWidthF(myPen.widthF() / scaleFactor); ////线段保持原来的线宽
    myPen.setWidthF(1); //线宽也可以设置为固定值
    myPen.setColor(Qt::red);
    painter->setBrush(Qt::red);
    painter->setPen(myPen);
    QFont font = painter->font();
    font.setFamily("Calibri");
    font.setPointSizeF(font.pointSizeF());
    painter->setFont(font);
    int test1 = 0;
    qreal startX = exposedRect.x() * scaleFactor;
    int val2 = startX / test;
    qreal val3 = test * val2;
    for (qreal i = val3 /*exposedRect.x() * scaleFactor*/; i < item->exposedRect.right() * scaleFactor; i += test) {
        painter->drawLine(QPointF(i, 0), QPointF(i, item->exposedRect.height()));
        painter->drawText(QPointF(i, 0 + 10), QString("%1").arg(i / scaleFactor * duration / mRect.width()));
        test1++;
    }

    qDebug() << "AudioRulerItem" << item->exposedRect << test1 << item->exposedRect.right() << test << val3;
    painter->restore();
}

void AudioRulerItem::setRect(const QRectF &rect) { mRect = rect; }
