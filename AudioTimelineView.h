/**************************************************************************
**   Created by TemetNosce 2020/7/17
**************************************************************************/
#pragma once

#include "AudioPeakItem.h"
#include "AudioRulerItem.h"
#include "AudioScaleItem.h"
#include "AudioSelectItem.h"

#include <QGraphicsScene>
#include <QGraphicsView>
class AudioTimelineView;
class AudioTimelineScene : public QGraphicsScene
{
public:
    AudioTimelineScene();
    AudioTimelineView*  timelineview() const;

    //        virtual void drawBackground(QPainter *painter, const QRectF &rect) override;
    //    virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    //    virtual void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    //    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    //    virtual void dropEvent(QGraphicsSceneDragDropEvent *event);
    //    virtual void focusInEvent(QFocusEvent *event);
    //    virtual void focusOutEvent(QFocusEvent *event);
    //    virtual void helpEvent(QGraphicsSceneHelpEvent *event);
    //    virtual void keyPressEvent(QKeyEvent *event);
    //    virtual void keyReleaseEvent(QKeyEvent *event);
    //    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    //    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    //    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    //    virtual void wheelEvent(QGraphicsSceneWheelEvent *event);
    //    virtual void inputMethodEvent(QInputMethodEvent *event);
};
class AudioTimelineView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit AudioTimelineView(QWidget *parent = nullptr);
    //    void paintEvent(QPaintEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
    //    void wheelEvent(QWheelEvent *event);
    virtual void leaveEvent(QEvent *event) override;
    virtual void drawBackground(QPainter *painter, const QRectF &rect) override;
    virtual void drawForeground(QPainter *painter, const QRectF &rect) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
      void scrollContentsBy(int dx, int dy) override;
    // private:
    AudioTimelineScene *scene = nullptr;
    AudioPeakItem *peakItem = nullptr;
    AudioScaleItem *scaleItem = nullptr;
    AudioRulerItem *rulerItem = nullptr;
    AudioSelectItem * selectItem = nullptr;
    int value = 0;
    int max;
    int min;
    int start = 0;
    qreal mark_h;
    qreal ruler_y;
    qreal audioPeakItem_y = 0;
    qreal rulerItem_y = 0;
    qreal scaleItem_y = 0;

    QTimer *timer;
    qreal withDuration = 600; // pix
    qreal duration = 62.5;    // s
    qreal val1  = 1;
    //

    qreal startSelect;//s
    qreal durationSelect;//s
    int mode  =0;
    void play();
    void pause();
    qreal getDuration() const;
    void setDuration(const qreal &value);

    void updatePeak(double start);
};
