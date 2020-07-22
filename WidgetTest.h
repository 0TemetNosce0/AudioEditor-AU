/**************************************************************************
**   Created by TemetNosce 2020/7/20
**************************************************************************/


#pragma once
#include "AudioTimelineView.h"

#include <QPushButton>
#include <QSlider>
#include <QTimer>
#include <QWidget>

class WidgetTest:public QWidget
{
    Q_OBJECT
public:
    explicit
    WidgetTest( QWidget * parent =nullptr);
    AudioTimelineView * view ;
    QSlider* slider1;
    QPushButton* btn;
    QTimer  playTimeTest;
    int cur = 1;
};

