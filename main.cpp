/**************************************************************************
**   Created by TemetNosce 2020/7/20
**************************************************************************/
#include "Widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
