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
    scene->setSceneRect(QRectF(0, 0, withDuration, 260));
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


    selectItem = new AudioSelectItem();
    selectItem->setRect(QRectF(0, 0, withDuration, 260));
    selectItem->setPos(0, 0);
    //    peakItem->setZValue(1);
    scene->addItem(selectItem);

    scaleItem = new AudioScaleItem();
    scaleItem->setPos(0, 20);
    scaleItem->setRect(QRectF(0, 0, 10, 200 + 60 - 20));
    scaleItem->setZValue(1);
    scene->addItem(scaleItem);

    //        setScale(QPointF(1.0,1.0));

    timer = new QTimer;
    timer->setInterval(80);
    connect(timer, &QTimer::timeout, [this]() {
        //        qDebug() << scene->selectedItems().size();
        if (scene->selectedItems().size() > 0) {
            horizontalScrollBar()->setValue(horizontalScrollBar()->value() + val1); //这里他有还原之前的了。
        }
    });
}

void AudioTimelineView::mousePressEvent(QMouseEvent *event)
{
//    if((event->pos().x()<mapFromScene(startSelect+durationSelect,0).x()+5)&&(event->pos().x()>mapFromScene(startSelect+durationSelect,0).x()-5)){
//       mode  = 2;
////        setCursor(Qt::SizeHorCursor);

//        return ;
//    }
    QPointF sceneP = mapToScene(event->pos());
    startSelect = sceneP.x() /**duration/withDuration*/;
    durationSelect = 0;
    mode = 1;
    //    qDebug()<<startSelect<<sceneP.x();
    QGraphicsView::mousePressEvent(event);
}

void AudioTimelineView::mouseReleaseEvent(QMouseEvent *event)
{
    mode = 0;
    QGraphicsView::mouseReleaseEvent(event);
}

void AudioTimelineView::leaveEvent(QEvent *event) { qDebug() << "AudioTimelineViewleaveEvent"; }

void AudioTimelineView::drawBackground(QPainter *painter, const QRectF &rect)
{

    QGraphicsView::drawBackground(painter, rect);
}

void AudioTimelineView::drawForeground(QPainter *painter, const QRectF &rect)
{
//    auto v1 = mapFromScene(startSelect, 0);
//    auto v2 = mapFromScene(durationSelect + startSelect, 0);
//    painter->setBrush(Qt::magenta);
//    painter->drawRect(v1.x(), 0, v2.x() - v1.x(), this->height());
    QGraphicsView::drawForeground(painter, rect);
}

void AudioTimelineView::mouseMoveEvent(QMouseEvent *event)
{


//    if((mode == 1) &&(event->pos().x()<mapFromScene(startSelect+durationSelect,0).x()+5)&&(event->pos().x()>mapFromScene(startSelect+durationSelect,0).x()-5)){
////        mode  = 2;
//        setCursor(Qt::SizeHorCursor);

//        return ;
//    }
//    if(mode ==2){
//        QPointF sceneP = mapToScene(event->pos());
//        durationSelect = sceneP.x() - startSelect;
//        update();
//          return;
//    }
// setCursor(Qt::ArrowCursor);
//    if (mode == 1) {
//        QPointF sceneP = mapToScene(event->pos());
//        durationSelect = sceneP.x() - startSelect;
//        update();
//        //    invalidateScene(this->rect(),QGraphicsScene::ForegroundLayer);
//        return;
//    }
    if (event->pos().x() + 20 > this->rect().width()) {
        if (scaleItem->isSelected()) {
            val1 = (event->pos().x() + 20 - this->rect().width()) / 10;
            if (!timer->isActive()) {
                timer->start();
            }
            return;
        }
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
