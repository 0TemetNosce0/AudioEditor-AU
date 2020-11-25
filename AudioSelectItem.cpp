/**************************************************************************
**   Created by TemetNosce 2020/7/24
**************************************************************************/
#include "AudioSelectItem.h"

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsView>
#include <QPainter>
#include <QScrollBar>
#include <QStyleOptionGraphicsItem>
AudioSelectItem::AudioSelectItem()
{
    //    setFlags(ItemUsesExtendedStyleOption);
    setAcceptHoverEvents(true);
    timer.setInterval(20);
    QObject::connect(&timer, &QTimer::timeout, [this]() {
        QGraphicsView *view = scene()->views().at(0);
        view->horizontalScrollBar()->setValue(view->horizontalScrollBar()->value() + val); //这里他有还原之前的了。
    });
}

QRectF AudioSelectItem::boundingRect() const { return mRect; }

void AudioSelectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *)
{
    QRectF exposedRect = item->exposedRect;
    // painter->setCompositionMode(QPainter::CompositionMode_Difference);
    painter->setPen(Qt::NoPen);
    painter->setOpacity(0.5);
    painter->setBrush(QColor(20, 35, 120));
    painter->drawRect(start.x(), 0, end.x() - start.x(), boundingRect().height());
}

void AudioSelectItem::setRect(const QRectF &rect) { mRect = rect; }

void AudioSelectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() & Qt::LeftButton) {
        start = event->pos();
        end = start;
    }
    //    QGraphicsItem::mousePressEvent(event);
}

void AudioSelectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    if (event->button() & Qt::LeftButton) {
        QGraphicsView *view = scene()->views().at(0);

        auto val1 = mapToScene(event->pos());
        if (view->mapFromScene(val1).x() + 50 > view->width()) {
            if (!timer.isActive()) {
                timer.start();
            }
            end = mapFromScene(view->mapToScene(view->width() - 50, 0));
            val = 2 /*view->mapFromScene(val1).x() + 20 - view->width()*/;
            return;
        }
        if (timer.isActive()) {
            timer.stop();
        }
        end = event->pos();
        update();
    } else if (event->button() & Qt::NoButton) {
    }
    //    QGraphicsItem::mouseMoveEvent(event);
}

void AudioSelectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() & Qt::LeftButton) {
        if (timer.isActive()) {
            timer.stop();
        }
        update();
        qDebug()<<"1111111111"<<start<<end;
    }
    //    QGraphicsItem::mouseReleaseEvent(event);
}
