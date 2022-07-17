#ifndef S21_SM_CALC_H
#define S21_SM_CALC_H

#include <QMainWindow>
#include <QDebug>
#include <QVector>
#include <QMessageBox>
#include <QPixmap>
#include <cctype>
#include "variable_x.h"
#include "graph_parameters.h"
#include "grid_graphics.h"
//#include "graph_grid.h"
#include "qcustomplot.h"
#include "credit.h"
#include "deposit.h"

extern "C" {
#include "s21_calc_back.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class s21_sm_calc; }
QT_END_NAMESPACE

class s21_sm_calc:public QMainWindow
{
    Q_OBJECT

public:
    s21_sm_calc(QWidget *parent = nullptr);
    ~s21_sm_calc();

private slots:
    void on_image_clicked();
    void numbers_and_brackets();
    void operations();
    void functions();
    void button_clear();
    void button_x_click();
    void button_back_click();
    void dot_click();
    void result_click();
    void on_graph_triggered();
    void on_deposit_triggered();
    void on_credit_triggered();

public slots:
    void get_x(double x);
    void get_graph_x(double x_min, double x_max);
    void return_calc();

private:
    Ui::s21_sm_calc *ui;
    variable_X *x_window;
    graph_parameters *param_window;
    Grid_graphics *graphic_window;
    Credit *credit_window;
    Deposit *deposit_window;
};

QString calculate_result(QString str, double x);

#endif // S21_SM_CALC_H
