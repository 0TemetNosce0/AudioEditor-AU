/**************************************************************************
**   Created by TemetNosce 2020/7/24
**************************************************************************/

#pragma once

#include <QGraphicsItem>
#include <QTimer>

class AudioSelectItem : public QGraphicsItem
{
public:
    AudioSelectItem();
    //有效区域，更新只会更新这个区域，绘制可以超出这个区域，但是更显的时候超出部分不会更新
    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    void setRect(const QRectF &rect);
    QPointF start{0,0};
    QPointF end{0,0};
protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    //    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    //    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;

private:
    QTimer timer;
    QRectF mRect;
    qreal val;
    int mode =0;
};
