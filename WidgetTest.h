/**************************************************************************
**   Created by TemetNosce 2020/7/20
**************************************************************************/


#pragma once
#include "AudioTimelineView.h"

#include <QSlider>
#include <QWidget>

class WidgetTest:public QWidget
{
    Q_OBJECT
public:
    explicit
    WidgetTest( QWidget * parent =nullptr);
    AudioTimelineView * view ;
    QSlider* slider1;
    QSlider* slider2;
    int cur = 1;
};

