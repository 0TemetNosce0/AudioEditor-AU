/**************************************************************************
**   Created by TemetNosce 2020/7/20
**************************************************************************/

#pragma once
#include <QGraphicsItem>

class AudioScaleItem : public QGraphicsItem
{
public:
    AudioScaleItem();
    QRectF boundingRect()
        const override; //有效区域，更新只会更新这个区域，绘制可以超出这个区域，但是更显的时候超出部分不会更新
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    QPainterPath shape() const override;
    void setRect(const QRectF &rect);

protected:
    //    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    //    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    //    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    //    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;
        virtual void dropEvent(QGraphicsSceneDragDropEvent *event) override;
    virtual void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
    // virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event)override;
    // virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event)override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
//    virtual void focusInEvent(QFocusEvent *event);
//    virtual void focusOutEvent(QFocusEvent *event);
//    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
//    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
//    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event)override;

private:
    QRectF mRect;
};
