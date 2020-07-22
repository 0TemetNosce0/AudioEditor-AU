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
    peakItem = new AudioPeakItem();
    peakItem->setRect(QRectF(0, 0, scene_rect.width(), 200));
    peakItem->setPos(0, audioPeakItem_y);
    //    peakItem->setZValue(1);
    scene->addItem(peakItem);

    scaleItem = new AudioScaleItem();
    scaleItem->setPos(0, scaleItem_y);
    scaleItem->setZValue(1);
    scene->addItem(scaleItem);

    rulerItem = new AudioRulerItem();
    rulerItem->setRect(QRectF(0, 0, scene_rect.width(), 60));
    rulerItem->setPos(0, audioPeakItem_y);
    //    rulerItem->setZValue(2);
    scene->addItem(rulerItem);

    scaleItem1 = new AudioScaleItem();
    scaleItem1->setPos(0, scaleItem_y);
    scaleItem1->setZValue(1);
    //    scene->addItem(scaleItem1);
    //    connect()
    //    scene->setZvalue(0);
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
            //            qDebug() << "-------------2-" << scaleItem->pos();
            scaleItem->setX(tmp /*scaleItem->pos()*/.x() + 0.5);
            qDebug() << "-------------3-" << scaleItem->pos();
            //        scaleItem->update();
            //            update();
        }
    });
}

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
    if (event->pos().x() + 20 > this->rect().width()) {

        //        if (scene->selectedItems().size() > 0) {
        //            //        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        //            //        this->translate(-700,0);
        //            this->horizontalScrollBar()->setValue(this->horizontalScrollBar()->value() + 10);
        //            //        this->setCursor();
        //            // QMatrix matrix;
        //            // matrix.translate(-100, 1);
        //            // matrix.rotate(rotateSlider->value());

        //            // this->setMatrix(matrix);
        qDebug() << "AudioTimelineView:mouseMoveEvent1" << scaleItem->pos();
        timer->start();
        // QGraphicsView::mouseMoveEvent(event);
        return;
        //        }
    }
    timer->stop();
    qDebug() << "AudioTimelineView:mouseMoveEvent" << scaleItem->pos();
    QGraphicsView::mouseMoveEvent(event);
}

void AudioTimelineView::updateValue()
{
    int v1 = this->horizontalScrollBar()->value();
    this->horizontalScrollBar()->setValue(v1 + 1);
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
