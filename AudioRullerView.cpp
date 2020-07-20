/**************************************************************************
**   Created by TemetNosce 2020/7/16
**************************************************************************/
#include "AudioRullerView.h"
//#include <QDebug>
//#include <QScrollBar>
//#include <QTime>
//#include <QWheelEvent>
//AudioRullerView::AudioRullerView(QWidget *parent) : QGraphicsView(parent) /*,CRulerBase(parent)*/
//{
//    scene = new RulerScene();
//    scene->setSceneRect(QRect(0, 0, 100, 50));
//    this->setScene(scene);
//    //       mGraphicsView->setFixedSize(400, 400);
//    this->setSceneRect(QRect(0, 0, 100, 50));
//    rulerItem = new RulerItem();
//    rulerItem->setPos(0, 0);
//    scene->addItem(rulerItem);

//    setStyleSheet("background: transparent;border:0px");
//    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
//    //    this->setStyleSheet("padding:0px;border:0px");
//}
////#include "RulerScene.h"
//void AudioRullerView::paintEvent(QPaintEvent *event) {
////    this->viewport()->rect().left()

//qDebug()<< mapToScene(this->viewport()->rect().x(),this->viewport()->rect().y());
//    return QGraphicsView::paintEvent(event);

//}
//void AudioRullerView::wheelEvent(QWheelEvent *event)
//{
//    //    this->scale(0.5, 1);
//    int numDegrees = event->delta() / 8;
//    if (numDegrees > 0) {
//        qDebug()<<this->horizontalScrollBar()->value()<<this->horizontalScrollBar()->maximum()<<this->horizontalScrollBar()->minimum();
//        this->scale(0.5, 1);
//    } else {
//        qDebug()<<this->horizontalScrollBar()->value()<<this->horizontalScrollBar()->maximum()<<this->horizontalScrollBar()->minimum();
//        this->scale(1.5, 1);
//    }
//    qDebug()<<scene->sceneRect();
//    //    this->scale(m_scale, m_scale);
//    //    qDebug()<<m_scale;
//}

//void AudioRullerView::drawBackground(QPainter *painter, const QRectF &rect)
//{
//    QScrollBar *horizontal = this->verticalScrollBar();
//    qreal x = sceneRect().width() * (horizontal->value() - horizontal->minimum())/
//              (qreal)(horizontal->maximum() - horizontal->minimum() + horizontal->pageStep());
//    //
//    QPointF delta(x,0);
//    qreal visibleWidth = viewport()->rect().width();


//    //qDebug() << delta << visibleWidth << sceneRect();
////刻度，时间
//    QRectF border = QRectF(delta,QSizeF(visibleWidth,0));
//    if (rect.intersects(border))
//    {
//        QBrush fillBrush(QColor(166,166,166));
//        painter->setBrush(fillBrush);
//        painter->drawRect(border);

//        QBrush textBrush(QColor(0,0,0));

//        QPen linePen(QColor(0,0,0));
//        linePen.setWidth(0);
//        painter->setPen(linePen);

//        double framerate = 60.0;
////        if (m_timeline)
////        {
////            m_lastTimeForegroundDraw = 0/*m_timeline->music()->getTime()*/;
////        }

//        //TODO condition for framerate
//        {
//            double step = framerate;
//            while (border.width()/step > 15.0)
//            {
//                step *= 2.0;
//            }
////            QFont textFont;
////            textFont.setPointSizeF(sceneBorderHeight()*0.5);
////            textFont.setStretch((int)(100 * 1.0 / m_scale.x()));
////            painter->setFont(textFont);


//            qreal sp = (border.height())*0.6 + border.top();
//            double start = rect.left() - fmod(rect.left(),step);
//            for (double f = start; f < rect.right(); f+=step)
//            {
//                painter->drawLine(QPointF(f,sp),QPointF(f,border.bottom()));
//            }
//            sp = (border.height())*0.8 + border.top();
//            for (double f = start+step/2.0; f < rect.right(); f+=step)
//            {
//                painter->drawLine(QPointF(f,sp),QPointF(f,border.bottom()));
//            }

//            QTime time;
//            painter->setBrush(textBrush);
//            for (double f = start; f < border.right(); f+=step)
//            {
//                double f_f = f/framerate; //in sec
//                time.setHMS(0,f_f/60.0,fmod(f_f,60.0));
////                painter->drawText(QRectF(f - step*0.9,border.top(),step*1.8,sceneBorderHeight()*0.5),Qt::AlignCenter,time.toString("mm:ss"));
//            }
//        }

////        qreal lineWidth = 2.0 / m_scale.x();
////        linePen.setWidthF(lineWidth);
////        painter->setPen(linePen);
////        double m_t = m_lastTimeForegroundDraw * framerate;
////        if (m_t >= rect.left() && m_t <= rect.right())
////        {
////            QLineF line(QPointF(m_t,rect.top()),QPointF(m_t,rect.bottom()));
////            painter->drawLine(line);
////        }

////        m_lastBorderRect = border;
//    }

//    QGraphicsView::drawForeground(painter,rect);
//}

//void AudioRullerView::mousePressEvent(QMouseEvent *event) { QGraphicsView::mousePressEvent(event); }
