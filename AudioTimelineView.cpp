/**************************************************************************
**   Created by TemetNosce 2020/7/17
**************************************************************************/
#include "AudioTimelineView.h"
#include <QDebug>
#include <QDropEvent>
#include <QScrollBar>
#include <QTimer>
#include <qgraphicssceneevent.h>
AudioTimelineView::AudioTimelineView(QWidget *parent) : QGraphicsView(parent)
{
    scene = new AudioTimelineScene();
    scene->setSceneRect(QRectF(0, 0, withDuration, 200));
    //
    setScene(scene);
    QRectF scene_rect = scene->sceneRect();
    this->setSceneRect(scene_rect);
    //    this->setDragMode(RubberBandDrag/*ScrollHandDrag*/);
    //   setStyleSheet("background: transparent;border:0px");
    //   setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //   setStyleSheet("padding:0px;border:0px");
    setStyleSheet("padding:0px;border:0px");
    //  setCacheMode(QGraphicsView::CacheBackground);//缓存模式
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate); //场景重绘更新方式

    rulerItem = new AudioRulerItem();
    rulerItem->setRect(QRectF(0, 0, withDuration, 60));
    rulerItem->setPos(0, 0);
    //    rulerItem->setZValue(2);
    scene->addItem(rulerItem);

    peakItem = new AudioPeakItem();
    peakItem->setRect(QRectF(0, 0, withDuration, 200));
    peakItem->setPos(0, 60);
    //    peakItem->setZValue(1);
    scene->addItem(peakItem);

    scaleItem = new AudioScaleItem();
    scaleItem->setPos(0, 20);
    scaleItem->setRect(QRectF(0, 0, 10, 200 + 60 - 20));
    scaleItem->setZValue(1);
    scene->addItem(scaleItem);

    //        setScale(QPointF(1.0,1.0));

    timer = new QTimer;
    timer->setInterval(80);
    connect(timer, &QTimer::timeout, [this]() {
        qDebug() << scene->selectedItems().size();
        //        scaleItem->scene()->clearSelection();
        //        scaleItem->setSelected(false);
        if (scene->selectedItems().size() > 0) {
            //            scaleItem->setActive(false);
            //            scaleItem->setFocus(Qt::FocusReason focusReason = Qt::OtherFocusReason);
            //            scaleItem->clearFocus();

            //            QPointF tmp = scaleItem->pos();
            //        scaleItem->setX(scaleItem->pos().x() + 2);
            horizontalScrollBar()->setValue(horizontalScrollBar()->value() + val1); //这里他有还原之前的了。
                                                                                 //            scaleItem->scroll(2,1);
            //            qDebug() << "-------------2-" << scaleItem->pos();
            //            scaleItem->setX(tmp /*scaleItem->pos()*/.x() - 0.5);
            //            qDebug() << "-------------3-" << scaleItem->pos();
            //        scaleItem->update();
            //            update();
        }
    });
}

void AudioTimelineView::leaveEvent(QEvent *event) { qDebug() << "AudioTimelineViewleaveEvent"; }

void AudioTimelineView::drawBackground(QPainter *painter, const QRectF &rect)
{

    QGraphicsView::drawBackground(painter, rect);
}

void AudioTimelineView::drawForeground(QPainter *painter, const QRectF &rect)
{

    QGraphicsView::drawForeground(painter, rect);
}

void AudioTimelineView::mouseMoveEvent(QMouseEvent *event)
{
    if (event->pos().x() + 40 > this->rect().width()) {
        //        qDebug() << "AudioTimelineView:mouseMoveEvent1" << scaleItem->pos();
        //         scaleItem->setAcceptedMouseButtons(Qt::NoButton);
        //        scaleItem->setFlag(QGraphicsItem::ItemIsMovable, false);
        qDebug()<<"AudioTimelineView:mouseMoveEvent"<<(event->pos().x()-this->rect().width())/10;
//        timer->setInterval(1/(event->pos().x()+40-this->rect().width())*10);
        val1 = (event->pos().x()+40-this->rect().width())/10;
        if (!timer->isActive()) {
        timer->start();
        }
         return;
    }
    if (timer->isActive()) {
        timer->stop();
//        QGraphicsView::mouseMoveEvent(event);
//        peakItem->setPos(0/*this->rect().width() - 20*/, 60);

//        return;
        //        scaleItem->setFlag(QGraphicsItem::ItemIsMovable, true);
        //        qDebug() << "_______________1" << scaleItem->pos();
        //        scaleItem->setX(event->x());

        //        qDebug() << "_______________2" << scaleItem->pos();
        //    scaleItem->setAcceptedMouseButtons(Qt::LeftButton);
        //        event->setLocalPos();
        //        QGraphicsView::mouseMoveEvent(event);
//                return;
    }
//    qDebug() << "AudioTimelineView:mouseMoveEvent" << scaleItem->pos();
//    qDebug() << this->pos() << event->pos() << event->globalPos() << event->localPos() << event->windowPos()
//             << event->screenPos();

    QGraphicsView::mouseMoveEvent(event);
}

void AudioTimelineView::scrollContentsBy(int dx, int dy)
{
    qDebug() << "AudioTimelineView:scrollContentsBy" << dx << dy << scaleItem->pos();

    QGraphicsView::scrollContentsBy(dx, dy);
    //    scaleItem->setX(scaleItem->pos().x()+dx);
}

void AudioTimelineView::play() { scaleItem->setPos(scaleItem->pos().x() + 1, scaleItem->pos().y()); }

void AudioTimelineView::pause() {}

AudioTimelineScene::AudioTimelineScene() {}

void AudioTimelineScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

//    qDebug() << "AudioTimelineScene mouseMoveEvent" << event->pos() << event->lastPos() << event->lastScreenPos()
//             << event->screenPos() << this->width();
//    QList<QGraphicsItem *> items = selectedItems();
//    if (items.size() > 0) {
//        qDebug() << items.at(0)->pos();
//    }
    //    if()

//    QPoint pot = this->views().at(0)->mapFromScene(event->screenPos());
//    if (pot.x() + 20 > this->views().at(0)->width()) {

//        qDebug() << pot << this->views().at(0)->mapToScene(event->screenPos());
//        return;
//    }
    QGraphicsScene::mouseMoveEvent(event);
}
