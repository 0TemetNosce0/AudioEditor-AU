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
            QPointF tmp = scaleItem->pos();
            //        scaleItem->setX(scaleItem->pos().x() + 2);
            horizontalScrollBar()->setValue(horizontalScrollBar()->value() + 2); //这里他有还原之前的了。
            qDebug() << "-------------2-" << scaleItem->pos();
            scaleItem->setX(tmp /*scaleItem->pos()*/.x() + 0.5);
            qDebug() << "-------------3-" << scaleItem->pos();
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
    if (event->pos().x() > this->rect().width()) {
        qDebug() << "AudioTimelineView:mouseMoveEvent1" << scaleItem->pos();
        timer->start();
        return;
    }
    timer->stop();
    qDebug() << "AudioTimelineView:mouseMoveEvent" << scaleItem->pos();
    QGraphicsView::mouseMoveEvent(event);
}

void AudioTimelineView::play() {


    scaleItem->setPos(scaleItem->pos().x()+1,scaleItem->pos().y());


}

void AudioTimelineView::pause() {

}

AudioTimelineScene::AudioTimelineScene() {}

void AudioTimelineScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    qDebug() << "AudioTimelineScene mouseMoveEvent" << event->pos();
    QList<QGraphicsItem *> items = selectedItems();
    if (items.size() > 0) {
        qDebug() << items.at(0)->pos();
    }
    QGraphicsScene::mouseMoveEvent(event);
}
