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
    setFlags(/*QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges
                |*/
             //             QGraphicsItem::ItemSendsScenePositionChanges |
             QGraphicsItem::
                 ItemUsesExtendedStyleOption /*|ItemClipsToShape*/ /*|QGraphicsItem::ItemIgnoresTransformations*/);

    setAcceptHoverEvents(true);
    timer.setInterval(20);
    QObject::connect(&timer, &QTimer::timeout, [this]() {
        //        qDebug() << scene->selectedItems().size();
        //        if (scene->selectedItems().size() > 0) {
        QGraphicsView *view = scene()->views().at(0);
        view->horizontalScrollBar()->setValue(view->horizontalScrollBar()->value() + val); //这里他有还原之前的了。
                                                                                           //        }
    });
}

QRectF AudioSelectItem::boundingRect() const { return mRect; }

void AudioSelectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *)
{
    QRectF exposedRect = item->exposedRect;
    //    qDebug() << "AudioSelectItem1:" << painter->matrix().m11() << painter->matrix().dx() << exposedRect;
    // painter->setCompositionMode(QPainter::CompositionMode_Difference);
    /*整个底色*/
    //    painter->save();
    //    painter->setPen(Qt::NoPen);
    painter->setOpacity(0.5);
    painter->setBrush(QColor(20, 35, 120) /*Qt::darkMagenta*/);

    painter->drawRect(start.x(), 0, end.x() - start.x(), boundingRect().height());
    //    painter->restore();
    //    return ;
    //    painter->save();
}

void AudioSelectItem::setRect(const QRectF &rect) { mRect = rect; }

void AudioSelectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    mode = 1;
    start = event->pos();
    end = start;

    qDebug() << "111" << event->pos() << event->scenePos();
    //    QGraphicsItem::mousePressEvent(event);
}

void AudioSelectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    if (mode == 1) {
        QGraphicsView *view = scene()->views().at(0);

        auto val1 = mapToScene(event->pos());
        if (view->mapFromScene(val1).x() + 50 > view->width()) {
            if (!timer.isActive()) {
                timer.start();
            }
            end = mapFromScene(view->mapToScene(view->width()-50, 0));
            val = 2/*view->mapFromScene(val1).x() + 20 - view->width()*/;
//            update();
            return;
        }
        if (timer.isActive()) {
            timer.stop();
        }
        end = event->pos();
        update();
        //        return ;
    }
    //    QGraphicsItem::mouseMoveEvent(event);
}

void AudioSelectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    mode = 0;
    if (timer.isActive()) {
        timer.stop();
    }
    //    QGraphicsItem::mouseReleaseEvent(event);
}
