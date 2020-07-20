/**************************************************************************
**   Created by TemetNosce 2020/7/20
**************************************************************************/
#include "AudioRulerItem.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDebug>
AudioRulerItem::AudioRulerItem() {}

QRectF AudioRulerItem::boundingRect() const { return mRect; }

void AudioRulerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *)
{

    QRectF exposedRect = item->exposedRect;

    /*整个底色*/
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkCyan);
    painter->drawRect(exposedRect);
    painter->restore();

    qreal startX = exposedRect.x() * duration / mRect.width();
    // 当前放缩倍数;
    qreal scaleFactor = painter->matrix().m11();

    //    //刻度，time
    //    QColor fillColor = QColor(255, 255, 255, 220);
    //    painter->setPen(fillColor);
    //    QFont font;

    //    qreal scale = painter->matrix().m11(); //缩放
    //    // Tahoma
    //    font.setFamily("Calibri");
    //    font.setPixelSize(12);
    //    painter->setFont(font);

    //    qreal exposedX = item->exposedRect.x();

    //    const qreal textY = mRect.height() - (_dpiInfo._rectH + _dpiInfo._lineH[2] + _dpiInfo._textH);
    //    const qreal textH = _dpiInfo._textH;

    qreal test = item->exposedRect.width()*scaleFactor / 10;
    //    painter->setPen(Qt::red);
    QPen myPen = painter->pen();
    // 重新设置画笔线宽;
//    myPen.setWidthF(myPen.widthF() / scaleFactor);////线段保持原来的线宽
    myPen.setWidthF(1);//线宽也可以设置为固定值
    myPen.setColor(Qt::red);
    painter->setPen(myPen);
    //        painter->setPen(Qt::red);
    //        painter->setBrush(Qt::red);
    //        painter->drawRect(exposedRect);

    // Tahoma
    double scaleFactor1 = 1.0 / painter->matrix().m11();

    // view放大或者缩小，我们在paint方法中进行反操作;
    // 比如view放大了一倍，我们就缩小一倍;view缩小一半，我们就放大一倍;
    painter->scale(scaleFactor1, 1/*scaleFactor1*/);
    QFont font = painter->font();
    font.setFamily("Calibri");
    font.setPointSizeF(font.pointSizeF() /*/ scaleFactor*/);
    painter->setFont(font);
    for (qreal i = exposedRect.x(); i < item->exposedRect.width()*scaleFactor; i += test) {
        painter->drawLine(QPointF(i, 0), QPointF(i, item->exposedRect.height()));
        painter->drawText(QPointF(i, 0), QString("%1").arg(i /scaleFactor* duration / mRect.width()));
    }
    qDebug()<<"AudioRulerItem"<<item->exposedRect.width()<<test;
}

void AudioRulerItem::setRect(const QRectF &rect) { mRect = rect; }
