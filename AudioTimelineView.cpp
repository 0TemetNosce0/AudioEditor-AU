/**************************************************************************
**   Created by TemetNosce 2020/7/17
**************************************************************************/
#include "AudioTimelineView.h"

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
    rulerItem->setZValue(2);
    scene->addItem(rulerItem);

    //    scene->setZvalue(0);
    //        setScale(QPointF(1.0,1.0));
}

void AudioTimelineView::drawBackground(QPainter *painter, const QRectF &rect)
{

    QGraphicsView::drawBackground(painter, rect);
}

void AudioTimelineView::drawForeground(QPainter *painter, const QRectF &rect)
{

    QGraphicsView::drawForeground(painter, rect);
}

AudioTimelineScene::AudioTimelineScene() {}
