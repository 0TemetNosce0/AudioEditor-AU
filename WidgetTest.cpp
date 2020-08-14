/**************************************************************************
**   Created by TemetNosce 2020/7/20
**************************************************************************/
#include "WidgetTest.h"
#include <QDebug>
#include <QScrollBar>
#include <fstream>
#include <qmath.h>
WidgetTest::WidgetTest(QWidget *parent) : QWidget(parent)
{
    //读取文件大小
    std::ifstream file;
    file.open("F:/TemetNosce-gitee/AudioEditor-AU/wavthumbtest.tmp", std::ios::binary);
    int64_t file_length = 0;
    if (!file) { //简析
        qDebug("getWavThumb fileopen fail.");
        file_length = 0;
        //                return s;
    } else {                               //文件读取
        file.seekg(0, std::ifstream::end); // go back to the beginning

        file.seekg(0, std::ifstream::end);
        file_length = file.tellg();
    }

    double duration = file_length/2/44100.0*512;

    this->setGeometry(200, 200, 1000, 800);
    view = new AudioTimelineView(this);
    view->setDuration(duration);
    view->move(60, 60);
    //    view->setGeometry(0, 0, 200, 200);
    //    view->setGeometry(0, 0, 800, 300);
    slider1 = new QSlider(Qt::Horizontal, this);
    slider1->setGeometry(10, 350, 400, 20);
    slider1->setMaximum(100);
    slider1->setMinimum(10);
    slider1->setSingleStep(1);

    connect(slider1, &QSlider::valueChanged, [this](int value) {
//        if (cur < value) {
            qreal scale = value/10.0;///*qPow(qreal(2), /*(*/slider1->value() /*- 250) / qreal(50)*/);*/

            QMatrix matrix;
            matrix.scale(scale, 1/*scale*/);
//            matrix.rotate(rotateSlider->value());

            view->setMatrix(matrix);

//            view->scale(1.1, 1);
            qDebug() << view->rect() << view->scene->sceneRect() << view->matrix().m11(); //缩放;
            qDebug() << view->rect() << view->horizontalScrollBar()->value()
                     << view->horizontalScrollBar()->maximum(); //缩放;
//        } else {
//            view->scale(0.9, 1);
//        }

        cur = value;
        qDebug() << value << view->mapToScene(QPoint(0, 0));
    });
    slider1->setValue(1);
    btn = new QPushButton(this);
    btn->setText("play");
    btn->setGeometry(10, 390, 400, 20);
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
