#include "s21_sm_calc.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    s21_sm_calc w;
    w.show();
    return a.exec();
}
