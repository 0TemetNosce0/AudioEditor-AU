/**************************************************************************
**   Created by TemetNosce 2020/7/20
**************************************************************************/
#pragma once

#include <QGraphicsItem>

class AudioRulerItem : public QGraphicsItem
{
public:
    AudioRulerItem();
    //有效区域，更新只会更新这个区域，绘制可以超出这个区域，但是更显的时候超出部分不会更新
    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    void setRect(const QRectF &rect);

    void setTypeF();

protected:
    //    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    //    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    //    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    //    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    //    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;

private:
    QRectF mRect;
//    qreal duration = 63.5;
    qreal preScale = 1.0;
    int type = 1; // 125
    qreal typeF = 1;
//    int maxWidth = 100;
    int minWidth = 50;
    // 1,2,5;
};
