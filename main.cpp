/**************************************************************************
**   Created by TemetNosce 2020/7/20
**************************************************************************/
#include "WidgetTest.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetTest w;
    w.show();
    return a.exec();
}
