/**************************************************************************
**   Created by TemetNosce 2020/7/20
**************************************************************************/
#pragma once

#include "WavThumb.h"

#include <QGraphicsItem>
#include <QPainter>

class AudioPeakItem : public QGraphicsItem
{
public:
    AudioPeakItem();

    // QGraphicsItem interface

    void setRect(const QRectF &rect);

    std::vector<MinMaxValue>  data;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    QRectF boundingRect() const override;

private:
    QRectF mRect/*{0,0,60,60}*/;
};
