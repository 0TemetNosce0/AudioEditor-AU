/**************************************************************************
**   Created by TemetNosce 2020/7/20
**************************************************************************/
#include "WidgetTest.h"
#include <QDebug>
#include <QScrollBar>
WidgetTest::WidgetTest(QWidget *parent) : QWidget(parent)
{
    this->setGeometry(200,200,1000,800);
    view = new AudioTimelineView(this);
    view->move(60,60);
    //    view->setGeometry(0, 0, 200, 200);
//    view->setGeometry(0, 0, 800, 300);
    slider1 = new QSlider(Qt::Horizontal, this);
    slider1->setGeometry(10, 310, 400, 20);
    slider1->setMaximum(100);
    slider1->setMinimum(1);
    slider1->setSingleStep(1);

    connect(slider1, &QSlider::valueChanged, [this](int value) {
        if (cur < value) {
            view->scale(1.1, 1);
            qDebug() << view->rect() << view->scene->sceneRect() << view->matrix().m11(); //缩放;
            qDebug() << view->rect() << view->horizontalScrollBar()->value()
                     << view->horizontalScrollBar()->maximum(); //缩放;
        } else {
            view->scale(0.9, 1);
        }

        cur = value;
        qDebug() << value << view->mapToScene(QPoint(0, 0));
    });
    slider1->setValue(1);
    btn = new QPushButton(this);
    btn->setText("play");
    btn->setGeometry(10, 340, 400, 20);
    playTimeTest.setInterval(20);
    connect(btn, &QPushButton::clicked, [this]() {
        if (playTimeTest.isActive()) {
            playTimeTest.stop();
            view->pause();
        } else {
            playTimeTest.start();
        }
    });
    connect(&playTimeTest, &QTimer::timeout, [this]() { view->play(); });
}
