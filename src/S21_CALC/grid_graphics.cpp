#include "grid_graphics.h"
#include "ui_grid_graphics.h"

Grid_graphics::Grid_graphics(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Grid_graphics)
{
    ui->setupUi(this);
}

Grid_graphics::~Grid_graphics() {
    delete ui;
}
