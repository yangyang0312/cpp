#include <QApplication>
#include "dialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //使用dll
    Dialog d;
    d.show();
    return a.exec();
}
