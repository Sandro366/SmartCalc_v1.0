#ifndef GRID_GRAPHICS_H
#define GRID_GRAPHICS_H

#include <QWidget>
#include <QVector>
#include "ui_grid_graphics.h"

namespace Ui {
class Grid_graphics;
}

class Grid_graphics : public QWidget
{
    Q_OBJECT

public:
    explicit Grid_graphics(QWidget *parent = nullptr);
    ~Grid_graphics();
    Ui::Grid_graphics *ui;

//private:
//    Ui::Grid_graphics *ui;
};

#endif // GRID_GRAPHICS_H
